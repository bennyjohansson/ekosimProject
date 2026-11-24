#include "PostgreSQLManager.h"

#include <cerrno>
#include <charconv>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <poll.h>
#include <string_view>

namespace {
using Result = std::unique_ptr<PGresult, decltype(&PQclear)>;

const char* environment(const char* name, const char* fallback)
{
    const char* value = std::getenv(name);
    return value ? value : fallback;
}

int timeoutFromEnvironment(const char* name, int fallback)
{
    const std::string_view value = environment(name, "");
    int timeout = 0;
    const auto end = value.data() + value.size();
    const auto parsed = std::from_chars(value.data(), end, timeout);
    if (parsed.ec == std::errc{} && parsed.ptr == end && timeout > 0 && timeout <= 3600000)
        return timeout;
    if (!value.empty())
        std::cerr << "Invalid " << name << ", using " << fallback << " ms\n";
    return fallback;
}
}

PostgreSQLManager::PostgreSQLManager()
{
    configureFromEnvironment();
}

PostgreSQLManager::~PostgreSQLManager()
{
    disconnect();
}

void PostgreSQLManager::configureFromEnvironment()
{
    host = environment("POSTGRES_HOST", "localhost");
    host_address = environment("POSTGRES_HOSTADDR", "");
    port = environment("POSTGRES_PORT", "5432");
    dbname = environment("POSTGRES_DB", "ekosim");
    user = environment("POSTGRES_USER", "ekosim");
    password = environment("POSTGRES_PASSWORD", "secure_dev_password_2025!");
    connect_timeout_ms = timeoutFromEnvironment("POSTGRES_CONNECT_TIMEOUT_MS", 5000);
    statement_timeout_ms = timeoutFromEnvironment("POSTGRES_STATEMENT_TIMEOUT_MS", 10000);
}

bool PostgreSQLManager::waitForSocket(short events, Deadline deadline)
{
    pollfd socket{PQsocket(connection), events, 0};
    if (socket.fd < 0)
    {
        last_error = "PostgreSQL connection has no socket";
        return false;
    }

    while (true)
    {
        const auto remaining = std::chrono::ceil<std::chrono::milliseconds>(
            deadline - std::chrono::steady_clock::now()).count();
        if (remaining <= 0)
        {
            last_error = "deadline exceeded";
            return false;
        }

        const int ready = poll(&socket, 1, static_cast<int>(remaining));
        if (ready > 0)
            return true; // libpq consumes readiness and reports socket errors.
        if (ready < 0 && errno != EINTR)
        {
            last_error = std::strerror(errno);
            return false;
        }
    }
}

bool PostgreSQLManager::connect()
{
    if (isConnected())
        return true;

    disconnect();
    last_error.clear();

    const std::string options = "-c statement_timeout=" + std::to_string(statement_timeout_ms);
    const char* keys[] = {"host", "hostaddr", "port", "dbname", "user", "password", "options", nullptr};
    const char* values[] = {host.c_str(), host_address.c_str(), port.c_str(), dbname.c_str(),
                            user.c_str(), password.c_str(), options.c_str(), nullptr};
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::milliseconds(connect_timeout_ms);
    connection = PQconnectStartParams(keys, values, 0);

    auto state = PGRES_POLLING_WRITING;
    while (connection && PQstatus(connection) != CONNECTION_BAD)
    {
        if (std::chrono::steady_clock::now() >= deadline)
        {
            last_error = "deadline exceeded";
            break;
        }

        if (state == PGRES_POLLING_READING && !waitForSocket(POLLIN, deadline))
            break;
        if (state == PGRES_POLLING_WRITING && !waitForSocket(POLLOUT, deadline))
            break;

        state = PQconnectPoll(connection);
        if (state == PGRES_POLLING_OK)
        {
            if (PQsetnonblocking(connection, 1) == 0)
                return true;
            break;
        }
        if (state == PGRES_POLLING_FAILED)
            break;
    }

    if (last_error.empty())
        last_error = connection ? PQerrorMessage(connection) : "could not allocate connection";
    last_error = "PostgreSQL connect to " + host + ":" + port + ": " + last_error;
    std::cerr << last_error << '\n';
    disconnect();
    return false;
}

