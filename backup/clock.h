#ifndef CLOCK_H
#define CLOCK_H


#include <iostream>
#include <iomanip>
#include <string>
//#include "market.h"
//#include "consumer.h"

using namespace std;

class Clock {
 public:

  Clock();

  int get_time();
  void set_time(int);
  void tick(); 

private:

  int time_;

};

#endif
