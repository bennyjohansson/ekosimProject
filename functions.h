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
double randnorm(double, double);
double get_norm(double average, double deviation);
double get_price(double excess);
double get_price(double, double);
double get_prod(double, double, double, double, double, int, double);
double get_prod(Consumer *, double, int, double);
double get_consumer_demand_deposit(double, double, double);
double get_consumer_demand_cash(double, double);

double change_motivation();
double get_consumer_deposit(double, double, double);
double get_consumer_borrow(double, double, double, double, double, double);
void log_transaction(string, double, string, double);
void log_transaction_full(string, string, double, string, double, int fraud = 0);
void log_launder_parameters(double, double, int, int);
unsigned int stopwatch();
string getTimeStr();
//void load_launder_parameters();


double capacity_increase(double, double, double, double);
double factor_increase(double, double, double, double, double);
double item_efficiency_increase(double, double, double);

double item_cost(double, double);

Consumer * random_consumer(string, Market *, Bank *, Clock *);

#endif
