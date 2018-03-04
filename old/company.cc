#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>

//#include "consumer.h"
#include "company.h"
#include "functions.h"

using namespace std;

Company::Company() :
  name_(""),
  capital_(0),
  stock_(0),
  invest_(0.6),
  prod_const_skill_(60),
  prod_const_motivation_(40),
  wage_const_(0.85),
  market_(0),
  employees_(new Consumer_list("Employees")){}

Company::Company(string name, Market * market) :
  name_(name),
  capital_(10000),
  stock_(0),
  invest_(0.6),
  prod_const_skill_(60),
  prod_const_motivation_(40),
  wage_const_(0.95),
  market_(market),
  capacity_(3),
  employees_(new Consumer_list("Employees"))
{}


void Company::info() {
  
  cout << "Name: " << name_ << endl 
       << "Capital: " <<  capital_ << endl
       << "Stock: " << stock_ << endl 
       << "Employees: " << employees_ -> get_size() << endl << endl;
}

void Company::employee_info() {
  cout << name_ << endl << "---------------------" << endl;
  employees_ -> info();
}

string Company::get_name() {
  return name_;
}

double Company::get_capital() {
  return capital_;
}

double Company::get_prod_const_skill() {
  return prod_const_skill_;
}

double Company::get_prod_const_motivation() {
  return prod_const_motivation_;
}

double Company::get_wage_const() {
  return wage_const_;
}

double Company::get_production() {
  
  double skill_sum = employees_ -> get_skill_sum(); 
  double sk = prod_const_skill_;
  double mot_sum =employees_ -> get_motivation_sum();
  //  cout << "I comp get prod, mot sum: " << mot_sum << endl; 
  double mot = prod_const_motivation_;
  double employees = employees_ -> get_size();
  double prod =  get_prod(skill_sum, sk, mot_sum, mot, employees, capacity_);
  return prod;
}

double Company::get_production(Consumer * consumer) {

  //double prod = consumer -> get_skill() * prod_const_skill_ +
  //  consumer -> get_motivation() * prod_const_motivation_;
  double skill = consumer -> get_skill();
  double mot = consumer -> get_motivation();
  double prod = get_prod(skill, skill, mot, mot, 1, capacity_);

  return prod;
} 

double Company::get_stock() {
  return stock_;
}

double Company::get_invest() {
  return invest_;
}

double Company::get_capacity() {
  return capacity_;
}

void Company::set_capital(double capital) {
  capital_ = capital;
}

void Company::set_prod_const_skill(double skill) {
  prod_const_skill_ = skill;
}

void Company::set_prod_const_motivation(double mot) {
  prod_const_motivation_ = mot;
}

void Company::set_wage_const(double wc) {
  wage_const_ = wc;
}

void Company::set_stock(double stock) {
  stock_ = stock;
}

void Company::set_invest(double invest) {
  invest_ = invest;
}

void Company::set_capacity(double capacity) {
  capacity_ = capacity;
}

void Company::change_capital(double ch) {
  //  if (capital_ + ch > 0) {
  capital_ += ch;
  // }
  //else {
  //cout << "Fel i company ch cap" << endl;
  // }
}

void Company::change_prod_const_skill(double ch) {
  prod_const_skill_ += prod_const_skill_;
}

void Company::change_prod_const_motivation(double ch) {
  prod_const_motivation_ += ch;
}

void Company::change_wage_const(double wcc) {
  wage_const_ += wcc;
}

void Company::change_stock(double ch) {
  stock_ += ch;
}

void Company::change_invest(double ch) {
  invest_ += ch;
}

void Company::change_capacity(double ch) {
  capacity_ += ch;
}

void Company::add_employee(Consumer * consumer) {
  
  if(!(consumer -> get_employment_status())) {
    consumer -> set_employment_status(true);
    employees_-> add_first(consumer);

  }
}

void Company::print_employees() {
  employees_ -> print_list();
}

void Company::produce() {  
  stock_ += get_production();
}

double Company::get_total_wages() {

  double production = get_production();
  double size = employees_ -> get_size();
  double price = market_->get_price_in();
  list<double>::iterator theIterator;
  theIterator = wages_.begin();
   
  double wages = production * price * wage_const_ ;
  if(wages/size < *theIterator) {
    wages = *theIterator*size;
    //cout << "hej i com get tot wages" << endl;
  }
  //if(wages/size>300) {
  //  wages = 300*size;
  //
  //}
  return wages;
}

void Company::pay_employees() {

  double size = employees_ -> get_size();

  double wage_tot = get_total_wages();
  double wage = wage_tot/size;

  employees_ -> pay_employees(wage);
  double sum_after = employees_ -> get_capital_sum();
  capital_ -= wage_tot;

  wages_.push_front(wage);
}

//Checks how the expected income changes by adding consumer 
double Company::contribution_adding(Consumer * consumer) {
  double skill = consumer -> get_skill();
  double mot = consumer -> get_motivation();
  double skill_sum = employees_ -> get_skill_sum();
  double mot_sum = employees_ -> get_motivation_sum();
  int employees = employees_ -> get_size();
  double sk_c = prod_const_skill_;
  double mot_c = prod_const_motivation_;

  double prod_before = get_production();
  double prod_after = get_prod(skill_sum+skill, sk_c, mot_sum+mot, mot_c, employees +1, capacity_);
  double price = market_ -> get_price_in();
  double wage = 0;
  double size = employees_ -> get_size() + 1;//I need to add the "1" here to get it right???
  
  if (size != 0) {
    wage = get_total_wages()/size;
  }
  else {
    wage = get_total_wages();   
  }
  double contribution = 0;

  contribution = (prod_after - prod_before)*price - wage;
  return contribution;
}

