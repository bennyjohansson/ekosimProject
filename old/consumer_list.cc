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

void Consumer_list::info() {
  if (list_) {
    cout << "Listname: " << name_ << endl
	 << "Listsize: " << size_ << endl;
    
    double total_cap = get_capital_sum();
    double total_mot = get_motivation_sum();
    double total_spendwill = get_spendwill_sum();
    double total_items = get_item_sum();
    int employed = get_employed();
    int unemployed = get_unemployed();
    
    cout << "Employed: " << employed << endl
	 << "Unemployed: " << unemployed << endl
	 << "Accumulated capital: " << total_cap << endl
	 << "Accumulated items: " << total_items << endl
	 << "Average motivation: " << total_mot/size_ << endl 
	 << "Accumulated spendwill: " << total_spendwill << endl << endl;
  }
  else {
    cout << "Empty list i consumer list info" << endl;
  }
}
  
  
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
  //int n = 0;
  if(list_) {
    for(p = list_; p; p = p -> next_) {//p->next_
      sum += p -> get_capital();
      //n++;
    } 
    return sum;
  }
  else {
    return 0;
  }
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
  //int n = 0;
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
  int nr = (rand()%size_);
  //cout << nr << endl;
  Element_consumer * p = list_;
  for(int i = 0; i < nr; i++) {
    //cout << i << " ";
    p = p -> next_;
  }
  return p -> get_consumer();
}

void Consumer_list::set_name(string name_string) {
  name_ = name_string;
}

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

void Consumer_list::print_list() {
  Element_consumer *p;
  cout << "LISTNAME: " << name_ << endl;
  cout << "SIZE: " << size_ << endl << endl;
  if(list_) {
    for(p = list_; p; p = p->next_) {
      p->consumer_->info();
      cout << endl;
    }
  }
}

void Consumer_list::update(double factor) {
//  cout << factor << "i cons list update" << endl;  
  Element_consumer *p;
  for(p = list_; p; p = p->next_) {
    p->consumer_->update_values(factor);
  }
}



Element_consumer * Consumer_list::get_motivated_consumers() {
  
  Element_consumer *p;
  Element_consumer *lista = 0;
  for(p = list_; p; p = p -> next_) {
    if((p -> get_motivation() > 0) &&
	!(p -> get_employment_status())) {
      lista = new Element_consumer(lista, p -> get_consumer());
    }
  }
  return lista;
}

void Consumer_list::add_group_last(Element_consumer * workers) {
  
  Element_consumer *p; 
  
  //Determining the size of the group
  Element_consumer *test;
  int size = 0;
  for(test = workers; test -> next_; test = test -> next_) {
    size++;
  }
  
  if(list_) {
    p = list_;
    for(p; p->next_;p = p->next_) {
    }
    p -> next_ = workers;
    size_ += (size + 1);
  } 
  else {
    list_ = workers;
    size_ += (size + 1);
  }
}

//*
//Kolla sa att vi inte missar den sista konsumenten me mitt break i sista ifsatsen
//
void Consumer_list::remove_consumer(Consumer * consumer, double capacity) {
 
   Element_consumer * p = list_;
   Element_consumer * q = list_;

  if(list_ && list_ -> get_consumer() == consumer) {//kollar sa inte tom och om det ar forsta
    
    if(p -> next_) {//om det finns en till sa skippar vi bara den forsta
      list_ = p -> next_;
      size_--;
      consumer -> set_employment_status(false);
    }

    else { //annars blir listan tom
      list_ = 0;
      size_ = 0;
      consumer -> set_employment_status(false);
    }
  }

  else if(list_) {//om den inte ar tom, och det inte ar forsta
    
    for(p = list_ -> next_; p; p = p -> next_) {
      
      //nu ar det den vi pekar pa och inte den sista?
      if((p -> get_consumer()) == consumer && p -> next_) {
	 size_--;
	 q -> next_ = (p -> next_);
         consumer -> set_employment_status(false);
      } 

      //nu ar det den sistaoch den vi pekar pa
      else if(p -> get_consumer() == consumer) {
	q -> next_ = 0;
	size_--;
        consumer -> set_employment_status(false);
      }
      q = q -> next_;
    }
  }
  else {
     consumer -> set_employment_status(true);
     cout << "The bitch is not employed here, error in remove_consumer in consumer_list" << endl;
  }
}

