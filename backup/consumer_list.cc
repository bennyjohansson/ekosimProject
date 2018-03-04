#include <iostream>
#include <iomanip>
#include <string>

//#include "element_consumer.h"
#include "consumer_list.h"
//#include "consumer.h"
#include "error_no_return.h"
#include "functions.h"

using namespace std;

Consumer_list::Consumer_list() :
  list_(0),
  size_(0),
  name_("")
{}

Consumer_list::Consumer_list(string name_string) :
  name_(name_string),
  list_(0),
  size_(0)
{}


/*
 * Info-functions
 */

void Consumer_list::info() {
  double total_cap = 0;
  double total_spendwill = 0;
  double average_skill = 0;
  double average_motivation = 0;
  int items = 0;
  int employed = 0;
  int unemployed = 0;
  int size = 0;

  if (list_) {
    cout << "Listname: " << name_ << endl
	 << "Listsize: " << size_ << endl;
    
    total_cap = get_capital_sum();
    average_motivation = get_motivation_sum()/size_;
    average_skill = get_skill_sum()/size_;
    total_spendwill = get_spendwill_sum();
    items = get_item_sum();
    employed = get_employed();
    unemployed = get_unemployed();
    
    cout << "Employed: " << employed << endl
	 << "Unemployed: " << unemployed << endl
	 << "Accumulated capital: " << total_cap << endl
	 << "Accumulated items: " << items << endl
	 << "Average motivation: " << average_motivation << endl 
	 << "Average skill: " << average_skill << endl
	 << "Accumulated spendwill: " << total_spendwill << endl << endl;
  }
  else {
    cout << "Empty list i consumer list info" << endl;
  }
}


void Consumer_list::print_list() {
  Element_consumer *p;
  cout << "LISTNAME: " << name_ << endl;
  cout << "SIZE: " << size_ << endl << endl;
  if(list_) {
    for(p = list_; p; p = p->next_) {
      p -> consumer_->info();
      cout << endl;
    }
  }
}


/*
 * Get-functions
 */

int Consumer_list::get_size() {
  return size_;
}

double Consumer_list::get_item_sum() {
  Element_consumer * p;
  double sum = 0;

  if(list_) {
    for(p = list_; p; p = p -> next_) {
      sum += (p -> get_consumer()) -> get_items();
    }
    return sum;
  } 
  else {
    return 0;
  }
}

double Consumer_list::get_skill_sum() {
  
  Element_consumer * p;
  double sum = 0;

  if(list_) {
    for(p = list_; p; p = p -> next_) {
      sum += p -> get_skill();
    }
    return sum;
  }
  else {
    return 0;
  }
}

double Consumer_list::get_capital_sum() {
  Element_consumer * p;
  double sum = 0;

  if(list_) {
    for(p = list_; p; p = p -> next_) {
      sum += p -> get_capital();
    } 
    return sum;
  }
  else {
    return 0;
  }
}

double Consumer_list::get_loans_sum() {
 Element_consumer * p;
  double sum = 0;
  
  if(list_) {
    for(p = list_; p ; p = p -> next_) {
      sum += p -> get_consumer() -> get_loans();
    }
  }
  else {
    sum = 0;
  }
  return sum;
  
}

double Consumer_list::get_spendwill_sum() {
  Element_consumer * p;
  double sum = 0;
  
  if(list_) {
    for(p = list_; p ; p = p -> next_) {
      sum += p -> get_spendwill();
    }
  }
  else {
    sum = 0;
  }
  return sum;
} 

double Consumer_list::get_motivation_sum() {
  
  Element_consumer * p;
  double sum = 0;
  
  if(list_) {
    for(p = list_; p -> next_; p = p -> next_) {
      sum += p -> get_skill();
    }
  }
  else {
    sum = 0;
  }
  return sum;
}

double Consumer_list::get_total_demand() {
  
  Element_consumer * p;
  double sum = 0;
  double sw = 0;
  double cap = 0;
  
  if(list_) {
    for(p = list_; p -> next_; p = p -> next_) {
      sw = p -> get_spendwill();
      cap = p -> get_capital();
      sum += (sw*cap);
    }
  }
  else {
    sum = 0;
  }
  return sum;
}

double Consumer_list::get_desired_loans_sum() {
 Element_consumer * p;
 double sum = 0;
  
  for(p = list_; p; p = p -> next_) {
      sum += p -> get_consumer() -> get_desired_loans();
  }
  return sum;
}

double Consumer_list::get_desired_borrow_sum() {
 Element_consumer * p;
 double sum = 0;
  
  for(p = list_; p; p = p -> next_) {
      sum += p -> get_consumer() -> get_desired_borrow();
  }
  return sum;
}

int Consumer_list::get_employed() {
  Element_consumer * p;
  int no = 0;
  
  for(p = list_; p; p = p -> next_) {
    if(p -> get_employment_status()) {
      no++;
    }
  }
  return no;
}

int Consumer_list::get_unemployed() {
  Element_consumer * p;
  int no = 0;

  for(p = list_; p; p = p -> next_) {
    if(!(p -> get_employment_status())) {
      no++;
    }
  }
  return no;
}

Consumer * Consumer_list::get_random_consumer() {
  int nr = (rand()%size_ + 1);
  Element_consumer * p = list_;

  for(int i = 0; i < nr; i++) {
    p = p -> next_;
  }
  return p -> get_consumer();
}

