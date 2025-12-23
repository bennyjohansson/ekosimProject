#include "PostgreSQLManager.h"
#include <iostream>

int main() {
    std::cout << "Checking high_scores table structure..." << std::endl;
    
    PostgreSQLManager pgManager;
    
    if (!pgManager.connect()) {
        std::cerr << "Failed to connect to PostgreSQL" << std::endl;
        return 1;
    }
    
    // Check the actual structure of high_scores table
    std::string describeTableSQL = "SELECT column_name, data_type, is_nullable "
                                  "FROM information_schema.columns "
                                  "WHERE table_schema = 'public' "
                                  "AND table_name = 'high_scores' "
                                  "ORDER BY ordinal_position;";
    
    PGresult* result = pgManager.executeQuery(describeTableSQL);
    
    if (result && PQntuples(result) > 0) {
        std::cout << "High scores table structure:" << std::endl;
        std::cout << "Column Name\t\tData Type\t\tNullable" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        
        for (int i = 0; i < PQntuples(result); i++) {
            std::cout << PQgetvalue(result, i, 0) << "\t\t\t" 
                     << PQgetvalue(result, i, 1) << "\t\t" 
                     << PQgetvalue(result, i, 2) << std::endl;
        }
        
        PQclear(result);
    } else {
        std::cerr << "Failed to get table structure or table doesn't exist" << std::endl;
        return 1;
    }
    
    return 0;
}