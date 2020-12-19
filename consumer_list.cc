#include <iostream>
#include <iomanip>
#include <string>
//#include <tuple>

//#include "element_consumer.h"
#include "consumer_list.h"
//#include "consumer.h"
#include "error_no_return.h"
#include "functions.h"
#include "SQLfunctions.h"

using namespace std;

Consumer_list::Consumer_list() : name_(""),
                                 list_(0),
                                 size_(0)

{
}

Consumer_list::Consumer_list(string name_string) : name_(name_string),
                                                   list_(0),
                                                   size_(0)
{
}

/*
 * Info-functions
 */

void Consumer_list::info()
{
  double total_cap = 0;
  double total_spendwill = 0;
  double average_skill = 0;
  double average_motivation = 0;
  long items = 0;
  int employed = 0;
  int unemployed = 0;
  //int size = 0;
  int trustworthy = 0;

  if (list_)
  {
    cout << "Listname: " << name_ << endl
         << "------------------------" << endl
         << "Listsize: " << size_ << endl;

    total_cap = get_capital_sum();
    average_motivation = get_motivation_sum() / size_;
    average_skill = get_skill_sum() / size_;
    total_spendwill = get_spendwill_sum();
    items = get_item_sum();
    employed = get_employed();
    unemployed = get_unemployed();
    trustworthy = get_trustworthy();

    cout << "Employed: " << employed << endl
         << "Unemployed: " << unemployed << endl
         << "Accumulated capital: " << total_cap << endl
         << "Accumulated items: " << items << endl
         << "Average motivation: " << average_motivation << endl
         << "Average skill: " << average_skill << endl
         << "Accumulated spendwill: " << total_spendwill << endl
         << "Trustworthy: " << trustworthy << endl
         << endl;
  }
  else
  {
    cout << "Empty list i consumer list info" << endl;
  }
}

void Consumer_list::print_list()
{
  Element_consumer *p;
  cout << "LISTNAME: " << name_ << endl;
  cout << "SIZE: " << size_ << endl
       << endl;
  if (list_)
  {
    for (p = list_; p; p = p->next_)
    {
      p->consumer_->info();
      cout << endl;
    }
  }
}

/*
 * Get-functions
 */

int Consumer_list::get_size()
{
  int size = 0;

  if (size_)
  {
    size = size_;
  }
  else
  {
    size = 0;
  }

  return size;
}

double Consumer_list::get_item_sum()
{
  Element_consumer *p;
  double sum = 0;

  if (list_)
  {
    for (p = list_; p; p = p->next_)
    {
      sum += (p->get_consumer())->get_items();
    }
    return sum;
  }
  else
  {
    return 0;
  }
}

double Consumer_list::get_skill_sum()
{

  Element_consumer *p;
  double sum = 0;

  if (list_)
  {
    for (p = list_; p; p = p->next_)
    {
      sum += p->get_skill();
    }
    return sum;
  }
  else
  {
    return 0;
  }
}

double Consumer_list::get_capital_sum()
{
  Element_consumer *p;
  double sum = 0;

  if (list_)
  {
    for (p = list_; p; p = p->next_)
    {
      sum += p->get_capital();
    }
    return sum;
  }
  else
  {
    return 0;
  }
}

double Consumer_list::get_deposit_sum()
{
  Element_consumer *p;
  double sum = 0;

  if (list_)
  {
    for (p = list_; p; p = p->next_)
    {
      sum += p->get_consumer()->get_loans();
    }
  }
  else
  {
    sum = 0;
  }
  return sum;
}

double Consumer_list::get_debts_sum()
{
  Element_consumer *p;
  double sum = 0;

  if (list_)
  {
    for (p = list_; p; p = p->next_)
    {
      sum += p->get_consumer()->get_debts();
    }
  }
  else
  {
    sum = 0;
  }
  return sum;
}

double Consumer_list::get_spendwill_sum()
{
  Element_consumer *p;
  double sum = 0;

  if (list_)
  {
    for (p = list_; p; p = p->next_)
    {
      sum += p->get_spendwill();
    }
  }
  else
  {
    sum = 0;
  }
  return sum;
}

double Consumer_list::get_motivation_sum()
{

  Element_consumer *p;
  double sum = 0;

  if (list_)
  {
    for (p = list_; p->next_; p = p->next_)
    {
      sum += p->get_skill();
    }
  }
  else
  {
    sum = 0;
  }
  return sum;
}

// std::tuple<double, double, double, double, double> Consumer_list::get_misc_sum() {

// //auto [quotient, remainder] = divide(14, 3);

