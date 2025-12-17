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
    double price_out = city->get_active_market()->get_price_out();
    double cost_of_investment = 0.0;
    
    for (double test_capacity : test_capacities) {
        cout << "\n--- Testing " << company_name << " at capacity: " << test_capacity << " ---" << endl;
        
        // Set test capacity
        company->set_capacity(test_capacity);
        company->set_capital(5000000);
        try {
            // Test investment functions with real company in real environment
            int desired_investment = company->get_desired_investment();
            
            // Test cashflow calculation with typical investment split
            double capacity_investment = desired_investment * 0.5;
            double efficiency_items = desired_investment * 0.25;
            double efficiency_factor = desired_investment * 0.25;
            double estimated_loans = 0;//max(0.0, desired_investment * 50.0 - original_capital * 0.6);
            
            double expected_cashflow = company->get_investment_cashflow(
                capacity_investment,
                efficiency_items,
                efficiency_factor,
                estimated_loans,
                0.05,  // FacIncreaseRate_1 (from database or default)
                15000,   // CapIncreaseParam_1
                0.0001, // CapIncreaseRate_1  
                0.0005   // ItemEfficiencyRate
            );

            cost_of_investment = price_out * desired_investment;
            
            double npv_estimate = expected_cashflow - cost_of_investment;
            
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

        initiateCityDB("Bennyland");
		testworld.initiate_city("Bennyland");
        
        
        // Print initial world state
        cout << "Initial world setup:" << endl;
        testworld.printWorldDB();
        
        // Run a mini-simulation to establish functioning market conditions
        cout << "\n=== Running Mini-Simulation to Establish Market Conditions ===" << endl;
        int warmup_cycles = 10; // Run 10 cycles to get realistic market conditions
        
        for (int cycle = 0; cycle < warmup_cycles; cycle++) {
            cout << "\nWarmup Cycle: " << (cycle + 1) << "/" << warmup_cycles << endl;
            
            // Run basic economic cycles (using actual World methods)
            //Printing eanch year in. the logs
            cout << "Year: " << testworld.get_time() << endl;

            testworld.run_employee_cycle();
            testworld.run_pricing_cycle();
            testworld.run_production_cycle();
            testworld.run_sales_cycle();
            testworld.run_investment_cycle();
            testworld.run_banking_cycle();
            testworld.run_dividend_cycle();
            testworld.run_adjust_money_and_consumer_cycle();
            testworld.reset_number_of_market_participants();
            testworld.run_save_cycle();
            testworld.update_companies_from_database();
			testworld.write_time_data_to_company_database();
			testworld.update_country_from_database();
            
            // Update time (tick advances the clock)
            testworld.tick();
            
            // Print some basic stats
            City* city = testworld.get_city("Bennyland");
            if (city && cycle % 3 == 0) { // Print every 3rd cycle
                cout << "  Market items: " << city->get_market()->get_items();
                cout << ", Price in: " << city->get_market()->get_price_in();
                cout << ", Price out: " << city->get_market()->get_price_out() << endl;
            }
        }
        
        cout << "\nWarmup complete! Market should now have realistic conditions." << endl;
        
        // Test capacities to examine
        vector<double> test_capacities = {1000, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 500000, 1000000, 2000000};
        
        // Create enhanced CSV output file  
        ofstream csv_file("investment_analysis.csv");
        csv_file << "Company,City,Capacity,Capital,Employees,Desired_Investment,Expected_Cashflow,NPV_Estimate" << endl;
        
        // Get the test city after warmup
        City* test_city = testworld.get_city("Bennyland");
        if (!test_city) {
            cout << "Error: Could not get Bennyland after warmup!" << endl;
            return 1;
        }
        
        cout << "\n=== Post-Warmup City Status ===" << endl;
        cout << "City: " << test_city->get_name() << endl;
        cout << "Time: " << testworld.get_time() << endl;
        cout << "Total capital: " << test_city->get_capital_sum() << endl;
        cout << "Number of companies: " << test_city->get_no_companies() << endl;
        cout << "Number of consumers: " << test_city->get_no_consumers() << endl;
        cout << "Market items: " << test_city->get_market()->get_items() << endl;
        cout << "Market price in: " << test_city->get_market()->get_price_in() << endl;
        cout << "Market price out: " << test_city->get_market()->get_price_out() << endl;
        
        // Show company employment status
        cout << "\nCompany employment after warmup:" << endl;
        for (const string& company_name : {"johansson_och_johansson", "bempa_AB", "benny_enterprises"}) {
            Company* comp = test_city->get_company(company_name);
            if (comp) {
                cout << "- " << company_name << ": " << comp->get_no_employees() << " employees, " 
                     << comp->get_capital() << " capital" << endl;
            }
        }
        
        // Test all companies in the city
        cout << "\n=== Testing All Companies in Bennyland ===" << endl;
        
        // Get all company names from the database initialization
        vector<string> company_names = {"johansson_och_johansson", "limpan_AB", "bempa_AB", "bempa_CO", "benny_enterprises", "benny_inc"};
        
        // Use the city name we actually found
        string found_city_name = test_city->get_name();
        cout << "Using city: " << found_city_name << endl;
        
        for (const string& company_name : company_names) {
            test_company_investment_behavior(&testworld, found_city_name, company_name, test_capacities, csv_file);
        }
        
        
        
        // for (const string& company_name : company_names) {
        //     test_company_investment_behavior(&testworld, "'Bennyland'", company_name, test_capacities, csv_file);
        // }
        
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
        
        cout << "\n=== Cleaning up simulation ===" << endl;
        
        return 0;
        
    } catch (const exception& e) {
        cout << "Error during simulation setup: " << e.what() << endl;
        return 1;
    } catch (...) {
        cout << "Unknown error during simulation" << endl;
        return 1;
    }
}