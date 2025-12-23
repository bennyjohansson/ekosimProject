#include "PostgreSQLManager.h"

PostgreSQLManager::PostgreSQLManager() : connection(nullptr) {
    configureFromEnvironment();
}

PostgreSQLManager::~PostgreSQLManager() {
    disconnect();
}

void PostgreSQLManager::configureFromEnvironment() {
    const char* host = getenv("POSTGRES_HOST");
    if (!host) host = "ekosim-postgres";
    
    const char* port = getenv("POSTGRES_PORT");
    if (!port) port = "5432";
    
    const char* dbname = getenv("POSTGRES_DB");
    if (!dbname) dbname = "ekosim";
    
    const char* user = getenv("POSTGRES_USER");
    if (!user) user = "ecosim_user";
    
    const char* password = getenv("POSTGRES_PASSWORD");
    
    connection_string = "host=" + std::string(host) + 
                       " port=" + std::string(port) +
                       " dbname=" + std::string(dbname) +
                       " user=" + std::string(user);
    
    if (password) {
        connection_string += " password=" + std::string(password);
    }
    
    std::cout << "PostgreSQL connection configured for host: " << host << ", db: " << dbname << std::endl;
}

bool PostgreSQLManager::connect() {
    if (connection && isConnected()) {
        return true; // Already connected
    }
    
    connection = PQconnectdb(connection_string.c_str());
    
    if (PQstatus(connection) != CONNECTION_OK) {
        std::cerr << "PostgreSQL connection failed: " << PQerrorMessage(connection) << std::endl;
        PQfinish(connection);
        connection = nullptr;
        return false;
    }
    
    std::cout << "Successfully connected to PostgreSQL" << std::endl;
    return true;
}

void PostgreSQLManager::disconnect() {
    if (connection) {
        PQfinish(connection);
        connection = nullptr;
        std::cout << "Disconnected from PostgreSQL" << std::endl;
    }
}

bool PostgreSQLManager::isConnected() {
    return connection && PQstatus(connection) == CONNECTION_OK;
}

PGresult* PostgreSQLManager::executeQuery(const std::string& query) {
    if (!isConnected()) {
        std::cerr << "Not connected to PostgreSQL" << std::endl;
        return nullptr;
    }
    
    PGresult* result = PQexec(connection, query.c_str());
    
    if (PQresultStatus(result) != PGRES_TUPLES_OK && PQresultStatus(result) != PGRES_COMMAND_OK) {
        std::cerr << "Query failed: " << PQerrorMessage(connection) << std::endl;
        std::cerr << "Query was: " << query << std::endl;
        PQclear(result);
        return nullptr;
    }
    
    return result;
}

bool PostgreSQLManager::executeCommand(const std::string& command) {
    PGresult* result = executeQuery(command);
    if (result) {
        PQclear(result);
        return true;
    }
    return false;
}

bool PostgreSQLManager::prepareStatement(const std::string& name, const std::string& query) {
    if (!isConnected()) {
        std::cerr << "Not connected to PostgreSQL" << std::endl;
        return false;
    }
    
    PGresult* result = PQprepare(connection, name.c_str(), query.c_str(), 0, NULL);
    
    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        std::cerr << "Prepare failed: " << PQerrorMessage(connection) << std::endl;
        PQclear(result);
        return false;
    }
    
    PQclear(result);
    return true;
}

PGresult* PostgreSQLManager::executePrepared(const std::string& name, const std::vector<std::string>& params) {
    if (!isConnected()) {
        std::cerr << "Not connected to PostgreSQL" << std::endl;
        return nullptr;
    }
    
    // Convert vector<string> to array of char*
    std::vector<const char*> paramValues;
    for (const auto& param : params) {
        paramValues.push_back(param.c_str());
    }
    
    PGresult* result = PQexecPrepared(connection, name.c_str(), params.size(), 
                                     paramValues.data(), NULL, NULL, 0);
    
    if (PQresultStatus(result) != PGRES_TUPLES_OK && PQresultStatus(result) != PGRES_COMMAND_OK) {
        std::cerr << "Prepared statement execution failed: " << PQerrorMessage(connection) << std::endl;
        PQclear(result);
        return nullptr;
    }
    
    return result;
}

std::string PostgreSQLManager::getLastError() {
    if (connection) {
        return std::string(PQerrorMessage(connection));
    }
    return "No connection";
}