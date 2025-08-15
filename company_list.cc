#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <exception>
#include <stdexcept>

//#include "consumer.h"
#include "functions.h"
#include "company_list.h"
//#include "element_company.h"
#include "error_no_return.h"

using namespace std;

Company_list::Company_list() :
list_(nullptr),
size_(0),
name_("")
{}

Company_list::Company_list(string name) :
list_(nullptr),
size_(0), 
name_(name)
{}


/*
 * Info-functions
 */

void Company_list::info() {
    cout << endl << "COMPANIES" << endl << "----------------------------------------------------------" << endl; 
    cout << "Number of companies: " << size_ << endl << endl;
}

void Company_list::employee_info(string command) {
    Element_company * q;
    cout << endl << name_ << endl << "--------------------------------" << endl;
    if(command == "all" || command == "") {
        for(q = list_.get(); q; q = q -> next_.get()) {
            q -> get_company() -> employee_info();
        }
    }
    else {
        try {
            get_company(command) -> employee_info();
        } 
        catch(no_return_error) {
            cout << "Company not found" << endl;
        }
        //    catch(exception& e) {
        //  cout << typeid(e) .name() << ": " << e.what() << endl;
        //}
    }
}

void Company_list::print_list() {
    
    info();
    if(list_) {
        for (Element_company *p = list_.get(); p; p = p -> next_.get()) {
            p->company_->info();
        }
    }
    
    cout << endl; 
}

void Company_list::print_employees(string company) {
    get_company(company) -> print_employees();
}


/*
 * Get-functions
 */

int Company_list::get_size() const {
    return size_;
}

Element_company * Company_list::get_random_company() {
    //print_list();
    int nr = (rand()%(size_ + 1));//SKA NOG VA +1
    //cout << "I element company ransdom" << nr << endl;
    Element_company * p = list_.get();
    for(int i = 1; i < nr; i++) {
        //cout << i << " ";
        p = p -> next_.get();
    }
    return p;
}

//Returns the company with highest average wage lower than "limit". 
Company * Company_list::get_next_best_salary_company(double limit) {


    Element_company * p;
    Element_company * r;
    double current_wage = 0;
    double highest_wage = 0;
    
    if(list_) {
        for(p = list_.get(); p; p = p -> next_.get()) {
            current_wage = p ->get_company() -> get_average_wage();

            if(current_wage == 0) {
                return get_random_company() -> get_company();
            }

            //cout << "I company list get_next_best, current_wage: " << current_wage << " highest wage: " << highest_wage << " limit " << limit << " for " << p-> get_company() -> get_name() << endl;
            if (current_wage < limit && current_wage > highest_wage) {
                highest_wage = current_wage;
                r = p;
            }
        }
        if(highest_wage == 0) {
            throw no_return_error("Cant find any company");
        }
    }
    else {
        throw no_return_error("no list"); 
    } 
    return r -> get_company() ;
}

Company * Company_list::get_company(string name) const {
    Element_company * p;
    
    if(list_) {
        for(p = list_.get(); p; p = p -> next_.get()) {
            if (p ->get_name() == name) {
                return p -> get_company() ;
            }
        }
        throw no_return_error("Cant find the company");
    }
    else {
        throw no_return_error("no list"); 
    } 
}

double Company_list::get_capital_sum() const{
    Element_company * p;
    double sum = 0;
    
    for (p = list_.get(); p; p = p -> next_.get()) {
        sum += p -> get_company() -> get_capital();
    }
    return sum;
}

double Company_list::get_item_sum() const{
    Element_company * p;
    double sum = 0;
    if(list_) {
    	for (p = list_.get(); p; p = p -> next_.get()) {
        	sum += p -> get_company() -> get_stock();
    	}
   	} 
    return sum;
}

double Company_list::get_capacity_sum() const {
    Element_company * p;
    double sum = 0;
    
    for (p = list_.get(); p; p = p -> next_.get()) {
        sum += p -> get_company() -> get_capacity();
    }
    return sum;
}


double Company_list::get_investment_sum() const {
    Element_company * p;
    int sum = 0;
    //double sum2 = 0;
    
    for (p = list_.get(); p; p = p -> next_.get()) {
        sum += p -> get_company() -> get_desired_investment();
        //sum2 += p -> get_company() -> get_desired_investment_old();
    }
    //   cout << "I company_list invest: " << sum << endl;
    return sum;
}

double Company_list::get_desired_loans_sum() const {
    Element_company * p;
    double sum = 0;
    
    for (p = list_.get(); p; p = p -> next_.get()) {
        sum += p -> get_company() -> get_desired_loans();
    }
    //cout << "I company_list loand: " << sum << endl;
    return sum;
}

