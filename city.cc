#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <list>
#include <fstream>
#include <cmath>
#include <random>

#include "SQLfunctions.h"
#include "functions.h"
#include "city.h"
#include "error_no_return.h"

using namespace std;

City::City() : name_("bennyland"),
               consumers_(std::make_unique<Consumer_list>("bennyland")),
               company_list_(std::make_unique<Company_list>("bennyland")),
               // labour_market_(std::make_unique<Consumer_list>("LABOUR MARKET")),
               market_(std::make_unique<Market>()),
               global_market_(nullptr),
               bank_(std::make_unique<Bank>("BENNYBANK", 0.02, 3)),
               clock_(new Clock()),
               enable_intercity_trading_(false)
{
}

City::City(string name) : name_(name),
                          consumers_(std::make_unique<Consumer_list>(name)),
                          company_list_(std::make_unique<Company_list>(name)),
                          // labour_market_(std::make_unique<Consumer_list>("LABOUR MARKET")),
                          capital_owners_(std::make_unique<Consumer_list>(name)),
                          market_(std::make_unique<Market>()),
                          global_market_(nullptr),
                          bank_(std::make_unique<Bank>("BENNYBANK", 0.05, 3)),
                          clock_(new Clock()),
                          flash_counter_(0),
                          shareToSteal_(0.95),
                          laundry_factor_(0.95),
                          no_years_laundry_(4),
                          capital_(0),
                          vat_(0.2),
                          income_tax_(0.3),
                          capital_gains_tax_(0.3),
                          time_to_steal_(7919),
                          enable_intercity_trading_(false)
{
}
City::City(string name, Clock *clock) : name_(name),
                                        consumers_(std::make_unique<Consumer_list>(name)),
                                        company_list_(std::make_unique<Company_list>(name)),
                                        // labour_market_(std::make_unique<Consumer_list>("LABOUR MARKET")),
                                        capital_owners_(std::make_unique<Consumer_list>(name)),
                                        market_(std::make_unique<Market>()),
                                        global_market_(nullptr),
                                        bank_(std::make_unique<Bank>("BENNYBANK", 0.05, 3)),
                                        clock_(clock),
                                        flash_counter_(0),
                                        shareToSteal_(0.95),
                                        laundry_factor_(0.95),
                                        no_years_laundry_(4),
                                        capital_(0),
                                        vat_(0.2),
                                        income_tax_(0.3),
                                        capital_gains_tax_(0.3),
                                        budget_balance_(0.00),
                                        time_to_steal_(7919),
                                        enable_intercity_trading_(false)
{
}

City::City(string name, Clock *clock, Market *global_market) : name_(name),
                                                               consumers_(std::make_unique<Consumer_list>(name)),
                                                               company_list_(std::make_unique<Company_list>(name)),
                                                               // labour_market_(std::make_unique<Consumer_list>("LABOUR MARKET")),
                                                               capital_owners_(std::make_unique<Consumer_list>(name)),
                                                               market_(std::make_unique<Market>()),
                                                               global_market_(global_market),
                                                               bank_(std::make_unique<Bank>("BENNYBANK", 0.05, 3)),
                                                               clock_(clock),
                                                               flash_counter_(0),
                                                               shareToSteal_(0.95),
                                                               laundry_factor_(0.95),
                                                               no_years_laundry_(4),
                                                               capital_(0),
                                                               vat_(0.2),
                                                               income_tax_(0.3),
                                                               capital_gains_tax_(0.3),
                                                               budget_balance_(0.00),
                                                               time_to_steal_(7919),
                                                               enable_intercity_trading_(false),
                                                               fac_increase_rate_1_(0.002),
                                                               cap_increase_param_1_(8000),
                                                               cap_increase_rate_1_(0.0001),
                                                               item_efficiency_rate_(0.001),
                                                               pay_wage_in_cash_(1)
{
}

void City::info()
{
    cout << endl
         << "----------------------------------------" << endl
         << "THE CITY" << endl
         << "----------------------------------------" << endl
         << "Name: " << name_ << endl
         << "Population: " << consumers_->get_size() << endl
         << "Capital owners; " << capital_owners_->get_size() << endl
         << endl
         << "COMPANIES " << endl;
    company_list_->print_list();
    cout << endl;
}

void City::consumer_info()
{
    consumers_->info();
}

void City::capital_owners_info()
{
    capital_owners_->info();
}

// void City::labour_info()
// {
//     labour_market_->info();
// }

void City::employee_info()
{
    employee_info("all");
}

void City::print_company_list()
{
    company_list_->print_list();
}

void City::employee_info(string command)
{
    company_list_->employee_info(command);
}

void City::market_info()
{
    market_->info();
}

void City::bank_info()
{
    bank_->info();
}

void City::print_consumer_list()
{
    consumers_->print_list();
}

void City::print_employees(string company)
{
    company_list_->print_employees(company);
}

// void City::print_labour_market()
// {
//     labour_market_->print_list();
// }

