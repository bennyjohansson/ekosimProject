#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "consumer.h"
#include "market.h"

using namespace std;

void randomize(double&, double);
void normalize(double&);
double get_norm(double average, double deviation);
double get_price(double excess);
double get_price(double, double);
double get_prod(double, double, double, double, double, double);
double get_prod(Consumer *, double);
double change_motivation();



Consumer * random_consumer(Market *);

#endif
