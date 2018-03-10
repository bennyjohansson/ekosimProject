#ifndef COMPANY_H
#define COMPANY_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>

#include "consumer.h"
#include "consumer_list.h"
#include "market.h"
#include "bank.h"
//#include "employee_list.h"
//#include "city.h"

using namespace std;

class Company {
public:
    
    Company();
    Company(string name);
    Company(string, Market*, Clock*);
    Company(string, double, double, double, double, double, double, double, Market*, Bank *, Clock*);
    // NAME CAPITAL STOCK CAPACITY PROD_CONST_SKILL PROD_CONST_MOT WAGE_CONST
    
    /*
     * Info functions
     */
    
    void info();
    void employee_info();  
    void print_employees();
    void save(string);
    Company * load(string, Market*, Bank*, Clock*);
    
    /*
     * Get functions
     */
    
    string get_name();
    double get_capital();
    double get_prod_const_skill();
    double get_prod_const_motivation();
    double get_wage_const();  
    double get_production();
    double get_production(Consumer *);
    double get_stock();
    double get_items_for_production();
    double get_investment();
    double get_invest();
    double get_debts();
    double get_capacity();
    double get_pbr();
    double get_total_wages();
    double get_estimated_wages(double);
    double get_wage_change_limit();
    double get_investment_cashflow(double, double);
    double get_desired_investment();
    double get_desired_loans();
    double get_expected_net_flow_to_bank();
    
    /*
     * Set functions
     */
    
    void set_capital(double);
    void set_prod_const_skill(double);
    void set_prod_const_motivation(double);
    void set_wage_const(double);
    void set_stock(double);
    void set_invest(double);
    void set_debts(double);
    void set_capacity(double); 
    void set_pbr(double);
    void set_wage_change_limit(double);
    //void set_market(Market * market);
    
    
    /*
     *Change functions
     */
    
    void change_capital(double);
    void change_prod_const_skill(double);
    void change_prod_const_motivation(double);
    void change_wage_const(double);
    void change_stock(double);  
    void change_invest(double);
    void change_debts(double);
    void change_capacity(double);
    void change_pbr(double);
    void change_wage_change_limit(double);
    
    
    /*
     * Functions to add or remove employees 
     */
    
    void add_employee(Consumer * consumer);
    void remove_employee(Consumer *);
    
    void update_company();
    bool update_employees(Consumer *);
    void remove_usless_employees();
    
    double contribution_adding(Consumer *);
    double contribution_removing(Consumer *);
    
    double produce();
    void sell_to_market();
    void pay_employees(); 
    void pay_employees_individual(); 
    void pay_interest();
    void repay_to_bank();
    double pay_dividends();
    void buy_items_for_production();
    double invest();
    
    
    /*
     * Lists that keep track of wages and how many employees the company has
     */
    
    list<double> wages_;
    list<int> employees_no_;
    list<double> investments_;
    list<double> profit_;
    list<double> dividends_;
    list<double> debts_list_;
    
private:
    string name_;  
    double capital_;
    double stock_;
    double capacity_;
    double capacity_0_;
    double debts_;
    
    double prod_const_skill_;
    double prod_const_motivation_;
    double wage_const_;  
    double wage_change_limit_;
    double invest_;
    double pbr_;
    double decay_;
    
    Consumer_list * employees_;
    Market *market_;
    Bank *bank_;
    Clock * clock_;
    
};

#endif
