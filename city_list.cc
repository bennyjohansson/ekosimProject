#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <exception>
#include <stdexcept>

#include "city_list.h"
//#include "error_no_return.h"

using namespace std;

City_list::City_list(string name) :
list_(new Element_city(0, new City("Bennyland"))),
size_(1), 
name_(name)
{}

City_list::City_list(string name, Clock * clock) :
list_(new Element_city(0, new City("Bennyland", clock))),
size_(1), 
name_(name)
{}

/*
 * Functions to add cities
 */ 

City * City_list::get_city(string name) {
    Element_city * p;
    
    if(list_) {
        for(p = list_; p; p = p -> next_) {
            if (p ->get_name() == name) {
                return p -> get_city() ;
            }
        }
        //throw no_return_error("Cant find the city");
        throw std::runtime_error(std::string("Cant find the city"));
    }
    else {
        // throw no_return_error("no list"); 
        throw std::runtime_error(std::string("No ciry list"));
        
    } 
}

/*
 * Functions to add cities
 */ 

void City_list::add_city(City * city) {
    //Element_city * p;
    size_++;
    
    if(list_) {
        list_ = new Element_city(list_, city);
    }
    else {
        list_ = new Element_city(0, city);
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
        for (Element_city *p = list_; p; p = p -> next_) {
            p->city_->info();
        }
    }
    
    cout << endl; 
}

void City_list::print_GDP() {
    
    if(list_) {
        for (Element_city *p = list_; p; p = p -> next_) {
            p->city_-> print_GDP();
        }
    }
    
    cout << endl; 
}

bool City_list::update_employees() {

    Element_city * p;
    if(list_) {
        for(p = list_; p; p = p -> next_) {
            
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

bool City_list::run_production_cycle() {

    Element_city * p;
    if(list_) {
        for(p = list_; p; p = p -> next_) {
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

    Element_city * p;
    if(list_) {
        for(p = list_; p; p = p -> next_) {
            cout << endl << " -- " << p-> get_city() -> get_name() << " -- " << endl;
            p -> get_city() -> update_companies();
            p -> get_city() -> save_data();
            p -> get_city() -> sell_to_market();
            p -> get_city() -> consumers_buy();
            p -> get_city() -> pay_company_employees();
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
        for(p = list_; p; p = p -> next_) {
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
        for(p = list_; p; p = p -> next_) {
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
        for(p = list_; p; p = p -> next_) {
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
        for(p = list_; p; p = p -> next_) {
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
        for(p = list_; p; p = p -> next_) {
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
        for(p = list_; p; p = p -> next_) {
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
        for(p = list_; p; p = p -> next_) {
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
        for(p = list_; p; p = p -> next_) {
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
        for(p = list_; p; p = p -> next_) {
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
        for(p = list_; p; p = p -> next_) {
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
