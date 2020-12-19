#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <cstring>
#include <list>

//#include "consumer.h"
#include "company.h"
#include "functions.h"
#include "SQLfunctions.h"
#include "error_no_return.h"

using namespace std;

Company::Company() : name_(""),
                     capital_(0),
                     stock_(0),
                     invest_(0.6),
                     prod_const_skill_(60),
                     prod_const_motivation_(40),
                     wage_const_(0.4),
                     market_(0),
                     employees_(new Consumer_list("Employees")) {}

Company::Company(string name, Market *market, Clock *clock) : name_(name),
                                                              capital_(10000),
                                                              stock_(0),
                                                              invest_(0.6),
                                                              production_function_(1),
                                                              prod_const_skill_(60),
                                                              prod_const_motivation_(40),
                                                              wage_const_(0.1),
                                                              wage_change_limit_(0.1),
                                                              market_(market),
                                                              capacity_(3000),
                                                              clock_(clock),
                                                              employees_(new Consumer_list("Employees"))
{
}

// NAME CAPITAL STOCK CAPACITY PROD_CONST_SKILL PROD_CONST_MOT WAGE_CONST

Company::Company(string name, string city_name, double capital, double stock, double capacity, double p_c_skill, double p_c_mot, double wage_const, double plow_back_ratio, Market *market, Bank *bank, Clock *clock) : name_(name),
                                                                                                                                                                                                                        city_name_(city_name),
                                                                                                                                                                                                                        capital_(capital),
                                                                                                                                                                                                                        stock_(stock),
                                                                                                                                                                                                                        debts_(0),
                                                                                                                                                                                                                        invest_(0),
                                                                                                                                                                                                                        production_function_(1),
                                                                                                                                                                                                                        current_production_items_(0),
                                                                                                                                                                                                                        production_parameter_(0.001),
                                                                                                                                                                                                                        prod_const_skill_(p_c_skill),
                                                                                                                                                                                                                        prod_const_motivation_(p_c_mot),
                                                                                                                                                                                                                        wage_const_(wage_const),
                                                                                                                                                                                                                        wage_change_limit_(0.8),
                                                                                                                                                                                                                        capacity_(capacity),
                                                                                                                                                                                                                        capacity_0_(capacity),
                                                                                                                                                                                                                        pbr_(plow_back_ratio),
                                                                                                                                                                                                                        decay_(0.001),
                                                                                                                                                                                                                        max_leverage_(1),
                                                                                                                                                                                                                        market_(market),
                                                                                                                                                                                                                        bank_(bank),
                                                                                                                                                                                                                        clock_(clock),
                                                                                                                                                                                                                        employees_(new Consumer_list("Employees"))
{
}

/*
 * Info-functions
 */

void Company::info()
{

    cout << "Name: " << name_ << endl
         << "Capital: " << capital_ << endl
         << "Stock: " << stock_ << endl
         << "Capacity: " << capacity_ << endl
         << "Prod const sk: " << prod_const_skill_ << endl
         << "Prod const mot: " << prod_const_motivation_ << endl
         << "Employees: " << employees_->get_size() << endl
         << endl;
}

void Company::employee_info()
{
    cout << name_ << endl
         << "---------------------" << endl;
    employees_->info();
}

void Company::print_employees()
{
    employees_->print_list();
}

void Company::save(string project)
{

    char name[100];

    strcpy(name, name_.c_str());

    ofstream ou(name);
    if (ou.is_open())
    {
        ou << capital_ << endl
           << stock_ << endl
           << capacity_ << endl
           << debts_ << endl
           << prod_const_skill_ << endl
           << prod_const_motivation_ << endl
           << wage_const_ << endl
           << wage_change_limit_ << endl
           << invest_ << endl
           << pbr_ << endl
           << decay_ << endl;
        ou.close();
    }
    else
    {
        cout << "Unable to open file" << endl;
    }
}

/*
 * Get-functions
 */

string Company::get_name()
{
    return name_;
}

double Company::get_capital()
{
    return capital_;
}

double Company::get_debts()
{
    return debts_;
}

double Company::get_prod_const_skill()
{
    return prod_const_skill_;
}

double Company::get_prod_const_motivation()
{
    return prod_const_motivation_;
}

double Company::get_wage_const()
{
    return wage_const_;
}

double Company::get_wage_change_limit()
{
    return wage_change_limit_;
}

int Company::get_production_function()
{
    return production_function_;
}

double Company::get_production_parameter()
{
    return production_parameter_;
}

int Company::get_no_employees()
{
    return employees_->get_size();
}

double Company::get_production()
{

    double skill_sum = 0;
    double mot_sum = 0;
    double employees = 0;
    double prod = 0;

    skill_sum = employees_->get_skill_sum();
    mot_sum = employees_->get_motivation_sum();
    employees = employees_->get_size();

    prod = get_prod(skill_sum, prod_const_skill_, mot_sum, prod_const_motivation_, capacity_, production_function_, production_parameter_);

    return prod;
}

