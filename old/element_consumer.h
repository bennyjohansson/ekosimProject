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
	Element_consumer *next_;
	Consumer * consumer_;

	Element_consumer();

	Element_consumer(Element_consumer *n, Consumer *c);

	Consumer * get_consumer();

	double get_motivation();
	double get_skill();
	double get_capital();
	double get_spendwill();
	double get_income();
	bool get_employment_status();
	void set_employment_status(bool);

};
#endif
