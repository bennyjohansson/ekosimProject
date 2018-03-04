#include <iostream>
#include <iomanip>
#include <string>
#include "element_consumer.h"
#include "employee_list.h"
#include "consumer.h"

using namespace std;


Employee_list::Employee_list() :
  list_(0),
  size_(0),
  name_(""),
  wage_(0)
{}

Employee_list::Employee_list(string name_string) :
  name_(name_string),
  list_(0),
  size_(0),
  wage_(0)
{}


void add_employee(Consumer * consumer) {}

double set_wage(double wage) {
  wage_ = wage;
}
void get_vage() {
  return wage_;
}

void change_wage(double wage) {
  wage_ += wage;
}