// double Company::get_production() {

//     double skill_sum = 0;
//     double mot_sum = 0;
//     double employees = 0;
//     double prod = 0;

//     skill_sum = employees_ -> get_skill_sum();
//     mot_sum =employees_ -> get_motivation_sum();
//     employees = employees_ -> get_size();

//     //Production rates
//     double rate1 = 0.001;
//     double rate2 = 0.000100;
//     double rate3 = 0.001;
//     double rate4 = 0.00000005;  //Funkar bra med 0.000000010;

//     int prod_function = 1;

//         switch (prod_function) {

//         case 1:
//             prod = capacity_*atan((skill_sum*prod_const_skill_ + mot_sum*prod_const_motivation_)*rate1);
//             break;

//         case 2:
//             prod = 2*capacity_*log(skill_sum*prod_const_skill_ + mot_sum*prod_const_motivation_+1);
//             break;

//         case 3:
//             prod = capacity_*atan((skill_sum*prod_const_skill_ + mot_sum*prod_const_motivation_)*rate3*capacity_);
//             break;

//         case 4:
//             prod = capacity_*atan((skill_sum*prod_const_skill_ + mot_sum*prod_const_motivation_)*rate4);
//             break;

//         default:
//         	cout << "I functions get_prod, no valid production function set" << endl;
//             prod = 0;
//             break;
//     }

//     return prod;

// }

/*
 * Calls the get_prod () function in functions.cc
 * Don't think this function works very well...
 */

double Company::get_production(Consumer *consumer)
{

    double skill = consumer->get_skill();
    double mot = consumer->get_motivation();
    double prod = get_prod(skill, prod_const_skill_, mot, prod_const_motivation_, capacity_, production_function_, production_parameter_);

    return prod;
}

double Company::get_stock()
{
    //cout << name_ << " i cmp get stock: " << stock_ << endl;
    return stock_;
}

double Company::get_invest()
{
    return invest_;
}

double Company::get_capacity()
{
    return capacity_;
}

double Company::get_items_for_production()
{
    double production = 0;
    double items = 0;
    int size = 0;
    double mot_sum = 0;
    double skill_sum = 0;

    if (employees_)
    {
        size = employees_->get_size();
        skill_sum = employees_->get_skill_sum();
        mot_sum = employees_->get_motivation_sum();
    }

    production = get_prod(skill_sum, prod_const_skill_, mot_sum, prod_const_motivation_, capacity_, production_function_, production_parameter_);

    items = item_cost(production);

    return items;
}

double Company::get_desired_loans()
{

    double desired_investment = 0;
    double price_out = 0;
    double capital_to_invest = 0;
    double desired_loans = 0;

    capital_to_invest = capital_ * pbr_;
    desired_investment = get_desired_investment();
    price_out = market_->get_price_out();

    desired_loans = fmax(0, desired_investment * price_out - capital_to_invest);

    //if(desired_loans < 0) {
    //    desired_loans = 0;
    //}

    return desired_loans;
}

double Company::get_expected_net_flow_to_bank()
{

    double loans_from_bank = 0;
    double repayment_to_bank = 0;
    double interest_to_bank = 0;

    double interest = 0;
    double sum = 0;
    int payback_time = 0;

    payback_time = bank_->get_payback_time();
    interest = bank_->get_interest();

    repayment_to_bank = debts_ / (payback_time * 12);

    if (repayment_to_bank > capital_)
    {

        repayment_to_bank = capital_;
    }

    interest_to_bank = interest * debts_;
    loans_from_bank = get_desired_loans();
    sum = repayment_to_bank + interest_to_bank - loans_from_bank;

    //cout << "Company net flows, interest: " << interest_to_bank << " borrow from bank: " << loans_from_bank << " repayment_to_bank: " << repayment_to_bank << endl;

    return sum;
}

/*
 * Set-functions
 */

void Company::set_capital(double capital)
{
    capital_ = capital;
}

void Company::set_production_function(int pf)
{
    production_function_ = pf;
}

void Company::set_production_parameter(double pp)
{
    production_parameter_ = pp;
}

void Company::set_prod_const_skill(double skill)
{
    prod_const_skill_ = skill;
}

void Company::set_prod_const_motivation(double mot)
{
    prod_const_motivation_ = mot;
}

void Company::set_wage_const(double wc)
{
    wage_const_ = wc;
}

void Company::set_stock(double stock)
{

    stock_ = stock;
}

void Company::set_invest(double invest)
{
    invest_ = invest;
}

void Company::set_debts(double debts)
{
    debts_ = debts;
}

void Company::set_capacity(double capacity)
{
    capacity_ = capacity;
}