double Company_list::get_debts_sum() const {
    Element_company * p;
    double sum = 0;
    
    for (p = list_.get(); p; p = p -> next_.get()) {
        sum += p -> get_company() -> get_debts();
    }
    //cout << "I company_list loand: " << sum << endl;
    return sum;
}

int Company_list::get_environmental_impact_sum() const {
    Element_company * p;
    double sum = 0;
    
    for (p = list_.get(); p; p = p -> next_.get()) {
        sum += p -> get_company() -> get_environmental_impact();
    }
    //cout << "I company_list loand: " << sum << endl;
    return sum;
}



double Company_list::get_average_wage() const {
    Element_company * p;
    double sum = 0;
    int number_of_companies = 0;
    double average_wage = 0;
    
    for (p = list_.get(); p; p = p -> next_.get()) {
        sum += p -> get_company() -> get_average_wage();
    }

    number_of_companies = get_size();
    
    if(not(number_of_companies == 0)) {
        average_wage = sum/number_of_companies;
    }
    else {
        cout << "No companies found in company list get average wage" << endl;
    }

    return sum;
}

double Company_list::get_average_wage_historical(int years) const {
    Element_company * p;
    double sum = 0;
    int number_of_companies = 0;
    double average_wage = 0;

    for (p = list_.get(); p; p = p -> next_.get()) {
        sum += p -> get_company() -> get_average_wage_historical(years);
    }

    number_of_companies = get_size();

    if(not(number_of_companies == 0)) {
        average_wage = sum/number_of_companies;
    }
    else {
        cout << "No companies found in company list get average wage" << endl;
    }

    return sum;
}



double Company_list::get_expected_net_flow_to_bank_sum() const {
    Element_company * p;
    double sum = 0;
    //cout << "I company_list net cf to bank sum: " << sum << endl;
    for (p = list_.get(); p; p = p -> next_.get()) {
        sum += p -> get_company() -> get_expected_net_flow_to_bank();
    }
    //cout << "I company_list net cf to bank sum: " << sum << endl;
    return sum;
}



double Company_list::get_items_for_production_sum() const {
    Element_company * p;
    double sum = 0;
    
    for (p = list_.get(); p; p = p -> next_.get()) {
        sum += p -> get_company() -> get_items_for_production();
    }
    return sum;
}

double Company_list::get_planned_production_sum() const {
    Element_company * p;
    double sum = 0;
    
    for (p = list_.get(); p; p = p -> next_.get()) {
        sum += p -> get_company() -> get_production();
    }
    return sum;
    
    
    
}

/*
 * Functions to add employees or companies
 */ 

void Company_list::add_company(Company * company) {
    Element_company * p;
    size_++;
    
    if(list_) {
        list_ = std::make_unique<Element_company>(std::move(list_), company);
    }
    else {
        list_ = std::make_unique<Element_company>(nullptr, company);
    }
}

void Company_list::add_employee(string name, Consumer * consumer) {  
    get_company(name) -> add_employee(consumer);
}


/*
 * Functions to update companies
 */

void Company_list::update_companies() {
    Element_company * p;
    
    for (p = list_.get(); p; p = p -> next_.get()) {
        p -> get_company() -> update_company();
    }
    
}

bool Company_list::update_employees(Consumer * opt, string name) {
    
    if(name == "all" || name == "") {
        return update_employees(opt);
    }
    else { 
        return get_company(name) -> update_employees(opt);
    }
    
}

bool Company_list::update_employees(Consumer * opt) {
    Element_company * p;
    
    for(p = list_.get(); p; p = p -> next_.get()) {
        return p -> get_company() -> update_employees(opt);
    }

    return false;
    
}

bool Company_list::update_employees3(Consumer * opt) {
    Element_company * p = 0;
    Element_company * r = 0;
    Element_company * q = 0;  
    bool after = 0;
    bool before = 0;  
    
    p = get_random_company();
    r = p;
    
    //Checks the random company and the liet to the end
    for(p; p; p = p -> next_.get()) {
        after = p -> get_company() -> update_employees(opt);
        
        //If hired, return true and get a new opt consumer
        if(after) {
            return after;
        }
    }
    
    //Checks the list from the start to the random company
    for(q = list_.get(); q != r; q = q -> next_.get()) {
        
        before = q -> get_company() -> update_employees(opt);
        
        //If hired, return true and get a new opt consumer
        if(before) {
            return before;
        }
    }
    
    //No one wants to hire opt, done. 
    return false;
}

