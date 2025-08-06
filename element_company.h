#ifndef ELEMENT_COMPANY_H
#define ELEMENT_COMPANY_H

#include <iostream>
#include <iomanip>
#include <string>
#include <memory>

#include "consumer.h"
#include "company.h"

using namespace std;

class Element_company {
public:
	std::unique_ptr<Element_company> next_;
	Company *company_;  // Non-owning pointer - Company is owned by the list

	Element_company();
	Element_company(std::unique_ptr<Element_company> n, Company *c);

	string get_name() const;
	Company * get_company();
};
#endif
