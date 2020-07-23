#ifndef CITY_LIST_H
#define CITY_LIST_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "city.h"
#include "element_city.h"

using namespace std;

class City_list {
 public:

  City_list();
  City_list(string name);
  City_list(City * city);


  /*
   * Info-functions
   */
  
    void info();
    void print_list();


  /*
   * Get-functions
   */

  int get_size();

  City * get_city(string name); 


  /*
   * Functions to add cities
   */ 

  void add_city(City * city);



 private:
  string name_;
  Element_city * list_;
  int size_;

};

#endif




