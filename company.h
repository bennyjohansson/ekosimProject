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
// #include "employee_list.h"
// #include "city.h"

using namespace std;

class Company
{
public:
    // COMMENTED OUT: Old constructors without global_market parameter - these were causing null pointer issues
    // Company();
    // Company(string name);
    // Company(string, Market*, Clock*);
    Company(string, Market *, Market *, Clock *); // name, local market, global market, clock
    // Company(string, string, double, double, double, double, double, double, double, Market*, Bank *, Clock*);
    Company(string, string, double, double, double, double, double, double, double, Market *, Market *, Bank *, Clock *); // Local market first then global market
    // NAME CAPITAL STOCK CAPACITY PROD_CONST_SKILL PROD_CONST_MOT WAGE_CONST

    /*
     * Info functions
     */

    void info();
    void employee_info();
    void print_employees();
    void print_shareholders();
    void save(string);
    Company *load(string, Market *, Bank *, Clock *);

    /*
     * Get functions
     */

    string get_name() const;
    double get_capital() const;
    double get_prod_const_skill() const;
    double get_prod_const_motivation() const;
    double get_item_efficiency() const;
    double get_wage_const() const;
    double get_production();
    int get_production_function() const;
    double get_production_parameter() const;
    int get_no_employees();

    double get_production(Consumer *);
    double get_stock() const;
    double get_items_for_production();
    double get_investment();
    double get_invest() const;
    double get_debts() const;
    int get_environmental_impact() const;
    double get_capacity() const;
    double get_pbr();
    double get_average_wage();
    double get_average_wage_historical(int);
    double get_total_wages();
    double get_estimated_wages(double);
    double get_wage_change_limit() const;
    double get_investment_cashflow(double, double, double, double, double, double, double, double);
    int get_desired_investment(double fac_rate, double cap_param, double cap_rate, double item_eff_rate);

    double get_desired_loans(double fac_rate, double cap_param, double cap_rate, double item_eff_rate);
    double get_expected_net_flow_to_bank(double fac_rate, double cap_param, double cap_rate, double item_eff_rate);

    Market *get_active_market();
    bool get_enable_intercity_trading() const;

    /*
     * Set functions
     */

    void set_capital(double);
    void set_production_function(int);
    void set_production_parameter(double);
    void set_prod_const_skill(double);
    void set_prod_const_motivation(double);
    void set_item_efficiency(double);
    void set_wage_const(double);
    void set_stock(double);
    void set_invest(double);
    void set_debts(double);
    void set_capacity(double);
    void set_pbr(double);
    void set_wage_change_limit(double);
    void set_market(Market *newMarket);
    void set_enable_intercity_trading(bool);

    /*
     *Change functions
     */

    void change_capital(double);
    void change_prod_const_skill(double);
    void change_prod_const_motivation(double);
    void change_item_efficiency(double);
    void change_wage_const(double);
    void change_stock(double);
    void change_invest(double);
    void change_debts(double);
    void change_environmental_impact(int);
    void change_capacity(double);
    void change_pbr(double);
    void change_wage_change_limit(double);

    /*
     * Functions to add or remove employees
     */

    void add_employee(Consumer *);
    void remove_employee(Consumer *);

    void add_shareholder(Consumer *);
    void add_multiple_shareholders(Element_consumer *);
    void remove_shareholder(Consumer *);

    void update_company();
    bool update_employees(Consumer *);
    void remove_usless_employees();
    void update_from_database(string city_name);
    void save_time_data_to_database(string city_name);

    double contribution_adding(Consumer *);
    double contribution_removing(Consumer *);

    double produce(string);
    void sell_to_market();
    void pay_employees();
    double pay_employees_individual(double, int);
    void pay_interest();
    void repay_to_bank();
    double pay_dividends();
    double pay_dividends_directly(double);
    int buy_items_for_production();
    double invest(double fac_rate, double cap_param, double cap_rate, double item_eff_rate);

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
    string city_name_;
    double capital_;
    int stock_;
    double capacity_;
    double capacity_0_;
    double debts_;
    int environmental_impact_;

    int production_function_;
    int current_production_items_;
    double production_parameter_;

    double investment_capacity_vs_efficiency_split_;
    double investment_item_vs_factor_split_;

    double prod_const_skill_;
    double prod_const_motivation_;
    double item_efficiency_;
    double wage_const_;
    double wage_change_limit_;
    double invest_;
    double pbr_;
    double decay_;
    double max_leverage_;
    bool enable_intercity_trading_;

    Consumer_list *employees_;
    Consumer_list *shareholders_;
    Market *market_;
    Market *global_market_; // Pointer to global market (owned by World)
    Bank *bank_;
    Clock *clock_;
};

#endif
