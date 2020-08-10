#ifndef CITY_LIST_H
#define CITY_LIST_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "city.h"
#include "element_city.h"

using namespace std;

class City_list {
 public:

  City_list();
  City_list(string name);
  City_list(string name, Clock * clock);


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


  bool update_employees();
  bool run_production_cycle();
  bool run_sales_cycle();
  bool run_investment_cycle();
  bool run_banking_cycle();
  bool run_dividend_cycle();
  bool run_save_cycle();
  bool run_adjust_money_and_consumer_cycle();
  bool update_companies_from_database();

 private:
  string name_;
  Element_city * list_;
  int size_;

};

#endif




