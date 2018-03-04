#include <iostream> 
#include <iomanip>
#include <string>

#include "market.h"



using namespace std;

Market::Market() : 
  name_("MARKET"),  
  items_(10),
  marginal_(0),
  capital_(100000),
  price_in_(100),
  price_out_(100)
{}

void Market::info() {
  cout << name_ << endl << "-------------------------------------------------"
       << endl << "Items: " << items_ << endl << "Value of items: " << items_*price_out_<< endl << "Capital: " << capital_ << endl << "Total assets: " << capital_ + price_out_*items_ << endl << "Price in: " << price_in_ << endl
       << "Price out: " << price_out_ << endl << endl;
}

double Market::get_items() {
  return items_;
}

double Market::get_marginal() {
  return marginal_;
}


double Market::get_capital() {
  return capital_;
}

long double Market::get_price_in() {
  return price_in_;
}

long double Market::get_price_out() {
  return price_out_;
}

void Market::set_items(double items) {
  items_ = items;
}

void Market::set_marginal(double marginal) {
  marginal_ = marginal;
}


void Market::set_capital(double capital) {
  capital_ = capital;
}

void Market::set_price_in(double price) {
  if(price > 0.000000001) {
    price_in_ = price;
  }
  else {
    price = 1;
  }
}

void Market::set_price_out(double price) {
  if(price > 0.000000001) {
    price_out_= price;
  } 
  else {
    price = 1;
  }
}

bool Market::change_items(double ch) {
  //  if(items_ >= -ch || ch > 0) {
    items_ += ch;
    return true;
    //}  
    //else {
    // cout << "Imarket ch_it och ch = " << ch << endl << "I = " << items_ << endl;
    // return false;
    //  }
}

void Market::change_marginal(double ch) {
  marginal_ += ch;
}

bool Market::change_capital(double ch) {
  //  if (capital_ >= -ch || ch > 0) {
    capital_ += ch;
    //    cout << "i market ch cap, ch = " << ch << endl;
    return true;
    //}
    //else {
    //cout << "Fel u market ch_cap" << endl;
    //return false;
    // }
}

void Market::change_price_in(double ch) {
  price_in_ += ch;
  cout << "i market ch_price in" << endl;
}

void Market::change_price_out(double ch) {
  price_out_ += ch;
  cout << "i market ch_price out" << endl;

}

void Market::negotiate_price(double items) {

}