void Company::set_wage_change_limit(double wcl)
{
    wage_change_limit_ = wcl;
}

/*
 * Change-functions
 */

void Company::change_capital(double ch)
{
    //  if (capital_ + ch > 0) {
    capital_ += ch;
    // }
    //else {
    //cout << "Fel i company ch cap" << endl;
    // }
}

void Company::change_prod_const_skill(double ch)
{
    //out << "Increasing skill i company" << endl;
    prod_const_skill_ += ch;
}

void Company::change_prod_const_motivation(double ch)
{
    prod_const_motivation_ += ch;
}

void Company::change_wage_const(double wcc)
{
    wage_const_ += wcc;
}

void Company::change_stock(double ch)
{
    stock_ += ch;
}

void Company::change_invest(double ch)
{
    invest_ += ch;
}

void Company::change_debts(double ch)
{
    debts_ += ch;
}

void Company::change_capacity(double ch)
{
    capacity_ += ch;
}

void Company::change_wage_change_limit(double ch)
{
    wage_change_limit_ += ch;
}

/*
 * Functions for adding and removing employees.
 */

void Company::add_employee(Consumer *consumer)
{

    if (!(consumer->get_employer() == name_))
    {
        employees_->add_first(consumer);
        consumer->set_employment_status(true);
        consumer->set_employer(name_);
    }
    else
    {
        cout << "Consumer " << consumer->get_name() << " already employed by" << name_ << endl;
    }
}

void Company::remove_employee(Consumer *consumer)
{

    consumer->set_income(0);
    consumer->set_employment_status(false);
    consumer->set_employer("");
    employees_->remove_consumer(consumer, capacity_);
}

void Company::update_company()
{
    capacity_ -= decay_ * capacity_;
    prod_const_skill_ -= decay_ * prod_const_skill_;
    prod_const_motivation_ -= decay_ * prod_const_motivation_;
}

bool Company::update_employees(Consumer *opt)
{
    //  cout << "I company update employees:v " << contribution_adding(opt) << endl;
    if (name_ != opt->get_employer()) {
        if (contribution_adding(opt) > 0.01) {
            try {
                //cout << "Company " << name_ << " hired " << opt->get_name() << " from " << opt->get_employer() << endl;
                add_employee(opt);
            }
            catch (std::exception a) {
                cout << a.what() << endl
                     << "I Company update empl" << endl;
                return false;
            }
            return true;
        }
        else {
            return false;
        }
    }
    else {
            //cout << opt->get_name() << " already employed by " << name_ << endl;
            return true;
        }
}

    void Company::remove_usless_employees()
    {

        int no_removed_employees = 0;

        if (employees_)
        {
            try
            {
                Consumer *bad_empl = employees_->get_usless_employee(prod_const_skill_, prod_const_motivation_, capacity_, production_function_, production_parameter_);

                while (contribution_removing(bad_empl) > 0.001)
                {

                    remove_employee(bad_empl);

                    bad_empl = employees_->get_usless_employee(prod_const_skill_, prod_const_motivation_, capacity_, production_function_, production_parameter_);
                    no_removed_employees++;
                }
            }
            catch (std::exception b)
            {
                cout << b.what() << endl
                     << "Error i company rem usless " << name_ << endl;
            }
        }
        else
        {
            cout << "I Company remove usless employees, no employees" << endl;
        }
        cout << "I Company " << name_ << " remove usless employees: " << no_removed_employees << " removed" << endl;
    }

    void Company::update_from_database(string city_name)
    {

        using Record = std::vector<std::string>;
        using Records = std::vector<Record>;

        string full_path = get_city_sql_string(city_name);
        // char dir[100];
        // dir = full_path.c_str();
        
        //cout << "I company update_from_databbase1 " << endl;
        const char *dir = full_path.c_str();
        //cout << "I company update_from_databbase2 " << endl;

        double wage_const = 0;
        double wage_change_limit = 0;
        double pbr = 0;
        double decay = 0;
        double production_parameter = 0;
        int production_function = 0;

        production_parameter = getDatabaseParameter("'ProductionParameter'", city_name);

        //const char* stmt = "SELECT * FROM PARAMETERS";
        string stmt = "SELECT * FROM COMPANY_TABLE WHERE NAME = ";
        stmt.append("'");
        stmt.append(name_);
        stmt.append("'");
        stmt.append(" AND TIME_STAMP = (SELECT MAX(TIME_STAMP) FROM COMPANY_TABLE)");
        //cout << "I company update_from_databbase3 " << endl;
        Records records = select_stmt(stmt, dir);
        //cout << "I company update_from_databbase4 " << endl;
        wage_const = std::stod(records[0][9]);
        wage_change_limit = std::stod(records[0][10]);
        pbr = std::stod(records[0][12]);
        decay = std::stod(records[0][13]);
        //production_parameter = std::stod(records[0][13]);
        production_function = std::stoi(records[0][15]);

        /*     cout << "Company update from database: " << name_ << " updated in "<< city_name << endl;
    cout << "wage_change_limit: " << wage_change_limit << " was: " << wage_change_limit_ << endl;
    cout << "pbr: " << pbr << " was: " << pbr_ << endl;
    cout << "decay: " << decay << " was: " << decay_ << endl;
    cout << "production_parameter: " << production_parameter << " was: " << production_parameter_ << endl;
    cout << "production_function: " << production_function << " was: " << production_function_ << endl;
    cout << "wage_const: " << wage_const << " was: " << wage_const_ << endl;
 */
        wage_const_ = wage_const;
        wage_change_limit_ = wage_change_limit;
        pbr_ = pbr;
        decay_ = decay;
        production_parameter_ = production_parameter;
        production_function_ = production_function;
}



