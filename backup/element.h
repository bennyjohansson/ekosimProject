#ifndef ELEMENT_H
#define ELEMENT_H
#include <iostream>
#include <iomanip>
#include <string>
#include "consumer.h"

using namespace std;

class Element {
public:
	Element *next_;
	Consumer *cons_;

	Element(Element *n, Consumer *c) : next_(n), cons_(c) {}
};
#endif
