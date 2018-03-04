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

using namespace std;

void randomize(double &average, double deviation) {
  
  //int randvalue;
  int randsign;
  double randv;

  double limit = deviation*average;
  randv = ((rand()%10))*limit/10;
  
  randsign = (rand()%3);
  if(randsign == 1) {
    //cout << " hej i functions.cc randomize1" << endl;
    randv = -randv;
  }
  else {
    //    cout << "hej i functions.cc randomize1" << endl;
  }  
  average += randv;
  if(randsign == 3)
    cout << "vafan i functions.cc randomize" << endl;
  //return randvalue;
}

void normalize(double & value) {
  if(value < 0) {
    value = 0;
  }
  if(value > 1) {
    value = 1;
  }
}

double get_norm(double average, double deviation) {
  double randvalue = 0.2;
  //return gaussian(average, deviation);
}

double get_prod(double sk_sum, double sk, double mot_sum, 
		      double mot, double employees, double capacity) {
  // double capacity = 150;
  double rate = 0.005;
  double prod = 2/3.14*capacity*(sk_sum*sk + mot_sum*mot)*atan(rate*employees);
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

Consumer * random_consumer(Market * market) {

  double mot = 0.6;
  double sk = 0.6;
  double cap = 130; 
  double spe = 0.75;
  randomize(mot, 1);
  randomize(sk, 1);
  randomize(cap, 1);
  randomize(spe, 0.5);
  normalize(spe);
  normalize(sk);
  normalize(mot);
  return new Consumer(mot,sk,cap,spe, market);
}







