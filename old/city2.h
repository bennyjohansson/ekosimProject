#ifndef COMPANY_H
#define COMPANY_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "consumer.h"
#include "consumer_list.h"
#include "market.h"
//#include "employee_list.h"
//#include "city.h"

using namespace std;

class Company {
 public:

  Company();
  Company(string name);
  Company(string, Market*);

  void info();
  void employee_info();
  string get_name();

  double get_capital();
  double get_prod_const_skill();
  double get_prod_const_motivation();
  double get_wage_const();
  double get_production();
  double get_production(Consumer *);
  double get_stock();
  double get_invest();

  void set_capital(double);
  void set_prod_const_skill(double);
  void set_prod_const_motivation(double);
  void set_wage_const(double);
  void set_stock(double);
 private:
  Company_list company_list_;
  Consumer_list consumers_;
