#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <fstream>

//#include "consumer.h"
#include "functions.h"
#include "city.h"
//#include "consumer_list.h"
//#include "company.h"
//#include "company_list.h"
#include "error_no_return.h"

using namespace std;

City::City() :
  name_("bennyland"),
  consumers_(new Consumer_list("CONSUMERS")),
  company_list_(new Company_list("COMPANIES")),
  labour_market_(new Consumer_list("LABOUR MARKET")),
  market_(new Market())
{}

City::City(string name) :
  name_(name),
  consumers_(new Consumer_list("CONSUMERS")),
  company_list_(new Company_list("COMPANIES")),
  labour_market_(new Consumer_list("LABOUR MARKET")),
  market_(new Market())

{}

void City::consumer_info() {
  consumers_-> info();
}

void City::labour_info() {
  labour_market_ -> info();
}

void City::employee_info() {
  employee_info("all");
}

void City::print_company_list(){

  company_list_ -> print_list();

}

double City::get_company_capacity_sum() {

  return company_list_ -> get_capacity_sum();
}

double City::get_consumer_capital_sum() {

  return consumers_ -> get_capital_sum();
}

void City::employee_info(string command) {
  company_list_ -> employee_info(command);
}

void City::follow_capital(Consumer * consumer) {
  cout << consumer -> get_capital() << " ";
}

void City::follow_capital() {
  follow_capital(get_random_consumer());
} 

Market * City::get_market() {
  return market_;
}

Consumer * City::get_random_consumer() {
  consumers_ -> get_random_consumer();
}

double City::get_capital_sum() {

  double csum = 0;

  csum = consumers_ -> get_capital_sum() + company_list_ -> get_capital_sum() + market_ -> get_capital();

  return csum;
}

int City::get_no_companies() {
  return company_list_ -> get_size();
}

void City::update_market() {
  double marginal_ = market_ -> get_marginal();;
  int consumers_nr = consumers_ -> get_size();
  double capital_sum = consumers_ -> get_capital_sum();
  double spendwill_sum = consumers_ -> get_spendwill_sum();
  double average_spendwill = spendwill_sum/consumers_nr;
  double items = market_ -> get_items();

  //  cout << "I city update market    items = " << items << endl;
  double price_out = average_spendwill*capital_sum/items;
  market_ -> set_price_out(price_out);
  double price_in = price_out/(1 + marginal_);
  market_ -> set_price_in(price_in);
  //cout << "I city update market" << endl << "P in " << price_in << "  P out " << price_out << endl;
} 

void City::negotiate_market_price() {

  double   marginal_ = market_ -> get_marginal();
  int consumers_nr = consumers_ -> get_size();
  double capital_sum = consumers_ -> get_capital_sum();
  //  cout << "I city negotiate!" << consumers_nr << endl;
  double spendwill_sum = consumers_ -> get_spendwill_sum();
  double average_spendwill = spendwill_sum/consumers_nr;
  //cout << "I city negotiate! " << average_spendwill << endl;
  double items = market_ -> get_items() + company_list_ -> get_item_sum();

  list <double>::iterator theIterator;

  theIterator = price_out_.begin();

  
  double price_out = 1*average_spendwill*capital_sum/items;
  
  //if(price_out < *theIterator) {
  //  price_out = *theIterator;
  // }

 

  market_ -> set_price_out(price_out);
  double price_in = price_out/(1 + marginal_);
  market_ -> set_price_in(price_in);

}

void City::market_info() {
  market_ -> info();
}

