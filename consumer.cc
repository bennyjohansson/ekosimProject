#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>

#include "functions.h"
#include "SQLfunctions.h"
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
employed_(false),
name_(""),
global_market_(nullptr),
enable_intercity_trading_(false)
//city_(0)
{}

Consumer::Consumer(double mot, double sk, double cap, double spe) :
motivation_(mot),
skill_(sk),
spendwill_(spe),
employed_(false),
capital_(cap),
income_(0),
items_(0),
name_(""),
global_market_(nullptr),
enable_intercity_trading_(false)
{}

Consumer::Consumer(double mot, double sk, double cap, double spe, double save, double borrow, string country, Market * m, Bank *b, Clock * c) :
name_(""), 
country_(country),
motivation_(mot),
skill_(sk),
capital_(cap),
spendwill_(spe),
savewill_(save),
borrowwill_(borrow),
items_(0),
loans_(0), 
debts_(0),
income_(0),
dividends_(0),
transfers_(0),
employed_(false),
trustworthy_(true),
bank_(b),
clock_(c),
market_(m),
global_market_(nullptr),
enable_intercity_trading_(false),
employer_ ("")

{}

Consumer::Consumer(double mot, double sk, double cap, double spe, double save, double borrow, string country, Market * m, Market * global_m, Bank *b, Clock * c) :
name_(""), 
country_(country),
motivation_(mot),
skill_(sk),
capital_(cap),
spendwill_(spe),
savewill_(save),
borrowwill_(borrow),
items_(0),
loans_(0), 
debts_(0),
income_(0),
dividends_(0),
transfers_(0),
employed_(false),
trustworthy_(true),
bank_(b),
clock_(c),
market_(m),
global_market_(global_m),
enable_intercity_trading_(false),
employer_ ("")

{}

/*
 * Info functions
 */

