#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <exception>
#include <stdexcept>

#include "city_list.h"
//#include "error_no_return.h"

using namespace std;

// City_list::City_list(string name) :
// list_(std::make_unique<Element_city>(nullptr, new City("Bennyland"))),
// size_(1), 
// name_(name)
// {}

// City_list::City_list(string name, Clock * clock) :
// list_(std::make_unique<Element_city>(nullptr, new City("Bennyland", clock))),
// size_(1), 
// name_(name)
// {}

City_list::City_list(string name, Clock * clock, Market * global_market) :
list_(std::make_unique<Element_city>(nullptr, new City("Bennyland", clock, global_market))),
size_(1), 
name_(name)
{}

/*
 * Functions to add cities
 */ 

City * City_list::get_city(string name) {
    Element_city * p;
    
    if(list_) {
        for(p = list_.get(); p; p = p -> next_.get()) {
            if (p ->get_name() == name) {
                return p -> get_city() ;
            }
        }
        //throw no_return_error("Cant find the city");
        throw std::runtime_error(std::string("Cant find the city"));
    }
    else {
        // throw no_return_error("no list"); 
        throw std::runtime_error(std::string("No city list"));
        
    } 
}

double City_list::get_capital_sum() const {
    Element_city * p;
    double sum = 0;
    
    if(list_) {
        for (p = list_.get(); p; p = p -> next_.get()) {
            sum += p -> get_city() -> get_capital_sum();
        }
    } 
    else {
        throw std::runtime_error(std::string("No city list"));
    }
    
    return sum; 
}

double City_list::get_added_capital_sum() const {
    Element_city * p;
    double sum = 0;
    
    if(list_) {
        for (p = list_.get(); p; p = p -> next_.get()) {
            sum += p -> get_city() -> get_loans_to_bank();
        }
    }   
    else {
        throw std::runtime_error(std::string("No city list"));
    }
    
    return sum; 
}

/*
 * Functions to add cities
 */ 

void City_list::add_city(City * city) {
    //Element_city * p;
    size_++;
    
    if(list_) {
        list_ = std::make_unique<Element_city>(std::move(list_), city);
    }
    else {
        list_ = std::make_unique<Element_city>(nullptr, city);
    }
}


/*
 * Info-functions
 */

void City_list::info() {
    cout << endl << "CITIES" << endl << "----------------------------------------------------------" << endl; 
    cout << "Number of cities: " << size_ << endl << endl;
}


void City_list::print_list() {
    
    info();
    if(list_) {
        for (Element_city *p = list_.get(); p; p = p -> next_.get()) {
            p->city_->info();
        }
    }
    
    cout << endl; 
}

void City_list::print_GDP() {
    
    if(list_) {
        for (Element_city *p = list_.get(); p; p = p -> next_.get()) {
            p->city_-> print_GDP();
        }
    }
    
    cout << endl; 
}

bool City_list::update_employees() {

    Element_city * p;
    if(list_) {
        for(p = list_.get(); p; p = p -> next_.get()) {
            
            cout << endl << " -- " << p-> get_city() -> get_name() << " -- " << endl;
            p -> get_city() -> update_employees();
        }
    }
    else {
        cout << "No countries to update employees" << endl;
        return false;
    }
    return true;
    
}

bool City_list::run_supply_demand_cycle() {
    
    Element_city * p;
    if(list_) {
        for(p = list_.get(); p; p = p -> next_.get()) {
            cout << endl << " -- " << p-> get_city() -> get_name() << " -- " << endl;
            cout << "Running supply demand cycle" << endl;
            p -> get_city() -> update_supply_and_demand();
        }
    }
    else {
        cout << "No countries to run supply demand cycle" << endl;
        return false;
    }
    return true;
}

bool City_list::update_market_price() {
    Element_city * p;
    if(list_) {
        for(p = list_.get(); p; p = p -> next_.get()) {
            cout << endl << " -- " << p-> get_city() -> get_name() << " -- " << endl;
            cout << "Updating market price" << endl;
            p -> get_city() -> update_market_price();

        }
    }
    else {
        cout << "No countries to update price" << endl;
        return false;
    }
    return true;
    
}

