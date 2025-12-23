#include <iostream>
#include "SQLfunctions.h"

int main() {
    std::cout << "Testing PostgreSQL connection from C++..." << std::endl;
    
    int result = testPostgreSQLConnection();
    
    if (result == 0) {
        std::cout << "PostgreSQL connection test PASSED!" << std::endl;
    } else {
        std::cout << "PostgreSQL connection test FAILED!" << std::endl;
    }
    
    return result;
}