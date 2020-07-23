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
      void initiate_city(string city_name);

 

   private:

    string name_;
    City_list * cities_;




};



#endif

