#include <iostream>
#include <iomanip>
#include <string>

//#include "consumer.h"
//#include "company.h"
#include "element_consumer.h"
//#include "city.h"

using namespace std;


/*
 *Constructors
 */

Element_consumer::Element_consumer() :
  next_(nullptr),
  consumer_(nullptr)
{}

Element_consumer::Element_consumer(std::unique_ptr<Element_consumer> n, Consumer *c) :
  next_(std::move(n)), consumer_(c)
{}

Element_consumer::~Element_consumer() {} 

/*
 *Functions to get either the consumer or one of the parameters of the consumer object
 */

Consumer * Element_consumer::get_consumer() const {
  return consumer_;
}

double  Element_consumer::get_motivation() const {
  return consumer_ -> get_motivation();
}

double  Element_consumer::get_skill() const {
  return consumer_ -> get_skill();
}

double  Element_consumer::get_capital() const {
  return consumer_ -> get_capital();
}

double  Element_consumer::get_loans() const {
  return consumer_ -> get_loans();
}

double  Element_consumer::get_spendwill() const {
  return consumer_ -> get_spendwill();
}

double  Element_consumer::get_income() const {
  return consumer_ -> get_income();
}

/*
 *Employment status, true = employed, false = unemployed
 */

bool Element_consumer::get_employment_status() const {
  return consumer_ -> get_employment_status();
}

void Element_consumer::set_employment_status(bool employed) {
	consumer_ -> set_employment_status(employed);
}














