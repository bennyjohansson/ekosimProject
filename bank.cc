#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <cmath>

#include "bank.h"

using namespace std;

Bank::Bank() :
name_(""),
interest_rate_(0),
capital_(0),
deposits_(0),
div_ratio_(0)
{}

Bank::Bank(string name, double interest, int payback_time) :
name_(name),
interest_rate_(interest),
interest_margin_(0.005),
target_interest_(0.04),
interest_rate_method_(1),
capital_(10000000),
deposits_(0),
loans_(0),
liquidity_(10000000), 
capital_reserve_ratio_(0.2),
liquidity_reserve_ratio_(1),
trustworthy_(true),
payback_time_(payback_time),
div_ratio_(0.3)
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

double Bank::get_interest_margin() {
	
	return interest_margin_;
}


double Bank::get_interest_rate_deposits() {

	return interest_rate_ - interest_margin_/2;

}


double Bank::get_interest_rate_loans() {

	return interest_rate_ + interest_margin_/2;


}



double Bank::get_target_interest() {
    return target_interest_;
}

int Bank::get_interest_rate_method() {
    return interest_rate_method_;
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
    safety_amount = loans_*capital_reserve_ratio_;
    
    if(safety_amount > liquidity_ && liquidity_ > 0) {
        //safety_amount = liquidity_;
        sum = liquidity_ - safety_amount;
        //sum = safety_amount - capital_;
    }
    else if (liquidity_ <= 0){
        sum = -liquidity_;
    }
    
    return sum;
}

double Bank::get_max_customer_borrow() {
    double safety_amount = 0;
    double sum = 0;
    
    //cout << "I bank get_sum_to_borrow, unchecked changes" << endl;
    safety_amount = loans_*capital_reserve_ratio_;
        
    if(capital_ > safety_amount && capital_ > 0) {
        sum = capital_ - safety_amount;
    }
    else {
        sum = 0;
    }
    
    sum = fmax(fmin(liquidity_, sum), 0);
    
    return sum;
}



double Bank::get_dividend_ratio() {
    return div_ratio_;
}

double Bank::get_liquidity_reserve_ratio() {
    return liquidity_reserve_ratio_;
}

double Bank::get_capital_reserve_ratio() {
    return capital_reserve_ratio_;
}


bool Bank::get_trustworthy() {
    return trustworthy_;
}

void Bank::set_interest(double interest) {
    interest_rate_ = interest;
}

void Bank::set_interest_margin(double interest_margin) {
	interest_margin_ = interest_margin;
}

void Bank::set_target_interest(double target_interest) {
    target_interest_ = target_interest;
}

