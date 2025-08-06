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
  next_(nullptr),
  company_(nullptr)
{}

Element_company::Element_company(std::unique_ptr<Element_company> n, Company *c) :
  next_(std::move(n)), company_(c)
{}

/*
 *Functions to get the company or company name
 */

string Element_company::get_name() const {
  return company_ -> get_name();
}

Company* Element_company::get_company() const {
  return company_;
}

