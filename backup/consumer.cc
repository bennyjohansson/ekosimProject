#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "functions.h"
#include "clock.h"
#include "consumer.h"

using namespace std;

/*
 * Constructors
 */

Consumer::Consumer() : 
  motivation_(0),
  skill_(0),
  capital_(0),
  spendwill_(0),
  employed_(false)
  //city_(0)
{}

Consumer::Consumer(double mot, double sk, double cap, double spe) :
  motivation_(mot),
  skill_(sk),
  spendwill_(spe),
  employed_(false),
  capital_(cap),
  income_(0),
  items_(0)
{}

Consumer::Consumer(double mot, double sk, double cap, double spe, double save, double borrow, Market * m, Bank *b, Clock * c) :
  motivation_(mot),
  skill_(sk),
  capital_(cap),
  spendwill_(spe),
  savewill_(save),
  borrowwill_(borrow),
  employed_(false),
  income_(0),
  items_(0),
  loans_(0), 
  market_(m),
  bank_(b),
  clock_(c)
{}

/*
 * Info functions
 */

void Consumer::info() {
  cout << "Motivation: " << get_motivation() << endl 
       << "Skill: " <<  get_skill() << endl
       << "Capital: " << get_capital() << endl
       << "Spendwill: " << get_spendwill() << endl
       << "Employed: ";
  if (employed_) {
    cout << "yes" << endl;
  }
  else {
    cout << "no" << endl;
  }
}


/*
 * Print short info about a consumer in table form over time. Call once in each loop.
 */
void Consumer::info_head() {
  int space = 9;
  cout << setw(space) << "Mot" 
       << setw(space) << "Skill" 
       << setw(space) << "Spendw" 
       << setw(space) << "Cap"
       << setw(space + 3) << "Items"
       << setw(space) << "Wage"
       << setw(space) << "Employed" << endl;
}

void Consumer::info_short() {
  int space = 9;
  string employed = "";
  
  if(get_employment_status()) {
    employed = "yes";
  }
  else {
    employed = "no";
  }
  
  cout << setiosflags(ios::fixed) << setprecision(2)  
       << setw(space) << get_motivation() 
       << setw(space) << get_skill()
       << setw(space) << get_spendwill()
       << setw(space) << get_capital()
       << setw(space + 2) << get_items()
       << setw(space) << get_income()
       << setw(space-2) << " " << employed << endl;
}

/*
 * Get-functions for the consumer
 */

double Consumer::get_motivation(){
  return motivation_;
}

double Consumer::get_skill(){
  return skill_;
}
double Consumer::get_capital(){
  return capital_;
}
double Consumer::get_spendwill(){
  return spendwill_;
}

double Consumer::get_income() {
  return income_;
}

bool Consumer::get_employment_status() {
  return employed_;
}

double Consumer::get_items() {
  return items_;
}

double Consumer::get_loans() {
  return loans_;
}

double Consumer::get_debts() {
  return debts_;
}

double Consumer::get_desired_loans() {
  double amount = 0;
  double interest = 0;

  interest = bank_ -> get_interest();

  if(capital_ > 0) {
    amount = savewill_*capital_*10*interest;
  }
  else {
    amount = 0;
  }

  return amount;
}

double Consumer::get_desired_borrow() {
  double amount = 0;
  double interest = 0;
  double available_capital = 0;

  interest = bank_ -> get_interest();
  available_capital = bank_ -> get_assets();

  amount = borrowwill_*capital_/(0.3+interest);

  if(amount > available_capital && available_capital > 0) {
    amount = available_capital;
  }
  else if (available_capital < 0) {
    amount = 0;
  }

  return amount;
}

/*
 * Set-functions for the consumer
 */

void Consumer::set_motivation(double mot){
  motivation_ = mot;
}
void Consumer::set_skill(double skil){
  skill_ = skil;
}
void Consumer::set_capital(double cap){
  capital_ = cap;
}
void Consumer::set_spedwill(double spendw){
  spendwill_ = spendw;
}

void Consumer::set_income(double income) {
  income_ = income;
}
void Consumer::set_employment_status(bool employed) {
  employed_ = employed;
}

void Consumer::set_items(double items) {
  items_ = items;
}

void Consumer::set_loans(double loans) {
  loans_ = loans;
} 

void Consumer::set_debts(double debts) {
  debts_ = debts;
}


/*
 * Change-functions for the consumer
 */

void Consumer::change_motivation(double mot){
  motivation_ += mot;
}
void Consumer::change_skill(double skil){
  skill_ += skil;
}

void Consumer::change_capital(double cap){
  //  if (capital_ >= -cap || cap > 0) {
    capital_ += cap;
    // }
    //else {
    //cout << "Fel i consumer ch_cap" << endl;
    // }
}