void Bank::set_interest_rate_method(double method) {
    interest_rate_method_ = method;
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

void Bank::set_dividend_ratio(double dr) {
    div_ratio_ = dr;
}

void Bank::set_liquidity_reserve_ratio(double rr) {
    liquidity_reserve_ratio_ = rr;
}

void Bank::set_capital_reserve_ratio(double rr) {
    capital_reserve_ratio_ = rr;
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
    
    if(capital_ < 0) {
    	cout << "I bank capital, capital < 0, changed with: " << ch << " to: " << capital_ << endl;
	}
}

void Bank::change_liquidity(double ch) {
    liquidity_ += ch;
    
    if(liquidity_ < 0) {
    	cout << "I bank liquidity, liquidity < 0, changed with: " << ch << " to: " << liquidity_ << endl;
	}
}

void Bank::change_deposits(double ch) {
    //cout << "deposits" << endl;
    deposits_ += ch;
    if(deposits_ < 0) {
    	cout << "I bank deposits, deposits < 0, changed with: " << ch << " to: " << deposits_ << endl;
	}
    //change_liquidity(ch);
}

void Bank::change_loans(double ch) {
    //cout << "Loans change" << ch << endl;
    loans_ += ch;
    if(loans_ < 0) {
    	cout << "I bank loans, loans < 0, changed with: " << ch << " to: " << loans_ << endl;
	}
    //change_liquidity(-ch);
}

void Bank::change_payback_time(double ch) {
    payback_time_ += ch;
}

void Bank::change_dividend_ratio(double ch) {
    div_ratio_ += ch;
}

void Bank::change_liquidity_reserve_ratio(double ch) {
    liquidity_reserve_ratio_ += ch;
}

void Bank::change_capital_reserve_ratio(double ch) {
    capital_reserve_ratio_ += ch;
}


void Bank::customer_deposit_money(double ch) {

	//deposits_ +=  ch;
	//liquidity_ += ch;
	change_deposits(ch);
	change_liquidity(ch);
	
	if(deposits_ < 0) {
		cout << "I bank cust deposit, depo: " << ch << " deposits: " << deposits_ << endl;
	}

}

double Bank::customer_withdraw_money(double ch) {

	double sum = 0; 
	double max_amount = 0;
	

	// if(deposits_ > ch) {
// 		sum = ch;
// 		
// 	}
// 	else {
// 		sum = 0;
// 	}
	
	 max_amount = get_max_customer_borrow();
    
    //safety_amount = loans_*safety_;
    
    sum = fmin(max_amount, ch);
	
	change_deposits(-sum);
	change_liquidity(-sum);
	
	if(deposits_ < 0) {
		cout << "I bank cust withdraw, depo: " << ch << " deposits: " << deposits_ << endl;
	}
	if(ch < 0) {
		cout << "I bank customer withdraw money, withdrawal < 0: " << ch << endl;
	
	}
	
	return sum;
}


double Bank::customer_borrow_money(double borrow_amount) {

	double max_amount = 0;
    double sum = 0;
    
    max_amount = get_max_customer_borrow();
    
    //safety_amount = loans_*safety_;
    
    sum = fmax(fmin(max_amount, borrow_amount),0);
     
    //loans_ += sum;
    //liquidity_ -= sum;
    change_loans(sum);
	change_liquidity(-sum);
    
    //cout << "I bank cust bor, amount: " << sum << " des amount " << borrow_amount << endl;


	return sum;
}

double Bank::customer_repay_loans(double loans, double max_customer_amount, bool pay) {

	double max_bank_amount = 0;
    double sum = 0;
    double repayment = 0;
    
    repayment = loans/(payback_time_*12);
	max_bank_amount = get_max_customer_borrow();
	
    sum = fmax(fmin(repayment, max_customer_amount), -max_bank_amount); 


	if(pay && sum != 0){
		change_loans(-sum);
		change_liquidity(sum);
	}

	return sum;

}

double Bank::customer_get_interest(double deposits, double max_customer_amount, bool pay) {

	double max_bank_amount = 0;
    double sum = 0;
    double interest = 0;
    
    
    interest = deposits * get_interest_rate_deposits();
	max_bank_amount = get_max_customer_borrow();
	
    sum = fmax(fmin(interest, max_bank_amount), -max_customer_amount);
    
   
	if(pay && sum != 0){
		change_capital(-sum);
		change_liquidity(-sum);
	}

	return sum;

	

}

double Bank::customer_pay_interest(double loans, double max_customer_amount, bool pay) {

	double max_bank_amount = 0;
    double sum = 0;
    double interest = 0;
    
    interest = loans * get_interest_rate_loans();
	max_bank_amount = get_max_customer_borrow();
    sum = fmax(fmin(interest, max_customer_amount), -max_bank_amount); 
    
	if(pay && sum != 0){ 
		change_capital(sum);
		change_liquidity(sum);
	}

	return sum;

}


double Bank::pay_dividends() {
    
    double dividends = 0;
    double safety_amount = 0;
    double buffer = 0.1;
    
    //cout << "I bank pay_dividends, unchecked changes here and in get_sum_to_borrow. Change interest had min of 0" << endl;
    //cout << "And assets, loans and deposits are wrong, needs to be fixed" << endl;
    
    //Safety amount
    safety_amount = loans_*capital_reserve_ratio_ *(1+buffer);
    

        
    dividends = fmax(0, fmin(liquidity_ - safety_amount, capital_ - safety_amount)) * div_ratio_;
        //dividends = capital_ * div_ratio_;
    //}
    //else {
        
    //    dividends = 0;
    //}
    change_capital(-dividends);
	change_liquidity(-dividends);
    //capital_ -= dividends;
    //liquidity_ -=dividends;
    
    return dividends;
    
}
