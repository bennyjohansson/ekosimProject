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
  next_(nullptr),
  city_(nullptr)
{}

Element_city::Element_city(std::unique_ptr<Element_city> n, City *c) :
  next_(std::move(n)), city_(c)
{}

/*
 *Functions to get the company or company name
 */

string Element_city::get_name() const {
  return city_ -> get_name();
}

City* Element_city::get_city() {
  return city_;
}
