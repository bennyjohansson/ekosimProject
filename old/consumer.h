#ifndef CONSUMER_H
#define CONSUMER_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "market.h"
//#include "company.h"
//#include "consumer_list.h"
//#include "city.h"

using namespace std;

class Consumer {
 public:
  Consumer();

  Consumer(double, double, double, double);
  Consumer(double, double, double, double, Market *);
  
  void info(); 
  void info_short();
  void info_head();
  
  double get_motivation();
  double get_skill();
  double get_capital();
  double get_spendwill();
  double get_income();
  double get_items();
  bool get_employment_status();

  void set_motivation(double);
  void set_skill(double);
  void set_capital(double);
  void set_spedwill(double);
  void set_income(double);  
  void set_employment_status(bool employed);
  void set_items(double);
//void set_city(City * city);

  void change_motivation(double);
  void change_skill(double);
  void change_capital(double);
  void change_spendwill(double);
  void change_income(double);
  void change_items(double);

  void update_values(double);

  void update_capital(); 
  void update_skill();
  void update_spendwill(double);
  void update_motivation();

  void buy();

 private:

  double motivation_;
  double skill_;
  double capital_;
  double spendwill_;
  double items_;

  Market * market_;  
  //Company * employer_;
  //Employee_list employee_info_;
  bool employed_;
  int weeks_employed_;
  int weeks_unemployed_;
  double income_;
  //City * city_;


};
#endif

