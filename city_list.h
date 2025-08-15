#ifndef CITY_LIST_H
#define CITY_LIST_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>

#include "city.h"
#include "element_city.h"

using namespace std;

class City_list {
 public:

  City_list();
  City_list(string name);
  City_list(string name, Clock * clock);
  City_list(string name, Clock * clock, Market * global_market);


  /*
   * Info-functions
   */
  
    void info();
    void print_list();
    void print_GDP();


  /*
   * Get-functions
   */

  int get_size();

  City * get_city(string name); 


  /*
   * Functions to add cities
   */ 

  void add_city(City * city);

  double get_capital_sum() const;
  double get_added_capital_sum() const;

  bool update_employees();
  bool run_supply_demand_cycle();
	bool update_market_price();
  bool reset_market_calculations();
  bool run_production_cycle();
  bool run_employee_pricing_and_production_cycle();
  bool run_sales_cycle();
  bool run_investment_cycle();
  bool run_banking_cycle();
  bool run_dividend_cycle();
  bool run_save_cycle();
  bool run_adjust_money_and_consumer_cycle();
  bool update_companies_from_database();
  bool write_time_data_to_company_database();
  bool update_country_from_database();
  bool save_high_score();
  bool save_consumers();
  bool change_market(Market * newMarket);

 private:
  string name_;
  std::unique_ptr<Element_city> list_;
  int size_;

};

#endif




