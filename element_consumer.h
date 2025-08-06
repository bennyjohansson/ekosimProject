#ifndef ELEMENT_CONSUMER_H
#define ELEMENT_CONSUMER_H
#include <iostream>
#include <iomanip>
#include <string>
#include <memory>

#include "consumer.h"
//#include "city.h"

using namespace std;

class Element_consumer {
public:

	Element_consumer();
	Element_consumer(std::unique_ptr<Element_consumer> n, Consumer *c);
	~Element_consumer();

	std::unique_ptr<Element_consumer> next_;
	Consumer * consumer_;

	Consumer * get_consumer() const;

	double get_motivation() const;
	double get_skill() const;
	double get_capital() const;
	double get_spendwill() const;
	double get_income() const;
	double get_loans() const;
	bool get_employment_status() const;
	void set_employment_status(bool);

};
#endif