bool Company_list::update_employees2(Consumer * opt) {
    Company * p = 0;
    bool hired = false;
    double best_wage = 10000000;  
    
    // Check if opt is null - this happens when no optimal consumer is found
    if (!opt) {
        return false;
    }
    
    for(int i = 1; i < size_; i++){
        p = get_next_best_salary_company(best_wage);
        best_wage = p-> get_average_wage();
        hired = p-> update_employees(opt);

        //If hired, return true and get new optimal consumer
        if(hired) {
            //cout << "Company i c-list " << p -> get_name() << " hired" << endl;
            return hired;
        }
        else {
            //cout << "Company " << p -> get_name() << " did not hire " << opt -> get_name() << endl;
        }
    }    

    //No one wants to hire opt, done. 
    return false;

}

void Company_list::set_market(Market * newMarket) {
    Element_company * p;

    for(p = list_.get(); p; p = p -> next_.get()) {
        (p -> get_company()) -> set_market(newMarket);
    }
}

void Company_list::set_intecity_trading(bool enable) {
    Element_company * p;

    for(p = list_.get(); p; p = p -> next_.get()) {
        (p -> get_company()) -> set_enable_intercity_trading(enable);
    }
}

void Company_list::remove_usless_employees() {
    
    Element_company * p;
    
    if(list_) {  
        for(p = list_.get(); p; p = p -> next_.get()) {
            (p -> get_company()) -> remove_usless_employees();
        }
    }
    else {
        cout << "No companies in company list" << endl;
    }
    
}

void Company_list::update_companies_from_database(string city_name) {
    
    Element_company * p;
    
    if(list_) {  
        for(p = list_.get(); p; p = p -> next_.get()) {
            (p -> get_company()) -> update_from_database(city_name);
        }
    }
    else {
        cout << "No companies in company list" << endl;
    }
    
}

void Company_list::write_time_data_to_database(string city_name) {
    
    Element_company * p;
    
    if(list_) {  
        for(p = list_.get(); p; p = p -> next_.get()) {
            (p -> get_company()) -> save_time_data_to_database(city_name);
        }
    }
    else {
        cout << "No companies in company list" << endl;
    }
    
}




/*
 * Functions to operate on the companies
 */

double Company_list::produce(string city_name) {
    
    Element_company * p;
    double sum = 0;
    cout << "I company list, items needed for production: (items): " << get_items_for_production_sum() << endl;
    
    for(p = list_.get(); p; p = p -> next_.get()) {
        sum += (p -> get_company()) -> produce(city_name);
    }
    
    //cout << "I company list, actual production (items): " << sum << endl;
    
    return sum;
}

void Company_list::sell_to_market() {
    
    Element_company * p;
    
    for(p = list_.get(); p; p = p -> next_.get()) {
        (p -> get_company()) -> sell_to_market();
    }
}

// void Company_list::pay_employees() {
//     
//     Element_company * p;
//     
//     for(p = list_.get(); p; p = p -> next_.get()) {
//         (p -> get_company()) -> pay_employees_individual();
//     }
// }

double Company_list::pay_employees(double income_tax) {
    
    Element_company * p;
    double income_tax_sum = 0;
    
    for(p = list_.get(); p; p = p -> next_.get()) {
        income_tax_sum += (p -> get_company()) -> pay_employees_individual(income_tax);
    }
    
    return income_tax_sum;
}

double Company_list::pay_dividends() {
    
    Element_company * p;
    double total_profit = 0;
    
    for(p = list_.get(); p; p = p -> next_.get()) {
        total_profit += (p -> get_company()) -> pay_dividends();
    }
    
    return total_profit;
}

void Company_list::pay_interest() {
    Element_company * p;
    
    for(p = list_.get(); p; p = p -> next_.get()) {
        p -> get_company() -> pay_interest();
    }
}

void Company_list::repay_to_bank() {
    Element_company * p;
    
    for(p = list_.get(); p; p = p -> next_.get()) {
        p -> get_company() -> repay_to_bank();
    }
}

double Company_list::invest() {
    
    double sum = 0;
    int i = 0;
    
    Element_company * p = 0;
    Element_company * r = 0;
    Element_company * q = 0;  
    
    p = get_random_company();
    r = p;
    
    for(p; p; p = p -> next_.get()) {
        sum += p -> get_company() -> invest();
        i++;
    }
    
    for(q = list_.get(); q != r; q = q -> next_.get()) {
        sum += q -> get_company() -> invest();
        i++;
    }
    //  cout << "I comp list, no companies that invested: " << i << endl;
    //  cout << "I  company list invest, invested items: " << endl;
    //for(p = list_.get(); p; p = p -> next_.get()) {
    //  sum += p -> get_company() -> invest();
    //}
    
    return sum;
}









