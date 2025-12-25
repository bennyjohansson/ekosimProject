#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <fstream>

#include "clock.h"

using namespace std;

Clock::Clock() : time_(0) //
{
}

int Clock::get_time() const
{
  return time_;
}

void Clock::set_time(int time)
{
  time_ = time;
}

void Clock::tick()
{
  time_++;
}