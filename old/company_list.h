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
  
  void info();
  void employee_info(string);
  int get_size();

  void add_company(Company * company);
  void add_employee(string name, Consumer * conumer);
  void print_list();
  void print_employees(string company);
  void sell_to_market();


  Company * get_company(string name); 
  Element_company * get_random_company();

  void update_company_employees();
  void produce();
  bool update_employees(Consumer *, string);
  bool update_employees(Consumer *);
  bool update_employees2(Consumer *);
  void remove_usless_employees();

  void pay_employees();
  double pay_dividends();

  void invest();

  double get_capital_sum();
  double get_item_sum();
  double get_capacity_sum();

 private:
  string name_;
  Element_company * list_;
  int size_;

};

#endif




