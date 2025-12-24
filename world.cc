#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <cstring>

#include "SQLfunctions.h"
#include "world.h"

using namespace std;

World::World(string name) : name_(name),
							clock_(new Clock()),
							global_market_(new Market("Global Market")),
							cities_(std::make_unique<City_list>("CITIES", clock_, global_market_))
{
}

World::~World()
{
	delete global_market_;
}

void World::add_city(City *city)
{

	cities_->add_city(city);
}

void World::add_city(string city_name, string email)
{

	City *myCity = new City(city_name, clock_, global_market_);
	int size = 0;
	size = myCity->get_no_consumers();
	double share_capital_owners = 0.3;
	int number_of_shareholders = 250;
	// string email = "myEmail@gmail.com";
	// Initiating database
	initiateCityDB(city_name);
	insertWorldData(name_, city_name, size, email, 1);

	/*
	 * Creating random consumers. See file functions.cc for settings about the consumers.
	 */
	myCity->add_random_consumers(3000);

	/*
	 * Adding capital owners
	 */
	myCity->add_capital_owners(share_capital_owners);

	myCity->add_companies_from_database();

	myCity->add_random_shareholders(number_of_shareholders);

	cities_->add_city(myCity);
}

void World::print_cities()
{

	cities_->print_list();
}

void World::print_GDP()
{
	cities_->print_GDP();
}

int World::get_time() const
{

	return clock_->get_time();
}

Clock *World::get_clock() const
{

	return clock_;
}

City *World::get_city(const string &name) const
{

	return cities_->get_city(name);
}

Market *World::get_global_market() const
{

	return global_market_;
}

void World::tick()
{
	clock_->tick();
}

void World::initiate_city(string city_name)
{

	City *myCity;
	string email = "johansson.benny@gmail.com";
	int no_consumers = 3000;
	double share_capital_owners = 0.3;
	int number_of_shareholders = 50;

	myCity = cities_->get_city(city_name);

	/*
	 * Creating random consumers. See file functions.cc for settings about the consumers.
	 */
	myCity->add_random_consumers(no_consumers);

	/*
	 * Adding capital owners and shareholders
	 */
	myCity->add_capital_owners(share_capital_owners);

	myCity->add_companies_from_database();
	myCity->add_random_shareholders(number_of_shareholders);

	// Adding default city to world db
	insertWorldData(name_, city_name, no_consumers, email, 1);
}

// Running updating of emplyees cycle

bool World::run_employee_cycle()
{

	bool success = false;

	success = cities_->update_employees();

	return success;
}

// running the pricing cycle

bool World::run_pricing_cycle()
{

	if (cities_ == nullptr)
	{
		cout << "ERROR: Cities list is null in run_pricing_cycle!" << endl;
		return false;
	}

	cout << "=== Validating city list before pricing cycle ===" << endl;
	cities_->validate_list_integrity();

	cities_->run_supply_demand_cycle();

	cities_->update_market_price();

	cities_->reset_market_calculations();

	return true;
}

// Production cycle
bool World::run_production_cycle()
{

	bool success = false;

	success = cities_->run_production_cycle();

	return success;
}

bool World::run_employee_pricing_and_production_cycle()
{

	// Running the following lines
	//  bennyland.update_employees();
	//  bennyland.negotiate_market_price();
	//  bennyland.produce();

	return cities_->run_employee_pricing_and_production_cycle();
}

bool World::run_sales_cycle()
{

	// Running the following lines
	//  bennyland.update_companies();
	//  bennyland.save_data();
	//  bennyland.sell_to_market();
	//  bennyland.consumers_buy();
	//  bennyland.pay_company_employees();

	return cities_->run_sales_cycle();
}

bool World::run_investment_cycle()
{

	// Running the following lines
	//  bennyland.update_interest_parameters();
	//  bennyland.update_interest_rate();
	//  bennyland.invest(true);

	return cities_->run_investment_cycle();
}

bool World::run_banking_cycle()
{

	// Running the following lines
	//  bennyland.consumers_bank_business();
	//  bennyland.company_pay_interest();
	//  bennyland.company_repay_to_bank();

	return cities_->run_banking_cycle();
}

