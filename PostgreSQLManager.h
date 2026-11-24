#ifndef POSTGRESQL_MANAGER_H
#define POSTGRESQL_MANAGER_H

#include <libpq-fe.h>
#include <chrono>
#include <functional>
#include <string>
#include <vector>

class PostgreSQLManager {
private:
    using Deadline = std::chrono::steady_clock::time_point;

    PGconn* connection = nullptr;
    std::string host, port, dbname, user, password, host_address;
    std::string last_error;
    int connect_timeout_ms;
    int statement_timeout_ms;

    bool waitForSocket(short events, Deadline deadline);
    PGresult* runQuery(const std::string& operation, const std::function<int()>& send);

public:
    PostgreSQLManager();
    ~PostgreSQLManager();
    PostgreSQLManager(const PostgreSQLManager&) = delete;
    PostgreSQLManager& operator=(const PostgreSQLManager&) = delete;

    bool connect();
    void disconnect();
    bool isConnected();

    // The caller owns successful results and releases them with PQclear.
    PGresult* executeQuery(const std::string& query);
    PGresult* executeParams(const std::string& query, int count, const char* const* values);
    bool executeCommand(const std::string& command);
    bool prepareStatement(const std::string& name, const std::string& query);
    PGresult* executePrepared(const std::string& name, const std::vector<std::string>& params);

    std::string getLastError() const;
    void configureFromEnvironment();
    PGconn* getConnection() { return connection; }
};

#endif
