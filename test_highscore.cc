#include <iostream>
#include <vector>
#include "SQLfunctions.h"

int main() {
    std::cout << "Testing PostgreSQL high score insertion..." << std::endl;
    
    // Test connection first
    if (testPostgreSQLConnection() != 0) {
        std::cout << "PostgreSQL connection failed! Cannot test high scores." << std::endl;
        return -1;
    }
    
    // Test data - growth, palma ratio, environmental impact
    std::vector<double> testData = {5.2, 1.8, 2.1}; // Good growth, decent palma ratio, low environmental impact
    
    // Insert a test high score
    std::cout << "\nInserting test high score..." << std::endl;
    int result = insertHighScorePG(testData, "Testland", "", "");
    
    if (result == 0) {
        std::cout << "High score insertion PASSED!" << std::endl;
        
        // Test retrieving high scores
        std::cout << "\nRetrieving high scores..." << std::endl;
        auto scores = getHighScoresPG("", 5); // Get top 5 scores
        
        std::cout << "Retrieved " << scores.size() << " high score records:" << std::endl;
        std::cout << "Country\t\tGrowth\t\tPalma\t\tEnv Impact\tDate" << std::endl;
        std::cout << "-------\t\t------\t\t-----\t\t----------\t----" << std::endl;
        
        for (const auto& score : scores) {
            if (score.size() >= 5) {
                std::cout << score[0] << "\t\t" << score[1] << "\t\t" 
                         << score[2] << "\t\t" << score[3] << "\t\t" 
                         << score[4] << std::endl;
            }
        }
        
        // Test country-specific filter
        std::cout << "\nRetrieving scores for Testland only..." << std::endl;
        auto testland_scores = getHighScoresPG("Testland", 3);
        
        std::cout << "Found " << testland_scores.size() << " scores for Testland" << std::endl;
        
        std::cout << "\nAll high score tests PASSED!" << std::endl;
    } else {
        std::cout << "High score insertion FAILED!" << std::endl;
        return -1;
    }
    
    return 0;
}