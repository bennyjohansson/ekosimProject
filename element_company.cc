#include <iostream>
#include <iomanip>
#include <string>

//#include "consumer.h"
//#include "company.h"
#include "element_company.h"

using namespace std;


/*
 *Constructors
 */

Element_company::Element_company() :
  next_(0),
  company_(0)
{}

Element_company::Element_company(Element_company *n, Company *c) :
  next_(n), company_(c)
{}

/*
 *Functions to get the company or company name
 */

string Element_company::get_name() {
  return company_ -> get_name();
}

Company* Element_company::get_company() {
  return company_;
}

