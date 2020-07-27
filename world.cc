#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <cstring>

#include "SQLfunctions.h"
// #include "functions.h"
#include "world.h"

using namespace std;

World::World(string name) : 
	name_(name),
	clock_(new Clock()),
    cities_(new City_list("CITIES", clock_))
{}

void World::add_city(City * city) {

	cities_ -> add_city(city);


}

void World::add_city(string city_name, string email) {

	City * myCity = new City(city_name, clock_);
	//string email = "myEmail@gmail.com";
	//Initiating database
	initiateCityDB(city_name);
	insertWorldData(name_, city_name, email, 1);
    
    /*
   	* Creating random consumers. See file functions.cc for settings about the consumers.
   	*/
	myCity -> add_random_consumers(3000);
  	
  	/*
   	* Adding capital owners
   	*/
  	myCity -> add_capital_owners(0.1);

	myCity -> add_companies_from_database();

	cities_ -> add_city(myCity);


}

void World::print_cities() {

    cities_ -> print_list();


}

void World::print_GDP() {
	cities_ -> print_GDP();

}

int World::get_time() {

    return clock_ -> get_time();

}

City * World::get_city(string name) {

	return cities_ -> get_city(name);

}

void World::tick()
{
    clock_ -> tick();
}




void World::initiate_city(string city_name) {

    City * myCity;
	string email = "johansson.benny@gmail.com";
	
	//Adding default city to world db
	insertWorldData(name_, city_name, email, 1);

    
    myCity = cities_ -> get_city(city_name);

    /*
   	* Creating random consumers. See file functions.cc for settings about the consumers.
   	*/
	myCity -> add_random_consumers(3000);
  	
  	/*
   	* Adding capital owners
   	*/
  	myCity -> add_capital_owners(0.1);

	myCity -> add_companies_from_database();

}



bool World::run_production_cycle() {

		//Running the following lines
		// bennyland.update_employees();
    	// bennyland.negotiate_market_price();
		// bennyland.produce();

    return cities_ -> run_production_cycle();
    
}

bool World::run_sales_cycle() {

		//Running the following lines
		// bennyland.update_companies();
		// bennyland.save_data();
		// bennyland.sell_to_market();
		// bennyland.consumers_buy();
		// bennyland.pay_company_employees();

    return cities_ -> run_sales_cycle();
    
}

bool World::run_investment_cycle() {

		//Running the following lines
		// bennyland.update_interest_parameters();
    	// bennyland.update_interest_rate();
    	// bennyland.invest(true);

    return cities_ -> run_investment_cycle();
    
}

bool World::run_banking_cycle() {

		//Running the following lines
		// bennyland.consumers_bank_business();
		// bennyland.company_pay_interest();
		// bennyland.company_repay_to_bank();

    return cities_ -> run_banking_cycle();
    
}

bool World::run_dividend_cycle() {

		//Running the following lines
    	//bennyland.company_pay_dividends();
    	//bennyland.pay_transfers();

    return cities_ -> run_dividend_cycle();
    
}

bool World::run_save_cycle() {

		//Running the following lines
    	// bennyland.save_money_data();

    return cities_ -> run_save_cycle();
    
}

bool World::run_adjust_money_and_consumer_cycle() {

		//Running the following lines

    	// bennyland.adjust_money();
    	// bennyland.update_consumer_list();

    return cities_ -> run_adjust_money_and_consumer_cycle();
    
}




void World::printWorldDB()
{

    using Record = std::vector<std::string>;
    using Records = std::vector<Record>;

    string full_path = get_city_sql_string(name_); 
    const char* dir =  full_path.c_str(); 

    string world_name = "";
	string email = "";
	int created = 0;

    
    cout << "I World print world DB, dir: " << dir << endl;
    string stmt = "SELECT * FROM WORLD_TABLE";

    Records records = select_stmt(stmt, dir);

    for (int i = 0; i < records.size(); i++) {

        world_name = records[i][1];
        email = records[i][2];
		created = std::stoi(records[i][3]);

        
        cout  << "City: " << world_name << " with email: " << email << " created status: " << created << endl;
        
    }

}