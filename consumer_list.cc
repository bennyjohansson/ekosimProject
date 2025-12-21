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
                                 list_(nullptr),
                                 size_(0)

{
}

Consumer_list::Consumer_list(string name_string) : name_(name_string),
                                                   list_(nullptr),
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
    for (p = list_.get(); p; p = p->next_.get())
    {
      p->consumer_->info();
      cout << endl;
    }
  }
}

/*
 * Get-functions
 */

int Consumer_list::get_size() const
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

double Consumer_list::get_item_sum() const
{
  Element_consumer *p;
  double sum = 0;

  if (list_)
  {
    for (p = list_.get(); p; p = p->next_.get())
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

double Consumer_list::get_skill_sum() const
{

  Element_consumer *p;
  double sum = 0;

  if (list_)
  {
    for (p = list_.get(); p; p = p->next_.get())
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

double Consumer_list::get_capital_sum() const
{
  Element_consumer *p;
  double sum = 0;

  if (list_)
  {
    for (p = list_.get(); p; p = p->next_.get())
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

double Consumer_list::get_deposit_sum() const
{
  Element_consumer *p;
  double sum = 0;

  if (list_)
  {
    for (p = list_.get(); p; p = p->next_.get())
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

double Consumer_list::get_debts_sum() const
{
  Element_consumer *p;
  double sum = 0;

  if (list_)
  {
    for (p = list_.get(); p; p = p->next_.get())
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

double Consumer_list::get_spendwill_sum() const
{
  Element_consumer *p;
  double sum = 0;

  if (list_)
  {
    for (p = list_.get(); p; p = p->next_.get())
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

double Consumer_list::get_motivation_sum() const
{

  Element_consumer *p;
  double sum = 0;

  if (list_)
  {
    for (p = list_.get(); p->next_; p = p->next_.get())
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

double Consumer_list::get_total_demand() const
{

  Element_consumer *p;
  double sum = 0;
  //double sw = 0;
  //double cap = 0;
  //double loans = 0;

  if (list_)
  {
    for (p = list_.get(); p->next_; p = p->next_.get())
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

double Consumer_list::get_desired_deposit_sum() const
{
  Element_consumer *p;
  double sum = 0;

  for (p = list_.get(); p; p = p->next_.get())
  {
    sum += p->get_consumer()->get_desired_deposit();
  }
  return sum;
}

double Consumer_list::get_desired_borrow_sum() const
{
  Element_consumer *p;
  double sum = 0;

  for (p = list_.get(); p; p = p->next_.get())
  {
    sum += p->get_consumer()->get_desired_borrow();
  }
  return sum;
}

double Consumer_list::get_expected_net_flow_to_bank_sum() const
{
  Element_consumer *p;
  double sum = 0;

  for (p = list_.get(); p; p = p->next_.get())
  {
    sum += p->get_consumer()->get_expected_net_flow_to_bank();
  }
  return sum;
}

int Consumer_list::get_employed() const
{
  Element_consumer *p;
  int no = 0;

  for (p = list_.get(); p; p = p->next_.get())
  {
    if (p->get_employment_status())
    {
      no++;
    }
  }
  return no;
}

int Consumer_list::get_unemployed() const
{
  Element_consumer *p;
  int no = 0;

  for (p = list_.get(); p; p = p->next_.get())
  {
    if (!(p->get_employment_status()))
    {
      no++;
    }
  }
  return no;
}

int Consumer_list::get_trustworthy() const
{
  Element_consumer *p;
  int no = 0;

  for (p = list_.get(); p; p = p->next_.get())
  {
    if (p->get_consumer()->get_trustworthy())
    {
      no++;
    }
  }
  return no;
}

Element_consumer *Consumer_list::get_first_consumer()
{

  return list_.get();
}

Consumer *Consumer_list::get_random_consumer()
{
  int nr = (rand() % size_);
  Element_consumer *p = list_.get();

  //cout << "random nr: " << nr << endl;

  for (int i = 0; i < nr; i++)
  {
    //cout << i << endl;
    p = p->next_.get();
  }

  return p->get_consumer();
}

Consumer *Consumer_list::get_consumer(string name)
{
  Element_consumer *p;

  if (list_)
  {
    for (p = list_.get(); p; p = p->next_.get())
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

bool Consumer_list::is_consumer(Consumer *consumer) const
{

  Element_consumer *p = list_.get();

  if (list_)
  {
    for (; p; p = p->next_.get())
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
  auto best_temp = std::make_unique<Element_consumer>(nullptr, new Consumer(0, 0, 0, 0));
  Element_consumer *best = best_temp.get();
  best->set_employment_status(true);

  if (!list_)
  {
    throw no_return_error("No optimal consumer");
  }

  for (p = list_.get(); p; p = p->next_.get())
  {
    Consumer *consumer = p->get_consumer();
    Consumer *besta = best->get_consumer();

    //    cout <<"I consumer list get optimal" << p -> get_skill() << " x  " << best -> get_skill() << "  " << get_prod(consumer, capacity) << " " <<  get_prod(besta, capacity) << endl;

    if ((get_prod(consumer, capacity, production_function, production_parameter) > get_prod(besta, capacity, production_function, production_parameter)) && !(p->get_employment_status()))
    {
      //if ((get_prod(consumer, capacity, production_function, production_parameter) > get_prod(besta, capacity, production_function, production_parameter))) {
      best = p;
      //	cout << "I consumer list get optimal" << p -> get_skill() << " x  " << best -> get_skill() << endl;
    }
  }

  if (best == best_temp.get())
  {
    throw no_return_error("No optimal consumer");
  }

  return best->get_consumer();
}

Consumer *Consumer_list::get_usless_employee(double skill, double mot, double capacity, int production_function, double production_parameter)
{

  Element_consumer *p;
  auto worst_temp = std::make_unique<Element_consumer>(nullptr, new Consumer(3, 3, 3, 3));
  Element_consumer *wors = worst_temp.get();
  wors->get_consumer()->set_employment_status(true);

  if (!list_)
  {
    throw no_return_error("No usless consumer");
  }

  for (p = list_.get(); p; p = p->next_.get())
  {
    Consumer *consumer = p->get_consumer();
    Consumer *worst = wors->get_consumer();

    if (get_prod(consumer, capacity, production_function, production_parameter) < get_prod(worst, capacity, production_function, production_parameter))
    {
      wors = p;
    }
  }

  if (wors == worst_temp.get())
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

void Consumer_list::set_market(Market * newMarket) {

  Element_consumer *p;
  
  for (p = list_.get(); p; p = p->next_.get())
  {
    p->get_consumer()->set_market(newMarket);
  }
}

void Consumer_list::set_intecity_trading(bool enable) {
  Element_consumer *p;

  for (p = list_.get(); p; p = p->next_.get())
  {
    p->get_consumer()->set_enable_intercity_trading(enable);
  }
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
      list_ = std::make_unique<Element_consumer>(std::move(list_), cons);
    }
    else
    {
      list_ = std::make_unique<Element_consumer>(nullptr, cons);
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
    for (p = list_.get(); p->next_; p = p->next_.get())
    {
    }
    p->next_ = std::make_unique<Element_consumer>(nullptr, cons);
  }
  else
  {
    list_ = std::make_unique<Element_consumer>(nullptr, cons);
  }
}

void Consumer_list::add_multiple_last(Element_consumer * list)
{
  int list_length = 0;
  Element_consumer *temp = list;
  while (temp != nullptr)
  {
    list_length++;
    temp = temp->next_.get();
  }
  size_ += list_length;

  Element_consumer *p;
  
  if (list_)
  {
    for (p = list_.get(); p->next_; p = p->next_.get())
    {
    }
    // Convert raw pointer to unique_ptr and attach to the chain
    p->next_ = std::unique_ptr<Element_consumer>(list);
  }
  else
  {
    // Convert raw pointer to unique_ptr and make it the head of the list
    list_ = std::unique_ptr<Element_consumer>(list);
  }
}

void Consumer_list::remove_consumer(Consumer *consumer, double capacity)
{

  Element_consumer *p = list_.get();
  Element_consumer *q = list_.get();

  //check that the list is not empty and if the first consumer is the one to remove
  if (list_ && list_->get_consumer() == consumer)
  {

    list_ = std::move(p->next_);
    size_--;
    consumer->set_employment_status(false);
    consumer->set_employer("");
  }

  //If list not empty and not the first consumer
  else if (list_)
  {
    q = list_.get();
    for (p = list_->next_.get(); p; p = p->next_.get())
    {

      //Is it the consumer we are pointing at?
      if (p->get_consumer() == consumer)
      {
        // Set employment status BEFORE removing from list
        p->get_consumer()->set_employment_status(false);
        p->get_consumer()->set_employer("");
        
        size_--;
        q->next_ = std::move(p->next_);
        break; // Exit loop after removal
      }
      q = p; // Move q to current p for next iteration
    }
  }
  else
  {
    consumer->set_employment_status(true);
    cout << "The bitch is not employed here, error in remove_consumer in consumer_list" << endl;
  }
}

void Consumer_list::remove_shareholder(Consumer *consumer)
{
  Element_consumer *p = list_.get();
  Element_consumer *q = list_.get();

  // Check that the list is not empty and if the first consumer is the one to remove
  if (list_ && list_->get_consumer() == consumer)
  {
    list_ = std::move(p->next_);
    size_--;
  }

  // If list not empty and not the first consumer
  else if (list_)
  {
    q = list_.get();
    for (p = list_->next_.get(); p; p = p->next_.get())
    {
      // Is it the consumer we are pointing at?
      if (p->get_consumer() == consumer)
      {
        size_--;
        q->next_ = std::move(p->next_);
        break; // Exit loop after removal
      }
      q = p; // Move q to current p for next iteration
    }
  }
  else
  {
    cout << "The consumer is not a shareholder here, error in remove_shareholder in consumer_list" << endl;
  }
}

/*
 * Functions to update and operate on the list
 */

void Consumer_list::update(double spendwill, double borrowwill)
{

  Element_consumer *p = 0;

  for (p = list_.get(); p; p = p->next_.get())
  {
    p->consumer_->update_values(spendwill, borrowwill);
  }
}

double Consumer_list::consumers_buy()
{
  double sum = 0;
  Element_consumer *p;

  for (p = list_.get(); p; p = p->next_.get())
  {
    sum += (p->get_consumer())->buy();
  }
  //cout << "I cons list, actual consumption: " << sum << " $BJ" << endl;

  return sum;
}

void Consumer_list::deposit_and_borrow_from_bank()
{
  Element_consumer *p;

  for (p = list_.get(); p; p = p->next_.get())
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
  double capital_before = 0;
  double temp_capital = 0;

  capital_before = get_capital_sum() + list_.get() ->get_consumer()->get_bank() ->get_liquidity();

  for (p = list_.get(); p; p = p->next_.get())
  {
    Consumer *consumer = p->get_consumer();
    
    //Receiving interest
    received_interest_sum += consumer->get_interest(); //Check, some error
    // temp_capital = get_capital_sum() + list_.get() ->get_consumer()->get_bank() ->get_liquidity();

    // //Checking for money leakage
    // if(std::abs(temp_capital - capital_before) > 0.01 ) {
    //   cout << "Money leakage in receiving interest" << endl;
    //   capital_before = get_capital_sum() + list_.get() ->get_consumer()->get_bank() ->get_liquidity();
    // }

    //Paying interest
    payed_interest_sum += consumer->pay_interest();    //Check
    // temp_capital = get_capital_sum() + list_.get() ->get_consumer()->get_bank() ->get_liquidity();
    //Checking for money leakage
    // if(std::abs(temp_capital - capital_before) > 0.01 ) {
    //   cout << "Money leakage in paying interest" << endl;
    //   // capital_before = get_capital_sum() + list_.get() ->get_consumer()->get_bank() ->get_liquidity();
    // }
    
    //Repaying loan
    consumer->repay_to_bank();                         //Check
    //consumer -> get_repayment_from_bank(); //This is not actually happening, removing function
    temp_capital = get_capital_sum() + list_.get() ->get_consumer()->get_bank() ->get_liquidity();
    //Checking for money leakage
    // if(std::abs(temp_capital - capital_before) > 0.01 ) {
    //   cout << "Money leakage in repaying loan, leaked " << abs(temp_capital - capital_before) << endl;
    //   capital_before = get_capital_sum() + list_.get() ->get_consumer()->get_bank() ->get_liquidity();
    // }

    //Deposit and borrow from bank
    consumer->deposit_and_borrow_from_bank(); //Check
    // temp_capital = get_capital_sum() + list_.get() ->get_consumer()->get_bank() ->get_liquidity();
    //Checking for money leakage
    // if(std::abs(temp_capital - capital_before) > 0.01 ) {
    //   cout << "Money leakage in deposit and borrow from bank" << endl;
    //   // capital_before = get_capital_sum() + list_.get() ->get_consumer()->get_bank() ->get_liquidity();
    // }
  }
  cout << "I cons. list, payed interest: " << payed_interest_sum << endl;
  cout << "I cons. list, rece. interest: " << received_interest_sum << endl;
}

void Consumer_list::deposit_money_to_bank()
{
  Element_consumer *p;

  for (p = list_.get(); p; p = p->next_.get())
  {
    (p->get_consumer())->deposit_to_bank();
  }
}

void Consumer_list::borrow_money_from_bank()
{
  Element_consumer *p;

  for (p = list_.get(); p; p = p->next_.get())
  {
    (p->get_consumer())->borrow_from_bank();
  }
}

void Consumer_list::get_repayment_from_bank()
{
  Element_consumer *p;

  for (p = list_.get(); p; p = p->next_.get())
  {
    (p->get_consumer())->get_repayment_from_bank();
  }
}

void Consumer_list::repay_to_bank()
{
  Element_consumer *p;

  for (p = list_.get(); p; p = p->next_.get())
  {
    (p->get_consumer())->repay_to_bank();
  }
}

void Consumer_list::get_and_pay_interest()
{
  Element_consumer *p;

  for (p = list_.get(); p; p = p->next_.get())
  {
    Consumer *consumer = p->get_consumer();
    consumer->get_interest();
    consumer->pay_interest();
  }
}

void Consumer_list::pay_employees(double wage)
{

  Element_consumer *p;

  for (p = list_.get(); p; p = p->next_.get())
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

  for (p = list_.get(); p; p = p->next_.get())
  {
    Consumer *consumer = p->get_consumer();
    skill = consumer->get_skill();
    my_wage = wage_sum * skill / skill_sum;
    my_income_tax = my_wage * income_tax;
    consumer->set_income(my_wage - my_income_tax);
    income_tax_sum += my_income_tax;
    country = consumer->get_country();

    if (pay_wages_in_cash == 1)
    {
      consumer->change_capital(my_wage - my_income_tax);
    }
    else
    {
      consumer->accept_deposit(my_wage - my_income_tax);
      //cout << "Paying wage to deposit account" << endl;
    }
    //

    log_transaction_full(employer, consumer->get_name(), my_wage, "Salary", consumer->get_time());
  }

  return income_tax_sum;
}

void Consumer_list::pay_dividends(double amount)
{

  Element_consumer *p;

  for (p = list_.get(); p; p = p->next_.get())
  {
    Consumer *consumer = p->get_consumer();
    consumer->change_capital(amount);
  }
}

void Consumer_list::pay_dividends_log(double amount, string party_pay)
{

  Element_consumer *p;

  if(list_ == nullptr) {
    cout << "Warning: Consumer list is null, skipping dividend payments" << endl;
    return;
  }

  for (p = list_.get(); p; p = p->next_.get())
  {
    if(p == nullptr) {
      cout << "Warning: Found null element in consumer list, skipping..." << endl;
      continue;
    }
    
    Consumer *consumer = p->get_consumer();
    if(consumer == nullptr) {
      cout << "Warning: Found null consumer pointer, skipping dividend payment..." << endl;
      continue;
    }
    //consumer -> change_capital(amount);
    consumer->accept_deposit(amount);
    log_transaction_full(party_pay, consumer->get_name(), amount, "Dividends", consumer->get_time());
  }
}

void Consumer_list::pay_transfers_log(double amount, string party_pay)
{

  Element_consumer *p;

  if(list_ == nullptr) {
    cout << "Warning: Consumer list is null, skipping transfer payments" << endl;
    return;
  }

  for (p = list_.get(); p; p = p->next_.get())
  {
    if(p == nullptr) {
      cout << "Warning: Found null element in consumer list, skipping..." << endl;
      continue;
    }
    
    Consumer *consumer = p->get_consumer();
    if(consumer == nullptr) {
      cout << "Warning: Found null consumer pointer, skipping transfer payment..." << endl;
      continue;
    }
    //consumer -> change_capital(amount);
    consumer->accept_deposit(amount);
    log_transaction_full(party_pay, consumer->get_name(), amount, "Dividends", consumer->get_time());
    consumer->set_transfers(amount);
  }
}

double Consumer_list::pay_all_dividends_log(double amount_company, double amount_market, double amount_bank)
{

  Element_consumer *p;
  int time = 0;
  string name;
  int pay_dividends_in_cash = 0;

  if(list_ == nullptr) {
    cout << "Warning: Consumer list is null, skipping dividend payments" << endl;
    return 0;
  }

  for (p = list_.get(); p; p = p->next_.get())
  {
    if(p == nullptr) {
      cout << "Warning: Found null element in consumer list, skipping..." << endl;
      continue;
    }
    
    Consumer *consumer = p->get_consumer();
    if(consumer == nullptr) {
      cout << "Warning: Found null consumer pointer, skipping dividend payment..." << endl;
      continue;
    }

    try {
      name = consumer->get_name();
      time = consumer->get_time();
    } catch (const std::exception& e) {
      cout << "Error getting consumer info: " << e.what() << endl;
      continue;
    } catch (...) {
      cout << "Unknown error getting consumer info" << endl;
      continue;
    }

    try {
      if (pay_dividends_in_cash == 0)
      {
        consumer->accept_deposit(amount_company);
        consumer->accept_deposit(amount_market);
        consumer->accept_deposit(amount_bank);
      }
      else
      {
        consumer->change_capital(amount_company);
        consumer->change_capital(amount_market);
        consumer->change_capital(amount_bank);
      }
      
      log_transaction_full("Company", name, amount_company, "Dividends", time);
      log_transaction_full("Market", name, amount_market, "Dividends", time);
      log_transaction_full("Bank", name, amount_bank, "Dividends", time);
      consumer->set_dividends(amount_company + amount_market + amount_bank);
    } catch (const std::exception& e) {
      cout << "Error processing dividend payments for consumer " << name << ": " << e.what() << endl;
      continue;
    } catch (...) {
      cout << "Unknown error processing dividend payments for consumer " << name << endl;
      continue;
    }
  }
  
  return 0;
}

void Consumer_list::save_consumers()
{

  Element_consumer *p;

  for (p = list_.get(); p; p = p->next_.get())
  {
    Consumer *consumer = p->get_consumer();
    consumer->save_to_database();
  }
}