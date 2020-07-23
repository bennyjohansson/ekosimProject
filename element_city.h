#ifndef ELEMENT_CITY_H
#define ELEMENT_CITY_H

#include <iostream>
#include <iomanip>
#include <string>

#include "city.h"

using namespace std;

class Element_city {
public:
	Element_city *next_;
	City *city_;

	Element_city();
	Element_city(Element_city *n, City *c);

	string get_name();
	City * get_city();
};
#endif
