#ifndef COMPANY_H
#define COMPANY_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>

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
  double get_capacity();
  double get_total_wages();

  void set_capital(double);
  void set_prod_const_skill(double);
  void set_prod_const_motivation(double);
  void set_wage_const(double);
  void set_stock(double);
  void set_invest(double);
  void set_capacity(double); 
 //void set_market(Market * market);

  void change_capital(double);
  void change_prod_const_skill(double);
  void change_prod_const_motivation(double);
  void change_wage_const(double);
  void change_stock(double);  
  void change_invest(double);
  void change_capacity(double);

  void add_employee(Consumer * consumer);
  void remove_employee(Consumer *);
  void update_employees(double skill_limit, double motivation_limit);
  void print_employees();

  void sell_to_market();

  double contribution_adding(Consumer *);
  double contribution_removing(Consumer *);
  bool update_employees(Consumer *);
  void remove_usless_employees();
  void produce();
  void pay_employees(); 
  void invest();

  list<double> wages_;

 private:
  string name_;  
  double capital_;
  double stock_;   //temp solution. later objects of class p1 osv
  double capacity_;
  
  double invest_;
  
  Consumer_list * employees_;
  Market *market_;

  double prod_const_skill_;
  double prod_const_motivation_;
  double wage_const_;  
};

#endif
