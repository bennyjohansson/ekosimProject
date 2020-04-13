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
      double get_capital();
      double get_deposits();
      double get_loans();
      double get_liquidity();
      double get_payback_time();
      double get_loan_cost(double);
      double get_sum_to_borrow();
      double get_max_customer_borrow();
      double get_safety();
      bool get_trustworthy();
      
      void set_interest(double);
      void set_capital(double);
      void set_deposits(double);
      void set_loans(double);
      void set_liquidity(double);
      void set_payback_time(double);
      void set_trustworthy(bool);
      
      void change_interest(double);
      void change_capital(double);
      void change_deposits(double);
      void change_loans(double);
      void change_liquidity(double);
      void change_payback_time(double);
      
      void customer_deposit_money(double);
      double customer_withdraw_money(double);
      double customer_borrow_money(double);
      void customer_repay_loans(double);
      void customer_pay_interest(double);
      double customer_get_interest(double);
      

      double pay_dividends();

      list<double> interest_list_;
      list<double> deposits_list_;
      list<double> assets_list_;

   private:

      string name_;
      double interest_rate_;
      double deposits_;
      double loans_;
      double capital_; 
      double liquidity_; 
      double payback_time_;
      double safety_;
      double trustworthy_;
      double div_ratio_;
};

#endif


