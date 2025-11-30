#include <iostream> 
#include <iomanip>
#include <string>
#include <cmath>

#include "market.h"



using namespace std;

Market::Market() : 
  name_("MARKET"),  
  items_(10),
  marginal_(0.05),
  capital_(200000),
  price_in_(5),
  price_out_(5),
  div_ratio_(0.5), 
  excess_demand_items_(0),
  number_of_participants_(0)
{}

Market::Market(string name) : 
  name_(name),  
  items_(10),
  marginal_(0.05),
  capital_(200000),
  price_in_(5),
  price_out_(5),
  div_ratio_(0.5), 
  excess_demand_items_(0),
  number_of_participants_(0)
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

int Market::get_excess_demand_items() {
	return excess_demand_items_;
}

double Market::get_aggregate_supply() {
  return aggregate_supply_;
}

double Market::get_aggregate_demand() {
  return aggregate_demand_;
}

int Market::get_number_of_participants() {
  return number_of_participants_;
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
    price_out_ = price_in_*(1+marginal_);
  }
  else {
    price = 1;
  }
}

void Market::set_price_out(double price) {
  if(price > 0.000000001) {
    price_out_= price;
    price_in_ = price_out_/(1+marginal_);
  } 
  else {
    price = 1;
  }
}

void Market::set_number_of_participants(int participants) {
  number_of_participants_ = participants;
}

void Market::change_aggregate_demand(double ch) {
  aggregate_demand_ += ch;
}

void Market::change_aggregate_supply(double ch) {
  aggregate_supply_ += ch;
}

void Market::reset_aggregate_demand_and_supply() {
  aggregate_demand_ = 0;
  aggregate_supply_ = 0;
  // number_of_participants_ = 0;
}

void Market::reset_numnber_of_participants() {
  number_of_participants_ = 0;
}

void Market::reset_excess_demand_items() {
	excess_demand_items_ = 0;

}

void Market::change_number_of_participants(int ch) {
  number_of_participants_ += ch;
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

int Market::customer_buy_items(double money) {

	int items_wanted = 0;
	int items_sold = 0;
	int items_available = 0;
	double purchase_amount = 0;
	
	items_wanted = floor(money/price_out_);
	
	items_available = items_;
	
	items_sold = fmax(0,fmin(items_wanted, items_available));
	purchase_amount = items_sold*price_out_;
	
	if(items_available < items_wanted) {
	
    cout << "I Market customer buy items, not enough items in market, wanted items: " << items_wanted << " available items: " << items_available << " excess demand: " << (items_wanted - items_available) << " total excess demand: " << excess_demand_items_ << endl;

		excess_demand_items_ += (items_wanted - items_available);
	
	}
	
	//cout << "I Market customer buy, items: " << items_sold << " Purch amount: " << purchase_amount << " wanted amount: " << money << endl;
	
	items_ -= items_sold;
	capital_ += purchase_amount;

	return items_sold;

}

double Market::market_buy_items(int items) {

	
	//double cost_of_items = 0;
	int max_items_to_be_bought = 0;
	double max_cost = 0;
	double desired_amount_cost = 0;
	int items_bought = 0;
	double price_in = 0;
	
	price_in = get_price_in();
	//double actual_cost = 0;
	
	desired_amount_cost = items*price_in;
	
	max_cost = fmax(0, fmin(desired_amount_cost, capital_));
	max_items_to_be_bought = max_cost/price_in;
	
	//cout << "I markt sell to mkt, cost: " << max_cost << " items: " << max_items_to_be_bought << " and price: " << price_in << endl;

	if(max_items_to_be_bought < items) {
		//cout << "I Market market_buy_items, not enough money in market, des cost: " << desired_amount_cost << " actual cost: " << max_cost << endl;
	
	}
	
	//items_ += max_items_to_be_bought;
	//capital_ -= max_cost;
	
	items_ += items;
	capital_ -= desired_amount_cost;
	

	return desired_amount_cost; //max_cost;

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

double Market::pay_dividends() {

  double dividends = 0;
  double safety_amount = 0;
  
  safety_amount = 10*fmax(0, excess_demand_items_)*price_out_;

  if(capital_ > 0) {

    dividends = fmax((capital_ -  safety_amount), 0)* div_ratio_;

  }
  else {

    dividends = 0;
  }

  capital_ -= dividends;

  return dividends;

}














