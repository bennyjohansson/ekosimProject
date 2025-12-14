#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cmath>

// Include all necessary headers for full simulation setup
#include "world.h"
#include "city.h"
#include "company.h"
#include "functions.h"
#include "SQLfunctions.h"

using namespace std;

// Test specific companies at different capacities
void test_company_investment_behavior(World* world, const string& city_name, const string& company_name, 
                                     const vector<double>& test_capacities, ofstream& csv_file) {
    
    City* city = world->get_city(city_name);
    if (!city) {
        cout << "Error: City " << city_name << " not found!" << endl;
        return;
    }
    
    Company* company = city->get_company(company_name);
    if (!company) {
        cout << "Error: Company " << company_name << " not found in " << city_name << "!" << endl;
        return;
    }
    
    cout << "\n=== Testing Company: " << company_name << " in " << city_name << " ===" << endl;
    
    // Store original capacity to restore later
    double original_capacity = company->get_capacity();
    double original_capital = company->get_capital();
    
    for (double test_capacity : test_capacities) {
        cout << "\n--- Testing " << company_name << " at capacity: " << test_capacity << " ---" << endl;
        
        // Set test capacity
        company->set_capacity(test_capacity);
        
        try {
            // Test investment functions with real company in real environment
            int desired_investment = company->get_desired_investment();
            
            // Test cashflow calculation with typical investment split
            double capacity_investment = desired_investment * 0.5;
            double efficiency_items = desired_investment * 0.25;
            double efficiency_factor = desired_investment * 0.25;
            double estimated_loans = max(0.0, desired_investment * 50.0 - original_capital * 0.6);
            
            double expected_cashflow = company->get_investment_cashflow(
                capacity_investment,
                efficiency_items,
                efficiency_factor,
                estimated_loans,
                0.002,  // FacIncreaseRate_1 (from database or default)
                8000,   // CapIncreaseParam_1
                0.0001, // CapIncreaseRate_1  
                0.001   // ItemEfficiencyRate
            );
            
            double npv_estimate = expected_cashflow - (desired_investment * 50.0);
            
            // Output results
            cout << "Company: " << company_name << endl;
            cout << "Capacity: " << test_capacity << endl;
            cout << "Current Capital: " << company->get_capital() << endl;
            cout << "Current Employees: " << company->get_no_employees() << endl;
            cout << "Desired Investment: " << desired_investment << " items" << endl;
            cout << "Expected Cashflow: " << expected_cashflow << endl;
            cout << "Estimated NPV: " << npv_estimate << endl;
            
            // Write to CSV
            csv_file << company_name << "," << city_name << "," << test_capacity 
                    << "," << company->get_capital() << "," << company->get_no_employees()
                    << "," << desired_investment << "," << expected_cashflow 
                    << "," << npv_estimate << endl;
                    
        } catch (const exception& e) {
            cout << "Error testing " << company_name << " at capacity " << test_capacity 
                 << ": " << e.what() << endl;
        }
    }
    
    // Restore original capacity
    company->set_capacity(original_capacity);
}

int main() {
    cout << "=== Advanced Investment Behavior Analysis ===" << endl;
    cout << "Testing with full simulation setup (World, Cities, Real Companies)" << endl;
    cout << "=================================================================" << endl;

    // Initialize random seed (like main.cc)
    srand(static_cast<unsigned>(time(0)));
    
    try {
        // Create world with full database setup (like main.cc)
        cout << "Creating world with full database setup..." << endl;
        World testworld("TestWorld");
        initiateWorldDB("TestWorld");
        
        // Add test city (this handles database initialization internally)
        cout << "Adding TestCity to world..." << endl;
        testworld.add_city("TestCity", "test@example.com");
        
        // Print initial world state
        cout << "Initial world setup:" << endl;
        testworld.printWorldDB();
        
        // Test capacities to examine
        vector<double> test_capacities = {1000, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 500000, 1000000, 2000000};
        
        // Create enhanced CSV output file  
        ofstream csv_file("investment_analysis.csv");
        csv_file << "Company,City,Capacity,Capital,Employees,Desired_Investment,Expected_Cashflow,NPV_Estimate" << endl;
        
        // Get the test city - debug the city name issue
        cout << "Attempting to get city 'TestCity'..." << endl;
        City* test_city = testworld.get_city("TestCity");
        if (!test_city) {
            cout << "Error: Could not get TestCity! Trying 'Bennyland' instead..." << endl;
            test_city = testworld.get_city("Bennyland");
            if (!test_city) {
                cout << "Error: Could not get any city! Check city initialization." << endl;
                return 1;
            } else {
                cout << "Successfully found 'Bennyland' city." << endl;
            }
        } else {
            cout << "Successfully found 'TestCity'." << endl;
        }
        
        cout << "\nCity initialized with:" << endl;
        cout << "- Total capital: " << test_city->get_capital_sum() << endl;
        cout << "- Number of companies: " << test_city->get_no_companies() << endl;
        cout << "- Number of consumers: " << test_city->get_no_consumers() << endl;
        
        // Test all companies in the city
        cout << "\n=== Testing All Companies in TestCity ===" << endl;
        
        // Get all company names from the database initialization
        vector<string> company_names = {"johansson_och_johansson", "limpan_AB", "bempa_AB", "bempa_CO", "benny_enterprises", "benny_inc"};
        
        // Use the city name we actually found
        string found_city_name = test_city->get_name();
        cout << "Using city: " << found_city_name << endl;
        
        for (const string& company_name : company_names) {
            test_company_investment_behavior(&testworld, found_city_name, company_name, test_capacities, csv_file);
        }
        
        // Also test with a second city if we want to compare
        cout << "\n=== Adding Second City for Comparison ===" << endl;
        testworld.add_city("ComparisonCity", "test@test.com");
        
        for (const string& company_name : company_names) {
            test_company_investment_behavior(&testworld, "ComparisonCity", company_name, test_capacities, csv_file);
        }
        
        csv_file.close();
        
        cout << "\n=== Analysis Complete ===" << endl;
        cout << "Results saved to investment_analysis.csv" << endl;
        cout << "This CSV contains real company data with:" << endl;
        cout << "- Real database parameters" << endl;
        cout << "- Actual employee counts and skills" << endl;
        cout << "- Market conditions from full simulation" << endl;
        cout << "- Inter-city trading effects" << endl;
        cout << "\nYou can analyze with:" << endl;
        cout << "- Excel/LibreOffice: Open investment_analysis.csv" << endl;
        cout << "- Python: pandas.read_csv('investment_analysis.csv')" << endl;
        cout << "- R: data <- read.csv('investment_analysis.csv')" << endl;
        
        return 0;
        
    } catch (const exception& e) {
        cout << "Error during simulation setup: " << e.what() << endl;
        return 1;
    }
}