/* Should only be used from a company, make private and friend
 */

void Consumer_list::remove_by_skill(double skill_limit) {
  Element_consumer *p = list_;

  //Check he first consumers
  //while(list_ -> get_skill() < skill_limit) {
  //  p -> set_employment_status(false);
  //  list_ = p -> next_;
  //  p = list_;
  //  size_--;
  //} 
  
  //And the rest of them
  //for(p; p -> next_; p = p -> next_)  {
  //  if((p -> next_) -> get_skill() < skill_limit) {
//	(p -> next_ ) -> set_employment_status(false);
//	size_--;
//	if((p -> next_) -> next_) {
//		p -> next_ = ((p -> next_) -> next_);
//	}
//	else {
//		p -> next_ = 0;
 //	}
   // }
  //}
}


void Consumer_list::remove_by_motivation(double motivation_limit) {
  Element_consumer *p = list_;

  //Check the first consuer
  //if(p -> get_motivation() < motivation_limit) {
  //  p -> get_consumer() -> set_employment_status(false); 
  //  list_ = p -> next_;
  //  size_--;
  //  p = list_;
  //}
  //And the rest of them

  //for(p = list_; p -> next_; p = p -> next_) {
  //  if((p -> next_) -> get_motivation() < motivation_limit) {
//	(p -> next_) -> set_employment_status(false);
//	size_--;
//	if((p -> next_) -> next_) {
//		p -> next_ = ((p -> next_) -> next_);
  //      }
//	else {
//		p -> next_ = 0;
//	     }
  //      }  
    //} 
}

//Denna maste skrivas om...
Consumer * Consumer_list::get_optimal_consumer(double skill_we, 
					       double mot_we, double capacity) { 
  Element_consumer *p;
  Element_consumer * best = new Element_consumer(0, new Consumer(0,0,0,0));
  if(!list_) {
    throw no_return_error("no optimal consumer");
  }
  for(p = list_; p; p = p -> next_) {
    Consumer * consumer = p -> get_consumer();
    Consumer * besta = best ->  get_consumer();
    if((get_prod(consumer, capacity) > get_prod(besta, capacity)) 
       && !(p -> get_employment_status()))
      {
	best = p;
      }
  }
 //best -> get_consumer() -> info(); 
 return best -> get_consumer();
}

Consumer * Consumer_list::get_usless_employee(double skill, double mot, double capacity){

  Element_consumer * p;
  Element_consumer * wors = new Element_consumer(0, new Consumer(1.01,1.01,1.01,1.01));
  wors -> get_consumer() -> set_employment_status(true);
  if(!list_) {
     throw no_return_error("no optimal consumer");
  }
  
  for(p = list_; p -> next_; p = p -> next_) {
    Consumer * consumer = p -> get_consumer();
    Consumer * worst = wors -> get_consumer();

    if(get_prod(consumer, capacity) < get_prod(worst, capacity)) {
      wors =  p;
    }
  }
//  p -> get_consumer() -> info();
  return wors -> get_consumer();
}


void Consumer_list::pay_employees(double skill_c, double mot_c, double
				  wage_c) {

  Element_consumer * p;

  for(p = list_; p ; p = p -> next_) {
	Consumer * consumer = p -> get_consumer();
	double skill = consumer -> get_skill();
	double mot = consumer -> get_motivation();
	double wage = wage_c*(mot * mot_c + skill * skill_c);
	consumer -> change_capital(wage);
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

void Consumer_list::consumers_buy() {

  Element_consumer * p;

  for(p = list_; p; p = p -> next_){
    (p -> get_consumer()) -> buy();
  }
}