bool World::run_dividend_cycle()
{

	// Running the following lines
	// bennyland.company_pay_dividends();
	// bennyland.pay_transfers();
	double city_dividends = 0;
	double global_market_dividends = 0;
	double share_of_global_market_dividends = 0;
	int number_of_market_participants = 0;

	number_of_market_participants = global_market_->get_number_of_participants();

	// World pays each city its share of global market profit

	if (number_of_market_participants != 0)
	{
		global_market_dividends = get_global_market()->pay_dividends();
		share_of_global_market_dividends = global_market_dividends / number_of_market_participants;
	}
	else
	{
		share_of_global_market_dividends = 0;
	}

	cout << "Global market dividends of: " << global_market_dividends << " shared between " << number_of_market_participants << endl;

	// Cities pay dividends for local markets and gets their share of the global_market_dividends
	city_dividends = cities_->run_dividend_cycle(share_of_global_market_dividends);

	return true;
}

bool World::run_save_cycle()
{

	// Running the following lines
	//  bennyland.save_money_data();

	return cities_->run_save_cycle();
}

bool World::run_adjust_money_and_consumer_cycle()
{

	// Running the following lines

	// bennyland.adjust_money();
	// bennyland.update_consumer_list();

	return cities_->run_adjust_money_and_consumer_cycle();
}

bool World::update_companies_from_database()
{

	// Running the following lines

	// bennyland.adjust_money();
	// bennyland.update_consumer_list();

	return cities_->update_companies_from_database();
}

bool World::write_time_data_to_company_database()
{

	return cities_->write_time_data_to_company_database();
}

bool World::update_country_from_database()
{

	return cities_->update_country_from_database();
}

bool World::save_high_score()
{

	return cities_->save_high_score();
}

bool World::save_consumers()
{

	return cities_->save_consumers();
}

void World::printWorldDB()
{

	using Record = std::vector<std::string>;
	using Records = std::vector<Record>;

	// Use PostgreSQL for world_table (centralized)
	Records records = getWorldTablePG(name_);

	if (records.empty())
	{
		cerr << "Warning: No world data found in PostgreSQL, falling back to SQLite" << endl;
		// Fallback to SQLite if PostgreSQL fails
		string full_path = get_city_sql_string(name_);
		const char *dir = full_path.c_str();
		cout << "I World print world DB (SQLite), dir: " << dir << endl;
		string stmt = "SELECT * FROM WORLD_TABLE";
		records = select_stmt(stmt, dir);
	}

	string world_name = "";
	string email = "";
	int no_consumers = 0;
	int created = 0;

	cout << "I World print world DB (PostgreSQL), found " << records.size() << " records" << endl;

	for (int i = 0; i < records.size(); i++)
	{

		world_name = records[i][1];
		no_consumers = std::stoi(records[i][2]);
		email = records[i][3];
		created = std::stoi(records[i][4]);

		cout << "City: " << world_name << " with " << no_consumers << " consumers " << "and email: " << email << " created status: " << created << endl;
	}
}

bool World::check_money_consistency(double sum_before)
{

	double total_added_money = 0;
	double total_money = 0;
	double global_market_capital = 0;

	bool consistent = true;
	global_market_capital = global_market_->get_capital();

	total_money = cities_->get_capital_sum() + global_market_capital;
	total_added_money = cities_->get_added_capital_sum();

	// Checking that sum before + total_added_money is equal to total_money
	if (std::abs(sum_before + total_added_money - total_money) > 1)
	{
		cout << "Money inconsistency detected!" << endl;
		cout << "Sum before: " << sum_before << ", Total added money: " << total_added_money << ", Total money: " << total_money << endl;
		cout << "Difference: " << std::abs(sum_before + total_added_money - total_money) << endl;
		cout << "MArket capital / 2: " << get_city("Bennyland")->get_market()->get_capital() << endl;
		// Set consistent to false to indicate inconsistency
		consistent = false;
	}
	else
	{
		cout << "Money consistency check passed." << endl;
	}
	return consistent;
}

bool World::reset_number_of_market_participants()
{
	global_market_->reset_numnber_of_participants();
	cities_->reset_number_of_market_participants();

	return true;
}

void World::validate_city_list_integrity()
{
	cout << "=== WORLD VALIDATION ===" << endl;
	if (cities_ == nullptr)
	{
		cout << "ERROR: World cities_ pointer is null!" << endl;
		return;
	}
	if (global_market_ == nullptr)
	{
		cout << "WARNING: Global market pointer is null!" << endl;
	}

	cities_->validate_list_integrity();
	cout << "========================" << endl;
}

// End of World class implementation
// This file contains the implementation of the World class, which manages a collection of cities and their interactions in a simulated environment.