void Consumer::info() {

    cout << "Name: " << name_ << endl;
    
    cout << "Motivation: " << get_motivation() << endl;
    cout << "Skill: " <<  get_skill() << endl;
    cout << "Capital: " << get_capital() << endl;
    cout << "Spendwill: " << get_spendwill() << endl;
    cout << "Employed: ";
    
    if (employed_) {
        cout << "yes" << endl;
    }
    else {
        cout << "no" << endl;
    }
    
    cout << "Money: " << capital_ << endl;
    cout << "Items: " << items_ << endl; 
    
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

string Consumer::get_country() const{
    return country_;
}

double Consumer::get_motivation() const{
    return motivation_;
}

double Consumer::get_skill() const{
    return skill_;
}
double Consumer::get_capital() const{
    return capital_;
}
double Consumer::get_spendwill() const{
    return spendwill_;
}

double Consumer::get_savewill() const{
    return savewill_;
}

double Consumer::get_borrowwill() const{
    return borrowwill_;
}


double Consumer::get_income() const {
    return income_;
}

double Consumer::get_dividends() const {
    return dividends_;
}

double Consumer::get_transfers() const {
    return transfers_;
}

bool Consumer::get_employment_status() const {
    return employed_;
}

bool Consumer::get_trustworthy() const {
    return trustworthy_;
}

double Consumer::get_items() const {
    return items_;
}

double Consumer::get_loans() const {
    return loans_;
}

double Consumer::get_debts() const {
    return debts_;
}

string Consumer::get_name() const {
	return name_;
}

string Consumer::get_employer() const {
	return employer_;
}

Market * Consumer::get_active_market() {

    if (enable_intercity_trading_) {
        if (global_market_ != nullptr) {
            return global_market_;
        } else {
            // This should never happen in normal operation since global_market_ is initialized
            cout << "ERROR: Global market is null in consumer but intercity trading is enabled!" << endl;
            return market_;
        }
    }
    else {
        return market_;
    }
}

Bank * Consumer::get_bank() {
    return bank_;
}

bool Consumer::get_enable_intercity_trading() const {
    return enable_intercity_trading_;
}

double Consumer::get_time() {

	return clock_ -> get_time();
} 

double Consumer::get_desired_deposit() {
    double amount = 0;
    double interest = 0;
    
    interest = bank_ -> get_interest();
    
    
    amount = get_consumer_deposit(savewill_, capital_, interest);
    
    
    return amount;
}

double Consumer::get_desired_borrow() {
    double amount = 0;
    double interest = 0;
    double available_capital = 0;
    double assets = 0;
    double total_income = dividends_ + income_ + transfers_;

    assets = loans_ + capital_;
    
    interest = bank_ -> get_interest();
    available_capital = bank_ -> get_sum_to_borrow();
    
    amount = get_consumer_borrow(borrowwill_, assets, loans_, debts_, interest, total_income);
    
    if(amount > available_capital && available_capital > 0) {
        amount = available_capital;
        cout << "In consumer, not enough money to borrow" << endl;
    }
    else if (available_capital < 0) {
        amount = 0;
    }
    
    //cout << "Efterat i consumer get_desired_borrow: " << available_capital << "  Desired borrow: " << amount << endl;
    
    return amount;
}

double Consumer::get_borrow() {
    double amount = 0;
    double interest = 0;
    double available_capital = 0;
    
    interest = bank_ -> get_interest();
    available_capital = bank_ -> get_max_customer_borrow();//get_assets();
    
    amount = get_desired_borrow(); //borrowwill_*capital_/(0.3+interest);
    
    //  cout << "I consumer get_desired_borrow: " << available_capital << "  Desired borrow: " << amount << endl;
    
    if(amount > available_capital && available_capital > 0) {
        amount = available_capital;
        //    cout << "In consumer, not enough money in bank to borrow" << endl;
    }
    else if (available_capital < 0) {
        amount = 0;
    }
    
    //cout << "Efterat i consumer get_desired_borrow: " << available_capital << "  Desired borrow: " << amount << endl;
    
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

void Consumer::set_dividends(double dividends) {
    dividends_ = dividends;
}

void Consumer::set_transfers(double transfers) {
    transfers_ = transfers;
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

void Consumer::set_name(string name) {
    name_ = name;
}

void Consumer::set_employer(string employer) {
    employer_ = employer;
}

void Consumer::set_trustworthy(bool tw) {
    trustworthy_ = tw;
}

void Consumer::set_market(Market *newMarket) {

    market_ = newMarket;
}

void Consumer::set_enable_intercity_trading(bool enable) {
    enable_intercity_trading_ = enable;
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

void Consumer::update_values(double spendwill, double borrowwill) {
    // update_capital(); 
    update_skill();
    update_spendwill(spendwill);
    update_borrowwill(borrowwill);
    //update_motivation();
}

void Consumer::update_skill() {
    //int skill_change;
    //double EMP_CONST = 0.05;
    
    //bool emp = get_employment_status();
    //if(emp) {
    //  skill_ *= (1 + EMP_CONST);
    //}
    //else {
    //  skill_ *= (1 - EMP_CONST);
    // }
    
    //double time = clock_ -> get_time();
    //  if(time == 330) {
    //  skill_ = 1.15*skill_;
    //}
    
    //if(time == 360) {
    //  skill_ = 0.9*skill_;
    //}
    //randomize(skill_, 0.1);
    normalize(skill_);
}


void Consumer::update_spendwill(double spendwill) {
    
    //spendwill_ = spendwill_ + 1*sum;
    
    /*
     * Trying the stem response on a change in demand, should not
     * be made here though, need to collect that somewhere else. 
     * Maybe we should make a "calander" class with events...
     */
    
    spendwill_ = randnorm(spendwill, 1);
    //randomize(spendwill_, spendwill);
    //normalize(spendwill_);
}

void Consumer::update_borrowwill(double borrowwill) {
    
    //spendwill_ = spendwill_ + 1*sum;
    
    /*
     * Trying the stem response on a change in demand, should not
     * be made here though, need to collect that somewhere else. 
     * Maybe we should make a "calander" class with events...
     */
    
    borrowwill_ = randnorm(borrowwill, 1);
    //cout << " i consumer update borrowwill " << borrowwill_ << " avg: " << borrowwill << endl;
    //randomize(borrowwill_, borrowwill);
    //normalize(borrowwill_);
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
    motivation_ = randnorm(motivation_, 1);
}

double Consumer::get_demand() {

	double demand_cash = 0;
	double demand_bank = 0;
	double demand_total = 0;
	double interest = 0;
	
	interest = bank_ -> get_interest();

	demand_bank = fmin(get_consumer_demand_deposit(spendwill_, loans_, interest), bank_ -> get_max_customer_borrow());
	demand_cash = get_consumer_demand_cash(spendwill_, capital_);
	
	demand_total = demand_bank + demand_cash;
	
	// Only log if there are unusual demand patterns
	if(get_time() >= 12 && (demand_cash < 0 || demand_bank < 0 || demand_total < 0)) {
	    cout << "CONSUMER DEMAND ISSUE [" << name_ << " @ time " << get_time() << "]: Negative demand detected!" << endl;
	    cout << "  cash=" << demand_cash << ", bank=" << demand_bank << ", total=" << demand_total << endl;
	    cout << "  spendwill=" << spendwill_ << ", capital=" << capital_ << ", loans=" << loans_ << ", interest=" << interest << endl;
	}
	
	return demand_total;
	
}


double Consumer::buy() {
    
    double amount_cash = 0;
    double amount_bank = 0;
    double total_amount = 0;
    double interest = 0;
    double actual_amount = 0;
    double price = 0;
    int desired_items = 0;
    int actual_items = 0;
    
    int max_items = 0;
    
    // Store initial state for leakage detection
    double initial_capital = capital_;
    double initial_loans = loans_;
    double initial_items = items_;
    
    price = get_active_market() -> get_price_out();
    max_items = get_active_market() -> get_items();
    interest = bank_ -> get_interest();
    
    
    //Desired amount to purchase
	amount_bank = fmin(get_consumer_demand_deposit(spendwill_, loans_, interest), bank_ -> get_max_customer_borrow());
	amount_cash = get_consumer_demand_cash(spendwill_, capital_);
	total_amount = amount_bank + amount_cash;
	
   	desired_items = fmax(0, total_amount/price);
   	
   	//Actual amount purchased
   	actual_items = get_active_market() -> customer_buy_items(total_amount);
   	actual_amount = actual_items*price;
   	
   	
   	if(actual_amount < amount_cash) {
   		double old_amount_cash = amount_cash;
   		double old_amount_bank = amount_bank;
   		amount_cash = actual_amount;
   		amount_bank = 0;
   	}
   	else {
   		double old_amount_bank = amount_bank;
   		amount_bank = fmax(actual_amount - amount_cash, 0);
   		
   	}
   	
   	//Changing inventory and money
    items_ += actual_items;
   
    /*
     * Have to check if the market has got enough intems to sell 
     */
    //cout << "I cons buy Amount cash: " << amount_cash << " Amount bank: " << amount_bank << " Total amount: " << actual_amount << endl;

    
    // Store pre-transaction values for validation
    double pre_capital = capital_;
    double pre_loans = loans_;
    
    // First, reduce capital (this is always exact)
    change_capital(-amount_cash);
    
    // Then, try to withdraw from bank and adjust loans based on actual withdrawal
    double actual_withdrawal = bank_ -> customer_withdraw_money(amount_bank);
    change_loans(-actual_withdrawal);  // Use actual withdrawal amount, not requested
    
    
    // Final money conservation check - only log if there are leakages
    double capital_change = capital_ - initial_capital;
    double loans_change = loans_ - initial_loans;
    double items_change = items_ - initial_items;
    double total_money_change = capital_change + loans_change;
    double expected_money_change = -(amount_cash + actual_withdrawal);  // Use actual withdrawal
    
    // Check for money leakage
    bool money_leakage = std::abs(total_money_change - expected_money_change) > 0.01;
    bool items_leakage = std::abs(items_change - actual_items) > 0.01;
    
    log_transaction_full(name_, "Market", actual_amount, "Purchase", get_time());
    log_transaction(name_, actual_amount, "Purchase", get_time());
    log_transaction(name_, amount_bank, "Deposit", get_time());
    
    
    return actual_amount;
}

// double Consumer::buy() {
//     
//     double amount_cash = 0;
//     double amount_bank = 0;
//     double total_amount = 0;
//     double price = 0;
//     double quantity = 0;
//     
//     int max_items = 0;
//     
//     price = market_ -> get_price_out();
//     max_items = market_ -> get_items();
//     
//     if (capital_ > 0) {
//         amount_cash = capital_ * spendwill_;
//         amount_bank = loans_ * spendwill_;
//         total_amount = amount_bank + amount_cash;
//    		 quantity = fmax(0, fmin(total_amount/price, max_items));
//     }
//     
//    
//     /*
//      * Have to check if the market has got enough intems to sell 
//      */
//     
//     if (max_items > quantity && total_amount > 0) {
//         
//         items_ += quantity;
//         market_ -> change_capital(total_amount);
//         market_ -> change_items(-quantity);
//         
//         change_capital(-amount_cash);
//         change_loans(-amount_bank);
//         bank_ -> customer_withdraw_money(amount_bank);
//         
//         log_transaction_full(name_, "Market", total_amount, "Purchase", get_time());
//         log_transaction(name_, total_amount, "Purchase", get_time());
//         log_transaction(name_, amount_bank, "Deposit", get_time());
//         
//     }
//     
//     
//     return total_amount;
// }


void Consumer::deposit_and_borrow_from_bank() {
    
    if(trustworthy_ && bank_ -> get_trustworthy()) {
        double sum_to_deposit = 0;
        double sum_to_borrow = 0;
        double max_sum_to_borrow = 0;
        
        
        //Loand = depostit
        sum_to_deposit = get_desired_deposit();
        
        change_loans(sum_to_deposit);
        change_capital(-sum_to_deposit);
        bank_ -> customer_deposit_money(sum_to_deposit);
        
        
        
        //Borrow
        sum_to_borrow = get_desired_borrow();
        
        max_sum_to_borrow = bank_ -> customer_borrow_money(sum_to_borrow);
        
        change_capital(max_sum_to_borrow);
        change_debts(max_sum_to_borrow);
        //cout << "I cons dep & bor, des bor: " << sum_to_borrow << " max sum: " << max_sum_to_borrow << endl;
        
        
        log_transaction_full(name_, "Bank", sum_to_deposit, "Deposit", get_time());
        log_transaction_full(name_, "Bank", max_sum_to_borrow, "Loan", get_time());
    }
    
    
    
}

void Consumer::deposit_to_bank() {

	bool trustworthy = 1;
	//trustworthy = bank_ -> get_trustworthy();
	
    if(trustworthy_ && trustworthy) {
        double amount = 0;
        
        amount = get_desired_deposit();
        
        change_capital(-amount);
        change_loans(amount);
        bank_ -> customer_deposit_money(amount);
        
      
    }
}

double Consumer::accept_deposit(double amount) {
	
	double sum = 0;
	
	sum = fmax(amount, 0);
	
    change_loans(amount);
    bank_ -> customer_deposit_money(amount);
	
	
	return amount;

}


void Consumer::borrow_from_bank() {
    
    bool trustworthy = 1;
    trustworthy = bank_ -> get_trustworthy();
    
    if(!employed_) {
        trustworthy_ = false;
    }
    
    
    if(trustworthy_ && trustworthy) {
        double amount = 0;
        
        amount = get_borrow();
        
        change_capital(amount);
        change_debts(amount);
        bank_ -> customer_borrow_money(amount);
    }
}

void Consumer::repay_to_bank() {

	double repayment = 0;
    double max_amount = 0;
    double withdrawal = 0;
	
	max_amount = fmax(capital_,0) + fmax(loans_, 0);
    
    repayment = bank_ -> customer_repay_loans(fmax(debts_,0), max_amount, 1);

    if(repayment < 0) {
        cout << "Repayment: " << repayment << " is negative in consumer.cc repay to bank, this should not happen!" << endl;
    }
    
    //If repayment is max amount most likely the consumer ca't pay the full amount
    if(repayment == max_amount && debts_ > 0) {
    	set_trustworthy(false);
    }
    else {
    	set_trustworthy(true);
    }
    //If the customer has enough money on the account to repay debts, doing so
    if(repayment <= loans_ && repayment != 0) {
    	
    	//Withdrawal to repay
    	withdrawal = bank_ -> customer_withdraw_money(repayment);
    	change_loans(-withdrawal);
    	
    	//Repayment done
        change_debts(-withdrawal);
        
    }
    else if (repayment != 0) {
    
    	//Withdraw all deposits to repay, the rest in from cash

        withdrawal = bank_ -> customer_withdraw_money(loans_);        
        change_loans(-withdrawal);
        
        //Withdraw rest from cash
        change_capital(-(repayment - withdrawal));
        
        //Repayment done
        change_debts(-repayment);
        cout << "I cons pay interest, need both cash and deposits to repay loans: " << loans_ << " withdrawal: " << withdrawal << " repayment: " << repayment << endl;

    }
    
 
        //change_capital(-amount);
        //change_debts(-amount);
        //bank_ -> change_assets(amount);        
        log_transaction_full(name_, "Bank", repayment, "Amortization", get_time());
}

void Consumer::get_repayment_from_bank() {
    double amount = 0;
    double max_amount = 0;
    double payback_time = 0;
    
    if(trustworthy_) {
        payback_time = bank_ -> get_payback_time();
        amount = loans_/(payback_time*12);
        
        if(amount > bank_ -> get_capital()) {
            amount = bank_ -> get_capital();
            //bank_ -> set_trustworthy(false);
            //	cout << "Not enough money in bank to repay to cvonsumer (in consumer get repayment)" << endl;
        }
        else {
            bank_ -> set_trustworthy(true);
        }
        
        max_amount = bank_ -> customer_withdraw_money(amount);
        change_capital(amount);
        change_loans(-amount);
        
        log_transaction_full("Bank", name_, amount, "Amortization", get_time());
        
        //bank_ -> change_assets(-amount);
    }
}

double Consumer::get_interest() {
    double interest = 0;
    double max_customer_amount = 0;
    double deposits = 0;
    
    max_customer_amount = fmax(capital_ + loans_, 0);
    
    
    //Max customer amount here can be wrong in some cases
    
    interest =  bank_ -> customer_get_interest(loans_, max_customer_amount, 1);
    
    bank_ -> customer_deposit_money(interest);        
    change_loans(interest);
    
    log_transaction_full("Bank", name_, interest, "Interest", get_time());
        
    return interest;
    
}


double Consumer::pay_interest() {

	//double amount_available = 0;
	double interest = 0;
    double max_amount = 0;
    double withdrawal = 0;
	
	max_amount = fmax(capital_ + loans_, 0);
    
    interest = bank_ -> customer_pay_interest(debts_, max_amount, 1);
    
    //cout << "I cons pay interest: " << interest << " loans: " << loans_ << " capital: " << capital_ << " max_amount: " << max_amount << endl;
    
    
    //If interest is max amount most likely the consumer ca't pay the full amount
    if(interest == max_amount && debts_ > 0) {
    	set_trustworthy(false);
    }
    else {
    	set_trustworthy(true);
    }
    
    if(interest <= loans_ && interest != 0) {
    	withdrawal = bank_ -> customer_withdraw_money(interest);
        change_loans(-withdrawal);
    }
    else if (interest != 0) {
    	withdrawal = bank_ -> customer_withdraw_money(loans_);
        change_loans(-withdrawal);
        change_capital(-(interest - withdrawal));
        //cout << "I cons pay interest, need both cash and deposits to repay interest: " << interest << " withdrawal: " << withdrawal << -withdrawal - (interest - withdrawal) << endl;
    }
    
    log_transaction_full(name_, "Bank", interest, "Interest", get_time());
    
    return interest;
        //bank_ -> customer_pay_interest(amount_available);
        
        
}

double Consumer::get_expected_net_flow_to_bank() {
    
    double loans_from_bank = 0;
    double loans_to_bank = 0;
    double repayment_to_bank = 0;
    double repayment_from_bank = 0;
    double interest_to_bank = 0;
    double interest_from_bank = 0;
    double interest = 0;
    double sum = 0;
    int payback_time = 0;
    bool trustworthy = 1;
	
	//trustworthy = bank_ -> get_trustworthy()
    
    payback_time = bank_ -> get_payback_time();
    interest = bank_ -> get_interest();
    
    
    if(trustworthy) {
        repayment_to_bank = debts_/(payback_time*12);
        interest_to_bank = interest*debts_;
    }
    
    if(trustworthy) {
        repayment_from_bank = loans_/(payback_time*12);
        interest_from_bank = interest*loans_;
        
        loans_from_bank = get_desired_borrow();
        loans_to_bank = get_desired_deposit();
    }
    
    //cout << "Cons net flow rtb: " << repayment_to_bank << " rfb: " <<  repayment_from_bank << "itb: " <<  interest_to_bank << "ifb: " <<  interest_from_bank << "ltb: " <<  loans_to_bank << "lfb: " <<  loans_from_bank << " b tw: " << bank_ -> get_trustworthy() << endl;
    sum = repayment_to_bank - repayment_from_bank + interest_to_bank - interest_from_bank + loans_to_bank - loans_from_bank;
    
    return sum;
}

void Consumer::save_to_database() {


    std::vector<double> consumer_data;
    int time_stamp = 0;
    time_stamp = clock_ -> get_time();

    consumer_data.push_back((double)items_);
    consumer_data.push_back((double)capital_);
    consumer_data.push_back((double)loans_);
    consumer_data.push_back((double)debts_);
    consumer_data.push_back((double)skill_);
    consumer_data.push_back((double)motivation_);
    consumer_data.push_back((double)spendwill_);
    consumer_data.push_back((double)savewill_);
    consumer_data.push_back((double)borrowwill_);
    consumer_data.push_back((double)income_);
    consumer_data.push_back((double)dividends_);
    consumer_data.push_back((double)transfers_);
    //cout << "I company save time database " << current_production_items_ << endl;
    //company_data.push_back((double)prod_const_motivation_);


    insertConsumerData(consumer_data, country_, name_, employer_);


}
