#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <cmath>

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
market_(new Market()),
bank_(new Bank("BENNYBANK", 0.02, 3)),
clock_(new Clock())
{}

City::City(string name) :
name_(name),
consumers_(new Consumer_list("CONSUMERS")),
company_list_(new Company_list("COMPANIES")),
labour_market_(new Consumer_list("LABOUR MARKET")),
market_(new Market()),
bank_(new Bank("BENNYBANK", 0.05, 3)),
clock_(new Clock()),
flash_counter_(0)
{}


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

void City::employee_info(string command) {
    company_list_ -> employee_info(command);
}

void City::market_info() {
    market_ -> info();
}

void City::bank_info() {
    bank_ -> info();
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

void City::print_GDP() {
    
    const int SPACE = 15;
    
    list <double>::iterator GDP;
    list <double>::iterator Growth;
    list <double>::iterator Investments;
    list <double>::iterator Demand;
    list <double>::iterator Price_out;
    list <double>::iterator Employed;
    list <double>::iterator Wages;
    list <double>::iterator Time;
    list <double>::iterator Consumer_capital;
    list <double>::iterator Company_capital;
    list <double>::iterator Market_capital;
    list <double>::iterator Bank_capital;
    list <double>::iterator Total_capital;
    
    list <double>::iterator Interest_rate;
    
    GDP = GDP_.begin();
    Time = time_.begin();
    Growth = growth_.begin();
    Investments = investments_.begin();
    Demand = demand_.begin();
    Wages = (company_list_ -> get_company("bempa_AB"))->wages_.begin();
    Price_out = price_out_.begin();
    Employed = employed_.begin();
    Consumer_capital = consumer_capital_.begin();
    Company_capital = company_capital_.begin();
    Market_capital = market_capital_.begin();
    Bank_capital = bank_capital_.begin();
    Total_capital = total_capital_.begin();
    Interest_rate = interest_rate_.begin();
    
    /*
     * Printing output to screen
     */
    cout << "Bennyland"
	<< endl << "-----------------------------------------------------" << endl 
	<< setw(SPACE - 10) << "Time" << setw(SPACE-1) << "GDP" << setw(SPACE-2) << "Growth" << setw(SPACE) << "Demand" 
	<< setw(SPACE) << "Wages" << setw(SPACE) << "Price out" << setw(SPACE) << "Employed"
	<< setw(SPACE + 4) << "Consumer_capital" << setw(SPACE + 4) << "Company_cap" << setw(SPACE) << "Invested cap" 
	<< setw(SPACE) <<  "Bank cap" << endl;
    
    for (GDP; GDP != GDP_.end(); GDP++) {
        
        cout << setw(SPACE - 10) << *Time << setw(SPACE-1) << *GDP << setw(SPACE-2) << *Growth << setw(SPACE) 
        << *Demand << setw(SPACE) << *Wages << setw(SPACE) 
        << *Price_out << setw(SPACE) << *Employed << setw(SPACE + 4)
        << *Consumer_capital << setw(SPACE + 4) << *Company_capital << setw(SPACE) 
        << *Investments << setw(SPACE) << *Bank_capital << endl;
        
        Time++;
        Demand++;
        Growth++;
        Wages++;
        Price_out++;
        Employed++;
        Consumer_capital++;
        Company_capital++;
        Investments++;  
        Bank_capital++;
    }
    
    
    /*
     * Printing to file gdp.txt
     */
    ofstream file ("gdp.txt");
    GDP = GDP_.begin();  
    Time = time_.begin();
    Investments = investments_.begin();
    Growth = growth_.begin();
    Demand = demand_.begin();
    Wages = (company_list_ -> get_company("bempa_AB"))->wages_.begin();
    Price_out = price_out_.begin();
    Employed = employed_.begin();
    Interest_rate = interest_rate_.begin();
    Market_capital = market_capital_.begin();
    Bank_capital = bank_capital_.begin();
    Total_capital = total_capital_.begin();
    Interest_rate = interest_rate_.begin();
    
    file << "#time1 gdp2 growth3 demand4 wages5 price6 employed7 company_capital8 consumer_capital9 interest_rate10 investments11 market_capital12 bank_capital13 total_capital14" << endl;
    for (GDP = GDP_.begin(); GDP != GDP_.end(); GDP++) {
        file << *Time << " " << *GDP << " " << *Growth << " " << *Demand 
        << " " << *Wages << " " << *Price_out << " " << *Employed
        << " " << *Consumer_capital << " " << *Company_capital << " " << 10*(*Interest_rate) << " " 
        << *Investments << " " << *Market_capital << " " << *Bank_capital << " " << *Total_capital << endl;
        Time++;
        Demand++;
        Growth++;
        Wages++;
        Price_out++;
        Employed++;
        Consumer_capital++;
        Company_capital++;
        Market_capital++;
        Bank_capital++;
        Total_capital++;
        Interest_rate++;
        Investments++;
        
    }
    file.close();
    
}


/*
 * Get-functions
 *
 */

int City::get_time() {
    return clock_ -> get_time();
}

Clock * City::get_clock() {
    return clock_;
}

Bank * City::get_bank() {
    return bank_;
}

double City::get_company_capacity_sum() {
    return company_list_ -> get_capacity_sum();
}

double City::get_consumer_capital_sum() {
    
    return consumers_ -> get_capital_sum();
}

Market * City::get_market() {
    return market_;
}

Consumer * City::get_random_consumer() {
    consumers_ -> get_random_consumer();
}

double City::get_capital_sum() {
    double csum = 0;
    csum = consumers_ -> get_capital_sum() + company_list_ -> get_capital_sum() + market_ -> get_capital() + bank_ -> get_assets();//consumers_ -> get_loans_sum();
    
    return csum;
}

int City::get_no_companies() {
    return company_list_ -> get_size();
}

double City::get_loans_to_bank() {
    return loans_to_bank_;
}

Company * City::get_company(string name) {
    return company_list_ -> get_company(name);
}

Company * City::get_random_company() {
    return company_list_ -> get_random_company() -> get_company();
}

Consumer * City::get_optimal_consumer(double mot_we, double skill_we) {
    
    double cap_sum = 0;
    double capacity = 0;
    int no_companies = 0;
    
    cap_sum = get_company_capacity_sum();
    no_companies = get_no_companies();
    capacity = cap_sum/no_companies;
    
    try {
        return (consumers_ -> get_optimal_consumer(mot_we, skill_we, capacity));
    }
    catch(no_return_error) {
        cout << "No optimal consumer" << endl;
    }
    
}

/*
 * Set-functions
 */

void City::set_consumers(Consumer_list * consumer_list) {
    consumers_ = consumer_list;
}
void City::set_companies(Company_list * company_list) {
    company_list_ = company_list;
}


/*
 * Functions for adding consumers and companies to bennyland
 */

void City::add_consumer(Consumer * consumer) {
    consumers_ -> add_first(consumer);
}

void City::add_company(Company * company) {
    company_list_ -> add_company(company);
}

void City::add_company(string name) {
    Company * company = new Company(name, market_, clock_);
    company_list_ -> add_company(company); 
} 

void City::load_company(string nameactual) {
    
    double capital;
    double stock;
    double capacity;
    double debts; 
    double p_c_skill;
    double p_c_mot;
    double wage_const;
    double wage_change_limit;
    double invest;
    double pbr;
    double decay;
    string name;
    
    string line;
    char char_name[100];
    
    strcpy(char_name, nameactual.c_str());
    
    ifstream myfile (char_name);
    if (myfile.is_open()) {
        getline (myfile,line);
        name = line;
        
        getline (myfile,line);
        strcpy(char_name, line.c_str());
        capital = atof(char_name);
        
        getline (myfile,line);
        strcpy(char_name, line.c_str());
        stock = atof(char_name);
        
        getline (myfile,line);
        strcpy(char_name, line.c_str());
        capacity = atof(char_name);
        
        getline (myfile,line);
        strcpy(char_name, line.c_str());
        debts = atof(char_name);
        
        getline (myfile,line);
        strcpy(char_name, line.c_str());
        p_c_skill = atof(char_name);
        
        getline (myfile,line);
        strcpy(char_name, line.c_str());
        p_c_mot = atof(char_name);
        
        getline (myfile,line);
        strcpy(char_name, line.c_str());
        wage_const = atof(char_name);
        
        getline (myfile,line);
        strcpy(char_name, line.c_str());
        wage_change_limit = atof(char_name);
        
        getline (myfile,line);
        strcpy(char_name, line.c_str());
        invest = atof(char_name);
        
        getline (myfile,line);
        strcpy(char_name, line.c_str());
        pbr = atof(char_name);
        
        getline (myfile,line);
        strcpy(char_name, line.c_str());
        decay = atof(char_name);
        
    }
    else {
        cout << "Unable to open file" << endl; 
    }
    //cout << "I city load_company(String) capital =  " << capital << " wc " << wage_const <<  endl;
    //cout << " name " << name << " capital " << capital << " stock " << stock << " capacity " << capacity << " mot " << p_c_mot << " skill " << p_c_skill << " wage_const " << wage_const << " pbr " << pbr << " wcl " << wage_change_limit << " decay " << decay << endl;
    pbr = 0.3;
    wage_const = 0.7;
    cout << "I city load company - fixing pbr to " << pbr << "and wage const to " << wage_const << endl;
    add_company(new Company(nameactual, capital, stock, capacity, p_c_skill, p_c_mot, wage_const, pbr, market_, bank_, clock_));
    
} 

/*
 * Functions to update Bennyland. Note that update_market() is old and not in use.
 * The update_company_employees() is also not in use
 */

void City::negotiate_market_price() {
    
    double demand = 0;
    double consumer_demand = 0;
    double investment_demand = 0;
    double average_investment = 0;
    double expected_investment = 0;
    double production_demand = 0;
    double market_items = 0;
    double company_items = 0;
    double company_planned_production = 0;
    double marginal = 0;
    double items = 0;
    double price_out = 0;
    double price_in = 0;
    double price_old = 0;
    int size = 0;
    int i = 0;
    list<double>::iterator invest; // = NULL;//list::end();
    
    invest = investments_.begin();
    marginal = market_ -> get_marginal();
    size = consumers_ -> get_size();
    price_out = market_ -> get_price_out();
    price_old = price_out;
    //for (int i = 0; i < 4; i++) {
    
    //   for(i; i < 4; i++) {
    //     average_investment += *invest;
    //   invest++;
    // }
    //average_investment = average_investment/i;
    //   expected_investment = (1 - *investmnts_.begin()/average_investment);
    
    consumer_demand = consumers_ -> get_total_demand();
    
    investment_demand = *investments_.begin();//average_investment;//price_out*(company_list_ -> get_investment_sum());//*investments_.begin();//
    
    production_demand =  (company_list_ -> get_items_for_production_sum())*price_out;
    
    market_items = market_ -> get_items();
    company_items = company_list_ -> get_item_sum();
    company_planned_production = company_list_ -> get_planned_production_sum();
    
    demand =  consumer_demand + production_demand + investment_demand;
    items = market_items + company_items + company_planned_production;
    
    price_out = demand/items;
    price_in = price_out/(1 + marginal);
    
    market_ -> set_price_out(price_out);
    
    cout << "I city neg market price, price: " << price_old << endl;
    
    //market_ -> set_price_in(price_in);
    //cout << "I city neg price, planned investment: " << investment_demand << " $BJ at the price: " << price_old << endl << "And planned production: " << company_planned_production  << endl << "   And planned demand: " << consumer_demand << endl;
    //      cout << "I city negotiate, price out: " << price_out << "  demand tot, $BJ:  " << demand << "  items tot:  " << items << endl
    //   << "cons demand: " << consumer_demand << "  investment_demand: " << investment_demand << "  prod dmeand: " << production_demand
    //   << endl
    //   << "market_items: " << market_items << "  company_items: " << company_items << "  planned production: " << company_planned_production 
    //   << endl;
    
    //}   
}

void City::update_consumer_list() {
    consumers_ -> update();
}

void City::update_companies() {
    company_list_ -> update_companies();
}


void City::update_interest_rate() {

	int counter = 0;
	
	double interest = 0.05;
	double prev_interest = 0.05;
    double ir_change_factor = 0.3;
    double est_ir_change = 0.005;
    
    double consumer_sum = 0;
    double company_sum = 0;
    double bank_sum = 0;
    
    double diff_limit = 50;
    double sum_flows_to_bank = 0;
        
    double delta_sum = 0;
    double d_sum_di = 1;
    
    interest = bank_ -> get_interest();
    prev_interest = interest;
    
    
    consumer_sum = consumers_ -> get_expected_net_flow_to_bank_sum();
    company_sum = company_list_ -> get_expected_net_flow_to_bank_sum();
    bank_sum = (bank_ -> get_sum_to_borrow());
    
    
   //Getting estimated flows to the bank
    sum_flows_to_bank = consumer_sum + company_sum + bank_sum;
    
    //Updating interest rate
    bank_ -> change_interest(est_ir_change);
    interest = bank_ -> get_interest();
    
    
    
    while(abs(sum_flows_to_bank) > diff_limit && counter < 20 && interest < 10) {
    
    	
    	
    	//Getting cash-flows
    	consumer_sum = consumers_ -> get_expected_net_flow_to_bank_sum();
    	company_sum = company_list_ -> get_expected_net_flow_to_bank_sum();
    	bank_sum = (bank_ -> get_sum_to_borrow());
    	
    	//Calculating deltas
    	delta_sum = (consumer_sum + company_sum + bank_sum) - sum_flows_to_bank;
    	d_sum_di = delta_sum/(prev_interest - interest);
    	sum_flows_to_bank = consumer_sum + company_sum + bank_sum;
    	
    	est_ir_change = sum_flows_to_bank/d_sum_di;
    	
    	//Changint interest rate
    	prev_interest = interest;
    	bank_ -> change_interest(est_ir_change*ir_change_factor);
    	interest = bank_ -> get_interest();
    	
    	cout << "I city update interest rate " << "Rate: " << interest << "Total cashflow to bank: " << sum_flows_to_bank << company_sum << "  consumer_sum: " << consumer_sum << "    Bank sum: "<< bank_sum << endl;
    	counter = counter + 1;
    }



}
void City::update_interest_rate2() {
    
    double interest = 0.01;
    double factor = 0.005;
    double counter = 1;
    double consumer_sum = 0;
    double company_sum = 0;
    double bank_sum = 0;
    int diff_limit = 50;
    int sum = 0;
    double bank_safety = 0;
    double delta_sum = 0;
    
    interest = bank_ -> get_interest();
    bank_safety = bank_ -> get_safety();
    
    //   cout << "cu i city interest" << endl << "before get consumer to bank cashflow" << endl;
    consumer_sum = consumers_ -> get_expected_net_flow_to_bank_sum();
    //cout << "cu  after get consumer to bank cashflow" << endl;
    company_sum = company_list_ -> get_expected_net_flow_to_bank_sum();
    //cout << "cu before  get company  to bank cashflow" << endl;
    bank_sum = (bank_ -> get_sum_to_borrow());
    //cout << "cu after  get company  to bank cashflow" << endl;
    
    
    //Checking direction of interest change
    sum = consumer_sum + company_sum + bank_sum;
    

     cout << "I city calculate interest  " << "Sum: " << sum  << "  Summa sum < 0, company_sum: " << company_sum << "  consumer_sum: " << consumer_sum << "   Bank sum:" << bank_sum << "  Bank assets: " << bank_ -> get_assets() << "  Interest: " << interest << endl;

    if(sum <= 0) {
        for(int i = 0; i < 5 && abs(sum) > diff_limit ; i++) {
            while(counter*sum < 0 && abs(sum) > diff_limit && interest < 5) { //&&interest > 0.0000001  && 
                cout << "I city calculate interest  " << "Sum: " << sum  << "  Summa sum < 0, company_sum: " << company_sum << "  consumer_sum: " << consumer_sum << "   Bank sum:" << bank_sum << "  Bank assets: " << bank_ -> get_assets() << "  Interest: " << interest << endl;
                //cout << "I city calculate interest  " << "Delta sum: " << delta_sum << endl;
                bank_ -> change_interest(counter*factor);
                interest = bank_ -> get_interest();
                
                consumer_sum = consumers_ -> get_expected_net_flow_to_bank_sum();
                company_sum = company_list_ -> get_expected_net_flow_to_bank_sum();
                bank_sum = (bank_ -> get_sum_to_borrow());
                
                delta_sum = (consumer_sum + company_sum + bank_sum) - sum;
                
                sum = consumer_sum + company_sum + bank_sum; 
                
            }
            counter = - counter;
            factor = factor/4;
        }
    }
    
    else if(sum > 0) {
        counter = 1;
        factor = 0.01; 
        for(int i = 0; i < 10 && abs(sum) > diff_limit ; i++) {
            while(counter*sum > 0 && abs(sum) > diff_limit && interest > 0.00001) {
                cout << "Sum: " << sum << "  Summa flr sum > 0, company_sum: " << company_sum << "  consumer_sum: " << consumer_sum << "    Bank sum: "<< bank_sum << "  Bank assets: " << bank_ -> get_assets() << "  Interest: " << interest << endl;
                
                bank_ -> change_interest(-counter*factor);
                interest = bank_ -> get_interest();
                
                // cout << "cd i city interest" << endl << "before get consumer to bank cashflow" << endl;
                consumer_sum = consumers_ -> get_expected_net_flow_to_bank_sum();
                //    cout << "cd  after get consumer to bank cashflow" << endl;
                company_sum = company_list_ -> get_expected_net_flow_to_bank_sum();
                //cout << "cd before  get company  to bank cashflow" << endl;
                bank_sum = (bank_ -> get_sum_to_borrow());
                //cout << "cd after  get company  to bank cashflow" << endl;
                
                sum = consumer_sum + company_sum + bank_sum; // + bank_sum   
            }
            counter = - counter;
            factor = factor/4; 
        }
    }
    cout << "I city update interest trustworthy " << consumers_ -> get_trustworthy() << endl; 
    //   bank_ -> set_interest(interest);
    
}

// void City::update_interest_rate() {
//     
//     double interest = 0.01;
//     double factor = 0.05;
//     double counter = 1;
//     double consumer_sum = 0;
//     double company_sum = 0;
//     double bank_sum = 0;
//     double d_sum = 1000;
//     double interest_change = 0.001;
//     double diff_limit = 1000;
//     double sum = 0;
//     double bank_safety = 0;
//     
//     interest = bank_ -> get_interest();
//     bank_safety = bank_ -> get_safety();
//     
//     //   cout << "cu i city interest" << endl << "before get consumer to bank cashflow" << endl;
//     consumer_sum = consumers_ -> get_expected_net_flow_to_bank_sum();
//     //cout << "cu  after get consumer to bank cashflow" << endl;
//     company_sum = company_list_ -> get_expected_net_flow_to_bank_sum();
//     //cout << "cu before  get company  to bank cashflow" << endl;
//     bank_sum = (bank_ -> get_sum_to_borrow());
//    
//     
//     
//     sum = consumer_sum + company_sum + bank_sum;
//     
//     cout << "I city calc interest rate, sum: " << sum << " interest: " << interest << endl;
//     
//     
//     
//     
//     if(sum <= 0) {
//         for(int i = 0; i < 10 && abs(sum) > diff_limit ; i++) {
//             while(abs(sum) > diff_limit && interest < 10 && abs(d_sum) > 100) { //&&interest > 0.0000001  && counter*sum < 0 &&
//                 
//                 cout << "I city calculate interest 1 " << "Sum: " << sum  << "  Summa sum < 0, company_sum: " << company_sum << "  consumer_sum: " << consumer_sum << "   Bank sum:" << bank_sum << "  Bank assets: " << bank_ -> get_assets() << "  Interest: " << interest << endl;
//                 
//                 //cout << "interest change: " << interest_change << endl;
//                 bank_ -> change_interest(interest_change);
//                 interest = bank_ -> get_interest();
//                 
//                 consumer_sum = consumers_ -> get_expected_net_flow_to_bank_sum();
//                 company_sum = company_list_ -> get_expected_net_flow_to_bank_sum();
//                 bank_sum = (bank_ -> get_sum_to_borrow());
//                 
// 				//cout << "I city calculate interest 2 " << "Sum: " << sum  << "  Summa sum < 0, company_sum: " << company_sum << "  consumer_sum: " << consumer_sum << "   Bank sum:" << bank_sum << "  Bank assets: " << bank_ -> get_assets() << "  Interest: " << interest << endl;
//                 
// 
//                 d_sum = (sum - (consumer_sum + company_sum + bank_sum))/(interest_change);
//                 
//                 cout << "d_sum in city calculate interest: " <<  d_sum << endl ;
//                 interest_change = (consumer_sum + company_sum + bank_sum)/(4*d_sum);
//                 cout << "expected interest change " << interest_change << endl;
// 
//                 
//                 sum = consumer_sum + company_sum + bank_sum; //+ banksum  
//                 
//             }
//             counter = - counter;
//             factor = factor/4;
//         }
//     }
//     
//     else if(sum > 0) {
//         counter = 1;
//         factor = 0.05; 
//         d_sum = 1;
//         for(int i = 0; i < 10 && abs(sum) > diff_limit ; i++) {
//             while(counter*sum > 0 && abs(sum) > diff_limit && interest > 0.00001) {
//                 cout << "Sum: " << sum << "  Summa for sum > 0, company_sum: " << company_sum << "  consumer_sum: " << consumer_sum << "    Bank sum: "<< bank_sum << "  Bank assets: " << bank_ -> get_assets() << "  Interest: " << interest << endl;
//                 
//                 bank_ -> change_interest(interest_change);
//                 interest = bank_ -> get_interest();
//                 
//                 // cout << "cd i city interest" << endl << "before get consumer to bank cashflow" << endl;
//                 consumer_sum = consumers_ -> get_expected_net_flow_to_bank_sum();
//                 //    cout << "cd  after get consumer to bank cashflow" << endl;
//                 company_sum = company_list_ -> get_expected_net_flow_to_bank_sum();
//                 //cout << "cd before  get company  to bank cashflow" << endl;
//                 bank_sum = (bank_ -> get_sum_to_borrow());
//                 //cout << "cd after  get company  to bank cashflow" << endl;
//                 
//                 d_sum = (sum - (consumer_sum + company_sum + bank_sum))/(interest_change);
//                 cout << "d_sum in city calculate interest: " <<  d_sum << endl ;
//                 interest_change = sum/(4*d_sum);
//                 cout << "expected interest change " << interest_change << endl;
//                 
//                 sum = consumer_sum + company_sum + bank_sum; // + bank_sum  
//                 
//             }
//             counter = - counter;
//             factor = factor/4; 
//         }
// 		}
// 
//     cout << "I city update interest trustworthy " << consumers_ -> get_trustworthy() << endl; 
//     //   bank_ -> set_interest(interest);
    
//}

// void City::update_interest_rate() {

//    double interest = 0;
//    double desired_loans = 0;
//    double available_capital = 0;
//    double factor = 0.001;
//    double counter = 1;
//    double consumer_sum = 0;
//    double company_sum = 0;
//    double sum = 0;

//    available_capital = bank_ -> get_assets();// +  consumers_ -> get_desired_loans_sum();
//    interest = bank_ -> get_interest();
//    desired_loans = company_list_ -> get_desired_loans_sum();// + consumers_ -> get_desired_borrow_sum(); 
//    conusmer_sum = consumers_ -> get_expected_net_flow_to_bank_sum();
//    company_sum = company_list_ -> get_expected_net_flow_to_bank_sum();

//    if(desired_loans > available_capital) {
//       for(int i = 0; i < 4 && abs(desired_loans - available_capital) > 5; i++) {
// 	 while(counter*desired_loans > counter*available_capital && interest < 1 && abs(desired_loans - available_capital) > 5) {
// 	    //  cout << "Desired loand > available capital, loans = " << desired_loans << "  investloans: "  << company_list_ -> get_desired_loans_sum() <<  endl << "Interest: " << interest  << "  Available capital:" << available_capital << endl;
// 	    bank_ -> change_interest(counter*factor);
// 	    interest = bank_ -> get_interest();
// 	    desired_loans = company_list_ -> get_desired_loans_sum();;// + consumers_ -> get_desired_borrow_sum();
// 	    available_capital = bank_ -> get_assets();// + consumers_ -> get_desired_loans_sum();
// 	 }
// 	 counter = - counter;
// 	 factor = factor/10;
//       }
//    }

//    else if(desired_loans < available_capital) {
//       counter = 1;
//       factor = 0.01; 
//       for(int i = 0; i < 4 && abs(desired_loans - available_capital) > 5 ; i++) {
// 	 while(counter*desired_loans < counter*available_capital && interest >= 0.000099 && abs(desired_loans - available_capital) > 5) {
// 	    //cout << "Desired loand < available capital, loans = " << desired_loans << "  investloans: "
// 	    //	 << company_list_ -> get_desired_loans_sum() <<  endl << "Interest: " << interest <<  endl
// 	    //	 << "Available capital:" << available_capital << endl;
// 	    bank_ -> change_interest(-counter*factor);
// 	    available_capital =  bank_ -> get_assets();// + consumers_ -> get_desired_loans_sum();
// 	    desired_loans = company_list_ -> get_desired_loans_sum();// + consumers_ -> get_desired_borrow_sum();
// 	    //desired_loans = company_list_ -> get_desired_loans_sum();
// 	    interest = bank_ -> get_interest();
// 	    //cout << "Desired loand < available capital, loans = " << desired_loans << endl << "Interest: " << interest <<  endl
// 	    //    << "Available capital:" << available_capital << endl;
// 	 }
// 	 counter = - counter;
// 	 factor = factor/10; 
// 	 }
//    }

// //   cout << "Desired loand: " << desired_loans << "  Investloans: "  << company_list_ -> get_desired_loans_sum() << " $BJ"  <<  endl << "Interest: " << interest  << "  Available capital:" << available_capital << " $BJ" << endl;

//    bank_ -> set_interest(interest);

// }

void City::update_employees() {
    
    string name = "";
    double skill = 0;
    double mot = 0;
    Consumer * opt = 0;
    
    /*
     * Starting by removing all the employees that are not profitable to keep
     */
    
    company_list_ -> remove_usless_employees();
    
    /*
     * A company does not always hire the optimal consumer first. A random company is selected
     * and asked if it wants to hire the consumer optimal for its conditions. If not hired other 
     * companies are asked if they want to hire the consumer, and sometimes they may, even though
     * there might be other conusmers more optimal for them...
     */
    
    name = get_random_company() -> get_name();
    skill =  get_company(name) -> get_prod_const_skill(); 
    mot = get_company(name) -> get_prod_const_motivation();
    
    while(company_list_ -> update_employees2(opt = get_optimal_consumer(mot, skill))){}
    
}

void City::tick() {
    clock_ -> tick();
}

void City::save_data() {
    
    double demand = 0;
    double growth = 0;
    double item = 0;
    int time = 0;
    double gdp = 0;
    double nominal_gdp = 0;
    double price_out = 0;
    double interest_rate = 0;
    double unemployment = 0;
    int employed = 0;
    int unemployed = 0;
    int size = 0;
    double wages = 0;
    double investments = 0;
    list <double>::iterator GDP;
    list <double>::iterator Time;
    
    demand = consumers_->get_spendwill_sum()*consumers_ -> get_capital_sum(); 
    item = company_list_ -> get_item_sum();
    price_out = market_ -> get_price_out();
    interest_rate = bank_ -> get_interest();
    size = consumers_ -> get_size();
    employed = consumers_ -> get_employed();
    unemployed = consumers_ -> get_unemployed();
    unemployment = unemployed/size;
    wages = *((company_list_ -> get_company("bempa_AB"))-> wages_.begin());
    nominal_gdp = price_out*item;
    GDP = GDP_.begin();
    
    if(*GDP != 0) {
        growth = (item - *GDP)/(*GDP);
    }
    else {
        growth = 0;
    }
    
    GDP_.push_front(item);
    growth_.push_front(growth);
    demand_.push_front(demand);
    price_out_.push_front(price_out);
    employed_.push_front(employed);
    time_.push_front(clock_ -> get_time()); 
    interest_rate_.push_front(interest_rate);
    investments = *investments_.begin();
    
    ofstream  file2 ("gdp_test.txt", ios::app);
    time = clock_ -> get_time();
    file2 << time << " " << item << " " << growth << " " << demand << " " << price_out << " " 
    << employed << " " << wages << " " << 100*interest_rate << " " << investments << " " << nominal_gdp << endl;
    
    file2.close();
    
}

void City::save_money_data() {
    
    double consumer_capital = 0;
    double company_capital = 0;
    double bank_capital = 0;
    double bank_loans = 0;
    double bank_deposits = 0;
    double market_capital = 0;
    double total_capital = 0;
    double time = 0;
    
    consumer_capital = consumers_ -> get_capital_sum();
    company_capital = company_list_ -> get_capital_sum();
    bank_capital = bank_ -> get_assets();
    bank_loans = bank_ -> get_loans();
    bank_deposits = bank_ -> get_deposits();
    market_capital = market_ -> get_capital();
    total_capital = get_capital_sum();
    time = clock_ -> get_time();
    //  cout << "I city save money data, time: " << clock_ -> get_time() << "  assets: " << bank_capital << endl;
    
    bank_capital_.push_front(bank_capital);
    consumer_capital_.push_front(consumer_capital);
    company_capital_.push_front(company_capital);
    market_capital_.push_front(market_capital);
    total_capital_.push_front(total_capital);
    
    ofstream  file2 ("money_test.txt", ios::app);
    file2 << time << " " << bank_capital << " " << bank_loans  << " " << bank_deposits  << " " << consumer_capital  << " "
    << company_capital << " " << market_capital << " " << total_capital << endl;
    
}


/*
 * save_flash(double time) registrerar alla transaktioner i bennyland i ett tidsschema s� att man kan se hur
 * pengar fl�dar mellan olika instanser under en "m�nad". 
 */

void City::save_flash(int time) {
    double timec = 0;
    timec = clock_ -> get_time();
    //If right time, do everything, else, do nothing
    if(timec >= time && timec < time + 10) {
        double consumer_capital = 0;
        double company_capital = 0;
        double bank_capital = 0;
        double market_capital = 0;
        double total_capital = 0;
        
        consumer_capital = consumers_ -> get_capital_sum();
        company_capital = company_list_ -> get_capital_sum();
        bank_capital = bank_ -> get_assets();
        market_capital = market_ -> get_capital();
        total_capital = get_capital_sum();
        
        ofstream  flash ("flash.txt", ios::app);
        
        flash << flash_counter_ << " " << consumer_capital << " " << company_capital << " "
	    << market_capital << " " << bank_capital << " " << total_capital << endl;
        flash_counter_++;
    }
}

/*
 * Functions to update Bennyland. Note that update_market() is old and not in use.
 * The update_company_employees() is also not in use
 */

void City::produce() {
    company_list_ -> produce();
}

void City::sell_to_market() {
    company_list_ -> sell_to_market();
}

void City::consumers_buy() {
    consumers_ -> consumers_buy();
}

void City::invest(bool invest) {
    double invested_capital = 0;
    if(invest) {
        invested_capital = company_list_ -> invest();
    }  
    investments_.push_front(invested_capital);
    cout << "I city invest, invested_capital: " << invested_capital << "  At the price: " << market_ -> get_price_out() << endl;
}

void City::adjust_money() {
    
    double money_change = 0;
    double total_money = 0;
    double average_price = 0;
    double average_items = 0;
    double average_wage = 0;
    double money_change_factor = 0;
    double bank_money = 0;
    double inflation = 0;
    double item_inflation = 0;
    
    double MAX_CHANGE_FACTOR = 0.5;
    
    
    /*
     *
     * Use function select to select money function
     *
     */

    int function_select = 1;
    
    int i = 0;
    double items_a = 0;
    double price_a = 0;
    double wages_a = 0;

    double sum = 0;
    double sum_items = 0;
    
    list<double>::iterator Price_out;
    list<double>::iterator Items;
    list<double>::iterator Wages;
    
    Price_out = price_out_.begin();
    Items = GDP_.begin();
    Wages = ((company_list_ -> get_company("bempa_AB"))-> wages_.begin());    
    
    total_money = get_capital_sum();
    bank_money = bank_ -> get_assets();
    
    
    //Function 1
    
    items_a = *Items;
    Items = GDP_.begin();
    
    for(i = 0; i < 4; i++) {
        sum_items += *Items;
        Items++;
        //cout << i << " i and items"<<  *Items << endl;
     }
     
    average_items = sum_items/i;
    
    
    //Function 2
    
    price_a = *Price_out;
    Price_out = price_out_.begin();
    
    sum = 0;
    for(i = 0; i < 4; i++) {
        sum += *Price_out;
        Price_out++;
    }
    
    average_price = sum/i;
    
    
    //Function 3
    
    wages_a = *Wages;
    Wages = ((company_list_ -> get_company("bempa_AB"))-> wages_.begin());    
    
    sum = 0;
    for(i = 0; i < 4; i++) {
        sum += *Wages;
        Wages++;
    }
    
    average_wage = sum/i;
    
    //cout << "I city adjust money, money change function " << function_select << endl;
    
    switch (function_select) {
        case 1:
            item_inflation = (1-average_items/items_a);
            inflation = -item_inflation;
            break;
            
        case 2:
            
            inflation = price_a/average_price - 1;
            
            
            break;
            
        case 3:
            
            inflation = wages_a/average_wage - 1;
            
            
            break;
            
        default:
            break;
    }
    
    money_change_factor = -inflation;
    

    if (money_change_factor > MAX_CHANGE_FACTOR) {
        money_change_factor = MAX_CHANGE_FACTOR;
    }
    else if( -money_change_factor > MAX_CHANGE_FACTOR) {
        money_change_factor = -MAX_CHANGE_FACTOR;
    }
    
    if (clock_ -> get_time() < 10) {
        money_change_factor = 0;
    }
    
    money_change = total_money*money_change_factor;
    
    
    cout << "I city adjust money, mone increase factor: " << money_change/total_money << " Total money " << total_money << " Money change " << money_change <<  endl;
    //money_change = (1-average_items/items_a)*total_money;
    
    //if(price_a > average_price) {
    //    money_change = (1-average_price/price_a)*total_money;
    //}
    
    /*
     *What happends if we increase the money without any reason?!!?
     */
    /*
    if(clock_ -> get_time() == 200) {
        
        money_change = -10000000;
        cout << "In city adjust money increasing money at time 200" << endl;
    }
    */
    
    bank_ -> change_assets(money_change);
    loans_to_bank_ += money_change;
    
}

void City::pay_company_employees() {
    company_list_ -> pay_employees();
}

void City::company_pay_interest() {
    company_list_ -> pay_interest();
}

void City::company_repay_to_bank() {
    
    company_list_ -> repay_to_bank();
}


void City::consumers_bank_business() {
    consumers_ -> repay_to_bank();
    consumers_ -> get_repayment_from_bank();
}

void City::consumer_get_and_pay_interest() {
    consumers_ -> get_and_pay_interest();
}



/*
 * Assuming that all the consumers owns an equal share of 
 * each company.
 */



void City::company_pay_dividends() {
    double total_profit_c = 0;
    double total_profit_m = 0;
    double total_profit_b = 0;
    double amount = 0;	
    int size = 0;
    
    size = consumers_ -> get_size();
    
    total_profit_c = company_list_ -> pay_dividends() ;
    total_profit_b = bank_ -> pay_dividends();
    total_profit_m = market_-> pay_dividends();
    
    //amount = (total_profit_m + total_profit_c+ total_profit_b)/size;
    
    consumers_ -> pay_dividends_log(total_profit_c/size, "Company");
    consumers_ -> pay_dividends_log(total_profit_m/size, "Market");
    consumers_ -> pay_dividends_log(total_profit_b/size, "Bank");
    
}

void City::consumers_deposit_and_borrow_from_bank() {
    consumers_ -> deposit_and_borrow_from_bank();
    
    //cout << "I city consumers_deposit_and_borrow_from_bank, no consumer lending activated" << endl;
    //cout << "I city consumers deposit and loan, bank_loans: " << bank_ -> get_loans() << endl;
    //cout << "I city consumers deposit and loan, consumer_loans: " << consumers_ -> get_loans_sum() << endl;
    //cout << "I city consumers deposit and loan, consumer_debts: " << consumers_ -> get_debts_sum() << endl;
    //cout << "I city consumers deposit and loan, company_loans: " << company_list_ -> get_debts_sum() << endl;
    
    //cout << "I city consumers deposit and loan, bank_borrow: " << bank_ -> get_deposits() << endl;
    
    
}

void City::consumers_deposit_to_bank() {
    consumers_ -> deposit_money_to_bank();
}

void City::consumers_borrow_from_bank() {
    consumers_ -> borrow_money_from_bank();
}
















