#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "consumer.h"
#include "market.h"
#include "bank.h"

using namespace std;

void randomize(double&, double);
void normalize(double&);
double get_norm(double average, double deviation);
double get_price(double excess);
double get_price(double, double);
double get_prod(double, double, double, double, double, double);
double get_prod(Consumer *, double);
double change_motivation();
double get_consumer_loan(double, double, double);
double get_consumer_borrow(double, double, double);
void log_transaction(string, double, string, double);
void log_transaction_full(string, string, double, string, double, int fraud = 0);
void log_launder_parameters(double, double, int, int);
//void load_launder_parameters();


double capacity_increase(double, double);
double item_cost(double);

Consumer * random_consumer(Market *, Bank *, Clock *);

#endif