//   //  cout << quotient << ',' << remainder << endl;

// 	double capital_sum = 0;
// 	double deposit_sum = 0;
// 	double borrow_sum = 0;
// 	double loanwill_sum = 0;
// 	double borrowwill_sum = 0;

// 	Element_consumer * p;
//   	double sum = 0;

// 	if(list_) {
//     	for(p = list_; p -> next_; p = p -> next_) {
//       		capital_sum += p -> get_consumer() -> get_capital();
//       		deposit_sum += p -> get_consumer()-> get_loans();
//       		borrow_sum += p -> get_consumer()-> get_borrow();
//       		loanwill_sum += p -> get_consumer()-> get_savewill();
//       		borrowwill_sum += p -> get_consumer() -> get_borrowwill();
//     	}
//   	}
//   	else {
//     	sum = 0;
//   	}

//   	return  std::make_tuple(capital_sum, deposit_sum, borrow_sum, loanwill_sum, borrowwill_sum);

// }

double Consumer_list::get_total_demand()
{

  Element_consumer *p;
  double sum = 0;
  //double sw = 0;
  //double cap = 0;
  //double loans = 0;

  if (list_)
  {
    for (p = list_; p->next_; p = p->next_)
    {

      sum += p->get_consumer()->get_demand();
      //sw = p -> get_spendwill();
      //cap = p -> get_capital();
      //loans = p -> get_loans();
      //sum += (sw*(cap + loans));
    }
  }
  else
  {
    sum = 0;
  }
  return sum;
}

double Consumer_list::get_desired_deposit_sum()
{
  Element_consumer *p;
  double sum = 0;

  for (p = list_; p; p = p->next_)
  {
    sum += p->get_consumer()->get_desired_deposit();
  }
  return sum;
}

double Consumer_list::get_desired_borrow_sum()
{
  Element_consumer *p;
  double sum = 0;

  for (p = list_; p; p = p->next_)
  {
    sum += p->get_consumer()->get_desired_borrow();
  }
  return sum;
}

double Consumer_list::get_expected_net_flow_to_bank_sum()
{
  Element_consumer *p;
  double sum = 0;

  for (p = list_; p; p = p->next_)
  {
    sum += p->get_consumer()->get_expected_net_flow_to_bank();
  }
  return sum;
}

int Consumer_list::get_employed()
{
  Element_consumer *p;
  int no = 0;

  for (p = list_; p; p = p->next_)
  {
    if (p->get_employment_status())
    {
      no++;
    }
  }
  return no;
}

int Consumer_list::get_unemployed()
{
  Element_consumer *p;
  int no = 0;

  for (p = list_; p; p = p->next_)
  {
    if (!(p->get_employment_status()))
    {
      no++;
    }
  }
  return no;
}

int Consumer_list::get_trustworthy()
{
  Element_consumer *p;
  int no = 0;

  for (p = list_; p; p = p->next_)
  {
    if (p->get_consumer()->get_trustworthy())
    {
      no++;
    }
  }
  return no;
}

Element_consumer * Consumer_list::get_first_consumer() {

  return list_;

}

Consumer *Consumer_list::get_random_consumer()
{
  int nr = (rand() % size_);
  Element_consumer *p = list_;

  //cout << "random nr: " << nr << endl;

  for (int i = 0; i < nr; i++)
  {
    //cout << i << endl;
    p = p->next_;
  }

  return p->get_consumer();
}

Consumer *Consumer_list::get_consumer(string name)
{
  Element_consumer *p;

  if (list_)
  {
    for (p = list_; p; p = p->next_)
    {
      if (p->get_consumer()->get_name() == name)
      {
        return p->get_consumer();
      }
    }
    throw no_return_error("Cant find the consumer");
  }
  else
  {
    throw no_return_error("No list");
  }
}

bool Consumer_list::is_consumer(Consumer *consumer)
{

  Element_consumer *p = list_;

  if (list_)
  {
    for (; p; p = p->next_)
    {
      if (consumer == p->get_consumer())
      {
        return true;
      }
    }
  }
  else
  {
    return false;
  }
  return false;
}

