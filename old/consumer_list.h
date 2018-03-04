#ifndef CONSUMER_LIST_H
#define CONSUMER_LIST_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "element_consumer.h"
#include "consumer.h"

using namespace std;

class Consumer_list {
 public:
  Consumer_list();
  Consumer_list(string name_string);
  
  void info();

  int get_size();
  double get_skill_sum();
  double get_motivation_sum();
  double get_capital_sum();
  double get_spendwill_sum();
  double get_item_sum();
  int get_employed();
  int get_unemployed();
  Consumer * get_random_consumer();
  void set_name(string name_string);
  
  void add_first(Consumer * cons);
  void add_last(Consumer * cons);
  void add_group_last(Element_consumer * workers);
  void empty_list();
  void print_list();
  
  void remove_consumer(Consumer *, double);
  void remove_by_skill(double skill_limit);
  void remove_by_motivation(double motivation_limit);

  Consumer * get_optimal_consumer(double, double, double);
  Consumer * get_usless_employee(double, double, double);
  Element_consumer * get_motivated_consumers();
  void update(double);  
  void pay_employees(double, double, double);
  void pay_employees(double);
  void pay_dividends(double);
  
  void consumers_buy();

 protected:

  string name_;
  Element_consumer * list_;
  int size_;
  
};
#endif