void PostgreSQLManager::disconnect()
{
    if (connection)
    {
        PQfinish(connection);
        connection = nullptr;
    }
}

bool PostgreSQLManager::isConnected()
{
    return connection && PQstatus(connection) == CONNECTION_OK;
}

PGresult* PostgreSQLManager::runQuery(const std::string& operation, const std::function<int()>& send)
{
    if (!isConnected())
    {
        if (last_error.empty())
            last_error = "PostgreSQL connection unavailable";
        return nullptr;
    }

    last_error.clear();
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::milliseconds(statement_timeout_ms);
    const auto fail = [&](std::string message, bool close) -> PGresult* {
        last_error = "PostgreSQL " + operation + ": " + message;
        std::cerr << last_error << '\n';
        if (close)
            disconnect(); // The connection may still have an in-flight query or transaction.
        return nullptr;
    };

    if (!send())
        return fail(PQerrorMessage(connection), true);

    for (int status = PQflush(connection); status != 0; status = PQflush(connection))
    {
        if (status < 0)
            return fail(PQerrorMessage(connection), true);
        if (!waitForSocket(POLLOUT, deadline))
            return fail(last_error, true);
    }

    Result result(nullptr, &PQclear);
    while (true)
    {
        if (std::chrono::steady_clock::now() >= deadline)
            return fail("deadline exceeded", true);
        if (PQisBusy(connection))
        {
            if (!waitForSocket(POLLIN, deadline))
                return fail(last_error, true);
            if (!PQconsumeInput(connection))
                return fail(PQerrorMessage(connection), true);
            continue;
        }

        Result next(PQgetResult(connection), &PQclear);
        if (!next)
            break;
        const auto status = PQresultStatus(next.get());
        if (status == PGRES_COPY_IN || status == PGRES_COPY_OUT || status == PGRES_COPY_BOTH)
            return fail("unexpected COPY response", true);
        result = std::move(next);
    }

    if (!result || !isConnected())
        return fail(PQerrorMessage(connection), true);
    const auto status = PQresultStatus(result.get());
    if (status != PGRES_TUPLES_OK && status != PGRES_COMMAND_OK)
    {
        const char* sqlstate = PQresultErrorField(result.get(), PG_DIAG_SQLSTATE);
        std::string message = PQresultErrorMessage(result.get());
        if (sqlstate)
            message = "SQLSTATE " + std::string(sqlstate) + ": " + message;
        return fail(std::move(message), false);
    }
    return result.release();
}

PGresult* PostgreSQLManager::executeQuery(const std::string& query)
{
    return runQuery(query.substr(0, query.find_first_of(" \t\r\n")), [&] {
        return PQsendQuery(connection, query.c_str());
    });
}

PGresult* PostgreSQLManager::executeParams(const std::string& query, int count, const char* const* values)
{
    return runQuery(query.substr(0, query.find_first_of(" \t\r\n")), [&] {
        return PQsendQueryParams(connection, query.c_str(), count, nullptr, values, nullptr, nullptr, 0);
    });
}

bool PostgreSQLManager::executeCommand(const std::string& command)
{
    Result result(executeQuery(command), &PQclear);
    return result && PQresultStatus(result.get()) == PGRES_COMMAND_OK;
}

bool PostgreSQLManager::prepareStatement(const std::string& name, const std::string& query)
{
    Result result(runQuery("prepare " + name, [&] {
        return PQsendPrepare(connection, name.c_str(), query.c_str(), 0, nullptr);
    }), &PQclear);
    return result && PQresultStatus(result.get()) == PGRES_COMMAND_OK;
}

PGresult* PostgreSQLManager::executePrepared(const std::string& name, const std::vector<std::string>& params)
{
    std::vector<const char*> values;
    values.reserve(params.size());
    for (const auto& param : params)
        values.push_back(param.c_str());
    return runQuery("execute " + name, [&] {
        return PQsendQueryPrepared(connection, name.c_str(), static_cast<int>(values.size()),
                                   values.data(), nullptr, nullptr, 0);
    });
}

std::string PostgreSQLManager::getLastError() const
{
    return last_error;
}