bool City_list::reset_market_calculations() {
    Element_city * p;
    if(list_) {
        for(p = list_.get(); p; p = p -> next_.get()) {
            cout << endl << " -- " << p-> get_city() -> get_name() << " -- " << endl;
            cout << "Resetting market calculations" << endl;
            p -> get_city() -> reset_supply_and_demand();
        }
    }
    else {
        cout << "No countries to reset market calculations" << endl;
        return false;
    }
    return true;
    
}

bool City_list::run_production_cycle() {

    Element_city * p;
    if(list_) {
        for(p = list_.get(); p; p = p -> next_.get()) {
            cout << endl << " -- " << p-> get_city() -> get_name() << " -- " << endl;
            cout << "Produce" << endl;
            p -> get_city() -> produce();
        }
    }
    else {
        cout << "No countries to run production cycle" << endl;
        return false;
    }
    return true;
    
}

bool City_list::run_employee_pricing_and_production_cycle() {

    Element_city * p;
    if(list_) {
        for(p = list_.get(); p; p = p -> next_.get()) {
            cout << endl << " -- " << p-> get_city() -> get_name() << " -- " << endl;
            cout << "Updating employees" << endl;
            p -> get_city() -> update_employees();
            cout << "Negotiate market price" << endl;
            p -> get_city() -> negotiate_market_price();
            cout << "Produce" << endl;
            p -> get_city() -> produce();
        }
    }
    else {
        cout << "No countries to run production cycle" << endl;
        return false;
    }
    return true;
    
}

bool City_list::run_sales_cycle() {

    	// bennyland.update_companies();
		// bennyland.save_data();
		// bennyland.sell_to_market();
		// bennyland.consumers_buy();
		// bennyland.pay_company_employees();

        double temp_money = 0;
        

    Element_city * p;
    if(list_) {
        for(p = list_.get(); p; p = p -> next_.get()) {
            temp_money = p-> get_city() -> get_capital_sum();
            cout << endl << " -- " << p-> get_city() -> get_name() << " -- " << endl;
            
            p -> get_city() -> update_companies();
            if(std::abs(temp_money - p-> get_city() -> get_capital_sum()) > 0.01) {cout << "Leakage in update_companies!" << endl; temp_money = p-> get_city() -> get_capital_sum();}
            p -> get_city() -> save_data();
            p -> get_city() -> sell_to_market();
            if(std::abs(temp_money - p-> get_city() -> get_capital_sum()) > 0.01) {cout << "Leakage in sell_to_market!" << endl; temp_money = p-> get_city() -> get_capital_sum();}
            p -> get_city() -> consumers_buy();
            if(std::abs(temp_money - p-> get_city() -> get_capital_sum()) > 0.01) {cout << "Leakage in consumers_buy!" << endl; temp_money = p-> get_city() -> get_capital_sum();}
            p -> get_city() -> pay_company_employees();
            if(std::abs(temp_money - p-> get_city() -> get_capital_sum()) > 0.01) {cout << "Leakage in pay_employees!" << endl; temp_money = p-> get_city() -> get_capital_sum();}
        }
    }
    else {
        cout << "No countries to run sales cycle" << endl;
        return false;
    }
    return true;
    
}

bool City_list::run_investment_cycle() {

		// bennyland.update_interest_parameters();
    	// bennyland.update_interest_rate();
    	// bennyland.invest(true);

    Element_city * p;
    if(list_) {
        for(p = list_.get(); p; p = p -> next_.get()) {
            cout << endl << " -- " << p-> get_city() -> get_name() << " -- " << endl;
            p -> get_city() -> update_interest_parameters();
            p -> get_city() -> update_interest_rate();
            p -> get_city() -> invest(true);
        }
    }
    else {
        cout << "No countries to run investment cycle" << endl;
        return false;
    }
    return true;
    
}



bool City_list::run_banking_cycle() {

		// bennyland.consumers_bank_business();
		// bennyland.company_pay_interest();
		// bennyland.company_repay_to_bank();

    Element_city * p;
    if(list_) {
        for(p = list_.get(); p; p = p -> next_.get()) {
            cout << endl << " -- " << p-> get_city() -> get_name() << " -- " << endl;
            p -> get_city() -> consumers_bank_business();
            p -> get_city() -> company_pay_interest();
            p -> get_city() -> company_repay_to_bank();
        }
    }
    else {
        cout << "No countries to run banking cycle" << endl;
        return false;
    }
    return true;
    
}

