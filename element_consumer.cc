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
  next_(0),
  consumer_(0)
{}

Element_consumer::Element_consumer(Element_consumer *n, Consumer *c) :
  next_(n), consumer_(c)
{}

Element_consumer::~Element_consumer() {} 

/*
 *Functions to get either the consumer or one of the parameters of the consumer object
 */

Consumer * Element_consumer::get_consumer() {
  return consumer_;
}

double  Element_consumer::get_motivation() {
  return consumer_ -> get_motivation();
}

double  Element_consumer::get_skill() {
  return  consumer_ -> get_skill();
}

double  Element_consumer::get_capital() {
  return consumer_ -> get_capital();
}

double  Element_consumer::get_loans() {
  return consumer_ -> get_loans();
}

double  Element_consumer::get_spendwill() {
  return consumer_ -> get_spendwill();
}

double  Element_consumer::get_income() {
  return consumer_ -> get_income();
}

/*
 *Employment status, true = employed, false = unemployed
 */

bool Element_consumer::get_employment_status() {
  return consumer_ -> get_employment_status();
}

void Element_consumer::set_employment_status(bool employed) {
	consumer_ -> set_employment_status(employed);
}














