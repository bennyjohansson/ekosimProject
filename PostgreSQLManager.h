#ifndef POSTGRESQL_MANAGER_H
#define POSTGRESQL_MANAGER_H

#include <libpq-fe.h>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <cstdlib>

class PostgreSQLManager {
private:
    PGconn* connection;
    std::string connection_string;
    
public:
    PostgreSQLManager();
    ~PostgreSQLManager();
    
    bool connect();
    void disconnect();
    bool isConnected();
    
    // High-level query methods
    PGresult* executeQuery(const std::string& query);
    bool executeCommand(const std::string& command);
    
    // Prepared statement support
    bool prepareStatement(const std::string& name, const std::string& query);
    PGresult* executePrepared(const std::string& name, const std::vector<std::string>& params);
    
    // Error handling
    std::string getLastError();
    
    // Connection configuration from environment
    void configureFromEnvironment();
    
    // Get connection for direct access if needed
    PGconn* getConnection() { return connection; }
};

#endif