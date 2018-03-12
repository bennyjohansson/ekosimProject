#ifndef CITY_H
#define CITY_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include "consumer_list.h"
#include "company_list.h"
#include "bank.h"
#include "clock.h"
//#include "market.h"
//#include "consumer.h"

using namespace std;

class City {
   public:

      City();
      City(string name);

      /*
       * Info-funktioner
       */

      void info();
      void print_consumer_list();
      void print_employees(string company);
      void print_labour_market();
      void consumer_info();
      void labour_info();
      void print_company_info(string name);  //EJ GJORD
      void market_info();
      void bank_info();
      void employee_info();
      void employee_info(string);
      void print_company_list();
      void print_GDP();

      /*
       * Get-funktioner
       */

      int get_time();
      Clock * get_clock();
      Market * get_market();
      Bank * get_bank();
      double get_consumer_capital_sum();
      double get_company_capacity_sum();
      int get_no_companies(); 
      double get_capital_sum(); 
      double get_loans_to_bank();
      Company * get_company(string name);
      Consumer * get_random_consumer();
      Company * get_random_company();
      Consumer * get_optimal_consumer(double mot_we, double skill_we);

      /*
       * Set-functions
       */

      void set_consumers(Consumer_list * consumer_list);
      void set_companies(Company_list * company_list);


      /*
       * Functions to add companies and employees to Bennyland
       */ 

      void add_consumer(Consumer * consumer);
      void add_company(Company * company);
      void add_company(string name);
      void load_company(string); 

      /*
       * Functions to update Bennyland. Note that update_market() is old and not in use.
       * The update_company_employees() is also not in use
       */

      void negotiate_market_price();
      void update_consumer_list();
      void update_interest_rate();
      void update_interest_rate2();
      void update_companies();
      void update_employees();
      string steal_money();
      string steal_money(string);
      double launder_money(string, string);
      
 
      void tick(); 
      void save_data();
      void save_money_data();
      void save_flash(int);
      /*
       * Functions for producing, selling and buying. 
       */

      void produce();
      void sell_to_market();
      void consumers_buy();
      void invest(bool);
      void adjust_money();

      void pay_company_employees();
      void company_pay_dividends();
      void company_pay_dividends(string, string, double);
      void company_pay_interest();
      void company_repay_to_bank();
      void consumer_bank_business();
      void consumer_get_and_pay_interest();
      void consumers_deposit_and_borrow_from_bank();
      void consumers_deposit_to_bank();
      void consumers_borrow_from_bank();
      void consumers_bank_business();

      list<double> GDP_;
      list<double> growth_;
      list<double> investments_;
      list<double> company_consumption_;
      list<double> demand_;
      list<double> price_out_;
      list<double> employed_;
      list<double> time_;

      list<double> company_capital_;
      list<double> consumer_capital_;
      list<double> bank_capital_;
      list<double> market_capital_;
      list<double> total_capital_;
      list<double> capital_sum_;

      list<double> interest_rate_;
 

   private:

      string name_;

      Consumer_list * consumers_;
      Consumer_list * labour_market_;
      Company_list * company_list_;
      Market * market_;
      Bank * bank_;
      Clock * clock_;
      int flash_counter_;
      double loans_to_bank_;
};



#endif