bool City_list::run_dividend_cycle() {

    	//bennyland.company_pay_dividends();
    	//bennyland.pay_transfers();

    Element_city * p;
    if(list_) {
        for(p = list_.get(); p; p = p -> next_.get()) {
            cout << endl << " -- " << p-> get_city() -> get_name() << " -- " << endl;
            p -> get_city() -> company_pay_dividends();
            p -> get_city() -> pay_transfers();
        }
    }
    else {
        cout << "No countries to run dividend cycle" << endl;
        return false;
    }
    return true;
    
}

bool City_list::run_save_cycle() {

    // bennyland.save_money_data();

    Element_city * p;
    if(list_) {
        for(p = list_.get(); p; p = p -> next_.get()) {
            cout << endl << " -- " << p-> get_city() -> get_name() << " -- " << endl;
            p -> get_city() -> save_money_data();
        }
    }
    else {
        cout << "No countries to run save cycle" << endl;
        return false;
    }
    return true;
    
}

bool City_list::run_adjust_money_and_consumer_cycle() {

    	// bennyland.adjust_money();
    	// bennyland.update_consumer_list();

    Element_city * p;
    if(list_) {
        for(p = list_.get(); p; p = p -> next_.get()) {
            cout << endl << " -- " << p-> get_city() -> get_name() << " -- " << endl;
            p -> get_city() -> adjust_money(); 
            p -> get_city() -> update_consumer_list();
        }
    }
    else {
        cout << "No countries to run adjust cycle" << endl;
        return false;
    }
    return true;
    
}




bool City_list::update_companies_from_database() {

    	

    Element_city * p;

    if(list_) {
        for(p = list_.get(); p; p = p -> next_.get()) {
            cout << endl << " -- " << p-> get_city() -> get_name() << " -- " << endl;
            p -> get_city() -> update_companies_from_database();
        }
    }
    else {
        cout << "No countries to run adjust cycle" << endl;
        return false;
    }
    return true;
    
}

bool City_list::write_time_data_to_company_database() {

    Element_city * p;

    if(list_) {
        for(p = list_.get(); p; p = p -> next_.get()) {
            cout << endl << " -- " << p-> get_city() -> get_name() << " -- " << endl;
            p -> get_city() -> write_time_data_to_company_database();
        }
    }
    else {
        cout << "No countries to run write company time data cycle" << endl;
        return false;
    }
    return true;

    
}



bool City_list::update_country_from_database() {

    Element_city * p;

    if(list_) {
        for(p = list_.get(); p; p = p -> next_.get()) {
            cout << endl << " -- " << p-> get_city() -> get_name() << " -- " << endl;
            p -> get_city() -> update_parameters_from_database();
        }
    }
    else {
        cout << "No countries to update from database" << endl;
        return false;
    }
    return true;

    
}

bool City_list::save_high_score() {

    Element_city * p;

    if(list_) {
        for(p = list_.get(); p; p = p -> next_.get()) {
            cout << endl << " -- " << p-> get_city() -> get_name() << " -- " << endl;
            p -> get_city() -> save_high_score();
        }
    }
    else {
        cout << "No countries to save high-score" << endl;
        return false;
    }
    return true;

    
}
bool City_list::save_consumers() {

    Element_city * p;

    if(list_) {
        for(p = list_.get(); p; p = p -> next_.get()) {
            cout << endl << " -- " << p-> get_city() -> get_name() << " -- " << endl;
            p -> get_city() -> save_consumers();
        }
    }
    else {
        cout << "No countries to save consumers" << endl;
        return false;
    }
    return true;

    
}

bool City_list::change_market(Market * newMarket) {

    Element_city * p;

    if(list_) {
        for(p = list_.get(); p; p = p -> next_.get()) {
            cout << endl << " -- " << p-> get_city() -> get_name() << " -- " << endl;
            p -> get_city() -> set_market(newMarket);
        }

    }
}
