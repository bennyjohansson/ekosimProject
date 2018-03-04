#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "functions.h"
//#include "city.h"
#include "consumer.h"

using namespace std;

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

Consumer::Consumer(double mot, double sk, double cap, double spe, Market * m) :
  motivation_(mot),
  skill_(sk),
  capital_(cap),
  spendwill_(spe),
  employed_(false),
  market_(m),
  income_(0),
  items_(0) 
  //city_(0)
{}


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

//void Consumer::set_city(City * city) {
//  city_ = city;
//}

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



// Here we must think. Should the change-functions be
// member-functions of Consumer or not? Benefit is that no 
// arguments have to be sent. Think this is the best solution.
//and the functions are very related to the consumer class

void Consumer::update_values(double factor) {
  //  update_capital(); 
  //update_skill();
  update_spendwill(factor);
  // update_motivation();
}

void Consumer::update_capital() {
  //capital += income_;
}

void Consumer::update_skill() {
  int skill_change;
  double EMP_CONST = 0.0001;

  bool emp = get_employment_status();
  if(emp) {
    skill_ *= (1 + EMP_CONST);
  }
  else {
    skill_ *= (1 - EMP_CONST);
  }

  randomize(skill_, 0.1);
  normalize(skill_);
}

void Consumer::update_spendwill(double sum) {

  //  double k = 0;
  //const double ka = 1;
  //const double kb = 0.5;
  //const double kc = 0.33;
  //double k = 1/(ka + kb+ kc)//;

  //SKRIV SOM EN SUMMA DAR KONST AR EN  sumISTA OXO
  //sum  = 0;
  //sum = ka*(*theIterator);
  //theIterator++;
  //sum  += kb*(*theIterator);
  //theIterator++;
  //sum += kc*(*theIterator);
  //sum *= k;
   
  spendwill_ = spendwill_ + 0.1*sum;

  //  randomize(spendwill_, 0.1);
  normalize(spendwill_);
}

void Consumer::update_motivation() {
  const double MOTIVATION_CAP_CONST = 0.001;
  const double EMP_CONST = 0.01;
  bool emp = get_employment_status();
  motivation_ = motivation_*(1+MOTIVATION_CAP_CONST*1/(1 + capital_));
  if(emp) {
    motivation_ *= (1-EMP_CONST);
  }
  else {
    motivation_ *= (1+EMP_CONST);
  }

  randomize(motivation_, 0.1);
  normalize(motivation_);

}


void Consumer::buy() {
  const double FEL_STALLE = 0.2;
  double amount = capital_ * spendwill_; //+ (capital_ - income_)*FEL_STALLE;
  //  cout << amount << endl;
  double price = market_ -> get_price_out();
  double quantity = amount/price;

  if (market_ -> get_items() > quantity) {
     items_ += quantity;
     market_ -> change_capital(amount);
     change_capital(-amount);
     market_ -> change_items(-quantity);
  }
}


//  Company * employer_;
// Employee_list employee_info_;
// int weeks_employed_;
// int weeks_unemployed_;
// double income_;
// City * city_;






