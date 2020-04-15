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
list_(0),
size_(0),
name_("")
{}

Company_list::Company_list(string name) :
list_(0),
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
        for(q = list_; q; q = q -> next_) {
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
        for (Element_company *p = list_; p; p = p -> next_) {
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

int Company_list::get_size() {
    return size_;
}

Element_company * Company_list::get_random_company() {
    //print_list();
    int nr = (rand()%(size_ + 1));//SKA NOG VA +1
    //cout << "I element company ransdom" << nr << endl;
    Element_company * p = list_;
    for(int i = 1; i < nr; i++) {
        //cout << i << " ";
        p = p -> next_;
    }
    return p;
}

Company * Company_list::get_company(string name) {
    Element_company * p;
    
    if(list_) {
        for(p = list_; p; p = p -> next_) {
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

double Company_list::get_capital_sum() {
    Element_company * p;
    double sum = 0;
    
    for (p = list_; p; p = p -> next_) {
        sum += p -> get_company() -> get_capital();
    }
    return sum;
}

double Company_list::get_item_sum() {
    Element_company * p;
    double sum = 0;
    
    for (p = list_; p; p = p -> next_) {
        sum += p -> get_company() -> get_stock();
    }
    return sum;
}

double Company_list::get_capacity_sum() {
    Element_company * p;
    double sum = 0;
    
    for (p = list_; p; p = p -> next_) {
        sum += p -> get_company() -> get_capacity();
    }
    return sum;
}


double Company_list::get_investment_sum() {
    Element_company * p;
    double sum = 0;
    
    for (p = list_; p; p = p -> next_) {
        sum += p -> get_company() -> get_desired_investment();
    }
    //   cout << "I company_list invest: " << sum << endl;
    return sum;
}

double Company_list::get_desired_loans_sum() {
    Element_company * p;
    double sum = 0;
    
    for (p = list_; p; p = p -> next_) {
        sum += p -> get_company() -> get_desired_loans();
    }
    //cout << "I company_list loand: " << sum << endl;
    return sum;
}

double Company_list::get_debts_sum() {
    Element_company * p;
    double sum = 0;
    
    for (p = list_; p; p = p -> next_) {
        sum += p -> get_company() -> get_debts();
    }
    //cout << "I company_list loand: " << sum << endl;
    return sum;
}



double Company_list::get_expected_net_flow_to_bank_sum() {
    Element_company * p;
    double sum = 0;
    //cout << "I company_list net cf to bank sum: " << sum << endl;
    for (p = list_; p; p = p -> next_) {
        sum += p -> get_company() -> get_expected_net_flow_to_bank();
    }
    //cout << "I company_list net cf to bank sum: " << sum << endl;
    return sum;
}



double Company_list::get_items_for_production_sum() {
    Element_company * p;
    double sum = 0;
    
    for (p = list_; p; p = p -> next_) {
        sum += p -> get_company() -> get_items_for_production();
    }
    return sum;
}

double Company_list::get_planned_production_sum() {
    Element_company * p;
    double sum = 0;
    
    for (p = list_; p; p = p -> next_) {
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
        list_ = new Element_company(list_, company);
    }
    else {
        list_ = new Element_company(0, company);
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
    
    for (p = list_; p; p = p -> next_) {
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
    
    for(p = list_; p; p = p -> next_) {
        return p -> get_company() -> update_employees(opt);
    }
    
}

bool Company_list::update_employees2(Consumer * opt) {
    Element_company * p = 0;
    Element_company * r = 0;
    Element_company * q = 0;  
    bool after = 0;
    bool before = 0;  
    
    p = get_random_company();
    r = p;
    
    //Checks the random company and the liet to the end
    for(p; p; p = p -> next_) {
        after = p -> get_company() -> update_employees(opt);
        
        //If hired, return true and get a new opt consumer
        if(after) {
            return after;
        }
    }
    
    //Checks the list from the start to the random company
    for(q = list_; q != r; q = q -> next_) {
        
        before = q -> get_company() -> update_employees(opt);
        
        //If hired, return true and get a new opt consumer
        if(before) {
            return before;
        }
    }
    
    //No one wants to hire opt, done. 
    return false;
}

void Company_list::remove_usless_employees() {
    
    Element_company * p;
    
    if(list_) {  
        for(p = list_; p; p = p -> next_) {
            (p -> get_company()) -> remove_usless_employees();
        }
    }
    else {
        cout << "No companies in company list" << endl;
    }
    
}


/*
 * Functions to operate on the companies
 */

double Company_list::produce() {
    
    Element_company * p;
    double sum = 0;
    cout << "I company list, items needed for production: (items): " << get_items_for_production_sum() << endl;
    
    for(p = list_; p; p = p -> next_) {
        sum += (p -> get_company()) -> produce();
    }
    
    //cout << "I company list, actual production (items): " << sum << endl;
    
    return sum;
}

void Company_list::sell_to_market() {
    
    Element_company * p;
    
    for(p = list_; p; p = p -> next_) {
        (p -> get_company()) -> sell_to_market();
    }
}

void Company_list::pay_employees() {
    
    Element_company * p;
    
    for(p = list_; p; p = p -> next_) {
        (p -> get_company()) -> pay_employees_individual();
    }
}

double Company_list::pay_dividends() {
    
    Element_company * p;
    double total_profit = 0;
    
    for(p = list_; p; p = p -> next_) {
        total_profit += (p -> get_company()) -> pay_dividends();
    }
    
    return total_profit;
}

void Company_list::pay_interest() {
    Element_company * p;
    
    for(p = list_; p; p = p -> next_) {
        p -> get_company() -> pay_interest();
    }
}

void Company_list::repay_to_bank() {
    Element_company * p;
    
    for(p = list_; p; p = p -> next_) {
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
    
    for(p; p; p = p -> next_) {
        sum += p -> get_company() -> invest();
        i++;
    }
    
    for(q = list_; q != r; q = q -> next_) {
        sum += q -> get_company() -> invest();
        i++;
    }
    //  cout << "I comp list, no companies that invested: " << i << endl;
    //  cout << "I  company list invest, invested items: " << endl;
    //for(p = list_; p; p = p -> next_) {
    //  sum += p -> get_company() -> invest();
    //}
    
    return sum;
}









