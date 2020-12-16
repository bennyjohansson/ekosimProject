#ifndef COMPANY_LIST_H
#define COMPANY_LIST_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "company.h"
#include "element_company.h"

using namespace std;

class Company_list {
 public:

  Company_list();
  Company_list(string name);
  Company_list(Company * company);


  /*
   * Info-functions
   */
  
  void info();
  void employee_info(string);
  void print_list();
  void print_employees(string company);


  /*
   * Get-functions
   */

  int get_size();
  double get_capital_sum();
  double get_item_sum();
  double get_capacity_sum();
  double get_investment_sum();
  double get_desired_loans_sum();
    double get_debts_sum();

    double get_expected_net_flow_to_bank_sum();
      double get_items_for_production_sum();
  double get_planned_production_sum();
  Company * get_company(string name); 
  Element_company * get_random_company();
  Company * get_next_best_salary_company(double);


  /*
   * Functions to add employees or companies
   */ 

  void add_company(Company * company);
  void add_employee(string name, Consumer * conumer);

  /*
   * Functions to update companies
   */

  void update_companies();
  bool update_employees(Consumer *, string);
  bool update_employees(Consumer *);
  bool update_employees2(Consumer *);
  bool update_employees3(Consumer *);

  void remove_usless_employees();
  void update_companies_from_database(string city_name);
  void write_time_data_to_database(string city_name);


  /*
   * Functions to operate on the companies
   */

  double produce(string);
  void sell_to_market();
  double pay_employees(double);
  double pay_dividends();
  void pay_interest();
  void repay_to_bank();
  double invest();

 private:
  string name_;
  Element_company * list_;
  int size_;

};

#endif




