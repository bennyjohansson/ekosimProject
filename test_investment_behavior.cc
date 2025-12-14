#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>

// Include all necessary headers
#include "company.h"
#include "market.h"
#include "bank.h"
#include "clock.h"
#include "consumer_list.h"

using namespace std;

void setup_test_market(Market* market) {
    // Setup realistic market conditions for testing
    market->set_items(100000);          // Plenty of items available
    market->set_price_in(100.0);        // Price companies sell at
    market->set_price_out(50.0);        // Price companies buy materials at
    market->set_capital(1000000.0);     // Market has sufficient capital
}

void setup_test_bank(Bank* bank) {
    // Setup bank for testing - we can't easily modify internal state
    // but the default constructor should work for testing
}

void setup_test_clock(Clock* clock) {
    // Clock should work with default state for testing
    // The time will be used by investment calculations
}

int main() {
    cout << "=== Investment Behavior Analysis ===" << endl;
    cout << "Testing get_desired_investment() and get_investment_cashflow() at different capacities" << endl;
    cout << "===============================================" << endl;

    // Create test infrastructure
    Market* local_market = new Market("LocalMarket");
    Market* global_market = new Market("GlobalMarket");
    Bank* bank = new Bank("TestBank", 0.05, 120); // 5% interest, 120 month payback
    Clock* clock = new Clock();
    
    // Setup test conditions
    setup_test_market(local_market);
    setup_test_market(global_market);
    setup_test_bank(bank);
    setup_test_clock(clock);

    // Test parameters
    vector<double> test_capacities = {1000, 3000, 5000, 10000, 15000, 20000, 30000};
    vector<double> test_capital_levels = {10000, 50000, 100000};
    
    // Create CSV output file
    ofstream csv_file("investment_analysis.csv");
    csv_file << "Capacity,Capital,Skill_Const,Mot_Const,Desired_Investment,Expected_Cashflow,NPV_Estimate" << endl;

    for (double capacity : test_capacities) {
        for (double capital : test_capital_levels) {
            cout << "\n--- Testing Capacity: " << capacity << ", Capital: " << capital << " ---" << endl;
            
            // Create company with specific capacity and capital
            Company test_company("TestCorp", "TestCity", capital, 0, capacity, 
                               60.0, 40.0, 0.1, 0.6, local_market, global_market, bank, clock);
            
            // Note: Company constructor creates its own employee list
            // No need to manually add employees for this test
            
            try {
                // Test get_desired_investment
                int desired_investment = test_company.get_desired_investment();
                
                // Test get_investment_cashflow with sample parameters
                double sample_capacity_investment = desired_investment * 0.5;
                double sample_efficiency_items = desired_investment * 0.25;
                double sample_efficiency_factor = desired_investment * 0.25;
                double sample_loans = max(0.0, desired_investment * 50.0 - capital * 0.6); // Estimate loans needed
                
                double expected_cashflow = test_company.get_investment_cashflow(
                    sample_capacity_investment,
                    sample_efficiency_items, 
                    sample_efficiency_factor,
                    sample_loans,
                    0.002, // FacIncreaseRate_1
                    8000,  // CapIncreaseParam_1  
                    0.0001, // CapIncreaseRate_1
                    0.001   // ItemEfficiencyRate
                );
                
                double npv_estimate = expected_cashflow - (desired_investment * 50.0); // Rough NPV
                
                // Output results
                cout << "Desired Investment: " << desired_investment << " items" << endl;
                cout << "Expected Cashflow: " << expected_cashflow << endl;
                cout << "Estimated NPV: " << npv_estimate << endl;
                
                // Write to CSV
                csv_file << capacity << "," << capital << "," << 60.0 << "," << 40.0 
                        << "," << desired_investment << "," << expected_cashflow 
                        << "," << npv_estimate << endl;
                        
            } catch (const exception& e) {
                cout << "Error testing capacity " << capacity << ": " << e.what() << endl;
            }
        }
    }
    
    csv_file.close();
    
    cout << "\n=== Analysis Complete ===" << endl;
    cout << "Results saved to investment_analysis.csv" << endl;
    cout << "You can open this in Excel or use gnuplot/matplotlib for visualization" << endl;

    // Cleanup
    delete local_market;
    delete global_market; 
    delete bank;
    delete clock;
    
    return 0;
}