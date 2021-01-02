#ifndef CONSUMER_H
#define CONSUMER_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "market.h"
#include "clock.h"
#include "bank.h"
//#include "company.h"
//#include "consumer_list.h"
//#include "city.h"

using namespace std;

class Consumer {
   public:
      Consumer();

      Consumer(double, double, double, double);
      Consumer(double, double, double, double, double, double, string, Market *, Bank *, Clock *);
  
      /*
       *Functions to get info regarding the consumer
       */

      void info(); 
      void info_short();
      void info_head();
  

      /*
       * Functions to get things from a consumer
       */
      string get_country();
      double get_motivation();
      double get_skill();
      double get_capital();
      double get_spendwill();
      double get_borrowwill();
      double get_savewill();
      double get_income();
      double get_dividends();
      double get_transfers();
      double get_items();
      double get_loans();
      double get_debts();
      double get_desired_deposit();
      double get_desired_borrow();
      double get_borrow();
      double get_demand();
      bool get_employment_status();
      bool get_trustworthy();
      string get_name();
      string get_employer();
      /*
       *Functions to set consumer parameters
       */

      void set_motivation(double);
      void set_skill(double);
      void set_capital(double);
      void set_spedwill(double);
      void set_income(double);  
      void set_dividends(double);  
      void set_transfers(double);  
      void set_employment_status(bool employed);
      void set_items(double);
      void set_loans(double);
      void set_debts(double);
      void set_name(string);
      void set_employer(string);
      void set_trustworthy(bool);
      /*
       *Functions to change consumer parameters
       */

      void change_motivation(double);
      void change_skill(double);
      void change_capital(double);
      void change_spendwill(double);
      void change_income(double);
      void change_items(double);
      void change_loans(double);
      void change_debts(double);

      /*
       *Update values calls the functions below to update consumer parameters
       */

      void update_values(double, double);

      void update_skill();
      void update_spendwill(double);
      void update_borrowwill(double);
      void update_motivation();

      /*
       *Function where consumers buy and deposit money
       */
      
      double buy();
      void deposit_and_borrow_from_bank();
      void deposit_to_bank();
      void borrow_from_bank();
      void repay_to_bank();
      void get_repayment_from_bank();
      double get_interest();
      double pay_interest();
      void pay_and_get_interest();
      double accept_deposit(double);
      double get_expected_net_flow_to_bank();
      double get_time();
      void save_to_database();
      
   private:
      
      string name_;
      string country_;
      double motivation_;
      double skill_;
      double capital_;
      double spendwill_;
      double savewill_;
      double borrowwill_;
      double items_;
      double loans_;
      double debts_;
    	double income_;
      double dividends_;
      double transfers_;
    	bool employed_;
      bool trustworthy_;
      string employer_;
      
       
      Bank * bank_;
      Clock * clock_;
      Market * market_; 
      
      //Company * employer_;
      //Employee_list employee_info_;
      

      //City * city_;
      
      
};
#endif

      
