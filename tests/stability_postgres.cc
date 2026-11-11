#include "PostgreSQLManager.h"
#include "SQLfunctions.h"

#include <cassert>
#include <chrono>
#include <cstdlib>
#include <memory>
#include <string_view>
#include <tuple>

using ConsumerRows = std::vector<std::tuple<std::string, std::string, std::string, int,
    double, double, double, double, double, double, double, double, double, double, double>>;

int main(int argc, char** argv)
{
    using namespace std::chrono;
    if (argc == 2 && std::string_view(argv[1]) == "--unavailable")
    {
        PostgreSQLManager unavailable;
        const auto start = steady_clock::now();
        assert(!unavailable.connect());
        assert(steady_clock::now() - start < seconds(5));
        assert(unavailable.getLastError().find("connect") != std::string::npos);
        return 0;
    }

    // Run only against an empty, disposable test database.
    PostgreSQLManager admin;
    assert(admin.connect());
    assert(admin.executeCommand(
        "CREATE TABLE consumer_data (city_name text, consumer_name text, employer text, "
        "items integer CHECK (items >= 0), capital float8, deposits float8, debts float8, "
        "skill float8, mot float8, spendwill float8, savewill float8, borrowwill float8, "
        "income float8, dividends float8, transfers float8, updated_at timestamp, "
        "PRIMARY KEY (city_name, consumer_name))"));

    ConsumerRows valid{{"Alice", "", "", 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
    assert(batchInsertConsumerDataPG(valid, "test") == 0);

    ConsumerRows invalid = valid;
    std::get<3>(invalid[0]) = 2;
    invalid.emplace_back("Bob", "", "", -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    assert(batchInsertConsumerDataPG(invalid, "test") != 0);

    const auto checkItems = [&](const char* expected) {
        std::unique_ptr<PGresult, decltype(&PQclear)> result(
            admin.executeQuery("SELECT items FROM consumer_data WHERE city_name = 'test'"), &PQclear);
        assert(result && PQntuples(result.get()) == 1);
        assert(std::string_view(PQgetvalue(result.get(), 0, 0)) == expected);
    };
    checkItems("1");

    assert(admin.executeCommand("BEGIN"));
    assert(admin.executeCommand("LOCK TABLE consumer_data IN ACCESS EXCLUSIVE MODE"));
    assert(setenv("POSTGRES_STATEMENT_TIMEOUT_MS", "150", 1) == 0);
    const auto start = steady_clock::now();
    assert(batchInsertConsumerDataPG(valid, "test") != 0);
    assert(steady_clock::now() - start < seconds(3));
    assert(admin.executeCommand("ROLLBACK"));
    assert(unsetenv("POSTGRES_STATEMENT_TIMEOUT_MS") == 0);

    std::get<3>(valid[0]) = 3;
    assert(batchInsertConsumerDataPG(valid, "test") == 0);
    checkItems("3");
    assert(admin.executeCommand("DROP TABLE consumer_data"));
}