void City::sell_to_market() {


  double demand = 0;
  double growth = 0;

  demand = consumers_->get_spendwill_sum();
  double ccapf = company_list_ -> get_capital_sum();
  double mcapf = market_ -> get_capital();
  double item = company_list_ -> get_item_sum();
  double price_out = market_ -> get_price_out();
  int size = consumers_ -> get_size();
  double unemployed = consumers_ -> get_unemployed();
  double unemployment = unemployed/size;

  company_list_ -> sell_to_market();
  list <double>::iterator theIterator;

  theIterator = GDP_.begin();

  if(*theIterator != 0) {
    growth = (item - *theIterator)/(*theIterator);
  }
  else {
    growth = 0;
  }

    double randv;

//TESTAR VAD SOM HANDER NAR MAN ANDRAR GROWTH OCH DARMED SPENDWILL
    randv = ((rand()%10));
    if (randv > 8 ) {
      growth = growth - 0.1;
    }
    if (randv <= 2 ) {
      growth = growth + 0.1;
    }


  GDP_.push_front(item);
  growth_.push_front(growth);
  demand_.push_front(demand);
  price_out_.push_front(price_out);
  unemployment_.push_front(unemployment);
  
  double ccape = company_list_ -> get_capital_sum();
  double mcape = market_ -> get_capital();

  //cout << "I city sell to market" << endl << "Market kopt " << item << " enh for " << mcapf - mcape << endl
    //      << "Comp salt for: " << ccape - ccapf << endl;
}

void City::set_consumers(Consumer_list * consumer_list) {
  consumers_ = consumer_list;
}
void City::set_companies(Company_list * company_list) {
  company_list_ = company_list;
}

void City::set_labour_market(Consumer_list * labour_market) {
  labour_market_ = labour_market;
}

void City::add_consumer(double motivation, double skill,
			double capital, double spendwill) {
  Consumer * consumer = new Consumer(motivation, skill, 
				     capital, spendwill);
  consumers_ -> add_first(consumer);
}

void City::add_consumer(Consumer * consumer) {
  consumers_ -> add_first(consumer);
}
 
void City::add_company(string name) {
  Company * company = new Company(name, market_);
  company_list_ -> add_company(company);
}

void City::info() {
  cout << endl 
       << "----------------------------------------" << endl
       << "THE CITY" << endl
       << "----------------------------------------" << endl
       << "Name: " << name_ << endl
       << "Population: " << consumers_ -> get_size() << endl << endl
       << "COMPANIES " << endl;
  company_list_ -> print_list();
  cout << endl;
}

void City::print_consumer_list() {
  consumers_ -> print_list();

}

void City::print_employees(string company) {
  company_list_ -> print_employees(company);
}

void City::print_labour_market() {
  labour_market_ -> print_list();
}

void City::update_consumer_list() {

  list <double>::iterator theIterator = growth_.begin();
  const int MAX = 4;
  int i = 1;
  double factor = 0;

  for(theIterator; (theIterator != growth_.end() && i < MAX); theIterator++) {
    factor += 1/i*(*theIterator);
    i++;
  }
  consumers_ -> update(factor);
}

Company * City::get_company(string name) {
  return company_list_ -> get_company(name);
}

Company * City::get_random_company() {
  return company_list_ -> get_random_company() -> get_company();
}

Element_consumer * City::get_motivated_consumers() {
  return consumers_ -> get_motivated_consumers();
}

void City::add_motivated_consumers(Element_consumer * workers) {
  //labour_market_ -> add_group_last(workers);
}

void City::add_employee(string name, Consumer * consumer) {
//  company_list_ -> add_employee(name, consumer);
//  labour_market_ -> remove_consumer(consumer);
}

void City::remove_consumer_from_labour_market(Consumer * consumer) {
  //labour_market_ -> remove_consumer(consumer);
}

void City::update_company_employees() {
  company_list_ -> update_company_employees();
}

void City::update_employees(string name) {
  //FLYTTA WHILESATSEN TILL COMPANYLIST SA SAR DE TURAS OM   
  //NU BLIR DET JU FEL ME OPTIMAL OCH SA, MEN DET ORDNAR VI SENARE
  name = get_random_company() -> get_name();
  
  double skill =  get_company(name) -> get_prod_const_skill(); 
  double mot = get_company(name) -> get_prod_const_motivation();


  company_list_ -> remove_usless_employees();
  
  cout << "Hej i city.cc update empl" << endl;  
  Consumer * opt;
  while(company_list_ -> update_employees2(opt = get_optimal_consumer(mot, skill))){}
}

void City::produce() {
   company_list_ -> produce();
}

void City::pay_company_employees() {
  company_list_ -> pay_employees();
}