void Consumer::change_spendwill(double spendw){
  spendwill_ += spendw;
}

void Consumer::change_income(double income_ch) {
  income_ += income_ch;
}

void Consumer::change_items(double ch) {
  items_ += ch;
}


void Consumer::change_loans(double ch) {
  loans_ += ch;
}

void Consumer::change_debts(double ch) {
  debts_ += ch;
}

/* 
 * Here we must think. Should the change-functions be  member-functions of Consumer or not? 
 * Benefit is that no  arguments have to be sent. Think this is the best solution and the 
 * functions are very related to the consumer class
 */

void Consumer::update_values() {
  // update_capital(); 
  update_skill();
  update_spendwill();
  //update_motivation();
}

void Consumer::update_skill() {
  int skill_change;
  double EMP_CONST = 0.05;

  //bool emp = get_employment_status();
  //if(emp) {
  //  skill_ *= (1 + EMP_CONST);
  //}
  //else {
  //  skill_ *= (1 - EMP_CONST);
  // }

  double time = clock_ -> get_time();
  //  if(time == 330) {
  //  skill_ = 1.15*skill_;
  //}

  //if(time == 360) {
  //  skill_ = 0.9*skill_;
  //}
  //randomize(skill_, 0.1);
  normalize(skill_);
}


void Consumer::update_spendwill() {

  //spendwill_ = spendwill_ + 1*sum;

  /*
   * Trying the stem response on a change in demand, should not
   * be made here though, need to collect that somewhere else. 
   * Maybe we should make a "calander" class with events...
   */

  double time = clock_ -> get_time();

  if(time == 120) {
    spendwill_ = 1.1*spendwill_;
  }
  if(time == 140) {
    spendwill_ = 1.1*spendwill_;
  }
 if(time == 160) {
    spendwill_ = 0.86*spendwill_;
  }

  
  //if(time == 220) {
  //  spendwill_ = 0.85*spendwill_;
  //}
  //if(time == 260) {
  //  spendwill_ = 0.85*spendwill_;
  // }
  
  //if(time == 300) {
  //  spendwill_ = 0.85*spendwill_;
  //}
  //  randomize(spendwill_, 0.1);
  normalize(spendwill_);
}


void Consumer::update_motivation() {
  //const double MOTIVATION_CAP_CONST = 0.001;
  //const double EMP_CONST = 0.01;

  //bool emp = get_employment_status();
  //motivation_ = motivation_*(1+MOTIVATION_CAP_CONST*1/(1 + capital_));

  //if(emp) {
  //  motivation_ *= (1-EMP_CONST);
  //}

  //else {
  //  motivation_ *= (1+EMP_CONST);
  //}

  randomize(motivation_, 0.1);
  normalize(motivation_);
}


void Consumer::buy() {
  
  double amount = 0;
  double price = 0;
  double quantity = 0;

  if (capital_ > 0) {
    amount = capital_ * spendwill_;
  }

  price = market_ -> get_price_out();
  quantity = amount/price;
  
  /*
   * Have to check if the market has got enough intems to sell 
   */

  if (market_ -> get_items() > quantity && amount > 0) {

    items_ += quantity;
    market_ -> change_capital(amount);
    change_capital(-amount);
    market_ -> change_items(-quantity);
  
  }

}

void Consumer::deposit_to_bank() {

  double amount = 0;
 
  amount = get_desired_loans();

  change_capital(-amount);
  change_loans(amount);
  bank_ -> change_debts(amount);

}

void Consumer::borrow_from_bank() {
  double amount = 0;

  amount = get_desired_borrow();

  change_capital(amount);
  change_debts(amount);
  bank_ -> change_loans(amount);

}

void Consumer::repay_to_bank() {
  double amount = 0;
  double payback_time = 0;
  
  payback_time = bank_ -> get_payback_time();
  amount = debts_/(payback_time*12);
  
  if(amount > capital_) {
    amount = capital_;
  }

  change_capital(-amount);
  change_debts(-amount);
  //  bank_ -> change_assets(amount);
  bank_ -> change_loans(-amount);
}

void Consumer::get_repayment_from_bank() {
  double amount = 0;
  double payback_time = 0;
  
  payback_time = bank_ -> get_payback_time();
  amount = loans_/(payback_time*12);
  
  if(amount > bank_ -> get_assets()) {
    amount = bank_ -> get_assets();
  }

  change_capital(amount);
  change_loans(-amount);
  //bank_ -> change_assets(-amount);
  bank_ -> change_debts(-amount);
}



void Consumer::get_interest() {
  double interest = 0;
  double amount = 0;

  interest = bank_ -> get_interest();
  amount = interest*loans_;

  change_capital(amount);
  bank_ -> change_assets(-amount);
}