void City::print_GDP()
{

    const int SPACE = 15;
    bool save_to_file = false;

    list<double>::iterator GDP;
    list<double>::iterator Growth;
    list<double>::iterator Investments;
    list<double>::iterator Demand;
    list<double>::iterator Price_out;
    list<double>::iterator Excess_demand_items;
    list<double>::iterator Employed;
    list<double>::iterator Wages;
    list<double>::iterator Time;
    list<double>::iterator Consumer_capital;
    list<double>::iterator Company_capital;
    list<double>::iterator Market_capital;
    list<double>::iterator Bank_capital;
    list<double>::iterator Total_capital;

    list<double>::iterator Interest_rate;

    GDP = GDP_.begin();
    Time = time_.begin();
    Growth = growth_.begin();
    Investments = investments_.begin();
    Demand = demand_.begin();
    Wages = (company_list_->get_company("bempa_AB"))->wages_.begin();
    Price_out = price_out_.begin();
    Excess_demand_items = excess_demand_items_.begin();
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
    cout << name_
         << endl
         << "-----------------------------------------------------" << endl
         << setw(SPACE - 10) << "Time" << setw(SPACE - 1) << "GDP" << setw(SPACE - 2) << "Growth" << setw(SPACE) << "Demand"
         << setw(SPACE) << "Wages" << setw(SPACE) << "Price out" << setw(SPACE) << "Employed"
         << setw(SPACE + 4) << "Consumer_capital" << setw(SPACE + 4) << "Company_cap" << setw(SPACE) << "Invested cap"
         << setw(SPACE) << "Bank cap" << endl;

    for (GDP; GDP != GDP_.end(); GDP++)
    {

        cout << setw(SPACE - 10) << *Time << setw(SPACE - 1) << *GDP << setw(SPACE - 2) << *Growth << setw(SPACE)
             << *Demand << setw(SPACE) << *Wages << setw(SPACE)
             << *Price_out << setw(SPACE) << *Employed << setw(SPACE + 4)
             << *Consumer_capital << setw(SPACE + 4) << *Company_capital << setw(SPACE)
             << *Investments / (*Price_out) << setw(SPACE) << *Bank_capital << endl;

        Time++;
        Demand++;
        Growth++;
        Wages++;
        Price_out++;
        Excess_demand_items++;
        Employed++;
        Consumer_capital++;
        Company_capital++;
        Investments++;
        Bank_capital++;
    }

    /*
     * Printing to file gdp.txt
     */
    if (save_to_file)
    {
        ofstream file("gdp.txt");
        GDP = GDP_.begin();
        Time = time_.begin();
        Investments = investments_.begin();
        Growth = growth_.begin();
        Demand = demand_.begin();
        Wages = (company_list_->get_company("bempa_AB"))->wages_.begin();
        Price_out = price_out_.begin();
        Excess_demand_items = excess_demand_items_.begin();
        Employed = employed_.begin();
        Interest_rate = interest_rate_.begin();
        Market_capital = market_capital_.begin();
        Bank_capital = bank_capital_.begin();
        Total_capital = total_capital_.begin();
        Interest_rate = interest_rate_.begin();

        file << "#time1 gdp2 growth3 demand4 wages5 price6 employed7 company_capital8 consumer_capital9 interest_rate10 investments11 market_capital12 bank_capital13 total_capital14" << endl;
        for (GDP = GDP_.begin(); GDP != GDP_.end(); GDP++)
        {
            file << *Time << " " << *GDP << " " << *Growth << " " << *Demand
                 << " " << *Wages << " " << *Price_out << " " << *Employed
                 << " " << *Consumer_capital << " " << *Company_capital << " " << 10 * (*Interest_rate) << " "
                 << *Investments << " " << *Market_capital << " " << *Bank_capital << " " << *Total_capital << endl;
            Time++;
            Demand++;
            Growth++;
            Wages++;
            Price_out++;
            Excess_demand_items++;
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
}

/*
 * Get-functions
 *
 */

int City::get_time() const
{
    return clock_->get_time();
}

Clock *City::get_clock() const
{
    return clock_;
}

Bank *City::get_bank()
{
    return bank_.get();
}

double City::get_company_capacity_sum()
{
    return company_list_->get_capacity_sum();
}

double City::get_consumer_capital_sum()
{

    return consumers_->get_capital_sum();
}

Market *City::get_market()
{
    return market_.get();
}

Consumer *City::get_random_consumer()
{
    return consumers_->get_random_consumer();
}

Element_consumer *City::get_random_consumers(int number_of_consumers)
{

    Element_consumer *head = nullptr;
    Element_consumer *tail = nullptr;

    for (int i = 0; i < number_of_consumers; i++)
    {
        Consumer *cons = consumers_->get_random_consumer();

        Element_consumer *new_element = new Element_consumer(nullptr, cons);

        if (head == nullptr)
        {
            head = new_element;
            tail = new_element;
        }
        else
        {
            tail->next_ = std::make_unique<Element_consumer>(nullptr, cons);
            tail = tail->next_.get();
        }
    }

    return head;
}

double City::get_capital_sum()
{
    double csum = 0;
    csum = consumers_->get_capital_sum() + company_list_->get_capital_sum() + market_->get_capital() + bank_->get_liquidity() + get_capital(); // bank_ -> get_capital() consumers_ -> get_loans_sum();+ consumers_ -> get_loans_sum()

    return csum;
}

int City::get_no_companies() const
{
    return company_list_->get_size();
}

double City::get_loans_to_bank()
{
    return loans_to_bank_;
}

double City::get_capital() const
{
    return capital_;
}

double City::get_vat() const
{
    return vat_;
}

double City::get_income_tax() const
{
    return income_tax_;
}

double City::get_capital_gains_tax() const
{
    return capital_gains_tax_;
}

double City::get_budget_balance() const
{
    return budget_balance_;
}

double City::get_inflation_target() const
{
    return inflation_target_;
}

double City::get_fac_increase_rate_1() const
{
    return fac_increase_rate_1_;
}

double City::get_cap_increase_param_1() const
{
    return cap_increase_param_1_;
}

double City::get_cap_increase_rate_1() const
{
    return cap_increase_rate_1_;
}

double City::get_item_efficiency_rate() const
{
    return item_efficiency_rate_;
}

int City::get_pay_wage_in_cash() const
{
    return pay_wage_in_cash_;
}

Company *City::get_company(const string &name)
{
    return company_list_->get_company(name);
}

Company *City::get_random_company()
{
    return company_list_->get_random_company()->get_company();
}

Consumer *City::get_optimal_consumer(double mot_we, double skill_we, int production_function, double production_parameter)
{

    double cap_sum = 0;
    double capacity = 0;
    int no_companies = 0;

    cap_sum = get_company_capacity_sum();
    no_companies = get_no_companies();
    capacity = cap_sum / no_companies;

    try
    {
        return (consumers_->get_optimal_consumer(mot_we, skill_we, capacity, production_function, production_parameter));
    }
    catch (no_return_error)
    {
        cout << "No optimal consumer" << endl;
    }
    return 0;
}

double City::get_shareToSteal() const
{
    return shareToSteal_;
}

double City::get_laundry_factor() const
{
    return laundry_factor_;
}

int City::get_no_years_laundry() const
{
    return no_years_laundry_;
}

int City::get_time_to_steal() const
{
    return time_to_steal_;
}

string City::get_name() const
{
    return name_;
}

int City::get_no_consumers() const
{
    return consumers_->get_size();
}

Market *City::get_active_market()
{
    // bool intercity_trading = false;

    // if (clock_ -> get_time()>20) {
    //     intercity_trading = true;
    // }

    if (enable_intercity_trading_)
    {
        return global_market_;
    }
    else
    {
        return market_.get();
    }
}

Market *City::get_global_market()
{

    return global_market_;
}

bool City::get_enable_intercity_trading() const
{
    return enable_intercity_trading_;
}

double City::get_average_excess_demand_items(int average_time) const
{
    list<double>::const_iterator Excess_demand_items;
    Excess_demand_items = excess_demand_items_.begin();

    double sum = 0;
    int count = 0;

    for (Excess_demand_items; Excess_demand_items != excess_demand_items_.end(); Excess_demand_items++)
    {
        if (count < average_time)
        {
            sum += *Excess_demand_items;
            count++;
        }
        else
        {
            break;
        }
    }

    if (count == 0)
    {
        return 0;
    }
    else
    {
        cout << "I City " << name_ << " get average excess demand items over " << count << " periods, sum: " << sum << ", avg: " << sum / count << endl;
        return sum / count;
    }
}

/*
 * Change-functions
 */

void City::change_capital(double ch)
{
    capital_ += ch;
}

/*
 * Set-functions
 */

void City::set_consumers(Consumer_list *consumer_list)
{
    consumers_.reset(consumer_list);
}
void City::set_companies(Company_list *company_list)
{
    company_list_.reset(company_list);
}

void City::set_shareToSteal(double share)
{
    shareToSteal_ = share;
}

void City::set_laundry_factor(double factor)
{
    laundry_factor_ = factor;
}

void City::set_no_years_laundry(int years)
{
    no_years_laundry_ = years;
}

void City::set_time_to_steal(int years)
{
    time_to_steal_ = years;
}

void City::set_vat(double vat)
{
    vat_ = vat;
}

void City::set_income_tax(double income_tax)
{
    income_tax_ = income_tax;
}

void City::set_capital_gains_tax(double capital_gains_tax)
{
    capital_gains_tax_ = capital_gains_tax;
}

void City::set_budget_balance(double budget_balance)
{
    budget_balance_ = budget_balance;
}

void City::set_inflation_target(double inflation_target)
{
    inflation_target_ = inflation_target;
}

void City::set_market(Market *market)
{
    // Changing market for the City
    market_.reset(market);

    // Changing market for all consumers
    consumers_->set_market(market);

    // Changing market for all companies
    company_list_->set_market(market);
}

void City::set_enable_intercity_trading(bool enable)
{
    enable_intercity_trading_ = enable;

    consumers_->set_intecity_trading(enable);

    company_list_->set_intecity_trading(enable);
}

/*
 * Functions for adding consumers and companies to bennyland
 */

void City::add_consumer(Consumer *consumer)
{
    consumers_->add_first(consumer);
}

void City::add_random_consumers(int number_of_consumers)
{

    double money_before = 0;
    money_before = get_capital_sum();

    for (int i = 0; i < number_of_consumers; i++)
    {

        Consumer *benny = random_consumer(name_, market_.get(), global_market_, bank_.get(), clock_);
        benny->set_name("Consumer" + std::to_string(i));
        add_consumer(benny);
    }

    cout << "I City, added consumers, total numeber of consumers: " << consumers_->get_size() << endl;
}

void City::add_random_consumers(int number_of_consumers, double capital)
{

    double money_before = 0;
    money_before = get_capital_sum();

    for (int i = 0; i < number_of_consumers; i++)
    {

        Consumer *benny = random_consumer(name_, market_.get(), global_market_, bank_.get(), clock_);
        benny->set_name("Consumer" + std::to_string(i));
        benny->set_capital(capital);
        add_consumer(benny);
    }

    cout << "I City, added consumers, total numeber of consumers: " << consumers_->get_size() << endl;
}

void City::add_capital_owners(double share_of_population)
{
    int total_number_of_consumers = 0;
    int number_of_capital_owners = 0;

    cout << "Adding capital owners, " << share_of_population * 100 << " % of population" << endl;

    total_number_of_consumers = consumers_->get_size();

    number_of_capital_owners = total_number_of_consumers * fmin(1, share_of_population);

    for (int i = 0; i < number_of_capital_owners; i++)
    {

        Consumer *consumer = consumers_->get_random_consumer();
        capital_owners_->add_first(consumer);
    }

    cout << "I city add cap owners, added: " << capital_owners_->get_size() << " capital owners" << endl;
}

void City::add_random_shareholders(int number_of_shareholders)
{

    // looping over all the companies and adding random shareholders
    // Using the function get company_by_index to get all companies
    // the number of companies is get_no_companies(), looping from 0 to number of companies -1
    int numbe_of_companies = get_no_companies();
    for (int i = 0; i < numbe_of_companies; i++)
    {
        Company *company = company_list_->get_company_by_index(i);

        Element_consumer *new_shareholders = get_random_consumers(number_of_shareholders);

        company->add_multiple_shareholders(new_shareholders);

        // company -> print_shareholders();

        cout << "I city add random shareholders, added: " << number_of_shareholders << " shareholders to company " << company->get_name() << endl;
    }
}

void City::add_company(Company *company)
{
    company_list_->add_company(company);
}

void City::add_company(string name)
{
    Company *company = new Company(name, market_.get(), global_market_, clock_);
    company_list_->add_company(company);
}

double City::invest_in_new_company(string nameactual, double capital)
{

    double max_capital = 0;
    int capital_owner_size = 0;

    // Getting max investment
    max_capital = capital_owners_->get_capital_sum();
    capital = fmax(fmin(capital, max_capital), 0);

    // Number of investrs
    capital_owner_size = capital_owners_->get_size();

    // Creating a new company from file
    load_company(nameactual);

    // Setting capital to new company
    company_list_->get_company(nameactual)->set_capital(capital);

    // Charging capital owners with "reverse dividend"
    capital_owners_->pay_dividends_log(-capital / capital_owner_size, nameactual);

    cout << "Added company" << endl;
    company_list_->get_company(nameactual)->info();

    return capital;
}

void City::load_company(string nameactual)
{

    double capital = 0;
    long stock = 0;
    double capacity = 0;
    double debts = 0;
    double p_c_skill = 0;
    double p_c_mot = 0;
    double wage_const = 0;
    double wage_change_limit = 0;
    double invest = 0;
    double pbr = 0;
    double decay = 0;
    int production_function;
    string name;

    string line;
    char char_name[100];

    strcpy(char_name, nameactual.c_str());

    ifstream myfile(char_name);
    if (myfile.is_open())
    {
        getline(myfile, line);
        name = line;

        getline(myfile, line);
        strcpy(char_name, line.c_str());
        capital = atof(char_name);

        getline(myfile, line);
        strcpy(char_name, line.c_str());
        stock = atof(char_name);

        getline(myfile, line);
        strcpy(char_name, line.c_str());
        capacity = atof(char_name);

        getline(myfile, line);
        strcpy(char_name, line.c_str());
        debts = atof(char_name);

        getline(myfile, line);
        strcpy(char_name, line.c_str());
        p_c_skill = atof(char_name);

        getline(myfile, line);
        strcpy(char_name, line.c_str());
        p_c_mot = atof(char_name);

        getline(myfile, line);
        strcpy(char_name, line.c_str());
        wage_const = atof(char_name);

        getline(myfile, line);
        strcpy(char_name, line.c_str());
        wage_change_limit = atof(char_name);

        getline(myfile, line);
        strcpy(char_name, line.c_str());
        invest = atof(char_name);

        getline(myfile, line);
        strcpy(char_name, line.c_str());
        pbr = atof(char_name);

        getline(myfile, line);
        strcpy(char_name, line.c_str());
        decay = atof(char_name);

        getline(myfile, line);
        strcpy(char_name, line.c_str());
        production_function = atof(char_name);
    }
    else
    {
        cout << "Unable to open file" << endl;
    }
    // cout << "I city load_company(String) capital =  " << capital << " wc " << wage_const <<  endl;
    // cout << " name " << name << " capital " << capital << " stock " << stock << " capacity " << capacity << " mot " << p_c_mot << " skill " << p_c_skill << " wage_const " << wage_const << " pbr " << pbr << " wcl " << wage_change_limit << " decay " << decay << endl;
    // pbr = 0.3;
    wage_const = 0.7;
    cout << "I city load company - fixing pbr to " << pbr << "and wage const to " << wage_const << endl;
    add_company(new Company(nameactual, name_, capital, stock, capacity, p_c_skill, p_c_mot, wage_const, pbr, market_.get(), global_market_, bank_.get(), clock_));
}

void City::load_launder_parameters()
{

    // double shareToSteal;
    // double laundry_factor;
    // double no_years_laundry;
    // double time_to_steal;

    string nameactual = "launder_parameters.txt";

    string line;
    char char_name[100];

    strcpy(char_name, nameactual.c_str());

    ifstream myfile(char_name);
    if (myfile.is_open())
    {

        // getline (myfile,line);
        // name = line;

        getline(myfile, line);
        strcpy(char_name, line.c_str());
        shareToSteal_ = atof(char_name);

        getline(myfile, line);
        strcpy(char_name, line.c_str());
        laundry_factor_ = atof(char_name);

        getline(myfile, line);
        strcpy(char_name, line.c_str());
        no_years_laundry_ = atof(char_name);

        getline(myfile, line);
        strcpy(char_name, line.c_str());
        time_to_steal_ = atof(char_name);
    }

    else
    {
        cout << "Unable to open file" << endl;
    }

    // cout << "I functions load parameters" << endl << "sts: " << shareToSteal_ << endl << "lf: " << laundry_factor_ << endl << "years: " << no_years_laundry_ << endl << "ttts: " << time_to_steal_ << endl;

    // return param{shareToSteal, laundry_factor, no_years_laundry, time_to_steal};
}

/*
 * Functions to update Bennyland. Note that update_market() is old and not in use.
 * The update_company_employees() is also not in use
 */

void City::update_supply_and_demand()
{

    double demand = 0;
    double consumer_demand = 0;
    double investment_demand = 0;
    // double expected_investment = 0;
    double production_demand = 0;
    double market_items = 0;
    double market_excess_demand = 0;
    double company_items = 0;
    double company_planned_production = 0;

    double aggregate_demand = 0;
    double aggregate_supply = 0;

    double marginal = 0;
    double items = 0;
    double price_out = 0;
    double price_in = 0;
    double price_old = 0;
    int size = 0;
    int number_of_market_participants = 0;
    // int i = 0;
    list<double>::iterator invest; // = NULL;//list::end();

    invest = investments_.begin();
    marginal = get_active_market()->get_marginal();
    size = consumers_->get_size();
    price_out = get_active_market()->get_price_out();
    price_old = price_out;
    number_of_market_participants = fmax(get_active_market()->get_number_of_participants(), 1);

    // Getting demand from participants
    consumer_demand = consumers_->get_total_demand();                                                                                                            //*demand_.begin(); //
    investment_demand = company_list_->get_investment_sum(fac_increase_rate_1_, cap_increase_param_1_, cap_increase_rate_1_, item_efficiency_rate_) * price_out; //*investments_.begin();        //average_investment;//price_out*(company_list_ -> get_investment_sum());//*investments_.begin();//
    production_demand = (company_list_->get_items_for_production_sum()) * price_out;
    // market_excess_demand = (get_active_market()->get_excess_demand_items()/number_of_market_participants) * price_out;
    market_excess_demand = (get_average_excess_demand_items(3) / number_of_market_participants) * price_out;
    // Getting avilable items;
    company_items = company_list_->get_item_sum();
    company_planned_production = company_list_->get_planned_production_sum();
    market_items = get_active_market()->get_items();

    demand = consumer_demand + production_demand + investment_demand + market_excess_demand;

    items = market_items + company_items + company_planned_production;

    // price_out = demand / items;
    // price_in = price_out / (1 + marginal);

    // Printing market aggregate supply and demand
    cout << "I City " << name_ << " update supply and demand"
         << " Tot dmd: " << get_active_market()->get_aggregate_demand() << "$BJ, items " << get_active_market()->get_aggregate_supply() << ", makt excess dmd: " << market_excess_demand << " Price: " << price_out << " P. without exc.: " << (demand - market_excess_demand) / items << "market it: " << market_items << " comp it " << company_items << " comp planned " << company_planned_production << endl;

    get_active_market()->change_aggregate_demand(demand);
    get_active_market()->change_aggregate_supply(items);
    get_active_market()->change_number_of_participants(1); // Adding one market participant, the city

    aggregate_demand = get_active_market()->get_aggregate_demand();
    aggregate_supply = get_active_market()->get_aggregate_supply();

    cout << "I City " << name_ << " update supply and demand"
         << " Tot dmd: " << demand << "$BJ, items " << items << ", makt excess dmd: " << market_excess_demand << " Price: " << price_out << " P. without exc.: " << (demand - market_excess_demand) / items << " market items: " << market_items << " comp it " << company_items << " comp planned " << company_planned_production << endl
         << "Aggregate demand: " << aggregate_demand << ", Aggregate supply: " << aggregate_supply << endl;

    // Save excess demand items to historical list
    excess_demand_items_.push_front(get_active_market()->get_excess_demand_items());
}

void City::update_market_price()
{

    double aggregate_supply = 0;
    double aggregate_demand = 0;
    double price_out = 0;
    double market_excess_demand = 0;

    // Getting aggregate supply and demand from market

    aggregate_demand = get_active_market()->get_aggregate_demand();
    aggregate_supply = get_active_market()->get_aggregate_supply();
    // market_excess_demand = get_active_market() -> get_excess_demand_items();
    market_excess_demand = get_average_excess_demand_items(3);

    price_out = (aggregate_demand + market_excess_demand) / aggregate_supply;

    cout << "I City update price"
         << " Tot dmd: " << aggregate_demand << "$BJ, items " << aggregate_supply << ", makt excess dmd: " << market_excess_demand << " Price: " << price_out << endl;

    get_active_market()->set_price_out(price_out);

    // cout << "I city neg market price, price: " << price_out << endl;
}

void City::reset_supply_and_demand()
{
    get_active_market()->reset_excess_demand_items();
    get_active_market()->reset_aggregate_demand_and_supply();
}

void City::negotiate_market_price()
{

    double demand = 0;
    double consumer_demand = 0;
    double investment_demand = 0;
    // double average_investment = 0;
    double expected_investment = 0;
    double production_demand = 0;
    double market_items = 0;
    double market_excess_demand = 0;
    double company_items = 0;
    double company_planned_production = 0;
    double marginal = 0;
    double items = 0;
    double price_out = 0;
    double price_in = 0;
    double price_old = 0;
    int size = 0;
    // int i = 0;
    list<double>::iterator invest; // = NULL;//list::end();

    invest = investments_.begin();
    // demand = demand_.begin();
    marginal = get_active_market()->get_marginal();
    size = consumers_->get_size();
    price_out = get_active_market()->get_price_out();
    price_old = price_out;
    // for (int i = 0; i < 4; i++) {

    //   for(i; i < 4; i++) {
    //     average_investment += *invest;
    //   invest++;
    // }
    // average_investment = average_investment/i;
    //   expected_investment = (1 - *investmnts_.begin()/average_investment);

    // Getting demand from participants
    consumer_demand = consumers_->get_total_demand();                                                                                                            //*demand_.begin(); //
    investment_demand = company_list_->get_investment_sum(fac_increase_rate_1_, cap_increase_param_1_, cap_increase_rate_1_, item_efficiency_rate_) * price_out; //*investments_.begin();        //average_investment;//price_out*(company_list_ -> get_investment_sum());//*investments_.begin();//
    production_demand = (company_list_->get_items_for_production_sum()) * price_out;
    market_excess_demand = (get_active_market()->get_excess_demand_items()) * price_out;

    // Getting avilable items;
    company_items = company_list_->get_item_sum();
    company_planned_production = company_list_->get_planned_production_sum();
    market_items = market_->get_items();

    demand = consumer_demand + production_demand + investment_demand + market_excess_demand;

    items = market_items + company_items + company_planned_production;

    price_out = demand / items;
    price_in = price_out / (1 + marginal);

    cout << "I City neg. price"
         << " Tot dmd: " << demand << "$BJ, items " << items << ", makt excess dmd: " << market_excess_demand << " Price: " << price_out << " P. without exc.: " << (demand - market_excess_demand) / items << "market it: " << market_items << " comp it " << company_items << " comp planned " << company_planned_production << endl;

    market_->set_price_out(price_out);

    // cout << "I city neg market price, price: " << price_out << endl;
    market_->reset_excess_demand_items();

    // market_ -> set_price_in(price_in);
    // cout << "I city neg price, planned investment: " << investment_demand << " $BJ at the price: " << price_old << endl << "And planned production: " << company_planned_production  << endl << "   And planned demand: " << consumer_demand << endl;
    //       cout << "I city negotiate, price out: " << price_out << "  demand tot, $BJ:  " << demand << "  items tot:  " << items << endl
    //    << "cons demand: " << consumer_demand << "  investment_demand: " << investment_demand << "  prod dmeand: " << production_demand
    //    << endl
    //    << "market_items: " << market_items << "  company_items: " << company_items << "  planned production: " << company_planned_production
    //    << endl;

    //}
}

void City::update_consumer_list()
{

    double set_avg_spendwill = 0;
    double set_avg_borrowwill = 0;

    set_avg_spendwill = getDatabaseParameter("'AverageSpendwill'", name_);
    set_avg_borrowwill = getDatabaseParameter("'AverageBorrowwill'", name_);

    cout << "I City Updating consumers, setting average spendwill to: " << set_avg_spendwill << endl;
    cout << "I City Updating consumers, setting average borrowwill to: " << set_avg_borrowwill << endl;

    // double test = getDatabaseParameter("AverageSpendwill");

    consumers_->update(set_avg_spendwill, set_avg_borrowwill);
}

void City::update_companies()
{
    company_list_->update_companies();
}

void City::update_interest_rate()
{

    int counter = 0;

    double interest = 0.05;
    double target_interest = 0;
    double prev_interest = 0.05;
    double initial_interest = 0;
    double ir_change_factor = 0.3;
    double est_ir_change = 0.005;
    double best_iterest_so_far = 0;

    double consumer_sum = 0;
    double minumum_flow_so_far = 0;
    double company_sum = 0;
    double bank_sum = 0;
    double max_bank_borrow_to_consumers = 0;

    double diff_limit = 10000; // 500 works fine
    double sum_flows_to_bank = 0;
    double prev_flows_to_bank = 0;
    double initial_flows_to_bank = 0;

    double delta_sum = 0;
    double d_sum_di = 1;
    double max_interest_rate = 0.5;
    double ir_delta = 0.0005;
    int number_of_iterations = 20; // 20 works fine
    int ir_method_select = 1;

    cout << endl
         << "Updating interest rate" << endl
         << endl;

    // Reading interest rates
    ir_method_select = bank_->get_interest_rate_method();
    target_interest = bank_->get_target_interest();
    interest = bank_->get_interest();
    initial_interest = interest;
    prev_interest = interest;
    max_bank_borrow_to_consumers = bank_->get_max_customer_borrow();

    // Interest rate method, target or market
    switch (ir_method_select)
    {
    case 1: // Market interest rate
        cout << "Using Market Interest method" << endl;
        // Calculating capital sums

        consumer_sum = consumers_->get_expected_net_flow_to_bank_sum();
        company_sum = company_list_->get_expected_net_flow_to_bank_sum(fac_increase_rate_1_, cap_increase_param_1_, cap_increase_rate_1_, item_efficiency_rate_);
        bank_sum = (bank_->get_sum_to_borrow());

        break;

    case 2: // Target interest rate
        cout << "Using Target Interest method" << endl;
        bank_->set_interest(target_interest);
        company_sum = company_list_->get_expected_net_flow_to_bank_sum(fac_increase_rate_1_, cap_increase_param_1_, cap_increase_rate_1_, item_efficiency_rate_);
        consumer_sum = consumers_->get_expected_net_flow_to_bank_sum();

        bank_sum = fmin(-(consumer_sum + company_sum), max_bank_borrow_to_consumers);
        cout << "Target interest rate: " << target_interest << " comp & cons sum: " << company_sum + consumer_sum << " bank sum: " << bank_sum << " bank max: " << max_bank_borrow_to_consumers << endl;

        break;
    }

    // Getting estimated flows to the bank before interest change
    sum_flows_to_bank = consumer_sum + company_sum + bank_sum;
    initial_flows_to_bank = sum_flows_to_bank;
    prev_flows_to_bank = sum_flows_to_bank;

    cout << "In city upd. flows to bank ir: " << interest << "  cons sum " << setw(6) << consumer_sum << " comp sum " << company_sum << " bank sum " << bank_sum << " tot flow " << sum_flows_to_bank << endl;

    // If we are outside tolerance (diff_limit), do something, else do nothing
    if (abs(sum_flows_to_bank) > abs(diff_limit))
    {

        // cout << "I City update interest, interest needs to be updated" << endl;

        // Setting ir_change_factor
        if (sum_flows_to_bank > 0)
        {
            est_ir_change = -interest / 10;
        }
        else
        {
            est_ir_change = interest / 10;
        }

        // Updating interest rate
        bank_->change_interest(est_ir_change);
        interest = bank_->get_interest();

        // If max interest rate setting interest to max_interest/2
        if (interest >= max_interest_rate)
        {
            interest = max_interest_rate / 2;
        }
    }

    while (abs(sum_flows_to_bank) > diff_limit && counter < number_of_iterations && interest < max_interest_rate)
    {
        // Getting cash-flows after initial interest change
        consumer_sum = consumers_->get_expected_net_flow_to_bank_sum();

        company_sum = company_list_->get_expected_net_flow_to_bank_sum(fac_increase_rate_1_, cap_increase_param_1_, cap_increase_rate_1_, item_efficiency_rate_);

        // COMMENT THIS LINE IN TO GET BACK TO NON-TARGET IR SETTING
        // bank_sum = (bank_ -> get_sum_to_borrow());

        // Updating flows to bank
        prev_flows_to_bank = sum_flows_to_bank;
        sum_flows_to_bank = consumer_sum + company_sum + bank_sum;

        // Calculating cash-flow deltas after interest update
        // delta_sum = (consumer_sum + company_sum + bank_sum) - sum_flows_to_bank;
        delta_sum = sum_flows_to_bank - prev_flows_to_bank;
        ir_delta = (prev_interest - interest);

        // If flows to bank increases we have risk of divergence, changing back half a step
        if (abs(prev_flows_to_bank) <= abs(sum_flows_to_bank))
        {

            cout << "In city upd. re, divergence: " << counter << " interest: " << interest << " prev flows: " << prev_flows_to_bank << "  and new flows " << sum_flows_to_bank << endl;
            // Changing back interest rate half way
            bank_->change_interest(-est_ir_change * ir_change_factor / 2);

            // Updating cashflows
            consumer_sum = consumers_->get_expected_net_flow_to_bank_sum();
            company_sum = company_list_->get_expected_net_flow_to_bank_sum(fac_increase_rate_1_, cap_increase_param_1_, cap_increase_rate_1_, item_efficiency_rate_);

            prev_flows_to_bank = sum_flows_to_bank;
            sum_flows_to_bank = consumer_sum + company_sum + bank_sum;
            delta_sum = sum_flows_to_bank - prev_flows_to_bank;

            ir_delta = est_ir_change * ir_change_factor / 2;
            cout << "In city upd. re, divergence: " << counter << " interest: " << bank_->get_interest() << " prev flows: " << prev_flows_to_bank << "  and new flows " << sum_flows_to_bank << endl;
        }

        if (ir_delta == 0)
        {
            // cout << "I city updte IR, IR delta: " << ir_delta << " Prev: " << prev_interest << " Current: " << interest << endl;
            ir_delta = est_ir_change;
        }

        d_sum_di = delta_sum / ir_delta;
        // d_sum_di = delta_sum/(prev_interest - interest);

        if (d_sum_di == 0)
        {
            cout << "d_sum_di: " << d_sum_di << " Counter " << counter << " ir: " << interest << "  cons sum " << consumer_sum << " comp sum " << company_sum << " bank sum " << bank_sum << " tot flow " << sum_flows_to_bank << " delta sum: " << delta_sum << endl;
            d_sum_di = 100000;
        }

        est_ir_change = sum_flows_to_bank / d_sum_di;
        // cout << fixed << setprecision(2) << setfill(' ');

        cout << "In city upd. flows to bank ir: " << counter << " ir: " << interest << "  cons sum " << setw(6) << consumer_sum << " comp sum " << company_sum << " bank sum " << bank_sum << " tot flow " << sum_flows_to_bank << endl;

        // Changint interest rate
        prev_interest = interest;
        bank_->change_interest(est_ir_change * ir_change_factor);
        interest = bank_->get_interest();

        counter = counter + 1;
    }

    // If interest above max interest
    if (interest > max_interest_rate)
    {
        cout << "I city update interest rate, setting max rate of: " << max_interest_rate << " was " << interest << endl;
        bank_->set_interest(max_interest_rate);
    }
    else if (-interest > max_interest_rate)
    {
        cout << "I city update interest rate, setting negative max rate of: " << -max_interest_rate << " was " << interest << endl;
        bank_->set_interest(-max_interest_rate);
    }

    // If divergence and initial interest better than final
    if (abs(initial_flows_to_bank) < abs(sum_flows_to_bank) && counter == 20)
    {
        cout << "Final divergence and worse than initial IR, setting initial IR of: " << initial_interest << " vs " << interest << " and initial flows: " << initial_flows_to_bank << " vs flows " << sum_flows_to_bank << endl;
        bank_->set_interest(initial_interest);
    }

    cout << "I city update interest rate "
         << "Market rate: " << interest << "  Total cashflow to bank: " << sum_flows_to_bank << "   Company sum: " << company_sum << "  consumer_sum: " << consumer_sum << "    Bank sum: " << bank_sum << endl;
}

void City::update_employees()
{

    string name = "";
    double skill = 0;
    double mot = 0;
    int prod_fcn = 1;
    double prod_param = 0.001;
    int no_consumers_hired = 0;
    Consumer *opt = 0;

    /*
     * Starting by removing all the employees that are not profitable to keep
     */

    company_list_->remove_usless_employees();
    cout << "I City update emplyees" << endl;

    /*
     * A company does not always hire the optimal consumer first. A random company is selected
     * and asked if it wants to hire the consumer optimal for its conditions. If not hired other
     * companies are asked if they want to hire the consumer, and sometimes they may, even though
     * there might be other conusmers more optimal for them...
     */

    name = get_random_company()->get_name();
    cout << "Name: " << name << endl;
    skill = get_company(name)->get_prod_const_skill();
    mot = get_company(name)->get_prod_const_motivation();
    prod_fcn = get_company(name)->get_production_function();
    prod_param = get_company(name)->get_production_parameter();

    while (company_list_->update_employees2(opt = get_optimal_consumer(mot, skill, prod_fcn, prod_param)))
    {
        no_consumers_hired++;
        // cout << "I City update employees, hired a total of: " << no_consumers_hired << " employees" << endl;
    }
    cout << "I City update employees, hired a total of: " << no_consumers_hired << " employees" << endl;

    // Employees looking for new jobs every 10(?) years
    if ((clock_->get_time()) % 10 == 0)
    {
        Element_consumer *p;

        p = consumers_->get_first_consumer();

        if (p)
        {
            for (p; p->next_; p = p->next_.get())
            {

                company_list_->update_employees2(p->get_consumer());
            }
        }
    }
}

void City::update_employees2()
{

    string name = "";
    double skill = 0;
    double mot = 0;
    int prod_fcn = 1;
    double prod_param = 0.001;
    int no_consumers_hired = 0;
    int job_change_frequency = 10; // Years between job changes
    Consumer *opt = 0;

    /*
     * Starting by removing all the employees that are not profitable to keep
     */

    company_list_->remove_usless_employees();
    cout << "I City update emplyees" << endl;

    // Employees looking for new jobs - distributed approach (1/10 per year instead of all every 10 years)
    int total_consumers = consumers_->get_size();
    if (total_consumers > 0)
    {
        int current_year = clock_->get_time();
        int year_position = current_year % job_change_frequency;
        int consumers_per_year = total_consumers / job_change_frequency;
        int start_position = year_position * consumers_per_year;
        int end_position = start_position + consumers_per_year;

        // Handle remainder for last year of cycle
        if (year_position == job_change_frequency - 1)
        {
            end_position = total_consumers;
        }

        Element_consumer *p = consumers_->get_first_consumer();
        int current_position = 0;

        // Navigate to start position
        while (p && current_position < start_position)
        {
            p = p->next_.get();
            current_position++;
        }

        // Process consumers in this year's range
        while (p && current_position < end_position)
        {
            company_list_->update_employees2(p->get_consumer());
            p = p->next_.get();
            current_position++;
        }

        cout << "I City update employees2, processed consumers " << start_position << " to " << (end_position - 1)
             << " (year " << year_position << " of " << job_change_frequency << " cycle)" << endl;
    }
}

void City::tick()
{
    clock_->tick();
}

void City::save_data()
{

    double demand = 0;
    double growth = 0;
    double item = 0;
    int time = 0;
    // double gdp = 0;
    double nominal_gdp = 0;
    double price_out = 0;
    double interest_rate = 0;
    double capital_reserve_ratio = 0;
    double liquidity_reserve_ratio = 0;
    double bank_dividend_ratio = 0;
    double unemployment = 0;
    double employed = 0;
    double unemployed = 0;
    double size = 0;
    double wages = 0;
    double investments = 0;
    double excess_demand_items = 0;
    list<double>::iterator GDP;
    list<double>::iterator Time;
    std::vector<double> time_data;

    demand = consumers_->get_spendwill_sum() * consumers_->get_capital_sum();
    item = company_list_->get_item_sum();
    price_out = get_active_market()->get_price_out();
    excess_demand_items = get_active_market()->get_excess_demand_items();
    interest_rate = bank_->get_interest();
    liquidity_reserve_ratio = bank_->get_liquidity_reserve_ratio();
    capital_reserve_ratio = bank_->get_capital_reserve_ratio();
    bank_dividend_ratio = bank_->get_dividend_ratio();

    size = consumers_->get_size();
    employed = consumers_->get_employed();
    unemployed = consumers_->get_unemployed();
    unemployment = unemployed / size;
    wages = company_list_->get_average_wage(); //*((company_list_->get_company("bempa_AB"))->wages_.begin());
    nominal_gdp = price_out * item;
    GDP = GDP_.begin();
    time = clock_->get_time();
    investments = *investments_.begin();

    if (*GDP != 0)
    {
        growth = (item - *GDP) / (*GDP);
    }
    else
    {
        growth = 0;
    }

    cout << "I city save data, employed: " << employed << " unemployed: " << unemployed << " unemployment: " << unemployed / size << " size: " << size << endl;
    // file2 << time << " " << item << " " << growth << " " << demand << " " << price_out << " "
    //<< employed << " " << wages << " " << 100*interest_rate << " " << investments << " " << nominal_gdp << endl;

    // Populating vector for database storage
    time_data.push_back((double)time);
    time_data.push_back((double)item);
    time_data.push_back((double)demand);
    time_data.push_back((double)price_out);
    time_data.push_back((double)unemployment);
    time_data.push_back((double)wages);
    time_data.push_back((double)interest_rate);
    time_data.push_back((double)investments);
    time_data.push_back((double)nominal_gdp);
    time_data.push_back((double)liquidity_reserve_ratio);
    time_data.push_back((double)capital_reserve_ratio);
    time_data.push_back((double)bank_dividend_ratio);

    try
    {
        insertTimeData(time_data, name_);
    }
    catch (exception &e)
    {
        cout << "Error: " << e.what() << endl;
    }

    GDP_.push_front(item);
    growth_.push_front(growth);
    demand_.push_front(demand);
    price_out_.push_front(price_out);
    employed_.push_front(employed);
    time_.push_front(clock_->get_time());
    interest_rate_.push_front(interest_rate);

    bool saveToFile = 0;
    if (saveToFile)
    {
        ofstream file2("gdp_test.txt", ios::app);
        file2 << time << " " << item << " " << growth << " " << demand << " " << price_out << " "
              << employed << " " << wages << " " << 100 * interest_rate << " " << investments << " " << nominal_gdp << endl;

        file2.close();
    }
}

void City::save_money_data()
{

    double consumer_capital = 0;
    double company_capital = 0;
    double city_capital = 0;
    double company_debts = 0;
    double bank_capital = 0;
    double bank_loans = 0;
    double bank_deposits = 0;
    double bank_liquidity = 0;
    double market_capital = 0;
    double total_capital = 0;
    double time = 0;
    double consumer_debts = 0;
    double consumer_deposits = 0;
    std::vector<int> money_data;
    list<double>::iterator Money_start;
    double money_start = 0;
    Money_start = total_capital_.end();

    money_start = *Money_start;

    consumer_capital = consumers_->get_capital_sum();
    consumer_debts = consumers_->get_debts_sum();
    consumer_deposits = consumers_->get_deposit_sum();

    company_capital = company_list_->get_capital_sum();
    company_debts = company_list_->get_debts_sum();

    city_capital = get_capital();

    bank_capital = bank_->get_capital();
    bank_liquidity = bank_->get_liquidity();
    bank_loans = bank_->get_loans();
    bank_deposits = bank_->get_deposits();

    market_capital = get_active_market()->get_capital();

    total_capital = get_capital_sum(); //    csum = consumers_ -> get_capital_sum() + company_list_ -> get_capital_sum() + market_ -> get_capital() + bank_ -> get_liquidity();//bank_ -> get_capital() consumers_ -> get_loans_sum();+ consumers_ -> get_loans_sum()
    time = clock_->get_time();

    // Populating vector for database storage
    money_data.push_back((int)time);
    money_data.push_back((int)bank_capital);
    money_data.push_back((int)bank_loans);
    money_data.push_back((int)bank_deposits);
    money_data.push_back((int)bank_liquidity);
    money_data.push_back((int)consumer_capital);
    money_data.push_back((int)consumer_deposits);
    money_data.push_back((int)consumer_debts);
    money_data.push_back((int)company_debts);
    money_data.push_back((int)company_capital);
    money_data.push_back((int)market_capital);
    money_data.push_back((int)city_capital);
    money_data.push_back((int)total_capital);

    try
    {
        insertMoneyData(money_data, name_);
    }
    catch (exception &e)
    {
        cout << "Error: " << e.what() << endl;
    }

    bank_capital_.push_front(bank_capital);
    consumer_capital_.push_front(consumer_capital);
    company_capital_.push_front(company_capital);
    market_capital_.push_front(market_capital);
    total_capital_.push_front(total_capital);

    bool saveToFile = 0;
    if (saveToFile)
    {
        ofstream file2("money_test.txt", ios::app);
        file2 << time << " " << bank_capital << " " << bank_loans << " " << bank_deposits << " " << consumer_capital << " "
              << company_capital << " " << market_capital << " " << total_capital << " " << consumer_debts << " " << consumer_deposits << " " << company_debts << " " << bank_liquidity << " " << city_capital << " " << loans_to_bank_ + money_start << endl;
    }
}

/*
 * save_flash(double time) registrerar alla transaktioner i bennyland i ett tidsschema s� att man kan se hur
 * pengar fl�dar mellan olika instanser under en "m�nad".
 */

void City::save_flash(int time)
{
    int timec = 0;
    timec = clock_->get_time();
    bool write_to_file = false;
    // If right time, do everything, else, do nothing  && timec < time + 10
    if (timec >= time)
    {
        double consumer_capital = 0;
        double company_capital = 0;
        double bank_capital = 0;
        double market_capital = 0;
        double total_capital = 0;

        consumer_capital = consumers_->get_capital_sum();
        company_capital = company_list_->get_capital_sum();
        bank_capital = bank_->get_capital();
        market_capital = get_active_market()->get_capital();
        total_capital = get_capital_sum();

        if (write_to_file)
        {
            ofstream flash("flash.txt", ios::app);

            flash << flash_counter_ << " " << consumer_capital << " " << company_capital << " "
                  << market_capital << " " << bank_capital << " " << total_capital << endl;
            flash_counter_++;
        }
    }
}

/*
 * Functions to update Bennyland. Note that update_market() is old and not in use.
 * The update_company_employees() is also not in use
 */

void City::produce()
{

    double production_items = 0;
    double price = 0;

    price = get_active_market()->get_price_out();

    production_items = company_list_->produce(name_);

    cout << "Actual production: " << production_items * price << " $BJ and items: " << production_items << " at price: " << price << endl;
}

void City::sell_to_market()
{
    company_list_->sell_to_market();
}

void City::consumers_buy()
{

    double demand_money = 0;
    double price = 0;

    price = get_active_market()->get_price_out();

    demand_money = consumers_->consumers_buy();

    cout << "Consumer demand: " << demand_money << " $BJ and items: " << demand_money / price << endl;
}

void City::invest(bool invest)
{
    double invested_capital = 0;
    double price = 0;

    cout << endl
         << "Companies investing" << endl
         << endl;

    price = get_active_market()->get_price_out();

    if (invest)
    {
        invested_capital = company_list_->invest(fac_increase_rate_1_, cap_increase_param_1_, cap_increase_rate_1_, item_efficiency_rate_);
    }

    investments_.push_front(invested_capital);
    cout << "I city invest, invested_capital: " << invested_capital << "  Items: " << invested_capital / price << "  At the price: " << price << endl;
}

void City::adjust_money()
{

    double money_change = 0;
    double total_money = 0;
    double average_price = 0;
    double average_items = 0;
    double average_wage = 0;
    double money_change_factor = 0;
    double bank_money = 0;
    double inflation = 0;
    double item_inflation = 0;
    double scale_factor = 0.5; // 0.5
    double target_inflation = 0;

    double MAX_CHANGE_FACTOR = 0.6;

    /*
     *
     * Use function select to select money function
     *
     */

    int function_select = 3; // 3
    int payment_function_select = 1;

    int i = 0;
    int number_of_companies = 0;
    int average_history = 6;
    double items_a = 0;
    double price_a = 0;
    double wages_a = 0;
    double average_wage_now = 0;
    double average_wage_historical = 0;

    double sum = 0;
    double sum_items = 0;

    list<double>::iterator Price_out;
    list<double>::iterator Items;
    list<double>::iterator Wages;

    Price_out = price_out_.begin();
    Items = GDP_.begin();

    Wages = ((company_list_->get_company("bempa_AB"))->wages_.begin());

    total_money = get_capital_sum();
    bank_money = bank_->get_capital();

    // Function 1

    items_a = *Items;
    Items = GDP_.begin();

    for (i = 0; i < 4; i++)
    {
        sum_items += *Items;
        Items++;
        // cout << i << " i and items"<<  *Items << endl;
    }

    average_items = sum_items / i;

    // Function 2

    price_a = *Price_out;
    Price_out = price_out_.begin();

    sum = 0;
    for (i = 0; i < 5; i++)
    {
        sum += *Price_out;
        Price_out++;
    }

    average_price = sum / i;

    // Function 3
    // OLD CODE - REMOVE!
    wages_a = *Wages;
    Wages = ((company_list_->get_company("bempa_AB"))->wages_.begin());

    sum = 0;
    for (i = 0; i < 4; i++)
    {
        sum += *Wages;
        Wages++;
    }

    average_wage = sum / i;
    // average_wage = company_list_ -> get_average_wage();

    // cout << "I city adjust money, money change function " << function_select << endl;

    switch (function_select)
    {
    case 1:
        item_inflation = (1 - average_items / items_a);
        inflation = -item_inflation;
        break;

    case 2:

        inflation = price_a / average_price - 1;

        break;

    case 3:

        // Checking for 0 average wage

        average_wage_now = company_list_.get()->get_average_wage();
        average_wage_historical = company_list_.get()->get_average_wage_historical(average_history);

        cout << "I City adjust money, using wage inflation, average now = " << average_wage_now << " average historical = " << average_wage_historical << endl;
        if (average_wage_historical != 0)
        {
            inflation = average_wage_now / average_wage_historical - 1;
        }
        else
        {
            average_wage_historical = 1; // To avoid division by zero
            inflation = average_wage_now / average_wage_historical - 1;
            cout << "Warning: Average wage historical is zero, setting to 1 to avoid division by zero" << endl;
        }
        break;

    default:
        break;
    }

    money_change_factor = -inflation + inflation_target_;

    if (money_change_factor > MAX_CHANGE_FACTOR)
    {
        money_change_factor = MAX_CHANGE_FACTOR;
        cout << "I City adjust money, reaching max change factor" << endl;
    }
    else if (-money_change_factor > MAX_CHANGE_FACTOR)
    {
        money_change_factor = -MAX_CHANGE_FACTOR;
        cout << "I City adjust money, reaching max change factor" << endl;
    }

    if (clock_->get_time() < 10)
    {
        money_change_factor = 0;
    }

    money_change = total_money * money_change_factor * scale_factor;

    cout << "I city adj. money, inflation: " << inflation << " target: " << inflation_target_ << " money ch %: " << money_change / total_money << " Total money " << total_money << " Money change " << money_change << endl;
    // money_change = (1-average_items/items_a)*total_money;

    // if(price_a > average_price) {
    //     money_change = (1-average_price/price_a)*total_money;
    // }

    /*
     *What happends if we increase the money without any reason?!!?
     */
    /*
    if(clock_ -> get_time() == 200) {

        money_change = -10000000;
        cout << "In city adjust money increasing money at time 200" << endl;
    }
    */

    switch (payment_function_select)
    {

    case 0:
        bank_->change_capital(std::round(money_change));
        bank_->change_liquidity(std::round(money_change));
        loans_to_bank_ += std::round(money_change);

        break;
    case 1:
        change_capital(std::round(money_change));
        loans_to_bank_ += std::round(money_change);
        break;
    }
}

void City::pay_company_employees()
{
    double income_tax_sum = 0;
    // company_list_ -> pay_employees();
    income_tax_sum = company_list_->pay_employees(income_tax_, pay_wage_in_cash_);

    cout << "I city pay employees, actual income tax: " << income_tax_sum << endl;

    change_capital(income_tax_sum);

    // NEED TO UPDATEESTIMATED WAGES or add A tAX ESTIMATE!!!
}

void City::company_pay_interest()
{
    company_list_->pay_interest();
}

void City::company_repay_to_bank()
{

    company_list_->repay_to_bank();
}

void City::consumers_bank_business()
{
    consumers_->bank_business();
}

// void City::consumers_bank_business() {
//     consumers_ -> repay_to_bank();
//     consumers_ -> get_repayment_from_bank();
// }

void City::consumer_get_and_pay_interest()
{
    consumers_->get_and_pay_interest();
}

/*
 * Assuming that all the capital_owners owns an equal share of
 * each company.
 */

void City::company_pay_dividends()
{
    double total_profit_c = 0;
    double total_profit_m = 0;
    double total_profit_b = 0;
    double company_tax = 0;
    double market_tax = 0;
    double bank_tax = 0;
    int number_of_market_participants = 1;

    int number_of_capital_owners = 0;

    number_of_capital_owners = capital_owners_->get_size();
    number_of_market_participants = fmax(get_active_market()->get_number_of_participants(), 1);

    // Companies paying tax to city
    total_profit_c = company_list_->pay_dividends_directly(capital_gains_tax_);

    // Bank paying dividends
    total_profit_b = bank_->pay_dividends();

    if (!enable_intercity_trading_)
    {
        total_profit_m = get_active_market()->pay_dividends();
    }
    else
    {
        total_profit_m = 0;
    }

    // Calculating capital gains tax
    company_tax = total_profit_c * capital_gains_tax_;
    market_tax = total_profit_m * capital_gains_tax_;
    bank_tax = total_profit_b * capital_gains_tax_;

    // Paying dividends after tax to capital owners
    // capital_owners_->pay_all_dividends_log((total_profit_c - company_tax) / number_of_capital_owners, (total_profit_m - market_tax) / number_of_capital_owners, (total_profit_b - bank_tax) / number_of_capital_owners);

    capital_owners_->pay_all_dividends_log(0, (total_profit_m - market_tax) / number_of_capital_owners, (total_profit_b - bank_tax) / number_of_capital_owners);

    // Increasing city capital with collected tax
    change_capital(company_tax + bank_tax + market_tax);

    cout << endl
         << "Company dividends: " << total_profit_c - company_tax << " $BJ" << endl
         << "Bank dividends: " << total_profit_b - bank_tax << " $BJ" << endl
         << "Market dividends: " << total_profit_m - market_tax << " $BJ" << " and # market participants: " << number_of_market_participants << endl;
}

void City::company_pay_dividends(string theCompanyString, string theConsumerString, double amount)
{

    Consumer *theConsumer = consumers_->get_consumer(theConsumerString);
    Company *theCompany = company_list_->get_company(theCompanyString);

    cout << "I city company_pay_dividends" << endl;
    theConsumer->info();

    theCompany->change_capital(-amount / 4);
    theConsumer->change_capital(amount / 4);
    log_transaction_full(theCompanyString, theConsumerString, amount / 4, "Dividend", get_time());

    theCompany->change_capital(-amount / 4);
    theConsumer->change_capital(amount / 4);
    log_transaction_full(theCompanyString, theConsumerString, amount / 4, "Dividend", get_time());

    theCompany->change_capital(-amount / 4);
    theConsumer->change_capital(amount / 4);
    log_transaction_full(theCompanyString, theConsumerString, amount / 4, "Dividend", get_time());

    theCompany->change_capital(-amount / 4);
    theConsumer->change_capital(amount / 4);
    log_transaction_full(theCompanyString, theConsumerString, amount / 4, "Dividend", get_time());

    theConsumer->info();
}

void City::pay_transfers()
{

    double number_of_consumers = 0;
    double total_transfers = 0;

    number_of_consumers = consumers_->get_size();

    total_transfers = fmax(capital_, 0);

    if (total_transfers > 0)
    {

        consumers_->pay_dividends_log(total_transfers / number_of_consumers, name_);
    }

    change_capital(-total_transfers);

    cout << "Transfers: " << total_transfers << " $BJ" << endl;
}
void City::consumers_deposit_and_borrow_from_bank()
{
    consumers_->deposit_and_borrow_from_bank();

    // cout << "I city consumers_deposit_and_borrow_from_bank, no consumer lending activated" << endl;
    // cout << "I city consumers deposit and loan, bank_loans: " << bank_ -> get_loans() << endl;
    // cout << "I city consumers deposit and loan, consumer_loans: " << consumers_ -> get_loans_sum() << endl;
    // cout << "I city consumers deposit and loan, consumer_debts: " << consumers_ -> get_debts_sum() << endl;
    // cout << "I city consumers deposit and loan, company_loans: " << company_list_ -> get_debts_sum() << endl;

    // cout << "I city consumers deposit and loan, bank_borrow: " << bank_ -> get_deposits() << endl;
}

void City::consumers_deposit_to_bank()
{
    consumers_->deposit_money_to_bank();
}

void City::consumers_borrow_from_bank()
{
    consumers_->borrow_money_from_bank();
}

string City::steal_money()
{

    Consumer *theThief = consumers_->get_random_consumer();

    return steal_money(theThief->get_name());
}

string City::steal_money(string theThiefString)
{

    double capital_to_steal = 0;

    Consumer *theThief = consumers_->get_consumer(theThiefString);

    cout << endl
         << "Consumer: " << theThief->get_name() << " is the Thief in City steal" << endl;
    cout << "Thief money before:" << theThief->get_capital() << endl;

    Company *theCompany = company_list_->get_company("johansson_och_johansson"); // -> get_company();
    // bank_ -> info();

    capital_to_steal = theCompany->get_capital() * shareToSteal_;

    theCompany->change_capital(-capital_to_steal);
    theThief->change_capital(capital_to_steal);

    theThief->set_spedwill(0);

    cout << "Thief money after:" << theThief->get_capital() << endl;
    cout << "SOMETHING IS FISHY IN THE BANK CONCERNING ASSETS, LOANS, DEBTS AND DEPOSITS" << endl
         << endl;

    return theThief->get_name();
}

double City::launder_money(string theThiefString, string theFraudCompanyString)
{

    double money_to_launder = 0;
    Consumer *theThief = consumers_->get_consumer(theThiefString);
    money_to_launder = (theThief->get_capital()) * laundry_factor_;

    // cout << "I city launder money" << endl;
    // theThief -> info();

    for (int j = 1; j <= no_years_laundry_; j++)
    {
        get_active_market()->change_capital(money_to_launder / no_years_laundry_);
        theThief->change_capital(-money_to_launder / no_years_laundry_);
        log_transaction_full(theThiefString, "Market", money_to_launder / no_years_laundry_, "Purchase", get_time(), 1);
    }

    Company *theFraudCompany = company_list_->get_company(theFraudCompanyString);

    get_active_market()->change_capital(-money_to_launder);
    theFraudCompany->change_capital(money_to_launder);
    log_transaction_full("Market", theFraudCompanyString, money_to_launder, "Inventory", get_time(), 1);

    return money_to_launder;
}

void City::randomize_laundry_parameters()
{

    std::default_random_engine generator;

    double temp = 0.5;

    log_launder_parameters(shareToSteal_, laundry_factor_, no_years_laundry_, time_to_steal_);

    // Share to steal

    std::normal_distribution<double> distribution_1(shareToSteal_, 1.0);
    temp = distribution_1(generator);
    while (temp <= 0 || temp > 1)
    {

        temp = distribution_1(generator);
    }
    shareToSteal_ = temp;

    std::normal_distribution<double> distribution_2(laundry_factor_, 1.0);
    temp = distribution_2(generator);
    while (temp <= 0 || temp > 1)
    {
        temp = distribution_2(generator);
    }
    laundry_factor_ = temp;

    std::normal_distribution<double> distribution_3(no_years_laundry_, 3.0);
    temp = (int)distribution_3(generator);
    while (temp <= 0)
    {
        temp = (int)distribution_3(generator);
    }
    no_years_laundry_ = temp;

    std::normal_distribution<double> distribution_4(time_to_steal_, 3.0);
    temp = (int)distribution_4(generator);
    while (temp <= 0)
    {
        temp = (int)distribution_4(generator);
    }
    time_to_steal_ = temp;

    cout << "Launder params updated in city randomize launder parameters" << endl;
    cout << "shareToSteal_: " << shareToSteal_ << endl;
    cout << "laundry_factor_: " << laundry_factor_ << endl;
    cout << "no_years_laundry_: " << no_years_laundry_ << endl;
    cout << "time_to_steal_: " << time_to_steal_ << endl;
}

void City::update_interest_parameters()
{

    using Record = std::vector<std::string>;
    using Records = std::vector<Record>;

    string full_path = get_city_sql_string(name_);
    const char *dir = full_path.c_str();

    double targetInteresRate = 0;
    double interestRateMethod = 0;
    double capital_reserve_ratio = 0;
    double liquidity_reserve_ratio = 0;
    double bank_dividend_ratio = 0;

    // const char* stmt = "SELECT * FROM PARAMETERS";
    string stmt = "SELECT * FROM PARAMETERS";
    // cout << "Test i cuty update interest parameters" << endl;

    Records records = select_stmt(stmt, dir);
    // sqlite3_close(DB);

    for (int i = 0; i < records.size(); i++)
    {
        if (records[i][1] == "InterestRateMethod")
        {
            interestRateMethod = std::stod(records[i][2]);
            cout << records[i][1] << " set to: " << std::stod(records[i][2]) << endl;
        }
        if (records[i][1] == "TargetInterestRate")
        {
            targetInteresRate = std::stod(records[i][2]);
            cout << records[i][1] << " set to: " << std::stod(records[i][2]) << endl;
        }
        if (records[i][1] == "LiquidityReserveRatio")
        {
            liquidity_reserve_ratio = std::stod(records[i][2]);
            cout << records[i][1] << " set to: " << std::stod(records[i][2]) << endl;
        }
        if (records[i][1] == "CapitalReserveRatio")
        {
            capital_reserve_ratio = std::stod(records[i][2]);
            cout << records[i][1] << " set to: " << std::stod(records[i][2]) << endl;
        }
        if (records[i][1] == "BankDividendRatio")
        {
            bank_dividend_ratio = std::stod(records[i][2]);
            cout << records[i][1] << " set to: " << std::stod(records[i][2]) << endl;
        }
    }
    cout << endl;
    bank_->set_interest_rate_method(interestRateMethod);
    bank_->set_target_interest(targetInteresRate);
    bank_->set_capital_reserve_ratio(capital_reserve_ratio);
    bank_->set_liquidity_reserve_ratio(liquidity_reserve_ratio);
    bank_->set_dividend_ratio(bank_dividend_ratio);
}

void City::update_parameters_from_database()
{

    using Record = std::vector<std::string>;
    using Records = std::vector<Record>;

    double budgetBalance = 0;
    double incomeTax = 0;
    double inflationTarget = 0;
    double targetInteresRate = 0;
    double interestRateMethod = 0;
    double capital_reserve_ratio = 0;
    double liquidity_reserve_ratio = 0;
    double bank_dividend_ratio = 0;

    // Use PostgreSQL version
    string stmt = "SELECT * FROM PARAMETERS";

    Records records = select_stmt_pg(stmt, name_);
    // sqlite3_close(DB);
    if (not(records.empty()))
    {
        for (int i = 0; i < records.size(); i++)
        {
            if (records[i][2] == "BudgetBalance")
            {
                budgetBalance = std::stod(records[i][3]);
                cout << records[i][2] << " set to: " << std::stod(records[i][3]) << endl;
            }
            if (records[i][2] == "IncomeTax")
            {
                incomeTax = std::stod(records[i][3]);
                cout << records[i][2] << " set to: " << std::stod(records[i][3]) << endl;
            }
            if (records[i][2] == "InflationTarget")
            {
                inflationTarget = std::stod(records[i][3]);
                cout << records[i][2] << " set to: " << std::stod(records[i][3]) << endl;
            }
            if (records[i][2] == "CapitalGainsTax")
            {
                capital_gains_tax_ = std::stod(records[i][3]);
                cout << records[i][2] << " set to: " << std::stod(records[i][3]) << endl;
            }
            if (records[i][2] == "FacIncreaseRate_1")
            {
                fac_increase_rate_1_ = std::stod(records[i][3]);
                cout << records[i][2] << " set to: " << std::stod(records[i][3]) << endl;
            }
            if (records[i][2] == "CapIncreaseParam_1")
            {
                cap_increase_param_1_ = std::stod(records[i][3]);
                cout << records[i][2] << " set to: " << std::stod(records[i][3]) << endl;
            }
            if (records[i][2] == "CapIncreaseRate_1")
            {
                cap_increase_rate_1_ = std::stod(records[i][3]);
                cout << records[i][2] << " set to: " << std::stod(records[i][3]) << endl;
            }
            if (records[i][2] == "ItemEfficiencyRate")
            {
                item_efficiency_rate_ = std::stod(records[i][3]);
                cout << records[i][2] << " set to: " << std::stod(records[i][3]) << endl;
            }
            if (records[i][2] == "PayWageInCash")
            {
                pay_wage_in_cash_ = std::stoi(records[i][3]);
                cout << records[i][2] << " set to: " << std::stoi(records[i][3]) << endl;
            }
            // Interest rate parameters
            if (records[i][2] == "InterestRateMethod")
            {
                interestRateMethod = std::stod(records[i][3]);
                cout << records[i][2] << " set to: " << std::stod(records[i][3]) << endl;
            }
            if (records[i][2] == "TargetInterestRate")
            {
                targetInteresRate = std::stod(records[i][3]);
                cout << records[i][2] << " set to: " << std::stod(records[i][3]) << endl;
            }
            if (records[i][2] == "LiquidityReserveRatio")
            {
                liquidity_reserve_ratio = std::stod(records[i][3]);
                cout << records[i][2] << " set to: " << std::stod(records[i][3]) << endl;
            }
            if (records[i][2] == "CapitalReserveRatio")
            {
                capital_reserve_ratio = std::stod(records[i][3]);
                cout << records[i][2] << " set to: " << std::stod(records[i][3]) << endl;
            }
            if (records[i][2] == "BankDividendRatio")
            {
                bank_dividend_ratio = std::stod(records[i][3]);
                cout << records[i][2] << " set to: " << std::stod(records[i][3]) << endl;
            }
        }

        cout << endl;
        set_budget_balance(budgetBalance);
        set_income_tax(incomeTax);
        set_inflation_target(inflationTarget);

        // Set interest rate parameters
        bank_->set_interest_rate_method(interestRateMethod);
        bank_->set_target_interest(targetInteresRate);
        bank_->set_capital_reserve_ratio(capital_reserve_ratio);
        bank_->set_liquidity_reserve_ratio(liquidity_reserve_ratio);
        bank_->set_dividend_ratio(bank_dividend_ratio);
    }
}

void City::add_companies_from_database()
{

    using Record = std::vector<std::string>;
    using Records = std::vector<Record>;

    string name = "";
    double capital = 0;
    long stock = 0;
    double capacity = 0;
    double debts = 0;
    double p_c_skill = 0;
    double p_c_mot = 0;
    double wage_const = 0;
    double wage_change_limit = 0;
    double invest = 0;
    double pbr = 0;
    double decay = 0;
    int production_function = 0;

    cout << "I City add companies from DB (PostgreSQL) for: " << name_ << endl;

    // Use PostgreSQL to get company data with explicit column selection
    // PostgreSQL company_data columns: id, city_name, company_name, time_stamp, capital, stock, capacity, debts,
    //                                  pcskill, pcmot, wage_const, wage_ch, invest, pbr, decay, prod_parm,
    //                                  prod_fcn, production, employees, item_efficiency, cap_vs_eff_split
    string stmt = "SELECT company_name, capital, stock, capacity, debts, pcskill, pcmot, "
                  "wage_const, wage_ch, invest, pbr, decay, prod_parm, prod_fcn "
                  "FROM COMPANY_TABLE WHERE time_stamp = 0";
    Records records = select_stmt_pg(stmt, name_);

    for (int i = 0; i < records.size(); i++)
    {
        // PostgreSQL result columns (0-indexed):
        // 0: company_name, 1: capital, 2: stock, 3: capacity, 4: debts, 5: pcskill, 6: pcmot,
        // 7: wage_const, 8: wage_ch, 9: invest, 10: pbr, 11: decay, 12: prod_parm, 13: prod_fcn

        name = records[i][0];                            // company_name
        capital = std::stod(records[i][1]);              // capital
        stock = std::stoi(records[i][2]);                // stock
        capacity = std::stod(records[i][3]);             // capacity
        debts = std::stod(records[i][4]);                // debts
        p_c_skill = std::stod(records[i][5]);            // pcskill
        p_c_mot = std::stod(records[i][6]);              // pcmot
        wage_const = std::stod(records[i][7]);           // wage_const
        wage_change_limit = std::stod(records[i][8]);    // wage_ch
        invest = std::stod(records[i][9]);               // invest
        pbr = std::stod(records[i][10]);                 // pbr
        decay = std::stod(records[i][11]);               // decay
        production_function = std::stoi(records[i][13]); // prod_fcn

        add_company(new Company(name, name_, capital, stock, capacity, p_c_skill, p_c_mot, wage_const, pbr, market_.get(), global_market_, bank_.get(), clock_));

        cout << endl
             << "Added company: " << name << endl
             << "Capital: " << capital << endl
             << "Capacity: " << capacity << endl;
    }
}

void City::update_companies_from_database()
{

    if (company_list_)
    {

        company_list_->update_companies_from_database(name_);
    }
}

void City::write_time_data_to_company_database()
{

    if (company_list_)
    {

        company_list_->write_time_data_to_database(name_);
    }
}

void City::save_high_score()
{

    double CAGR = 0;
    double environmental_impact = 0;
    double environmental_impact_per_year = 0;
    double GINI = 0;
    double palma_index = 0;
    int total_years = 0;
    string timenow = "";
    string world_name = "Bennyworld";

    total_years = clock_->get_time();

    std::vector<double> score;

    CAGR = calculate_CAGR(clock_->get_time() - 1);
    palma_index = calculate_Palma_ratio();
    environmental_impact = company_list_->get_environmental_impact_sum();

    if (total_years > 0)
    {
        cout << "I save highscore, years: " << total_years << endl;
        environmental_impact_per_year = round(environmental_impact / total_years);
    }

    std::time_t t = std::time(0); // get time now
    std::tm *now = std::localtime(&t);

    timenow = to_string(now->tm_year + 1900) + '-' + to_string(now->tm_mon + 1) + '-' + to_string(now->tm_mday) + ' ' + to_string(now->tm_hour) + ':' + to_string(now->tm_min) + ':' + to_string(now->tm_sec);

    cout << "time: " << timenow << endl;

    score.push_back(CAGR);
    score.push_back(palma_index);
    score.push_back(environmental_impact_per_year);

    // Write to SQLite (existing functionality)
    insertHighScore(score, name_, world_name, timenow);

    // Also write to PostgreSQL for centralized high scores
    // This enables cross-country leaderboards while maintaining backward compatibility
    try
    {
        cout << "Saving high score to PostgreSQL..." << endl;
        int pg_result = insertHighScorePG(score, name_, "", timenow);
        if (pg_result == 0)
        {
            cout << "High score successfully saved to PostgreSQL centralized database" << endl;
        }
        else
        {
            cout << "Warning: Failed to save high score to PostgreSQL, but SQLite save was successful" << endl;
        }
    }
    catch (const exception &e)
    {
        cout << "Warning: PostgreSQL high score save failed with exception: " << e.what() << endl;
        cout << "SQLite high score save was successful" << endl;
    }
}

double City::calculate_CAGR(int end_time)
{

    double CAGR = 0;
    int start_time1 = 3;
    int start_time2 = 0;
    double start_GDP_real = 0;
    double end_GDP_real = 0;
    double delta_time = 0;

    using Record = std::vector<std::string>;
    using Records = std::vector<Record>;

    // Use PostgreSQL instead of SQLite
    string stmt1 = "SELECT * FROM TIME_DATA WHERE TIME = " + std::to_string(start_time1);
    string stmt2 = "SELECT * FROM TIME_DATA WHERE TIME = " + std::to_string(end_time);

    // Query PostgreSQL with automatic city_name filtering
    Records records_start = select_stmt_pg(stmt1, name_);
    Records records_end = select_stmt_pg(stmt2, name_);

    try
    {
        if (not(records_start.empty()) && records_start[0].size() > 2)
        {
            start_GDP_real = std::stod(records_start[0][2]);
        }
        else
        {
            cout << "No start time data in database for " << name_ << " at time " << start_time1 << endl;
            return 0.0;
        }
    }
    catch (const exception &e1)
    {
        cerr << "Error parsing start GDP data: " << e1.what() << endl;
        return 0.0;
    }

    try
    {
        if (not(records_end.empty()) && records_end[0].size() > 2)
        {
            end_GDP_real = std::stod(records_end[0][2]);
        }
        else
        {
            cout << "No end time data in database for " << name_ << " at time " << end_time << endl;
            return 0.0;
        }
    }
    catch (const exception &e2)
    {
        cerr << "Error parsing end GDP data: " << e2.what() << endl;
        return 0.0;
    }

    // Calculate CAGR with additional safety checks
    if (start_GDP_real <= 0)
    {
        cout << "Invalid start GDP (<=0) for " << name_ << ", cannot calculate CAGR" << endl;
        return 0.0;
    }

    if (end_time <= start_time1)
    {
        cout << "Invalid time range for " << name_ << ", cannot calculate CAGR" << endl;
        return 0.0;
    }

    delta_time = end_time - start_time1;
    CAGR = pow(end_GDP_real / start_GDP_real, 1.0 / delta_time) - 1.0;

    cout << "CAGR calculated for " << name_ << ": " << CAGR << " (GDP: " << start_GDP_real << " -> " << end_GDP_real << " over " << delta_time << " periods)" << endl;

    return CAGR;
}

double City::calculate_Palma_ratio()
{

    double Palma_ratio = 0;
    int number_of_consumers = 0;
    double top_percentile = 0.1;
    double bottom_percentile = 0.4;
    int top_count = 0;
    int bottom_count = 0;

    double top_net_wealth = 0;
    double bottom_net_wealth = 0;

    using Record = std::vector<std::string>;
    using Records = std::vector<Record>;

    // SETTING LIMITS
    number_of_consumers = consumers_->get_size();

    if (number_of_consumers == 0)
    {
        cout << "No consumers found for " << name_ << ", cannot calculate Palma ratio" << endl;
        return 0.0;
    }

    bottom_count = floor(bottom_percentile * number_of_consumers);
    top_count = ceil(top_percentile * number_of_consumers);

    // Debug: Check if consumer data exists in database
    string count_query = "SELECT COUNT(*) FROM consumer_data WHERE city_name = '" + name_ + "'";
    Records count_result = select_stmt_pg(count_query, "");
    if (!count_result.empty() && count_result[0].size() > 0)
    {
        cout << "Consumer records in database for " << name_ << ": " << count_result[0][0] << endl;
    }

    // Construct PostgreSQL queries with city_name filter already included
    // Pass empty string to select_stmt_pg to skip automatic WHERE injection
    string top_net_wealth_stmt = "SELECT sum(NET_INCOME) FROM (SELECT (income + dividends + transfers) as NET_INCOME FROM consumer_data WHERE city_name = '" + name_ + "' ORDER BY (income + dividends + transfers) DESC LIMIT " + std::to_string(top_count) + ") as top_consumers";
    string bottom_net_wealth_stmt = "SELECT sum(NET_INCOME) FROM (SELECT (income + dividends + transfers) as NET_INCOME FROM consumer_data WHERE city_name = '" + name_ + "' ORDER BY (income + dividends + transfers) ASC LIMIT " + std::to_string(bottom_count) + ") as bottom_consumers";

    // Call select_stmt_pg with empty city_name to skip automatic WHERE injection
    Records records_top = select_stmt_pg(top_net_wealth_stmt, "");
    Records records_bottom = select_stmt_pg(bottom_net_wealth_stmt, "");

    try
    {
        if (not(records_top.empty()) && records_top[0].size() > 0 && !records_top[0][0].empty())
        {
            top_net_wealth = std::stod(records_top[0][0]);
            cout << "Extracting net income top: " << top_net_wealth << endl;
        }
        else
        {
            cout << "No top wealth data found for " << name_ << endl;
        }
    }
    catch (const exception &e)
    {
        cerr << "Error parsing top wealth data: " << e.what() << endl;
    }

    try
    {
        if (not(records_bottom.empty()) && records_bottom[0].size() > 0 && !records_bottom[0][0].empty())
        {
            bottom_net_wealth = std::stod(records_bottom[0][0]);
            cout << "Extracting net income bottom: " << bottom_net_wealth << endl;
        }
        else
        {
            cout << "No bottom wealth data found for " << name_ << endl;
        }
    }
    catch (const exception &e)
    {
        cerr << "Error parsing bottom wealth data: " << e.what() << endl;
    }

    if (bottom_net_wealth > 0)
    {
        Palma_ratio = top_net_wealth / bottom_net_wealth;
    }
    else
    {
        cout << "Bottom wealth is zero or negative for " << name_ << ", cannot calculate Palma ratio" << endl;
        return 0.0;
    }

    cout << "Palma ratio for " << name_ << ": " << Palma_ratio << endl;

    return Palma_ratio;
}

void City::save_consumers()
{

    if (consumers_)
    {

        consumers_->save_consumers();

        // Export CONSUMER_TABLE to CSV file
        // export_consumers_to_csv();
    }
}

void City::export_consumers_to_csv()
{
    try
    {
        // Create SQL query to select all data from CONSUMER_TABLE for this city
        string sql_query = "SELECT ID, NAME, EMPLOYER, ITEMS, CAPITAL, DEPOSITS, DEBTS, SKILL, MOT, SPENDWILL, SAVEWILL, BORROWWILL, INCOME, DIVIDENDS, TRANSFERS FROM CONSUMER_TABLE";

        // Execute the query and get results
        Records consumer_records = select_stmt(sql_query, get_city_sql_string(name_).c_str());

        // Create filename with city name and timestamp
        string filename = "consumers_" + name_ + "_cycle_" + std::to_string(get_time()) + ".csv";

        // Open file for writing
        std::ofstream csv_file(filename);
        if (!csv_file.is_open())
        {
            std::cerr << "Error: Could not open file " << filename << " for writing" << std::endl;
            return;
        }

        // Write CSV header
        csv_file << "ID,NAME,EMPLOYER,ITEMS,CAPITAL,DEPOSITS,DEBTS,SKILL,MOT,SPENDWILL,SAVEWILL,BORROWWILL,INCOME,DIVIDENDS,TRANSFERS" << std::endl;

        // Write data rows
        for (const auto &record : consumer_records)
        {
            for (size_t i = 0; i < record.size(); ++i)
            {
                if (i > 0)
                    csv_file << ",";

                // Escape any commas or quotes in the data
                string field = record[i];
                if (field.find(',') != std::string::npos || field.find('"') != std::string::npos)
                {
                    // Replace quotes with double quotes and wrap in quotes
                    size_t pos = 0;
                    while ((pos = field.find('"', pos)) != std::string::npos)
                    {
                        field.replace(pos, 1, "\"\"");
                        pos += 2;
                    }
                    field = "\"" + field + "\"";
                }
                csv_file << field;
            }
            csv_file << std::endl;
        }

        csv_file.close();

        std::cout << "Consumer data exported to CSV file: " << filename << " (" << consumer_records.size() << " records)" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error exporting consumers to CSV: " << e.what() << std::endl;
    }
}