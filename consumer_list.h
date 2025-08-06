#ifndef CONSUMER_LIST_H
#define CONSUMER_LIST_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
//#include <tuple>

#include "element_consumer.h"
#include "consumer.h"

using namespace std;

class Consumer_list {
   public:
      Consumer_list();
      Consumer_list(string name_string);
  
      /*
       * Info-functions
       */

      void info();
      void print_list();


      /*
       * Get-functions
       */

      int get_size() const;
      double get_skill_sum() const;
      double get_motivation_sum() const;
      double get_capital_sum() const;
      double get_deposit_sum() const;
    double get_debts_sum() const;
      double get_spendwill_sum() const;
      double get_item_sum() const;
      //std::tuple<double, double, double, double, double> get_misc_sum();
      double get_desired_deposit_sum() const;
      double get_desired_borrow_sum() const;
      double get_expected_net_flow_to_bank_sum() const;
      double get_total_demand() const;
      int get_employed() const;
      int get_unemployed() const;
      int get_trustworthy() const;
      
      Element_consumer * get_first_unemployed();
      Element_consumer * get_first_consumer();
      
      bool is_consumer(Consumer *) const;
      Consumer * get_random_consumer();
      Consumer * get_optimal_consumer(double, double, double, int, double);
      Consumer * get_usless_employee(double, double, double, int, double);
      Consumer * get_consumer(string);


      /*
       * Set-functions
       */

      void set_name(string name_string);
  

      /*
       * Functions for adding and removing consumers
       */

      void add_first(Consumer * cons);
      void add_last(Consumer * cons);
      void add_group_last(Element_consumer * workers);

      void remove_consumer(Consumer *, double);

      /*
       * Functions to update and operate on the list
       */

      void update(double, double);  
      double consumers_buy();
      void deposit_and_borrow_from_bank();
      void deposit_money_to_bank();
      void borrow_money_from_bank();
      void repay_to_bank();
      void get_repayment_from_bank();
      void get_and_pay_interest();
      void bank_business();
      
      void pay_employees(double);
      double pay_employees_individual(double, double, double, double, string, int); 
      void pay_dividends(double);
		void pay_dividends_log(double, string);
		double pay_all_dividends_log(double, double, double); 
		void pay_transfers_log(double, string);
      void save_consumers();
	
   protected:

      string name_;
      std::unique_ptr<Element_consumer> list_;
      int size_;
  
};
#endif

