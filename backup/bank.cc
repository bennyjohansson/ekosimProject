#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "bank.h"

using namespace std;

Bank::Bank() :
  name_(""),
  interest_rate_(0),
  debts_(0),
  assets_(0)
{}

Bank::Bank(string name, double interest, int payback_time) :
  name_(name),
  interest_rate_(interest),
  assets_(0),
  debts_(0),
  loans_(0),
  payback_time_(payback_time)
{}

/*
 * Info-functions
 */

void Bank::info() {

  cout << "BANK: " << name_ << endl << "--------------------------" << endl
       << "Iterest rate: " << interest_rate_ << endl
       << "Assets: " << assets_ << endl
       << "Debts: " << debts_ << endl
       << "Loans: " << loans_ << endl;
  
}

double Bank::get_interest() {
  return interest_rate_;
}

double Bank::get_assets() {
  return assets_;
}

double Bank::get_debts() {
  return debts_;
}

double Bank::get_loans() {
  return loans_;
}
double Bank::get_payback_time() {
  return payback_time_;
}

double Bank::get_loan_cost(double loan) {
  double monthly_amount = 0;
  double remains = 0;
  double sum = 0;
  int t = 0;  
  remains = loan;

  monthly_amount = loan/(payback_time_*12);

  while(remains > 0) {

    if(remains < monthly_amount) {
      monthly_amount = remains;
    }
    //   cout << "Hej i bank loan_cost " << monthly_amount << endl;
    sum += (monthly_amount + interest_rate_*remains)/pow((1 + interest_rate_), t);

    remains -= monthly_amount;
  }

  return sum;

}

void Bank::set_interest(double interest) {
  interest_rate_ = interest;
}

void Bank::set_assets(double assets) {
  assets_ = assets;
}

void Bank::set_debts(double debts) {
  debts_ = debts;
  //update_assets();
}

void Bank::set_loans(double loans) {
  loans_ = loans;
  //update_assets();
}

void Bank::set_payback_time(double pb) {
  payback_time_ = pb;
}

void Bank::change_interest(double ch) {
  if(interest_rate_ + ch > 0) {
    interest_rate_ += ch;
  }
  else {
    interest_rate_ = 0;
  }
}

void Bank::change_assets(double ch) {
  //  cout << "Assets" << endl;
  assets_ += ch;
}

void Bank::change_debts(double ch) {
  //cout << "Debts" << endl;
  debts_ += ch;
  change_assets(ch);
}

void Bank::change_loans(double ch) {
  //cout << "Loans" << endl;
  loans_ += ch;
  change_assets(-ch);
}

void Bank::change_payback_time(double ch) {
  payback_time_ += ch;
}

void Bank::update_assets() {
  //cout << "update assets" << endl;
  //assets_ = debts_ - loans_;
}
