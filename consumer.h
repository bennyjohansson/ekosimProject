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
      Consumer(double, double, double, double, double, double, Market *, Bank *, Clock *);
  
      /*
       *Functions to get info regarding the consumer
       */

      void info(); 
      void info_short();
      void info_head();
  

      /*
       * Functions to get things from a consumer
       */

      double get_motivation();
      double get_skill();
      double get_capital();
      double get_spendwill();
      double get_income();
      double get_items();
      double get_loans();
      double get_debts();
      double get_desired_loans();
      double get_desired_borrow();
      double get_borrow();
      bool get_employment_status();
      bool get_trustworthy();
      /*
       *Functions to set consumer parameters
       */

      void set_motivation(double);
      void set_skill(double);
      void set_capital(double);
      void set_spedwill(double);
      void set_income(double);  
      void set_employment_status(bool employed);
      void set_items(double);
      void set_loans(double);
      void set_debts(double);
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

      void update_values();

      void update_skill();
      void update_spendwill();
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
      void get_interest();
      void pay_interest();
      void pay_and_get_interest();
      double get_expected_net_flow_to_bank();
   private:
      
      double motivation_;
      double skill_;
      double capital_;
      double spendwill_;
      double savewill_;
      double borrowwill_;
      double items_;
      double loans_;
      double debts_;
      bool trustworthy_;
      
      Market * market_;  
      Bank * bank_;
      Clock * clock_;
      
      //Company * employer_;
      //Employee_list employee_info_;
      bool employed_;
      double income_;
      //City * city_;
      
      
};
#endif

      
