#ifndef MARKET_H
#define MARKET_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

//#include "consumer_list.h"
//#include "company_list.h"
//#include "consumer.h"

using namespace std;

class Market {
 public:

  Market();
  Market(string name);

  void info();
  double get_items();
  double get_marginal();
  double get_capital();
  long double get_price_in();
  long double get_price_out();
  
  void set_items(double);
  void set_marginal(double);
  void set_capital(double);
  void set_price_in(double);
  void set_price_out(double);


  bool change_items(double);
  void change_marginal(double);
  bool change_capital(double);
  void change_price_in(double);
  void change_price_out(double);

  void negotiate_price(double);
  double pay_dividends();


 private:

  string name_;
  double items_;
  double marginal_;
  double capital_;  
  double price_in_;
  double price_out_;
  double div_ratio_;

};
#endif






