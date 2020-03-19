#ifndef ELEMENT_CONSUMER_H
#define ELEMENT_CONSUMER_H
#include <iostream>
#include <iomanip>
#include <string>

#include "consumer.h"
//#include "city.h"

using namespace std;

class Element_consumer {
public:

	Element_consumer();
	Element_consumer(Element_consumer *n, Consumer *c);
	~Element_consumer();

	Element_consumer *next_;
	Consumer * consumer_;

	Consumer * get_consumer();

	double get_motivation();
	double get_skill();
	double get_capital();
	double get_spendwill();
	double get_income();
	double get_loans();
	bool get_employment_status();
	void set_employment_status(bool);

};
#endif