Consumer *Consumer_list::get_optimal_consumer(double skill_we,
                                              double mot_we, double capacity, int production_function, double production_parameter)
{
  Element_consumer *p;
  Element_consumer *best = new Element_consumer(0, new Consumer(0, 0, 0, 0));
  best->set_employment_status(true);

  if (!list_)
  {
    throw no_return_error("No optimal consumer");
  }

  for (p = list_; p; p = p->next_)
  {
    Consumer *consumer = p->get_consumer();
    Consumer *besta = best->get_consumer();

    //    cout <<"I consumer list get optimal" << p -> get_skill() << " x  " << best -> get_skill() << "  " << get_prod(consumer, capacity) << " " <<  get_prod(besta, capacity) << endl;

    if ((get_prod(consumer, capacity, production_function, production_parameter) > get_prod(besta, capacity, production_function, production_parameter)) && !(p->get_employment_status())) {
    //if ((get_prod(consumer, capacity, production_function, production_parameter) > get_prod(besta, capacity, production_function, production_parameter))) {
      best = p;
      //	cout << "I consumer list get optimal" << p -> get_skill() << " x  " << best -> get_skill() << endl;
    }
  }

  if (p == best)
  {
    throw no_return_error("No optimal consumer");
  }

  return best->get_consumer();
}

Consumer *Consumer_list::get_usless_employee(double skill, double mot, double capacity, int production_function, double production_parameter)
{

  Element_consumer *p;
  Element_consumer *worst = new Element_consumer(0, new Consumer(3, 3, 3, 3));
  Element_consumer *wors = worst;
  wors->get_consumer()->set_employment_status(true);

  if (!list_)
  {
    throw no_return_error("No usless consumer");
  }

  for (p = list_; p; p = p->next_)
  {
    Consumer *consumer = p->get_consumer();
    Consumer *worst = wors->get_consumer();

    if (get_prod(consumer, capacity, production_function, production_parameter) < get_prod(worst, capacity, production_function, production_parameter))
    {
      wors = p;
    }
  }

  if (wors == worst)
  {
    throw no_return_error("No usless consumer");
  }
  //  cout << "I cons list get usles" << endl;
  return wors->get_consumer();
}

/*
 * Set-functions
 */

void Consumer_list::set_name(string name_string)
{
  name_ = name_string;
}

/*
 * Functions for adding and removing consumers
 */

void Consumer_list::add_first(Consumer *cons)
{
  if (!(cons->get_employment_status()))
  {
    if (list_)
    {
      list_ = new Element_consumer(list_, cons);
    }
    else
    {
      list_ = new Element_consumer(0, cons);
    }
    size_++;
  }
}

void Consumer_list::add_last(Consumer *cons)
{
  Element_consumer *p;
  size_++;
  if (list_)
  {
    for (p = list_; p->next_; p = p->next_)
    {
    }
    p->next_ = new Element_consumer(0, cons);
  }
  else
  {
    list_ = new Element_consumer(0, cons);
  }
}

void Consumer_list::remove_consumer(Consumer *consumer, double capacity)
{

  Element_consumer *p = list_;
  Element_consumer *q = list_;

  //check that the list is not empty and if the first consumer is the one to remove
  if (list_ && list_->get_consumer() == consumer)
  {

    list_ = (p->next_);
    size_--;
    consumer->set_employment_status(false);
    consumer->set_employer("");
  }

  //If list not empty and not the first consumer
  else if (list_)
  {

    for (p = list_->next_; p; p = p->next_)
    {

      //Is it the consumer we are pointing at?
      if (p->get_consumer() == consumer)
      {
        size_--;
        q->next_ = (p->next_);
        p->get_consumer()->set_employment_status(false);
      }
      q = q->next_;
    }
  }
  else
  {
    consumer->set_employment_status(true);
    cout << "The bitch is not employed here, error in remove_consumer in consumer_list" << endl;
  }
}

/*
 * Functions to update and operate on the list
 */

void Consumer_list::update(double spendwill, double borrowwill)
{

  Element_consumer *p = 0;

  for (p = list_; p; p = p->next_)
  {
    p->consumer_->update_values(spendwill, borrowwill);
  }
}

double Consumer_list::consumers_buy()
{
  double sum = 0;
  Element_consumer *p;

  for (p = list_; p; p = p->next_)
  {
    sum += (p->get_consumer())->buy();
  }
  //cout << "I cons list, actual consumption: " << sum << " $BJ" << endl;

  return sum;
}

void Consumer_list::deposit_and_borrow_from_bank()
{
  Element_consumer *p;

  for (p = list_; p; p = p->next_)
  {
    (p->get_consumer())->deposit_and_borrow_from_bank();
  }
}