bool Consumer_list::is_consumer(Consumer * consumer) {

  Element_consumer * p = list_;
  
  if(list_) {
    for (p; p; p = p-> next_) {
      if(consumer == p -> get_consumer()) {
	return true;
      } 
    }
  }
  else {
    return false;
  }
  return false;
}


Consumer * Consumer_list::get_optimal_consumer(double skill_we, 
					       double mot_we, double capacity) { 
  Element_consumer *p;
  Element_consumer * best = new Element_consumer(0, new Consumer(0,0,0,0));
  best -> set_employment_status(true);
    
  if(!list_) {
    throw no_return_error("no optimal consumer");
  }
  
  for(p = list_; p; p = p -> next_) {
    Consumer * consumer = p -> get_consumer();
    Consumer * besta = best ->  get_consumer();
   
    if((get_prod(consumer, capacity) > get_prod(besta, capacity)) && !(p -> get_employment_status())) {
	best = p;
    }
  }

  if(p == best) {
    throw no_return_error("no optimal consumer");
  }
  
  return best -> get_consumer();
}

Consumer * Consumer_list::get_usless_employee(double skill, double mot, double capacity){

  Element_consumer * p;
  Element_consumer * worst = new Element_consumer(0, new Consumer(3,3,3,3));
  Element_consumer * wors = worst;
  wors -> get_consumer() -> set_employment_status(true);
  
  if(!list_) {
    throw no_return_error("no optimal consumer");
  }
  
  for(p = list_; p; p = p -> next_) {
    Consumer * consumer = p -> get_consumer();
    Consumer * worst = wors -> get_consumer();
    
    if(get_prod(consumer, capacity) < get_prod(worst, capacity)) {
      wors =  p;
    }
  }
  
  if(wors == worst) {
    throw no_return_error("no optimal consumer");
  }
  //  cout << "I cons list get usles" << endl;
  return wors -> get_consumer();
}


/*
 * Set-functions
 */

void Consumer_list::set_name(string name_string) {
  name_ = name_string;
}


/*
 * Functions for adding and removing consumers
 */

void Consumer_list::add_first(Consumer * cons) {
  if(!(cons -> get_employment_status())) {
    if(list_) {
      list_ = new Element_consumer(list_, cons);
    }
    else {
      list_ = new Element_consumer(0, cons);
    }
    size_++;
  }
}


void Consumer_list::add_last(Consumer * cons) {
  Element_consumer *p;
  size_++;
  if(list_) {
    for(p = list_; p->next_;p = p->next_) {
    }
    p -> next_ = new Element_consumer(0, cons);
  }
  else {
    list_ = new Element_consumer(0, cons);
  }
}

void Consumer_list::remove_consumer(Consumer * consumer, double capacity) {
  
  Element_consumer * p = list_;
  Element_consumer * q = list_;
  
  
  //check that the list is not empty and if the first consumer is the one to remove
  if(list_ && list_ -> get_consumer() == consumer) {
    
    list_ = (p -> next_);
    size_--;
    consumer -> set_employment_status(false);
  }
  
  //If list not empty and not the first consumer
  else if(list_) {
    
    for(p = list_ -> next_; p; p = p -> next_) {
      
      //Is it the consumer we are pointing at?
      if(p -> get_consumer() == consumer) {
	size_--;
	q -> next_ = (p -> next_);
	p -> get_consumer() -> set_employment_status(false);
      } 
      q = q -> next_;
    }
  }
  else {
    consumer -> set_employment_status(true);
    cout << "The bitch is not employed here, error in remove_consumer in consumer_list" << endl;
  }
}


/*
 * Functions to update and operate on the list
 */

void Consumer_list::update() {  

  Element_consumer *p = 0;

  for(p = list_; p; p = p->next_) {
    p -> consumer_ -> update_values();
  }

}

void Consumer_list::consumers_buy() {

  Element_consumer * p;
  
  for(p = list_; p; p = p -> next_){
    (p -> get_consumer()) -> buy();
  }

}

void Consumer_list::deposit_money_to_bank() {
 Element_consumer * p;
  
  for(p = list_; p; p = p -> next_){
    (p -> get_consumer()) -> deposit_to_bank();
  }
}

void Consumer_list::borrow_money_from_bank() {
 Element_consumer * p;
  
  for(p = list_; p; p = p -> next_){
    (p -> get_consumer()) -> borrow_from_bank();
  }
}

void Consumer_list::get_repayment_from_bank() {
 Element_consumer * p;
  
  for(p = list_; p; p = p -> next_){
    (p -> get_consumer()) -> get_repayment_from_bank();
  }
}

void Consumer_list::repay_to_bank() {
 Element_consumer * p;
  
  for(p = list_; p; p = p -> next_){
    (p -> get_consumer()) -> repay_to_bank();
 
 }
}

void Consumer_list::get_interest() {
  Element_consumer * p;
  
  for(p = list_; p; p = p -> next_){
    (p -> get_consumer()) -> get_interest();
  }
}

void Consumer_list::pay_employees(double wage) {
  
  Element_consumer * p;
  
  for(p = list_; p; p = p -> next_) {
    Consumer * consumer = p -> get_consumer();
    consumer -> change_capital(wage);
    consumer -> set_income(wage);
  }

}

void Consumer_list::pay_dividends(double amount) {

  Element_consumer * p;

  for(p = list_; p; p = p -> next_) {
    Consumer * consumer = p -> get_consumer();
    consumer -> change_capital(amount);
  }
}