// THIS FUNCTION MUST BE RUN AFTER UPDATING THE COMPANY DATA FROM DATABASE
void Company::save_time_data_to_database(string city_name) {


    std::vector<double> company_data;
    int time_stamp = 0;
    time_stamp = clock_ -> get_time();

    //TIME_STAMP, NAME, CAPITAL, STOCK, CAPACITY, DEBTS, PCSKILL, PCMOT, 
    //WAGE_CONST, WAGE_CH, INVEST, PBR, DECAY, PROD_PARM, PROD_FCN) VALUES(";


    company_data.push_back((double)time_stamp);
    company_data.push_back((double)capital_);
    company_data.push_back((double)stock_);
    company_data.push_back((double)capacity_);
    company_data.push_back((double)debts_);
    company_data.push_back((double)prod_const_skill_);
    company_data.push_back((double)prod_const_motivation_);
    company_data.push_back((double)wage_const_);
    company_data.push_back((double)wage_change_limit_);
    company_data.push_back((double)invest_);
    company_data.push_back((double)pbr_);
    company_data.push_back((double)decay_);
    company_data.push_back((double)production_parameter_);
    company_data.push_back((double)production_function_);
    company_data.push_back((double)current_production_items_);
    company_data.push_back((double)employees_ -> get_size());
    //cout << "I company save time database " << current_production_items_ << endl;
    //company_data.push_back((double)prod_const_motivation_);


    insertCompanyTimeData(company_data, city_name, name_);


}

    //Checks how the expected income changes by adding consumer
    double Company::contribution_adding(Consumer * consumer)
    {
        double skill = 0;
        double mot = 0;
        double skill_sum = 0;
        double mot_sum = 0;
        int size = 0;
        double prod_before = 0;
        double prod_after = 0;
        double price = 0;
        double price_out = 0;
        double wage = 0;
        double contribution = 0;
        double delta_sales = 0;
        double material_cost_delta = 0;

        skill = consumer->get_skill();
        mot = consumer->get_motivation();
        skill_sum = employees_->get_skill_sum();
        mot_sum = employees_->get_motivation_sum();
        size = employees_->get_size();
        price = market_->get_price_in();
        price_out = market_->get_price_out();

        //  cout << "I company contribution adding"<< endl << "skill och mot" << skill << "  " << mot << "  " << "tabort"<< endl;

        prod_before = get_production();
        prod_after = get_prod(skill_sum + skill, prod_const_skill_, mot_sum + mot, prod_const_motivation_, capacity_, production_function_, production_parameter_);

        /*
     * This estimates the wage, but will not be the correct one...
     * Might as well use the previous wage to estimate... 
     */

        //  if (size != 0) {
        //  wage = get_total_wages()/size;
        // }
        //else {
        //  wage = get_total_wages();
        //}

        list<double>::iterator theIterator;
        theIterator = wages_.begin();
        wage = *theIterator;

        //contribution = (prod_after - prod_before)*price   - wage + (item_cost(prod_after) - item_cost(prod_before))*price_out;

        delta_sales = (prod_after - prod_before) * price;
        material_cost_delta = (item_cost(prod_after) - item_cost(prod_before)) * price_out;
        contribution = delta_sales - wage - material_cost_delta;

        //cout << "I comp contrib adding for " << name_ << " sales_loss: " << delta_sales << " Wages: " << wage << " material_cost: " << material_cost_delta << "  Contribution: " << contribution << endl;

        //cout << "I comp contrib adding"  << "Prod bef: " << prod_before << "  Prod after: " << prod_after  << "Wages: " << wage << "  Contribution: " << contribution << endl;

        return contribution;
    }

    double Company::contribution_removing(Consumer * consumer)
    {

        double skill = 0;
        double mot = 0;
        double skill_sum = 0;
        double mot_sum = 0;
        int size = 0;
        double prod_before = 0;
        double prod_after = 0;
        double price = 0;
        double price_out = 0;
        double wage = 0;
        double contribution = 0;
        double delta_sales = 0;
        double material_cost_delta = 0;

        skill = consumer->get_skill();
        mot = consumer->get_motivation();
        skill_sum = employees_->get_skill_sum();
        mot_sum = employees_->get_motivation_sum();
        price = market_->get_price_in();
        price_out = market_->get_price_out();
        size = employees_->get_size();

        prod_before = get_production();
        prod_after = get_prod(skill_sum - skill, prod_const_skill_, mot_sum - mot, prod_const_motivation_, capacity_, production_function_, production_parameter_);

        if (size != 0)
        {
            wage = get_total_wages() / size;

            delta_sales = (prod_after - prod_before) * price;
            material_cost_delta = (item_cost(prod_after) - item_cost(prod_before)) * price_out;
            //contribution = (prod_after - prod_before)*price - (item_cost(prod_after) - item_cost(prod_before))*price_out + wage;
            contribution = delta_sales + wage - material_cost_delta;

            //cout << "I comp contrib removing for " << name_ << " sales_loss: " << delta_sales << " Wages: " << wage << " material_cost: " << material_cost_delta << "  Contribution: " << contribution << endl;
        }
        else
        {
            contribution = 0;
        }

        //list<double>::iterator theIterator;
        //theIterator = wages_.begin();

        //wage = *theIterator;
        //  cout << "cont rem i company, cont = " << endl
        //     << "Contr before: " << prod_before << endl
        //     << "Prod_after" << prod_after << endl
        //     << "Contribution: " << contribution << endl;

        return contribution;
    }

    double Company::produce(string city_name)
    {

        double production = 0;

        buy_items_for_production();
        production = get_production();
        current_production_items_  = production;
        stock_ += production;
        //insertCompanyDatapoint("PRODUCTION", production, clock_ -> get_time(), city_name, name_);

        cout << "I Company produce, share of full capacity: " << production / (capacity_ * 3.1415 / 2) << " capacity: " << capacity_ << " employees: " << employees_->get_size() << " for " << name_ << endl;

        return production;
    }

    void Company::sell_to_market()
    {
        double price = 0;
        int actual_items = 0;
        double actual_cost = 0;

        price = market_->get_price_in();

        actual_cost = market_->market_buy_items(stock_);
        actual_items = actual_cost / price;

        //cout << "I comp sell to mkt, cost: " << actual_cost << " items: " << actual_items  << " and price: " << price << endl;

        change_capital(actual_cost);
        change_stock(-actual_items);

        log_transaction_full(name_, "market", actual_cost, "Inventory", clock_->get_time());
    }

    double Company::invest()
    {

        int max_items = 0;
        int actual_items = 0;
        int desired_items = 0;
        double cost = 0;
        double actual_amount = 0;
        double loans = 0;
        //double loans2 = 0;
        //double desired_loans = 0;
        double available_capital = 0;
        double available_bank_financing = 0;
        double own_capital_to_invest = 0;
        //double income = 0;
        double price_out = 0;
        //double value = 0;
        double capacity_change = 0;
        double factor_change = 0;
        bool increase = true;

        //Database parameters
        double FacIncreaseRate_1 = 0.002;
        double CapIncreaseParam_1 = 8000;
        double CapIncreaseRate_1 = 0.0001;

        FacIncreaseRate_1 = getDatabaseParameter("'FacIncreaseRate_1'", city_name_);
        CapIncreaseParam_1 = getDatabaseParameter("'CapIncreaseParam_1'", city_name_);
        CapIncreaseRate_1 = getDatabaseParameter("'CapIncreaseRate_1'", city_name_);

        price_out = market_->get_price_out();
        max_items = market_->get_items();

        //Getting the desired investment for the company (after max leverage) and available items
        desired_items = fmax(0, get_desired_investment());

        //Calculating cost of the desired investment and available capital
        cost = desired_items * price_out;
        available_capital = fmax(capital_ * pbr_, 0);
        loans = fmax(0, cost - available_capital);

        //If not all money available in the bank
        available_bank_financing = fmax(0, bank_->get_max_customer_borrow());

        if (available_bank_financing < loans)
        {
            //cout << "Not enough money in bank (from company invest)" << " Desired loans: " << loans << " Avail bank cap: " << available_bank_financing << " Items" << items << " Max items " << max_items << endl;
            loans = fmax(0, available_bank_financing);
            cost = (available_capital + loans);
            desired_items = cost / price_out;
            cout << "Not enough money in bank (from company invest)"
                 << " Desired loans: " << loans << " Avail bank cap: " << available_bank_financing << " Items: " << desired_items << " Max items " << max_items << endl;
        }

        //Total amount to invest from own money
        own_capital_to_invest = cost - loans;

        //Paying market for goods

        actual_items = market_->customer_buy_items(own_capital_to_invest + loans);
        actual_amount = actual_items * price_out;

        cout << "I cmp inv, des it: " << desired_items << " Act. ite: " << actual_items << " Act. Cost: " << actual_amount << " Avail. own cap: " << available_capital << " Des. loans: " << loans << " Avail. bank cap: " << available_bank_financing << " Max it " << max_items << " " << name_ << endl;

        if (actual_amount < available_capital)
        {
            own_capital_to_invest = actual_amount;
            loans = 0;
        }
        else
        { //Need loans as well
            loans = actual_amount - own_capital_to_invest;
        }

        change_capital(-own_capital_to_invest);

        //Getting items from market
        change_stock(actual_items);
        //market_ -> change_items(-items);

        //Updating loans from bank
        change_debts(loans);
        bank_->customer_borrow_money(loans);

        log_transaction_full(name_, "Bank", loans, "Loan", clock_->get_time());
        log_transaction_full(name_, "Market", own_capital_to_invest + loans, "Investment", clock_->get_time());

        FacIncreaseRate_1 = getDatabaseParameter("'FacIncreaseRate_1'", city_name_);
        CapIncreaseParam_1 = getDatabaseParameter("'CapIncreaseParam_1'", city_name_);
        CapIncreaseRate_1 = getDatabaseParameter("'CapIncreaseRate_1'", city_name_);

        //Increasing capacity and efficiency
        capacity_change = capacity_increase(actual_items, capacity_, CapIncreaseParam_1, CapIncreaseRate_1);
        factor_change = factor_increase(actual_items, prod_const_skill_, prod_const_motivation_, capacity_, FacIncreaseRate_1);

        //cout << "I comp invest sk before: " << prod_const_skill_ << " f change: " << factor_change << " cap " << capacity_ << " c change: " << capacity_change << " for " << name_ << endl;
        //cout << "I comp invest sk before: " << prod_const_skill_ << " and after " << prod_const_skill_ + factor_change << " increase:  " << factor_change << " for " << name_ << endl;

        change_prod_const_skill(factor_change);
        change_prod_const_motivation(factor_change);
        change_capacity(capacity_change);

        //cout << " New cap: " << capacity_ << ", own capital invested: " << capital << "  Loans: " << loans << " des loans" << loans2 << "   total capital: " << cost << " available capital: " << available_capital << endl;
        //cout << "I comp inv items: " << actual_items << " Cost: " << actual_amount << " Capa ch: " << capacity_change << " Factor ch: " << factor_change << " Desired loans: " << loans << " Max items " << max_items << " Name: " << name_ << endl;

        investments_.push_front(actual_amount);

        return cost;
    }

    int Company::get_desired_investment()
    {

        double invested_items = 0;
        double item_increase = 0;
        double price_out = 0;
        double cost_of_investment = 0;
        double NPV = 0;
        double discounted_cashflows = 0;
        double borrow = 0;

        //Database parameters
        double FacIncreaseRate_1 = 0.002;
        double CapIncreaseParam_1 = 8000;
        double CapIncreaseRate_1 = 0.0001;

        FacIncreaseRate_1 = getDatabaseParameter("'FacIncreaseRate_1'", city_name_);
        CapIncreaseParam_1 = getDatabaseParameter("'CapIncreaseParam_1'", city_name_);
        CapIncreaseRate_1 = getDatabaseParameter("'CapIncreaseRate_1'", city_name_);

        invested_items = 1;
        item_increase = 2500;

        price_out = market_->get_price_out();

        while (NPV >= 0 && (debts_ + borrow) / capital_ - 1 < max_leverage_)
        {

            //Cost of investment
            cost_of_investment = price_out * invested_items;

            //If not sufficient own capital for investment, borrow money
            if (cost_of_investment > capital_ * pbr_)
            {
                borrow = cost_of_investment - capital_ * pbr_;
            }

            //calculating NPV of investment
            discounted_cashflows = get_investment_cashflow(invested_items, borrow, FacIncreaseRate_1, CapIncreaseParam_1, CapIncreaseRate_1); //items NET PRESENT VALUE OF FUTURE CASHFLOWS

            NPV = discounted_cashflows - cost_of_investment;

            //cout << "I comp des inv new items: " << invested_items_temp << " income (NPV): " << NPV << " cost: " << cost_of_investment << "  debt: " << debts_   << "  Loans: " << borrow  << endl;

            invested_items += item_increase;
        }

        //Adjusting for two extra loops
        invested_items = invested_items - 2 * item_increase;

        return invested_items;
    }

    // double Company::get_investment() {
    //
    //     double max_items = 0;
    //     double items_temp = 10;
    //     double items = 0;
    //     double cost = 0;
    //     double income = 0;
    //     double price_out = 0;
    //     double value = 0;
    //     double capacity_change = 0;
    //     double loans = 0;
    //     bool increase = true;
    //
    //     price_out = market_ -> get_price_out();
    //     max_items = market_ -> get_items();
    //
    //     while(items_temp < max_items && cost < capital_*pbr_ && (debts_ + loans)/capital_ - 1 < max_leverage_) {
    //
    //         cout << "I company get investments: NOT TO BE USED!!" << (debts_ + loans)/capital_ - 1 << endl;
    //
    //         cost = price_out * items_temp;
    //
    //         income = get_investment_cashflow(items_temp, loans);
    //
    //
    //         items_temp += 10;
    //
    //     }
    //     items = items_temp;
    //     return items;
    //
    // }

    double Company::get_investment_cashflow(double items, double loans, double FacIncreaseRate_1, double CapIncreaseParam_1, double CapIncreaseRate_1)
    {

        double interest_rate = 0;

        double capacity_incr = 0;
        double factor_change = 0;
        double new_capacity = 0;
        double old_capacity = 0;
        double production_old = 0;
        double production_new = 0;
        double pcs = 0;
        double pcm = 0;

        double value = 0;
        double price_in = 0;
        double price_out = 0;

        int t = 1;
        int size = 0;

        double mot_sum = 0;
        double skill_sum = 0;

        double loan_cost = 0;
        double sales_value = 0;
        double est_wages = 0;
        double est_prod_cost = 0;
        double zero_limit = 1;

        interest_rate = bank_->get_interest();
        price_in = market_->get_price_in();
        price_out = market_->get_price_out();
        size = employees_->get_size();
        skill_sum = employees_->get_skill_sum();
        mot_sum = employees_->get_motivation_sum();

        pcs = prod_const_skill_;
        pcm = prod_const_motivation_;

        //Capacity and efficiency increase
        capacity_incr = capacity_increase(items, capacity_, CapIncreaseParam_1, CapIncreaseRate_1);

        old_capacity = capacity_;
        new_capacity = capacity_ + capacity_incr;

        factor_change = factor_increase(items, prod_const_skill_, prod_const_motivation_, capacity_, FacIncreaseRate_1);

        loan_cost = bank_->get_loan_cost(loans);

        while (new_capacity >= zero_limit && t < 60)
        { //&& new_capacity > 0.1*capacity_initial_increase t< 20 was initially

            production_old = get_prod(skill_sum, pcs, mot_sum, pcm, old_capacity, production_function_, production_parameter_);
            production_new = get_prod(skill_sum, pcs + factor_change, mot_sum, pcm + factor_change, new_capacity, production_function_, production_parameter_);

            sales_value = (production_new - production_old) * price_in;
            est_wages = get_estimated_wages(production_new) - get_estimated_wages(production_old);
            est_prod_cost = (item_cost(production_new) - item_cost(production_old)) * price_out;

            value += (sales_value - est_prod_cost - est_wages) / (pow((1 + interest_rate), t));
            t++;

            //Simulating decay of production factors
            new_capacity -= new_capacity * decay_;
            old_capacity -= old_capacity * decay_;
            pcs -= pcs * decay_;
            pcm -= pcm * decay_;
            factor_change -= factor_change * decay_;

            //cout << "   - " << t << " " << "Capacity: " << capacity_ << " Capacity incr: " << capacity_incr << endl;
        }
        //cout << "Years:in compny casflows " << t/12 << "  Value: " << value << " Loan cost " << loan_cost << endl;
        value -= loan_cost;
        //cout << "I Company investment Cashflows - error in factor increase for skill and motivation" << endl;
        return value;
    }

    double Company::get_average_wage()
    {

        double average_wage = 0;

        list<double>::iterator theIterator;
        theIterator = wages_.begin();

        average_wage = *theIterator;

        return average_wage;
    }

    double Company::get_total_wages()
    {

        double production = 0;
        int size = 0;
        double price = 0;
        double wages = 0;
        double price_out = 0;

        size = employees_->get_size();

        if (size)
        {
            production = get_production();
            price = market_->get_price_in();
            price_out = market_->get_price_out();
        }

        list<double>::iterator theIterator;
        theIterator = wages_.begin();
        wages = (production * price - get_items_for_production() * price_out) * wage_const_;

        /*
     * Letting the wages change unlimited to let the system get to equilibrium
     * for the first 70 loops. After that we don't let it change by more than
     * 'wage_change_limit_'
     */

        if (clock_->get_time() > 30)
        {
            if (wages / size > *theIterator * (1 + wage_change_limit_))
            {
                wages = *theIterator * (1 + wage_change_limit_) * size;
            }
            if (wages / size < *theIterator * (1 - wage_change_limit_))
            {
                wages = *theIterator * (1 - wage_change_limit_) * size;
            }
        }

        return wages;
    }

    double Company::get_estimated_wages(double production)
    {

        int size = 0;
        double price = 0;
        double wages = 0;
        double price_out = 0;

        size = employees_->get_size();

        price = market_->get_price_in();
        price_out = market_->get_price_out();

        wages = (production * price - get_items_for_production() * price_out) * wage_const_;

        return wages;
    }

    double Company::pay_employees_individual(double income_tax)
    {
        double size = 0;
        double wage_tot = 0;
        double wage = 0;
        double price = 0;
        double income_tax_sum = 0;
        double skill_sum = 0;
        double motivation_sum = 0;

        price = market_->get_price_in();
        size = employees_->get_size();

        skill_sum = employees_->get_skill_sum();
        motivation_sum = employees_->get_motivation_sum();

        wage_tot = get_total_wages();
        //cout << name_ << "I company pay wage employ1" << endl;

        if (size)
        {
            wage = wage_tot / size;
            income_tax_sum = employees_->pay_employees_individual(wage_tot, skill_sum, motivation_sum, income_tax, name_);
            capital_ -= wage_tot;
            //log_transaction(name_, -wage_tot, "Salary", clock_ ->  get_time());
        }

        //cout << "I company pay wages: " << wage_tot << " income tax est: " << wage_tot*income_tax << " " << name_ << endl;
        wages_.push_front(wage);
        employees_no_.push_front(size);

        return income_tax_sum;

        //cout << "I company pay employ23" << endl;
    }

    void Company::pay_employees()
    {
        double size = 0;
        double wage_tot = 0;
        double wage = 0;
        double price = 0;
        //double sum_after = 0;

        price = market_->get_price_in();
        size = employees_->get_size();

        wage_tot = get_total_wages();
        //cout << name_ << "I company pay wage employ1" << endl;

        if (size)
        {
            wage = wage_tot / size;
            employees_->pay_employees(wage);
            capital_ -= wage_tot;
            log_transaction(name_, -wage_tot, "Salary", clock_->get_time());
        }

        //  cout << name_ << "    "  << "     I company pay wage employ2: " << wage << endl;
        wages_.push_front(wage);
        employees_no_.push_front(size);

        //cout << "I company pay employ23" << endl;
    }

    void Company::pay_interest()
    {
        //double amount = 0;
        double max_amount = 0;
        double interest = 0;

        //interest = bank_ -> get_interest();
        //amount = debts_*interest;

        max_amount = fmax(capital_, 0);
        interest = bank_->customer_pay_interest(debts_, max_amount, 1);

        change_capital(-interest);

        log_transaction_full(name_, "Bank", interest, "Interest", clock_->get_time());
    }

    void Company::repay_to_bank()
    {

        double amount = 0;
        double repayment = 0;

        //amount = fmax(amount,0);

        repayment = bank_->customer_repay_loans(debts_, capital_, 1);

        change_capital(-repayment);
        change_debts(-repayment);
        //  bank_ -> change_assets(amount);

        log_transaction_full(name_, "Bank", repayment, "Amortization", clock_->get_time());
    }

    double Company::pay_dividends()
    {
        double capital = 0;

        capital = capital_;

        if (capital > 0)
        {
            capital_ = 0;
        }
        else
        {
            capital = 0;
        }

        log_transaction(name_, -capital, "Dividend", clock_->get_time());

        return capital;

        profit_.push_front(capital_);
        employees_no_.push_front(employees_->get_size());
    }

    void Company::buy_items_for_production()
    {
        int desired_items = 0;
        int actual_items = 0;
        double price = 0;
        double desired_amount = 0;
        double actual_amount = 0;

        desired_items = get_items_for_production();
        price = market_->get_price_out();
        desired_amount = desired_items * price;

        //  cout << "I comapny buy items, cost = " << items << endl;

        actual_items = market_->customer_buy_items(desired_amount);
        actual_amount = actual_items * price;

        change_capital(-actual_amount);
        //market_ -> change_capital(amount);
        //market_ -> change_items(-items);

        log_transaction_full(name_, "Market", actual_amount, "Inventory", clock_->get_time());
    }

    //void Company::invest() {
    //  double investment = 0;
    //  double limit = 500000;
    //  if(capital_ > 0 && investment < limit) {
    //    investment = invest_ * capital_;
    //capital_ -= investment;

    /*
 * Borde kunna investera bade i storlek, dvs rate, och effektivitet, dvs 
 * prod const skill och motivation. Gor ett enkelt forsok, men borde eg
 *kolla pa reapektive derivator
 */
    //  }

    //else if(investment > limit) {
    //investment = limit;
    //}

    // prod_const_motivation_ *= 1 + 0.5*investment/limit;
    // prod_const_skill_ *= 1 + 0.5*investment/limit;

    //}
