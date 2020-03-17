#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>

#include "bank.h"

using namespace std;

Bank::Bank() :
name_(""),
interest_rate_(0),
deposits_(0),
assets_(0),
div_ratio_(0)
{}

Bank::Bank(string name, double interest, int payback_time) :
name_(name),
interest_rate_(interest),
assets_(0),
deposits_(0),
loans_(0),
safety_(0.4),
trustworthy_(true),
payback_time_(payback_time),
div_ratio_(0.00)
{}

/*
 * Info-functions
 */

void Bank::info() {
    
    cout << "BANK: " << name_ << endl << "--------------------------" << endl
    << "Iterest rate: " << interest_rate_ << endl
    << "Assets: " << assets_ << endl
    << "deposits: " << deposits_ << endl
    << "Loans: " << loans_ << endl;
    
}

double Bank::get_interest() {
    return interest_rate_;
}

double Bank::get_assets() {
    return assets_;
}

double Bank::get_deposits() {
    return deposits_;
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

double Bank::get_sum_to_borrow() {
    double safety_amount = 0;
    double sum = 0;
    
    
    //cout << "I bank get_sum_to_borrow, unchecked changes" << endl;
    safety_amount = loans_*safety_;
    
    if(safety_amount > assets_ && assets_ > 0) {
        safety_amount = assets_;
        sum = assets_ - safety_amount;
        //sum = safety_amount - assets_;
    }
    else if (assets_ <= 0){
        sum = -assets_;
    }
    
    return sum;
}

double Bank::get_safety() {
    return safety_;
}

bool Bank::get_trustworthy() {
    return trustworthy_;
}

void Bank::set_interest(double interest) {
    interest_rate_ = interest;
}

void Bank::set_assets(double assets) {
    assets_ = assets;
}

void Bank::set_deposits(double deposits) {
    deposits_ = deposits;
    //update_assets();
}

void Bank::set_loans(double loans) {
    loans_ = loans;
    //update_assets();
}

void Bank::set_payback_time(double pb) {
    payback_time_ = pb;
}

void Bank::set_trustworthy(bool trust) {
    trustworthy_ = trust;
}

void Bank::change_interest(double ch) {
    if(interest_rate_ + ch > 0) {
        interest_rate_ += ch;
    }
    else {
    
    	interest_rate_ += ch;
        //interest_rate_ = 0;
    }
}

void Bank::change_assets(double ch) {
    //  cout << "Assets" << endl;
    assets_ += ch;
}

void Bank::change_deposits(double ch) {
    //cout << "deposits" << endl;
    deposits_ += ch;
    change_assets(ch);
}

void Bank::change_loans(double ch) {
    //cout << "Loans change" << ch << endl;
    loans_ += ch;
    change_assets(-ch);
}

void Bank::change_payback_time(double ch) {
    payback_time_ += ch;
}

void Bank::update_assets() {
    //cout << "update assets" << endl;
    //assets_ = deposits_ - loans_;
}

double Bank::pay_dividends() {
    
    double dividends = 0;
    double safety_amount = 0;
    
    cout << "I bank pay_dividends, unchecked changes here and in get_sum_to_borrow. Change interest had min of 0" << endl;
    
    //Safety amount
    safety_amount = loans_*safety_;
    
    
    
    
    if(deposits_ < loans_) {
        
        //dividends = fmax(0, assets_ - safety_amount) * div_ratio_;
        dividends = assets_ * div_ratio_;
    }
    else {
        
        dividends = 0;
    }
    
    assets_ -= dividends;
    
    return dividends;
    
}