void Consumer_list::bank_business()
{
  Element_consumer *p;
  double payed_interest_sum = 0;
  double received_interest_sum = 0;
  //double repayments = 0;

  for (p = list_; p; p = p->next_)
  {
    Consumer *consumer = p->get_consumer();
    received_interest_sum += consumer->get_interest(); //Check, some error
    payed_interest_sum += consumer->pay_interest();    //Check
    consumer->repay_to_bank();                         //Check
    //consumer -> get_repayment_from_bank(); //This is not actually happening, removing function
    consumer->deposit_and_borrow_from_bank(); //Check
  }
  cout << "I cons. list, payed interest: " << payed_interest_sum << endl;
  cout << "I cons. list, rece. interest: " << received_interest_sum << endl;
}

void Consumer_list::deposit_money_to_bank()
{
  Element_consumer *p;

  for (p = list_; p; p = p->next_)
  {
    (p->get_consumer())->deposit_to_bank();
  }
}

void Consumer_list::borrow_money_from_bank()
{
  Element_consumer *p;

  for (p = list_; p; p = p->next_)
  {
    (p->get_consumer())->borrow_from_bank();
  }
}

void Consumer_list::get_repayment_from_bank()
{
  Element_consumer *p;

  for (p = list_; p; p = p->next_)
  {
    (p->get_consumer())->get_repayment_from_bank();
  }
}

void Consumer_list::repay_to_bank()
{
  Element_consumer *p;

  for (p = list_; p; p = p->next_)
  {
    (p->get_consumer())->repay_to_bank();
  }
}

void Consumer_list::get_and_pay_interest()
{
  Element_consumer *p;

  for (p = list_; p; p = p->next_)
  {
    Consumer *consumer = p->get_consumer();
    consumer->get_interest();
    consumer->pay_interest();
  }
}

void Consumer_list::pay_employees(double wage)
{

  Element_consumer *p;

  for (p = list_; p; p = p->next_)
  {
    Consumer *consumer = p->get_consumer();
    consumer->change_capital(wage);
    consumer->set_income(wage);
  }
}

double Consumer_list::pay_employees_individual(double wage_sum, double skill_sum, double motivation_sum, double income_tax, string employer, int pay_wages_in_cash)
{

  Element_consumer *p;
  double skill = 0;
  double my_wage = 0;
  double my_income_tax = 0;
  double income_tax_sum = 0;
  string country = "";

  for (p = list_; p; p = p->next_)
  {
    Consumer *consumer = p->get_consumer();
    skill = consumer->get_skill();
    my_wage = wage_sum * skill / skill_sum;
    my_income_tax = my_wage * income_tax;
    consumer->set_income(my_wage);
    income_tax_sum += my_income_tax;
    country = consumer -> get_country();



  if(pay_wages_in_cash = 1) {
      consumer->change_capital(my_wage - my_income_tax);
  }
  else {
    consumer -> accept_deposit(my_wage - my_income_tax);
    cout << "Paying wage to deposit account" << endl;
  }
    //




    log_transaction_full(employer, consumer->get_name(), my_wage, "Salary", consumer->get_time());
  }

  return income_tax_sum;
}

void Consumer_list::pay_dividends(double amount)
{

  Element_consumer *p;

  for (p = list_; p; p = p->next_)
  {
    Consumer *consumer = p->get_consumer();
    consumer->change_capital(amount);
  }
}

void Consumer_list::pay_dividends_log(double amount, string party_pay)
{

  Element_consumer *p;

  for (p = list_; p; p = p->next_)
  {
    Consumer *consumer = p->get_consumer();
    //consumer -> change_capital(amount);
    consumer->accept_deposit(amount);
    log_transaction_full(party_pay, consumer->get_name(), amount, "Dividends", consumer->get_time());
  }
}

void Consumer_list::pay_transfers_log(double amount, string party_pay)
{

  Element_consumer *p;

  for (p = list_; p; p = p->next_)
  {
    Consumer *consumer = p->get_consumer();
    //consumer -> change_capital(amount);
    consumer->accept_deposit(amount);
    log_transaction_full(party_pay, consumer->get_name(), amount, "Dividends", consumer->get_time());
  }
}

void Consumer_list::pay_all_dividends_log(double amount_company, double amount_market, double amount_bank)
{

  Element_consumer *p;
  int time = 0;
  string name;

  for (p = list_; p; p = p->next_)
  {
    Consumer *consumer = p->get_consumer();

    name = consumer->get_name();
    time = consumer->get_time();

    consumer->change_capital(amount_company);
    log_transaction_full("Company", name, amount_company, "Dividends", time);

    consumer->change_capital(amount_market);
    log_transaction_full("Market", name, amount_market, "Dividends", time);

    consumer->change_capital(amount_bank);
    log_transaction_full("Bank", name, amount_bank, "Dividends", time);
  }
}
