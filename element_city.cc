#include <iostream>
#include <iomanip>
#include <string>

//#include "consumer.h"
//#include "company.h"
#include "element_city.h"

using namespace std;


/*
 *Constructors
 */

Element_city::Element_city() :
  next_(0),
  city_(0)
{}

Element_city::Element_city(Element_city *n, City *c) :
  next_(n), city_(c)
{}

/*
 *Functions to get the company or company name
 */

string Element_city::get_name() {
  return city_ -> get_name();
}

City* Element_city::get_city() {
  return city_;
}
