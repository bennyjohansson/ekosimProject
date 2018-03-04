#ifndef CITY_H
#define CITY_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include "consumer_list.h"
#include "company_list.h"
//#include "market.h"
//#include "consumer.h"

using namespace std;

class City {
 public:

  City();
  City(string name);

  void info();

  Market * get_market();
  void update_market();
  void market_info();
  void employee_info();
  void employee_info(string);
  void follow_capital(Consumer *);
  void follow_capital();
  void pay_company_employees();
  void company_pay_dividends();
  double get_capital_sum();
  void sell_to_market();
  void print_company_list();
  void set_consumers(Consumer_list * consumer_list);
  void set_companies(Company_list * company_list);
  void set_labour_market(Consumer_list * labour_market);
  void negotiate_market_price();	

  double get_consumer_capital_sum();
  double get_company_capacity_sum();
  int get_no_companies();  

  void add_consumer(double motivation, double skill, 
		    double capital, double spendwill);

  void add_consumer(Consumer * consumer);

  void add_company(string name);
  void add_employee(string name, Consumer * consumer);
  void print_company_info(string name);  //EJ GJORD
  void update_consumer_list();
  void print_consumer_list();
  void print_employees(string company);
  void print_labour_market();
  void consumer_info();
  void labour_info();
  Company * get_company(string name);
  Consumer * get_random_consumer();

  Element_consumer * get_motivated_consumers();

  void remove_consumer_from_labour_market(Consumer *);
  void add_motivated_consumers(Element_consumer * workers);
  void update_company_employees();
  void update_employees(string);
  void produce();

  Company * get_random_company();

  void consumers_buy();
  void invest();
  void print_GDP();
  Consumer * get_optimal_consumer(double mot_we, double skill_we);

  list<double> GDP_;
  list<double> growth_;
  list<double> demand_;
  list<double> price_out_;
  list<double> unemployment_;
 
 private:

  string name_;


  Consumer_list * consumers_;
  Consumer_list * labour_market_;
  Company_list * company_list_;
  Market * market_;

  //int week_;
  //  list<double> GDP_;


};



#endif

