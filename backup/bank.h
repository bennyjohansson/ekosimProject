#ifndef BANK_H
#define BANK_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include "clock.h"
//#include "consumer_list.h"
//#include "company_list.h"
//#include "consumer.h"

using namespace std;

class Bank {
 public:

  Bank();
  Bank(string name, double interest, int payback_time);

  void info();

  double get_interest();
  double get_assets();
  double get_debts();
  double get_loans();
  double get_payback_time();
  double get_loan_cost(double); 

  void set_interest(double);
  void set_assets(double);
  void set_debts(double);
  void set_loans(double);
  void set_payback_time(double);

  void change_interest(double);
  void change_assets(double);
  void change_debts(double);
  void change_loans(double);
  void change_payback_time(double);

  void update_assets();

  list<double> interest_list_;
  list<double> debts_list_;
  list<double> assets_list_;

 private:

  string name_;
  double interest_rate_;
  double debts_;
  double loans_;
  double assets_;  
  double payback_time_;
};

#endif


