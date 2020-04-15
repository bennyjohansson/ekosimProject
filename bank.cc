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
capital_(0),
div_ratio_(0)
{}

Bank::Bank(string name, double interest, int payback_time) :
name_(name),
interest_rate_(interest),
capital_(0),
deposits_(0),
loans_(0),
liquidity_(0), 
safety_(0.4),
trustworthy_(true),
payback_time_(payback_time),
div_ratio_(0.05)
{}

/*
 * Info-functions
 */

void Bank::info() {
    
    cout << "BANK: " << name_ << endl << "--------------------------" << endl
    << "Iterest rate: " << interest_rate_ << endl
    << "capital: " << capital_ << endl
    << "deposits: " << deposits_ << endl
    << "Loans: " << loans_ << endl;
    
}

double Bank::get_interest() {
    return interest_rate_;
}

double Bank::get_capital() {
    return capital_;
}

double Bank::get_deposits() {
    return deposits_;
}

double Bank::get_loans() {
    return loans_;
}

double Bank::get_liquidity() {
    return liquidity_;
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
    
    if(safety_amount > capital_ && capital_ > 0) {
        safety_amount = capital_;
        sum = capital_ - safety_amount;
        //sum = safety_amount - capital_;
    }
    else if (capital_ <= 0){
        sum = -capital_;
    }
    
    return sum;
}

double Bank::get_max_customer_borrow() {
    double safety_amount = 0;
    double sum = 0;
    
    
    //cout << "I bank get_sum_to_borrow, unchecked changes" << endl;
    safety_amount = loans_*safety_;
    
    if(capital_ > safety_amount && capital_ > 0) {
        sum = capital_ - safety_amount;
    }
    else {
        sum = 0;
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

void Bank::set_capital(double capital) {
    capital_ = capital;
}

void Bank::set_deposits(double deposits) {
    deposits_ = deposits;
    //update_capital();
}

void Bank::set_loans(double loans) {
    loans_ = loans;
    //update_capital();
}

void Bank::set_liquidity(double liquidity) {
    loans_ = liquidity;
    //update_capital();
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

void Bank::change_capital(double ch) {
    //  cout << "capital" << endl;
    capital_ += ch;
}

void Bank::change_liquidity(double ch) {
    //  cout << "capital" << endl;
    liquidity_ += ch;
}

void Bank::change_deposits(double ch) {
    //cout << "deposits" << endl;
    deposits_ += ch;
    change_liquidity(ch);
}

void Bank::change_loans(double ch) {
    //cout << "Loans change" << ch << endl;
    loans_ += ch;
    change_liquidity(-ch);
}

void Bank::change_payback_time(double ch) {
    payback_time_ += ch;
}


void Bank::customer_deposit_money(double ch) {

	deposits_ +=  ch;
	liquidity_ += ch;

}

double Bank::customer_withdraw_money(double ch) {

	double sum = 0; 

	if(deposits_ > ch) {
		sum = ch;
		
	}
	else {
		sum = 0;
	}
	
	deposits_ -=  sum;
	liquidity_ -= sum;
	
	return sum;
}


double Bank::customer_borrow_money(double borrow_amount) {

	double max_amount = 0;
    double sum = 0;
    
    max_amount = get_max_customer_borrow();
    
    //safety_amount = loans_*safety_;
    
    sum = fmax(fmin(max_amount, borrow_amount),0);
     
    loans_ += sum;
    liquidity_ -= sum;
    
    //cout << "I bank cust bor, amount: " << sum << " des amount " << borrow_amount << endl;


	return sum;
}

void Bank::customer_repay_loans(double ch) {


	loans_ -=  ch;
	liquidity_ += ch;


}

double Bank::customer_get_interest(double interest) {

	double max_amount = 0;
    double sum = 0;
    
    max_amount = get_max_customer_borrow();
    
    //safety_amount = loans_*safety_;
    
    sum = fmin(max_amount, interest);
    
    //
    // if(capital_ -  interest > safety_amount && capital_ > 0) {
//         sum = interest;
//     
//     }
//     else {
//         sum = 0;
//     }


	capital_ -=  sum;
	liquidity_ -= sum;

	return sum;

	

}

void Bank::customer_pay_interest(double interest) {

	capital_ +=  interest;
	liquidity_ += interest;


}


double Bank::pay_dividends() {
    
    double dividends = 0;
    double safety_amount = 0;
    
    cout << "I bank pay_dividends, unchecked changes here and in get_sum_to_borrow. Change interest had min of 0" << endl;
    cout << "And assets, loans and deposits are wrong, needs to be fixed" << endl;
    
    //Safety amount
    safety_amount = loans_*safety_;
    
    
    
    
    //if(deposits_ < loans_) {
        
    dividends = fmax(0, fmin(liquidity_, capital_ - safety_amount)) * div_ratio_;
        //dividends = capital_ * div_ratio_;
    //}
    //else {
        
    //    dividends = 0;
    //}
    
    capital_ -= dividends;
    
    return dividends;
    
}