//ASSUMING THAT ALL CONSUMERS OWNS AN EQUAL SHARE OF THE COMPANIES
void City::company_pay_dividends() {
   double total_profit_c;
   double total_profit_m;
   double amount;	
   double size = consumers_ -> get_size();
   
   total_profit_c = company_list_ -> pay_dividends();
   total_profit_m = market_->get_capital();
   market_ -> set_capital(0);

   amount = (total_profit_m + total_profit_c)/size;
   consumers_ -> pay_dividends(amount);


}

//MASTE JATTEMYCKET SKRIVAS OM!!!
Consumer * City::get_optimal_consumer(double mot_we, double skill_we) {
  double cap_sum = get_company_capacity_sum();
  int no_companies = get_no_companies();
  double  capacity = cap_sum/no_companies;
  try {
    //return (labour_market_ -> get_optimal_consumer(mot_we, skill_we, capacity));
  return (consumers_ -> get_optimal_consumer(mot_we, skill_we, capacity));

   }
  catch(no_return_error) {
    cout << "ingen_consumer" << endl;
  }
}


void City::consumers_buy() {
  double csumf = consumers_ -> get_capital_sum();
  double msumf = market_ -> get_capital();
  double isumf = consumers_ -> get_item_sum();
  consumers_ -> consumers_buy();

  double csume = consumers_ -> get_capital_sum();
  double msume = market_ -> get_capital();
  double isume = consumers_ -> get_item_sum();

  //  cout << "i  city cons_buy" << endl << "Conumers har kopt " << isume - isumf << " for: " << csumf - csume << endl 
  //   << "Market har salt for: " << msume - msumf << endl;
}


void City::invest() {
  company_list_ -> invest();
}


void City::print_GDP() {

  const int SPACE = 15;
  list <double>::iterator theIterator;
  list <double>::iterator theIterator2;
  list <double>::iterator theIterator3;
  list <double>::iterator theIterator4;
  list <double>::iterator theIterator5;
 list <double>::iterator theIterator6;

  theIterator2 = growth_.begin();
  theIterator3 = demand_.begin();
  theIterator4 = (company_list_ -> get_company("bempa AB"))->wages_.begin();
  theIterator5 = price_out_.begin();
  theIterator6 = unemployment_.begin();

  cout << "GDP for bennyland / produced items"
       << endl << "-----------------------------------------------------" << endl 
       << setw(SPACE) << "GDP" << setw(SPACE) << "Growth" << setw(SPACE) << "Acc. sw." << setw(SPACE) << "Wages" << setw(SPACE) << "Price in" << endl;
  theIterator2 = growth_.begin();
  for (theIterator = GDP_.begin(); theIterator != GDP_.end();theIterator++) {
    cout << setw(SPACE) << *theIterator << setw(SPACE) << *theIterator2 << setw(SPACE) << *theIterator3 << setw(SPACE) << *theIterator4 << setw(SPACE) << *theIterator5 << setw(SPACE) << *theIterator6 << endl;
    theIterator2++;
    theIterator3++;
    theIterator4++;
    theIterator5++;
    theIterator6++;

  }
  cout << endl << endl;
  

  theIterator2 = growth_.begin();
  theIterator3 = demand_.begin();
  theIterator4 = (company_list_ -> get_company("bempa AB"))->wages_.begin();
  ofstream  file ("gdp.txt");
  for (theIterator = GDP_.begin(); theIterator != GDP_.end();theIterator++) {
    file << *theIterator << " " << *theIterator2 << " " << *theIterator3 << " " << *theIterator4 << endl;
    theIterator2++;
    theIterator3++;
    theIterator4++;  
}
  file.close();

  ofstream  file2 ("growth.txt");
  for (theIterator = growth_.begin(); theIterator != growth_.end();theIterator++) {
    file2 << setw(SPACE) << *theIterator << endl;
  }
  file2.close();

  ofstream  file3 ("demand.txt");
  for (theIterator = demand_.begin(); theIterator != demand_.end();theIterator++) {
    file3 << setw(SPACE) << *theIterator << endl;
  }
  file3.close();
  

}















