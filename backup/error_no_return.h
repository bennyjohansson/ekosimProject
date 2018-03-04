#include <iostream>
#include <iomanip>
#include <exception>
#include <stdexcept>

using namespace std;

class no_return_error : public runtime_error {
 public:
  no_return_error(const string& what_arg = "")
    : runtime_error(what_arg) {}
};
