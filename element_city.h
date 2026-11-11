#ifndef ELEMENT_CITY_H
#define ELEMENT_CITY_H

#include <iostream>
#include <iomanip>
#include <string>
#include <memory>

#include "city.h"

using namespace std;

class Element_city {
public:
	std::unique_ptr<Element_city> next_;
	std::unique_ptr<City> city_;

	Element_city();
	Element_city(std::unique_ptr<Element_city> n, std::unique_ptr<City> c);

	string get_name() const;
	City * get_city() const;
};
#endif