double Company::contribution_removing(Consumer * consumer) {
  double skill = consumer -> get_skill();
  double mot = consumer -> get_motivation();
  double skill_sum = employees_ -> get_skill_sum();
  double mot_sum = employees_ -> get_motivation_sum();
  int employees = employees_ -> get_size();
  double sk_c = prod_const_skill_;
  double mot_c = prod_const_motivation_;
  double contribution = 0;
  double prod_before = get_production();
  double prod_after = get_prod(skill_sum - skill, sk_c, mot_sum - mot, 
			       mot_c, employees, capacity_); 
  double price = market_ -> get_price_in();
  //double wage = wage_const_ * get_production(consumer)*price;
  
  double size = employees_ -> get_size();
  double wage = 0;
  if (size != 0) {
    wage = get_total_wages()/size;
    contribution = (prod_after - prod_before)*price + wage;
  }
  else {
    wage = get_total_wages();
    contribution = 0;
  }
  
  
  //  cout << "cont rem i company, cont = " << contribution << endl;
  return contribution;
} 

void Company::remove_usless_employees() {
  if(employees_ -> get_size() != 0) {
    employees_ -> info();
    Consumer * bad_empl;
    bad_empl = employees_ -> get_usless_employee(prod_const_skill_, prod_const_motivation_, capacity_);
    cout << "Hej i company usless" << endl;

    while(contribution_removing(bad_empl) > 1) {
      try {
	remove_employee(bad_empl);
      }
      catch (std:: exception a) {
	cout << a.what() << endl;
      }
      //cout << "Hej i com usless" << endl;
      bad_empl = employees_ -> get_usless_employee(prod_const_skill_,  prod_const_motivation_, capacity_);
      //}
      //catch(std::exception e) {
      //cout << e.what() << "Noll anstallda" << endl;
      //}
    }
  }
  cout <<  employees_ -> get_size() << "No consumers to remove in company remove usless employee" << endl;
}

bool Company::update_employees(Consumer * opt) {
  //    cout << name_ << "  " << employees_->get_size() << endl;

  if(employees_ -> get_size() != 0) {
    
    // Consumer * bad_empl = employees_ -> get_usless_employee(prod_const_skill_, prod_const_motivation_, capacity_);

    //while(contribution_removing(bad_empl) > 1000) {	
    //   try {
    //      remove_employee(bad_empl);      	  
    //      bad_empl = employees_ -> get_usless_employee(prod_const_skill_,  prod_const_motivation_, capacity_); 
    //   }
    //   catch(std::exception e) {
    //   //cout << e.what() << "Noll anstallda" << endl;
    //   }
    //} 
    cout << name_ << "	" << employees_->get_size() << endl;  
     
    if(contribution_adding(opt) > 10) {
      add_employee(opt);
      return true;
    }
    //else if(get_production(opt) > get_production(bad_empl) && contribution_adding(opt) > 1000) {
    //   remove_employee(bad_empl);
    //   add_employee(opt);
    //  cout << "I com updsate empl, där remove och sen add" << endl;
    //    return false;
    //}
    //return false;
  }
  else {
    add_employee(opt);
    return true;
  }
}

void Company::update_employees(double skill_limit, 
			       double motivation_limit) {
  //employees_ -> remove_by_motivation(motivation_limit);
  //employees_ -> remove_by_skill(skill_limit);
}

void Company::remove_employee(Consumer * consumer) {
  consumer -> set_employment_status(false);
  consumer -> set_income(0);
  employees_ -> remove_consumer(consumer, capacity_);
  //cout << "I compa rem empl" << endl;
}  


void Company::sell_to_market() {
  double price = market_ -> get_price_in();
  //cout << "s " << stock_ << " p " << price << endl;
  //market_ -> change_items(stock_);
  //change_capital(price*stock_);
  //  cout << "stock: " << stock_ << endl <<"i sell to market company Price: " << price << endl;
  //  if (market_ -> change_capital(-price*stock_)) {
  
  change_capital(price*stock_);
  market_ -> change_capital(-price*stock_);

  market_ -> change_items(stock_);
  change_stock(-stock_);
  //  }
  //else {
  //cout << "Kuk i company sell" << endl;
  //}
}

void Company::invest() {
  double investment = 0;
  double limit = 500000;
  if(capital_ > 0 && investment < limit) {
    investment = invest_ * capital_;
    //    capital_ -= investment;
    //Borde kunna investera bade i storlek, dvs rate, och effektivitet, dvs 
    //prod const skill och motivation. Gor ett enkelt forsok, men borde eg
    //kolla pa reapektive derivator
  }
  else if(investment > limit) {
    //investment = limit;
  }
  
  //  prod_const_motivation_ *= 1 + 0.5*investment/limit;
  //prod_const_skill_ *= 1 + 0.5*investment/limit;
    
}



















