#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "functions.h"
#include "consumer.h"
#include "market.h"
#include "clock.h"

using namespace std;

void randomize(double &average, double deviation) {
  
  //int randvalue;
  int randsign;
  double randv;

  double limit = deviation*average;
  randv = ((rand()%10))*limit/10;
  
  randsign = (rand()%3);
  if(randsign == 1) {
    randv = -randv;
  }  
  average += randv;
}

void normalize(double & value) {
  if(value < 0) {
    value = 0;
  }
  if(value > 1) {
    value = 1;
  }
}

double get_prod(double sk_sum, double sk, double mot_sum, 
		double mot, double employees, double capacity) {
  // double capacity = 150;
  double rate = 0.0002;
  double prod = 1/3.14*capacity*(atan(rate*sk_sum*sk) + atan(rate*mot_sum*mot));
  //cout << prod << endl;
  return prod;
}

double get_prod(Consumer * consumer, double capacity) {
  double skill = consumer -> get_skill();
  double mot = consumer -> get_motivation(); 
  //  cout << "Hej i functions get_prod(Consumer) " << endl;
  return get_prod(skill, skill, mot, mot, 1, capacity);
  //THE 150 ABOVE SHOLUD NOT BE; IS THIS IN USE; TESTING
}

double get_price(double excess) {

double P_MAX = 100;
double P_SENS = -0.002;
double price = 0;
price = P_MAX*exp(P_SENS*excess);
//cout << price << endl;

return price;
}

double get_price(double excess, double sum_spend) {
  
  double price;
  if(excess != 0) {
    return price = sum_spend/excess;
  }
  else {
    return INT_MAX;
  }
}

Consumer * random_consumer(Market * market, Bank * bank, Clock * clock) {

  double mot = 0.6;
  double sk = 0.5;
  double cap = 70; 
  double spe = 0.7;
  double save = 1-spe;
  double borrow = 0.01;
  randomize(mot, 0.7);
  randomize(sk, 0.7);
  randomize(cap, 1);
  randomize(spe, 0.5);
  randomize(save, 0.5);
  randomize(borrow, 0.5);
  normalize(spe);
  normalize(sk);
  normalize(mot);
  normalize(save);
  normalize(borrow);
  return new Consumer(mot,sk,cap,spe, save, borrow, market, bank, clock);
}


double capacity_increase(double items) {

  double increase = 0;

  increase = 20*log(0.01*items + 1);//70*log(1 + 0.1*items);

  return increase;
}

double item_cost(double production) {

  double items = 0;
  const double factor = 0.1;

  items = log(production + 1)*(factor);

  return items;
}







