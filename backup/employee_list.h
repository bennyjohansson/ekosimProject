#ifndef EMPLOYEE_LIST_H
#define EMPLOYEE_LIST_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "consumer.h"
#include "consumer_list.h"

using namespace std;

class Employee_list : public Consumer_list {
 public:
  Employee_list();
  Employee_list(string name_string);

  void add_employee(Consumer * consumer);

  double get_wage();
  void set_vage(double wage);
  void change_wage(double wage);

 private:
  
  double wage_;
}
  
#endif
