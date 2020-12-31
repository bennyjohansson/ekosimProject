#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include "bank.h"
#include "clock.h"
#include "city_list.h"
//#include "market.h"
//#include "consumer.h"

using namespace std;

class World {
   public:

      World();
      World(string name);

      /*
       * Info-funktioner
       */
      void print_cities();
      void printWorldDB();
      void initiate_city(string city_name);
      void add_city(City * city);
      void add_city(string city_name, string email);
      void print_GDP();

      /* 
       * Get functions
       */

      int get_time();
      Clock * get_clock();
      City * get_city(string);
      
      void tick();
      
      bool run_production_cycle();
      bool run_sales_cycle();
      bool run_investment_cycle();
      bool run_banking_cycle();
      bool run_dividend_cycle();
      bool run_save_cycle();
      bool run_adjust_money_and_consumer_cycle();
      bool update_companies_from_database();
      bool write_time_data_to_company_database();
      bool update_country_from_database();
      bool save_high_score();
      bool save_consumers();

 

   private:

    string name_;
    Clock * clock_;
    City_list * cities_;




};



#endif

