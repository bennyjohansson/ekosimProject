#ifndef ELEMENT_COMPANY_H
#define ELEMENT_COMPANY_H

#include <iostream>
#include <iomanip>
#include <string>

#include "consumer.h"
#include "company.h"

using namespace std;

class Element_company {
public:
	Element_company *next_;
	Company *company_;

	Element_company();
	Element_company(Element_company *n, Company *c);

	string get_name();
	Company * get_company();
};
#endif
