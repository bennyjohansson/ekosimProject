#ifndef CITY_H
#define CITY_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <memory>
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
      City(string name, Clock * clock);

      /*
       * Info-funktioner
       */

      void info();
      void print_consumer_list();
      void print_employees(string company);
      void print_labour_market();
      void consumer_info();
      void capital_owners_info();
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

      int get_time() const;
      Clock * get_clock() const;
      Market * get_market();
      Bank * get_bank();
      double get_consumer_capital_sum();
      double get_company_capacity_sum();
      double get_expected_consumer_net_flow_to_bank_sum();
      int get_no_companies() const; 
      double get_capital_sum(); 
      double get_loans_to_bank();
      Company * get_company(const string& name);
      Consumer * get_random_consumer();
      Company * get_random_company();
      Consumer * get_optimal_consumer(double mot_we, double skill_we, int production_function, double production_parameter);
      double get_shareToSteal() const;
      double get_laundry_factor() const;
      double get_capital() const;
      double get_vat() const;
      double get_income_tax() const;
      double get_capital_gains_tax() const;
      double get_budget_balance() const;
      double get_inflation_target() const;
      int get_no_years_laundry() const;
      int get_time_to_steal() const;
      string get_name() const;
      int get_no_consumers() const;
      
      /*
       * Change-functions
       */
       
       void change_capital(double);

      /*
       * Set-functions
       */

      void set_consumers(Consumer_list * consumer_list);
      void set_companies(Company_list * company_list);
      void set_shareToSteal(double);
      void set_laundry_factor(double);
      void set_no_years_laundry(int);
      void set_time_to_steal(int);
      void set_vat(double);
      void set_income_tax(double);
      void set_capital_gains_tax(double);
      void set_budget_balance(double);
      void set_inflation_target(double);
      void set_market(Market *);


      /*
       * Functions to add companies and employees to Bennyland
       */ 

      void add_consumer(Consumer * consumer);
      void add_random_consumers(int);
      void add_random_consumers(int, double);
      void add_capital_owners(double);
      void add_company(Company * company);
      void add_company(string name);
      void load_company(string); 
      double invest_in_new_company(string, double);
      void load_launder_parameters();

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
      void randomize_laundry_parameters();
      
 
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
      void pay_transfers();
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
      void add_companies_from_database();
      void update_companies_from_database();
      void write_time_data_to_company_database();
      void save_high_score();
      void save_consumers();
      double calculate_CAGR(int);
      double calculate_Palma_ratio();
      
      //Database functions
      void update_interest_parameters();
      void update_parameters_from_database();

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

      std::unique_ptr<Consumer_list> consumers_;
      std::unique_ptr<Consumer_list> labour_market_;
      std::unique_ptr<Consumer_list> capital_owners_;
      std::unique_ptr<Company_list> company_list_;
      std::unique_ptr<Market> market_;
      std::unique_ptr<Bank> bank_;
      Clock * clock_;  // Keep as raw pointer - may be shared resource
      int flash_counter_;
      double loans_to_bank_;
      double vat_;
      double income_tax_; 
      double capital_gains_tax_;
      double budget_balance_;
      double inflation_target_;
      double capital_;
      
    
    
    //Launder parameters  
    double shareToSteal_;
   	double laundry_factor_;
    double no_years_laundry_;
   	double time_to_steal_; 
};



#endif

