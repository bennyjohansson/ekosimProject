#ifndef COMPANY_H
#define COMPANY_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "consumer.h"
#include "consumer_list.h"
#include "market.h"
//#include "employee_list.h"
//#include "city.h"

using namespace std;

class Company {
 public:

  Company();
  Company(string name);
  Company(string, Market*);
 
  void info();
  void employee_info();  
  string get_name();
  
  double get_capital();
  double get_prod_const_skill();
  double get_prod_const_motivation();
  double get_wage_const();  
  double get_production();
  double get_production(Consumer *);
  double get_stock();
  double get_invest();

  void set_capital(double);
  void set_prod_const_skill(double);
  void set_prod_const_motivation(double);
  void set_wage_const(double);
  void set_stock(double);
  void set_invest(double);
  //void set_market(Market * market);

  void change_capital(double);
  void change_prod_const_skill(double);
  void change_prod_const_motivation(double);
  void change_wage_const(double);
  void change_stock(double);  
  void change_invest(double);

  void add_employee(Consumer * consumer);
  void remove_employee(Consumer *);
  void update_employees(double skill_limit, double motivation_limit);
  void print_employees();

  void sell_to_market();

  double contribution_adding(Consumer *);
  double contribution_removing(Consumer *);
  bool update_employees(Consumer *);
  void produce();
  void pay_employees(); 
  void invest();

 private:
  string name_;  
  double capital_;
  double stock_;   //temp solution. later objects of class p1 osv
  
  double invest_;
  
  Consumer_list * employees_;
  Market *market_;

  double prod_const_skill_;
  double prod_const_motivation_;
  double wage_const_;  
};

#endif
                                                                                                                                                                                                                                                                                                    company_list.h                                                                                      0000644 0001766 0000062 00000001714 10311504064 014167  0                                                                                                    ustar   benny                           staff                           0000000 0000000                                                                                                                                                                        #ifndef COMPANY_LIST_H
#define COMPANY_LIST_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "company.h"
#include "element_company.h"

using namespace std;

class Company_list {
 public:
  Company_list();
  Company_list(string name);
  Company_list(Company * company);
  
  void info();
  void employee_info(string);

  void add_company(Company * company);
  void add_employee(string name, Consumer * conumer);
  void print_list();
  void print_employees(string company);
  void sell_to_market();


  Company * get_company(string name); 
  Element_company * get_random_company();

  void update_company_employees();
  void produce();
  bool update_employees(Consumer *, string);
  bool update_employees(Consumer *);
  bool update_employees2(Consumer *);

  void pay_employees();
  void invest();

  double get_capital_sum();
  double get_item_sum();

 private:
  string name_;
  Element_company * list_;
  int size_;

};

#endif




                                                    consumer.h                                                                                          0000644 0001766 0000062 00000002722 10307577441 013337  0                                                                                                    ustar   benny                           staff                           0000000 0000000                                                                                                                                                                        #ifndef CONSUMER_H
#define CONSUMER_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "market.h"
//#include "company.h"
//#include "consumer_list.h"
//#include "city.h"

using namespace std;

class Consumer {
 public:
  Consumer();

  Consumer(double, double, double, double);
  Consumer(double, double, double, double, Market *);
  
  void info(); 
  void info_short();
  void info_head();
  
  double get_motivation();
  double get_skill();
  double get_capital();
  double get_spendwill();
  double get_income();
  double get_items();
  bool get_employment_status();

  void set_motivation(double);
  void set_skill(double);
  void set_capital(double);
  void set_spedwill(double);
  void set_income(double);  
  void set_employment_status(bool employed);
  void set_items(double);
//void set_city(City * city);

  void change_motivation(double);
  void change_skill(double);
  void change_capital(double);
  void change_spendwill(double);
  void change_income(double);
  void change_items(double);

  void update_values();

  void update_capital(); 
  void update_skill();
  void update_spendwill();
  void update_motivation();

  void buy();

 private:

  double motivation_;
  double skill_;
  double capital_;
  double spendwill_;
  double items_;

  Market * market_;  
  //Company * employer_;
  //Employee_list employee_info_;
  bool employed_;
  int weeks_employed_;
  int weeks_unemployed_;
  double income_;
  //City * city_;


};
#endif

                                              consumer_list.h                                                                                     0000644 0001766 0000062 00000002350 10212321742 014351  0                                                                                                    ustar   benny                           staff                           0000000 0000000                                                                                                                                                                        #ifndef CONSUMER_LIST_H
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
  
  void remove_consumer(Consumer *);
  void remove_by_skill(double skill_limit);
  void remove_by_motivation(double motivation_limit);

  Consumer * get_optimal_consumer(double mot_we, double skill_we);
  Consumer * get_usless_employee(double, double);
  Element_consumer * get_motivated_consumers();
  void update();  
  void pay_employees(double, double, double);
  void pay_employees(double);

  void consumers_buy();

 protected:

  string name_;
  Element_consumer * list_;
  int size_;
  
};
#endif

                                                                                                                                                                                                                                                                                        element.h                                                                                           0000644 0001766 0000062 00000000433 10177266010 013122  0                                                                                                    ustar   benny                           staff                           0000000 0000000                                                                                                                                                                        #ifndef ELEMENT_H
#define ELEMENT_H
#include <iostream>
#include <iomanip>
#include <string>
#include "consumer.h"

using namespace std;

class Element {
public:
	Element *next_;
	Consumer *cons_;

	Element(Element *n, Consumer *c) : next_(n), cons_(c) {}
};
#endif
                                                                                                                                                                                                                                     element_company.h                                                                                   0000644 0001766 0000062 00000000626 10204247213 014647  0                                                                                                    ustar   benny                           staff                           0000000 0000000                                                                                                                                                                        #ifndef ELEMENT_COMPANY_H
#define ELEMENT_COMPANY_H

#include <iostream>
#include <iomanip>
#include <string>

#include "consumer.h"
#include "company.h"

using namespace std;

class Element_company {
public:
	Element_company *next_;
	Company *company_;

	Element_company();
	Element_company(Element_company *n, Company *c);

	string get_name();
	Company * get_company();
};
#endif
                                                                                                          element_consumer.h                                                                                  0000644 0001766 0000062 00000001115 10205072315 015026  0                                                                                                    ustar   benny                           staff                           0000000 0000000                                                                                                                                                                        #ifndef ELEMENT_CONSUMER_H
#define ELEMENT_CONSUMER_H
#include <iostream>
#include <iomanip>
#include <string>

#include "consumer.h"
//#include "city.h"

using namespace std;

class Element_consumer {
public:
	Element_consumer *next_;
	Consumer * consumer_;

	Element_consumer();

	Element_consumer(Element_consumer *n, Consumer *c);

	Consumer * get_consumer();

	double get_motivation();
	double get_skill();
	double get_capital();
	double get_spendwill();
	double get_income();
	bool get_employment_status();
	void set_employment_status(bool);

};
#endif
                                                                                                                                                                                                                                                                                                                                                                                                                                                   employee_list.h                                                                                     0000644 0001766 0000062 00000000735 10204243175 014346  0                                                                                                    ustar   benny                           staff                           0000000 0000000                                                                                                                                                                        #ifndef EMPLOYEE_LIST_H
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
                                   error_no_return.h                                                                                   0000644 0001766 0000062 00000000363 10206534116 014715  0                                                                                                    ustar   benny                           staff                           0000000 0000000                                                                                                                                                                        #include <iostream>
#include <iomanip>
#include <exception>
#include <stdexcept>

using namespace std;

class no_return_error : public runtime_error {
 public:
  no_return_error(const string& what_arg = "")
    : runtime_error(what_arg) {}
};
                                                                                                                                                                                                                                                                             functions.h                                                                                         0000644 0001766 0000062 00000001011 10212337754 013476  0                                                                                                    ustar   benny                           staff                           0000000 0000000                                                                                                                                                                        #ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "consumer.h"
#include "market.h"

using namespace std;

void randomize(double&, double);
void normalize(double&);
double get_norm(double average, double deviation);
double get_price(double excess);
double get_price(double, double);
double get_prod(double, double, double, double, double);
double get_prod(Consumer *);
double change_motivation();



Consumer * random_consumer(Market *);

#endif
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       market.h                                                                                            0000644 0001766 0000062 00000001610 10310035625 012745  0                                                                                                    ustar   benny                           staff                           0000000 0000000                                                                                                                                                                        #ifndef MARKET_H
#define MARKET_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

//#include "consumer_list.h"
//#include "company_list.h"
//#include "consumer.h"

using namespace std;

class Market {
 public:

  Market();
  Market(string name);

  void info();
  double get_items();
  double get_marginal();
  double get_capital();
  long double get_price_in();
  long double get_price_out();
  
  void set_items(double);
  void set_marginal(double);
  void set_capital(double);
  void set_price_in(double);
  void set_price_out(double);


  bool change_items(double);
  void change_marginal(double);
  bool change_capital(double);
  void change_price_in(double);
  void change_price_out(double);

  void negotiate_price(double);

 private:

  string name_;
  double items_;
  double marginal_;
  double capital_;  
  double price_in_;
  double price_out_;

};
#endif






                                                                                                                        city.cc                                                                                             0000644 0001766 0000062 00000013724 10311505660 012603  0                                                                                                    ustar   benny                           staff                           0000000 0000000                                                                                                                                                                        #include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "consumer.h"
#include "functions.h"
#include "city.h"
#include "consumer_list.h"
#include "company.h"
#include "company_list.h"
#include "error_no_return.h"

using namespace std;

City::City() :
  name_("bennyland"),
  consumers_(new Consumer_list("CONSUMERS")),
  company_list_(new Company_list("COMPANIES")),
  labour_market_(new Consumer_list("LABOUR MARKET")),
  market_(new Market())
{}

City::City(string name) :
  name_(name),
  consumers_(new Consumer_list("CONSUMERS")),
  company_list_(new Company_list("COMPANIES")),
  labour_market_(new Consumer_list("LABOUR MARKET")),
  market_(new Market())
{}

void City::consumer_info() {
  consumers_-> info();
}

void City::labour_info() {
  labour_market_ -> info();
}

void City::employee_info() {
  employee_info("all");
}

void City::print_company_list(){

  company_list_ -> print_list();

}

void City::employee_info(string command) {
  company_list_ -> employee_info(command);
}

void City::follow_capital(Consumer * consumer) {
  cout << consumer -> get_capital() << " ";
}

void City::follow_capital() {
  follow_capital(get_random_consumer());
} 

Market * City::get_market() {
  return market_;
}

Consumer * City::get_random_consumer() {
  consumers_ -> get_random_consumer();
}

double City::get_capital_sum() {

  double csum = 0;

  csum = consumers_ -> get_capital_sum() + company_list_ -> get_capital_sum() + market_ -> get_capital();

  return csum;
}

void City::update_market() {
  double marginal_ = market_ -> get_marginal();;
  int consumers_nr = consumers_ -> get_size();
  double capital_sum = consumers_ -> get_capital_sum();
  double spendwill_sum = consumers_ -> get_spendwill_sum();
  double average_spendwill = spendwill_sum/consumers_nr;
  double items = market_ -> get_items();

  //  cout << "I city update market    items = " << items << endl;
  double price_out = average_spendwill*capital_sum/items;
  market_ -> set_price_out(price_out);
  double price_in = price_out/(1 + marginal_);
  market_ -> set_price_in(price_in);
  //cout << "I city update market" << endl << "P in " << price_in << "  P out " << price_out << endl;
} 

void City::negotiate_market_price() {

  double   marginal_ = market_ -> get_marginal();
  int consumers_nr = consumers_ -> get_size();
  double capital_sum = consumers_ -> get_capital_sum();
  //  cout << "I city negotiate!" << capital_sum << endl;
  double spendwill_sum = consumers_ -> get_spendwill_sum();
  double average_spendwill = spendwill_sum/consumers_nr;
  double items = market_ -> get_items() + company_list_ -> get_item_sum();

  double price_out = average_spendwill*capital_sum/items;
  market_ -> set_price_out(price_out);
  double price_in = price_out/(1 + marginal_);
  market_ -> set_price_in(price_in);

}

void City::market_info() {
  market_ -> info();
}

void City::sell_to_market() {
  company_list_ -> sell_to_market();
}

void City::set_consumers(Consumer_list * consumer_list) {
  consumers_ = consumer_list;
}
void City::set_companies(Company_list * company_list) {
  company_list_ = company_list;
}

void City::set_labour_market(Consumer_list * labour_market) {
  labour_market_ = labour_market;
}

void City::add_consumer(double motivation, double skill,
			double capital, double spendwill) {
  Consumer * consumer = new Consumer(motivation, skill, 
				     capital, spendwill);
  consumers_ -> add_first(consumer);
}

void City::add_consumer(Consumer * consumer) {
  consumers_ -> add_first(consumer);
}
 
void City::add_company(string name) {
  Company * company = new Company(name, market_);
  company_list_ -> add_company(company);
}

void City::info() {
  cout << endl 
       << "----------------------------------------" << endl
       << "THE CITY" << endl
       << "----------------------------------------" << endl
       << "Name: " << name_ << endl
       << "Population: " << consumers_ -> get_size() << endl << endl
       << "COMPANIES " << endl;
  company_list_ -> print_list();
  cout << endl;
}

void City::print_consumer_list() {
  consumers_ -> print_list();

}

void City::print_employees(string company) {
  company_list_ -> print_employees(company);
}

void City::print_labour_market() {
  labour_market_ -> print_list();
}

void City::update_consumer_list() {
  consumers_ -> update();
}

Company * City::get_company(string name) {
  return company_list_ -> get_company(name);
}

Element_consumer * City::get_motivated_consumers() {
  return consumers_ -> get_motivated_consumers();
}

void City::add_motivated_consumers(Element_consumer * workers) {
  labour_market_ -> add_group_last(workers);
}

void City::add_employee(string name, Consumer * consumer) {
  company_list_ -> add_employee(name, consumer);
  labour_market_ -> remove_consumer(consumer);
}

void City::remove_consumer_from_labour_market(Consumer * consumer) {
  labour_market_ -> remove_consumer(consumer);
}

void City::update_company_employees() {
  company_list_ -> update_company_employees();
}

void City::update_employees(string name) {
  //FLYTTA WHILESATSEN TILL COMPANYLIST SA SAR DE TURAS OM   
  //NU BLIR DET JU FEL ME OPTIMAL OCH SA, MEN DET ORDNAR VI SENARE
  double skill =  get_company(name) -> get_prod_const_skill(); 
   double mot = get_company(name) -> get_prod_const_motivation();
   Consumer * opt; //get_optimal_consumer(mot, skill);
   //cout << "icity" << endl;
   while(company_list_ -> update_employees2(opt = get_optimal_consumer(mot, skill))){}

   //while(company_list_ -> update_employees(opt = get_optimal_consumer(mot, skill), name)) {}
}

void City::produce() {
   company_list_ -> produce();
}

void City::pay_company_employees() {
  company_list_ -> pay_employees();
}


Consumer * City::get_optimal_consumer(double mot_we, double skill_we) {
  try {
    return (labour_market_ -> get_optimal_consumer(mot_we, skill_we));
  }
  catch(no_return_error) {
    cout << "ingen_consumer" << endl;
  }
}


void City::consumers_buy() {
  consumers_ -> consumers_buy();
}


void City::invest() {
  company_list_ -> invest();
}



















                                            company.cc                                                                                          0000644 0001766 0000062 00000021122 10311504533 013266  0                                                                                                    ustar   benny                           staff                           0000000 0000000                                                                                                                                                                        #include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "consumer.h"
#include "company.h"
#include "functions.h"

using namespace std;

Company::Company() :
  name_(""),
  capital_(0),
  stock_(0),
  invest_(0.6),
  prod_const_skill_(60),
  prod_const_motivation_(40),
  wage_const_(0.75),
  market_(0),
  employees_(new Consumer_list("Employees")){}

Company::Company(string name, Market * market) :
  name_(name),
  capital_(10000),
  stock_(0),
  invest_(0.6),
  prod_const_skill_(60),
  prod_const_motivation_(40),
  wage_const_(0.5),
  market_(market),
  employees_(new Consumer_list("Employees"))
{}


void Company::info() {
 cout << "Name: " << name_ << endl 
      << "Capital: " <<  capital_ << endl
      << "Stock: " << stock_ << endl 
      << "Employees: " << employees_ -> get_size() << endl << endl;
}

void Company::employee_info() {
  cout << name_ << endl << "---------------------" << endl;
  employees_ -> info();
}

string Company::get_name() {
  return name_;
}

double Company::get_capital() {
  return capital_;
}

double Company::get_prod_const_skill() {
	return prod_const_skill_;
}

double Company::get_prod_const_motivation() {
	return prod_const_motivation_;
}

double Company::get_wage_const() {
	return wage_const_;
}

double Company::get_production() {
  
  double skill_sum = employees_ -> get_skill_sum(); 
  double sk = prod_const_skill_;
  double mot_sum =employees_ -> get_motivation_sum();
  //  cout << "I comp get prod, mot sum: " << mot_sum << endl; 
  double mot = prod_const_motivation_;
  double employees = employees_ -> get_size();
  double prod =  get_prod(skill_sum, sk, mot_sum, mot, employees);
  return prod;
}

double Company::get_production(Consumer * consumer) {

  //double prod = consumer -> get_skill() * prod_const_skill_ +
  //  consumer -> get_motivation() * prod_const_motivation_;
  double skill = consumer -> get_skill();
  double mot = consumer -> get_motivation();
  double prod = get_prod(skill, skill, mot, mot, 1);

  return prod;
} 

double Company::get_stock() {
   return stock_;
}

double Company::get_invest() {
  return invest_;
}

void Company::set_capital(double capital) {
  capital_ = capital;
}

void Company::set_prod_const_skill(double skill) {
      	prod_const_skill_ = skill;
}

void Company::set_prod_const_motivation(double mot) {
	prod_const_motivation_ = mot;
}

void Company::set_wage_const(double wc) {
	wage_const_ = wc;
}

void Company::set_stock(double stock) {
   stock_ = stock;
}

void Company::set_invest(double invest) {
  invest_ = invest;
}

void Company::change_capital(double ch) {
  //  if (capital_ + ch > 0) {
    capital_ += ch;
  // }
    //else {
    //cout << "Fel i company ch cap" << endl;
    // }
}

void Company::change_prod_const_skill(double ch) {
	prod_const_skill_ += prod_const_skill_;
}

void Company::change_prod_const_motivation(double ch) {
	prod_const_motivation_ += ch;
}

void Company::change_wage_const(double wcc) {
	wage_const_ += wcc;
}

void Company::change_stock(double ch) {
   stock_ += ch;
}

void Company::change_invest(double ch) {
  invest_ += ch;
}

void Company::add_employee(Consumer * consumer) {
  consumer -> set_employment_status(true);
  employees_-> add_first(consumer);
}

void Company::print_employees() {
  employees_ -> print_list();
}

void Company::produce() {  
  stock_ += get_production();
  //  pay_employees();
  //cout << "prod: " << get_production() << "stock: " << stock_ << endl;

}

void Company::pay_employees() {
  double production = get_production();
  double size = employees_ -> get_size();
  double price = market_ -> get_price_in();
  double sum_bef = employees_ -> get_capital_sum();
 
  double wage_tot = production * price * wage_const_ ;
  double wage = wage_tot/size;
  double wage_tot2 = wage_tot;
 
  employees_ -> pay_employees(wage);
  double sum_after = employees_ -> get_capital_sum();
  wage_tot = sum_after - sum_bef;
  capital_ -= wage_tot;
  
  //  cout << "Name: " << name_ << endl << "I company pay empl" << endl;
  //cout << "Reduced com cap: " << wage_tot2 << endl
  //       << "Wages paid: " << sum_after - sum_bef << endl << endl;
}

//Checks how the expected income changes by adding consumer 
double Company::contribution_adding(Consumer * consumer) {
  double skill = consumer -> get_skill();
  double mot = consumer -> get_motivation();
  double skill_sum = employees_ -> get_skill_sum();
  double mot_sum = employees_ -> get_motivation_sum();
  int employees = employees_ -> get_size();
  double sk_c = prod_const_skill_;
  double mot_c = prod_const_motivation_;

  double prod_before = get_production();
  double prod_after = get_prod(skill_sum+skill, sk_c, mot_sum+mot, mot_c, employees +1);
  double price = market_ -> get_price_in();

  double size = employees_ -> get_size() + 1;//I need to add the "1" here to get it right???
  double wage = prod_after * price * wage_const_ / size;
  
  //  double prod_increase = get_production(consumer);
  //double wage_tmp = prod_increase * wage_const_;

  double contribution = 0;

  contribution = (prod_after - prod_before)*price - wage;
  return contribution;
}

double Company::contribution_removing(Consumer * consumer) {
  double skill = consumer -> get_skill();
  double mot = consumer -> get_motivation();
  double skill_sum = employees_ -> get_skill_sum();
  double mot_sum = employees_ -> get_motivation_sum();
  int employees = employees_ -> get_size();
  double sk_c = prod_const_skill_;
  double mot_c = prod_const_motivation_;

  double prod_before = get_production();
  double prod_after = get_prod(skill_sum - skill, sk_c, mot_sum - mot, 
				     mot_c, employees); 
  double price = market_ -> get_price_in();
  //double wage = wage_const_ * get_production(consumer)*price;
  
  double size = employees_ -> get_size();
  double wage = prod_before * price * wage_const_ / size;


  double contribution = 0;
  contribution = (prod_after - prod_before)*price + wage;
  //  cout << "cont rem i company, cont = " << contribution << endl;
  return contribution;
} 

bool Company::update_employees(Consumer * opt) {
  if(employees_ -> get_size() != 0) {
    Consumer * bad_empl = employees_ -> get_usless_employee(prod_const_skill_, 
							    prod_const_motivation_);
    double add =    contribution_adding(opt);
    double rem =    contribution_removing(bad_empl);
    //    cout << "Adding opt: " << add << endl << "Rem usl: " << rem << endl;
  while(contribution_removing(bad_empl) > 0) {
    //      cout << employees_ -> get_size() << endl;
      remove_employee(bad_empl);
      //cout << employees_ -> get_size() << endl;
      
      bad_empl = employees_ -> get_usless_employee(prod_const_skill_,
						   prod_const_motivation_); 
      //bad_empl -> info();
    }
    //        cout << "hej i company upd emp" << endl;
    
    if(contribution_adding(opt) > 500) { //100 annars hanger det sig
      // cout << "kuk i com upd emp" << endl;
      add_employee(opt);
      return true;
    }
    else if(get_production(opt) > get_production(bad_empl) && contribution_adding(opt) > 500) {
      remove_employee(bad_empl);
      add_employee(opt);
      return false;
     }
    return false;
  }
  else {
    add_employee(opt);
    return true;  //SKa de va har
  }
}

void Company::update_employees(double skill_limit, 
			  double motivation_limit) {
  employees_ -> remove_by_motivation(motivation_limit);
  employees_ -> remove_by_skill(skill_limit);
}

void Company::remove_employee(Consumer * consumer) {
  consumer -> set_employment_status(false);
  consumer -> set_income(0);
  employees_ -> remove_consumer(consumer);
}  


void Company::sell_to_market() {
  double price = market_ -> get_price_in();
  //cout << "s " << stock_ << " p " << price << endl;
  //market_ -> change_items(stock_);
  //change_capital(price*stock_);
  //  cout << "stock: " << stock_ << endl <<"i sell to market company Price: " << price << endl;
  //  if (market_ -> change_capital(-price*stock_)) {
  
    change_capital(price*stock_);
    market_ -> change_capital(-price*stock_);

    market_ -> change_items(stock_);
    change_stock(-stock_);
    //  }
    //else {
    //cout << "Kuk i company sell" << endl;
    //}
}

void Company::invest() {
  double investment = 0;
  double limit = 500000;
  if(capital_ > 0 && investment < limit) {
    investment = invest_ * capital_;
    //    capital_ -= investment;
    //Borde kunna investera bade i storlek, dvs rate, och effektivitet, dvs 
    //prod const skill och motivation. Gor ett enkelt forsok, men borde eg
    //kolla pa reapektive derivator
  }
  else if(investment > limit) {
    //investment = limit;
  }
  
  //  prod_const_motivation_ *= 1 + 0.5*investment/limit;
  //prod_const_skill_ *= 1 + 0.5*investment/limit;
    
}



















                                                                                                                                                                                                                                                                                                                                                                                                                                              company_list.cc                                                                                     0000644 0001766 0000062 00000012264 10311504133 014324  0                                                                                                    ustar   benny                           staff                           0000000 0000000                                                                                                                                                                        #include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <exception>
#include <stdexcept>

#include "consumer.h"
#include "functions.h"
#include "company_list.h"
#include "element_company.h"
#include "error_no_return.h"

using namespace std;

Company_list::Company_list() :
  list_(0),
  size_(0),
  name_("")
{}

Company_list::Company_list(string name) :
  list_(0),
  size_(0), 
  name_(name)
{}

void Company_list::info() {
  cout << endl << "COMPANIES" << endl << "----------------------------------------------------------" << endl; 
  cout << "Number of companies: " << size_ << endl << endl;
}

void Company_list::add_company(Company * company) {
  Element_company * p;
  size_++;
  
  //if(list_) {
    //for(p = list_; p -> next_; p = p -> next_) {}
    //p -> next_ = new Element_company(0, company);
    //}
  //else {
    list_ = new Element_company(list_, company);
    //}
}

void Company_list::print_list() {
  
  info();
  if(list_) {
    for (Element_company *p = list_; p; p = p -> next_) {
      p->company_->info();
    }
  }
  
  cout << endl; 
}

void Company_list::print_employees(string company) {
  get_company(company) -> print_employees();
}

Element_company * Company_list::get_random_company() {
  //print_list();
  int nr = (rand()%(size_ + 1));//SKA NOG VA +1
  //  cout << "I element company ransdom" << nr << endl;
  Element_company * p = list_;
  for(int i = 0; i < nr; i++) {
    //    cout << i << " ";
    p = p -> next_;
  }
  return p;
}


Company * Company_list::get_company(string name) {
  Element_company * p;
  
  if(list_) {
    for(p = list_; p; p = p -> next_) {
      if (p ->get_name() == name) {
	return p -> get_company() ;
      }
    }
    throw no_return_error("Cant find the company");
  }
  else {
    throw no_return_error("no list"); 
  } 
}

double Company_list::get_capital_sum() {
  Element_company * p;
  double sum = 0;

  for (p = list_; p; p = p -> next_) {
    sum += p -> get_company() -> get_capital();
  }
  return sum;
}

double Company_list::get_item_sum() {
  Element_company * p;
  double sum = 0;

  for (p = list_; p; p = p -> next_) {
    sum += p -> get_company() -> get_stock();
  }
  return sum;
}


void Company_list::add_employee(string name, Consumer * consumer) {  
  get_company(name) -> add_employee(consumer);
}

void Company_list::update_company_employees() {
  double motivation_limit =  0.3;
  double skill_limit = 0.5;

  Element_company * p;
  
  for(p = list_; p -> next_; p = p -> next_) {
    //cout << "1" << endl;
    (p -> get_company()) -> update_employees(skill_limit, 
					     motivation_limit);
  }
}

void Company_list::employee_info(string command) {
  Element_company * q;
  
  if(command == "all" || command == "") {
    for(q = list_; q; q = q -> next_) {
      q -> get_company() -> employee_info();
    }
  }
  else {
    try {
      get_company(command) -> employee_info();
    } 
    catch(no_return_error) {
      cout << "Company not found" << endl;
    }
    //    catch(exception& e) {
    //  cout << typeid(e) .name() << ": " << e.what() << endl;
    //}
  }
}

void Company_list::produce() {
  
  Element_company * p;
  
  for(p = list_; p; p = p -> next_) {
    (p -> get_company()) -> produce();
  }
}

void Company_list::pay_employees() {

  Element_company * p;

  for(p = list_; p; p = p -> next_) {
    (p -> get_company()) -> pay_employees();
  }
}


void Company_list::sell_to_market() {
  
  Element_company * p;
  
  for(p = list_; p; p = p -> next_) {
    (p -> get_company()) -> sell_to_market();
      }
}

//Borde kunna gora nat smartare, dar man anropar listan med
//en funktion och att den gor pa hela listan...
//Nu blev det har daligt. company maste kanna till arb markn
//annars blir det ett javla massa skickande. Det har maste andras.

bool Company_list::update_employees(Consumer * opt, string name) {
  if(name == "all") {
    return update_employees(opt);
  }
  else { 
    return get_company(name) -> update_employees(opt);
  }
}

bool Company_list::update_employees(Consumer * opt) {
  Element_company * p;
  
  for(p = list_; p; p = p -> next_) {
    cout << "vi loopar i com list upd emp" << endl;
    return p -> get_company() -> update_employees(opt);
  }
}


bool Company_list::update_employees2(Consumer * opt) {
  Element_company * p = get_random_company();
  Element_company * r = p;
  Element_company * q;
  bool after = 0;
  bool before = 0;
  //Checks the random company and the ones after in the list
  for(p; p; p = p -> next_) {
    after = p -> get_company() -> update_employees(opt);
    //    cout << "First" << endl << p -> get_company() -> get_name() << endl;
    //If employed, return true and get a new opt consumer
    if(after) {
      return after;
    }
  }
  //Checks the list from the start and till the random
  for(q = list_; q != r; q = q -> next_) {
    bool before = q -> get_company() -> update_employees(opt);
    //cout << "Second" << endl << q -> get_company() -> get_name() << endl;
    //If employed, return true and get a new opt consumer
    if(before) {
      return before;
    }
  }
  //No one wants to hire opt, done. 
  return false;
}


void Company_list::invest() {
  Element_company * p;
  
  for(p = list_; p; p = p -> next_) {
    p -> get_company() -> invest();
  }
}









                                                                                                                                                                                                                                                                                                                                            consumer.cc                                                                                         0000644 0001766 0000062 00000012355 10307614050 013464  0                                                                                                    ustar   benny                           staff                           0000000 0000000                                                                                                                                                                        #include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "functions.h"
#include "city.h"
#include "consumer.h"

using namespace std;

Consumer::Consumer() : 
  motivation_(0),
  skill_(0),
  capital_(0),
  spendwill_(0),
  employed_(false)
  //city_(0)
{}

Consumer::Consumer(double mot, double sk, double cap, double spe) :
  motivation_(mot),
  skill_(sk),
  spendwill_(spe),
  employed_(false),
  capital_(0),
  income_(0),
  items_(0)
{}

Consumer::Consumer(double mot, double sk, double cap, double spe, Market * m) :
  motivation_(mot),
  skill_(sk),
  capital_(cap),
  spendwill_(spe),
  employed_(false),
  market_(m),
  income_(0),
  items_(0) 
  //city_(0)
{}


void Consumer::info() {
  cout << "Motivation: " << get_motivation() << endl 
       << "Skill: " <<  get_skill() << endl
       << "Capital: " << get_capital() << endl
       << "Spendwill: " << get_spendwill() << endl
       << "Employed: ";
  if (employed_) {
    cout << "yes" << endl;
  }
  else {
    cout << "no" << endl;
  }
}

void Consumer::info_head() {
  int space = 9;
  cout << setw(space) << "Mot" 
       << setw(space) << "Skill" 
       << setw(space) << "Spendw" 
       << setw(space) << "Cap"
       << setw(space + 3) << "Items"
       << setw(space) << "Wage"
       << setw(space) << "Employed" << endl;
}

void Consumer::info_short() {
  int space = 9;
  string employed = "";
  
  if(get_employment_status()) {
    employed = "yes";
  }
  else {
    employed = "no";
  }
  
  
  cout << setiosflags(ios::fixed) << setprecision(2)  
       << setw(space) << get_motivation() 
       << setw(space) << get_skill()
       << setw(space) << get_spendwill()
       << setw(space) << get_capital()
       << setw(space + 2) << get_items()
       << setw(space) << get_income()
       << setw(space-2) << " " << employed << endl;
}

double Consumer::get_motivation(){
  return motivation_;
}

double Consumer::get_skill(){
  return skill_;
}
double Consumer::get_capital(){
  return capital_;
}
double Consumer::get_spendwill(){
  return spendwill_;
}

double Consumer::get_income() {
  return income_;
}

bool Consumer::get_employment_status() {
  return employed_;
}

double Consumer::get_items() {
  return items_;
}

void Consumer::set_motivation(double mot){
  motivation_ = mot;
}
void Consumer::set_skill(double skil){
  skill_ = skil;
}
void Consumer::set_capital(double cap){
  capital_ = cap;
}
void Consumer::set_spedwill(double spendw){
  spendwill_ = spendw;
}

void Consumer::set_income(double income) {
  income_ = income;
}
void Consumer::set_employment_status(bool employed) {
  employed_ = employed;
}

void Consumer::set_items(double items) {
  items_ = items;
}

//void Consumer::set_city(City * city) {
//  city_ = city;
//}

void Consumer::change_motivation(double mot){
  motivation_ += mot;
}
void Consumer::change_skill(double skil){
  skill_ += skil;
}

void Consumer::change_capital(double cap){
  //  if (capital_ >= -cap || cap > 0) {
    capital_ += cap;
    // }
    //else {
    //cout << "Fel i consumer ch_cap" << endl;
    // }
}

void Consumer::change_spendwill(double spendw){
  spendwill_ += spendw;
}

void Consumer::change_income(double income_ch) {
  income_ += income_ch;
}

void Consumer::change_items(double ch) {
  items_ += ch;
}



// Here we must think. Should the change-functions be
// member-functions of Consumer or not? Benefit is that no 
// arguments have to be sent. Think this is the best solution.
//and the functions are very related to the consumer class

void Consumer::update_values() {
  update_capital(); 
  update_skill();
  update_spendwill();
  update_motivation();
}

void Consumer::update_capital() {
  //capital += income_;
}

void Consumer::update_skill() {
  int skill_change;
  double EMP_CONST = 0.0001;

  bool emp = get_employment_status();
  if(emp) {
    skill_ *= (1 + EMP_CONST);
  }
  else {
    skill_ *= (1 - EMP_CONST);
  }

  randomize(skill_, 0.1);
  normalize(skill_);
}

void Consumer::update_spendwill() {
  randomize(spendwill_, 0.1);
  normalize(spendwill_);
}

void Consumer::update_motivation() {
  const double MOTIVATION_CAP_CONST = 0.001;
  const double EMP_CONST = 0.01;
  bool emp = get_employment_status();
  motivation_ = motivation_*(1+MOTIVATION_CAP_CONST*1/(1 + capital_));
  if(emp) {
    motivation_ *= (1-EMP_CONST);
  }
  else {
    motivation_ *= (1+EMP_CONST);
  }

  randomize(motivation_, 0.1);
  normalize(motivation_);

}


void Consumer::buy() {
  const double FEL_STALLE = 0.2;
  double amount = capital_ * spendwill_; //+ (capital_ - income_)*FEL_STALLE;
  //  cout << amount << endl;
  double price = market_ -> get_price_out();
  double quantity = amount/price;
  //if(amount > capital_) {
  //  amount = capital_;
  // }
  quantity = amount/price;
  //if (!(market_ -> change_items(-quantity))) {
  //  quantity = market_ -> get_items();
  //  amount = quantity * price;
  // }
  items_ += quantity;
  // cout << "I consumer buy" << endl << "Amount: " << amount << endl << "Quant: " << quantity << endl;
  market_ -> change_capital(amount);
  //  cout << "i cons buy, amount = " << amount << endl;  
  change_capital(-amount);
  market_ -> change_items(-quantity);
}


//  Company * employer_;
// Employee_list employee_info_;
// int weeks_employed_;
// int weeks_unemployed_;
// double income_;
// City * city_;






                                                                                                                                                                                                                                                                                   consumer_list.cc                                                                                    0000644 0001766 0000062 00000021577 10307574207 014536  0                                                                                                    ustar   benny                           staff                           0000000 0000000                                                                                                                                                                        #include <iostream>
#include <iomanip>
#include <string>

#include "element_consumer.h"
#include "consumer_list.h"
#include "consumer.h"
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
  } 
  //  cout << "I cons list get capital, sa manga: " << n << endl;
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
  return sum;
} 


double Consumer_list::get_motivation_sum() {

  Element_consumer * p;
  double sum = 0;
  //int n = 0;
  if(list_) {
    for(p = list_; p -> next_; p = p -> next_) {
      sum += p -> get_skill();
      //n++;
    }
  }
  //cout << "i cons list get mot, n= " << n << endl;
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
  if(list_) {
    list_ = new Element_consumer(list_, cons);
  }
  else {
    list_ = new Element_consumer(0, cons);
  }
  size_++;
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

void Consumer_list::update() {
  
  Element_consumer *p;
  for(p = list_; p; p = p->next_) {
    p->consumer_->update_values();
  }
}



Element_consumer * Consumer_list::get_motivated_consumers() {
  
  Element_consumer *p;
  Element_consumer *lista = 0;
  for(p = list_; p; p = p -> next_) {
    if((p -> get_motivation() > 0.4) &&
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
void Consumer_list::remove_consumer(Consumer * consumer) {
  Element_consumer * p = list_;
  consumer -> set_employment_status(false);
  if(list_ && list_ -> get_consumer() == consumer) {//kollar sa inte tom och om det ar forsta
    if(p -> next_) {//om det finns en till sa skippar vi bara den forsta
      //      cout << "hej i  con list rem consumer " << endl;
      list_ = p -> next_;
      size_--;
    }
    else { //annars blir listan tom
      // cout << "hej i  con list rem consumer 2" << endl;
      list_ = 0;
      size_ = 0;
    }
  }
  else if(list_) {//om den inte ar tom, och det inte ar forsta
    for(p; p -> next_; p = p -> next_) {
      if((p -> next_) -> get_consumer() == consumer 
	 && (p -> next_) -> next_) { //nu ar det den vi pekar pa och inte den sista?
	//	cout << "hej i  con list rem consumer 3" << endl;
	size_--;
	p -> next_ = (p -> next_) -> next_;
      } 
      else if((p -> next_) -> get_consumer() == consumer) { //nu ar det den sistaoch den vi pekar pa
	p -> next_ = 0;
	size_--;
	break;
	//	cout << "hej i con list rem consumer" << endl;
      }
    }
    //cout << "tar vi oss ut ur rem cons i con list2" << endl;
  }
  else {
    cout << "The bitch is not employed here, error in remove_consumer in consumer_list" << endl;
  }
}

/* Should only be used from a company, make private and friend
 */

void Consumer_list::remove_by_skill(double skill_limit) {
  Element_consumer *p = list_;

  //Check he first consumers
  while(list_ -> get_skill() < skill_limit) {
    p -> set_employment_status(false);
    list_ = p -> next_;
    p = list_;
    size_--;
  } 
  
  //And the rest of them
  for(p; p -> next_; p = p -> next_)  {
    if((p -> next_) -> get_skill() < skill_limit) {
	(p -> next_ ) -> set_employment_status(false);
	size_--;
	if((p -> next_) -> next_) {
		p -> next_ = ((p -> next_) -> next_);
	}
	else {
		p -> next_ = 0;
 	}
    }
  }
}


void Consumer_list::remove_by_motivation(double motivation_limit) {
  Element_consumer *p = list_;

  //Check the first consuer
  if(p -> get_motivation() < motivation_limit) {
    p -> get_consumer() -> set_employment_status(false); 
    list_ = p -> next_;
    size_--;
    p = list_;
  }
  //And the rest of them

  for(p = list_; p -> next_; p = p -> next_) {
    if((p -> next_) -> get_motivation() < motivation_limit) {
	(p -> next_) -> set_employment_status(false);
	size_--;
	if((p -> next_) -> next_) {
		p -> next_ = ((p -> next_) -> next_);
        }
	else {
		p -> next_ = 0;
	     }
        }  
    } 
}

Consumer * Consumer_list::get_optimal_consumer(double skill_we, 
					       double mot_we) { 
  Element_consumer *p;
  Element_consumer * best = new Element_consumer(0, new Consumer(0,0,0,0));
  if(!list_) {
    throw no_return_error("no optimal consumer");
  }
  for(p = list_; p; p = p -> next_) {
    Consumer * consumer = p -> get_consumer();
    Consumer * besta = best ->  get_consumer();
    if((get_prod(consumer) > get_prod(besta)) 
       && !(p -> get_employment_status()))
      {
	best = p;
      }
  }
  return best -> get_consumer();
}

Consumer * Consumer_list::get_usless_employee(double skill, double mot){

  Element_consumer * p;
  Element_consumer * worst = new Element_consumer(0, 
						new Consumer(1,1,1,1));

  for(p = list_; p; p = p -> next_) {
	if(( 
	    (p -> get_motivation() * mot + p -> get_skill()* skill)
		<
	    (worst -> get_motivation()*mot + worst ->get_skill()*skill)
	   )) {
     		worst =  p;
         }
  }
  return worst -> get_consumer();
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

void Consumer_list::consumers_buy() {

  Element_consumer * p;

  for(p = list_; p; p = p -> next_){
    (p -> get_consumer()) -> buy();
  }
}












                                                                                                                                 element_company.cc                                                                                  0000644 0001766 0000062 00000000704 10204247373 015011  0                                                                                                    ustar   benny                           staff                           0000000 0000000                                                                                                                                                                        #include <iostream>
#include <iomanip>
#include <string>

#include "consumer.h"
#include "company.h"
#include "element_company.h"

using namespace std;

Element_company::Element_company() :
  next_(0),
  company_(0)
{}

Element_company::Element_company(Element_company *n, Company *c) :
  next_(n), company_(c)
{}

string Element_company::get_name() {
  return company_ -> get_name();
}

Company* Element_company::get_company() {
  return company_;
}

                                                            element_consumer.cc                                                                                 0000644 0001766 0000062 00000002033 10307530116 015165  0                                                                                                    ustar   benny                           staff                           0000000 0000000                                                                                                                                                                        #include <iostream>
#include <iomanip>
#include <string>

#include "consumer.h"
#include "company.h"
#include "element_consumer.h"
//#include "city.h"

using namespace std;

Element_consumer::Element_consumer() :
  next_(0),
  consumer_(0)
{}

Element_consumer::Element_consumer(Element_consumer *n, Consumer *c) :
  next_(n), consumer_(c)
{}

Consumer * Element_consumer::get_consumer() {
  return consumer_;
}

double  Element_consumer::get_motivation() {
  return consumer_ -> get_motivation();
}

double  Element_consumer::get_skill() {
  return  consumer_ -> get_skill();
}

double  Element_consumer::get_capital() {
  return consumer_ -> get_capital();
}

double  Element_consumer::get_spendwill() {
  return consumer_ -> get_spendwill();
}

double  Element_consumer::get_income() {
  return consumer_ -> get_income();
}

bool Element_consumer::get_employment_status() {
  return consumer_ -> get_employment_status();
}
void Element_consumer::set_employment_status(bool employed) {
	consumer_ -> set_employment_status(employed);
}














                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     employee_list.cc                                                                                    0000644 0001766 0000062 00000001035 10204243757 014504  0                                                                                                    ustar   benny                           staff                           0000000 0000000                                                                                                                                                                        #include <iostream>
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



                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   functions.cc                                                                                        0000644 0001766 0000062 00000003720 10310057203 013630  0                                                                                                    ustar   benny                           staff                           0000000 0000000                                                                                                                                                                        #include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "functions.h"
#include "consumer.h"
#include "market.h"

using namespace std;

void randomize(double &average, double deviation) {
  
  //int randvalue;
  int randsign;
  double randv;

  double limit = deviation*average;
  randv = ((rand()%10))*limit/10;
  
  randsign = (rand()%3);
  if(randsign == 1) {
    //cout << " hej i functions.cc randomize1" << endl;
    randv = -randv;
  }
  else {
    //    cout << "hej i functions.cc randomize1" << endl;
  }  
  average += randv;
  if(randsign == 3)
    cout << "vafan i functions.cc randomize" << endl;
  //return randvalue;
}

void normalize(double & value) {
  if(value < 0) {
    value = 0;
  }
  if(value > 1) {
    value = 1;
  }
}

double get_norm(double average, double deviation) {
  double randvalue = 0.2;
  //return gaussian(average, deviation);
}

double get_prod(double sk_sum, double sk, double mot_sum, 
		      double mot, double employees) {
  double capacity = 200;
  double rate = 0.05;
  double prod = capacity*(sk_sum*sk + mot_sum*mot)*atan(rate*employees);
  //cout << prod << endl;
  return prod;
}

double get_prod(Consumer * consumer) {
  double skill = consumer -> get_skill();
  double mot = consumer -> get_motivation(); 
  return get_prod(skill, skill, mot, mot, 1);
}

double get_price(double excess) {

double P_MAX = 100;
double P_SENS = -0.002;
double price = 0;
price = P_MAX*exp(P_SENS*excess);
//cout << price << endl;

return price;
}

double get_price(double excess, double sum_spend) {
  
  double price;
  if(excess != 0) {
    return price = sum_spend/excess;
  }
  else {
    return INT_MAX;
  }
}

Consumer * random_consumer(Market * market) {

  double mot = 0.5;
  double sk = 0.5;
  double cap = 400; 
  double spe = 0.65;
  randomize(mot, 1);
  randomize(sk, 1);
  randomize(cap, 1);
  randomize(spe, 1);

  
  return new Consumer(mot,sk,cap,spe, market);
}







                                                main.cc                                                                                             0000644 0001766 0000062 00000007307 10311505610 012552  0                                                                                                    ustar   benny                           staff                           0000000 0000000                                                                                                                                                                        #include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>

#include "consumer.h"
#include "consumer_list.h"
#include "city.h"
#include "company.h"
#include "company_list.h"
#include "element.h"
#include "functions.h"

using namespace std;

int main() {

  //Creates "Bennyland" and creates the consumer_list, 
  //the labour_market and the Company_list. Maybe these should

  //be created (the two last) in the constructor and be hidden,
  //but then there must be functions returning those and every-
  //body must know about thr city...
  
  //starting a clock for randomizin later
  srand(static_cast<unsigned>(time(0)));
  
  string b1 = "bempa AB";  
  string b2 = "bempa co";
  string b3 = "benny inc.";
  string b4 = "benjo pld";
  string b5 = "benny enterprises";
  string b6 = "johansson och johansson";

City bennyland("Bennyland");

 //Creates ten consumers
  for(int i = 0; i < 2000; i++) {    
    Consumer * benny = random_consumer(bennyland.get_market());
    bennyland.add_consumer(benny);    
  }
  
  //Creates two companies
  bennyland.add_company(b1);
  bennyland.add_company(b2);  
  bennyland.add_company(b3);
  bennyland.add_company(b4);
  bennyland.add_company(b5);
  bennyland.add_company(b6);

  //  bennyland.print_company_list();

  bennyland.get_company(b1) -> set_prod_const_skill(50);
  bennyland.get_company(b1) -> set_prod_const_motivation(50);
  bennyland.get_company(b2) -> set_prod_const_skill(60);
  bennyland.get_company(b2) -> set_prod_const_motivation(40);
  bennyland.get_company(b3) -> set_prod_const_skill(40);
  bennyland.get_company(b3) -> set_prod_const_motivation(60);
  bennyland.get_company(b4) -> set_prod_const_skill(50);
  bennyland.get_company(b4) -> set_prod_const_motivation(70);
  bennyland.get_company(b5) -> set_prod_const_skill(30);
  bennyland.get_company(b5) -> set_prod_const_motivation(80);
  bennyland.get_company(b6) -> set_prod_const_skill(90);
  bennyland.get_company(b6) -> set_prod_const_motivation(30);

  
  //Gets the consumers with high motivation and adds them to th  
  //the labour market
  Element_consumer * workers = bennyland.get_motivated_consumers();  
  bennyland.add_motivated_consumers(workers);


  Consumer * random = bennyland.get_random_consumer();

  random -> info_head();

  double sum_before = bennyland.get_capital_sum();
  int test = 0;  
  for(int j = 0; j < 20; j++) {
    bennyland.update_employees(b1);
    bennyland.update_employees(b2); 
    bennyland.update_employees(b3);
    bennyland.update_employees(b4);
    bennyland.update_employees(b5);
    bennyland.update_employees(b6);

    //Initial price check
    if (test == 0) {
      bennyland.produce();
      bennyland.pay_company_employees();
      bennyland.sell_to_market();
      bennyland.invest();
      bennyland.update_market();
      bennyland.consumers_buy();

      test = 1;
    }


    for(int i = 0; i < 5; i++) {
      bennyland.update_consumer_list();
      bennyland.produce();
      //bennyland.market_info();
      bennyland.negotiate_market_price();
      bennyland.pay_company_employees();
      bennyland.sell_to_market();
      //bennyland.market_info();
      //      bennyland.get_company(b4) -> info();
      bennyland.invest();
      bennyland.update_market();
      bennyland.consumers_buy();
      random -> info_short();
    }
    //bennyland.follow_capital(random);
  }

  //  bennyland.print_company_list();
  


  bennyland.market_info();
  //  bennyland.consumer_info();
 
  double sum_after = bennyland.get_capital_sum();

  cout << endl << "Capital before: " << sum_before << endl << "Capital after: " << sum_after << endl << "Difference: " << sum_before - sum_after << endl;
  //bennyland.labour_info();
  // bennyland.employee_info();
};


















                                                                                                                                                                                                                                                                                                                         market.cc                                                                                           0000644 0001766 0000062 00000004112 10311505707 013107  0                                                                                                    ustar   benny                           staff                           0000000 0000000                                                                                                                                                                        #include <iostream> 
#include <iomanip>
#include <string>

#include "market.h"



using namespace std;

Market::Market() : 
  name_("MARKET"),  
  items_(1000),
  marginal_(0.15),
  capital_(50000),
  price_in_(100),
  price_out_(100)
{}

void Market::info() {
  cout << name_ << endl << "-------------------------------------------------"
       << endl << "Items: " << items_ << endl << "Capital: " << capital_ << endl << "Price in: " << price_in_ << endl
       << "Price out: " << price_out_ << endl << endl;
}

double Market::get_items() {
  return items_;
}

double Market::get_marginal() {
  return marginal_;
}


double Market::get_capital() {
  return capital_;
}

long double Market::get_price_in() {
  return price_in_;
}

long double Market::get_price_out() {
  return price_out_;
}

void Market::set_items(double items) {
  items_ = items;
}

void Market::set_marginal(double marginal) {
  marginal_ = marginal;
}


void Market::set_capital(double capital) {
  capital_ = capital;
}

void Market::set_price_in(double price) {
  if(price > 0.000000001) {
    price_in_ = price;
  }
  else {
    price = 1;
  }
}

void Market::set_price_out(double price) {
  if(price > 0.000000001) {
    price_out_= price;
  } 
  else {
    price = 1;
  }
}

bool Market::change_items(double ch) {
  //  if(items_ >= -ch || ch > 0) {
    items_ += ch;
    return true;
    //}  
    //else {
    // cout << "Imarket ch_it och ch = " << ch << endl << "I = " << items_ << endl;
    // return false;
    //  }
}

void Market::change_marginal(double ch) {
  marginal_ += ch;
}

bool Market::change_capital(double ch) {
  //  if (capital_ >= -ch || ch > 0) {
    capital_ += ch;
    //    cout << "i market ch cap, ch = " << ch << endl;
    return true;
    //}
    //else {
    //cout << "Fel u market ch_cap" << endl;
    //return false;
    // }
}

void Market::change_price_in(double ch) {
  price_in_ += ch;
  cout << "i market ch_price in" << endl;
}

void Market::change_price_out(double ch) {
  price_out_ += ch;
  cout << "i market ch_price out" << endl;

}

void Market::negotiate_price(double items) {

}















                                                                                                                                                                                                                                                                                                                                                                                                                                                      main                                                                                                0000755 0001766 0000062 00001172310 10311505710 012170  0                                                                                                    ustar   benny                           staff                           0000000 0000000                                                                                                                                                                        ELF              ��4   �     4    ( % "    4   4�4��   �            �   ��                    � ���  ��           ��  �3�3�v  �w           � �����   �              ��              /lib/ld-linux.so.2           GNU               a   p   )           h                     .      -   "   _       n       7   L   R   Y   K              <   $   \   I   !   U   f       b   P   T       2   k   #           j   5       N       e   Z   F                        o   M   a   `   B   W   l       1      Q   m   [       g         @       =   G       S       d   +   8           A       i       c          C   ^       D   4                                                 	                                                                                                            '          *                        &                                                          0           
              /       J   6          (                  H                  X           E   ?   >           O   ;   ]       V   ,       %       3   :               9                      ��$   "  w   0�B   "  �   4�   "  $  L4   !  T  `.   "  �   �  "  �  ��^   "  L  ���   "  �  P4   !  �  ��	      �  ��  "    ��n        ��     ��%  ��8      �  @�8   "  6  ��@   "  `  Ģ4      n  0�/   "  �  ��   !  �   �7   "  I
  x�5   "  *  0�   "  �  Ԣ�     �  �)      �  ���     �  ��   "  -  �:   "  �  �#      �  `�?   "  U   �   "  �  �(      �  �3@   !  �  ��"   "  D  �  "  �  $�@      �  4�/        P�<   "  ;  l�     
 �  T��     A  ��     U  T4   !  �  d��      �  t��     �  Ъ   !  �  ��/      �  T�!   "  	  �#   "  f	  ��  "  �	  ���   "   �	  ��      �	  ��   "  
  ��/      �  ģ      E
  ��U   "  �
  p�B   "  �  ԣ1      G  �/   "  �  h   !    �(        ��$      !  8�   "  y  ��(   "    ��     ���  �   "  �  ��        H4   !  L  �~      �  84   !  �  $��      �  4��        D��        ��B   "  r  T�      �  0      �  t�V      �  ��)      �  ��      �  ��C        ���     �  Ĥ^      %  �Q   "  �  Ԥ       �  �<   "  �  �*   "  H  �(      Y  �  "  �   ��   "    ��     ���  ���      �  ܩ     ��O  ��         P�     ���  �   !  �  P�3   "     4   !  :  �4      H  $��      �  d     �  4�1      Y  D�H     g  �G   "  �  `��   "  �   �2   "  �  T�      B   �,     G  d�}   "   ]  H�$   "  �  ��-   "    t�5      !  l�'   "  �               libstdc++-libc6.2-2.so.3 release__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep __ls__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_R7ostreamRCt12basic_string3ZX01ZX11ZX21_R7ostream _S_freelist_index__t24__default_alloc_template2b1i0Ui _t24__default_alloc_template2b1i0._S_start_free __eq__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21T0_b _S_chunk_alloc__t24__default_alloc_template2b1i0UiRi clone__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep check_realloc__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ui _t24__default_alloc_template2b1i0._S_end_free _S_oom_malloc__t23__malloc_alloc_template1i0Ui __cp_push_exception _DYNAMIC endl__FR7ostream allocate__t23__malloc_alloc_template1i0Ui _._9exception data__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 __vt_9bad_alloc assign__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc data__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep __ls__7ostreamd copy__t18string_char_traits1ZcPcPCcUi __out_of_range__FPCc compare__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUiUi compare__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUi __ls__7ostreamPFR7ostream_R7ostream repup__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PQ2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep rep__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 setprecision__Fi _t24__default_alloc_template2b1i0._S_free_list __dl__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepPv compare__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUi __rtti_si what__C13runtime_error _._Q2t24__default_alloc_template2b1i0_5_Lock _init __ti13runtime_error _t24__default_alloc_template2b1i0._S_heap_size __throw __ls__7ostreamPCc __vt_13runtime_error __ls__H1ZUl_R7ostreamRCt6smanip1ZX01_R7ostream deallocate__t23__malloc_alloc_template1i0PvUi length__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUiPCcUi __deregister_frame_info terminate__Fv __Q2t24__default_alloc_template2b1i0_5_Lock __ls__H1Zi_R7ostreamRCt6smanip1ZX01_R7ostream __as__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 copy__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUiPCcUi __eq__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21PCX01_b _t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0.npos setw__Fi __start_cp_handler max_size__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 __as__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc _S_round_up__t24__default_alloc_template2b1i0Ui __cp_pop_exception _t23__malloc_alloc_template1i0.__malloc_alloc_oom_handler __13runtime_errorRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 _t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0.nilRep __ls__7ostreami move__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUiPCcUi compare__t18string_char_traits1ZcPCcT1Ui _fini __eh_rtime_match move__t18string_char_traits1ZcPcPCcUi length__t18string_char_traits1ZcPCc __tf13runtime_error __length_error__FPCc create__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUi __9exception grab__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep __nw__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUiUi setiosflags__FUl allocate__t24__default_alloc_template2b1i0Ui _S_refill__t24__default_alloc_template2b1i0Ui write__7ostreamPCci _GLOBAL_OFFSET_TABLE_ __vt_9exception _._13runtime_error _t24__default_alloc_template2b1i0._S_node_allocator_lock _._9bad_alloc __builtin_delete __builtin_new _._t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 deallocate__t24__default_alloc_template2b1i0PvUi assign__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUi cout __register_frame_info capacity__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 frob_size__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUi __eh_alloc excess_slop__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUiUi __gmon_start__ libm.so.6 exp atan libc.so.6 malloc srand time pthread_mutex_unlock pthread_mutex_lock _IO_stdin_used __libc_start_main _edata __bss_start _end GLIBC_2.0                                                                                                                                                              �         ii   %        �         ii   %      ��o  ��  ��(  Ъ,  �]   �i  �
  �  �  ��  ��  ��   �  �  �  �#  �$  �&  �'  �*   �+  $�-  (�1  ,�2  0�4  4�5  8�8  <�;  @�<  D�A  H�C  L�E  P�F  T�G  X�I  \�J  `�K  d�L  h�M  l�N  p�O  t�P  x�R  |�U  ��Y  ��[  ��`  ��a  ��c  ��d  ��h  ��j  ��m  U����=  �  �x  �� �5��%�    �%�h    ������%�h   ������%�h   ������%��h   �����%��h    �����%��h(   �����% �h0   �����%�h8   �p����%�h@   �`����%�hH   �P����%�hP   �@����%�hX   �0����%�h`   � ����%�hh   �����% �hp   � ����%$�hx   ������%(�h�   ������%,�h�   ������%0�h�   ������%4�h�   �����%8�h�   �����%<�h�   �����%@�h�   �����%D�h�   �p����%H�h�   �`����%L�h�   �P����%P�h�   �@����%T�h�   �0����%X�h�   � ����%\�h�   �����%`�h�   � ����%d�h�   ������%h�h   ������%l�h  ������%p�h  ������%t�h  �����%x�h   �����%|�h(  �����%��h0  �����%��h8  �p����%��h@  �`����%��hH  �P����%��hP  �@����%��hX  �0����%��h`  � ����%��hh  �����%��hp  � ���            1�^����PTRh�h@QVhp��s������U��S�    [�� P���   ��t�Ћ]��Ð���������U����=�3 u>���3�P��3� �С�3�8 u且���t���hl4�q�����3   �ÐU�����U����d���t���h,�hl4�����ÐU����Í�    ��    U���h�����j �A�������P�6��������hr�E�P�  �������h{�E�P�  �������h��E�P�r  �������h��E�P�\  �������h��E�P�F  �������h��E�P�0  �������h��E�P�  ��������E�P�E�P�  ���E�    �}��  ~�@�����E�P�  ����P�O  �����Eȃ���E�P�E�P��"  ���E�뻍�    ����E�P�E�P��  ��������E�P�E�P��"  ������E�P�E�P�  ��������E�P�E�P��"  ������E�P�E�P�  ��������E�P�E�P�"  ������E�P�E�P�`  ��������E�P�E�P�w"  ������E�P�E�P�8  ��������E�P�E�P�O"  ������E�P�E�P�  ��������E�P�E�P�'"  ������ ���$����E�P�E�P��  ��������E�P�E�P�(%  ����P�T  ������ ���$����E�P�E�P�  ��������E�P�E�P��$  ����P�T  ���������$����E�P�E�P�U  ��������E�P�E�P�$  ����P�1T  ���������$����E�P�E�P�  ��������E�P�E�P�b$  ����P��S  ���������$����E�P�E�P��  ��������E�P�E�P� $  ����P�S  ���������$����E�P�E�P�  ��������E�P�E�P��#  ����P�{S  ������ ���$����E�P�E�P�M  ��������E�P�E�P�#  ����P�)S  ���������$����E�P�E�P�  ��������E�P�E�P�Z#  ����P��R  ������ ���$����E�P�E�P��  ��������E�P�E�P�#  ����P�R  ������(���$����E�P�E�P�  ��������E�P�E�P��"  ����P�sR  ������0���$����E�P�E�P�E  ��������E�P�E�P�"  ����P�!R  ������ ���$����E�P�E�P�  ��������E�P�E�P�R"  ����P��Q  �����E�P�"  �����Eȃ���E�P�E�P�"  �����E�P�Y  �����Eă��E�P�*  �����E�P�V  ���]��E�    �E�    �}�~�  �v ����E�P�E�P�X  ��������E�P�E�P�/#  ������E�P�E�P�0  ��������E�P�E�P�#  ������E�P�E�P�  ��������E�P�E�P��"  ������E�P�E�P��  ��������E�P�E�P�"  ������E�P�E�P�  ��������E�P�E�P�"  ������E�P�E�P�  ��������E�P�E�P�g"  ���}� ua���E�P�>#  �����E�P�O#  �����E�P�0  �����E�P��$  �����E�P�V  �����E�P�$  ���E�   �E�    ���}�~
�   ��t& ���E�P�0   �����E�P�"  �����E�P�  �����E�P�"  �����E�P�  �����E�P�1$  �����E�P�  �����E�P��#  �����E�P�H*  ���E��a�����E���������E�P�  �����E�P�  ���]����h������E��e����$���h����h������E����$���h����h������E����$���h����h��h ��b�������P���������P��������P�A�������P��������P���������P� �������P��������P���������P����������    �O������j�E�P�  ����7����v ���j�E�P�  ����������j�E�P�  ���
��t& ��������j�E�P�m  ���������v ���j�E�P�R  �����������j�E�P�:  ���
��t& �������j�E�P�  ��1���   �   � ���j�E�P��  ���&�����t& ���j�E�P��  ���"���� ���j�E�P��  ���%���� ���j�E�P�  ���*���� ���j�E�P�  ���*���� ���j�E�P�  ���-���� ���j�E�P�j  ���2���������� �����t& �Í�&    ��'    U�吋E;Et
�E;Eu� �(�E�U� :}��0�E�U� :}� � �E�E�İ �U;Uu
�U;Ut���� �Í�    U�吋E;Et
�E;Eu� �8�E�U� :}������L��t& �E�U� :}�   �4�E�E빐�t& �E;Eu�E;E���Љ�����    ������ �Í�&    U����U�E�   9U�r��E����	�E���M���� �Ív U���S�]���S�������������������,�*��v ���j S�����������m������&    �����]��Í�    U��M�U����� �Ív ��������U���VS�u�]���SV������������������)�'� ���j V�Y����������������&    �����e�[^�Ít& U��� VS���&    �H4�E��}� uu���E�P������������j�������Ã���E�PS�U�����������	�x����t& ���j�E�P���������h�����0�։�PS�������A����u��փ��EP� ��������U��}� t�U����E��t& �K����9���&    �?���� ���j�E�P�������j����������� �����t& �e�[^�É���'    U���S�]���S���������U��}� u���S����������E��U���� �]���U��U�J������ �É�������������U���4S�E�U��U��P4�L4��)щM�E�;E�r#�L4�E��E�L4�U�����  ��  �v �E�;ErH�E�E��]��1��u���E���E�U��U��L4�E��E�L4�U����{  �v  ��t& ����T4��P�/��������U��э	��M��}� t:���E�P�^  ������    ��3��M�L4�U�
��E�L4����E�P�D��������L4�=L4 ��   �E�E�v �}�   v�   �����E�P��  ������    ��3��M�E��U�}� t?�E�U�
��E�L4�L4�U��P4����EP�EP�\��������d�v �E��w�����&    �P4    ���E�P��������L4�E�T4�L4�U���P4����EP�EP���������� �]��Ív ��'    U���(�E�   ����E�P�EP����������E��}�u�U����~���EP��  ������    ��3��M�E��E��E�U��MʉщM��E�   �E�E�EE�E�H;E�u�E��     ���E�U��E��ыU������    �Í�&    ��'    U��� VS�]���   v���S����������   ���S�#  ������    ��3��M����E�P�\  ���E���U��}� u;�����S��������P����������E��u����j�E�P��  �����k�t& �E��U��
��u����j�E�P�  �����E�������&    �5� ���j�E�P�  �������&    ��� ��������v � �����e�[^�É�U���VS�]�u���P���������� �e�[^�É�U���S�]���CP�N��������Ã��Sj�������E��E��X�E��@   �E��@ �U���� �]��Ív U���WVS�]�u�}�} t"����EPW���S�  �����R�=������e�[^_�É�U���S�]���P�S��������E��P���S�S  ����Pj �E�P�������E������E�P�,  ����� �]��É�U���S�]���S��  �������� �]��ÐU��U������ �ÐU���S�]���S��  �����P��� �]���U��S�U�M�Ѓ�s�   � 9��È�� �]��Ð������������U���WVS�]�uF���S�g  �������G �E� ���S�O  �����xw5���S�c�������9�w#������S�N�������PV�f���������u��E��E�� �e�[^_�Í�&    ��'    U���S�]�����S��  ����P��  ����� �]��ÐU���VS�u�]�����V�  ����P�+  �����S�  ������e�[^�ÐU���WVS�]�u�}�} t"����EPW���S�g  �����R�������e�[^_�É�������������U���WVS�u���V�������É]��v �E;E�v���h8����������    �ދE��U)�9Ev�E��U��)щM��v �E��U��)щM����V�����������+U9U�v���hB�2������	�Ǎ�&    �E��U)ЋUU�����E�PV�������������   ���E�P�V��������E�EP���V�U�������Pj �E�P�������E�UЋU�)�R���V�*���������U��EP�E�U�P�E�P�H������EP�EP�EP�E�P�0���������E�PV�������j�E�UЋU�)�R���V�����������U��EP�E�U�P���V�   ����P�������EP�EP�EP���V�o   ����P���������V�X   �����ǋE����� �e�[^_��U���VS�u�]���jV��   ���؃���t���V������� �e�[^�Í�    U��U�
������ �Ív U��U�J�����H���� �Ð����U���VS�]�u���h 4�������������t���S������� �e�[^�Ít& U������h 4�1������E� �Ív U���S�]�K�{ u���S��   ���]��Ð�����������U���VS�u�]�����V�&�������P�������؃���t���V�
��������e�[^�É���'    U��U�J��� �ÐU���VS�u�]���h84�   ������SV�   ����� �e�[^��U���VS�u�]�����S��������P�C   ������ �e�[^�Ív U���S�]����C��PS�   ���]��É�������������U���S�]�{ t���S����������C���S�"�������� �]��Ít& U���VS�]�u������V�Z�������PVS��   ����� �e�[^�Ð��������U��� VS�]�u�]����   v���VS��   ���   ��t& ���V����������    ��3��M����E�P��������E��U��
��E��U����������j�E�P�j������,��v ���j�E�P�R���������Z�����    � �����e�[^�É�U���WVS�]�u�}���WVj�j S������ ��� �e�[^_�É�U���VS�u�]���V�������e�[^�Ív ��������U���,WVS�]���h�S���������j�����������E����h��E�P�}�����������E�PV�  �����E� �C��|����}� t���V�-�������t& ���j�:����������E����h��E�P������������E�PW�$  �����E� �C�
������t& �}� t���W�������� ���j����������E��E����h��E�P������������E�P�E�P�C  �����E� �C��������}� t���E�P�]�������t& ���j,�j��������E��E����E�P�T  �����E� �C��_����}� t���E�P��������t& ��=������   �   � �}� t���V����������&    ����� �}� t���W���������t& ������ �}� t���E�P�������������� �}� t���E�P�{���������K���� ���j S�������X����	�t& ����� ������t& �e�[^_��U���,WVS�}�u���VW�w��������j�6��������E��E����h��E�P������������E�P�E�P�  �����E� �G��������}� t���E�P��������t& ���j����������E��E����h��E�P������������E�P�E�P�  �����E� �G���    �����}� t���E�P�M�������t& ���j�Z��������E��E����h��E�P�9�����������E�P�E�P�@A  �����E� �G���    �/����}� t���E�P���������t& ���j,����������E��E����E�P�.R  �����E� �G�������}� t���E�P��������t& ��������   �   � �}� t���E�P�]�������t& �{���� �}� t���E�P�;�������������� �}� t���E�P�������������� �}� t���E�P�����������K���� ���j W�������X����	�t& ����� �H����t& � ��������&    ���jV�e������� ���jV�S������҉؍e�[^_��U���S�]���CP�J  ���]��É�U���S�]���CP�*  ���]��É�U���S�]���h��E�P�I�����������E�PS�+   ���]��Ív U���S�]���CP�.A  ���]��É�U���VS�u�]���S�E�P�)�����������E�P�FP��F  ��� �
��t& ��������jS�`������� ���jS�N������ٍe�[^�É�U���S�]���h�������EP�  �����$h �� �������P�������]��ÐU���S�]������S�&   ����PS�������]��É�U��U�J��� �ÐU���S�]���CP��  ���]��É�U���$S�]�E�    �E�    ���CP��  ���]����CP�D  ���]���CP� Q  ���E��E����]��E�� �]���U���TS�]���CP��P  ���]����CP�  �����E���CP�h  ���]���CP�  ���]��E��E����]؃��CP�}P  ���]��E��M��u��]�����E����$�CP�
Q  �����E����E����]�����E����$�CP�P  ���]��Ív U���dS�]���CP�P  ���]����CP��  �����E���CP�  ���]���CP��  ���]��E��E����]؃��CP�O  ���]����CP��B  ���E����]��E��M��u��]�����E����$�CP�/P  �����E����E����]�����E����$�CP��O  ���]���U���S�]���CP��M  ���]��É�U���S�]���CP�fF  ���]��É�U��E�U�P�É�U��E�U�P�É�U��E�U�P�É�U���VS�]���j@�����������E�����E$���$�E���$�E���$�E���$V�k
  ��0���E� �E��
��t& �O����}� t���V� ��������&    ����E�P�CP�  ���2� �}� t���V����������t& ���������&    � �-����e�[^�É�U���S�]����EP�CP�&  ���]��É�U���WVS�u�]���j<�����������E����S�E�P������������FP�E�PW��-  �����E� �E����&    �_����}� t���W���������&    ����E�P�FP�;  ���2� �}� t���W����������t& ��������&    � �=���� �
��t& ��������jS�`������� ���jS�N������ٍe�[^_�ÐU���S�]���h�����h����h�����h��������CP�  ����P���h����h�����S���h����h�����h����h�����h	���h�����h����h��h ����������P�,�������P��������P��������P��������P� �������P��������P���������P�  ����P�d�������P���������P��������P�C�������P�8�������P��������P�"��������CP�g:  �����h��h ���������]��É�U���S�]���CP��  ���]��É�U���VS�u�]���S�E�P�-�����������E�P�FP�`:  ��� �	������t& ���jS�e������� ���jS�S������Սe�[^�Ív U���S�]���CP�^  ���]��É�U���S�]���CP�&  ���]��É�U���WVS�}�u���V�E�P������������E�P�GP�:  ������� � ���    �?������jV�������� ���jV�������ى؍e�[^_�Ív U���S�]���CP��  ����� �]���U���S�]����EP�CP�  ���]��É�U���VS�u�]���S�E�P�������������EP�E�P�FP�|=  ������EP�FP��  ��� ���    �o������jS��������� ���jS��������ٍe�[^�É�U���S�]����EP�CP�  ���]��É�U���S�]���CP�n=  ���]��É�U���0VS�u�]�����S�E�P�������������E�PV�H�������P�e,  ���]������S�E�P�������������E�PV��������P�B,  ���]�������E����$�E���$V�   �� ���E�E�P�FP�MA  ������u���� �	�t& �?������jS�������� ���jS�������ٍe�[^�É�U���S�]���CP��>  ���]��É�U���S�]���CP�?  ���]��É�U���S�]����E���$�E���$�CP��  �� ���  �
������t& �  � ������P����������   ��������E�����E��PR�E�P��  ������K�����&    ���h�����hh ��:�������P���������    �������j�E�P�]  ���������v ���E�P�������L����=������t& ����� ���j�E�P�  �����t& ���E�P�H������� ��������    ����� ������t& �]��Ív U���S�]���CP�!  ���]��É�U���S�]���CP�@  ���]��Ív ��'    U���������EP���������P���EP���������P�EP�����������Í�&    ��'    U����=D� u!���������h��hGhD��w������D�� �Í�&    U���VS�]�u���VS�x   ���e�[^�É�������������U���VS�u�]���SV�   ���X4��L������)�'� ���j V�%   ������-������&    �_����e�[^�Ít& U���VS�u�]���j�FP�t��������SV�K������e�[^�Ð������������U���VS�u�]���SV�h������Ъ����CP�FP�������
������t& ��������<�:�����j �FP���������� ���j V����������	�X����t& � �����e�[^�É�U��U�    �B    �B    �B    �B    �B    �B    �B    �B, ��� �ÐU��U�E��E�Z�B    �B    �E$�Z�B     �B$    �B, �B8    �B<    ��� �ÐU��U�E��E�Z�E�Z�E$�Z�B     �B$    �E,�B(�B, �B8    �B<    ��� �Ív U���S�]���hj���h��������S�R  �����$���hu���h��������S�  �����$���h����h��������S��  �����$���h����h��������S�  �����$���h�h ����������P��������P�>�������P��������P���������P��������P��������P���������P���������P�a�������P��������P���������P�@������{, t*���h�����h�h ���������P�������(���h�����h�h ����������P�x������]���U���DS�]�E�	   ���h�����h��E����U�RP�������E���P���h��E����U�RP��������E���P���h��E����U���RP��������E���P���h��E܃���U�RP�������E܃��P���h��Eԃ���U�RP�������Eԃ��P���h��Ẽ���U�RP�r������Ẽ��P���h��Eă���U�RP�P������Eă��Ph ���������P���������P���������P��������P���������P��������P���������P��������P��������P�i�������P��������P�S�������P��������P�=�������P��������]��É�U���dS�]�E�	   ���h��E�P������������S�  ������t���h��E�P�*  �����t& ���h��E�P�  �����h������E�P���h��E�����U����RP�������E����P������S�  �����$�E����U�RP��������E���P������S�  �����$�E�����U���RP�������E����P������S�  �����$�E؃���U�RP�v������E؃��P������S��  �����$�EЃ���U�RP�G������EЃ��P������S�  �����$�Eȃ���U�RP�������Eȃ��P������S�j  �����$�E�����U�RP��������E����P�E����jP�������E����P�E����h   P�������E����Ph ��B�������P�g�������P�\�������P�q�������P�F�������P�[�������P�0�������P�E�������P��������P�/�������P��������P��������P���������P��������P���������P��������P�>�������P��������]������j�E�P��������-��t& ���j�E�P����������*�����    � �]����]���U��E� � ��U��E�@� �Ív U��E�@� �Ív U��E�@� �Ív U��E�@8� �Ív U��U�J,��� �ÐU��E�@ � �Ív U��E�E��Ív U��E�E�X�É�U��E�E�X�É�U��E�E�X�É�U��E�E�X8�É�U��E�U�P,�É�U��E�E�X �É�U��E� �E��ÐU��E�@�E�X�Ív U��E�@�E�X�Ív U��E�@�E�X�Ív U��E�@8�E�X8�Ív U��E�@ �E�X �Ív U���S�]���S�-   �����S�)   �����S�   �����S��   ���]��ÐU��E��U���$S�]���]����S���������E�}� t���E����C���[�����e��C���[��������$�CP��  �����CP�  ���]���U���S�]��������$�CP�  �����CP�g  ���]��Ív U���$S�]���]����]����S����������E����C���������������}� t�� ����������������$S�  �����S��  ���]��ÐU���4S�]��]��C�K�]����C(P�|:  ���]��E��u��]��E��u��]��C �E��[ ����E����$�C(P�;  ������E������$S����������E������$�C(P�:  ���]��ÐU���VS�]�u���VS�H�������� �e�[^�Ð�������U���S�]���hkS�8������C    �C    �
��t& �?������,�*��v ���j S����������������&    �O����]��É�U���WVS�}�u���VW�������G    �G    �������v ���,�*� ���j W�=����������    ����� ������t& � �������&    ���jV�������� ���jV��������҉؍e�[^_��U���4S�]���h������CP���hl���h�����S���hwh ��9�������P���������P��������P��������P���������P���������S��  ���]����S�  ���]����S�  ���]���S�  ���]����S�  �����E܃��S��  �����E؃��h�����h������E���$���h����h������C�E�����$���h����h������E����$���h����h������E����$���h����h������E�P���h����h������E�P���h�h ����������P��������P�f�������P���������P��������P�E�������P��������P���������P�$�������P��������P���������P��������P�h�������P��������P���������P�G�������P��������P���������P�������]��É�U��U�J��� �ÐU���$S�]�E�    �E�    �{ tJ�C�E��t& �}� u�/�����E�P��2  ����P��������E����]��E���U����E�������� �]��Ív U���$S�]�E�    �E�    �{ t=�C�E��}� u�(���E�P�2  ���E����]��E���U��׍�&    �E���	�����t& �]��Ív U���$S�]�E�    �E�    �{ t:�C�E��t& �}� u�(���E�P�l2  ���E����]��E���U��׍�&    �E�� �]��É�U���$S�]�E�    �E�    �{ t6�C�E��}� u�(���E�P�,2  ���E����]��E���U��׍�&    �E�� �]��É�U���$S�]�E�    �E�    �{ t7�C�E��E��8 u�'��    ���E�P�1  ���E����]��E���U����E�� �]��ÐU���S�]�E�    �C�E��}� u�'��t& ���E�P�1  ������t�E��E���U��ыU���� �]��É�U���S�]�E�    �C�E��}� u�#����E�P�d1  ������u�E��E���U��ՋU���� �]��É�U���S�]�5������ș�{�U��C�E��E�    �E�;E�|��E���U��E�������E�P�D0  ����� �]��É�U���VS�u�]���SV�<  ��� �
��t& �Ͻ�����jS�@������� ���jS�.������ٍe�[^�É�U���WVS�]�{ tT���j�h����������E�����EP�CPV�/  �����E� �C�
�Y�����t& �}� t���V������� �N���j�����������E�����EPj W�>/  �����E� �C������v �}� t���W赾����� �C�N���t& �}� t���V蕾����� �m������t& �}� t���W�u������ ��觼���v � �ݼ���e�[^_�ÐU���WVS�]�C�{ �}   �C�E���E��8 u���    �E���U��捶    �}����j�'����������E�����EPj V�Q.  �����E� ��������&    �}� t���V�Ž����� �N���j�Խ���������E�����EPj W��-  �����E� �C��ǻ���v �}� t���W�u������ �Q� �}� t���V�]�������t& �o���� �}� t���W�>��������t& ���k�����&    � 蝻���e�[^_�ÐU���S�]���h�����S���h�h ��<�������P���������P趺�������h�����h������CP���h�h ����������P迻������P�t�������P�i������{ tL�C�E���    �}� u�8���E��PR�9��������h��h ��(������E���U��Ǎ�&    �]��Ív U���S�]�C�E��}� u� ���E��PR�}������E���U��܍t& �]��Ív U��� VS�]�E�    �C�E��}� u
�   ��t& ���E�P�D,  ���������E��us���E�P��,  ������u^���j褻���������E�������E�P��+  ����P�E�PV�+  �����E� �E��臹���v �}� t���V�5������ �E���U��O����U����/�-��t& �}� t���V������� ���7����v � �m����e�[^�É�U����E�E�    �U�U��U��: u��E�U��
�M���v �x t@�P�U��t& �U��: u���    �U��
�M��捶    �U��M�
�PB�M�щH��U�P�PB�M�щH�É�U���S�]�C�E�������fj �EP�������{ t>���CP�*  ����;Eu(�E��8 t�E���S�K��C    �C    �   �{ ��   ��E��8 u�v��    ���E��R�B*  ����;Eu�E���: t�K�E��U��
���-���E��R�*  ����;Eu�E��     �K���&    �E���U�농�    �(���h�����h h �蘷������P�������]��ÐU���S�]�C�E����CP��)  ���]����E��t�*��������fj �E�P�B*  ���E���S�C�E��K븋E��8 u�c���E��R�p)  ���]����E��u;������fj �E��R��)  ���K�E���: t�E��U��
���	�E��     �E���U�듋]��É�U���S�]�C�E����E�P��(  ���]����E��u4������fj ���E�P�(  ����P� ������E���S�K�C�E��C�E��E��8 u�g�t& ���E��R�r(  ���]����E��u;������fj �E��R�)  ���K�E���: t�E��U��
���	�E��     �E���U�돋]���U���LWVS�]���j薷���������E����j@職�������E��E����j j j j j j j j �E�P�}�����0���E� ���Pj W�'  �����E� �E�����O����}� t���U�R���������t& ��-����}� t���W�޶�������t& �{ ��   ���hj�E�P����������E���P�E�P��  �����	�ش���t& ���j�E�P�B��������j�ɶ�����ƃ���E�PV�3������蝴�����&    菴�����j�E�P����������h�������UԋU��҉�PV螳�����V������C�E��}� u�   ���E�P�s&  �����E���E�P�_&  �����E���E�P�O  ���]ȃ��E�P�=  ���]�����E��u���E�P��&  ������u�E��E��E���U��w�������E�P��%  �����   �   ���}� t���U�R�R������ �4�������}� t���W�5������ �9������t& ���j�E�P��������q���� 至�������j�E�P������������'����v � �]����e�[^_�ÐU���<WVS�]���j�޴���������E����j@�ɴ���������E����h  �?j h  �?j h  �?j h  �?j W������0���E� ���Pj V��$  �����E� �E����菲���}� t���W�@��������&    ��m����}� t���V���������t& �C�E��}� u�   ���E�P�$  ���]���E�P�$  ���E��M���M���]����E�P�R$  ���]؃��E�P�`$  ���E��M���M���]�����Eu�E��E��E���U��y����v ���E�P��#  �����[�Y���&    �}� t���W�U������ ��������t& �}� t���V�5������ ������
��t& �_���� 蘱���t& �e�[^_��U���4S�]�C�E��}� u�p���E�P�d#  �����E����E�P�������]����E�P��������]��E��M�E��M���E���]�����E����$�E�P�������E���U�눋]��Ív U���S�]�C�E��}� u�P���E�P��"  �����E�����E���$�E�P�c���������E���$�E�P��������E���U�몉��]��Ív U���S�]�C�E��}� u�'�����E�P�a"  ����P��������E���U��ы]��Ít& U���VS�u�]���SV蜰�����X4��ܯ�����)�'� ���j V���������软�����&    �����e�[^�Ít& U���VS�u�]9�t8�����V�B�������P������������S�(�������P������������� �e�[^�Ív ��������U���4S�E�E��]������E�gfff�E�������U���)щ���ʍ�E�)ȉE��E��M��  ���]��۰���E�VUUU�E���M�����)ȉE��M����ʋE�)ЉE��}�u
�E����]�� �E�U��E���}�u(���h�����h�h �蓮������P�������]���U��E� ��������Eu�E�     �@    �E� ��������E��u�E�     �@  �?��U���� �U��Ív U���(� �]�� �]�����E��M(���$�������E�M�E�M ���M����]��E����    �É�U������EP�������]����EP�������]����h  �?j �E����$�E����$�E����$�E����$�O�����0� ��U���(�  �]��( �]��E�    �E�    ����E��M���$�������E����]��E�� ��U����E��������E��@t�E�u�U��
��0 � �É�U���0VS�8 �]��8 �]��@ �]��H �]����h  �?j �E�P�]��������h  �?j �E�P�G��������h  �?j �E�P�1��������h  �?j �E�P���������j@�2����������E�����EP�E����$�E���$�E����$�E����$S�f�����0���E� �}� t���S辭�������t& ���C�
������t& �5� �}� t���S葭����� ����t& ���軫����&    � ������e�[^�É�U���VS�]���hj S�g������C    �C    �C    �C    �x �[���j�9����������E����hk �E�P������������E�PV�#��������E� �C�	�����t& �}� t���V�Ŭ����� �C     �� �[$�� �[,�� �[4��ת���v ���C�A� �}� t���V�}�������t& �� ���j S�!��������
虪����t& � �ͪ���e�[^�É�U���WVS�}�u���VW�������� �_�G    �G    �� �_���j���������E��E����hk �E�P�������������E�P�E�P���������E� �G�
�������t& �}� t���E�P被����� �E�G �� �_$�� �_,�� �_4���    诩�����L�J��v �}� t���E�P�R������ ����t& ���j W�����������m������&    蟩��� ���&    �O������jV��������� ���jV�������ى؍e�[^_�Ív U���S�]���h�����h��������CP���������P���h� ���h������C���$���h� ���h������C���$���h� ���h�����S���h� h �裨������P�T�������P��������P肨������P�ק������P���������P�a�������P趧������P�ۧ������P�@�������P��������P躧������P诧�����]��Ív U���S�]���h�����h� ���h�����Sh ���������P�i�������P�Χ������P�S��������CP�<������]���U���VS�]�u���VS��������� �؍e�[^�� ��U��E�@� �Ív U��E�@$� �Ív U��E�@,� �Ív U��E�@4� �Ív U���DS�]���CP�������]��C$�]����CP�������]��C,�]����CP����������E��E��]؃���E؃��$�E����$�E���$�E����$�E����$������0�]��E�� �]��Ív U���$S�]���EP�r������]����EP�T������]����h  �?j �E����$�E����$�E����$�E����$������0�]��E�� �]��Ív U��E�@� �Ív U��E�@� �Ív U��E�E�X�É�U��E�E�X$�É�U��E�E�X,�É�U��E�E�X4�É�U��E�E�X�É�U��E�E�X�É�U��E�@�E�X�Ív U��E�@$�@$�X$�Ív U��E�@,�E�X,�Ív U��E�@4�E�X4�Ív U��E�@�E�X�Ív U��E�@�E�X�Ív U���S�]������fj�EP����������EP�CP�U������]��ÐU���S�]���CP�������]��É�U���S�]���S�������C���[�]��ÐU���dS�]���S�i������]����CP�{��������E��E��]����C P��  ���]����CP�?������]��E��M��K4�]��E��u��]��E��]�����E����$�CP�i��������CP��������]��E��e��]��C�e��[�]��ÐU���   S�]���EP��������]����EP�������]����CP�3������]���CP�Q������]����CP���������E��C$�]��C,�]ȃ��S�J������]�����E�@�E��E����$�Eȃ��$�E��E����$�EЃ��$�E��E����$������0�]����C P�x  ���]����CP���������P�U��E��]��E��M��K4�u��]��E�    �E�    �E��e��M��e��]��E�� ��x�����U���   S�]���EP�������]����EP�������]����CP��������]���CP�������]����CP�W��������E��C$�]��C,�]ȃ��S�������]�����E܃��$�Eȃ��$�E��e����$�EЃ��$�E��e����$�������0�]����C P�K  ���]����CP����������E��E��]��E��M��K4�u��]��E�    �E�    �E��e��M��E��]��E�� ��x����É�U���4S�]���CP�v����������g  ����C,���$�C$���$�CP�C����� ���E�����EPS�J������]�����E�PS�k������]萍t& ����E�PS�S�������������E��t�8����E�PS�K  ������C,���$�C$���$�CP������� ���E�먃���EPS�������� !������E��u����EPS�u�������   �}����EPS��������]�����E�PS��������]�����E��uM����EPS�\������ !������E��u+����E�PS�   ������EPS�������� �'��&    � ������EPS�����������    �]��Ív U���S�]����E���$�CP�%���������E���$�CP�A������]��ÐU���S�]������fj �EP�4��������j j �EP����������EP�CP��������]��É�U���$S�]���C P�  ���]�����E��K���$S����������E����K���$�C P�N  ������C���$�C P�
  ������C�����$S�������]��Ív U����E�    �E�    �!�]��E�@��������E��u#�E��]�����E��u�E�@�E�H�]�����E��]�����Eu �ÐU���S�]���hK!S�8������C    �C    �
��t& �?������,�*��v ���j S襸��������������&    �O����]��É�U���WVS�}�u���VW�������G    �G    ��ם���v ���,�*� ���j W�=����������    话��� �����t& � �蛝����&    ���jV�������� ���jV�������҉؍e�[^_��U���S�]���h�����h`!���h�����h�!���h��h ��̜������P�1�������P趜������P��������P蠜�������h�����h������CP���h�!h ���������P詝������P�^�������P�S������]��Ív U���VS�]�C���j�p����������E�����EP�CPV�(  �����E� �C����_����}� t���V���������&    �.� �}� t���V������� ���	�t& ����� �X����t& �e�[^�ÐU���S�]���S�������{ t0�C�E���    �}� u����E��PR�������E���U��܃��h��h ��N������]��É�U���VS�u�]�����S�E�P蚶����������E�PV�   ����P�y������ ��]������jS�ε��������&    ���jS赵�����ҍe�[^�ÐU���S�]�������KA����U��C�E��E�    �E�;E�|���    �E���U��E���v �U���� �]���U���,WVS�}�u� �?  �G�E���t& �}� u�h�E�����U�RP�h  ���E����VP�  ���E���������j�E�P��������}� t���E�P�T  �������,  �E���U�뒉����h�!�E�P���������E����P�E�P����������v �������j�E�P�}��������j�������E����E�P�E�P�j������
��t& �ϙ���	�ș���t& ���j�E�P���������h���U�����U�U��҉�P�E�P�͘����腙���   ���h�!�E�P�K��������E����P�E�P�V���������N������j�E�P輳�������j�C������E�����E�P�U�R�������	�t& �����	�����t& ���j�E�P�R��������h���U������U܋U��҉�P�E�P�������Ř����   � ���j�E�P�+������#��������j�E�P�������z���� �ǘ�������j�E�P������������ ���j�E�P�ڲ��������� 菘��� ���j�E�P�������*������/���� �h����t& � �������&    ���jV腲������ ���jV�s������҉؍e�[^_��U���$S�]�E�    �E�    �C�E���    �}� u�/�����E�P�	  ����P�2������E����]��E���U����E�� �]��Ív U���$S�]�E�    �E�    �C�E��}� u�6��    �����E�P�=	  ����P�������E����]��E���U��Ð�E�� �]��É�U���VS�u�]����EP���S�E�P�
�����������E�PV��������P������� ��͖�����jS�>���������&    ���jS�%������ҍe�[^�ÐU���$S�]��!�]���!�]��C�E썶    �E�8 u�F��    ����E����$�E����$���E�P�;  ����P�L����� �E��U�뷍�&    �]��Ív U��� VS�u�]���h�!S�,  ������u���hK!S�  ������u�<�F�E��t& �}� u�(�����E�P�  ����P�������E���U��ѐ�>�����S�E�P覰����������E�PV��������P�q�������k�����&    �  � ������P�_���������   �ϕ�����E����E�PR�E�P���������������&    ���h�����h�!h ��
�������P菔�������    �ߔ�����j�E�P�-�������ǔ���v ���E�P�X������L����;������t& �ߔ��� ���j�E�P����������t& ���E�P�������� ��������    �_���� 蘔���t& � ��K�����&    ���jS赮������ ���jS裮�����ҍe�[^�Ív U���S�]�C�E��t& �}� u�(�����E�P��  ����P�������E���U��ѐ�]��Ív U���S�]�C�E��}� u�'�����E�P�  ����P��������E���U��ы]���U���S�]�C�E��t& �}� u�(�����E�P�U  ����P��������E���U��ѐ�]��Ív U���WVS�}�u���h�!V�K  ������t����EPW�   �������<�:����EP���V�E�P�������������E�PW� �������P�5���������� � �軒����&    ���jV�%������� ���jV�������҈؍e�[^_��U���S�]�C�E��t& �}� u�Y���h�����h"h ��b�������P����������EP���E�P�)  ����P���������
�E���U�럋]��É�U���$S�]���S����������E��E��E��E� �E� �}� u	�G��&    ����EP���E�P�  ����P���������E�}� t�U���a�E���U�봍v �C�E�E�;E�u�@����EP���E�P�i  ����P����������E�}� t�U����E��U�빍v � � �]��Ív U���S�]�C�E��t& �}� u�(�����E�P�  ����P�*������E���U��ѐ�]��Ít& ��'    U���VS�]��t& ���S�{�������9Ev���hI"�D�������ك��S�T���������+U�U��E�;Ev�E�E����EP�-�������9E�v���EP���������E�����E�P���EP��������P���S�	���������UR���������E��}� t�U����>�t& �E�;Eu1��.�t& ���S諥�����ƃ��EP蚥��������+U)�� �e�[^����������������U���S�]��    ���S�[�������9Ev���hI"�$�������ك��S�4���������+U�U��E�;Ev�E�E�����E�P�EP���S�!���������UR�5��������E��}� t�U�������S�פ��������+U+U��� �]��Í�    ��'    U���VS�]�uj�j VS������������� �e�[^�É�U���VS�]�u���j VS�   ��������� �e�[^�ÐU���WVS�]�}�u���W蹏������PVWS��������� �e�[^_�É�U��U�    �B    ��� �Ív U��U�E��E�B��� �ÐU���VS�]�u����FPS�}������ �؍e�[^�� �U��U�J��� �ÐU��U�    �B    ��� �Ív U��U�E��E�B��� �ÐU��U�J��� �ÐU���S�]���CP������� �]���U���S�]���CP�r������ �]���U���S�]���CP�b������ �]���U���S�]���CP�R������ �]���U���S�]���CP�B������ �]���U���S�]���CP�2�������� �]���U���S�]�������EfP�CP�v������]��É�����U���S�]���h�"S舧������"�[��"�[��"�[��"�[��"�[$���    �o������,�*��v ���j S�զ��������M������&    �����]��É�U���S�]���h�����h������C$���$���h�"���h������C���$���h�"���h������C���$���h�"���h������C���$���h�"���h�����h #���h�����Sh ��\�������P�%�������P芋������P��������P�t�������P�Ɋ������P��������P�S�������P訊������P�͊������P�2�������P臊������P謊������P��������P�f�������P苊������P耊�����]���U��E�@� �Ív U��E�@� �Ív U��E�@� �Ív U���(�E�@� ��U���(�E�@$� ��U��E�E�X�É�U��E�E�X�É�U��E�E�X�É�U���E�X#������E��u�E�E�X���E    �E  �?��U���E�`#������E��u�E�E�X$��E    �E  �?�ÐU��U�B�E�Z�� �Ív U��E�@�E�X�Ív U��U�B�E�Z�� �Ív U���S�]�C�E�[���h�����hh#h �菉������P�������]���U���S�]�C$�E�[$���h�����h}#h ��O�������P�Ԉ�����]���U��E��U��WV1�S���   �Ì�  ��������������)���9�s�׍�&    ��'    ������F9�r��[^_]Í�    ��    U����$�B   ��.�  �t$����������)������p�u菉���$�t$��]���������N��u����$Ð�����������U���S�̩�=̩�t��Ѓ���;�u�[��U����Ít& U��S�    [�ã�  R蚊���]���                          bad_alloc bempa AB bempa co benny inc. benjo pld benny enterprises johansson och johansson Bennyland Difference:  Capital after:  Capital before:             I@      N@      D@     �Q@      >@      T@     �V@pos > len len - n1 > max_size () - n2           ����                    bad_alloc  bennyland CONSUMERS LABOUR MARKET COMPANIES all   COMPANIES  Population:  Name:      ---------------------------------------- THE CITY ingen_consumer pos > len len - n1 > max_size () - n2 15no_return_error        bad_alloc Employed:  Spendwill:  Capital:  Skill:  Motivation:  yes no Employed Wage Items Cap Spendw Skill Mot         -C��6?�������?�������?����MbP?{�G�z�?�G�z��?)\���(�?�������?�������?pos > len len - n1 > max_size () - n2                           bad_alloc   Listsize:  Listname:  Accumulated spendwill:  Average motivation:  Accumulated items:  Accumulated capital:  Unemployed:  Employed:  LISTNAME:  SIZE:       �������?                The bitch is not employed here, error in remove_consumer in consumer_list no optimal consumer pos > len len - n1 > max_size () - n2     15no_return_error       bad_alloc                       vafan i functions.cc randomize        $@�������?      i@�������?      Y@����Mb`�  �����A      �?      y@�������?                bad_alloc  Employees    333333�?      N@      D@      �?     ��@333333�?      N@      D@      �?Employees:  Stock:  Capital:  Name:  ---------------------           @@    ��Apos > len len - n1 > max_size () - n2           bad_alloc                       ---------------------------------------------------------- COMPANIES Number of companies:  Cant find the company no list        333333�?      �?all Company not found vi loopar i com list upd emp pos > len len - n1 > max_size () - n2 pos > length () 15no_return_error                      bad_alloc       bad_alloc       bad_alloc MARKET             @�@333333�?     j�@      Y@Price out:  Price in:  Capital:  Items:                                 -------------------------------------------------       ��&�.>��&�.>i market ch_price in i market ch_price out pos > len len - n1 > max_size () - n2                ة                                                                                                                                               ����4�           eh P�|��      p�"
     �      .�  .    .
   .    .
   .    .   .    .
   .    .
   .    .   .    .�   .    �   ��Z      �      �    �y      �      �   ��-      �   @     ��Z      �      �   .   .    .   .     P  �      �   H   p  0�\      �      �   �   .   .    .   .   p   �  ��     �      �   �   .+   .    .   .    .   .    .1   .    .   . ,   0  ��@      �      �   .     `  �      �   ,   �   �     �      ��   .  $   �   ��      �      . H   �  �     �      �   �   .�   .    .   .   4   $  �*      �      �   �   .   ,   \  �Q      �      �
   .  8   �  p�B      �      �   �   �   .,   �  ��^      �      �	   .  ,   �  �#      �      �   .     (  8�      �   ,   H  H�$      �      �   .  $   x  l�'      �      � 8   �  ���      �      �   �   �   .,   �  0�/      �      �
   .  4     `�?      �      �   �   .   8   D  ��B      �      �   �   �   .8   �  ��     �      �
   �   �   .4   �  �:      �      �   �   .      �   �      �        4�      �   4   4  P�<      �      �   �   .   $   l  ��      �      . ,   �  ��$      �      �   .  4   �  �G      �      �   �   .      �  0�      �   4     @�8      �      �   �   .   4   T  x�5      �      �   �   .   ,   �  ��"      �      �   .  ,   �  �<      �      �   .  4   �   �7      �      �   �   .   H   $  `��      �      �   �   .U   .    .$   .   8   p   �2      �      �   �   �   . 4   �  T�!      �      �   �
   .          eh T�|��      ��h     �      �   �   �   .N   .    .T   .    .V   .    .>   .    .   .    .�   .    �   �   ���     �      �   �   �   .T   .    .^   .    .^   .    .>   .    .   .     .�   . &   .,   8  ��      �      �
   .  ,   h  ��      �      �
   .  ,   �  ��5      �      �   .  ,   �  �      �      �
   .  @   �  4�j      �      �   �   .&   .    . ,   <  ��G      �      �   .  ,   l  ��*      �      �
   .     �  �      �   ,   �  $�      �      �
   .  ,   �  D�`      �      �   .  ,     ���      �      �
   .  ,   L  h��      �      �
   .  ,   |  @�      �      �
   .  ,   �  `�      �      �
   .     �  ��      �      �  ��      �        ��      �   P   <  ���      �      �   �   .8   .0   .    .E   .    ,   �  ��"      �      �   .  T   �  ���      �      �
   �   �   .H   .    .E   . '   .,     ��n     �      �-   .  ,   H  �      �      �
   .  @   x  0�i      �      �   �   .!   .    . ,   �  ��      �      �
   .  ,   �  ��      �      �
   .  H     ��u      �      �   �   �   .-   .    .  ,   h  T�$      �      �
   .  ,   �  x�"      �      �   .  @   �  ���      �      �   �   .>   .    . ,      �"      �      �   .  ,   <  D�      �      �
   .  P   l  d��      �      �   �   .t   .    .   .    .   ,   �  P�      �      �
   .  ,   �  p�      �      �
   .  �      ��U     �      �   .    .    .   .    .   . !   .   .    .
   .    .   .    .0   .    ,   �  ��      �      �
   .  ,   �  �      �      �
   .     	      Z      �      ,	      y      �      L	      -      �   @   l	      Z      �      �   .   .    .   .  H   �	      \      �      �   �   .   .    .   .   p   �	           �      �   �   .+   .    .   .    .   .    .1   .    .   . ,   p
      @      �      �   .     �
            �   ,   �
           �      ��   .  $   �
      �      �      . H              �      �   �   .�   .    .   .   4   d      *      �      �   �   .   ,   �      Q      �      �
   .  8   �      B      �      �   �   �   .,         ^      �      �	   .     8            �   ,   X      $      �      �   .  $   �      '      �      � 8   �      �      �      �   �   �   .4   �      ?      �      �   �   .   8   $      B      �      �   �   �   .8   `      �     �      �
   �   �   .$   �  0�B      �      . $   �  ��9      �   %   .    �            �                  �      ,            �   4   L      5      �      �   �   .      �            �   4   �      <      �      �   �   .   $   �            �      . ,         $      �      �   .  4   4      G      �      �   �   .   ,   l      #      �      �   .  ,   �      /      �      �
   .  4   �  ��"      �      �   �   .   H     ��\      �      �   �   .   .    .   .   4   P      8      �      �   �   .   ,   �      <      �      �   .  ,   �      "      �      �   .  4   �  P�3      �      �   �   .   H      ���      �      �   �   .#   . #   .   .   4   l      7      �      �   �   .   H   �      �      �      �   �   .U   .    .$   .   8   �      2      �      �   �   �   . 4   ,      !      �      �   �
   .          eh ��|�       �G      �      <   h�K      �      \   ��I      �   ,   |    ��     �      �   .  ,   �   ���     �      �%   .  @   �   L�      �      �   .�  .    .%   .        L�      �      @  X�      �      `  h�      �      �  x�      �      �  ��      �      �  ��      �      �  ��      �         ��      �         ��      �      @  ��      �      `  ��      �      �  ��      �      �  �      �      �  �      �      �  (�      �         8�      �         L�      �      @  `�      �      `  t�      �      �  ��      �   ,   �  ��?      �      �   .     �  ��      �   ,   �  ��x      �      �   .  ,      \�9      �      �   .  ,   P  ���      �      �   .  ,   �  (��      �      �   .     �      Z      �      �      y      �      �      -      �   @         Z      �      �   .   .    .   .     T            �   H   t      \      �      �   �   .   .    .   .   p   �           �      �   �   .+   .    .   .    .   .    .1   .    .   . ,   4      @      �      �   .     d            �   ,   �           �      ��   .  $   �      �      �      . H   �           �      �   �   .�   .    .   .   4   (      *      �      �   �   .   ,   `      Q      �      �
   .  8   �      B      �      �   �   �   .,   �      ^      �      �	   .  ,   �      #      �      �   .     ,            �   ,   L      $      �      �   .  $   |      '      �      � 8   �      �      �      �   �   �   .,   �      /      �      �
   .  4   	      ?      �      �   �   .   8   H	      B      �      �   �   �   .8   �	      �     �      �
   �   �   .$   �	      B      �      .    �	            �      
            �   4   (
      <      �      �   �   .   $   `
            �      . ,   �
      $      �      �   .  4   �
      G      �      �   �   .      �
            �   4         8      �      �   �   .   4   H  ��(      �      �   �   .   ,   �      "      �      �   .  ,   �      <      �      �   .  4   �      7      �      �   �   .   H         �      �      �   �   .U   .    .$   .   8   d      2      �      �   �   �   . 4   �      !      �      �   �
   .          eh L�|�@      ��j      �      �   .   .    .   .  T   `   \��      �      �   �   �   .   .    .   . &   .,   �   ��Z     �      �3   .     �   X�      �   ,     h�q      �      �3   .  ,   8  ��i      �      �,   .  ,   h  H�b      �      �0   .  ,   �  ��^      �      �,   .  ,   �  �_      �      �4   .  ,   �  l�R      �      �$   .  ,   (  ��N      �      �    .  ,   X  �Z      �      �@   .  @   �  l�R      �      �   �   .   .    . \   �  ��     �      �   �   �   ./   .    .>   .    .N   .  \   ,  ��?     �      �
   �   �?   .,   .    .>   .    .J   .  ,   �  ��      �      �   .  ,   �  ��=      �      �   .  H   �  8�     �      �   �'   .q   .    .>   .      8  @��      �   ,   X  ��#     �      �   .  ,   �  ���      �      �   .  ,   �  ���      �      �   .  �   �  ���     �      �   �   �   .=   .0   .   .    .   .    .F   .    .)   .    .   .    .   .    .�   .    .   .  l   �  P��     �      �   �   �   .E   .0   .   .    .   .    .�   .    ,     ��      �      �   .  ,   <  ��m      �      �   .  ,   l  �D      �      �   .     �      Z      �      �      y      �      �      -      �   @   �      Z      �      �   .   .    .   .  H   @      \      �      �   �   .   .    .   .   p   �           �      �   �   .+   .    .   .    .   .    .1   .    .   . ,          @      �      �   .     0            �   ,   P           �      ��   .  $   �      �      �      . H   �           �      �   �   .�   .    .   .   4   �      *      �      �   �   .   ,   ,	      Q      �      �
   .  8   \	      B      �      �   �   �   .,   �	      ^      �      �	   .     �	            �   ,   �	      $      �      �   .  $   
      '      �      � 8   @
      �      �      �   �   �   .4   |
      ?      �      �   �   .   8   �
      B      �      �   �   �   .8   �
      �     �      �
   �   �   .$   ,      B      �      .    T            �      t            �      �            �   4   �      5      �      �   �   .      �            �   4         <      �      �   �   .   $   D            �      . ,   l      $      �      �   .  4   �      G      �      �   �   .   ,   �      #      �      �   .  ,         /      �      �
   .  4   4      "      �      �   �   .   H   l      \      �      �   �   .   .    .   .   H   �  `�\      �      �   �   .   .    .   .   4         8      �      �   �   .   4   <  ��U      �      �   �   .   $   t      9      �   %   . ,   �      <      �      �   .  ,   �      "      �      �   .  4   �      3      �      �   �   .   H   4      �      �      �   �   .#   . #   .   .   4   �      7      �      �   �   .   H   �      �      �      �   �   .U   .    .$   .   8         2      �      �   �   �   . 4   @      !      �      �   �
   .          eh X�|�,       ��      �      ��   .     L   ��H      �      l   <�      �   $   �   P�R      �   $   . ,   �   ��d      �   
   .K   .0  $   �   �L      �   2   .      T�.      �   T   ,  ��:     �      �   �2   .�   .0   .   .    .   .    �      Z      �      �      y      �          eh ��|�T      ��     �      �   �   .s   .    ..   .    .$   . d   t   ��a     �      �
   �   �   .r   .    .3   .    .%   . )   .  ,   �   D�     �      �   .  ,     `�h      �      �$   .  4   <  ��*      �      �   �   .      t  ��      �      �  �      �      �  �      �      �  $�      �   4   �  4��      �      �
   .s   .0   4   ,  ��q      �      �
   .K   .0      d  D�      �      �  T�      �      �  d�      �      �  t�      �      �  ��      �        ��      �      $  ��      �      D  ��      �      d  ��      �      �  ��      �      �  ��      �      �   �      �      �  �      �        (�      �   ,   $  <�7      �      �   .  ,   T  t�      �      �
   .  ,   �  ��#      �      �   .  ,   �  ���      �      �   .  8   �  l�4     �      �$
   .�   .0   .8      � *     �      �$
   .�   .0   .H   \  ��     �      �
   .+   .    .l   .    .  ,   �  x?      �      �   .  ,   �  �J      �      �   .  ,     �      �      �
   .     8  �c      �      X      Z      �      x      y      �      �      -      �   @   �      Z      �      �   .   .    .   .     �            �   H         \      �      �   �   .   .    .   .   p   h           �      �   �   .+   .    .   .    .   .    .1   .    .   . ,   �      @      �      �   .                 �   ,   ,           �      ��   .  $   \      �      �      . H   �           �      �   �   .�   .    .   .   4   �      *      �      �   �   .   ,   	      Q      �      �
   .  8   8	      B      �      �   �   �   .,   t	      ^      �      �	   .  ,   �	      #      �      �   .     �	            �   ,   �	      $      �      �   .  $   $
      '      �      � 8   L
      �      �      �   �   �   .,   �
      /      �      �
   .  4   �
      ?      �      �   �   .   8   �
      B      �      �   �   �   .8   ,      �     �      �
   �   �   .$   h      B      �      .    �            �   4   �      8      �      �   �   .      �            �                  �   4   (      <      �      �   �   .   $   `            �      . ,   �      $      �      �   .  4   �      G      �      �   �   .   4   �      5      �      �   �   .   ,   (      <      �      �   .  4   X      7      �      �   �   .   ,   �      "      �      �   .  8   �      2      �      �   �   �   . H   �      �      �      �   �   .U   .    .$   .   4   H      !      �      �   �
   .          eh |�|�@      �j      �      �   .   .    .   .  T   `   \�      �      �   �   �   .   .    .   . &   .,   �   ��      �      �0   .  H   �   ��      �      �   �   .1   .    .1   .   ,   4  Xf      �      �   .  @   d  �w      �      �   �   .)   .    . $   �  8T      �      � �   �  ��     �      �   �   �.   .   .    .b   .    .2   .    .    . 	   .   .    .!   .    .1   .    .    . 	   .   .    .(   .    .'   .    .   . &   .,   �  |e      �      �/   .  ,   �  �f      �      �/   .  @     L{      �      �   �   .)   .    . 4   X  �}      �      �M   .   .    �   �  H     �      �   �   .�   .    .   .    .   . !   .   .    .
   .    .   .    .0   . &   . ,   (  LI      �      �   .  ,   X  �D      �      �   .  ,   �  �I      �      �   .  H   �  (�      �      �   �   �   .d   .    .  ,     �z      �      �*   .  ,   4  X�      �      �   .  ,   d  ,I      �      �   .     �      Z      �      �      y      �      �      -      �   @   �      Z      �      �   .   .    .   .  H   8      \      �      �   �   .   .    .   .   p   �           �      �   �   .+   .    .   .    .   .    .1   .    .   . ,   �      @      �      �   .     (            �   ,   H           �      ��   .  $   x      �      �      . H   �           �      �   �   .�   .    .   .   4   �      *      �      �   �   .   ,   $      Q      �      �
   .  8   T      B      �      �   �   �   .,   �      ^      �      �	   .     �            �   ,   �      $      �      �   .  $   	      '      �      � 8   8	      �      �      �   �   �   .4   t	      ?      �      �   �   .   8   �	      B      �      �   �   �   .8   �	      �     �      �
   �   �   .4   $
  �     �      �   �   .   ,   \
  ��      �      �   .  $   �
      9      �   %   .    �
            �      �
            �      �
            �   4         5      �      �   �   .      L            �   4   l      <      �      �   �   .   $   �            �      . ,   �      $      �      �   .  4   �      G      �      �   �   .   ,   4      #      �      �   .  ,   d      /      �      �
   .  4   �      "      �      �   �   .   H   �      \      �      �   �   .   .    .   .   H         \      �      �   �   .   .    .   .   4   d      8      �      �   �   .   4   �  `.      �      �   �   .   4   �  �/      �      �   �   .   ,         <      �      �   .  ,   <      "      �      �   .  4   l      3      �      �   �   .   H   �      �      �      �   �   .#   . #   .   .   4   �      7      �      �   �   .   8   (  �:      �      �   �   �   .H   d      �      �      �   �   .U   .    .$   .   8   �      2      �      �   �   �   . 4   �      !      �      �   �
   .          eh ��|�      �      �      <         �   4   \   0+      �      �   �   .      �   \      �      �       Z      �      �       y      �      �       -      �   @         Z      �      �   .   .    .   .     X            �   H   x      \      �      �   �   .   .    .   .   p   �           �      �   �   .+   .    .   .    .   .    .1   .    .   . ,   8      @      �      �   .     h            �   4   �      <      �      �   �   .   $   �            �      .    �            �   ,              �      ��   .  $   8      �      �      . H   `           �      �   �   .�   .    .   .   4   �      *      �      �   �   .   ,   �      Q      �      �
   .  8         B      �      �   �   �   .,   P      ^      �      �	   .     �            �           |�        l      �      8   �      �      X   �      �   ,   x   �       �      �
   .  ,   �   �       �      �
   .  ,   �   �       �      �
   .  ,            �      �
   .  ,   8  0       �      �
   .  ,   h  P$      �      �
   .  ,   �  t&      �      �   .         eh 8�|�@      ��      �      �   .=   .    .   .  ,   `   ,`     �      ��   .     �   �      �      �   �      �      �   �      �      �   �      �        �      �      0  �      �      P  �      �      p  �      �      �  4      �      �  @3      �      �  t      �      �  �      �        �      �   ,   0  �@      �      �!   .  ,   `  �@      �      �!   .     �  8      �      �      Z      �      �      y      �      �      -      �   @         Z      �      �   .   .    .   .     T            �   H   t      \      �      �   �   .   .    .   .   p   �           �      �   �   .+   .    .   .    .   .    .1   .    .   . ,   4      @      �      �   .     d            �   ,   �           �      ��   .  $   �      �      �      . H   �           �      �   �   .�   .    .   .   4   (      *      �      �   �   .   ,   `      Q      �      �
   .  8   �      B      �      �   �   �   .,   �      ^      �      �	   .  ,   �      #      �      �   .     ,            �   ,   L      $      �      �   .  $   |      '      �      � 8   �      �      �      �   �   �   .,   �      /      �      �
   .  4         ?      �      �   �   .   8   H      B      �      �   �   �   .8   �      �     �      �
   �   �   .$   �      B      �      .    �            �   4         8      �      �   �   .      @            �      `            �   4   �      <      �      �   �   .   $   �            �      . ,   �      $      �      �   .  4   	      G      �      �   �   .   ,   H	      <      �      �   .  4   x	      7      �      �   �   .   ,   �	      "      �      �   .  8   �	      2      �      �   �   �   . H   
      �      �      �   �   .U   .    .$   .   4   h
      !      �      �   �
   .       ����h�����P�Ӧv�8��Y� ���A���&��>��ԯү~���Ʊ̱�۱� �K�Q�`�^�p������g�β޲`�W�}���7�����g�x�Է����з��ַ���ѿ�������������� �������5��D�W�z���w�������3�������b������7��L�����������(���f�~����J�W�B�i�����	�G�E�b�r���i�������7�5�R�b�>�e������7������r��7���������������������f�������� �H���      0   +   @   P      !   0   .   @   P      U   �   >   N   �   �   �   �   W   �   �   �   �   �   �   �   �   �   �     �� ��0�@�����������������_   q   �   �   �   �   ��������s� � ��3�B�      0   +   @   P      !   0   .   @   P      U   �   >   N   �   �   �   �   W   �   �   �   �   �   �   �   �   �   �     _   q   �   �   �   �   ����������0�+�@�P�k�����x�����������z����������;�V���y�����(�B���{���������������
�&�2���0��������Z��� �p��� ��������6�B�q����������������      0   +   @   P      !   0   .   @   P      U   �   >   N   �   �   �   �   W   �   �   �   �   �   �   �   �   �   �        !   0   .   @   P   {�����������   @   e   4   4   P   M   u   �   _   q   �   �   �   �   ���������t���W�p������������������������E������������'�������2�d������� �      0   +   @   P      !   0   .   @   P      U   �   >   N   �   �   �   �   W   �   �   �   �   �   �   �   �   �   �     _   q   �   �   �   �   ��������0+@Pk��x�������$":G�  �Bb���
 	�	�
6	K	�
v	�	�
�	U
�	
�
7
J
�
-7Z��V2�����*��*B�Px�7��      0   +   @   P      !   0   .   @   P      U   �   >   N   �   �   �   �   W   �   �   �   �   �   �   �   �   �   �        !   0   .   @   P      !   0   .   @   P      @   e   4   4   P   M   u   �   _   q   �   �   �   �   ��������      0   +   @   P      !   0   .   @   P      U   �   >   N   �   �   �   �   W   �   �   �   �   �   �   �   �   �   �     ���������� �       0   +   @   P      !   0   .   @   P      U   �   >   N   �   �   �   �   W   �   �   �   �   �   �   �   �   �   �     _   q   �   �   �   �   ��������         �     �     l�   0   (�   t�   t�
   /                  ܩ   x           ��   Ġ   0         ���o�����o   ���o��                                                ����    ����    ��        ������ʢڢ���
��*�:�J�Z�j�z���������ʣڣ���
��*�:�J�Z�j�z���������ʤڤ���
��*�:�J�Z�j�z�         F%�� 	   d   p�   d   p�/   <       >   �       m   �       �   �       �   �       �   �       0  �       |  �       �  �       �  �         �       >  �       c  �       }  �       �  �       �  �       �  �         �       9  �       c  �       y  �       �  �       �  �       �  �       0  �   ?'  x  �   �a  �  �   0Q �  �   9�  �  �   �d 	  �       !  �           �       :  �           �           �       S  �           �       p  �   �  �  � �         �       �  � "     �  � #     �  � $     �  � %       � (     )  � )     A  � *     X  � +     p  � ,     �  � -     �  � 2     �  � 3     �  � ;     �  � <       �           �         � �     5  � �     K  � �     a  � �     w  � �     �  � �     �  � �     �  � �     �  � �     �  � �       � �     	  � �     #	  � �     :	  � �     S	  � �     h	  � �     	  � �     �	  � �     �	  � �     �	  � �     �	  � �     �	  � �     
  � �     .
  � �     H
  � �     a
  � �     |
  � �     �
  � �     �
  � �     �
  � �     �
  � �       � �       � �     =  � �     ]  � �     v  � �         �       p  �   �  �  �         �       �  �   Co  p  �           �       �  �           �       �  � T         �         �        � #       �   Z �  �       p  �           �       p  �       1  � H     [  � K     �  � N     �  � O     �  � X        � ]     [  � a     �  � d     �  � e       � o     Q  � �     �  � �     /  � �     +  � �         �       F  � 5     s  � 7     �  � 8     �  � 9     �  � :         �       �  �   =    � I         �       ,  � �     E  � �       � �       � E    �  � _    �  � h    �  � p       � s        �       �  �   9  9   � �         �       P   � J     h   � K     �   � P     �   � R     �   � S     �   � �     !  � �     b!  � �     �!  � 	        �       �!  � #     �!  � $     "  � %         �           �       A"  �       �"  �           �           �       �"  �   �#  #  �       ]#  �       p  �   	  �#  � v         �           �       �#  �       $  �       I$  �       ^$  �       t$  �           �           �           �           �       �$  �       �$  �       p  �           �           �           �       �$  �       /%  �           �       y%  �   �� �%  �   �  p  �       �%  �   �  &&  �      W&  �          �       y&  �          �       p  �       �&  �   O�  p  �       �&  � c     �'  � k     �(  �   �  �(  � #     �(  � $     	)  � %     )  � &     2)  � '     H)  � (     `)  � )     v)  � .     �)  � 2     �)  � >     �)  � C     �)  � H     �)  � M     �)  � R     *  � X     (*  � d     >*  � i     S*  � n     k*  � t     �*  � u     �*  � {     �*  �   �  �*  � L     �*  � \     �*  � h         �       p  �       +  � �      +  � �     6+  � �     J+  � �     a+  � �     x+  � �     �+  � �     �+  � �     �+  � �     �+  � �     �+  � �     
,  � �     $,  �   0M  >,  �           �       Y,  �   J<  t,  �      �,  �          �       �-  � &     �*  �   �*  �-  � z         �       s.  �   2)  �.  � I         �       =/  � 1     X/  � 7     p/  � N     �0  � U         �       �0  �           �       �0  � �     �0  � �     �0  � �     1  �   �  .1  �   1  H1  � V         �       2  �      %2  � !     3  � %     D3  � 6     �4  � 6     5  � <     ,5  � H     �6  � O     �7  � R     �7  � _     N9  � f     m:  � j     �:  � �         �           �       �:  � �    �;  �     �<  �       p  �           �       =  � �        �       @=  �           �       V=  �   �O  m=  �       �*  �           �       .1  �   �f  �=  � A     9>  � b     R>  � l         �           �       �*  �   �  p  �       s.  �           �       _?  � <     v?  � �     �@  � �         �       �A  �       Y,  �           �           �       1  �           �       �A  �           �       �A  � �     �B  �           �           �       C  � �     JC  � �     kF  � �    �F  � �    �F  � �    �K  �         �           �       gL  �       �L  �           �       p  �       �L  �   �S CM  � $     �M  � %     �N  � &     �O  � '     ~P  � (     mQ  � =         �           �       !R  �           �           �       nR  � 	         �       �R  �       S  �       eS  �           �       �S  �   �{ �S  � 8     �T  � ;     6U  � f     -V  � p     $W  � x     'X  � �     ,Y  � �     (Z  � �     $[  � �     .\  � �     $]  � �     (^  � �     #_  � �     ,`  � �     ,a  � �     :b  � �     2c  � �     /d  � �     6e  � 5    (f  � ;    g  � ?    h  � C    i  � I    j  � O    k  � S    l  � W    �l  � [    �m  � _    �n  � c    �o  � i    �p  � m        �       �q  �       -r  �       �q  �       dr  �       zr  �       �r  �       �r  �           �           �           �       �r  �           �           �           �           �       p  �       �r  �           �           �       #s  �           �       ps  �           �       �s  �           �       t  �   F] Vt  � B     �u  � V     ,w  � �     z  � �     V}  � $        �           �       �}  �       �}  �   +P  �}  �           �       ~  �           �       4~  �           �       4~  �       4~  �       R~  �     �~  �         �           �       �  �   �^ �  �   � �  � ~     ̇  � �    {�  � 4         �       c�  � N         �       ��  �   �y ��  �   �  ��  �          �       ��  � 9         �       f�  �   �� m�  �   |� |�  �   � ��  � O         �       ��  �   �R  ��  �          �       �  � 2         �       ��  � P         �       ��  �   �-  �  �          �       ��  �           �       ��  � �    {�  � R    ��  $  p�    D         D         D         D  !       D  7       D  M       D   c       D ! y       D " �       D $ �       D ' �       D ( �       D )       D *       D -        D . H      D / p      D 0 �      D 1 �      D 2 �      D 6       D 7 R      D 8 �      D 9 �      D :       D ; Z      D < �      D = �      D >        D ? b      D @ �      D A �      D F (      D G <      D J O      D L c      D N r      D O �      D P �      D Q �      D R �      D S �      D T       D U @      D V h      D Y �      D Z �      D [ �      D \ �      D ] �      D ^ �      D _ �      D a �      D e �      D f       D g       D i .      D j =      D k L      D n [      D o j      D p y      D q �      D r �      D t �      D z �      D } �      D  �      D �  
  ��  �  �����  �  �����  �  �����  �   ����#�  � ! ����-�  � " ����7�  � $ ����I�  � F ����Y�  � J ����h�  � N ����z�  � O ������  � } ����    �      ��  � ' ����    �   �   ��  � ( ����    �   �       �         �      ��  � P ����    �   �      �   �  ��  � e ����    �   �      �   �      �   �      �   �      �   V	      $   "
  ��  $ �����  � �   
�  � �   �  � �   +�  � �   S  �   ��    D �       D �       D �       D �       D �$       D �(       D �4       D �@       D �X       �          �   X       $   Z   ;�  $ � �~�  � �   
�  � �   �  � �   +�  � �       D �       D �       D �       D �       D �$       D �0       D �<       D �C       D �F       D �P       D �X       D �p       D �w       �          �   w       $   y   ��    �    ��    E    	�        g�  $ 0 ����  � 0    !R  �   ��    D 0        D 0 	       D 1 	       D 2        D 3 $       D 3 +   ��  @ 0    ��  � 1 ����    �   	       �   +       $   -   ��    �     /�  $  ��Y�  �     y%  �   ��    D �    �%  �   ��    D  
   y%  �   �    D � U   f�  @         $   Z   s�  $  ���  �     ��  �         D �    �%  �   �    D  	   y%  �   #�    D �    ��  @     ��  @         $      ��  $  0�Y�  �     �  �         D �    �%  �   >�    D     y%  �   ��    D � U   f�  @     *�  @         $   \   <�  $ � ��t�  � �        D �        D �        D �        D �        D �        D � �       D � �       D � �       D �    ��  � � ������  � � ����    �          �   �       $     ��  $ � ��t�  � �        D �        D � 
       D � 
       D �        D � 4       D � ;   ��  @ �    ��  � � ����    �   
       �   ;       $   @   ��  $ L�#�  � L       D L       D L       D L   3�  @ L       �          �          $      C�    �    {�    �    ��    �    ��  $ � �%�  � �   4�  � �       D �       D �       D �       D �       D �%       D �-       D �5       D �>       D �P       D �X       D �o       D �{       D ��       D ��       D ��       D ��       D ��       D ��       D ��       D ��       D �      D �      D �'      D �@      D �c      D �k      D �q      D �{      D ��      D ��      D ��      D ��      D �      D �      D �      D   K�  � �����[�  � �����p�  � �����    �          �   %       �   P       �   P   ��  � �����    �   �       �   �   ��  � �����    �   �       �         �         �     ��  � �������  � �������  � �����    �   '      �   �      �   �      �         �         �         �         �         $     ��  $  �t�  �        D        D        D        D        D %       D 2       D U       D [       D  m       D !t       D "z       D #�       D $�       D %�       D '�       D *�       D *�   �  � ����+�  � ������  � ����:�  � ����K�  � ����a�  � ����t�  � ����    �          �   �       $   �   ~�  $ ��t�  � �       D �       D �       D �       D �       D �(       D �H       D �W       D �_       D �e       D ��       D ��       D ��       D �  ��  @ �   ��  � �����:�  � �������  � �����    �          �   _   ��  � �����    �   e       �   �       �   �       �   �       �   �       �   �       �   �       �   �       $     ��  $   ���  �      >�  �      !R  �   ��    D          D          D !        D ! #   ��  @      L�  @          �          �   #       $   *   Z�  $ : �>�  � :        D :        D : 
       D ; 
       D <        D = .       D > 4       D ? >       D @ E       D @ L   L�  @ :    ��  � < ����    �   
       �   L       $   Q   ��  $ � p�4�  � �    B�  � �    N�  � �    Y�  � �        D � 	       D �        D �        D �        D � :   c�  @ �    q�  @ �    }�  @ �        �          �   :       $   B   ��  $ F ��4�  � F        D F        D F 
       D G 
       D H        D I =       D J D       D J Y   c�  @ F    ��  � G ����    �   
       �   Y       $   ^   ��  $ � �I�  � �    #  �   �    D �        D � 
       D �    ^�  @ �        �   
       �          $   #   k�  $ � 8���  � �        D �        D �        D �    ^�  @ �        �          �          $      ��  $ � H���  � �        D �        D � 
       D �    ^�  @ �        �   
       �          $   $   8�  $ P l���  � P    ��  � P    !R  �   p�    D P        D P 
       D Q 
       D Q "   ��  @ P    ��  @ P        �   
       �   "       $   '   ��  $ W ����  � W    ��  � W        D W 	       D W        D X        D Y        D \ $       D \ z   ^�  @ W    ��  @ W        �          �   z       $   �    �  $ � 0���  � �    #  �   7�    D �        D � 
       D � *   ^�  @ �        �   
       �   *       $   /   }�  $ � `�-�  � �    <�  � �        D �        D �        D � 8   G�  @ �    V�  @ �        �          �   8       $   ?   a�  $ � ��4�  � �    B�  � �    N�  � �    Y�  � �    !R  �   ��    D � 	       D �        D �        D �        D � :   c�  @ �    q�  @ �    }�  @ �        �          �   :       $   B   ��  $ � �-�  � �    B�  � �    3�  � �    N�  � �    >�  � �        D � 	       D �        D �        D �        D � B       D � O       D � ]       D � �       D � �       D � �       D � �       D � �       D � �       D � ;      D � S      D � e      D � �      D � �      D � �      D � �  G�  @ �    I�  � � ����T�  � � ����    �          �   �   ��  � � ����    �   �       �   c      �   �      �   �      $   �  b�  $ P �s�  � P    ��  � P       �   �    D $        D $ 3   ��  @ P    ��  @ P        $   :   ��  $ �  ���  � �    #  �   #�    D �        D �        D �    ^�  @ �        �          �          $      �  $ Z4�#�  � Z   y%  �   7�    D Z       D Z       D [       D [   3�  @ Z       �          �          $      K�  $ �P���  � �   ��  � �       D �       D �       D �5   ��  @ �   ��  @ �       �          �          $   <   ��  $ �����  � �       D �       D �       D �       �          �          $      ��  $ m ��4�  � m    #  �   ��    D m        D m 
       D m    c�  @ m        �   
       �          $   $   3�  $ � �-�  � �    ��  � �        D �        D �        D � @   G�  @ �    ��  @ �        �          �   (       $   G   ��  $ I 0�4�  � I        D I        D I        D I    c�  @ I        �          �          $      ��  $ � @�-�  � �    N�  � �        D �        D �        D � 1   G�  @ �    }�  @ �        �           �   -       $   8   I�  $ � x�-�  � �    ��  � �        D �        D �        D � .   G�  @ �    �  @ �        �   *       �   *       $   5   �  & $ `$�    �     �  $ ' ����  � '    !R  �   ��    D '        D ' 
       D * 
       D *    ��  @ '        �   
       �          $   "   ��  $ K �4�  � K    #  �   �    D K        D K 
       D K 7   c�  @ K        �   
       �   7       $   <   _�  $ �  �-�  � �    N�  � �        D �        D �        D � 0   G�  @ �    }�  @ �        �          �   0       $   7   ��  $ �`���  � �   t�  � �   y%  �   h�    D �       D �       D �       D �       D �       D �&       D �0       D �P       D �_       D �i       D ��   �  @ �   ��  @ �   �  � �������  � �������  � �����    �          �   �       $   �    �  $ �  �-�  � �    N�  � �    Y�  � �    #  �   )�    D � 	       D �        D � *   G�  @ �    }�  @ �    ��  @ �        �          �   *       $   2   ��  $ � T���  � �    y%  �   \�    D �        D �        D �        D �    �  @ �        �          �          $   !       d   ��	   d   ����  d   ��/   <       >   �       m   �       �   �       �   �       �   �       0  �       |  �       �  �       �  �         �       >  �       c  �       }  �       �  �       �  �       �  �         �       9  �       c  �       y  �       �  �       �  �       �  �       0  �   ?'  x  �   �a  �  �   0Q �  �   9�  �  �   �d 	  �       !  �       :  �       S  �       p  �   �    �       p  �   �  �  �   Co  p  �       �  �         �   Z �  �       p  �       p  �       �  �   =  �  �   9  A"  �       �"  �       �"  �   �#  #  �       ]#  �       p  �   	  �#  �       $  �       I$  �       ^$  �       t$  �       �$  �       �$  �       p  �       �$  �       /%  �       y%  �   �� �%  �   �  p  �       �%  �   �  p  �       �&  �   O�  p  �       �(  �   �  �*  �   �  p  �       $,  �   0M  >,  �       Y,  �   J<  �*  �   �*  s.  �   2)  �0  �       1  �   �  .1  �   1  �<  �       p  �       @=  �       V=  �   �O  m=  �       �*  �       .1  �   �f  �*  �   �  p  �       s.  �       �A  �       Y,  �       1  �       �A  �       �B  �       gL  �       �L  �       p  �       �L  �   �S !R  �       �R  �       S  �       eS  �       �S  �   �{ �q  �       -r  �       �q  �       dr  �       zr  �       �r  �       �r  �       �r  �       p  �       �r  �       #s  �       ps  �       �s  �       t  �   F] �  �   �^ �  �   � ��  �       f�  �   �� ��  �   �y ��  �   �  m�  �   |� |�  �   � ��  �   �R  ��  �   Fj  ��  �   ��  %�  � �    ��  � R        �       L�  �          �       ��  $  ����  �         D  	       D         D  �      D  `  ��  @         �   �      �   �      $   h  ��  $  ����  �     \�  �         D  	       D         D  �      D  z  ��  @     i�  @         �   �      �   �      �   �      �   �      $   �  ~�  $   ����  �          D          D   
       D ! 
       D "    ��  @          �   
       �          $      ��  $ $ ����  � $        D $        D $ 
       D % 
       D &    ��  @ $        �   
       �          $      ��  $ ( ����  � (        D (        D ( 
       D ) 
       D * 0   ��  @ (        �   
       �   0       $   5   ��  $ , ���  � ,        D ,        D , 
       D . 
       D 0    ��  @ ,        �   
       �          $      ��  $ 2 4���  � 2    _  � 2        D 2        D 2        D 3        D 4 5   ��  @ 2    o  @ 2        �          �   3       $   j   �  $ 6 ����  � 6    �  � 6        D 6        D 6 
       D 7 
       D 8 B   ��  @ 6        �   
       �   B       $   G   �  $ : ����  � :        D :        D : 
       D ; 
       D < %   ��  @ :        �   
       �   %       $   *   �  $ > ���  � >        D >        D >        D ?        D @    ��  @ >        �          �          $      �  $ B $���  � B        D B        D B 
       D C 
       D D    ��  @ B        �   
       �          $       $ F D���  � F        D F        D F 
       D H 
       D J        D L V       D M [   ��  @ F    ; � H ����    �   
       �   [       $   `   G $ O ����  � O        D O        D O 
       D P 
       D Q        D R 0       D S B       D T T       D U _       D X q       D Y }       D Z �       D [ �       D ] �   ��  @ O    d � P ����u � Q ����� � R ����� � S ����� � T ����� � U ����� � X ����� � Z ����    �   
       �   �       $   �   � $ _ h���  � _        D _        D _ 
       D a 
       D b        D c 0       D e B       D f T       D g _       D i �       D j �       D k �       D l �       D n �   ��  @ _    d � a ����u � b ����� � c ����� � e ����� � f ����� � g ����� � i ����� � k ����    �   
       �   �       $   �    $ p @���  � p        D p        D p 
       D q 
       D r    ��  @ p        �   
       �          $      8 $ t `���  � t        D t        D t 
       D u 
       D v    ��  @ t        �   
       �          $      V $ x ����  � x    � � x        D x        D x        D y        D z    ��  @ x         �          �          $      � $ { ����  � {    � � {        D {        D {        D |        D }    ��  @ {         �          �          $      � $  ����  �      �         D         D         D �        D �    ��  @          �          �          $      " $ � ����  � �    B � �    U � �    c � �    s � � $       D �        D �        D �        D � �       D � �   ��  @ �    � � � ����    �          �   �       $   �   � $ � ����  � �    �  � �        D �        D � 
       D � 
       D �    ��  @ �        �   
       �          $   "   � $ � ����  � �    \�  � �        D � 	       D �        D �        D � |       D � �   ��  @ �    # @ �    8 � � ����    �          �   �       $   �   H $ � ����  � �        D �        D � 
       D � 
       D � E      D � T      D � i  ��  @ �        �   
       �   i      $   n  \ $ � ���  � �        D �        D � 
       D � 
       D �    ��  @ �        �   
       �          $       $ � 0���  � �    � � �        D �        D �        D �        D � 5   ��  @ �    � @ �        �          �   3       $   i    $ � ����  � �        D �        D � 
       D � 
       D �    ��  @ �        �   
       �          $      6 $ � ����  � �        D �        D � 
       D � 
       D �    ��  @ �        �   
       �          $      Z $ � ����  � �    \�  � �        D � 	       D �        D �        D � <   ��  @ �    � @ �        �          �   6       �   6       �   :       $   u   � $ � T���  � �        D �        D � 
       D � 
       D �    ��  @ �        �   
       �          $   $     $ � x���  � �    : � �        D �        D � 
       D � 
       D �    ��  @ �        �   
       �          $   "   K $ � ����  � �    \�  � �    �  � �        D �        D �        D �        D � 7       D � L   ��  @ �    � @ �        �          �   J       $   �   � $ �  ���  � �    �  � �        D �        D � 
       D � 
       D �    ��  @ �        �   
       �          $   "    $ � D���  � �        D �        D � 
       D � 
       D �    ��  @ �        �   
       �          $      7 $ � d���  � �    \�  � �        D �        D �        D �        D � A       D � t       D � �   ��  @ �    � @ �    � � � ����� � � ����� � � ����    �          �   �       $   �   � $ � P���  � �        D �        D � 
       D � 
       D �    ��  @ �        �   
       �          $      � $ � p���  � �        D �        D � 
       D � 
       D �    ��  @ �        �   
       �          $       $ � ����  � �    > � �    M � �        D �        D � 
       D � 
       D � @       D � E       D � �       D � P  ��  @ �        �   
       �   E   ^ � � ����    �   E       �   j       �   �       �   �       �   �       �   @       $   U  � $ � ����  � �        D �        D � 
       D � 
       D �    ��  @ �        �   
       �          $      � $ � ���  � �        D �        D � 
       D � 
       D �    ��  @ �        �   
       �          $      ��  $ ���� � �   � � �   � � �   � � �   S  �          D �       D �       D �       D �       D �$       D �(       D �4       D �@       D �X       �          �   X       $   Z   ;�  $ � �		 � �   � � �   � � �   � � �       D �       D �       D �       D �       D �$       D �0       D �<       D �C       D �F       D �P       D �X       D �p       D �w       �          �   w       $   y   g�  $ 0 ����  � 0    !R  �          D 0        D 0 	       D 1 	       D 2        D 3 $       D 3 +   ��  @ 0    ��  � 1 ����    �   	       �   +       $   -   ��    �     	 $  ��D	 �     y%  �          D �    �%  �   
       D  
   y%  �   U       D � U   Q	 @         $   Z   ^	 $  0�D	 �     	 �         D �    �%  �          D     y%  �   U       D � U   Q	 @     �	 @         $   \   <�  $ � ��t�  � �        D �        D �        D �        D �        D �        D � �       D � �       D � �       D �    ��  � � ������  � � ����    �          �   �       $     ��  $ � ��t�  � �        D �        D � 
       D � 
       D �        D � 4       D � ;   ��  @ �    ��  � � ����    �   
       �   ;       $   @   ��    �    ��  $ L�#�  � L       D L       D L       D L   3�  @ L       �          �          $      C�    �    {�    �    ��    �    ��  $ � �%�  � �   �	 � �       D �       D �       D �       D �       D �%       D �-       D �5       D �>       D �P       D �X       D �o       D �{       D ��       D ��       D ��       D ��       D ��       D ��       D ��       D ��       D �      D �      D �'      D �@      D �c      D �k      D �q      D �{      D ��      D ��      D ��      D ��      D �      D �      D �      D   K�  � �����[�  � �����p�  � �����    �          �   %       �   P       �   P   ��  � �����    �   �       �   �   �	 � �����    �   �       �         �         �     ��  � ������	 � �������  � �����    �   '      �   �      �   �      �         �         �         �         �         $     ��  $  �t�  �        D        D        D        D        D %       D 2       D U       D [       D  m       D !t       D "z       D #�       D $�       D %�       D '�       D *�       D *�   �  � ����+�  � �����	 � ����:�  � ����K�  � ����a�  � ����t�  � ����    �          �   �       $   �   ~�  $ ��t�  � �       D �       D �       D �       D �       D �(       D �H       D �W       D �_       D �e       D ��       D ��       D ��       D �  ��  @ �   �	 � �����:�  � ������	 � �����    �          �   _   ��  � �����    �   e       �   �       �   �       �   �       �   �       �   �       �   �       �   �       $     ��  $   ���  �      >�  �      !R  �          D          D          D !        D ! #   ��  @      L�  @          �          �   #       $   *   
 $ : �>�  � :        D :        D : 
       D ; 
       D <        D = .       D > 4       D ? >       D @ E       D @ L   L�  @ :    u
 � < ����    �   
       �   L       $   Q   ��  $ � p�~
 � �    B�  � �    N�  � �    Y�  � �        D � 	       D �        D �        D �        D � :   �
 @ �    q�  @ �    }�  @ �        �          �   :       $   B   ��  $ F ��~
 � F        D F        D F 
       D G 
       D H        D I =       D J D       D J Y   �
 @ F    u
 � G ����    �   
       �   Y       $   ^   ��    E    �
       k�  $ � 8��
 � �    #  �          D �        D �        D �    
 @ �        �          �          $      ��  $ � H� � �        D �        D � 
       D �    
 @ �        �   
       �          $   $   8�  $ P l���  � P    ��  � P    !R  �          D P        D P 
       D Q 
       D Q "   ��  @ P    ��  @ P        �   
       �   "       $   '   ��  $ W �� � W    ��  � W        D W 	       D W        D X        D Y        D \ $       D \ z   
 @ W    ��  @ W        �          �   z       $   �   }�  $ � `�$ � �    2 � �    #  �          D �        D �        D � 8   < @ �    J @ �        �          �   8       $   ?   a�  $ � ��~
 � �    B�  � �    N�  � �    Y�  � �    !R  �   	       D � 	       D �        D �        D �        D � :   �
 @ �    q�  @ �    }�  @ �        �          �   :       $   B   T $ � �$ � �    B�  � �    3�  � �    N�  � �    >�  � �        D � 	       D �        D �        D �        D � B       D � O       D � ]       D � �       D � �       D � �       D � �       D � �       D � �       D � ;      D � S      D � e      D � �      D � �      D � �      D � �  < @ �    I�  � � ����T�  � � ����    �          �   �   u
 � � ����    �   �       �   c      �   �      �   �      $   �  � $ �0�; � �   E � �       D �       D �       D �       D �?       �          �   ?       $   B   W   �     � $  ����  �   ��    D �        D � 7       $   9   � $  ���  �     � �         D �    �%  �   	       D  	   ��  �          D �    ^�  @      @         $       $ �  � � �    #  �          D �        D �        D �    
 @ �        �          �          $      ��  $ I 0�~
 � I        D I        D I        D I    �
 @ I        �          �          $      n $ � x�$ � �     � �        D �        D �        D � .   < @ �    ! @ �        �   *       �   *       $   5   �  $ Z4�#�  � Z   y%  �          D Z       D Z       D [       D [   3�  @ Z       �          �          $      K�  $ �P�. � �   ��  � �       D �       D �       D �5   < @ �   ��  @ �       �          �          $   <   J $ ���. � �       D �       D �       D �       �          �          $      ��  $ m ��~
 � m    #  �          D m        D m 
       D m    �
 @ m        �   
       �          $   $   3�  $ � �$ � �    ��  � �        D �        D �        D � @   < @ �    ��  @ �        �          �   (       $   G   ��  $ � � � �        D �        D � 
       D �    
 @ �        �   
       �          $   #    �  $ � 0� � �        D �        D � 
       D � *   
 @ �        �   
       �   *       $   /    $  ��� �     ��  �     ��  �   ��    D �        D �    � @     ��  @         $   "   � $  ��� �     � �         D �    ��  �   ��    D     ��  �   E�    D � U   � @      @         $   \    $ � @�$ � �    N�  � �    #  �          D �        D �        D � 1   < @ �    }�  @ �        �           �   -       $   8   �  & $ \$�    �     p        ��  $ K �~
 � K        D K        D K 
       D K 7   �
 @ K        �   
       �   7       $   <   �  $ ' ����  � '    !R  �          D '        D ' 
       D * 
       D *    ��  @ '        �   
       �          $   "   � $ L P�� � L    ��  � L    ��  �   X�    D P        D P ,   � @ L    ��  @ L        $   3   � $ L �� � L     � L    ��  �   ��    D �    ��  �   ��    D L    ��  �   �    D � �   � @ L    3 @ L        $   �   E $ �  �$ � �    N�  � �    #  �          D �        D �        D � 0   < @ �    }�  @ �        �          �   0       $   7   ��  $ �`���  � �   t�  � �   y%  �          D �       D �       D �       D �       D �       D �&       D �0       D �P       D �_       D �i       D ��   �  @ �   ��  @ �   �  � ������	 � ������	 � �����    �          �   �       $   �   � $ �  �$ � �    N�  � �    Y�  � �    #  �   	       D � 	       D �        D � *   < @ �    }�  @ �    ��  @ �        �          �   *       $   2   ��  $ � T���  � �    y%  �          D �        D �        D �        D �    �  @ �        �          �          $   !       d   &�	   d    �	 d    �/   <       >   �       m   �       �   �       �   �       �   �       0  �       |  �       �  �       �  �         �       >  �       c  �       }  �       �  �       �  �       �  �         �       9  �       c  �       y  �       �  �       �  �       �  �       0  �   ?'  x  �   �a  �  �   0Q �  �   9�  �  �   �d 	  �       !  �       :  �       S  �       p  �   �    �       p  �   �  �  �   Co  p  �       �  �         �   Z �  �       p  �       p  �       �  �   =  �  �   9  A"  �       �"  �       �"  �   �#  #  �       ]#  �       p  �   	  �#  �       $  �       I$  �       ^$  �       t$  �       �$  �       �$  �       p  �       �$  �       /%  �       y%  �   �� �%  �   �  p  �       �%  �   �  p  �       �&  �   O�  p  �       �(  �   �  �*  �   �  p  �       $,  �   0M  >,  �       Y,  �   J<  �*  �   �*  s.  �   2)  �0  �       1  �   �  .1  �   1  �<  �       p  �       @=  �       V=  �   �O  m=  �       �*  �       .1  �   �f  �*  �   �  p  �       s.  �       �A  �       Y,  �       1  �       �A  �       �B  �       gL  �       �L  �       p  �       �L  �   �S !R  �       �R  �       S  �       eS  �       �S  �   �{ �q  �       -r  �       �q  �       dr  �       zr  �       �r  �       �r  �       �r  �       p  �       �r  �       #s  �       ps  �       �s  �       t  �   F] ��  �       �  �   �^ �  �   � f�  �   a� ��  �   �y ��  �   �  m�  �   ]� |�  �   � ��  �   �R   � 0         �       � � O         �       { $   �� �         D         D         D  A       D  E   � @         �   A       �   A       $   G   � $  h�� �     � �     � �     � �     � �  $       D         D         D  E       D  I   � @         �   E       �   E       $   K   � $  ��� �     � �     � �     � �     � �  $     �  ,       D         D         D ) C       D ) G   � @         �   C       �   C       $   I     $ ,  �� � ,        D ,        D , 
       D 1 
       D 2 7      D 3 =      D 6 g      D 8 �  � @ ,        �   
       �   �      $   �  3  $ : ��� � :        D :        D : 
       D ; 
       D B        D C �  � @ :    P  � ; ����    �   
       �   �      $   �  ��  � �    {�  � R    \  $ E L�� � E        D E        D E 
       D F 
       D G        D I '       D J 9       D M T       D X h       D Y �  � @ E    P  � F ����z  � G ����    �   
       �   �      $      �  $ [ L�� � [        D [        D [        D \        D ] 
   � @ [         �          �   
       $      �  $ _ X�� � _        D _        D _        D `        D a    � @ _         �          �          $      �  $ b h�� � b        D b        D b        D c        D d    � @ b         �          �          $      �  $ e x�� � e        D e        D e        D f        D g    � @ e         �          �          $      	! $ i ��� � i        D i        D i        D j        D k    � @ i         �          �          $      '! $ m ��� � m        D m        D m        D n        D o    � @ m        �          �          $      P! $ q ��� � q        D q        D q        D r        D s    � @ q         �          �          $      m! $ u ��� � u    � � u        D u        D u        D v        D w    � @ u         �          �          $      �! $ x ��� � x    �! � x        D x        D x        D y        D z    � @ x         �          �          $      �! $ { ��� � {    � � {        D {        D {        D |        D }    � @ {         �          �          $      �! $ ~ ��� � ~    �! � ~        D ~        D ~        D         D �    � @ ~         �          �          $      " $ � ��� � �    *" � �        D �        D �        D �        D �    � @ �         �          �          $      9" $ � �� � �    c" � �        D �        D �        D �        D �    � @ �         �          �          $      t" $ � �� � �    �" � �        D �        D �        D �        D �    � @ �         �          �          $      �" $ � (�� � �    � � �        D �        D �        D �        D �    � @ �         �          �          $      �" $ � 8�� � �    �! � �        D �        D �        D �        D �    � @ �         �          �          $      �" $ � L�� � �    � � �        D �        D �        D �        D �    � @ �         �          �          $      
# $ � `�� � �    �! � �        D �        D �        D �        D �    � @ �         �          �          $      /# $ � t�� � �    Q# � �        D �        D �        D �        D �    � @ �         �          �          $      c# $ � ��� � �    �# � �        D �        D �        D �        D �    � @ �         �          �          $      �# $ � ��� � �        D �        D � 
       D � 
       D �        D � "       D � .       D � :   � @ �        �   
       �   :       $   ?   �# $ � ��� � �        D �        D �        D �    � @ �         �          �          $      �# $ � ��� � �        D �        D � 
       D � 
       D �        D � $       D � *       D � <       D � I       D � d       D � s   � @ �    �# � � ����$ � � ����$ � � ����    �   
       �   s       $   x   !$ $ � \�� � �        D �        D � 
       D � 
       D � %       D � 4   � @ �        �   
       �   4       $   9   E$ $ � ��� � �        D �        D � 
       D � 
       D �        D �        D � -       D � F       D � L       D � Z       D � f       D � ~       D � �   � @ �    j$ � � ����$ � � ����$ � � ����    �   
       �   �       $   �   �$ $ � (�� � �        D �        D � 
       D � 
       D �        D �        D � .       D � 7       D � @       D � I       D � a       D � x       D � �   � @ �    �$ � � �����$ � � �����$ � � �����$ � � ����    �   
       �   �       $   �   ��  $ �����  � �   
�  � �   �  � �   +�  � �   S  �          D �       D �       D �       D �       D �$       D �(       D �4       D �@       D �X       �          �   X       $   Z   ;�  $ � �~�  � �   
�  � �   �  � �   +�  � �       D �       D �       D �       D �       D �$       D �0       D �<       D �C       D �F       D �P       D �X       D �p       D �w       �          �   w       $   y   ��    �    ��    E    �$       g�  $ 0 ����  � 0    !R  �          D 0        D 0 	       D 1 	       D 2        D 3 $       D 3 +   ��  @ 0    ��  � 1 ����    �   	       �   +       $   -   ��    �     /�  $  ��Y�  �     y%  �          D �    �%  �   
       D  
   y%  �   U       D � U   f�  @         $   Z   s�  $  ���  �     ��  �         D �    �%  �   	       D  	   y%  �          D �    ��  @     ��  @         $      ��  $  0�Y�  �     �  �         D �    �%  �          D     y%  �   U       D � U   f�  @     *�  @         $   \   <�  $ � ��t�  � �        D �        D �        D �        D �        D �        D � �       D � �       D � �       D �    ��  � � ������  � � ����    �          �   �       $     ��  $ � ��t�  � �        D �        D � 
       D � 
       D �        D � 4       D � ;   ��  @ �    ��  � � ����    �   
       �   ;       $   @   ��  $ L�#�  � L       D L       D L       D L   3�  @ L       �          �          $      C�    �    {�    �    ��    �    ��  $ � �%�  � �   4�  � �       D �       D �       D �       D �       D �%       D �-       D �5       D �>       D �P       D �X       D �o       D �{       D ��       D ��       D ��       D ��       D ��       D ��       D ��       D ��       D �      D �      D �'      D �@      D �c      D �k      D �q      D �{      D ��      D ��      D ��      D ��      D �      D �      D �      D   K�  � �����[�  � �����p�  � �����    �          �   %       �   P       �   P   ��  � �����    �   �       �   �   ��  � �����    �   �       �         �         �     ��  � �������  � �������  � �����    �   '      �   �      �   �      �         �         �         �         �         $     ��  $  �t�  �        D        D        D        D        D %       D 2       D U       D [       D  m       D !t       D "z       D #�       D $�       D %�       D '�       D *�       D *�   �  � ����+�  � ������  � ����:�  � ����K�  � ����a�  � ����t�  � ����    �          �   �       $   �   ~�  $ ��t�  � �       D �       D �       D �       D �       D �(       D �H       D �W       D �_       D �e       D ��       D ��       D ��       D �  ��  @ �   ��  � �����:�  � �������  � �����    �          �   _   ��  � �����    �   e       �   �       �   �       �   �       �   �       �   �       �   �       �   �       $     ��  $   ���  �      >�  �      !R  �          D          D          D !        D ! #   ��  @      L�  @          �          �   #       $   *   7% $ : �>�  � :        D :        D : 
       D ; 
       D <        D = .       D > 4       D ? >       D @ E       D @ L   L�  @ :    �% � < ����    �   
       �   L       $   Q   ��  $ � p��% � �    B�  � �    N�  � �    Y�  � �        D � 	       D �        D �        D �        D � :   �% @ �    q�  @ �    }�  @ �        �          �   :       $   B   ��  $ F ���% � F        D F        D F 
       D G 
       D H        D I =       D J D       D J Y   �% @ F    �% � G ����    �   
       �   Y       $   ^   ��  $ � �I�  � �    #  �          D �        D � 
       D �    ^�  @ �        �   
       �          $   #   k�  $ � 8���  � �        D �        D �        D �    ^�  @ �        �          �          $      ��  $ � H���  � �        D �        D � 
       D �    ^�  @ �        �   
       �          $   $   8�  $ P l���  � P    ��  � P    !R  �          D P        D P 
       D Q 
       D Q "   ��  @ P    ��  @ P        �   
       �   "       $   '   ��  $ W ����  � W    ��  � W        D W 	       D W        D X        D Y        D \ $       D \ z   ^�  @ W    ��  @ W        �          �   z       $   �    �  $ � 0���  � �    #  �          D �        D � 
       D � *   ^�  @ �        �   
       �   *       $   /   }�  $ � `��% � �    �% � �        D �        D �        D � 8   �% @ �    �% @ �        �          �   8       $   ?   a�  $ � ���% � �    B�  � �    N�  � �    Y�  � �    !R  �   	       D � 	       D �        D �        D �        D � :   �% @ �    q�  @ �    }�  @ �        �          �   :       $   B   �% $ � ��% � �    B�  � �    3�  � �    N�  � �    >�  � �        D � 	       D �        D �        D �        D � B       D � O       D � ]       D � �       D � �       D � �       D � �       D � �       D � �       D � ;      D � S      D � e      D � �      D � �      D � �      D � �  �% @ �    I�  � � ����T�  � � ����    �          �   �   �% � � ����    �   �       �   c      �   �      �   �      $   �  � $ �0�; � �   X& � �       D �       D �       D �       D �?       �          �   ?       $   B   j& $ �  ���  � �    #  �          D �        D �        D �    ^�  @ �        �          �          $      �  $ Z4�#�  � Z   y%  �          D Z       D Z       D [       D [   3�  @ Z       �          �          $      K�  $ �P���  � �   ��  � �       D �       D �       D �5   ��  @ �   ��  @ �       �          �          $   <   ��  $ �����  � �       D �       D �       D �       �          �          $      ��  $ m ���% � m    #  �          D m        D m 
       D m    �% @ m        �   
       �          $   $   3�  $ � ��% � �    ��  � �        D �        D �        D � @   �% @ �    ��  @ �        �          �   (       $   G   ��  $ I 0��% � I        D I        D I        D I    �% @ I        �          �          $      �& $ � @��% � �    N�  � �        D �        D �        D � 1   �% @ �    }�  @ �        �           �   -       $   8    ' $ � ���% � �    N�  � �        D �        D �        D � !   �% @ �    }�  @ �        �          �   !       $   (   �  & $ H$�    �     �  $ ' ����  � '    !R  �          D '        D ' 
       D * 
       D *    ��  @ '        �   
       �          $   "   ��  $ K ��% � K    #  �          D K        D K 
       D K 7   �% @ K        �   
       �   7       $   <   ' $ �  ��% � �    N�  � �        D �        D �        D � 0   �% @ �    }�  @ �        �          �   0       $   7   ��  $ �`���  � �   t�  � �   y%  �          D �       D �       D �       D �       D �       D �&       D �0       D �P       D �_       D �i       D ��   �  @ �   ��  @ �   �  � �������  � �������  � �����    �          �   �       $   �   �' $ �  ��% � �    N�  � �    Y�  � �    #  �   	       D � 	       D �        D � *   �% @ �    }�  @ �    ��  @ �        �          �   *       $   2   ��  $ � T���  � �    y%  �          D �        D �        D �        D �    �  @ �        �          �          $   !       d   ��	   d   ��C( d   ��/   <       >   �       m   �       �   �       �   �       �   �       0  �       |  �       �  �       �  �         �       >  �       c  �       }  �       �  �       �  �       �  �         �       9  �       c  �       y  �       �  �       �  �       �  �       0  �   ?'  x  �   �a  �  �   0Q �  �   9�  �  �   �d 	  �       !  �       :  �       S  �       p  �   �    �       p  �   �  �  �   Co  p  �       �  �         �   Z �  �       p  �       p  �       �  �   =  �  �   9  A"  �       �"  �       �"  �   �#  #  �       ]#  �       p  �   	  �#  �       $  �       I$  �       ^$  �       t$  �       �$  �       �$  �       p  �       �$  �       /%  �       y%  �   �� �%  �   �  p  �       �%  �   �  p  �       �&  �   O�  p  �       �(  �   �  �*  �   �  p  �       $,  �   0M  >,  �       Y,  �   J<  �*  �   �*  s.  �   2)  �0  �       1  �   �  .1  �   1  �<  �       p  �       @=  �       V=  �   �O  m=  �       �*  �       .1  �   �f  �*  �   �  p  �       s.  �       �A  �       Y,  �       1  �       �A  �       �B  �       gL  �       �L  �       p  �       �L  �   �S !R  �       ��  �   �  �  �   �^ �R  �       S  �       eS  �       �S  �   �{ �q  �       -r  �       �q  �       dr  �       zr  �       �r  �       �r  �       �r  �       p  �       �r  �       #s  �       ps  �       �s  �       t  �   F] �  �   � ��  �   �y ��  �   Fj  ��  �   ��  ��  �       T( $  ����  �         D         D  
       D  )       D  e   ��  @         �   )       �   )       $   j   n( $  \���  �     �( �         D  	       D         D  *       D  f   ��  @     �( @         �   *       �   *       �   4       �   4       $   �   ) $  ����  �         D         D  
       D  
       D  y       D  �       D  �       D   �       D ! �       D " �       D ) �       D * U  ��  @     #) �  ����4) �  ����E) �  ����\) �   ����o) � ! ����~) � " ����    �   
       �   U      $   Z  �) $ . X���  � .        D .        D .        D /        D 0    ��  @ .        �          �          $      �) $ 2 h���  � 2        D 2        D 2 
       D 4 
       D 6        D 7        D 8 0       D 9 U       D : _       D = h       D ? l   ��  @ 2    �) � 3 �����) � 4 ����    �   
       �   l       $   q   �) $ A ����  � A        D A        D A 
       D D 
       D F        D G        D H ,       D I C       D J T       D M [       D O d   ��  @ A    �) � C �����) � D ����    �   
       �   d       $   i   * $ Q H���  � Q        D Q        D Q 
       D S 
       D U        D V        D W 0       D Y G       D \ X       D ] ]   ��  @ Q    �) � R �����) � S ����    �   
       �   ]       $   b   :* $ _ ����  � _        D _        D _ 
       D a 
       D c        D d        D e ,       D f C       D h T       D i Y   ��  @ _    �) � ` �����) � a ����    �   
       �   Y       $   ^   e* $ l ���  � l        D l        D l 
       D o 
       D q        D r        D s 4       D u K       D x U       D y Z   ��  @ l    �) � n �����) � o ����    �   
       �   Z       $   _   �* $ { l���  � {        D {        D { 
       D } 
       D         D � $       D � 9       D � <       D � F       D � M   ��  @ {    �) � | �����* � } ����    �   
       �   M       $   R   �* $ � ����  � �        D �        D � 
       D � 
       D �        D �         D � 5       D � 8       D � B       D � I   ��  @ �    �) � � �����* � � ����    �   
       �   I       $   N   �* $ � ���  � �        D �        D � 
       D � 
       D �        D �         D � 1       D � 9       D � @       D � U   ��  @ �    + � � �����) � � ����    �   
   ��  � � ����    �           �   @       �   U       $   Z   + $ � l���  � �    �( � �        D �        D �        D �        D �    ��  @ �    �+ @ �        �          �          $   R   �+ $ � ����  � �    �+ � �        D � 	       D �        D �        D �        D � f       D � �       D �   ��  @ �        �          �   �       $     �+ $ � ����  � �    �+ � �        D � 	       D �        D �        D �        D �        D � 0       D � @       D � �       D � 7  ��  @ �    �) � � ����    �          �   �       $   ?  , $ � ���  � �        D �        D � 
       D � 
       D � A       D � �       D � �       D � �       D � �       D � �       D � �   ��  @ �    �) � � ����    �   
       �   �       $   �   1, $ � ����  � �        D �        D � 
       D � 
       D �        D � *       D � 8   ��  @ �    �) � � ����    �   
       �   8       $   =   Q, $ � 8���  � �        D �        D �        D �        D �        D � (       D � ^       D � �       D � �       D � �   ��  @ �    �) � � �����, � � ����    �          �   �       $     �, $ � @���  � �    �, � �        D �        D � 	       D � 	       D �        D �         D � #       D � 0       D � 6       D � <       D � P       D � `       D � h       D � v       D � |       D � �   ��  @ �     �) � � �����, � � �����, � � ����    �   	       �   �       $   �   �, $ � ����  � �    $- � �        D �        D � 
       D � 
       D �        D � %       D � A       D � I       D � Q       D V       D ]       D i       D s       D 	�       D �       D �       D �       D �       D �       D �       D �       D �       D   ��  @ �    �) � � ����    �   
       �         $   #  5- $ ����  �    _- �        D        D 
       D  
       D #       D $0       D %E       D &M       D 'S       D +X       D ,b       D -�       D .�       D /�       D 0�       D 3�       D 6�       D 7�   ��  @    �) �  ����    �   
       �   �       $   �   s- $ :����  � :   �- � :       D :       D :
       D ;
       D >       D ?,       D @O       D AW       D BZ       D F`       D Gt       D H�       D I�       D J�       D K�       D N�       D Q�       D R�   ��  @ :   �) � ;����    �   
       �   �       $   �   �- $ U����  � U   M � U   > � U       D U	       D U       D W       D X�       D Y�       D [x      D \�      D ]�      D _�      D a�      D c�      D d      D e�  ��  @ U   �) � V�����- � W����    �          �   x  �- � \����. � ]����    �   �      �   �      �         �          $   �  . $ gP���  � g   U � g   � � g       D g	       D g       D j       D m�       D r�       D s:      D u@      D vP      D w�  ��  @ g   �) � i����C. � j����    �          �   e      $   �  P. $ y���  � y   z. � y   �. � y   �. � y       D y       D y
       D }
       D ~       D ,       D �>       D �P       D �f       D �~       D ��   ��  @ y   �) � {����    �   
       �   
   �- � ~����� � ����� � ������. � �����    �          �   ~       �   �       �   �       $   �   �. $ �����  � �   �. � �       D �       D �
       D �
       D �       D �,       D �D       D �\       D �h   ��  @ �   �) � �����    �   
       �   
   �- � �����    �          �   \       �   h       �   h       $   m   �. $ ����  � �       D �       D �
       D �
       D �       D �5       D �?   ��  @ �   �) � �����    �   
       �   ?       $   D   ��  $ ���/ � �   (/ � �   8/ � �   I/ � �   S  �          D �       D �       D �       D �       D �$       D �(       D �4       D �@       D �X       �          �   X       $   Z   ;�  $ � �Y/ � �   (/ � �   8/ � �   I/ � �       D �       D �       D �       D �       D �$       D �0       D �<       D �C       D �F       D �P       D �X       D �p       D �w       �          �   w       $   y   g�  $ 0 ����  � 0    !R  �          D 0        D 0 	       D 1 	       D 2        D 3 $       D 3 +   ��  @ 0    ��  � 1 ����    �   	       �   +       $   -   ��    �     j/ $  ���/ �     y%  �          D �    �%  �   
       D  
   y%  �   U       D � U   �/ @         $   Z   �/ $  0��/ �     �/ �         D �    �%  �          D     y%  �   U       D � U   �/ @     �/ @         $   \   <�  $ � ��t�  � �        D �        D �        D �        D �        D �        D � �       D � �       D � �       D �    ��  � � ������  � � ����    �          �   �       $     ��  $ � ��t�  � �        D �        D � 
       D � 
       D �        D � 4       D � ;   ��  @ �    ��  � � ����    �   
       �   ;       $   @   ��    �    ��  $ L�#�  � L       D L       D L       D L   3�  @ L       �          �          $      C�    �    {�    �    ��    �    ��  $ � �%�  � �   �/ � �       D �       D �       D �       D �       D �%       D �-       D �5       D �>       D �P       D �X       D �o       D �{       D ��       D ��       D ��       D ��       D ��       D ��       D ��       D ��       D �      D �      D �'      D �@      D �c      D �k      D �q      D �{      D ��      D ��      D ��      D ��      D �      D �      D �      D   K�  � �����[�  � �����p�  � �����    �          �   %       �   P       �   P   ��  � �����    �   �       �   �   0 � �����    �   �       �         �         �     ��  � �����10 � �������  � �����    �   '      �   �      �   �      �         �         �         �         �         $     ��  $  �t�  �        D        D        D        D        D %       D 2       D U       D [       D  m       D !t       D "z       D #�       D $�       D %�       D '�       D *�       D *�   �  � ����+�  � ����10 � ����:�  � ����K�  � ����a�  � ����t�  � ����    �          �   �       $   �   ~�  $ ��t�  � �       D �       D �       D �       D �       D �(       D �H       D �W       D �_       D �e       D ��       D ��       D ��       D �  ��  @ �   10 � �����:�  � �����G0 � �����    �          �   _   ��  � �����    �   e       �   �       �   �       �   �       �   �       �   �       �   �       �   �       $     ��  $   ���  �      >�  �      !R  �          D          D          D !        D ! #   ��  @      L�  @          �          �   #       $   *   7% $ : �>�  � :        D :        D : 
       D ; 
       D <        D = .       D > 4       D ? >       D @ E       D @ L   L�  @ :    �% � < ����    �   
       �   L       $   Q   ��  $ � p��% � �    B�  � �    N�  � �    Y�  � �        D � 	       D �        D �        D �        D � :   �% @ �    q�  @ �    }�  @ �        �          �   :       $   B   ��  $ F ���% � F        D F        D F 
       D G 
       D H        D I =       D J D       D J Y   �% @ F    �% � G ����    �   
       �   Y       $   ^   ��    E    �$       k�  $ � 8�_0 � �    #  �          D �        D �        D �    t0 @ �        �          �          $      ��  $ � H��0 � �        D �        D � 
       D �    t0 @ �        �   
       �          $   $   8�  $ P l���  � P    ��  � P    !R  �          D P        D P 
       D Q 
       D Q "   ��  @ P    ��  @ P        �   
       �   "       $   '   ��  $ W ���0 � W    ��  � W        D W 	       D W        D X        D Y        D \ $       D \ z   t0 @ W    ��  @ W        �          �   z       $   �   }�  $ � `��% � �    �% � �    #  �          D �        D �        D � 8   �% @ �    �% @ �        �          �   8       $   ?   a�  $ � ���% � �    B�  � �    N�  � �    Y�  � �    !R  �   	       D � 	       D �        D �        D �        D � :   �% @ �    q�  @ �    }�  @ �        �          �   :       $   B   �% $ � ��% � �    B�  � �    3�  � �    N�  � �    >�  � �        D � 	       D �        D �        D �        D � B       D � O       D � ]       D � �       D � �       D � �       D � �       D � �       D � �       D � ;      D � S      D � e      D � �      D � �      D � �      D � �  �% @ �    I�  � � ����T�  � � ����    �          �   �   �% � � ����    �   �       �   c      �   �      �   �      $   �  � $ �0�; � �   �0 � �       D �       D �       D �       D �?       �          �   ?       $   B   �0 $  �D	 �     �0 �     C( �          D Y   �%  �   	       D  	   C( �          D Y   Q	 @     �0 @         $      j& $ �  ��0 � �    #  �          D �        D �        D �    t0 @ �        �          �          $      ��  $ I 0��% � I        D I        D I        D I    �% @ I        �          �          $      �0 $ � x��% � �    �1 � �        D �        D �        D � .   �% @ �    �1 @ �        �   *       �   *       $   5   �  $ Z4�#�  � Z   y%  �          D Z       D Z       D [       D [   3�  @ Z       �          �          $      K�  $ �P��1 � �   ��  � �       D �       D �       D �5   �1 @ �   ��  @ �       �          �          $   <   �1 $ ����1 � �       D �       D �       D �       �          �          $      ��  $ m ���% � m    #  �          D m        D m 
       D m    �% @ m        �   
       �          $   $   3�  $ � ��% � �    ��  � �        D �        D �        D � @   �% @ �    ��  @ �        �          �   (       $   G   ��  $ � ��0 � �        D �        D � 
       D �    t0 @ �        �   
       �          $   #    �  $ � 0��0 � �        D �        D � 
       D � *   t0 @ �        �   
       �   *       $   /    $  ��2 �     ��  �     C( �          D Y       D Y   2 @     ��  @         $   "    2 $  ��2 �     O2 �         D Y   ��  �          D     C( �   U       D YU   2 @     �	 @         $   \   i2 $  `�2 �     �2 �     ��  �   h�    D         D         D  U   2 @     �2 @         �   !       �   !       $   \   �& $ � @��% � �    N�  � �    #  �          D �        D �        D � 1   �% @ �    }�  @ �        �           �   -       $   8   �2 $ � ���% � �    �3 � �        D �        D �        D �        D � J       D � N   �% @ �    �3 @ �        �          �   N       $   U   �  & $ �$�    �     �3        �3        #4 $  ��C( �          D         D  7       $   9   ��  $ K ��% � K    #  �          D K        D K 
       D K 7   �% @ K        �   
       �   7       $   <   �  $ ' ����  � '    !R  �          D '        D ' 
       D * 
       D *    ��  @ '        �   
       �          $   "   � $ L P�V4 � L    ��  � L    ��  �          D P        D P ,   k4 @ L    ��  @ L        $   3   x4 $ L ���4 � L    �4 � L    C( �          D Y   ��  �          D L    C( �   �       D Y�   k4 @ L    �4 @ L        $   �   ' $ �  ��% � �    N�  � �    #  �          D �        D �        D � 0   �% @ �    }�  @ �        �          �   0       $   7   ��  $ �`���  � �   t�  � �   y%  �          D �       D �       D �       D �       D �       D �&       D �0       D �P       D �_       D �i       D ��   �  @ �   ��  @ �   �  � �����10 � �����G0 � �����    �          �   �       $   �   �' $ �  ��% � �    N�  � �    Y�  � �    #  �   	       D � 	       D �        D � *   �% @ �    }�  @ �    ��  @ �        �          �   *       $   2   ��  $ � T���  � �    y%  �          D �        D �        D �        D �    �  @ �        �          �          $   !       d   \�	   d    ��4 d    �/   <       >   �       m   �       �   �       �   �       �   �       0  �       |  �       �  �       �  �         �       >  �       c  �       }  �       �  �       �  �       �  �         �       9  �       c  �       y  �       �  �       �  �       �  �       0  �   ?'  x  �   �a  �  �   0Q �  �   9�  �  �   �d 	  �       !  �       :  �       S  �       p  �   �    �       p  �   �  �  �   Co  p  �       �  �         �   Z �  �       p  �       p  �       �  �   =  �  �   9  A"  �       �"  �       �"  �   �#  #  �       ]#  �       p  �   	  �#  �       $  �       I$  �       ^$  �       t$  �       �$  �       �$  �       p  �       �$  �       /%  �       y%  �   �� �%  �   �  p  �       �%  �   �  p  �       �&  �   O�  p  �       �(  �   �  �*  �   �  p  �       $,  �   0M  >,  �       Y,  �   J<  �*  �   �*  s.  �   2)  �0  �       1  �   �  .1  �   1  �<  �       p  �       @=  �       V=  �   �O  m=  �       �*  �       .1  �   �f  �*  �   �  p  �       s.  �       �A  �       Y,  �       1  �       �A  �       �B  �       gL  �       �L  �       p  �       �L  �   �S !R  �       �R  �       S  �       eS  �       �S  �   �{ �q  �       -r  �       �q  �       dr  �       zr  �       �r  �       �r  �       �r  �       p  �       �r  �       #s  �       ps  �       �s  �       t  �   F] �}  �       �}  �   +P  �}  �       ~  �       4~  �       4~  �       4~  �       �4 �           �       .5 �           �       ��  �       �  �   �^ �  �   � q5 $   ��5 �     �5 �         D         D         D         D         D  T       D  �       D  �       D  �       D   �       D ! �       D # �   �5 �  �����5 �  �����5 �  ����    �          �   �       $   �   �5 $ % ���5 � %        D %        D %        D &        D '        D ) #       D * 6       D , F       �          �   F       $   H   6 $ . <�6 � .    �5 � .        D .        D .        D /        D 1    '6 � / ����    �          �          $      86 $ 4 P�Q6 � 4    � � 4    `6 � 4    � � 4     p6 � 4 (       D 4        D 4        D 5        D 6        D 7        D 9 E       D : J   �6 � 5 �����6 � 6 �����6 � 7 ����    �          �   J       $   R   �6 $ < ���6 � <        D <        D <        D =        D >        D ? *       D @ b   � � = ����� � > ����    �          �   b       $   d   �6 $ B ��6 � B        D B        D B        D D        D E        D F        D G &       D J E       D K J   �6 � D ����7 � E �����$ � F ����    �          �   J       $   L   7 $ M T��6 � M    17 � M        D M        D M        D P        D Q        D T $       D V ,   �$ � O ����    �          �   ,       $   .   C7 $ X ��g7 � X        D X        D X        D Z        D [        D \        D ] #       D ^ ,       D _ B       D ` X       D a n       D d �       D e 3  � � Z ����x7 � [ �����7 � \ �����7 � ] ����    �          �   �       �   �       �   �       $   :  ��  $ ����7 � �   �7 � �   �7 � �   �7 � �   S  �          D �       D �       D �       D �       D �$       D �(       D �4       D �@       D �X       �          �   X       $   Z   ;�  $ � ��7 � �   �7 � �   �7 � �   �7 � �       D �       D �       D �       D �       D �$       D �0       D �<       D �C       D �F       D �P       D �X       D �p       D �w       �          �   w       $   y   �  & $ P     d   ��	   d   ���7 d   ��/   <       >   �       m   �       �   �       �   �       �   �       0  �       |  �       �  �       �  �         �       >  �       c  �       }  �       �  �       �  �       �  �         �       9  �       c  �       y  �       �  �       �  �       �  �       0  �   ?'  x  �   �a  �  �   0Q �  �   9�  �  �   �d 	  �       !  �       :  �       S  �       p  �   �    �       p  �   �  �  �   Co  p  �       �  �         �   Z �  �       p  �       p  �       �  �   =  �  �   9  A"  �       �"  �       �"  �   �#  #  �       ]#  �       p  �   	  �#  �       $  �       I$  �       ^$  �       t$  �       �$  �       �$  �       p  �       �$  �       /%  �       y%  �   �� �%  �   �  p  �       �%  �   �  p  �       �&  �   O�  p  �       �(  �   �  �*  �   �  p  �       $,  �   0M  >,  �       Y,  �   J<  �*  �   �*  s.  �   2)  �0  �       1  �   �  .1  �   1  �<  �       p  �       @=  �       V=  �   �O  m=  �       �*  �       .1  �   �f  �*  �   �  p  �       s.  �       �A  �       Y,  �       1  �       �A  �       �B  �       gL  �       �L  �       p  �       �L  �   �S !R  �       �R  �       S  �       eS  �       �S  �   �{ �q  �       -r  �       �q  �       dr  �       zr  �       �r  �       �r  �       �r  �       p  �       �r  �       #s  �       ps  �       �s  �       t  �   F] �  �   �^ �  �   � |�  �   � ��  �   �y ��  �   �  ��  �       ��  � �    {�  � R    �7 $  ��8 �         D         D         D  �       D    8 @         �   �       �   �       $     +8 $  ��8 �     \�  �     �8 �         D  	       D         D ! �       D ! '  8 @     �8 @         �   �       �   �       �   �       �   �       $   a  �8 $ $ D�8 � $        D $        D $ 
       D ( 
       D )   8 @ $        �   
       �         $     �8 $ + `�8 � +        D +        D + 
       D , 
       D - T       D . c   8 @ +        �   
       �   c       $   h   �8 $ 0 ��8 � 0        D 0        D 0        D 1        D 2    8 @ 0        �          �          $   *   
9 $ 4 ��8 � 4        D 4        D 4        D 5        D 6    8 @ 4         �          �          $      (9 $ 8 �8 � 8        D 8        D 8        D 9        D :    8 @ 8         �          �          $      O9 $ < �8 � <        D <        D <        D =        D >    8 @ <         �          �          $      {9 $ @ $�8 � @        D @        D @        D A        D B    8 @ @         �          �          $      �9 $ D 4�8 � D        D D        D D 
       D F 
       D G        D H "       D J 4       D K :       D L T       D M �       D N �   8 @ D    �9 � F ����x7 � G �����9 � H ����� � J �����9 � K �����6 � L ����    �   
       �   �       $   �   �9 $ P ��8 � P    �  � P        D P        D P 
       D T 
       D U        D V .       D X g       D Y l   8 @ P    � � T ����� � U �����6 � V ����    �   
       �   l       $   q   : $ [ D�8 � [        D [        D [        D \        D ]    8 @ [         �          �          $      5: $ _ T�8 � _        D _        D _        D `        D a    8 @ _         �          �          $      R: $ c d�8 � c    c � c        D c        D c        D d        D e    8 @ c         �          �          $      q: $ g t�8 � g    U � g        D g        D g        D h        D i    8 @ g         �          �          $      �: $ k ��8 � k    � � k        D k        D k        D l        D m    8 @ k         �          �          $      �: $ o ��8 � o    �: � o        D o        D o        D p        D q    8 @ o         �          �          $      �: $ s ��8 � s    ; � s        D s        D s        D t        D u    8 @ s         �          �          $      ; $ w ��8 � w    <; � w        D w        D w        D x        D y    8 @ w         �          �          $      K; $ { ��8 � {    �# � {        D {        D {        D }        D �    8 @ {         �          �          $      m; $ � ��8 � �    �# � �        D �        D �        D �        D �    8 @ �         �          �          $      �; $ � ��8 � �    �# � �        D �        D �        D �        D �    8 @ �         �          �          $      �; $ �  �8 � �    �; � �        D �        D �        D �        D �    8 @ �         �          �          $      �; $ � �8 � �    �# � �        D �        D �        D �        D �    8 @ �         �          �          $      < $ � (�8 � �    �# � �        D �        D �        D �        D �    8 @ �         �          �          $      :< $ � <�8 � �    �  � �        D �        D � 
       D � 
       D �        D � 2   8 @ �        �   
       �   2       $   7   c< $ � t�8 � �        D �        D � 
       D � 
       D �    8 @ �        �   
       �          $      �< $ � ��8 � �        D �        D � 
       D � 
       D �    8 @ �        �   
       �          $   #   �< $ � ��8 � �        D �        D � 
       D � 
       D �        D � 3       D � E       D � W       D � c       D � l       D � r       D � �       D � �       D � �       D � �   8 @ �    �< � � �����< � � �����$ � � �����< � � �����< � � �����. � � �����< � � ������  � � ����    �   
       �   �       $   �   = $ � l�8 � �    �  � �        D � 
       D �        D �        D �        D � 1       D � C       D � U       D � i       D � o       D � u       D � �       D � �       D � �       D � �       D � 
      D �       D � '      D � ,  8 @ �    � � � ����� � � �����9 � � �����9 � � ����== � � ����M= � � ����Y= � � ����f= � � ����y= � � �����$ � � �����< � � �����. � � �����= � � ����    �          �   ,      $   4  �= $ � � 8 � �    �  � �        D � 
       D �        D �        D �        D � 1       D � C       D � U       D � i       D � o       D � u       D � �       D � �       D � �       D � �       D �        D �       D �       D � "  8 @ �    � � � ����� � � �����9 � � �����9 � � ����== � � ����M= � � ����Y= � � ����f= � � ����y= � � �����$ � � �����< � � �����. � � �����= � � ����    �          �   "      $   *  �= $ � �8 � �    �= � �        D �        D � 
       D � 
       D � #       D � I       D � \       D � o       D � �       D � �       D �       D �       D �       D       D Y      D i      D 	y      D �      D �      D �      D �  8 @ �        �   
       �   
   
> � � ����> � � ����%> � � ����    �   #       �   �      �   �      �   �      $   �  0> $ x8 �    _- �    �- �        D        D 
       D 
       D "       D :   8 @        �   
       �   :       $   ?   U> $ �8 �    �  �        D        D 
       D 
       D        D 2       D E   8 @        �   
       �   E       $   J   �> $  8 �         D         D  
       D !
       D (       D )4       D +Q       D ,i       D 1�   8 @     �$ � !����    �   
       �   �       $   �   �> $ 3�8 � 3       D 3       D 3       D 4       D 5       D 6       D 7A       D =T       D Da   �> � 4�����5 � 5����    �          �   a       $   c   ��  $ ����> � �   �> � �   �> � �   ? � �   S  �          D �       D �       D �       D �       D �$       D �(       D �4       D �@       D �X       �          �   X       $   Z   ;�  $ � �? � �   �> � �   �> � �   ? � �       D �       D �       D �       D �       D �$       D �0       D �<       D �C       D �F       D �P       D �X       D �p       D �w       �          �   w       $   y   �
       g�  $ 0 ����  � 0    !R  �          D 0        D 0 	       D 1 	       D 2        D 3 $       D 3 +   ��  @ 0    ��  � 1 ����    �   	       �   +       $   -   ��    �     (? $  ��R? �     y%  �          D �    �%  �   
       D  
   y%  �   U       D � U   _? @         $   Z   l? $  � �     �? �         D �    �%  �   	       D  	   y%  �          D �    
 @     *�  @         $      �? $  0�R? �     �? �         D �    �%  �          D     y%  �   U       D � U   _? @     �? @         $   \   <�  $ � ��t�  � �        D �        D �        D �        D �        D �        D � �       D � �       D � �       D �    ��  � � ������  � � ����    �          �   �       $     ��  $ � ��t�  � �        D �        D � 
       D � 
       D �        D � 4       D � ;   ��  @ �    ��  � � ����    �   
       �   ;       $   @   ��    �    ��  $ L�#�  � L       D L       D L       D L   3�  @ L       �          �          $      C�    �    {�    �    ��    �    ��  $ � �%�  � �   	@ � �       D �       D �       D �       D �       D �%       D �-       D �5       D �>       D �P       D �X       D �o       D �{       D ��       D ��       D ��       D ��       D ��       D ��       D ��       D ��       D �      D �      D �'      D �@      D �c      D �k      D �q      D �{      D ��      D ��      D ��      D ��      D �      D �      D �      D   K�  � �����[�  � �����p�  � �����    �          �   %       �   P       �   P   ��  � �����    �   �       �   �    @ � �����    �   �       �         �         �     ��  � �����?@ � �������  � �����    �   '      �   �      �   �      �         �         �         �         �         $     ��  $  �t�  �        D        D        D        D        D %       D 2       D U       D [       D  m       D !t       D "z       D #�       D $�       D %�       D '�       D *�       D *�   �  � ����+�  � ����?@ � ����:�  � ����K�  � ����a�  � ����t�  � ����    �          �   �       $   �   ~�  $ ��t�  � �       D �       D �       D �       D �       D �(       D �H       D �W       D �_       D �e       D ��       D ��       D ��       D �  ��  @ �   ?@ � �����:�  � �������  � �����    �          �   _   ��  � �����    �   e       �   �       �   �       �   �       �   �       �   �       �   �       �   �       $     ��  $   ���  �      >�  �      !R  �          D          D          D !        D ! #   ��  @      L�  @          �          �   #       $   *   
 $ : �>�  � :        D :        D : 
       D ; 
       D <        D = .       D > 4       D ? >       D @ E       D @ L   L�  @ :    u
 � < ����    �   
       �   L       $   Q   ��  $ � p�~
 � �    B�  � �    N�  � �    Y�  � �        D � 	       D �        D �        D �        D � :   �
 @ �    q�  @ �    }�  @ �        �          �   :       $   B   ��  $ F ��~
 � F        D F        D F 
       D G 
       D H        D I =       D J D       D J Y   �
 @ F    u
 � G ����    �   
       �   Y       $   ^   ��  $ � �U@ � �    #  �          D �        D � 
       D �    j@ @ �        �   
       �          $   #   k�  $ � 8�w@ � �        D �        D �        D �    j@ @ �        �          �          $      ��  $ � H�w@ � �        D �        D � 
       D �    j@ @ �        �   
       �          $   $   8�  $ P l���  � P    ��  � P    !R  �          D P        D P 
       D Q 
       D Q "   ��  @ P    ��  @ P        �   
       �   "       $   '   ��  $ W ��w@ � W    ��  � W        D W 	       D W        D X        D Y        D \ $       D \ z   j@ @ W    ��  @ W        �          �   z       $   �    �  $ � 0�w@ � �    #  �          D �        D � 
       D � *   j@ @ �        �   
       �   *       $   /   }�  $ � `�$ � �    2 � �        D �        D �        D � 8   < @ �    J @ �        �          �   8       $   ?   a�  $ � ��~
 � �    B�  � �    N�  � �    Y�  � �    !R  �   	       D � 	       D �        D �        D �        D � :   �
 @ �    q�  @ �    }�  @ �        �          �   :       $   B   T $ � �$ � �    B�  � �    3�  � �    N�  � �    >�  � �        D � 	       D �        D �        D �        D � B       D � O       D � ]       D � �       D � �       D � �       D � �       D � �       D � �       D � ;      D � S      D � e      D � �      D � �      D � �      D � �  < @ �    I�  � � ����T�  � � ����    �          �   �   u
 � � ����    �   �       �   c      �   �      �   �      $   �  ��    E    � $ �0�; � �   �@ � �       D �       D �       D �       D �?       �          �   ?       $   B   ��  $ I 0�~
 � I    #  �          D I        D I        D I    �
 @ I        �          �          $       $ � @�$ � �    N�  � �        D �        D �        D � 1   < @ �    }�  @ �        �           �   -       $   8    $ �  �w@ � �        D �        D �        D �    j@ @ �        �          �          $      �  $ Z4�#�  � Z   y%  �          D Z       D Z       D [       D [   3�  @ Z       �          �          $      K�  $ �P���  � �   ��  � �       D �       D �       D �5   ��  @ �   ��  @ �       �          �          $   <   ��  $ �����  � �       D �       D �       D �       �          �          $      ��  $ m ��~
 � m    #  �          D m        D m 
       D m    �
 @ m        �   
       �          $   $   3�  $ � �$ � �    ��  � �        D �        D �        D � @   < @ �    ��  @ �        �          �   (       $   G   n $ � x�$ � �    �@ � �        D �        D �        D � .   < @ �    �@ @ �        �   *       �   *       $   5   �  & $ 8!$�    �     ��  $ K �~
 � K        D K        D K 
       D K 7   �
 @ K        �   
       �   7       $   <   E $ �  �$ � �    N�  � �        D �        D �        D � 0   < @ �    }�  @ �        �          �   0       $   7   �  $ ' ����  � '    !R  �          D '        D ' 
       D * 
       D *    ��  @ '        �   
       �          $   "   � $ �  �$ � �    N�  � �    Y�  � �    #  �   	       D � 	       D �        D � *   < @ �    }�  @ �    ��  @ �        �          �   *       $   2   ��  $ �`���  � �   t�  � �   y%  �          D �       D �       D �       D �       D �       D �&       D �0       D �P       D �_       D �i       D ��   �  @ �   ��  @ �   �  � �����?@ � �������  � �����    �          �   �       $   �   ��  $ � T���  � �        D �        D �        D �        D �    �  @ �        �          �          $   !       d   �	   d   ��@ d   �/   <       >   �       m   �       �   �       �   �       �   �       0  �       |  �       �  �       �  �         �       >  �       c  �       }  �       �  �       �  �       �  �         �       9  �       c  �       y  �       �  �       �  �       �  �       0  �   ?'  x  �   �a  �  �   0Q �  �   9�  �  �   �d 	  �       !  �       :  �       S  �       p  �   �    �       p  �   �  �  �   Co  p  �       �  �         �   Z �  �       p  �       p  �       �  �   =  �  �   9  A"  �       �"  �       �"  �   �#  #  �       ]#  �       p  �   	  �#  �       $  �       I$  �       ^$  �       t$  �       �$  �       �$  �       p  �       �$  �       /%  �       y%  �   �� �%  �   �  p  �       �%  �   �  p  �       �&  �   O�  p  �       �(  �   �  �*  �   �  p  �       $,  �   0M  >,  �       Y,  �   J<  �*  �   �*  s.  �   2)  �0  �       1  �   �  .1  �   1  �<  �       p  �       @=  �       V=  �   �O  m=  �       �*  �       .1  �   �f  �*  �   �  p  �       s.  �       �A  �       Y,  �       1  �       �A  �       �B  �       gL  �       �L  �       p  �       �L  �   �S !R  �       �R  �       S  �       eS  �       �S  �   �{ �q  �       -r  �       �q  �       dr  �       zr  �       �r  �       �r  �       �r  �       p  �       �r  �       #s  �       ps  �       �s  �       t  �   F] ��  �   @ �@ � �    �p � ~     �x � �    �z � R        �       �  �   q^ �  �   ��  	| � 4         �       � � N         �       ��  �       m�  �   |� |�  �   �� ��  �   �y ��  �   �  ۄ � O         �       ��  �   �R  ��  �   Fj  � $  �� �         D         D  
       D  )       D  e   )� @         �   )       �   )       $   j   6� $  \� �     \�  �         D  	       D         D  *       D  f   )� @     i�  @         �   *       �   *       �   4       �   4       $   �   �� $  �� �         D         D  
       D  
       D  k       D  �   )� @         �   
       �   �       $   �   �� $ ! �� � !    � � !        D !        D !        D #        D *        D , �   )� @ !    �� � " ����    �          �   d       $   �   � $ . X� � .        D .        D . 
       D 0 
       D 1        D 2        D 3 0       D 4 B       D 7 L       D 8 a   )� @ .        �   
       �          �      �� � 2 ����    �          �   L       �   L       �   L       �   a       $   f   $� $ : �� � :    � � :        D :        D :        D ;        D < @   )� @ :    �� @ :        �          �   >       $   w   �� $ > 8� � >        D >        D > 
       D @ 
       D B        D C !       D E 8       D F @       D G H       D H O   )� @ >    + � @ ������ � B ����    �   
   ��  � C ����    �   !       �   H       �   O       $   T   ݍ $ K �� � K    \�  � K        D K 	       D K        D N        D O        D P ,       D Q p       D S �       D T �       D W X      D Y �  )� @ K    # @ K    �� � L ����    �          �          �          �          �   ,       �   ,       �   p       �   �       �   �       �   �       �   �       �   �       �   �       �   S      �         �         $   �  O� $ [ |� � [        D [        D [ 
       D ] 
       D _        D ` ,       D a Q       D b [       D c `   )� @ [    �� � \ �����) � ] ����    �   
       �   `       $   e   w� $ e �� � e        D e        D e 
       D g 
       D i        D j ,       D k Q       D l \       D m a   )� @ e    �� � f �����) � g ����    �   
       �   a       $   f   �� $ p L� � p    \�  � p    � � p        D p        D p        D q        D r D   )� @ p    )� @ p        �          �   B       $   {   >� $ t �� � t        D t        D t 
       D u 
       D v        D z        D } 8       D ~ g       D  x   )� @ t    o� � u ������ � v ������ � x ����    �   
       �   x       $   }   �� $ � H� � �    _  � �        D �        D �        D �        D � >       D � P       D � m       D � z       D � z       D � �       D � �       D �       D � �  )� @ �    � @ �    %� � � ����    �          �          �   z       �   �   /� � � ����    �   �       �   �       �   N      �   g      �   l      �   �       �   �       �   �       $     ]� $ � L� � �        D �        D � 
       D � 
       D �        D � 9       D � D   )� @ �    �� � � ����    �   
       �   D       $   I   }� $ � �� � �        D �        D � 
       D � 
       D �        D � 5       D � ?   )� @ �    �� � � ����    �   
       �   ?       $   D   �� $ � �� � �        D �        D � 
       D � 
       D �        D � 9       D � D   )� @ �    �� � � ����    �   
       �   D       $   I   ʐ $ � (� � �    J� � �    \�  � �        D � 	       D �        D �        D � &       D � >       D � >       D � z   )� @ �    V� @ �        �          �          �   &       �   8       �   8       �   <       �   >       �   t       �   t       �   x       �   x       �   x       $   �   k� $ � �� � �    J� � �        D �        D � 
       D � 
       D �        D � D       D � k       D � u   )� @ �    �� � � ����    �   
       �   u       $   z   �� $ � X� � �    J� � �        D �        D � 
       D � 
       D �        D � !       D � %       D � )       D � 8       D � ^       D � d       D � k       D � x       D � �       D � �       D � �       D � �       D � �       D � �   )� @ �    �� � � ����ґ � � ����%� � � ����ܑ � � ����� � � ����    �   
       �   x   � � � ����    �   �       �   �       �   �       �   �       $   �   �� $ � ,� � �        D �        D � 
       D � 
       D �        D � 9       D � D   )� @ �    �� � � ����    �   
       �   D       $   I   ��  $ ���� � �   /� � �   ?� � �   P� � �   S  �          D �       D �       D �       D �       D �$       D �(       D �4       D �@       D �X       �          �   X       $   Z   ;�  $ � �`� � �   /� � �   ?� � �   P� � �       D �       D �       D �       D �       D �$       D �0       D �<       D �C       D �F       D �P       D �X       D �p       D �w       �          �   w       $   y   g�  $ 0 ����  � 0    !R  �          D 0        D 0 	       D 1 	       D 2        D 3 $       D 3 +   ��  @ 0    ��  � 1 ����    �   	       �   +       $   -   ��    �     q� $  ���� �     y%  �          D �    �%  �   
       D  
   y%  �   U       D � U   �� @         $   Z   �� $  0��� �     ֒ �         D �    �%  �          D     y%  �   U       D � U   �� @     �0 @         $   \   <�  $ � ��t�  � �        D �        D �        D �        D �        D �        D � �       D � �       D � �       D �    ��  � � ������  � � ����    �          �   �       $     ��  $ � ��t�  � �        D �        D � 
       D � 
       D �        D � 4       D � ;   ��  @ �    ��  � � ����    �   
       �   ;       $   @   ��    �    ��  $ L�#�  � L       D L       D L       D L   3�  @ L       �          �          $      C�    �    {�    �    ��    �    ��  $ � �%�  � �   � � �       D �       D �       D �       D �       D �%       D �-       D �5       D �>       D �P       D �X       D �o       D �{       D ��       D ��       D ��       D ��       D ��       D ��       D ��       D ��       D �      D �      D �'      D �@      D �c      D �k      D �q      D �{      D ��      D ��      D ��      D ��      D �      D �      D �      D   K�  � �����[�  � �����p�  � �����    �          �   %       �   P       �   P   ��  � �����    �   �       �   �   � � �����    �   �       �         �         �     ��  � �����&� � �������  � �����    �   '      �   �      �   �      �         �         �         �         �         $     ��  $  �t�  �        D        D        D        D        D %       D 2       D U       D [       D  m       D !t       D "z       D #�       D $�       D %�       D '�       D *�       D *�   �  � ����+�  � ����&� � ����:�  � ����K�  � ����a�  � ����t�  � ����    �          �   �       $   �   ~�  $ ��t�  � �       D �       D �       D �       D �       D �(       D �H       D �W       D �_       D �e       D ��       D ��       D ��       D �  ��  @ �   &� � �����:�  � �����<� � �����    �          �   _   ��  � �����    �   e       �   �       �   �       �   �       �   �       �   �       �   �       �   �       $     ��  $   ���  �      >�  �      !R  �          D          D          D !        D ! #   ��  @      L�  @          �          �   #       $   *   T� $ : �>�  � :        D :        D : 
       D ; 
       D <        D = .       D > 4       D ? >       D @ E       D @ L   L�  @ :    �� � < ����    �   
       �   L       $   Q   ��  $ � p�Ó � �    B�  � �    N�  � �    Y�  � �        D � 	       D �        D �        D �        D � :   Г @ �    q�  @ �    }�  @ �        �          �   :       $   B   ��  $ F ��Ó � F        D F        D F 
       D G 
       D H        D I =       D J D       D J Y   Г @ F    �� � G ����    �   
       �   Y       $   ^   ��    E    ݓ       k�  $ � 8�:� � �    #  �          D �        D �        D �    ��  @ �        �          �          $      ��  $ � H���  � �        D �        D � 
       D �    ��  @ �        �   
       �          $   $   8�  $ P l���  � P    ��  � P    !R  �          D P        D P 
       D Q 
       D Q "   ��  @ P    ��  @ P        �   
       �   "       $   '   ��  $ W ����  � W    ��  � W        D W 	       D W        D X        D Y        D \ $       D \ z   ��  @ W    ��  @ W        �          �   z       $   �   }�  $ � `�O� � �    ]� � �    #  �          D �        D �        D � 8   g� @ �    u� @ �        �          �   8       $   ?   a�  $ � ��Ó � �    B�  � �    N�  � �    Y�  � �    !R  �   	       D � 	       D �        D �        D �        D � :   Г @ �    q�  @ �    }�  @ �        �          �   :       $   B   � $ � �O� � �    B�  � �    3�  � �    N�  � �    >�  � �        D � 	       D �        D �        D �        D � B       D � O       D � ]       D � �       D � �       D � �       D � �       D � �       D � �       D � ;      D � S      D � e      D � �      D � �      D � �      D � �  g� @ �    I�  � � ����T�  � � ����    �          �   �   �� � � ����    �   �       �   c      �   �      �   �      $   �  � $ ����  � �   �� � �   B�  � �   Y�  � �       D �       D �       D �       D �7       D �M       D �U       D �[       D �q       D ��       D ��       D ��       D ��       D ��       D ��       D �
  ��  @ �   �� � ������� � �����    �          �   
      $     �� $ ����  � �   N�  � �   B�  � �   Y�  � �       D �       D �
       D �
       D �7       D �M       D �U       D �[       D ��       D ��       D ��       D ��   ��  @ �   �� � ������� � �����    �   
       �   �       $   �   $�   �    V� $  ��#  �          D �       D �7       $   9   �� $  ��� �     �� �     �@ �          D T    �%  �   	       D  	   �@ �          D T    ۖ @     � @         $      �� $ �  ���  � �    #  �          D �        D �        D �    ��  @ �        �          �          $      ��  $ I 0�Ó � I        D I        D I        D I    Г @ I        �          �          $      U� $ � x�O� � �    �� � �        D �        D �        D � .   g� @ �    � @ �        �   *       �   *       $   5   �  $ Z4�#�  � Z   y%  �          D Z       D Z       D [       D [   3�  @ Z       �          �          $      K�  $ �P�� � �   ��  � �       D �       D �       D �5   #� @ �   ��  @ �       �          �          $   <   1� $ ���� � �       D �       D �       D �       �          �          $      ��  $ m ��Ó � m    #  �          D m        D m 
       D m    Г @ m        �   
       �          $   $   3�  $ � �O� � �    ��  � �        D �        D �        D � @   g� @ �    ��  @ �        �          �   (       $   G   ��  $ � ���  � �        D �        D � 
       D �    ��  @ �        �   
       �          $   #    �  $ � 0���  � �        D �        D � 
       D � *   ��  @ �        �   
       �   *       $   /    $  ��� �     ��  �     �@ �          D T        D T    � @     ��  @         $   "   � $  ��� �     f� �         D T    ��  �          D     �@ �   U       D T U   � @      @         $   \   �� $  `�� �     � �     ��  �          D         D         D  U   � @     � @         �   !       �   !       $   \   � $ � @�O� � �    N�  � �    #  �          D �        D �        D � 1   g� @ �    }�  @ �        �           �   -       $   8   q� $ `� �    � �        D        D        D        D '   �� @    � @        �          �   '       $   .   � $ �� �    �� �        D        D        D        D (   �� @    �� @        �          �   (       $   /   �  & $ l"$�    �     p        ��  $ K �Ó � K        D K        D K 
       D K 7   Г @ K        �   
       �   7       $   <   �  $ ' ����  � '    !R  �          D '        D ' 
       D * 
       D *    ��  @ '        �   
       �          $   "   � $ L P�� � L    ��  � L    ��  �          D P        D P ,   � @ L    ��  @ L        $   3   � $ L �� � L     � L    �@ �          D T    ��  �          D L    �@ �   �       D T �   � @ L    3 @ L        $   �   �� $ �  �O� � �    N�  � �    #  �          D �        D �        D � 0   g� @ �    }�  @ �        �          �   0       $   7   �� $ ����  � �   N�  � �   B�  � �       D �	       D �       D �2   ��  @ �   }�  @ �   q�  @ �       �          �   2       $   :   ��  $ �`���  � �   t�  � �   y%  �          D �       D �       D �       D �       D �       D �&       D �0       D �P       D �_       D �i       D ��   �  @ �   ��  @ �   �  � �����&� � �����<� � �����    �          �   �       $   �   a� $ �  �O� � �    N�  � �    Y�  � �    #  �   	       D � 	       D �        D � *   g� @ �    }�  @ �    ��  @ �        �          �   *       $   2   ��  $ � T���  � �    y%  �          D �        D �        D �        D �    �  @ �        �          �          $   !       d   u	   d   �Û d   �/   <       >   �       m   �       �   �       �   �       �   �       0  �       |  �       �  �       �  �         �       >  �       c  �       }  �       �  �       �  �       �  �         �       9  �       c  �       y  �       �  �       �  �       �  �       0  �   ?'  x  �   �a  �  �   0Q �  �   9�  �  �   �d 	  �       !  �       :  �       S  �       p  �   �    �       p  �   �  �  �   Co  p  �       �  �         �   Z �  �       p  �       p  �       �  �   =  �  �   9  A"  �       �"  �       �"  �   �#  #  �       ]#  �       p  �   	  �#  �       $  �       I$  �       ^$  �       t$  �       �$  �       �$  �       p  �       �$  �       /%  �       y%  �   �� �%  �   �  p  �       �%  �   �  p  �       �&  �   O�  p  �       �(  �   �  �*  �   �  p  �       $,  �   0M  >,  �       Y,  �   J<  �*  �   �*  s.  �   2)  �0  �       1  �   �  .1  �   1  �<  �       p  �       @=  �       V=  �   �O  m=  �       �*  �       .1  �   �f  �*  �   �  p  �       s.  �       �A  �       Y,  �       1  �       �A  �       �B  �       gL  �       �L  �       p  �       �L  �   �S !R  �       �  �   �^ �R  �       S  �       eS  �       �S  �   �{ �q  �       -r  �       �q  �       dr  �       zr  �       �r  �       �r  �       �r  �       p  �       �r  �       #s  �       ps  �       �s  �       t  �   F] �  �   � |�  �   � ��  �   �y ��  �   �  ��  �   �R  ֛ $  �� �         D         D         D         D     � @         �          �          $      � $  � �     G� �     R� �         D         D         D         D     � @         �          �          $      \� $  0� �         D         D         D         D      � @         �          �           $   +   �� $  \� �         D         D         D         D     � @         �          �          $      ��  $ ����� � �   �� � �   М � �   � � �   S  �          D �       D �       D �       D �       D �$       D �(       D �4       D �@       D �X       �          �   X       $   Z   ;�  $ � �� � �   �� � �   М � �   � � �       D �       D �       D �       D �       D �$       D �0       D �<       D �C       D �F       D �P       D �X       D �p       D �w       �          �   w       $   y   g�  $ 0 ����  � 0    !R  �          D 0        D 0 	       D 1 	       D 2        D 3 $       D 3 +   ��  @ 0    ��  � 1 ����    �   	       �   +       $   -   ��    �     � $  ��,� �     y%  �          D �    �%  �   
       D  
   y%  �   U       D � U   9� @         $   Z   F� $  ��/ �     �/ �         D �    �%  �   	       D  	   y%  �          D �    �/ @     �/ @         $      |� $  0�,� �     �� �         D �    �%  �          D     y%  �   U       D � U   9� @     �� @         $   \   <�  $ � ��t�  � �        D �        D �        D �        D �        D �        D � �       D � �       D � �       D �    ��  � � ������  � � ����    �          �   �       $     ��  $ � ��t�  � �        D �        D � 
       D � 
       D �        D � 4       D � ;   ��  @ �    ��  � � ����    �   
       �   ;       $   @   ��    �    �  $ Z4�#�  � Z       D Z       D Z       D [       D [   3�  @ Z       �          �          $      ɝ � �    ��    E    K�  $ �P�j� � �   ��  � �       D �       D �       D �5   w� @ �   ��  @ �       �          �          $   <   �� $ ���j� � �       D �       D �       D �       �          �          $      ��  $ L�#�  � L       D L       D L       D L   3�  @ L       �          �          $      C�    �    {�    �    ��    �    �� � R    ��  $ � �%�  � �   4�  � �       D �       D �       D �       D �       D �%       D �-       D �5       D �>       D �P       D �X       D �o       D �{       D ��       D ��       D ��       D ��       D ��       D ��       D ��       D ��       D �      D �      D �'      D �@      D �c      D �k      D �q      D �{      D ��      D ��      D ��      D ��      D �      D �      D �      D   K�  � �����[�  � �����p�  � �����    �          �   %       �   P       �   P   ��  � �����    �   �       �   �   ��  � �����    �   �       �         �         �     ��  � �������  � �������  � �����    �   '      �   �      �   �      �         �         �         �         �         $     ��  $  �t�  �        D        D        D        D        D %       D 2       D U       D [       D  m       D !t       D "z       D #�       D $�       D %�       D '�       D *�       D *�   �  � ����+�  � ������  � ����:�  � ����K�  � ����a�  � ����t�  � ����    �          �   �       $   �   ~�  $ ��t�  � �       D �       D �       D �       D �       D �(       D �H       D �W       D �_       D �e       D ��       D ��       D ��       D �  ��  @ �   ��  � �����:�  � �����,� � �����    �          �   _   ��  � �����    �   e       �   �       �   �       �   �       �   �       �   �       �   �       �   �       $     ��  $   ���  �      >�  �      !R  �          D          D          D !        D ! #   ��  @      L�  @          �          �   #       $   *   
 $ : �>�  � :        D :        D : 
       D ; 
       D <        D = .       D > 4       D ? >       D @ E       D @ L   L�  @ :    u
 � < ����    �   
       �   L       $   Q   ��  $ � p�~
 � �    B�  � �    N�  � �    Y�  � �        D � 	       D �        D �        D �        D � :   �
 @ �    q�  @ �    }�  @ �        �          �   :       $   B   ��  $ F ��~
 � F        D F        D F 
       D G 
       D H        D I =       D J D       D J Y   �
 @ F    u
 � G ����    �   
       �   Y       $   ^   ��  $ I 0�~
 � I    #  �          D I        D I        D I    �
 @ I        �          �          $      �  & $ �"    d   k	   d   lC� d   l/   <       >   �       m   �       �   �       �   �       �   �       0  �       |  �       �  �       �  �         �       >  �       c  �       }  �       �  �       �  �       �  �         �       9  �       c  �       y  �       �  �       �  �       �  �       0  �   ?'  x  �   �a  �  �   0Q �  �   9�  �  �   �d 	  �       !  �       :  �       S  �       p  �   �    �       p  �   �  �  �   Co  p  �       �  �         �   Z �  �       p  �       p  �       �  �   =  �  �   9  A"  �       �"  �       �"  �   �#  #  �       ]#  �       p  �   	  �#  �       $  �       I$  �       ^$  �       t$  �       �$  �       �$  �       p  �       �$  �       /%  �       y%  �   �� �%  �   �  p  �       �%  �   �  p  �       �&  �   O�  p  �       �(  �   �  �*  �   �  p  �       $,  �   0M  >,  �       Y,  �   J<  �*  �   �*  s.  �   2)  �0  �       1  �   �  .1  �   1  �<  �       p  �       @=  �       V=  �   �O  m=  �       �*  �       .1  �   �f  �*  �   �  p  �       s.  �       �A  �       Y,  �       1  �       �A  �       �B  �       gL  �       �L  �       p  �       �L  �   �S !R  �       �  �   �^ �R  �       S  �       eS  �       �S  �   �{ �q  �       -r  �       �q  �       dr  �       zr  �       �r  �       �r  �       �r  �       p  �       �r  �       #s  �       ps  �       �s  �       t  �   F] �  �   � |�  �   � ��  �   �y ��  �   �  W� $  lt� �         D         D         D         D     �� @         �          �          $      �� $  �t� �     ȡ �     ҡ �         D         D         D         D     �� @         �          �          $      ܡ $  �t� �         D         D         D         D     �� @         �          �          $      � $  �t� �         D         D  
       D  
       D     �� @         �   
       �          $       0� $  �t� �         D         D  
       D  
       D     �� @         �   
       �          $       V� $ ! �t� � !        D !        D ! 
       D " 
       D #    �� @ !        �   
       �          $       ~� $ % t� � %        D %        D % 
       D & 
       D '    �� @ %        �   
       �          $       �� $ ) 0t� � )        D )        D ) 
       D * 
       D +    �� @ )        �   
       �          $       Ϣ $ - Pt� � -        D -        D - 
       D . 
       D /    �� @ -        �   
       �          $   $   � $ 0 tt� � 0    c" � 0        D 0        D 0 
       D 1 
       D 2 !   �� @ 0        �   
       �   !       $   &   ��  $ ����� � �   �� � �   М � �   � � �   S  �          D �       D �       D �       D �       D �$       D �(       D �4       D �@       D �X       �          �   X       $   Z   ;�  $ � �� � �   �� � �   М � �   � � �       D �       D �       D �       D �       D �$       D �0       D �<       D �C       D �F       D �P       D �X       D �p       D �w       �          �   w       $   y   �  & $ �"    d   �	   d   �4� d   �/   <       >   �       m   �       �   �       �   �       �   �       0  �       |  �       �  �       �  �         �       >  �       c  �       }  �       �  �       �  �       �  �         �       9  �       c  �       y  �       �  �       �  �       �  �       0  �   ?'  x  �   �a  �  �   0Q �  �   9�  �  �   �d 	  �       !  �       :  �       S  �       p  �   �    �       p  �   �  �  �   Co  p  �       �  �         �   Z �  �       p  �       p  �       �  �   =  �  �   9  A"  �       �"  �       �"  �   �#  #  �       ]#  �       p  �   	  �#  �       $  �       I$  �       ^$  �       t$  �       �$  �       �$  �       p  �       �$  �       /%  �       y%  �   �� �%  �   �  p  �       �%  �   �  p  �       �&  �   O�  p  �       �(  �   �  �*  �   �  p  �       $,  �   0M  >,  �       Y,  �   J<  �*  �   �*  s.  �   2)  �0  �       1  �   �  .1  �   1  �<  �       p  �       @=  �       V=  �   �O  m=  �       �*  �       .1  �   �f  �*  �   �  p  �       s.  �       �A  �       Y,  �       1  �       �A  �       �B  �       gL  �       �L  �       p  �       �L  �   �S !R  �       �  �   � �R  �       S  �       eS  �       �S  �   �{ �q  �       -r  �       �q  �       dr  �       zr  �       �r  �       �r  �       �r  �       p  �       �r  �       #s  �       ps  �       �s  �       t  �   F] ��  � �    {�  � R    >� $  �Q� �         D         D  
       D  H       D  �   _� @         �   H       �   H       $   �   m� $  ,Q� �         D         D  
       D  
       D  [  _� @         �   
       �   [      $   `  �� $  �Q� �         D         D         D         D     _� @          �          �          $      �� $  �Q� �         D         D         D         D      _� @          �          �          $      �� $ # �Q� � #        D #        D #        D $        D %    _� @ #         �          �          $      ٣ $ ' �Q� � '        D '        D ' 	       D ( 	       D )    _� @ '         �   	       �          $      �� $ + �Q� � +        D +        D + 	       D , 	       D -    _� @ +         �   	       �          $      � $ / �Q� � /    �" � /        D /        D /        D 0        D 1    _� @ /         �          �          $      2� $ 3 �Q� � 3    Q� � 3        D 3        D 3        D 4        D 5    _� @ 3         �          �          $      b� $ 8 �Q� � 8    c � 8        D 8        D 8        D 9        D :    _� @ 8         �          �          $      �� $ < Q� � <    �� � <        D <        D <        D =        D >        D A $       D C 2       �          �   2       $   4   �� $ E @Q� � E    �� � E        D E        D E        D F        D G        D J #       D L 1       �          �   1       $   3   ͤ $ N tQ� � N    �# � N        D N        D N        D P        D Q        D W    _� @ N        �          �          $      � $ Y �Q� � Y    �# � Y        D Y        D Y        D Z        D [    _� @ Y         �          �          $      � $ ] �Q� � ]    �# � ]        D ]        D ]        D _        D a        D g    _� @ ]        �          �          $      /� $ i �Q� � i    �# � i        D i        D i 
       D j 
       D k        D l ;   _� @ i        �   
       �   ;       $   @   Q� $ n �Q� � n    �# � n        D n        D n 
       D o 
       D p        D r ;   _� @ n        �   
       �   ;       $   @   t� $ t 8Q� � t    �" � t        D t        D t        D v    _� @ t         �          �          $      ��  $ �����  � �   
�  � �   �  � �   +�  � �   S  �          D �       D �       D �       D �       D �$       D �(       D �4       D �@       D �X       �          �   X       $   Z   ;�  $ � �~�  � �   
�  � �   �  � �   +�  � �       D �       D �       D �       D �       D �$       D �0       D �<       D �C       D �F       D �P       D �X       D �p       D �w       �          �   w       $   y   ��       g�  $ 0 ����  � 0    !R  �          D 0        D 0 	       D 1 	       D 2        D 3 $       D 3 +   ��  @ 0    ��  � 1 ����    �   	       �   +       $   -   ��    �     /�  $  ��Y�  �     y%  �          D �    �%  �   
       D  
   y%  �   U       D � U   f�  @         $   Z   s�  $  ���  �     ��  �         D �    �%  �   	       D  	   y%  �          D �    ��  @     ��  @         $      ��  $  0�Y�  �     �  �         D �    �%  �          D     y%  �   U       D � U   f�  @     *�  @         $   \   <�  $ � ��t�  � �        D �        D �        D �        D �        D �        D � �       D � �       D � �       D �    ��  � � ������  � � ����    �          �   �       $     ��  $ � ��t�  � �        D �        D � 
       D � 
       D �        D � 4       D � ;   ��  @ �    ��  � � ����    �   
       �   ;       $   @   ��    �    ��  $ L�#�  � L       D L       D L       D L   3�  @ L       �          �          $      C�    �    {�    �    ��    �    ��  $ � �%�  � �   4�  � �       D �       D �       D �       D �       D �%       D �-       D �5       D �>       D �P       D �X       D �o       D �{       D ��       D ��       D ��       D ��       D ��       D ��       D ��       D ��       D �      D �      D �'      D �@      D �c      D �k      D �q      D �{      D ��      D ��      D ��      D ��      D �      D �      D �      D   K�  � �����[�  � �����p�  � �����    �          �   %       �   P       �   P   ��  � �����    �   �       �   �   ��  � �����    �   �       �         �         �     ��  � �������  � �������  � �����    �   '      �   �      �   �      �         �         �         �         �         $     ��  $  �t�  �        D        D        D        D        D %       D 2       D U       D [       D  m       D !t       D "z       D #�       D $�       D %�       D '�       D *�       D *�   �  � ����+�  � ������  � ����:�  � ����K�  � ����a�  � ����t�  � ����    �          �   �       $   �   ~�  $ ��t�  � �       D �       D �       D �       D �       D �(       D �H       D �W       D �_       D �e       D ��       D ��       D ��       D �  ��  @ �   ��  � �����:�  � �������  � �����    �          �   _   ��  � �����    �   e       �   �       �   �       �   �       �   �       �   �       �   �       �   �       $     ��  $   ���  �      >�  �      !R  �          D          D          D !        D ! #   ��  @      L�  @          �          �   #       $   *   � $ : �>�  � :        D :        D : 
       D ; 
       D <        D = .       D > 4       D ? >       D @ E       D @ L   L�  @ :    Y� � < ����    �   
       �   L       $   Q   ��  $ � p�b� � �    B�  � �    N�  � �    Y�  � �        D � 	       D �        D �        D �        D � :   o� @ �    q�  @ �    }�  @ �        �          �   :       $   B   ��  $ F ��b� � F        D F        D F 
       D G 
       D H        D I =       D J D       D J Y   o� @ F    Y� � G ����    �   
       �   Y       $   ^   ��  $ � �I�  � �    #  �          D �        D � 
       D �    ^�  @ �        �   
       �          $   #   k�  $ � 8���  � �        D �        D �        D �    ^�  @ �        �          �          $      ��  $ � H���  � �        D �        D � 
       D �    ^�  @ �        �   
       �          $   $   8�  $ P l���  � P    ��  � P    !R  �          D P        D P 
       D Q 
       D Q "   ��  @ P    ��  @ P        �   
       �   "       $   '   ��  $ W ����  � W    ��  � W        D W 	       D W        D X        D Y        D \ $       D \ z   ^�  @ W    ��  @ W        �          �   z       $   �    �  $ � 0���  � �    #  �          D �        D � 
       D � *   ^�  @ �        �   
       �   *       $   /   }�  $ � `�|� � �    �� � �        D �        D �        D � 8   �� @ �    �� @ �        �          �   8       $   ?   a�  $ � ��b� � �    B�  � �    N�  � �    Y�  � �    !R  �   	       D � 	       D �        D �        D �        D � :   o� @ �    q�  @ �    }�  @ �        �          �   :       $   B   �� $ � �|� � �    B�  � �    3�  � �    N�  � �    >�  � �        D � 	       D �        D �        D �        D � B       D � O       D � ]       D � �       D � �       D � �       D � �       D � �       D � �       D � ;      D � S      D � e      D � �      D � �      D � �      D � �  �� @ �    I�  � � ����T�  � � ����    �          �   �   Y� � � ����    �   �       �   c      �   �      �   �      $   �  ��    E    � $ �0�; � �   X& � �       D �       D �       D �       D �?       �          �   ?       $   B   ��  $ I 0�b� � I    #  �          D I        D I        D I    o� @ I        �          �          $      � $ � @�|� � �    N�  � �        D �        D �        D � 1   �� @ �    }�  @ �        �           �   -       $   8   o� $ �  ���  � �        D �        D �        D �    ^�  @ �        �          �          $      �  $ Z4�#�  � Z   y%  �          D Z       D Z       D [       D [   3�  @ Z       �          �          $      K�  $ �P���  � �   ��  � �       D �       D �       D �5   ��  @ �   ��  @ �       �          �          $   <   ��  $ �����  � �       D �       D �       D �       �          �          $      ��  $ m ��b� � m    #  �          D m        D m 
       D m    o� @ m        �   
       �          $   $   3�  $ � �|� � �    ��  � �        D �        D �        D � @   �� @ �    ��  @ �        �          �   (       $   G   �  & $ �#$�    �     ��  $ K �b� � K        D K        D K 
       D K 7   o� @ K        �   
       �   7       $   <   ʧ $ �  �|� � �    N�  � �        D �        D �        D � 0   �� @ �    }�  @ �        �          �   0       $   7   �  $ ' ����  � '    !R  �          D '        D ' 
       D * 
       D *    ��  @ '        �   
       �          $   "   +� $ �  �|� � �    N�  � �    Y�  � �    #  �   	       D � 	       D �        D � *   �� @ �    }�  @ �    ��  @ �        �          �   *       $   2   ��  $ �`���  � �   t�  � �   y%  �          D �       D �       D �       D �       D �       D �&       D �0       D �P       D �_       D �i       D ��   �  @ �   ��  @ �   �  � �������  � �������  � �����    �          �   �       $   �   ��  $ � T���  � �        D �        D �        D �        D �    �  @ �        �          �          $   !       d   @ main.cc /home/pic1/users/benny/Backup/ekosim/ gcc2_compiled. int:t(0,1)=r(0,1);0020000000000;0017777777777; char:t(0,2)=r(0,2);0;127; long int:t(0,3)=r(0,1);0020000000000;0017777777777; unsigned int:t(0,4)=r(0,1);0000000000000;0037777777777; long unsigned int:t(0,5)=r(0,1);0000000000000;0037777777777; long long int:t(0,6)=r(0,1);01000000000000000000000;0777777777777777777777; long long unsigned int:t(0,7)=r(0,1);0000000000000;01777777777777777777777; short int:t(0,8)=r(0,8);-32768;32767; short unsigned int:t(0,9)=r(0,9);0;65535; signed char:t(0,10)=r(0,10);-128;127; unsigned char:t(0,11)=r(0,11);0;255; float:t(0,12)=r(0,1);4;0; double:t(0,13)=r(0,1);8;0; long double:t(0,14)=r(0,1);12;0; complex int:t(0,15)=s8real:(0,1),0,32;imag:(0,1),32,32;; complex float:t(0,16)=r(0,16);4;0; complex double:t(0,17)=r(0,17);8;0; complex long double:t(0,18)=r(0,18);12;0; bool:t(0,19)=@s8;-16; void:t(0,20)=(0,20) __wchar_t:t(0,21)=r(0,1);0020000000000;0017777777777; __vtbl_ptr_type:t(0,22)=*(0,23)=f(0,1) /usr/lib/gcc-lib/i386-linux/2.95.4/../../../../include/g++-3/iostream /usr/lib/gcc-lib/i386-linux/2.95.4/../../../../include/g++-3/iostream.h /usr/lib/gcc-lib/i386-linux/2.95.4/../../../../include/g++-3/streambuf.h /usr/include/libio.h /usr/include/_G_config.h /usr/include/bits/types.h /usr/include/features.h /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h /usr/include/bits/wordsize.h /usr/lib/gcc-lib/i386-linux/2.95.4/include/stddef.h size_t:t(11,1)=(0,4) __u_char:t(6,1)=(0,11) __u_short:t(6,2)=(0,9) __u_int:t(6,3)=(0,4) __u_long:t(6,4)=(0,5) __int8_t:t(6,5)=(0,10) __uint8_t:t(6,6)=(0,11) __int16_t:t(6,7)=(0,8) __uint16_t:t(6,8)=(0,9) __int32_t:t(6,9)=(0,1) __uint32_t:t(6,10)=(0,4) __int64_t:t(6,11)=(0,6) __uint64_t:t(6,12)=(0,7) __quad_t:t(6,13)=(0,6) __u_quad_t:t(6,14)=(0,7) /usr/include/bits/typesizes.h __dev_t:t(6,15)=(0,7) __uid_t:t(6,16)=(0,4) __gid_t:t(6,17)=(0,4) __ino_t:t(6,18)=(0,5) __ino64_t:t(6,19)=(0,7) __mode_t:t(6,20)=(0,4) __nlink_t:t(6,21)=(0,4) __off_t:t(6,22)=(0,3) __off64_t:t(6,23)=(0,6) __pid_t:t(6,24)=(0,1) __fsid_t:t(6,25)=s8__val:(6,26)=ar(0,1);0;1;(0,1),0,64;__as::(6,27)=#(6,25),(6,28)=&(6,25),(6,29)=*(6,25),(6,30)=&(6,25),(0,20);:__as__3._0RC3._0;2A.;._0::(6,31)=#(6,25),(6,29),(6,29),(6,30),(0,20);:__3._0RC3._0;2A.(6,32)=#(6,25),(6,29),(6,29),(0,20);:__3._0;2A.;; __clock_t:t(6,33)=(0,3) __rlim_t:t(6,34)=(0,5) __rlim64_t:t(6,35)=(0,7) __id_t:t(6,36)=(0,4) __time_t:t(6,37)=(0,3) __useconds_t:t(6,38)=(0,4) __suseconds_t:t(6,39)=(0,3) __daddr_t:t(6,40)=(0,1) __swblk_t:t(6,41)=(0,3) __key_t:t(6,42)=(0,1) __clockid_t:t(6,43)=(0,1) __timer_t:t(6,44)=(0,1) __blksize_t:t(6,45)=(0,3) __blkcnt_t:t(6,46)=(0,3) __blkcnt64_t:t(6,47)=(0,6) __fsblkcnt_t:t(6,48)=(0,5) __fsblkcnt64_t:t(6,49)=(0,7) __fsfilcnt_t:t(6,50)=(0,5) __fsfilcnt64_t:t(6,51)=(0,7) __ssize_t:t(6,52)=(0,1) __loff_t:t(6,53)=(6,23) __qaddr_t:t(6,54)=(6,55)=*(6,13) __caddr_t:t(6,56)=(6,57)=*(0,2) __intptr_t:t(6,58)=(0,1) __socklen_t:t(6,59)=(0,4) wint_t:t(13,1)=(0,4) /usr/include/wchar.h /usr/include/bits/wchar.h __mbstate_t:t(14,1)=s8__count:(0,1),0,32;__value:(14,2)=u4__wch:(13,1),0,32;__wchb:(14,3)=ar(0,1);0;3;(0,2),0,32;__as::(14,4)=#(14,2),(14,5)=&(14,2),(14,6)=*(14,2),(14,7)=&(14,2),(0,20);:__as__Q23._13._2RCQ23._13._2;2A.;._2::(14,8)=#(14,2),(14,6),(14,6),(14,7),(0,20);:__Q23._13._2RCQ23._13._2;2A.(14,9)=#(14,2),(14,6),(14,6),(0,20);:__Q23._13._2;2A.;;,32,32;__as::(14,10)=#(14,1),(14,11)=&(14,1),(14,12)=*(14,1),(14,13)=&(14,1),(0,20);:__as__3._1RC3._1;2A.;._1::(14,14)=#(14,1),(14,12),(14,12),(14,13),(0,20);:__3._1RC3._1;2A.(14,15)=#(14,1),(14,12),(14,12),(0,20);:__3._1;2A.;; _G_fpos_t:t(5,1)=s12__pos:(6,22),0,32;__state:(14,1),32,64;__as::(5,2)=#(5,1),(5,3)=&(5,1),(5,4)=*(5,1),(5,5)=&(5,1),(0,20);:__as__3._3RC3._3;2A.;._3::(5,6)=#(5,1),(5,4),(5,4),(5,5),(0,20);:__3._3RC3._3;2A.(5,7)=#(5,1),(5,4),(5,4),(0,20);:__3._3;2A.;; _G_fpos64_t:t(5,8)=s16__pos:(6,23),0,64;__state:(14,1),64,64;__as::(5,9)=#(5,8),(5,10)=&(5,8),(5,11)=*(5,8),(5,12)=&(5,8),(0,20);:__as__3._4RC3._4;2A.;._4::(5,13)=#(5,8),(5,11),(5,11),(5,12),(0,20);:__3._4RC3._4;2A.(5,14)=#(5,8),(5,11),(5,11),(0,20);:__3._4;2A.;; /usr/include/gconv.h __gconv_fct:t(17,1)=(17,2)=*(17,3)=f(0,1) __gconv_btowc_fct:t(17,4)=(17,5)=*(17,6)=f(13,1) __gconv_init_fct:t(17,7)=(17,8)=*(17,9)=f(0,1) __gconv_end_fct:t(17,10)=(17,11)=*(17,12)=f(0,20) __gconv_trans_fct:t(17,13)=(17,14)=*(17,15)=f(0,1) __gconv_trans_context_fct:t(17,16)=(17,17)=*(17,18)=f(0,1) __gconv_trans_query_fct:t(17,19)=(17,20)=*(17,21)=f(0,1) __gconv_trans_init_fct:t(17,22)=(17,23)=*(17,24)=f(0,1) __gconv_trans_end_fct:t(17,25)=(17,26)=*(17,27)=f(0,20) __gconv_trans_data:Tt(17,28)=s20__trans_fct:(17,13),0,32;__trans_context_fct:(17,16),32,32;__trans_end_fct:(17,25),64,32;__data:(17,29)=*(0,20),96,32;__next:(17,30)=*(17,28),128,32;__as::(17,31)=##(17,32)=&(17,28);:RC18__gconv_trans_data;2A.;__gconv_trans_data::(17,33)=##(17,30);:RC18__gconv_trans_data;2A.(17,34)=##(17,30);:;2A.;; __gconv_step:Tt(17,35)=s60__shlib_handle:(17,36)=*(17,37)=xs__gconv_loaded_object:,0,32;__modname:(17,38)=*(0,2),32,32;__counter:(0,1),64,32;__from_name:(6,57),96,32;__to_name:(6,57),128,32;__fct:(17,1),160,32;__btowc_fct:(17,4),192,32;__init_fct:(17,7),224,32;__end_fct:(17,10),256,32;__min_needed_from:(0,1),288,32;__max_needed_from:(0,1),320,32;__min_needed_to:(0,1),352,32;__max_needed_to:(0,1),384,32;__stateful:(0,1),416,32;__data:(17,29),448,32;__as::(17,39)=##(17,40)=&(17,35);:RC12__gconv_step;2A.;__gconv_step::(17,41)=##(17,42)=*(17,35);:RC12__gconv_step;2A.(17,43)=##(17,42);:;2A.;; __gconv_step_data:Tt(17,44)=s36__outbuf:(17,45)=*(0,11),0,32;__outbufend:(17,45),32,32;__flags:(0,1),64,32;__invocation_counter:(0,1),96,32;__internal_use:(0,1),128,32;__statep:(14,12),160,32;__state:(14,1),192,64;__trans:(17,30),256,32;__as::(17,46)=##(17,47)=&(17,44);:RC17__gconv_step_data;2A.;__gconv_step_data::(17,48)=##(17,49)=*(17,44);:RC17__gconv_step_data;2A.(17,50)=##(17,49);:;2A.;; __gconv_info:Tt(17,51)=s8__nsteps:(11,1),0,32;__steps:(17,42),32,32;__data:(17,52)=ar(0,1);0;-1;(17,44),64,0;__as::(17,53)=##(17,54)=&(17,51);:RC12__gconv_info;2A.;__gconv_info::(17,55)=##(17,56)=*(17,51);:RC12__gconv_info;2A.(17,57)=##(17,56);:;2A.;; __gconv_t:t(17,58)=(17,56) _G_iconv_t:t(5,15)=u44__cd:(17,51),0,64;__combined:(5,16)=s44__cd:(17,51),0,64;__data:(17,44),64,288;__as::(5,17)=#(5,16),(5,18)=&(5,16),(5,19)=*(5,16),(5,20)=&(5,16),(0,20);:__as__Q23._73._8RCQ23._73._8;2A.;._8::(5,21)=#(5,16),(5,19),(5,19),(5,20),(0,20);:__Q23._73._8RCQ23._73._8;2A.(5,22)=#(5,16),(5,19),(5,19),(0,20);:__Q23._73._8;2A.;;,0,352;__as::(5,23)=#(5,15),(5,24)=&(5,15),(5,25)=*(5,15),(5,26)=&(5,15),(0,20);:__as__3._7RC3._7;2A.;._7::(5,27)=#(5,15),(5,25),(5,25),(5,26),(0,20);:__3._7RC3._7;2A.(5,28)=#(5,15),(5,25),(5,25),(0,20);:__3._7;2A.;; _G_int16_t:t(5,29)=(0,8) _G_int32_t:t(5,30)=(0,1) _G_uint16_t:t(5,31)=(0,9) _G_uint32_t:t(5,32)=(0,4) /usr/lib/gcc-lib/i386-linux/2.95.4/include/stdarg.h __gnuc_va_list:t(21,1)=(17,29) _IO_lock_t:t(4,1)=(0,20) _IO_marker:Tt(4,2)=s12_next:(4,3)=*(4,2),0,32;_sbuf:(4,4)=*(4,5)=xs_IO_FILE:,32,32;_pos:(0,1),64,32;__as::(4,6)=##(4,7)=&(4,2);:RC10_IO_marker;2A.;_IO_marker::(4,8)=##(4,3);:RC10_IO_marker;2A.(4,9)=##(4,3);:;2A.;; __codecvt_result:t(4,10)=e__codecvt_ok:0,__codecvt_partial:1,__codecvt_error:2,__codecvt_noconv:3,; _IO_FILE:Tt(4,5)=s148_flags:(0,1),0,32;_IO_read_ptr:(6,57),32,32;_IO_read_end:(6,57),64,32;_IO_read_base:(6,57),96,32;_IO_write_base:(6,57),128,32;_IO_write_ptr:(6,57),160,32;_IO_write_end:(6,57),192,32;_IO_buf_base:(6,57),224,32;_IO_buf_end:(6,57),256,32;_IO_save_base:(6,57),288,32;_IO_backup_base:(6,57),320,32;_IO_save_end:(6,57),352,32;_markers:(4,3),384,32;_chain:(4,4),416,32;_fileno:(0,1),448,32;_flags2:(0,1),480,32;_old_offset:(6,22),512,32;_cur_column:(0,9),544,16;_vtable_offset:(0,10),560,8;_shortbuf:(4,11)=ar(0,1);0;0;(0,2),568,8;_lock:(4,12)=*(4,1),576,32;_offset:(6,23),608,64;__pad1:(17,29),672,32;__pad2:(17,29),704,32;_mode:(0,1),736,32;_unused2:(4,13)=ar(0,1);0;51;(0,2),768,416;__as::(4,14)=##(4,15)=&(4,5);:RC8_IO_FILE;2A.;_IO_FILE::(4,16)=##(4,4);:RC8_IO_FILE;2A.(4,17)=##(4,4);:;2A.;; __io_read_fn:t(4,18)=(4,19)=f(6,52) __io_write_fn:t(4,20)=(4,21)=f(6,52) __io_seek_fn:t(4,22)=(4,23)=f(0,1) __io_close_fn:t(4,24)=(4,25)=f(0,1) va_list:t(22,1)=(21,1) streamoff:t(3,1)=(6,23) streampos:t(3,2)=(6,23) streamsize:t(3,3)=(6,52) __fmtflags:t(3,4)=(0,5) __iostate:t(3,5)=(0,11) io_state:t(3,6)=egoodbit:0,eofbit:1,failbit:2,badbit:4,; open_mode:t(3,7)=ein:1,out:2,ate:4,app:8,trunc:16,nocreate:32,noreplace:64,bin:128,binary:128,; seek_dir:t(3,8)=ebeg:0,cur:1,end:2,; _seek_dir:t(3,9)=(3,8) __manip:t(2,1)=(2,2)=*(2,3)=f(2,4)=&(2,5)=xsios: __imanip:t(2,6)=(2,7)=*(2,8)=f(2,9)=&(2,10)=xsistream: __omanip:t(2,11)=(2,12)=*(2,13)=f(2,14)=&(2,15)=xsostream: /usr/lib/gcc-lib/i386-linux/2.95.4/../../../../include/g++-3/iomanip /usr/lib/gcc-lib/i386-linux/2.95.4/../../../../include/g++-3/iomanip.h /usr/lib/gcc-lib/i386-linux/2.95.4/../../../../include/g++-3/string /usr/lib/gcc-lib/i386-linux/2.95.4/../../../../include/g++-3/std/bastring.h /usr/lib/gcc-lib/i386-linux/2.95.4/../../../../include/g++-3/cstddef ptrdiff_t:t(28,1)=(0,1) /usr/lib/gcc-lib/i386-linux/2.95.4/../../../../include/g++-3/std/straits.h /usr/lib/gcc-lib/i386-linux/2.95.4/../../../../include/g++-3/cctype /usr/include/ctype.h /usr/include/endian.h /usr/include/bits/endian.h /usr/lib/gcc-lib/i386-linux/2.95.4/../../../../include/g++-3/cstring /usr/include/string.h /usr/lib/gcc-lib/i386-linux/2.95.4/../../../../include/g++-3/alloc.h /usr/lib/gcc-lib/i386-linux/2.95.4/../../../../include/g++-3/stl_config.h /usr/lib/gcc-lib/i386-linux/2.95.4/../../../../include/g++-3/stl_alloc.h /usr/lib/gcc-lib/i386-linux/2.95.4/include/new /usr/lib/gcc-lib/i386-linux/2.95.4/include/exception terminate_handler:t(42,1)=(42,2)=*(42,3)=f(0,20) unexpected_handler:t(42,4)=(42,2) new_handler:t(40,1)=(42,2) /usr/include/stdlib.h div_t:t(44,1)=s8quot:(0,1),0,32;rem:(0,1),32,32;__as::(44,2)=#(44,1),(44,3)=&(44,1),(44,4)=*(44,1),(44,5)=&(44,1),(0,20);:__as__4._12RC4._12;2A.;._12::(44,6)=#(44,1),(44,4),(44,4),(44,5),(0,20);:__4._12RC4._12;2A.(44,7)=#(44,1),(44,4),(44,4),(0,20);:__4._12;2A.;; ldiv_t:t(44,8)=s8quot:(0,3),0,32;rem:(0,3),32,32;__as::(44,9)=#(44,8),(44,10)=&(44,8),(44,11)=*(44,8),(44,12)=&(44,8),(0,20);:__as__4._13RC4._13;2A.;._13::(44,13)=#(44,8),(44,11),(44,11),(44,12),(0,20);:__4._13RC4._13;2A.(44,14)=#(44,8),(44,11),(44,11),(0,20);:__4._13;2A.;; /usr/include/sys/types.h u_char:t(46,1)=(6,1) u_short:t(46,2)=(6,2) u_int:t(46,3)=(6,3) u_long:t(46,4)=(6,4) quad_t:t(46,5)=(6,13) u_quad_t:t(46,6)=(6,14) fsid_t:t(46,7)=(6,25) loff_t:t(46,8)=(6,53) ino_t:t(46,9)=(6,18) dev_t:t(46,10)=(6,15) gid_t:t(46,11)=(6,17) mode_t:t(46,12)=(6,20) nlink_t:t(46,13)=(6,21) uid_t:t(46,14)=(6,16) off_t:t(46,15)=(6,22) pid_t:t(46,16)=(6,24) id_t:t(46,17)=(6,36) ssize_t:t(46,18)=(6,52) daddr_t:t(46,19)=(6,40) caddr_t:t(46,20)=(6,56) key_t:t(46,21)=(6,42) /usr/include/time.h time_t:t(47,1)=(6,37) clockid_t:t(47,2)=(6,43) timer_t:t(47,3)=(6,44) ulong:t(46,22)=(0,5) ushort:t(46,23)=(0,9) uint:t(46,24)=(0,4) int8_t:t(46,25)=(0,10) int16_t:t(46,26)=(0,8) int32_t:t(46,27)=(0,1) int64_t:t(46,28)=(0,6) u_int8_t:t(46,29)=(0,11) u_int16_t:t(46,30)=(0,9) u_int32_t:t(46,31)=(0,4) u_int64_t:t(46,32)=(0,7) register_t:t(46,33)=(0,1) /usr/include/sys/select.h /usr/include/bits/select.h /usr/include/bits/sigset.h __sig_atomic_t:t(51,1)=(0,1) __sigset_t:t(51,2)=s128__val:(51,3)=ar(0,1);0;31;(0,5),0,1024;__as::(51,4)=#(51,2),(51,5)=&(51,2),(51,6)=*(51,2),(51,7)=&(51,2),(0,20);:__as__4._14RC4._14;2A.;._14::(51,8)=#(51,2),(51,6),(51,6),(51,7),(0,20);:__4._14RC4._14;2A.(51,9)=#(51,2),(51,6),(51,6),(0,20);:__4._14;2A.;; sigset_t:t(49,1)=(51,2) timespec:Tt(52,1)=s8tv_sec:(6,37),0,32;tv_nsec:(0,3),32,32;__as::(52,2)=##(52,3)=&(52,1);:RC8timespec;2A.;timespec::(52,4)=##(52,5)=*(52,1);:RC8timespec;2A.(52,6)=##(52,5);:;2A.;; /usr/include/bits/time.h timeval:Tt(53,1)=s8tv_sec:(6,37),0,32;tv_usec:(6,39),32,32;__as::(53,2)=##(53,3)=&(53,1);:RC7timeval;2A.;timeval::(53,4)=##(53,5)=*(53,1);:RC7timeval;2A.(53,6)=##(53,5);:;2A.;; suseconds_t:t(49,2)=(6,39) __fd_mask:t(49,3)=(0,3) fd_set:t(49,4)=s128__fds_bits:(49,5)=ar(0,1);0;31;(0,3),0,1024;__as::(49,6)=#(49,4),(49,7)=&(49,4),(49,8)=*(49,4),(49,9)=&(49,4),(0,20);:__as__4._15RC4._15;2A.;._15::(49,10)=#(49,4),(49,8),(49,8),(49,9),(0,20);:__4._15RC4._15;2A.(49,11)=#(49,4),(49,8),(49,8),(0,20);:__4._15;2A.;; fd_mask:t(49,12)=(49,3) /usr/include/sys/sysmacros.h blkcnt_t:t(46,34)=(6,46) fsblkcnt_t:t(46,35)=(6,48) fsfilcnt_t:t(46,36)=(6,50) /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h __sched_param:Tt(56,1)=s4__sched_priority:(0,1),0,32;__as::(56,2)=##(56,3)=&(56,1);:RC13__sched_param;2A.;__sched_param::(56,4)=##(56,5)=*(56,1);:RC13__sched_param;2A.(56,6)=##(56,5);:;2A.;; __atomic_lock_t:t(55,1)=(0,1) _pthread_fastlock:Tt(55,2)=s8__status:(0,3),0,32;__spinlock:(55,1),32,32;__as::(55,3)=##(55,4)=&(55,2);:RC17_pthread_fastlock;2A.;_pthread_fastlock::(55,5)=##(55,6)=*(55,2);:RC17_pthread_fastlock;2A.(55,7)=##(55,6);:;2A.;; _pthread_descr:t(55,8)=(55,9)=*(55,10)=xs_pthread_descr_struct: __pthread_attr_s:Tt(55,11)=s36__detachstate:(0,1),0,32;__schedpolicy:(0,1),32,32;__schedparam:(56,1),64,32;__inheritsched:(0,1),96,32;__scope:(0,1),128,32;__guardsize:(11,1),160,32;__stackaddr_set:(0,1),192,32;__stackaddr:(17,29),224,32;__stacksize:(11,1),256,32;__as::(55,12)=##(55,13)=&(55,11);:RC16__pthread_attr_s;2A.;__pthread_attr_s::(55,14)=##(55,15)=*(55,11);:RC16__pthread_attr_s;2A.(55,16)=##(55,15);:;2A.;; pthread_attr_t:t(55,17)=(55,11) __pthread_cond_align_t:t(55,18)=(0,6) pthread_cond_t:t(55,19)=s48__c_lock:(55,2),0,64;__c_waiting:(55,8),64,32;__padding:(55,20)=ar(0,1);0;27;(0,2),96,224;__align:(55,18),320,64;__as::(55,21)=#(55,19),(55,22)=&(55,19),(55,23)=*(55,19),(55,24)=&(55,19),(0,20);:__as__4._16RC4._16;2A.;._16::(55,25)=#(55,19),(55,23),(55,23),(55,24),(0,20);:__4._16RC4._16;2A.(55,26)=#(55,19),(55,23),(55,23),(0,20);:__4._16;2A.;; pthread_condattr_t:t(55,27)=s4__dummy:(0,1),0,32;__as::(55,28)=#(55,27),(55,29)=&(55,27),(55,30)=*(55,27),(55,31)=&(55,27),(0,20);:__as__4._17RC4._17;2A.;._17::(55,32)=#(55,27),(55,30),(55,30),(55,31),(0,20);:__4._17RC4._17;2A.(55,33)=#(55,27),(55,30),(55,30),(0,20);:__4._17;2A.;; pthread_key_t:t(55,34)=(0,4) pthread_mutex_t:t(55,35)=s24__m_reserved:(0,1),0,32;__m_count:(0,1),32,32;__m_owner:(55,8),64,32;__m_kind:(0,1),96,32;__m_lock:(55,2),128,64;__as::(55,36)=#(55,35),(55,37)=&(55,35),(55,38)=*(55,35),(55,39)=&(55,35),(0,20);:__as__4._18RC4._18;2A.;._18::(55,40)=#(55,35),(55,38),(55,38),(55,39),(0,20);:__4._18RC4._18;2A.(55,41)=#(55,35),(55,38),(55,38),(0,20);:__4._18;2A.;; pthread_mutexattr_t:t(55,42)=s4__mutexkind:(0,1),0,32;__as::(55,43)=#(55,42),(55,44)=&(55,42),(55,45)=*(55,42),(55,46)=&(55,42),(0,20);:__as__4._19RC4._19;2A.;._19::(55,47)=#(55,42),(55,45),(55,45),(55,46),(0,20);:__4._19RC4._19;2A.(55,48)=#(55,42),(55,45),(55,45),(0,20);:__4._19;2A.;; pthread_once_t:t(55,49)=(0,1) pthread_t:t(55,50)=(0,5) random_data:Tt(44,15)=s28fptr:(44,16)=*(46,27),0,32;rptr:(44,16),32,32;state:(44,16),64,32;rand_type:(0,1),96,32;rand_deg:(0,1),128,32;rand_sep:(0,1),160,32;end_ptr:(44,16),192,32;__as::(44,17)=##(44,18)=&(44,15);:RC11random_data;2A.;random_data::(44,19)=##(44,20)=*(44,15);:RC11random_data;2A.(44,21)=##(44,20);:;2A.;; drand48_data:Tt(44,22)=s24__x:(44,23)=ar(0,1);0;2;(0,9),0,48;__old_x:(44,23),48,48;__c:(0,9),96,16;__init:(0,9),112,16;__a:(0,7),128,64;__as::(44,24)=##(44,25)=&(44,22);:RC12drand48_data;2A.;drand48_data::(44,26)=##(44,27)=*(44,22);:RC12drand48_data;2A.(44,28)=##(44,27);:;2A.;; /usr/include/alloca.h __compar_fn_t:t(44,29)=(44,30)=*(44,31)=f(0,1) /usr/include/assert.h /usr/include/pthread.h /usr/include/sched.h sched_param:Tt(63,1)=s4__sched_priority:(0,1),0,32;__as::(63,2)=##(63,3)=&(63,1);:RC11sched_param;2A.;sched_param::(63,4)=##(63,5)=*(63,1);:RC11sched_param;2A.(63,6)=##(63,5);:;2A.;; __cpu_mask:t(63,7)=(0,5) cpu_set_t:t(63,8)=s128__bits:(51,3),0,1024;__as::(63,9)=#(63,8),(63,10)=&(63,8),(63,11)=*(63,8),(63,12)=&(63,8),(0,20);:__as__4._20RC4._20;2A.;._20::(63,13)=#(63,8),(63,11),(63,11),(63,12),(0,20);:__4._20RC4._20;2A.(63,14)=#(63,8),(63,11),(63,11),(0,20);:__4._20;2A.;; clock_t:t(64,1)=(6,33) tm:Tt(64,2)=s44tm_sec:(0,1),0,32;tm_min:(0,1),32,32;tm_hour:(0,1),64,32;tm_mday:(0,1),96,32;tm_mon:(0,1),128,32;tm_year:(0,1),160,32;tm_wday:(0,1),192,32;tm_yday:(0,1),224,32;tm_isdst:(0,1),256,32;tm_gmtoff:(0,3),288,32;tm_zone:(17,38),320,32;__as::(64,3)=##(64,4)=&(64,2);:RC2tm;2A.;tm::(64,5)=##(64,6)=*(64,2);:RC2tm;2A.(64,7)=##(64,6);:;2A.;; itimerspec:Tt(64,8)=s16it_interval:(52,1),0,64;it_value:(52,1),64,64;__as::(64,9)=##(64,10)=&(64,8);:RC10itimerspec;2A.;itimerspec::(64,11)=##(64,12)=*(64,8);:RC10itimerspec;2A.(64,13)=##(64,12);:;2A.;; /usr/include/signal.h /usr/include/bits/initspin.h _pthread_cleanup_buffer:Tt(60,1)=s16__routine:(17,26),0,32;__arg:(17,29),32,32;__canceltype:(0,1),64,32;__prev:(60,2)=*(60,1),96,32;__as::(60,3)=##(60,4)=&(60,1);:RC23_pthread_cleanup_buffer;2A.;_pthread_cleanup_buffer::(60,5)=##(60,2);:RC23_pthread_cleanup_buffer;2A.(60,6)=##(60,2);:;2A.;; /usr/include/bits/sigthread.h malloc_alloc:t(39,1)=(39,2)=xs__malloc_alloc_template<0>: __malloc_alloc_template<0>:Tt(39,2)=s1__malloc_alloc_oom_handler:/0(42,2):_t23__malloc_alloc_template1i0.__malloc_alloc_oom_handler;__as::(39,3)=##(39,4)=&(39,2);:t23__malloc_alloc_template1i0RCt23__malloc_alloc_template1i0;2A.;__malloc_alloc_template::(39,5)=##(39,6)=*(39,2);:__t23__malloc_alloc_template1i0RCt23__malloc_alloc_template1i0;2A.(39,7)=##(39,6);:__t23__malloc_alloc_template1i0;2A.;_S_oom_malloc::(39,8)=f(17,29):t23__malloc_alloc_template1i0Ui;0A?;_S_oom_realloc::(39,9)=f(17,29):t23__malloc_alloc_template1i0PvUi;0A?;allocate::(39,8):t23__malloc_alloc_template1i0Ui;2A?;deallocate::(39,10)=f(0,20):t23__malloc_alloc_template1i0PvUi;2A?;reallocate::(39,11)=f(17,29):t23__malloc_alloc_template1i0PvUiUi;2A?;__set_malloc_handler::(39,12)=f(42,2):t23__malloc_alloc_template1i0PFv_v;2A?;; alloc:t(39,13)=(39,14)=xs__default_alloc_template<true,0>: single_client_alloc:t(39,15)=(39,16)=xs__default_alloc_template<false,0>: __default_alloc_template<true,0>:Tt(39,14)=s1_S_free_list:/0(39,17)=ar(0,1);0;15;(39,18)=*(39,19)=xu_Obj::_t24__default_alloc_template2b1i0._S_free_list;_S_start_free:/0(6,57):_t24__default_alloc_template2b1i0._S_start_free;_S_end_free:/0(6,57):_t24__default_alloc_template2b1i0._S_end_free;_S_heap_size:/0(11,1):_t24__default_alloc_template2b1i0._S_heap_size;_S_node_allocator_lock:/0(55,35):_t24__default_alloc_template2b1i0._S_node_allocator_lock;__as::(39,20)=##(39,21)=&(39,14);:t24__default_alloc_template2b1i0RCt24__default_alloc_template2b1i0;2A.;__default_alloc_template::(39,22)=##(39,23)=*(39,14);:__t24__default_alloc_template2b1i0RCt24__default_alloc_template2b1i0;2A.(39,24)=##(39,23);:__t24__default_alloc_template2b1i0;2A.;_S_round_up::(39,25)=f(11,1):t24__default_alloc_template2b1i0Ui;0A?;_S_freelist_index::(39,25):t24__default_alloc_template2b1i0Ui;0A?;_S_refill::(39,8):t24__default_alloc_template2b1i0Ui;0A?;_S_chunk_alloc::(39,26)=f(6,57):t24__default_alloc_template2b1i0UiRi;0A?;allocate::(39,8):t24__default_alloc_template2b1i0Ui;2A?;deallocate::(39,10):t24__default_alloc_template2b1i0PvUi;2A?;reallocate::(39,11):t24__default_alloc_template2b1i0PvUiUi;2A?;; allocator<void>:Tt(39,27)=s1__as::(39,28)=##(39,29)=&(39,27);:t9allocator1ZvRCt9allocator1Zv;2A.;allocator::(39,30)=##(39,31)=*(39,27);:__t9allocator1ZvRCt9allocator1Zv;2A.(39,32)=##(39,31);:__t9allocator1Zv;2A.;; /usr/lib/gcc-lib/i386-linux/2.95.4/../../../../include/g++-3/iterator /usr/lib/gcc-lib/i386-linux/2.95.4/../../../../include/g++-3/stl_relops.h /usr/lib/gcc-lib/i386-linux/2.95.4/../../../../include/g++-3/stl_iterator.h input_iterator_tag:Tt(75,1)=s1__as::(75,2)=##(75,3)=&(75,1);:RC18input_iterator_tag;2A.;input_iterator_tag::(75,4)=##(75,5)=*(75,1);:RC18input_iterator_tag;2A.(75,6)=##(75,5);:;2A.;; output_iterator_tag:Tt(75,7)=s1__as::(75,8)=##(75,9)=&(75,7);:RC19output_iterator_tag;2A.;output_iterator_tag::(75,10)=##(75,11)=*(75,7);:RC19output_iterator_tag;2A.(75,12)=##(75,11);:;2A.;; forward_iterator_tag:Tt(75,13)=s1!1,020,(75,1);__as::(75,14)=##(75,15)=&(75,13);:RC20forward_iterator_tag;2A.;forward_iterator_tag::(75,16)=##(75,17)=*(75,13);:RC20forward_iterator_tag;2A.(75,18)=##(75,17);:;2A.;; bidirectional_iterator_tag:Tt(75,19)=s1!1,020,(75,13);__as::(75,20)=##(75,21)=&(75,19);:RC26bidirectional_iterator_tag;2A.;bidirectional_iterator_tag::(75,22)=##(75,23)=*(75,19);:RC26bidirectional_iterator_tag;2A.(75,24)=##(75,23);:;2A.;; random_access_iterator_tag:Tt(75,25)=s1!1,020,(75,19);__as::(75,26)=##(75,27)=&(75,25);:RC26random_access_iterator_tag;2A.;random_access_iterator_tag::(75,28)=##(75,29)=*(75,25);:RC26random_access_iterator_tag;2A.(75,30)=##(75,29);:;2A.;; output_iterator:Tt(75,31)=s1__as::(75,32)=##(75,33)=&(75,31);:RC15output_iterator;2A.;output_iterator::(75,34)=##(75,35)=*(75,31);:RC15output_iterator;2A.(75,36)=##(75,35);:;2A.;; /usr/lib/gcc-lib/i386-linux/2.95.4/../../../../include/g++-3/std/bastring.cc string:t(25,1)=(25,2)=xsbasic_string<char,string_char_traits<char>,__default_alloc_template<true,0> >: /usr/lib/gcc-lib/i386-linux/2.95.4/../../../../include/g++-3/vector /usr/lib/gcc-lib/i386-linux/2.95.4/../../../../include/g++-3/stl_algobase.h /usr/lib/gcc-lib/i386-linux/2.95.4/../../../../include/g++-3/stl_pair.h /usr/lib/gcc-lib/i386-linux/2.95.4/../../../../include/g++-3/type_traits.h __true_type:Tt(80,1)=s1__as::(80,2)=##(80,3)=&(80,1);:RC11__true_type;2A.;__true_type::(80,4)=##(80,5)=*(80,1);:RC11__true_type;2A.(80,6)=##(80,5);:;2A.;; __false_type:Tt(80,7)=s1__as::(80,8)=##(80,9)=&(80,7);:RC12__false_type;2A.;__false_type::(80,10)=##(80,11)=*(80,7);:RC12__false_type;2A.(80,12)=##(80,11);:;2A.;; __type_traits<bool>:Tt(80,13)=s1__as::(80,14)=##(80,15)=&(80,13);:t13__type_traits1ZbRCt13__type_traits1Zb;2A.;__type_traits::(80,16)=##(80,17)=*(80,13);:__t13__type_traits1ZbRCt13__type_traits1Zb;2A.(80,18)=##(80,17);:__t13__type_traits1Zb;2A.;; __type_traits<char>:Tt(80,19)=s1__as::(80,20)=##(80,21)=&(80,19);:t13__type_traits1ZcRCt13__type_traits1Zc;2A.;__type_traits::(80,22)=##(80,23)=*(80,19);:__t13__type_traits1ZcRCt13__type_traits1Zc;2A.(80,24)=##(80,23);:__t13__type_traits1Zc;2A.;; __type_traits<signed char>:Tt(80,25)=s1__as::(80,26)=##(80,27)=&(80,25);:t13__type_traits1ZScRCt13__type_traits1ZSc;2A.;__type_traits::(80,28)=##(80,29)=*(80,25);:__t13__type_traits1ZScRCt13__type_traits1ZSc;2A.(80,30)=##(80,29);:__t13__type_traits1ZSc;2A.;; __type_traits<unsigned char>:Tt(80,31)=s1__as::(80,32)=##(80,33)=&(80,31);:t13__type_traits1ZUcRCt13__type_traits1ZUc;2A.;__type_traits::(80,34)=##(80,35)=*(80,31);:__t13__type_traits1ZUcRCt13__type_traits1ZUc;2A.(80,36)=##(80,35);:__t13__type_traits1ZUc;2A.;; __type_traits<__wchar_t>:Tt(80,37)=s1__as::(80,38)=##(80,39)=&(80,37);:t13__type_traits1ZwRCt13__type_traits1Zw;2A.;__type_traits::(80,40)=##(80,41)=*(80,37);:__t13__type_traits1ZwRCt13__type_traits1Zw;2A.(80,42)=##(80,41);:__t13__type_traits1Zw;2A.;; __type_traits<short int>:Tt(80,43)=s1__as::(80,44)=##(80,45)=&(80,43);:t13__type_traits1ZsRCt13__type_traits1Zs;2A.;__type_traits::(80,46)=##(80,47)=*(80,43);:__t13__type_traits1ZsRCt13__type_traits1Zs;2A.(80,48)=##(80,47);:__t13__type_traits1Zs;2A.;; __type_traits<short unsigned int>:Tt(80,49)=s1__as::(80,50)=##(80,51)=&(80,49);:t13__type_traits1ZUsRCt13__type_traits1ZUs;2A.;__type_traits::(80,52)=##(80,53)=*(80,49);:__t13__type_traits1ZUsRCt13__type_traits1ZUs;2A.(80,54)=##(80,53);:__t13__type_traits1ZUs;2A.;; __type_traits<int>:Tt(80,55)=s1__as::(80,56)=##(80,57)=&(80,55);:t13__type_traits1ZiRCt13__type_traits1Zi;2A.;__type_traits::(80,58)=##(80,59)=*(80,55);:__t13__type_traits1ZiRCt13__type_traits1Zi;2A.(80,60)=##(80,59);:__t13__type_traits1Zi;2A.;; __type_traits<unsigned int>:Tt(80,61)=s1__as::(80,62)=##(80,63)=&(80,61);:t13__type_traits1ZUiRCt13__type_traits1ZUi;2A.;__type_traits::(80,64)=##(80,65)=*(80,61);:__t13__type_traits1ZUiRCt13__type_traits1ZUi;2A.(80,66)=##(80,65);:__t13__type_traits1ZUi;2A.;; __type_traits<long int>:Tt(80,67)=s1__as::(80,68)=##(80,69)=&(80,67);:t13__type_traits1ZlRCt13__type_traits1Zl;2A.;__type_traits::(80,70)=##(80,71)=*(80,67);:__t13__type_traits1ZlRCt13__type_traits1Zl;2A.(80,72)=##(80,71);:__t13__type_traits1Zl;2A.;; __type_traits<long unsigned int>:Tt(80,73)=s1__as::(80,74)=##(80,75)=&(80,73);:t13__type_traits1ZUlRCt13__type_traits1ZUl;2A.;__type_traits::(80,76)=##(80,77)=*(80,73);:__t13__type_traits1ZUlRCt13__type_traits1ZUl;2A.(80,78)=##(80,77);:__t13__type_traits1ZUl;2A.;; __type_traits<long long int>:Tt(80,79)=s1__as::(80,80)=##(80,81)=&(80,79);:t13__type_traits1ZxRCt13__type_traits1Zx;2A.;__type_traits::(80,82)=##(80,83)=*(80,79);:__t13__type_traits1ZxRCt13__type_traits1Zx;2A.(80,84)=##(80,83);:__t13__type_traits1Zx;2A.;; __type_traits<long long unsigned int>:Tt(80,85)=s1__as::(80,86)=##(80,87)=&(80,85);:t13__type_traits1ZUxRCt13__type_traits1ZUx;2A.;__type_traits::(80,88)=##(80,89)=*(80,85);:__t13__type_traits1ZUxRCt13__type_traits1ZUx;2A.(80,90)=##(80,89);:__t13__type_traits1ZUx;2A.;; __type_traits<float>:Tt(80,91)=s1__as::(80,92)=##(80,93)=&(80,91);:t13__type_traits1ZfRCt13__type_traits1Zf;2A.;__type_traits::(80,94)=##(80,95)=*(80,91);:__t13__type_traits1ZfRCt13__type_traits1Zf;2A.(80,96)=##(80,95);:__t13__type_traits1Zf;2A.;; __type_traits<double>:Tt(80,97)=s1__as::(80,98)=##(80,99)=&(80,97);:t13__type_traits1ZdRCt13__type_traits1Zd;2A.;__type_traits::(80,100)=##(80,101)=*(80,97);:__t13__type_traits1ZdRCt13__type_traits1Zd;2A.(80,102)=##(80,101);:__t13__type_traits1Zd;2A.;; __type_traits<long double>:Tt(80,103)=s1__as::(80,104)=##(80,105)=&(80,103);:t13__type_traits1ZrRCt13__type_traits1Zr;2A.;__type_traits::(80,106)=##(80,107)=*(80,103);:__t13__type_traits1ZrRCt13__type_traits1Zr;2A.(80,108)=##(80,107);:__t13__type_traits1Zr;2A.;; _Is_integer<bool>:Tt(80,109)=s1__as::(80,110)=##(80,111)=&(80,109);:t11_Is_integer1ZbRCt11_Is_integer1Zb;2A.;_Is_integer::(80,112)=##(80,113)=*(80,109);:__t11_Is_integer1ZbRCt11_Is_integer1Zb;2A.(80,114)=##(80,113);:__t11_Is_integer1Zb;2A.;; _Is_integer<char>:Tt(80,115)=s1__as::(80,116)=##(80,117)=&(80,115);:t11_Is_integer1ZcRCt11_Is_integer1Zc;2A.;_Is_integer::(80,118)=##(80,119)=*(80,115);:__t11_Is_integer1ZcRCt11_Is_integer1Zc;2A.(80,120)=##(80,119);:__t11_Is_integer1Zc;2A.;; _Is_integer<signed char>:Tt(80,121)=s1__as::(80,122)=##(80,123)=&(80,121);:t11_Is_integer1ZScRCt11_Is_integer1ZSc;2A.;_Is_integer::(80,124)=##(80,125)=*(80,121);:__t11_Is_integer1ZScRCt11_Is_integer1ZSc;2A.(80,126)=##(80,125);:__t11_Is_integer1ZSc;2A.;; _Is_integer<unsigned char>:Tt(80,127)=s1__as::(80,128)=##(80,129)=&(80,127);:t11_Is_integer1ZUcRCt11_Is_integer1ZUc;2A.;_Is_integer::(80,130)=##(80,131)=*(80,127);:__t11_Is_integer1ZUcRCt11_Is_integer1ZUc;2A.(80,132)=##(80,131);:__t11_Is_integer1ZUc;2A.;; _Is_integer<__wchar_t>:Tt(80,133)=s1__as::(80,134)=##(80,135)=&(80,133);:t11_Is_integer1ZwRCt11_Is_integer1Zw;2A.;_Is_integer::(80,136)=##(80,137)=*(80,133);:__t11_Is_integer1ZwRCt11_Is_integer1Zw;2A.(80,138)=##(80,137);:__t11_Is_integer1Zw;2A.;; _Is_integer<short int>:Tt(80,139)=s1__as::(80,140)=##(80,141)=&(80,139);:t11_Is_integer1ZsRCt11_Is_integer1Zs;2A.;_Is_integer::(80,142)=##(80,143)=*(80,139);:__t11_Is_integer1ZsRCt11_Is_integer1Zs;2A.(80,144)=##(80,143);:__t11_Is_integer1Zs;2A.;; _Is_integer<short unsigned int>:Tt(80,145)=s1__as::(80,146)=##(80,147)=&(80,145);:t11_Is_integer1ZUsRCt11_Is_integer1ZUs;2A.;_Is_integer::(80,148)=##(80,149)=*(80,145);:__t11_Is_integer1ZUsRCt11_Is_integer1ZUs;2A.(80,150)=##(80,149);:__t11_Is_integer1ZUs;2A.;; _Is_integer<int>:Tt(80,151)=s1__as::(80,152)=##(80,153)=&(80,151);:t11_Is_integer1ZiRCt11_Is_integer1Zi;2A.;_Is_integer::(80,154)=##(80,155)=*(80,151);:__t11_Is_integer1ZiRCt11_Is_integer1Zi;2A.(80,156)=##(80,155);:__t11_Is_integer1Zi;2A.;; _Is_integer<unsigned int>:Tt(80,157)=s1__as::(80,158)=##(80,159)=&(80,157);:t11_Is_integer1ZUiRCt11_Is_integer1ZUi;2A.;_Is_integer::(80,160)=##(80,161)=*(80,157);:__t11_Is_integer1ZUiRCt11_Is_integer1ZUi;2A.(80,162)=##(80,161);:__t11_Is_integer1ZUi;2A.;; _Is_integer<long int>:Tt(80,163)=s1__as::(80,164)=##(80,165)=&(80,163);:t11_Is_integer1ZlRCt11_Is_integer1Zl;2A.;_Is_integer::(80,166)=##(80,167)=*(80,163);:__t11_Is_integer1ZlRCt11_Is_integer1Zl;2A.(80,168)=##(80,167);:__t11_Is_integer1Zl;2A.;; _Is_integer<long unsigned int>:Tt(80,169)=s1__as::(80,170)=##(80,171)=&(80,169);:t11_Is_integer1ZUlRCt11_Is_integer1ZUl;2A.;_Is_integer::(80,172)=##(80,173)=*(80,169);:__t11_Is_integer1ZUlRCt11_Is_integer1ZUl;2A.(80,174)=##(80,173);:__t11_Is_integer1ZUl;2A.;; _Is_integer<long long int>:Tt(80,175)=s1__as::(80,176)=##(80,177)=&(80,175);:t11_Is_integer1ZxRCt11_Is_integer1Zx;2A.;_Is_integer::(80,178)=##(80,179)=*(80,175);:__t11_Is_integer1ZxRCt11_Is_integer1Zx;2A.(80,180)=##(80,179);:__t11_Is_integer1Zx;2A.;; _Is_integer<long long unsigned int>:Tt(80,181)=s1__as::(80,182)=##(80,183)=&(80,181);:t11_Is_integer1ZUxRCt11_Is_integer1ZUx;2A.;_Is_integer::(80,184)=##(80,185)=*(80,181);:__t11_Is_integer1ZUxRCt11_Is_integer1ZUx;2A.(80,186)=##(80,185);:__t11_Is_integer1ZUx;2A.;; /usr/lib/gcc-lib/i386-linux/2.95.4/include/limits.h /usr/lib/gcc-lib/i386-linux/2.95.4/include/syslimits.h /usr/include/limits.h /usr/include/bits/posix1_lim.h /usr/include/bits/local_lim.h /usr/include/linux/limits.h /usr/include/bits/posix2_lim.h /usr/lib/gcc-lib/i386-linux/2.95.4/include/new.h /usr/lib/gcc-lib/i386-linux/2.95.4/../../../../include/g++-3/stl_construct.h /usr/lib/gcc-lib/i386-linux/2.95.4/../../../../include/g++-3/stl_uninitialized.h /usr/lib/gcc-lib/i386-linux/2.95.4/../../../../include/g++-3/stl_vector.h /usr/lib/gcc-lib/i386-linux/2.95.4/../../../../include/g++-3/stl_bvector.h _Bit_reference:Tt(94,1)=s8_M_p:(94,2)=*(0,4),0,32;_M_mask:(0,4),32,32;_Bit_reference::(94,3)=##(94,4)=*(94,1);:RC14_Bit_reference;2A.(94,5)=##(94,4);:PUiUi;2A.(94,6)=##(94,4);:;2A.;__opb::(94,7)=##(0,19);:;2B.;__as::(94,8)=##(94,9)=&(94,1);:b;2A.(94,10)=##(94,9);:RC14_Bit_reference;2A.;__eq::(94,11)=##(0,19);:RC14_Bit_reference;2B.;__lt::(94,11):RC14_Bit_reference;2B.;flip::(94,12)=##(0,20);:;2A.;; random_access_iterator<bool,int>:Tt(94,13)=s1__as::(94,14)=##(94,15)=&(94,13);:t22random_access_iterator2ZbZiRCt22random_access_iterator2ZbZi;2A.;random_access_iterator::(94,16)=##(94,17)=*(94,13);:__t22random_access_iterator2ZbZiRCt22random_access_iterator2ZbZi;2A.(94,18)=##(94,17);:__t22random_access_iterator2ZbZi;2A.;; _Bit_iterator:Tt(94,19)=s12!1,020,(94,13);_M_p:(94,2),32,32;_M_offset:(0,4),64,32;__as::(94,20)=##(94,21)=&(94,19);:RC13_Bit_iterator;2A.;_Bit_iterator::(94,22)=##(94,23)=*(94,19);:RC13_Bit_iterator;2A.;bump_up::(94,24)=##(0,20);:;2A.;bump_down::(94,24):;2A.;_Bit_iterator::(94,25)=##(94,23);:;2A.(94,26)=##(94,23);:PUiUi;2A.;__ml::(94,27)=##(94,1);:;2B.;__pp::(94,28)=##(94,21);:;2A.(94,29)=##(94,19);:i;2A.;__mm::(94,28):;2A.(94,29):i;2A.;__apl::(94,30)=##(94,21);:i;2A.;__ami::(94,30):i;2A.;__pl::(94,31)=##(94,19);:i;2B.;__mi::(94,31):i;2B.(94,32)=##(28,1);:G13_Bit_iterator;2B.;__vc::(94,33)=##(94,1);:i;2A.;__eq::(94,34)=##(0,19);:RC13_Bit_iterator;2B.;__ne::(94,34):RC13_Bit_iterator;2B.;__lt::(94,35)=##(0,19);:G13_Bit_iterator;2B.;; _Bit_const_iterator:Tt(94,36)=s12!1,020,(94,13);_M_p:(94,2),32,32;_M_offset:(0,4),64,32;__as::(94,37)=##(94,38)=&(94,36);:RC19_Bit_const_iterator;2A.;_Bit_const_iterator::(94,39)=##(94,40)=*(94,36);:RC19_Bit_const_iterator;2A.;bump_up::(94,41)=##(0,20);:;2A.;bump_down::(94,41):;2A.;_Bit_const_iterator::(94,42)=##(94,40);:;2A.(94,43)=##(94,40);:PUiUi;2A.(94,44)=##(94,40);:RC13_Bit_iterator;2A.;__ml::(94,45)=##(0,19);:;2B.;__pp::(94,46)=##(94,38);:;2A.(94,47)=##(94,36);:i;2A.;__mm::(94,46):;2A.(94,47):i;2A.;__apl::(94,48)=##(94,38);:i;2A.;__ami::(94,48):i;2A.;__pl::(94,49)=##(94,36);:i;2B.;__mi::(94,49):i;2B.(94,50)=##(28,1);:G19_Bit_const_iterator;2B.;__vc::(94,51)=##(0,19);:i;2A.;__eq::(94,52)=##(0,19);:RC19_Bit_const_iterator;2B.;__ne::(94,52):RC19_Bit_const_iterator;2B.;__lt::(94,53)=##(0,19);:G19_Bit_const_iterator;2B.;; bit_vector:t(94,54)=(94,55)=xsvector<bool,__default_alloc_template<true,0> >: /usr/lib/gcc-lib/i386-linux/2.95.4/../../../../include/g++-3/cmath /usr/include/math.h /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h _LIB_VERSION_TYPE:t(96,1)=e_IEEE_:-1,_SVID_:0,_XOPEN_:1,_POSIX_:2,_ISOC_:3,; __exception:Tt(96,2)=s32type:(0,1),0,32;name:(6,57),32,32;arg1:(0,13),64,64;arg2:(0,13),128,64;retval:(0,13),192,64;__as::(96,3)=##(96,4)=&(96,2);:RC11__exception;2A.;__exception::(96,5)=##(96,6)=*(96,2);:RC11__exception;2A.(96,7)=##(96,6);:;2A.;; consumer.h market.h Rep:Tt(103,1)=s16len:(11,1),0,32;res:(11,1),32,32;ref:(11,1),64,32;selfish:(0,19),96,8;Rep::(103,2)=##(103,3)=*(103,1);:__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepRCQ2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep;2A.(103,4)=##(103,3);:__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep;2A.;data::(103,5)=##(6,57);:Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep;2A.;__vc::(103,6)=##(103,7)=&(0,2);:Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUi;2A.;grab::(103,5):Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep;2A.;release::(103,8)=##(0,20);:Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep;2A.;__nw::(103,9)=f(17,29):Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUiUi;2A?;__dl::(17,27):Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepPv;2A?;create::(103,10)=f(103,3):Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUi;2A?;clone::(103,5):Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep;2A.;copy::(103,11)=##(0,20);:Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUiPCcUi;2A.;move::(103,11):Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUiPCcUi;2A.;set::(103,12)=##(0,20);:Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUicUi;2A.;excess_slop::(103,13)=f(0,19):Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUiUi;2A?;frob_size::(39,25):Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUi;2A?;__as::(103,14)=##(103,15)=&(103,1);:Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepRCQ2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep;0A.;; basic_string<char,string_char_traits<char>,__default_alloc_template<true,0> >:Tt(25,2)=s4npos:/2(11,1):_t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0.npos;nilRep:/0(103,1):_t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0.nilRep;dat:/0(6,57),0,32;rep::(103,16)=##(103,3);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;0B.;repup::(103,17)=##(0,20);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PQ2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep;0A.;data::(103,18)=##(17,38);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2B.;length::(103,19)=##(11,1);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2B.;size::(103,19):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2B.;capacity::(103,19):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2B.;max_size::(103,19):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2B.;empty::(103,20)=##(0,19);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2B.;__as::(103,21)=##(103,22)=&(25,2);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;basic_string::(103,23)=##(103,24)=*(25,2);:__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.(103,25)=##(103,24);:__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.(103,26)=##(103,24);:__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUi;2A.(103,27)=##(103,24);:__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUi;2A.(103,28)=##(103,24);:__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc;2A.(103,29)=##(103,24);:__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Uic;2A.(103,30)=#(25,2),(0,20),(103,24),(0,1),(0,20);:_._t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;swap::(103,31)=##(0,20);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Rt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;append::(103,32)=##(103,22);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUi;2A.(103,33)=##(103,22);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUi;2A.(103,34)=##(103,22);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc;2A.(103,35)=##(103,22);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Uic;2A.;push_back::(103,36)=##(0,20);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0c;2A.;assign::(103,32):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUi;2A.(103,33):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUi;2A.(103,34):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc;2A.(103,35):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Uic;2A.;__as::(103,34):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc;2A.(103,37)=##(103,22);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0c;2A.;__apl::(103,21):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.(103,34):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc;2A.(103,37):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0c;2A.;insert::(103,38)=##(103,22);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUi;2A.(103,39)=##(103,22);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiPCcUi;2A.(103,40)=##(103,22);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiPCc;2A.(103,41)=##(103,22);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUic;2A.(103,42)=##(6,57);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Pcc;2A.(103,43)=##(6,57);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcUic;2A.;erase::(103,44)=##(103,22);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUi;2A.(103,45)=##(6,57);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Pc;2A.(103,46)=##(6,57);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcT1;2A.;replace::(103,47)=##(103,22);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUiRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUi;2A.(103,48)=##(103,22);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUiPCcUi;2A.(103,49)=##(103,22);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUiPCc;2A.(103,50)=##(103,22);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUiUic;2A.(103,41):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUic;2A.(103,51)=##(103,22);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcT1RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.(103,52)=##(103,22);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcT1PCcUi;2A.(103,53)=##(103,22);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcT1PCc;2A.(103,54)=##(103,22);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcT1Uic;2A.;eos::(103,55)=f(0,2):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;0A?;unique::(103,56)=##(0,20);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;0A.;selfish::(103,56):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;0A.;__vc::(103,57)=##(0,2);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ui;2B.(103,58)=##(103,7);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ui;2A.;at::(103,58):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ui;2A.(103,59)=##(103,60)=&(0,2);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ui;2B.;terminate::(103,61)=##(0,20);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;0B.;c_str::(103,18):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2B.;resize::(103,62)=##(0,20);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Uic;2A.(103,63)=##(0,20);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ui;2A.;reserve::(103,63):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ui;2A.;copy::(103,64)=##(11,1);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcUiUi;2B.;find::(103,65)=##(11,1);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ui;2B.(103,66)=##(11,1);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUiUi;2B.(103,67)=##(11,1);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUi;2B.(103,68)=##(11,1);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0cUi;2B.;rfind::(103,69)=##(11,1);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ui;2B.(103,66):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUiUi;2B.(103,70)=##(11,1);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUi;2B.(103,71)=##(11,1);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0cUi;2B.;find_first_of::(103,65):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ui;2B.(103,66):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUiUi;2B.(103,67):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUi;2B.(103,68):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0cUi;2B.;find_last_of::(103,69):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ui;2B.(103,66):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUiUi;2B.(103,70):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUi;2B.(103,71):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0cUi;2B.;find_first_not_of::(103,65):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ui;2B.(103,66):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUiUi;2B.(103,67):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUi;2B.(103,68):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0cUi;2B.;find_last_not_of::(103,69):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ui;2B.(103,66):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUiUi;2B.(103,70):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUi;2B.(103,71):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0cUi;2B.;substr::(103,72)=##(25,2);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUi;2B.;compare::(103,73)=##(0,1);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUi;2B.(103,74)=##(0,1);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUiUi;2B.(103,75)=##(0,1);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUi;2B.;begin::(103,76)=##(6,57);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;end::(103,76):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;ibegin::(103,77)=##(6,57);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;0B.;iend::(103,77):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;0B.;begin::(103,18):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2B.;end::(103,18):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2B.;rbegin::(103,78)=##(103,79)=xsreverse_iterator<char *>:;:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.(103,80)=##(103,81)=xsreverse_iterator<const char *>:;:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2B.;rend::(103,78):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.(103,80):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2B.;alloc::(103,82)=##(0,20);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Uib;0A.;_find::(103,83)=f(11,1):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCccUiUi;0A?;check_realloc::(103,84)=##(0,19);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ui;0B.;; Market:Tt(103,85)=s44name_:/0(25,1),0,32;items_:/0(0,13),32,64;marginal_:/0(0,13),96,64;capital_:/0(0,13),160,64;price_in_:/0(0,13),224,64;price_out_:/0(0,13),288,64;__as::(103,86)=##(103,87)=&(103,85);:RC6Market;2A.;Market::(103,88)=##(103,89)=*(103,85);:RC6Market;2A.(103,90)=#(103,85),(0,20),(103,89),(0,1),(0,20);:_._6Market;2A.(103,91)=##(103,89);:;2A.(103,92)=##(103,89);:Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;info::(103,93)=##(0,20);:;2A.;get_items::(103,94)=##(0,13);:;2A.;get_marginal::(103,94):;2A.;get_capital::(103,94):;2A.;get_price_in::(103,95)=##(0,14);:;2A.;get_price_out::(103,95):;2A.;set_items::(103,96)=##(0,20);:d;2A.;set_marginal::(103,96):d;2A.;set_capital::(103,96):d;2A.;set_price_in::(103,96):d;2A.;set_price_out::(103,96):d;2A.;change_items::(103,97)=##(0,19);:d;2A.;change_marginal::(103,96):d;2A.;change_capital::(103,97):d;2A.;change_price_in::(103,96):d;2A.;change_price_out::(103,96):d;2A.;negotiate_price::(103,96):d;2A.;; Consumer:Tt(102,1)=s64motivation_:/0(0,13),0,64;skill_:/0(0,13),64,64;capital_:/0(0,13),128,64;spendwill_:/0(0,13),192,64;items_:/0(0,13),256,64;market_:/0(103,89),320,32;employed_:/0(0,19),352,8;weeks_employed_:/0(0,1),384,32;weeks_unemployed_:/0(0,1),416,32;income_:/0(0,13),448,64;__as::(102,2)=##(102,3)=&(102,1);:RC8Consumer;2A.;Consumer::(102,4)=##(102,5)=*(102,1);:RC8Consumer;2A.(102,6)=##(102,5);:;2A.(102,7)=##(102,5);:dddd;2A.(102,8)=##(102,5);:ddddP6Market;2A.;info::(102,9)=##(0,20);:;2A.;info_short::(102,9):;2A.;info_head::(102,9):;2A.;get_motivation::(102,10)=##(0,13);:;2A.;get_skill::(102,10):;2A.;get_capital::(102,10):;2A.;get_spendwill::(102,10):;2A.;get_income::(102,10):;2A.;get_items::(102,10):;2A.;get_employment_status::(102,11)=##(0,19);:;2A.;set_motivation::(102,12)=##(0,20);:d;2A.;set_skill::(102,12):d;2A.;set_capital::(102,12):d;2A.;set_spedwill::(102,12):d;2A.;set_income::(102,12):d;2A.;set_employment_status::(102,13)=##(0,20);:b;2A.;set_items::(102,12):d;2A.;change_motivation::(102,12):d;2A.;change_skill::(102,12):d;2A.;change_capital::(102,12):d;2A.;change_spendwill::(102,12):d;2A.;change_income::(102,12):d;2A.;change_items::(102,12):d;2A.;update_values::(102,9):;2A.;update_capital::(102,9):;2A.;update_skill::(102,9):;2A.;update_spendwill::(102,9):;2A.;update_motivation::(102,9):;2A.;buy::(102,9):;2A.;; consumer_list.h element_consumer.h Element_consumer:Tt(105,1)=s8next_:(105,2)=*(105,1),0,32;consumer_:(102,5),32,32;__as::(105,3)=##(105,4)=&(105,1);:RC16Element_consumer;2A.;Element_consumer::(105,5)=##(105,2);:RC16Element_consumer;2A.(105,6)=##(105,2);:;2A.(105,7)=##(105,2);:P16Element_consumerP8Consumer;2A.;get_consumer::(105,8)=##(102,5);:;2A.;get_motivation::(105,9)=##(0,13);:;2A.;get_skill::(105,9):;2A.;get_capital::(105,9):;2A.;get_spendwill::(105,9):;2A.;get_income::(105,9):;2A.;get_employment_status::(105,10)=##(0,19);:;2A.;set_employment_status::(105,11)=##(0,20);:b;2A.;; Consumer_list:Tt(104,1)=s12name_:/1(25,1),0,32;list_:/1(105,2),32,32;size_:/1(0,1),64,32;__as::(104,2)=##(104,3)=&(104,1);:RC13Consumer_list;2A.;Consumer_list::(104,4)=##(104,5)=*(104,1);:RC13Consumer_list;2A.(104,6)=#(104,1),(0,20),(104,5),(0,1),(0,20);:_._13Consumer_list;2A.(104,7)=##(104,5);:;2A.(104,8)=##(104,5);:Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;info::(104,9)=##(0,20);:;2A.;get_size::(104,10)=##(0,1);:;2A.;get_skill_sum::(104,11)=##(0,13);:;2A.;get_motivation_sum::(104,11):;2A.;get_capital_sum::(104,11):;2A.;get_spendwill_sum::(104,11):;2A.;get_item_sum::(104,11):;2A.;get_employed::(104,10):;2A.;get_unemployed::(104,10):;2A.;get_random_consumer::(104,12)=##(102,5);:;2A.;set_name::(104,13)=##(0,20);:Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;add_first::(104,14)=##(0,20);:P8Consumer;2A.;add_last::(104,14):P8Consumer;2A.;add_group_last::(104,15)=##(0,20);:P16Element_consumer;2A.;empty_list::(104,9):;2A.;print_list::(104,9):;2A.;remove_consumer::(104,14):P8Consumer;2A.;remove_by_skill::(104,16)=##(0,20);:d;2A.;remove_by_motivation::(104,16):d;2A.;get_optimal_consumer::(104,17)=##(102,5);:dd;2A.;get_usless_employee::(104,17):dd;2A.;get_motivated_consumers::(104,18)=##(105,2);:;2A.;update::(104,9):;2A.;pay_employees::(104,19)=##(0,20);:ddd;2A.(104,16):d;2A.;consumers_buy::(104,9):;2A.;; city.h company_list.h company.h Company:Tt(108,1)=s60name_:/0(25,1),0,32;capital_:/0(0,13),32,64;stock_:/0(0,13),96,64;invest_:/0(0,13),160,64;employees_:/0(104,5),224,32;market_:/0(103,89),256,32;prod_const_skill_:/0(0,13),288,64;prod_const_motivation_:/0(0,13),352,64;wage_const_:/0(0,13),416,64;__as::(108,2)=##(108,3)=&(108,1);:RC7Company;2A.;Company::(108,4)=##(108,5)=*(108,1);:RC7Company;2A.(108,6)=#(108,1),(0,20),(108,5),(0,1),(0,20);:_._7Company;2A.(108,7)=##(108,5);:;2A.(108,8)=##(108,5);:Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.(108,9)=##(108,5);:Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0P6Market;2A.;info::(108,10)=##(0,20);:;2A.;employee_info::(108,10):;2A.;get_name::(108,11)=##(25,1);:;2A.;get_capital::(108,12)=##(0,13);:;2A.;get_prod_const_skill::(108,12):;2A.;get_prod_const_motivation::(108,12):;2A.;get_wage_const::(108,12):;2A.;get_production::(108,12):;2A.(108,13)=##(0,13);:P8Consumer;2A.;get_stock::(108,12):;2A.;get_invest::(108,12):;2A.;set_capital::(108,14)=##(0,20);:d;2A.;set_prod_const_skill::(108,14):d;2A.;set_prod_const_motivation::(108,14):d;2A.;set_wage_const::(108,14):d;2A.;set_stock::(108,14):d;2A.;set_invest::(108,14):d;2A.;change_capital::(108,14):d;2A.;change_prod_const_skill::(108,14):d;2A.;change_prod_const_motivation::(108,14):d;2A.;change_wage_const::(108,14):d;2A.;change_stock::(108,14):d;2A.;change_invest::(108,14):d;2A.;add_employee::(108,15)=##(0,20);:P8Consumer;2A.;remove_employee::(108,15):P8Consumer;2A.;update_employees::(108,16)=##(0,20);:dd;2A.;print_employees::(108,10):;2A.;sell_to_market::(108,10):;2A.;contribution_adding::(108,13):P8Consumer;2A.;contribution_removing::(108,13):P8Consumer;2A.;update_employees::(108,17)=##(0,19);:P8Consumer;2A.;produce::(108,10):;2A.;pay_employees::(108,10):;2A.;invest::(108,10):;2A.;; element_company.h Element_company:Tt(109,1)=s8next_:(109,2)=*(109,1),0,32;company_:(108,5),32,32;__as::(109,3)=##(109,4)=&(109,1);:RC15Element_company;2A.;Element_company::(109,5)=##(109,2);:RC15Element_company;2A.(109,6)=##(109,2);:;2A.(109,7)=##(109,2);:P15Element_companyP7Company;2A.;get_name::(109,8)=##(25,1);:;2A.;get_company::(109,9)=##(108,5);:;2A.;; Company_list:Tt(107,1)=s12name_:/0(25,1),0,32;list_:/0(109,2),32,32;size_:/0(0,1),64,32;__as::(107,2)=##(107,3)=&(107,1);:RC12Company_list;2A.;Company_list::(107,4)=##(107,5)=*(107,1);:RC12Company_list;2A.(107,6)=#(107,1),(0,20),(107,5),(0,1),(0,20);:_._12Company_list;2A.(107,7)=##(107,5);:;2A.(107,8)=##(107,5);:Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.(107,9)=##(107,5);:P7Company;2A.;info::(107,10)=##(0,20);:;2A.;employee_info::(107,11)=##(0,20);:Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;add_company::(107,12)=##(0,20);:P7Company;2A.;add_employee::(107,13)=##(0,20);:Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0P8Consumer;2A.;print_list::(107,10):;2A.;print_employees::(107,11):Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;sell_to_market::(107,10):;2A.;get_company::(107,14)=##(108,5);:Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;get_random_company::(107,15)=##(109,2);:;2A.;update_company_employees::(107,10):;2A.;produce::(107,10):;2A.;update_employees::(107,16)=##(0,19);:P8ConsumerGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.(107,17)=##(0,19);:P8Consumer;2A.;update_employees2::(107,17):P8Consumer;2A.;pay_employees::(107,10):;2A.;invest::(107,10):;2A.;get_capital_sum::(107,18)=##(0,13);:;2A.;get_item_sum::(107,18):;2A.;; City:Tt(106,1)=s20name_:/0(25,1),0,32;consumers_:/0(104,5),32,32;labour_market_:/0(104,5),64,32;company_list_:/0(107,5),96,32;market_:/0(103,89),128,32;__as::(106,2)=##(106,3)=&(106,1);:RC4City;2A.;City::(106,4)=##(106,5)=*(106,1);:RC4City;2A.(106,6)=#(106,1),(0,20),(106,5),(0,1),(0,20);:_._4City;2A.(106,7)=##(106,5);:;2A.(106,8)=##(106,5);:Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;info::(106,9)=##(0,20);:;2A.;get_market::(106,10)=##(103,89);:;2A.;update_market::(106,9):;2A.;negotiate_market_price::(106,9):;2A.;market_info::(106,9):;2A.;employee_info::(106,9):;2A.(106,11)=##(0,20);:Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;follow_capital::(106,12)=##(0,20);:P8Consumer;2A.(106,9):;2A.;sell_to_market::(106,9):;2A.;set_consumers::(106,13)=##(0,20);:P13Consumer_list;2A.;set_companies::(106,14)=##(0,20);:P12Company_list;2A.;set_labour_market::(106,13):P13Consumer_list;2A.;add_consumer::(106,15)=##(0,20);:dddd;2A.(106,12):P8Consumer;2A.;add_company::(106,11):Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;add_employee::(106,16)=##(0,20);:Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0P8Consumer;2A.;print_company_info::(106,11):Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;update_consumer_list::(106,9):;2A.;print_consumer_list::(106,9):;2A.;print_company_list::(106,9):;2A.;print_employees::(106,11):Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;print_labour_market::(106,9):;2A.;consumer_info::(106,9):;2A.;labour_info::(106,9):;2A.;get_company::(106,17)=##(108,5);:Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;get_random_consumer::(106,18)=##(102,5);:;2A.;get_motivated_consumers::(106,19)=##(105,2);:;2A.;remove_consumer_from_labour_market::(106,12):P8Consumer;2A.;add_motivated_consumers::(106,20)=##(0,20);:P16Element_consumer;2A.;update_company_employees::(106,9):;2A.;update_employees::(106,11):Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;produce::(106,9):;2A.;pay_company_employees::(106,9):;2A.;consumers_buy::(106,9):;2A.;invest::(106,9):;2A.;get_capital_sum::(106,21)=##(0,13);:;2A.;get_optimal_consumer::(106,22)=##(102,5);:dd;2A.;; element.h Element:Tt(110,1)=s8next_:(110,2)=*(110,1),0,32;cons_:(102,5),32,32;__as::(110,3)=##(110,4)=&(110,1);:RC7Element;2A.;Element::(110,5)=##(110,2);:RC7Element;2A.(110,6)=##(110,2);:P7ElementP8Consumer;2A.;; functions.h _Lock:Tt(0,24)=s1__as::(0,25)=##(0,26)=&(0,24);:Q2t24__default_alloc_template2b1i0_5_LockRCQ2t24__default_alloc_template2b1i0_5_Lock;2A.;_Lock::(0,27)=##(0,28)=*(0,24);:__Q2t24__default_alloc_template2b1i0_5_LockRCQ2t24__default_alloc_template2b1i0_5_Lock;2A.(0,29)=##(0,28);:__Q2t24__default_alloc_template2b1i0_5_Lock;2A.(0,30)=#(0,24),(0,20),(0,28),(0,1),(0,20);:_._Q2t24__default_alloc_template2b1i0_5_Lock;2A.;; _Obj:Tt(39,19)=u4_M_free_list_link:(39,18),0,32;_M_client_data:(4,11),0,8;__as::(0,31)=##(0,32)=&(39,19);:Q2t24__default_alloc_template2b1i0_4_ObjRCQ2t24__default_alloc_template2b1i0_4_Obj;2A.;_Obj::(0,33)=##(39,18);:__Q2t24__default_alloc_template2b1i0_4_ObjRCQ2t24__default_alloc_template2b1i0_4_Obj;2A.(0,34)=##(39,18);:__Q2t24__default_alloc_template2b1i0_4_Obj;2A.;; main:F(0,1) b1:(25,1) b2:(25,1) b3:(25,1) b4:(25,1) b5:(25,1) b6:(25,1) bennyland:(106,1) workers:(105,2) random:(102,5) sum_before:(0,13) test:(0,1) sum_after:(0,13) i:(0,1) benny:(102,5) j:(0,1) lexicographical_compare__H2ZPCScZPCSc_X01X01X11X11_b:F(0,19) __first1:p(0,35)=*(0,10) __last1:p(0,35) __first2:p(0,35) __last2:p(0,35) __lexicographical_compare_3way__H2ZPCScZPCSc_X01X01X11X11_i:F(0,1) __first1:p(0,35) _t24__default_alloc_template2b1i0._S_free_list:G(39,17) _t24__default_alloc_template2b1i0._S_node_allocator_lock:G(55,35) _t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0.nilRep:G(103,1) frob_size__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUi:F(11,1) s:p(11,1) s:r(11,1) i:(11,1) _t23__malloc_alloc_template1i0.__malloc_alloc_oom_handler:G(42,2) __9bad_alloc:F(0,36)=*(0,37)=xsbad_alloc: this:p(0,36) this:r(0,36) __9exceptionRC9exception:F(0,38)=*(0,39)=xsexception: this:p(0,38) _ctor_arg:p(0,40)=&(0,39) this:r(0,38) _ctor_arg:r(0,40) __9bad_allocRC9bad_alloc:F(0,36) _ctor_arg:p(0,41)=&(0,37) _ctor_arg:r(0,41) _S_oom_malloc__t23__malloc_alloc_template1i0Ui:F(17,29) __n:p(11,1) __my_malloc_handler:(42,2) __result:(17,29) allocate__t23__malloc_alloc_template1i0Ui:F(17,29) __n:r(11,1) _S_round_up__t24__default_alloc_template2b1i0Ui:F(11,1) __bytes:p(11,1) __bytes:r(11,1) _t24__default_alloc_template2b1i0._S_start_free:G(6,57) _t24__default_alloc_template2b1i0._S_end_free:G(6,57) _t24__default_alloc_template2b1i0._S_heap_size:G(11,1) _S_chunk_alloc__t24__default_alloc_template2b1i0UiRi:F(6,57) __size:p(11,1) __nobjs:p(0,42)=&(0,1) __result:(6,57) __total_bytes:(11,1) __bytes_left:(11,1) __bytes_to_get:(11,1) __my_free_list:(0,43)=*(39,18) __i:(11,1) __my_free_list:(0,43) __p:(39,18) _S_refill__t24__default_alloc_template2b1i0Ui:F(17,29) __nobjs:(0,1) __chunk:(6,57) __result:(39,18) __current_obj:(39,18) __next_obj:(39,18) __i:(0,1) allocate__t24__default_alloc_template2b1i0Ui:F(17,29) __lock_instance:(0,24) __r:(17,29) __nw__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUiUi:F(17,29) extra:p(11,1) extra:r(11,1) create__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUi:F(103,3) p:(103,3) copy__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUiPCcUi:F(0,20) this:p(103,3) pos:p(11,1) s:p(17,38) n:p(11,1) this:r(103,3) pos:r(11,1) s:r(17,38) clone__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep:F(6,57) length__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0:F(11,1) this:p(0,44)=*(25,2) this:r(0,44) max_size__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0:F(11,1) this:p(0,44) capacity__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0:F(11,1) excess_slop__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUiUi:F(0,19) r:p(11,1) r:r(11,1) check_realloc__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ui:F(0,19) data__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0:F(17,38) repup__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PQ2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep:F(0,20) this:p(103,24) p:p(103,3) this:r(103,24) p:r(103,3) move__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUiPCcUi:F(0,20) replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUiPCcUi:F(103,22) n1:p(11,1) n2:p(11,1) len:(11,1) newlen:(11,1) _._4City:F(0,20) this:p(106,5) __in_chrg:p(0,1) this:r(106,5) __in_chrg:r(0,1) rep__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0:F(103,3) _S_freelist_index__t24__default_alloc_template2b1i0Ui:F(11,1) _._Q2t24__default_alloc_template2b1i0_5_Lock:F(0,20) this:p(0,28) this:r(0,28) __Q2t24__default_alloc_template2b1i0_5_Lock:F(0,28) release__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep:F(0,20) _._t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0:F(0,20) data__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep:F(6,57) __t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc:F(103,24) __t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0:F(103,24) _str:p(0,45)=&(25,2) _str:r(0,45) __WORD_BIT:S(0,1) _t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0.npos:G(11,1) __dl__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepPv:F(0,20) ptr:p(17,29) ptr:r(17,29) grab__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep:F(6,57) assign__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc:F(103,22) deallocate__t24__default_alloc_template2b1i0PvUi:F(0,20) __p:p(17,29) __p:r(17,29) __q:(39,18) assign__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUi:F(103,22) n:r(11,1) deallocate__t23__malloc_alloc_template1i0PvUi:F(0,20) city.cc error_no_return.h /usr/lib/gcc-lib/i386-linux/2.95.4/../../../../include/g++-3/stdexcept _Lock:Tt(105,1)=s1__as::(105,2)=##(105,3)=&(105,1);:Q2t24__default_alloc_template2b1i0_5_LockRCQ2t24__default_alloc_template2b1i0_5_Lock;2A.;_Lock::(105,4)=##(105,5)=*(105,1);:__Q2t24__default_alloc_template2b1i0_5_LockRCQ2t24__default_alloc_template2b1i0_5_Lock;2A.(105,6)=##(105,5);:__Q2t24__default_alloc_template2b1i0_5_Lock;2A.(105,7)=#(105,1),(0,20),(105,5),(0,1),(0,20);:_._Q2t24__default_alloc_template2b1i0_5_Lock;2A.;; _Obj:Tt(39,19)=u4_M_free_list_link:(39,18),0,32;_M_client_data:(4,11),0,8;__as::(105,8)=##(105,9)=&(39,19);:Q2t24__default_alloc_template2b1i0_4_ObjRCQ2t24__default_alloc_template2b1i0_4_Obj;2A.;_Obj::(105,10)=##(39,18);:__Q2t24__default_alloc_template2b1i0_4_ObjRCQ2t24__default_alloc_template2b1i0_4_Obj;2A.(105,11)=##(39,18);:__Q2t24__default_alloc_template2b1i0_4_Obj;2A.;; no_return_error:Tt(104,1)=s8!1,020,(104,2)=xsruntime_error:;__as::(104,3)=##(104,4)=&(104,1);:RC15no_return_error;2A.;no_return_error::(104,5)=##(104,6)=*(104,1);:RC15no_return_error;2A.(104,7)=#(104,1),(0,20),(104,6),(0,1),(0,20);:_._15no_return_error;2A*2;(104,8)=xsexception:;(104,9)=##(104,6);:RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;;~%(104,8); __4City:F(98,5) this:p(98,5) this:r(98,5) __4CityGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0:F(98,5) name:p(25,1) name:r(0,24)=*(25,1) consumer_info__4City:F(0,20) labour_info__4City:F(0,20) employee_info__4City:F(0,20) print_company_list__4City:F(0,20) employee_info__4CityGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0:F(0,20) command:p(25,1) command:r(0,25)=*(25,1) follow_capital__4CityP8Consumer:F(0,20) consumer:p(95,5) follow_capital__4City:F(0,20) get_market__4City:F(96,89) get_random_consumer__4City:F(95,5) get_capital_sum__4City:F(0,13) csum:(0,13) update_market__4City:F(0,20) marginal_:(0,13) consumers_nr:(0,1) capital_sum:(0,13) spendwill_sum:(0,13) average_spendwill:(0,13) items:(0,13) price_out:(0,13) price_in:(0,13) negotiate_market_price__4City:F(0,20) market_info__4City:F(0,20) sell_to_market__4City:F(0,20) set_consumers__4CityP13Consumer_list:F(0,20) consumer_list:p(99,5) set_companies__4CityP12Company_list:F(0,20) company_list:p(101,5) set_labour_market__4CityP13Consumer_list:F(0,20) labour_market:p(99,5) add_consumer__4Citydddd:F(0,20) motivation:p(0,13) skill:p(0,13) capital:p(0,13) spendwill:p(0,13) consumer:(95,5) add_consumer__4CityP8Consumer:F(0,20) add_company__4CityGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0:F(0,20) name:r(0,26)=*(25,1) company:(102,5) info__4City:F(0,20) print_consumer_list__4City:F(0,20) print_employees__4CityGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0:F(0,20) company:p(25,1) company:r(0,27)=*(25,1) print_labour_market__4City:F(0,20) update_consumer_list__4City:F(0,20) get_company__4CityGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0:F(102,5) name:r(0,28)=*(25,1) get_motivated_consumers__4City:F(100,2) add_motivated_consumers__4CityP16Element_consumer:F(0,20) workers:p(100,2) add_employee__4CityGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0P8Consumer:F(0,20) name:r(0,29)=*(25,1) remove_consumer_from_labour_market__4CityP8Consumer:F(0,20) update_company_employees__4City:F(0,20) update_employees__4CityGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0:F(0,20) name:r(0,30)=*(25,1) skill:(0,13) mot:(0,13) opt:(95,5) produce__4City:F(0,20) pay_company_employees__4City:F(0,20) get_optimal_consumer__4Citydd:F(95,5) mot_we:p(0,13) skill_we:p(0,13) __exception_info:(0,31)=*(0,32)=xscp_eh_info: consumers_buy__4City:F(0,20) invest__4City:F(0,20) __first1:p(0,33)=*(0,10) __last1:p(0,33) __first2:p(0,33) __last2:p(0,33) __first1:p(0,33) __9bad_alloc:F(0,34)=*(0,35)=xsbad_alloc: this:p(0,34) this:r(0,34) __9bad_allocRC9bad_alloc:F(0,34) _ctor_arg:p(0,36)=&(0,35) _ctor_arg:r(0,36) __nobjs:p(0,37)=&(0,1) __my_free_list:(0,38)=*(39,18) __my_free_list:(0,38) __lock_instance:(105,1) create__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUi:F(96,3) p:(96,3) this:p(96,3) this:r(96,3) _t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0.nilRep:G(96,1) this:p(0,39)=*(25,2) this:r(0,39) this:p(0,39) this:p(96,24) p:p(96,3) this:r(96,24) p:r(96,3) replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUiPCcUi:F(96,22) __ls__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_R7ostreamRCt12basic_string3ZX01ZX11ZX21_R7ostream:F(2,14) o:p(2,14) s:p(0,40)=&(25,2) __ti15no_return_error:G(0,41)=ar(0,1);0;11;(0,11) __tf15no_return_error:F(0,42)=&(0,43)=xstype_info: __9exceptionRC9exception:F(0,44)=*(104,8) _ctor_arg:p(0,45)=&(104,8) _ctor_arg:r(0,45) rep__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0:F(96,3) __t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0:F(96,24) _str:p(0,40) _str:r(0,40) this:p(105,5) this:r(105,5) __Q2t24__default_alloc_template2b1i0_5_Lock:F(105,5) _._15no_return_error:F(0,20) this:p(104,6) this:r(104,6) __15no_return_errorRC15no_return_error:F(104,6) _ctor_arg:p(0,46)=&(104,1) _ctor_arg:r(0,46) __t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc:F(96,24) __vt_15no_return_error:G(0,47)=ar(0,1);0;4;(0,22) _._13runtime_error:F(0,20) this:p(0,48)=*(104,2) this:r(0,48) __13runtime_errorRC13runtime_error:F(0,48) this:p(0,48) _ctor_arg:p(0,49)=&(104,2) _ctor_arg:r(0,49) assign__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc:F(96,22) assign__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUi:F(96,22) consumer.cc Company_list:Tt(101,1)=s12name_:/0(25,1),0,32;list_:/0(103,2),32,32;size_:/0(0,1),64,32;__as::(101,2)=##(101,3)=&(101,1);:RC12Company_list;2A.;Company_list::(101,4)=##(101,5)=*(101,1);:RC12Company_list;2A.(101,6)=#(101,1),(0,20),(101,5),(0,1),(0,20);:_._12Company_list;2A.(101,7)=##(101,5);:;2A.(101,8)=##(101,5);:Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.(101,9)=##(101,5);:P7Company;2A.;info::(101,10)=##(0,20);:;2A.;employee_info::(101,11)=##(0,20);:Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;add_company::(101,12)=##(0,20);:P7Company;2A.;add_employee::(101,13)=##(0,20);:Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0P8Consumer;2A.;print_list::(101,10):;2A.;print_employees::(101,11):Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;sell_to_market::(101,10):;2A.;get_company::(101,14)=##(102,5);:Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;get_random_company::(101,15)=##(103,2);:;2A.;update_company_employees::(101,10):;2A.;produce::(101,10):;2A.;update_employees::(101,16)=##(0,19);:P8ConsumerGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.(101,17)=##(0,19);:P8Consumer;2A.;update_employees2::(101,17):P8Consumer;2A.;invest::(101,10):;2A.;get_capital_sum::(101,18)=##(0,13);:;2A.;get_item_sum::(101,18):;2A.;; City:Tt(98,1)=s20name_:/0(25,1),0,32;consumers_:/0(99,5),32,32;labour_market_:/0(99,5),64,32;company_list_:/0(101,5),96,32;market_:/0(97,89),128,32;__as::(98,2)=##(98,3)=&(98,1);:RC4City;2A.;City::(98,4)=##(98,5)=*(98,1);:RC4City;2A.(98,6)=#(98,1),(0,20),(98,5),(0,1),(0,20);:_._4City;2A.(98,7)=##(98,5);:;2A.(98,8)=##(98,5);:Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;info::(98,9)=##(0,20);:;2A.;get_market::(98,10)=##(97,89);:;2A.;update_market::(98,9):;2A.;negotiate_market_price::(98,9):;2A.;market_info::(98,9):;2A.;employee_info::(98,9):;2A.(98,11)=##(0,20);:Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;follow_capital::(98,12)=##(0,20);:P8Consumer;2A.(98,9):;2A.;sell_to_market::(98,9):;2A.;set_consumers::(98,13)=##(0,20);:P13Consumer_list;2A.;set_companies::(98,14)=##(0,20);:P12Company_list;2A.;set_labour_market::(98,13):P13Consumer_list;2A.;add_consumer::(98,15)=##(0,20);:dddd;2A.(98,12):P8Consumer;2A.;add_company::(98,11):Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;add_employee::(98,16)=##(0,20);:Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0P8Consumer;2A.;print_company_info::(98,11):Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;update_consumer_list::(98,9):;2A.;print_consumer_list::(98,9):;2A.;print_company_list::(98,9):;2A.;print_employees::(98,11):Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;print_labour_market::(98,9):;2A.;consumer_info::(98,9):;2A.;labour_info::(98,9):;2A.;get_company::(98,17)=##(102,5);:Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;get_random_consumer::(98,18)=##(96,5);:;2A.;get_motivated_consumers::(98,19)=##(100,2);:;2A.;remove_consumer_from_labour_market::(98,12):P8Consumer;2A.;add_motivated_consumers::(98,20)=##(0,20);:P16Element_consumer;2A.;update_company_employees::(98,9):;2A.;update_employees::(98,11):Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;produce::(98,9):;2A.;consumers_buy::(98,9):;2A.;invest::(98,9):;2A.;get_capital_sum::(98,21)=##(0,13);:;2A.;get_optimal_consumer::(98,22)=##(96,5);:dd;2A.;; __8Consumer:F(96,5) this:p(96,5) this:r(96,5) __8Consumerdddd:F(96,5) mot:p(0,13) sk:p(0,13) cap:p(0,13) spe:p(0,13) __8ConsumerddddP6Market:F(96,5) m:p(97,89) info__8Consumer:F(0,20) info_head__8Consumer:F(0,20) space:(0,1) info_short__8Consumer:F(0,20) employed:(25,1) get_motivation__8Consumer:F(0,13) get_skill__8Consumer:F(0,13) get_capital__8Consumer:F(0,13) get_spendwill__8Consumer:F(0,13) get_income__8Consumer:F(0,13) get_employment_status__8Consumer:F(0,19) get_items__8Consumer:F(0,13) set_motivation__8Consumerd:F(0,20) set_skill__8Consumerd:F(0,20) skil:p(0,13) set_capital__8Consumerd:F(0,20) set_spedwill__8Consumerd:F(0,20) spendw:p(0,13) set_income__8Consumerd:F(0,20) income:p(0,13) set_employment_status__8Consumerb:F(0,20) employed:p(0,19) set_items__8Consumerd:F(0,20) items:p(0,13) change_motivation__8Consumerd:F(0,20) change_skill__8Consumerd:F(0,20) change_capital__8Consumerd:F(0,20) change_spendwill__8Consumerd:F(0,20) change_income__8Consumerd:F(0,20) income_ch:p(0,13) change_items__8Consumerd:F(0,20) ch:p(0,13) update_values__8Consumer:F(0,20) update_capital__8Consumer:F(0,20) update_skill__8Consumer:F(0,20) skill_change:(0,1) EMP_CONST:(0,13) emp:(0,19) update_spendwill__8Consumer:F(0,20) update_motivation__8Consumer:F(0,20) MOTIVATION_CAP_CONST:(0,13) buy__8Consumer:F(0,20) FEL_STALLE:(0,13) amount:(0,13) price:(0,13) quantity:(0,13) _t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0.nilRep:G(97,1) create__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUi:F(97,3) p:(97,3) this:p(97,3) this:r(97,3) this:p(97,24) p:p(97,3) this:r(97,24) p:r(97,3) replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUiPCcUi:F(97,22) s:p(0,45)=&(25,2) rep__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0:F(97,3) __t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc:F(97,24) __as__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc:F(97,22) assign__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc:F(97,22) assign__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUi:F(97,22) consumer_list.cc __13Consumer_list:F(98,5) __13Consumer_listGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0:F(98,5) name_string:p(25,1) name_string:r(0,24)=*(25,1) info__13Consumer_list:F(0,20) total_cap:(0,13) total_mot:(0,13) total_spendwill:(0,13) total_items:(0,13) employed:(0,1) unemployed:(0,1) get_size__13Consumer_list:F(0,1) get_item_sum__13Consumer_list:F(0,13) p:(77,2) sum:(0,13) get_skill_sum__13Consumer_list:F(0,13) get_capital_sum__13Consumer_list:F(0,13) get_spendwill_sum__13Consumer_list:F(0,13) get_motivation_sum__13Consumer_list:F(0,13) get_employed__13Consumer_list:F(0,1) no:(0,1) get_unemployed__13Consumer_list:F(0,1) get_random_consumer__13Consumer_list:F(78,5) nr:(0,1) set_name__13Consumer_listGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0:F(0,20) name_string:r(0,25)=*(25,1) add_first__13Consumer_listP8Consumer:F(0,20) cons:p(78,5) add_last__13Consumer_listP8Consumer:F(0,20) print_list__13Consumer_list:F(0,20) update__13Consumer_list:F(0,20) get_motivated_consumers__13Consumer_list:F(77,2) lista:(77,2) add_group_last__13Consumer_listP16Element_consumer:F(0,20) workers:p(77,2) test:(77,2) size:(0,1) remove_consumer__13Consumer_listP8Consumer:F(0,20) consumer:p(78,5) remove_by_skill__13Consumer_listd:F(0,20) skill_limit:p(0,13) remove_by_motivation__13Consumer_listd:F(0,20) motivation_limit:p(0,13) get_optimal_consumer__13Consumer_listdd:F(78,5) best:(77,2) consumer:(78,5) besta:(78,5) get_usless_employee__13Consumer_listdd:F(78,5) worst:(77,2) pay_employees__13Consumer_listddd:F(0,20) skill_c:p(0,13) mot_c:p(0,13) wage_c:p(0,13) wage:(0,13) pay_employees__13Consumer_listd:F(0,20) wage:p(0,13) consumers_buy__13Consumer_list:F(0,20) __first1:p(0,26)=*(0,10) __last1:p(0,26) __first2:p(0,26) __last2:p(0,26) __first1:p(0,26) __9bad_alloc:F(0,27)=*(0,28)=xsbad_alloc: this:p(0,27) this:r(0,27) __9bad_allocRC9bad_alloc:F(0,27) _ctor_arg:p(0,29)=&(0,28) _ctor_arg:r(0,29) __nobjs:p(0,30)=&(0,1) __my_free_list:(0,31)=*(39,18) __my_free_list:(0,31) __lock_instance:(100,1) this:p(0,32)=*(25,2) this:r(0,32) this:p(0,32) s:p(0,33)=&(25,2) __9exceptionRC9exception:F(0,34)=*(99,8) _ctor_arg:p(0,35)=&(99,8) _ctor_arg:r(0,35) __t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0:F(97,24) _str:p(0,33) _str:r(0,33) this:p(100,5) this:r(100,5) __Q2t24__default_alloc_template2b1i0_5_Lock:F(100,5) this:p(99,6) this:r(99,6) __15no_return_errorRC15no_return_error:F(99,6) _ctor_arg:p(0,36)=&(99,1) __15no_return_errorRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0:F(99,6) what_arg:p(0,37)=&(25,1) what_arg:r(0,37) __as__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0:F(97,22) str:p(0,33) str:r(0,33) __vt_15no_return_error:G(0,38)=ar(0,1);0;4;(0,22) __ti15no_return_error:G(0,39)=ar(0,1);0;11;(0,11) __tf15no_return_error:F(0,40)=&(0,41)=xstype_info: this:p(0,42)=*(99,2) this:r(0,42) __13runtime_errorRC13runtime_error:F(0,42) this:p(0,42) _ctor_arg:p(0,43)=&(99,2) _ctor_arg:r(0,43) functions.cc /usr/lib/gcc-lib/i386-linux/2.95.4/../../../../include/g++-3/cstdlib /usr/lib/gcc-lib/i386-linux/2.95.4/../../../../include/g++-3/ctime randomize__FRdd:F(0,20) average:p(0,24)=&(0,13) deviation:p(0,13) randsign:(0,1) randv:(0,13) limit:(0,13) normalize__FRd:F(0,20) value:p(0,24) get_norm__Fdd:F(0,13) average:p(0,13) randvalue:(0,13) get_prod__Fddddd:F(0,13) sk_sum:p(0,13) mot_sum:p(0,13) employees:p(0,13) capacity:(0,13) rate:(0,13) prod:(0,13) get_prod__FP8Consumer:F(0,13) consumer:p(105,5) get_price__Fd:F(0,13) excess:p(0,13) P_MAX:(0,13) P_SENS:(0,13) get_price__Fdd:F(0,13) sum_spend:p(0,13) random_consumer__FP6Market:F(105,5) market:p(106,89) sk:(0,13) cap:(0,13) spe:(0,13) __first1:p(0,25)=*(0,10) __last1:p(0,25) __first2:p(0,25) __last2:p(0,25) __first1:p(0,25) company.cc __7Company:F(97,5) this:p(97,5) this:r(97,5) __7CompanyGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0P6Market:F(97,5) market:p(96,89) name:r(0,35)=*(25,1) info__7Company:F(0,20) employee_info__7Company:F(0,20) get_name__7Company:F(25,1) get_capital__7Company:F(0,13) get_prod_const_skill__7Company:F(0,13) get_prod_const_motivation__7Company:F(0,13) get_wage_const__7Company:F(0,13) get_production__7Company:F(0,13) skill_sum:(0,13) mot_sum:(0,13) employees:(0,13) get_production__7CompanyP8Consumer:F(0,13) get_stock__7Company:F(0,13) get_invest__7Company:F(0,13) set_capital__7Companyd:F(0,20) set_prod_const_skill__7Companyd:F(0,20) set_prod_const_motivation__7Companyd:F(0,20) set_wage_const__7Companyd:F(0,20) wc:p(0,13) set_stock__7Companyd:F(0,20) stock:p(0,13) set_invest__7Companyd:F(0,20) invest:p(0,13) change_capital__7Companyd:F(0,20) change_prod_const_skill__7Companyd:F(0,20) change_prod_const_motivation__7Companyd:F(0,20) change_wage_const__7Companyd:F(0,20) wcc:p(0,13) change_stock__7Companyd:F(0,20) change_invest__7Companyd:F(0,20) add_employee__7CompanyP8Consumer:F(0,20) print_employees__7Company:F(0,20) produce__7Company:F(0,20) pay_employees__7Company:F(0,20) production:(0,13) size:(0,13) sum_bef:(0,13) wage_tot:(0,13) wage_tot2:(0,13) contribution_adding__7CompanyP8Consumer:F(0,13) employees:(0,1) sk_c:(0,13) mot_c:(0,13) prod_before:(0,13) prod_after:(0,13) contribution:(0,13) contribution_removing__7CompanyP8Consumer:F(0,13) update_employees__7CompanyP8Consumer:F(0,19) opt:p(95,5) bad_empl:(95,5) add:(0,13) rem:(0,13) update_employees__7Companydd:F(0,20) remove_employee__7CompanyP8Consumer:F(0,20) sell_to_market__7Company:F(0,20) invest__7Company:F(0,20) investment:(0,13) __first1:p(0,36)=*(0,10) __last1:p(0,36) __first2:p(0,36) __last2:p(0,36) __first1:p(0,36) __9bad_alloc:F(0,37)=*(0,38)=xsbad_alloc: this:p(0,37) this:r(0,37) __9exceptionRC9exception:F(0,39)=*(0,40)=xsexception: _ctor_arg:p(0,41)=&(0,40) __9bad_allocRC9bad_alloc:F(0,37) _ctor_arg:p(0,42)=&(0,38) _ctor_arg:r(0,42) __nobjs:p(0,43)=&(0,1) __my_free_list:(0,44)=*(39,18) __my_free_list:(0,44) this:p(0,45)=*(25,2) this:r(0,45) this:p(0,45) s:p(0,46)=&(25,2) _str:p(0,46) _str:r(0,46) company_list.cc basic_string<char,string_char_traits<char>,__default_alloc_template<true,0> >:Tt(25,2)=s4npos:/2(11,1):_t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0.npos;nilRep:/0(95,1)=xsRep::_t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0.nilRep;dat:/0(6,57),0,32;rep::(95,2)=##(95,3)=*(95,1);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;0B.;repup::(95,4)=##(0,20);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PQ2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep;0A.;data::(95,5)=##(17,38);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2B.;length::(95,6)=##(11,1);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2B.;size::(95,6):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2B.;capacity::(95,6):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2B.;max_size::(95,6):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2B.;empty::(95,7)=##(0,19);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2B.;__as::(95,8)=##(95,9)=&(25,2);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;basic_string::(95,10)=##(95,11)=*(25,2);:__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.(95,12)=##(95,11);:__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.(95,13)=##(95,11);:__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUi;2A.(95,14)=##(95,11);:__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUi;2A.(95,15)=##(95,11);:__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc;2A.(95,16)=##(95,11);:__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Uic;2A.(95,17)=#(25,2),(0,20),(95,11),(0,1),(0,20);:_._t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;swap::(95,18)=##(0,20);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Rt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;append::(95,19)=##(95,9);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUi;2A.(95,20)=##(95,9);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUi;2A.(95,21)=##(95,9);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc;2A.(95,22)=##(95,9);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Uic;2A.;push_back::(95,23)=##(0,20);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0c;2A.;assign::(95,19):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUi;2A.(95,20):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUi;2A.(95,21):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc;2A.(95,22):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Uic;2A.;__as::(95,21):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc;2A.(95,24)=##(95,9);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0c;2A.;__apl::(95,8):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.(95,21):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc;2A.(95,24):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0c;2A.;insert::(95,25)=##(95,9);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUi;2A.(95,26)=##(95,9);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiPCcUi;2A.(95,27)=##(95,9);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiPCc;2A.(95,28)=##(95,9);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUic;2A.(95,29)=##(6,57);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Pcc;2A.(95,30)=##(6,57);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcUic;2A.;erase::(95,31)=##(95,9);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUi;2A.(95,32)=##(6,57);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Pc;2A.(95,33)=##(6,57);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcT1;2A.;replace::(95,34)=##(95,9);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUiRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUi;2A.(95,35)=##(95,9);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUiPCcUi;2A.(95,36)=##(95,9);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUiPCc;2A.(95,37)=##(95,9);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUiUic;2A.(95,28):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUic;2A.(95,38)=##(95,9);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcT1RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.(95,39)=##(95,9);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcT1PCcUi;2A.(95,40)=##(95,9);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcT1PCc;2A.(95,41)=##(95,9);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcT1Uic;2A.;eos::(95,42)=f(0,2):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;0A?;unique::(95,43)=##(0,20);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;0A.;selfish::(95,43):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;0A.;__vc::(95,44)=##(0,2);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ui;2B.(95,45)=##(95,46)=&(0,2);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ui;2A.;at::(95,45):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ui;2A.(95,47)=##(95,48)=&(0,2);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ui;2B.;terminate::(95,49)=##(0,20);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;0B.;c_str::(95,5):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2B.;resize::(95,50)=##(0,20);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Uic;2A.(95,51)=##(0,20);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ui;2A.;reserve::(95,51):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ui;2A.;copy::(95,52)=##(11,1);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcUiUi;2B.;find::(95,53)=##(11,1);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ui;2B.(95,54)=##(11,1);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUiUi;2B.(95,55)=##(11,1);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUi;2B.(95,56)=##(11,1);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0cUi;2B.;rfind::(95,57)=##(11,1);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ui;2B.(95,54):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUiUi;2B.(95,58)=##(11,1);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUi;2B.(95,59)=##(11,1);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0cUi;2B.;find_first_of::(95,53):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ui;2B.(95,54):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUiUi;2B.(95,55):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUi;2B.(95,56):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0cUi;2B.;find_last_of::(95,57):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ui;2B.(95,54):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUiUi;2B.(95,58):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUi;2B.(95,59):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0cUi;2B.;find_first_not_of::(95,53):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ui;2B.(95,54):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUiUi;2B.(95,55):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUi;2B.(95,56):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0cUi;2B.;find_last_not_of::(95,57):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ui;2B.(95,54):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUiUi;2B.(95,58):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUi;2B.(95,59):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0cUi;2B.;substr::(95,60)=##(25,2);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUi;2B.;compare::(95,61)=##(0,1);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUi;2B.(95,62)=##(0,1);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUiUi;2B.(95,63)=##(0,1);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUi;2B.;begin::(95,64)=##(6,57);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;end::(95,64):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;ibegin::(95,65)=##(6,57);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;0B.;iend::(95,65):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;0B.;begin::(95,5):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2B.;end::(95,5):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2B.;rbegin::(95,66)=##(95,67)=xsreverse_iterator<char *>:;:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.(95,68)=##(95,69)=xsreverse_iterator<const char *>:;:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2B.;rend::(95,66):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.(95,68):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2B.;alloc::(95,70)=##(0,20);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Uib;0A.;_find::(95,71)=f(11,1):t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCccUiUi;0A?;check_realloc::(95,72)=##(0,19);:t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ui;0B.;; Rep:Tt(95,1)=s16len:(11,1),0,32;res:(11,1),32,32;ref:(11,1),64,32;selfish:(0,19),96,8;Rep::(95,73)=##(95,3);:__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepRCQ2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep;2A.(95,74)=##(95,3);:__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep;2A.;data::(95,75)=##(6,57);:Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep;2A.;__vc::(95,76)=##(95,46);:Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUi;2A.;grab::(95,75):Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep;2A.;release::(95,77)=##(0,20);:Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep;2A.;__nw::(95,78)=f(17,29):Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUiUi;2A?;__dl::(17,27):Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepPv;2A?;create::(95,79)=f(95,3):Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUi;2A?;clone::(95,75):Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep;2A.;copy::(95,80)=##(0,20);:Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUiPCcUi;2A.;move::(95,80):Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUiPCcUi;2A.;set::(95,81)=##(0,20);:Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUicUi;2A.;excess_slop::(95,82)=f(0,19):Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUiUi;2A?;frob_size::(39,25):Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUi;2A?;__as::(95,83)=##(95,84)=&(95,1);:Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepRCQ2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep;0A.;; _Lock:Tt(95,85)=s1__as::(95,86)=##(95,87)=&(95,85);:Q2t24__default_alloc_template2b1i0_5_LockRCQ2t24__default_alloc_template2b1i0_5_Lock;2A.;_Lock::(95,88)=##(95,89)=*(95,85);:__Q2t24__default_alloc_template2b1i0_5_LockRCQ2t24__default_alloc_template2b1i0_5_Lock;2A.(95,90)=##(95,89);:__Q2t24__default_alloc_template2b1i0_5_Lock;2A.(95,91)=#(95,85),(0,20),(95,89),(0,1),(0,20);:_._Q2t24__default_alloc_template2b1i0_5_Lock;2A.;; _Obj:Tt(39,19)=u4_M_free_list_link:(39,18),0,32;_M_client_data:(4,11),0,8;__as::(95,92)=##(95,93)=&(39,19);:Q2t24__default_alloc_template2b1i0_4_ObjRCQ2t24__default_alloc_template2b1i0_4_Obj;2A.;_Obj::(95,94)=##(39,18);:__Q2t24__default_alloc_template2b1i0_4_ObjRCQ2t24__default_alloc_template2b1i0_4_Obj;2A.(95,95)=##(39,18);:__Q2t24__default_alloc_template2b1i0_4_Obj;2A.;; Market:Tt(97,1)=s44name_:/0(25,1),0,32;items_:/0(0,13),32,64;marginal_:/0(0,13),96,64;capital_:/0(0,13),160,64;price_in_:/0(0,13),224,64;price_out_:/0(0,13),288,64;__as::(97,2)=##(97,3)=&(97,1);:RC6Market;2A.;Market::(97,4)=##(97,5)=*(97,1);:RC6Market;2A.(97,6)=#(97,1),(0,20),(97,5),(0,1),(0,20);:_._6Market;2A.(97,7)=##(97,5);:;2A.(97,8)=##(97,5);:Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.;info::(97,9)=##(0,20);:;2A.;get_items::(97,10)=##(0,13);:;2A.;get_marginal::(97,10):;2A.;get_capital::(97,10):;2A.;get_price_in::(97,11)=##(0,14);:;2A.;get_price_out::(97,11):;2A.;set_items::(97,12)=##(0,20);:d;2A.;set_marginal::(97,12):d;2A.;set_capital::(97,12):d;2A.;set_price_in::(97,12):d;2A.;set_price_out::(97,12):d;2A.;change_items::(97,13)=##(0,19);:d;2A.;change_marginal::(97,12):d;2A.;change_capital::(97,13):d;2A.;change_price_in::(97,12):d;2A.;change_price_out::(97,12):d;2A.;negotiate_price::(97,12):d;2A.;; Consumer:Tt(96,1)=s64motivation_:/0(0,13),0,64;skill_:/0(0,13),64,64;capital_:/0(0,13),128,64;spendwill_:/0(0,13),192,64;items_:/0(0,13),256,64;market_:/0(97,5),320,32;employed_:/0(0,19),352,8;weeks_employed_:/0(0,1),384,32;weeks_unemployed_:/0(0,1),416,32;income_:/0(0,13),448,64;__as::(96,2)=##(96,3)=&(96,1);:RC8Consumer;2A.;Consumer::(96,4)=##(96,5)=*(96,1);:RC8Consumer;2A.(96,6)=##(96,5);:;2A.(96,7)=##(96,5);:dddd;2A.(96,8)=##(96,5);:ddddP6Market;2A.;info::(96,9)=##(0,20);:;2A.;info_short::(96,9):;2A.;info_head::(96,9):;2A.;get_motivation::(96,10)=##(0,13);:;2A.;get_skill::(96,10):;2A.;get_capital::(96,10):;2A.;get_spendwill::(96,10):;2A.;get_income::(96,10):;2A.;get_items::(96,10):;2A.;get_employment_status::(96,11)=##(0,19);:;2A.;set_motivation::(96,12)=##(0,20);:d;2A.;set_skill::(96,12):d;2A.;set_capital::(96,12):d;2A.;set_spedwill::(96,12):d;2A.;set_income::(96,12):d;2A.;set_employment_status::(96,13)=##(0,20);:b;2A.;set_items::(96,12):d;2A.;change_motivation::(96,12):d;2A.;change_skill::(96,12):d;2A.;change_capital::(96,12):d;2A.;change_spendwill::(96,12):d;2A.;change_income::(96,12):d;2A.;change_items::(96,12):d;2A.;update_values::(96,9):;2A.;update_capital::(96,9):;2A.;update_skill::(96,9):;2A.;update_spendwill::(96,9):;2A.;update_motivation::(96,9):;2A.;buy::(96,9):;2A.;; Company:Tt(100,1)=s60name_:/0(25,1),0,32;capital_:/0(0,13),32,64;stock_:/0(0,13),96,64;invest_:/0(0,13),160,64;employees_:/0(101,5),224,32;market_:/0(97,5),256,32;prod_const_skill_:/0(0,13),288,64;prod_const_motivation_:/0(0,13),352,64;wage_const_:/0(0,13),416,64;__as::(100,2)=##(100,3)=&(100,1);:RC7Company;2A.;Company::(100,4)=##(100,5)=*(100,1);:RC7Company;2A.(100,6)=#(100,1),(0,20),(100,5),(0,1),(0,20);:_._7Company;2A.(100,7)=##(100,5);:;2A.(100,8)=##(100,5);:Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0;2A.(100,9)=##(100,5);:Gt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0P6Market;2A.;info::(100,10)=##(0,20);:;2A.;employee_info::(100,10):;2A.;get_name::(100,11)=##(25,1);:;2A.;get_capital::(100,12)=##(0,13);:;2A.;get_prod_const_skill::(100,12):;2A.;get_prod_const_motivation::(100,12):;2A.;get_wage_const::(100,12):;2A.;get_production::(100,12):;2A.(100,13)=##(0,13);:P8Consumer;2A.;get_stock::(100,12):;2A.;get_invest::(100,12):;2A.;set_capital::(100,14)=##(0,20);:d;2A.;set_prod_const_skill::(100,14):d;2A.;set_prod_const_motivation::(100,14):d;2A.;set_wage_const::(100,14):d;2A.;set_stock::(100,14):d;2A.;set_invest::(100,14):d;2A.;change_capital::(100,14):d;2A.;change_prod_const_skill::(100,14):d;2A.;change_prod_const_motivation::(100,14):d;2A.;change_wage_const::(100,14):d;2A.;change_stock::(100,14):d;2A.;change_invest::(100,14):d;2A.;add_employee::(100,15)=##(0,20);:P8Consumer;2A.;remove_employee::(100,15):P8Consumer;2A.;update_employees::(100,16)=##(0,20);:dd;2A.;print_employees::(100,10):;2A.;sell_to_market::(100,10):;2A.;contribution_adding::(100,13):P8Consumer;2A.;contribution_removing::(100,13):P8Consumer;2A.;update_employees::(100,17)=##(0,19);:P8Consumer;2A.;produce::(100,10):;2A.;pay_employees::(100,10):;2A.;invest::(100,10):;2A.;; __12Company_list:F(99,5) this:p(99,5) this:r(99,5) __12Company_listGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0:F(99,5) info__12Company_list:F(0,20) add_company__12Company_listP7Company:F(0,20) company:p(100,5) p:(103,2) print_list__12Company_list:F(0,20) print_employees__12Company_listGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0:F(0,20) company:r(0,25)=*(25,1) get_random_company__12Company_list:F(103,2) get_company__12Company_listGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0:F(100,5) get_capital_sum__12Company_list:F(0,13) get_item_sum__12Company_list:F(0,13) add_employee__12Company_listGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0P8Consumer:F(0,20) consumer:p(96,5) name:r(0,27)=*(25,1) update_company_employees__12Company_list:F(0,20) motivation_limit:(0,13) skill_limit:(0,13) employee_info__12Company_listGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0:F(0,20) command:r(0,28)=*(25,1) q:(103,2) __exception_info:(0,29)=*(0,30)=xscp_eh_info: produce__12Company_list:F(0,20) pay_employees__12Company_list:F(0,20) sell_to_market__12Company_list:F(0,20) update_employees__12Company_listP8ConsumerGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0:F(0,19) opt:p(96,5) name:r(0,31)=*(25,1) update_employees__12Company_listP8Consumer:F(0,19) update_employees2__12Company_listP8Consumer:F(0,19) r:(103,2) after:(0,19) before:(0,19) invest__12Company_list:F(0,20) __first1:p(0,32)=*(0,10) __last1:p(0,32) __first2:p(0,32) __last2:p(0,32) __first1:p(0,32) __9bad_alloc:F(0,33)=*(0,34)=xsbad_alloc: this:p(0,33) this:r(0,33) __9bad_allocRC9bad_alloc:F(0,33) _ctor_arg:p(0,35)=&(0,34) __nobjs:p(0,36)=&(0,1) __my_free_list:(0,37)=*(39,18) __my_free_list:(0,37) __lock_instance:(95,85) create__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUi:F(95,3) p:(95,3) this:p(95,3) this:r(95,3) _t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0.nilRep:G(95,1) this:p(0,38)=*(25,2) this:p(95,11) p:p(95,3) this:r(95,11) p:r(95,3) replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUiPCcUi:F(95,9) compare__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUi:F(0,1) _str:p(0,39)=&(25,2) rlen:(11,1) r:(0,1) compare__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUiUi:F(0,1) __ti15no_return_error:G(0,40)=ar(0,1);0;11;(0,11) __tf15no_return_error:F(0,41)=&(0,42)=xstype_info: __9exceptionRC9exception:F(0,43)=*(104,8) this:p(0,43) _ctor_arg:p(0,44)=&(104,8) this:r(0,43) _ctor_arg:r(0,44) rep__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0:F(95,3) __t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0:F(95,11) _str:p(0,39) _str:r(0,39) this:p(95,89) this:r(95,89) __Q2t24__default_alloc_template2b1i0_5_Lock:F(95,89) _ctor_arg:p(0,45)=&(104,1) __15no_return_errorRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0:F(104,6) what_arg:p(0,46)=&(25,1) what_arg:r(0,46) __t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc:F(95,11) __eq__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21T0_b:F(0,19) lhs:p(0,39) rhs:p(0,39) lhs:r(0,39) rhs:r(0,39) __eq__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21PCX01_b:F(0,19) rhs:p(17,38) rhs:r(17,38) assign__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc:F(95,9) compare__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUi:F(0,1) assign__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUi:F(95,9) element_company.cc __15Element_company:F(100,2) this:p(100,2) this:r(100,2) __15Element_companyP15Element_companyP7Company:F(100,2) n:p(100,2) c:p(97,5) get_name__15Element_company:F(25,1) get_company__15Element_company:F(97,5) __first1:p(0,24)=*(0,10) __last1:p(0,24) __first2:p(0,24) __last2:p(0,24) __first1:p(0,24) __9bad_alloc:F(0,25)=*(0,26)=xsbad_alloc: this:p(0,25) this:r(0,25) __9exceptionRC9exception:F(0,27)=*(0,28)=xsexception: __9bad_allocRC9bad_alloc:F(0,25) _ctor_arg:p(0,30)=&(0,26) _ctor_arg:r(0,30) _Lock:Tt(0,31)=s1__as::(0,32)=##(0,33)=&(0,31);:Q2t24__default_alloc_template2b1i0_5_LockRCQ2t24__default_alloc_template2b1i0_5_Lock;2A.;_Lock::(0,34)=##(0,35)=*(0,31);:__Q2t24__default_alloc_template2b1i0_5_LockRCQ2t24__default_alloc_template2b1i0_5_Lock;2A.(0,36)=##(0,35);:__Q2t24__default_alloc_template2b1i0_5_Lock;2A.(0,37)=#(0,31),(0,20),(0,35),(0,1),(0,20);:_._Q2t24__default_alloc_template2b1i0_5_Lock;2A.;; this:p(0,35) this:r(0,35) __Q2t24__default_alloc_template2b1i0_5_Lock:F(0,35) _Obj:Tt(39,19)=u4_M_free_list_link:(39,18),0,32;_M_client_data:(4,11),0,8;__as::(0,38)=##(0,39)=&(39,19);:Q2t24__default_alloc_template2b1i0_4_ObjRCQ2t24__default_alloc_template2b1i0_4_Obj;2A.;_Obj::(0,40)=##(39,18);:__Q2t24__default_alloc_template2b1i0_4_ObjRCQ2t24__default_alloc_template2b1i0_4_Obj;2A.(0,41)=##(39,18);:__Q2t24__default_alloc_template2b1i0_4_Obj;2A.;; __lock_instance:(0,31) element_consumer.cc __16Element_consumer:F(99,2) this:p(99,2) this:r(99,2) __16Element_consumerP16Element_consumerP8Consumer:F(99,2) n:p(99,2) c:p(77,5) get_consumer__16Element_consumer:F(77,5) get_motivation__16Element_consumer:F(0,13) get_skill__16Element_consumer:F(0,13) get_capital__16Element_consumer:F(0,13) get_spendwill__16Element_consumer:F(0,13) get_income__16Element_consumer:F(0,13) get_employment_status__16Element_consumer:F(0,19) set_employment_status__16Element_consumerb:F(0,20) market.cc __6Market:F(77,89) this:p(77,89) this:r(77,89) info__6Market:F(0,20) get_items__6Market:F(0,13) get_marginal__6Market:F(0,13) get_capital__6Market:F(0,13) get_price_in__6Market:F(0,14) get_price_out__6Market:F(0,14) set_items__6Marketd:F(0,20) set_marginal__6Marketd:F(0,20) marginal:p(0,13) set_capital__6Marketd:F(0,20) set_price_in__6Marketd:F(0,20) price:p(0,13) set_price_out__6Marketd:F(0,20) change_items__6Marketd:F(0,19) change_marginal__6Marketd:F(0,20) change_capital__6Marketd:F(0,19) change_price_in__6Marketd:F(0,20) change_price_out__6Marketd:F(0,20) negotiate_price__6Marketd:F(0,20) _t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0.nilRep:G(77,1) create__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUi:F(77,3) p:(77,3) this:p(77,3) this:r(77,3) this:p(77,24) p:p(77,3) this:r(77,24) p:r(77,3) replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUiPCcUi:F(77,22) __t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc:F(77,24) rep__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0:F(77,3) assign__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc:F(77,22) assign__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUi:F(77,22)  GCC: (GNU) 3.3.5 (Debian 1:3.3.5-12)  GCC: (GNU) 3.3.5 (Debian 1:3.3.5-12)  GCC: (GNU) 2.95.4 20011002 (Debian prerelease)  GCC: (GNU) 2.95.4 20011002 (Debian prerelease)  GCC: (GNU) 2.95.4 20011002 (Debian prerelease)  GCC: (GNU) 2.95.4 20011002 (Debian prerelease)  GCC: (GNU) 2.95.4 20011002 (Debian prerelease)  GCC: (GNU) 2.95.4 20011002 (Debian prerelease)  GCC: (GNU) 2.95.4 20011002 (Debian prerelease)  GCC: (GNU) 2.95.4 20011002 (Debian prerelease)  GCC: (GNU) 2.95.4 20011002 (Debian prerelease)  GCC: (GNU) 2.95.4 20011002 (Debian prerelease)  GCC: (GNU) 2.95.4 20011002 (Debian prerelease)  GCC: (GNU) 3.3.5 (Debian 1:3.3.5-12)  GCC: (GNU) 2.95.4 20011002 (Debian prerelease)  GCC: (GNU) 3.3.5 (Debian 1:3.3.5-12)                    ��"           ,    !	       0   l�   ��"           $    �	       F   ��           !    �   �  �  _IO_stdin_used     �            ����../sysdeps/i386/elf/start.S /home/drow/debian-glibc/glibc-2.3.2.ds1/build-tree/glibc-2.3.2/csu GNU AS 2.15 ��      q   ����.  <  U  �  �0   '  �  "B   �   3  #T   �   �  $0   N  %q   "  3  (�   �   @  )B   �  *�   �  C  +T   �  ,�   int �  -0   �  2�   �  �  3�     E  ;�   u  <�   �  ��   4  �0   �  �0   �  �q   )  ��   g  �0   �  �0     �a  �    ��   +  ��   �  ��   ��  #  �  �   �   '  W  �~  �  �a    �q   \   ��   �  �0      �a  �   �0     �a    ��   �  �a  �  ��   �  ��   �  ��   �  �a  Y  �a  K  ��   �  �q   X  ��   5  �q   J  ��     ��   �  �h  p  ��  	�   �  ��  	�  �     ��   �  �0   
3  Ea  
N  b0     S
  Q�  <  R   $  �  �   I  T=  N�   # �   S�  # �  T$  y  z  V  # 8   I  # )  T  �  #z  !h  # 8   "I  # z  #�  �  &-      �    �  `  �     g   �  	   8;     J  H  	  R  �   R  7  �  �  �  �  �   �    	X  7  �  <?�  u�  # �  v�  #�   x�   #V  z�  #�  {�  #�   }  #  ~�  #�    #.  �$  # b  ��   #$�   ��   #(�  ��   #,t  ��   #0�  ��   #4�  ��  #8 	=  �  �  $@  ��  # �  ��  #�  ��   #  ��   #�  ��   #%  ��  #8   �I  #8  ��  #  	�  	�  B   	�  	B   	%     K�  	�    �  R  B    @   N  	  $  �   R   �  O/  	5  A  R   t  XL  	R  �  �   R  7  �  �  �  �  �  �   �  ]�  	�  �  �   �  �  �  �  �   �  a�  	�  �  �   �  �  �   	�  �  	�  	�  �  d	  	  $  �   $  �   	�  �  e5  	;  G  �   �    B�  jA  # �  k�  #�  l*  #�  m�  #  n�  # 	G  d  	�  	I  �  �   ��   �%   # B  �R  #�  ��  # �  =  �   �  �  	�  .  ,4�  2�  # �  3=  # M  ,5�  /�  �  4	   Q   5.  �   7�       8�   �  9T   �  :0   �  �  d�    �      5  /home/drow/debian-glibc/glibc-2.3.2.ds1/build-tree/i386-libc/csu/crti.S /home/drow/debian-glibc/glibc-2.3.2.ds1/build-tree/glibc-2.3.2/csu GNU AS 2.15 ��    (  �  /home/drow/debian-glibc/glibc-2.3.2.ds1/build-tree/i386-libc/csu/crtn.S /home/drow/debian-glibc/glibc-2.3.2.ds1/build-tree/glibc-2.3.2/csu GNU AS 2.15 � %   %   :;I  $ >  $ >  :;   :;I8
  I  ! I/  	 I  
 :;I  :;   :;I  :;  (   'I   I  :;  & I  '      <  ! I  4 :;I?
    %    %   S    /   �
    ../sysdeps/i386/elf  start.S     ��.01:"VWYX        �
      �    �   �
    /usr/lib/gcc-lib/i486-linux/3.3.5/include ../sysdeps/generic/bits ../wcsmbs ../sysdeps/gnu ../iconv  init.c    stddef.h   types.h   wchar.h   _G_config.h   gconv.h    �    [   �
    /home/drow/debian-glibc/glibc-2.3.2.ds1/build-tree/i386-libc/csu  crti.S     02,Wd  l�",:  ��,Wdd,,-: �    [   �
    /home/drow/debian-glibc/glibc-2.3.2.ds1/build-tree/i386-libc/csu  crtn.S     F:  ��	 _G_int32_t __time_t __GCONV_INCOMPLETE_INPUT __GCONV_OK __state __gconv_init_fct _G_iconv_t __rlim64_t __GCONV_ILLEGAL_DESCRIPTOR __gconv_info short unsigned int unsigned char __useconds_t __counter __fct __val __value __nsteps _G_int16_t __max_needed_from __gconv_btowc_fct __off_t __ssize_t __statep init.c __fsfilcnt_t __steps __fsfilcnt64_t __blkcnt_t __gconv_loaded_object _G_fpos64_t __gconv_t __trans_end_fct __u_int __GCONV_ILLEGAL_INPUT __blksize_t __to_name __uint64_t __id_t __GCONV_EMPTY_INPUT __cd __ino_t __GCONV_NOCONV __invocation_counter __pid_t __u_short __count __quad_t __u_long __fsid_t __GCONV_FULL_OUTPUT __max_needed_to __timer_t __stateful __uint32_t __key_t __u_char __gconv_step __shlib_handle __min_needed_to short int __dev_t long long int __gconv_trans_data __outbuf long long unsigned int __uid_t __wchb __uint16_t wint_t GNU C 3.3.5 (Debian 1:3.3.5-12) __u_quad_t __gconv_trans_end_fct __flags __outbufend __combined __gconv_trans_init_fct __init_fct __modname __trans_context_fct __trans_fct __rlim_t __wch __intptr_t __suseconds_t __ino64_t wchar_t __GCONV_IS_LAST __blkcnt64_t __fsblkcnt64_t __mode_t __qaddr_t __pos __gconv_end_fct _IO_stdin_used __internal_use __GCONV_NODB __clock_t __gconv_step_data __gconv_trans_query_fct __socklen_t __int64_t __GCONV_NOMEM __off64_t __btowc_fct _G_fpos_t __int8_t /home/drow/debian-glibc/glibc-2.3.2.ds1/build-tree/glibc-2.3.2/csu __daddr_t __fsblkcnt_t _G_uint32_t __nlink_t __swblk_t __GCONV_INTERNAL_ERROR __mbstate_t __gid_t __clockid_t __int32_t __gconv_trans_context_fct __next __GCONV_IGNORE_ERRORS __end_fct __trans __uint8_t __gconv_fct __from_name __min_needed_from __gconv_trans_fct __data __caddr_t _G_uint16_t __loff_t __int16_t           01.01             01.01             01.01             01.01             01.01             01.01             01.01             01.01             01.01             01.01             01.01             01.01    .symtab .strtab .shstrtab .interp .note.ABI-tag .hash .dynsym .dynstr .gnu.version .gnu.version_r .rel.dyn .rel.plt .init .text .fini .rodata .data .eh_frame .gcc_except_table .dynamic .ctors .dtors .got .bss .stab .stabstr .comment .debug_aranges .debug_pubnames .debug_info .debug_abbrev .debug_line .debug_str .note.GNU-stack .note                                                     ��                     #         �                     1         (�(  L               7         t�t                 ?         t�t  /                 G   ���o   ���  �                T   ���o   ���   @                c   	      Ġ�   0                l   	      ���   x              u         l�l"                    p         ���"                   {         ���%  �u                 �         00�                    �         ``�  `                  �         �3��  �                   �         l4l�  �i                 �         P�P �
                 �         ��� �                �         ̩�                   �         ԩ�                   �         ܩ� �                 �         ��� �                  �              � T�              �              �� ��                �              �� �                 �              h� x                  �              �� %                  	             � s
                              x� 8                 #             �� c                 /     0       � �                :             ɚ                    J             ɚ �                                �� P                               Ԣ �  $   �         	              T� t4                                     �          �          (�          t�          t�          ��          ��          Ġ          ��     	     l�     
     ��          ��          0          `          �3          l4          P�          ��          ̩          ԩ          ܩ          ��                                                                                                                                                                !              "              #              $             ��            ��            ��V            ��a            ��l            ��a            ��            ��a            ��            ��            ��            ��V            ��a            ���            ���            ��           ��N           ���            ��            ��            ��            ��V            ���            ��Y  ��      i           ��t  �       �  �3      �  ԩ      �  �3      �  �      �  l4      �  0�      �  ,�     �  8�      �  \�      �  �3        ̩      i           ��t                   (  Щ      �  $      �  l4      5  ة      B  L�      P           ��           ��N           ��P           ��            ��            ��            ��V            ��P           ���           ���  `     �  P�       �  ��       �  l4       �           ���  \     �  T�       �  &�       �  L=       �           ���  H     �  ��       �  ��       �  �O       �           ���  �     �  L�       �  \�       �  �\       �           ���  P      �  X�       �  ��       �  �l                  ���  8!     �  ��       �  �       �  �n                  ���  l"     �  |�       �  u       �  0}       #           ���  �"     �  ��       �  k       �  P�       6           ���  �"     �  �       �  �       J           ���  �#     �  8�       �  @       �  ��       T  ��$   "  �  0�B   "  (  l�4    P  ��?    t  ��j     �  ��     �  4�   "  �  ��5     �  ��       l�R     u  L4   !  �  �     �  `.   "  &   �  "  [  �        �y   "  �  �     �  ��     �  ��    T  d��     �  �      �  ��^   "  7  ���   "  �  ��     �  P4   !  �  ��	      �  ��  "  	  ��     :	  ��n      N	  ��     ��W	  �D     u	  (�     �	  \�9     �	  ��     �	  ��     �	  ��8      �	  @�8   "  K
  ��#    v
  ��@   "  �
  Ģ4      �
  h�q     �
  �     �
  $�     �
  \       ��     /  ��     9  0�/   "  �  �@     �  ��?     �  t�     �  `     �  ��   !  �  ��#        �7   "  \  x�     u  x�5   "    �w       L�     �        �  0�   "    0+     -  �j     >  @3     V  �3     ��g  H    �  Ԣ�     �  �J       ��Z   "    ��     /  �)      U  D�     k  ��     �  $�     �  ��H     �  �      �  ��       �3       `�     &  ��Z    <  ��    a  T�.     p  ��U    �  �P     �  ��N     �  ��     �  ��    �  L{     q  ���     �  ��   "  �  ��*     �  ��"       P�     $  �:   "  �  �   "  �  �#      �  `�?   "  e  ���     z  l�R     �   �   "  �  ��"   "     x?       LI     5  t�     U  �     �  8�    �  (�     �  �(      �  �3@   !  	  �I     (  ��"   "  �  �  "  -  $�@      7  ���     �  ���       �       4�/      3  P�<   "  `  �c     q  l�     
 w  �     �  ��     �  �     �  X�     �  ��a    8  T�$     W  ���    l  T��     ~  �     �  ��d     �  ��I     �  ��     �  �Z     �  ��       T4   !  A  4��     Z  <�7     {  `�h     �  D�     �  ��     �  d��      �  �     �  t��     �  Ъ   !    ��     %  ��/      T   �     q  4     �  � *    �  T�!   "  �  �#   "  6  ��  "  �  ���   "   �  ��     �  ��      �  ���     �  ��m     	  4�j     k  �     �  ��h    �  ��   "  �  ��^     �  ��9   "  �  ��/        �     *  ģ      :  ��U   "  �  ��      �  �@     �  ��Z   "  1  p�B   "  �  ԣ1      �   ��    �  �/   "  +  ���     R  t&     }  �     �  �     �  ��     �  �f     �  h   !  <   X�     V   ���     s   �(      |   ��$      �   D�     �   �     �   d�     �   D�`     �   T�     !  0      3!  L�     N!  ��     d!  X4   !  {!  `�     �!  8�   "  �!  X�     "  ��x     4"  �3     ��G"  ��=     _"  @T     o"  8     �"   ��     �"  ��(   "  �"  ��     ���"  p�     #  �     ,#  �   "  \#  ���     t#  p�"
    y#  ��     �#  ���    �#  ��      �#  ��i     �#  H4   !  '$  �~      �$  ,I     �$  84   !  �$  ��    �$  (��     %  0�i     q%  @�     �%  $��      �%  �}     �%  �3     ���%  \��     :&  0�\   "  S&  �     j&  4��      y&  D��      �&  ��     �&  ��B   "  '   �G     '  �      9'  ��*     O'  8T     r'  ��G     �'  ��     �'  �3       �'  �L     �'  T�      �'  0      �'  t�V      (  ��)      *(  <�     8(  ��     M(  ��      q(  ��C      �(  x�"     �(  ���     �(  ��     �(  Ĥ^      �(  �Q   "  P)  Ԥ       ])  ��u     �)  �<   "  *  ���    l*  ,`    z*  ��     �*  |e     �*  ���     �*  �     �*  �*   "  K+  �     e+  \�     �+  ��n    �+  �(      �+  �  "  ,  8�     &,  ��q     I,  P��    p,   ��   "  �,  ��     ���,  ��     �,  ���      �,  �     �,  �     �,  ܩ     ��-  ��      %-  D�    4-  P�     ��9-  �_     ]-  Xf     x-  h��     �-  t     �-  �:   "  �-  �   !  �-  ��\   "  �-  h�K     �-  �D     .  P�3   "  /.  @��     b.   4   !  �.  ��     �.  �4      �.  P$     �.  l     /  �3     �� /  $��      1/  L�     K/  d     Z/  P�R     k/  4�1      �/  �     �/  D�H     �/  �G   "  0  `��   "  90   �2   "  �0  ��     �0  �z     �0        1  ��:    1  `�\   "  }1   �"     �1  �3      �1  �     �1  (�     N2  T�      ^2  ���   "  �2  ��     �2   �,     �2  ��     �2  d�}   "   �2  �     �2  H�$   "  B3  ��-   "  �3  t�5      �3  H�b     �3  l�'   "  44  h�     K4              Z4  t�      <command line> /home/drow/debian-glibc/glibc-2.3.2.ds1/build-tree/i386-libc/config.h <built-in> abi-note.S /home/drow/debian-glibc/glibc-2.3.2.ds1/build-tree/i386-libc/csu/abi-tag.h init.c /home/drow/debian-glibc/glibc-2.3.2.ds1/build-tree/i386-libc/csu/crti.S /home/drow/debian-glibc/glibc-2.3.2.ds1/build-tree/i386-libc/csu/defs.h initfini.c call_gmon_start crtstuff.c gcc2_compiled. p.3 __DTOR_LIST__ completed.4 __do_global_dtors_aux __EH_FRAME_BEGIN__ fini_dummy object.11 frame_dummy init_dummy force_to_data __CTOR_LIST__ __do_global_ctors_aux __CTOR_END__ __DTOR_END__ __FRAME_END__ /home/drow/debian-glibc/glibc-2.3.2.ds1/build-tree/i386-libc/csu/crtn.S main.cc __WORD_BIT __EXCEPTION_TABLE__ Letext __FRAME_BEGIN__ city.cc consumer.cc consumer_list.cc functions.cc company.cc company_list.cc element_company.cc element_consumer.cc market.cc release__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep __ls__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_R7ostreamRCt12basic_string3ZX01ZX11ZX21_R7ostream contribution_adding__7CompanyP8Consumer add_last__13Consumer_listP8Consumer __13Consumer_list change_prod_const_motivation__7Companyd _S_freelist_index__t24__default_alloc_template2b1i0Ui employee_info__4City info__12Company_list set_name__13Consumer_listGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 _t24__default_alloc_template2b1i0._S_start_free change_capital__6Marketd __eq__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21T0_b _S_chunk_alloc__t24__default_alloc_template2b1i0UiRi get_prod_const_motivation__7Company __lexicographical_compare_3way__H2ZPCScZPCSc_X01X01X11X11_i print_consumer_list__4City get_items__8Consumer get_company__12Company_listGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 update_employees__4CityGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 get_motivation__16Element_consumer clone__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep check_realloc__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ui print_labour_market__4City _t24__default_alloc_template2b1i0._S_end_free atan@@GLIBC_2.0 _S_oom_malloc__t23__malloc_alloc_template1i0Ui update_consumer_list__4City __cp_push_exception _DYNAMIC pay_employees__12Company_list change_motivation__8Consumerd update_spendwill__8Consumer set_capital__8Consumerd get_employment_status__8Consumer endl__FR7ostream __t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc remove_consumer__13Consumer_listP8Consumer allocate__t23__malloc_alloc_template1i0Ui _._9exception get_item_sum__13Consumer_list get_market__4City get_wage_const__7Company get_company__15Element_company set_spedwill__8Consumerd __6Market data__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 change_price_out__6Marketd update_values__8Consumer print_employees__7Company _fp_hw __vt_9bad_alloc produce__7Company assign__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc get_spendwill__8Consumer __t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 print_employees__12Company_listGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 info_short__8Consumer get_spendwill__16Element_consumer data__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep get_name__15Element_company __12Company_list set_price_out__6Marketd __fini_array_end employee_info__12Company_listGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 __ls__7ostreamd remove_employee__7CompanyP8Consumer __9bad_alloc print_list__13Consumer_list copy__t18string_char_traits1ZcPcPCcUi __ti15no_return_error add_company__12Company_listP7Company get_random_consumer__4City normalize__FRd get_capital__16Element_consumer set_labour_market__4CityP13Consumer_list __dso_handle sell_to_market__4City info__13Consumer_list update_employees__7CompanyP8Consumer get_price__Fdd get_optimal_consumer__4Citydd __libc_csu_fini get_unemployed__13Consumer_list change_capital__7Companyd add_first__13Consumer_listP8Consumer add_employee__12Company_listGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0P8Consumer __out_of_range__FPCc compare__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUiUi get_name__7Company add_consumer__4CityP8Consumer produce__4City compare__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUi __9exceptionRC9exception __ls__7ostreamPFR7ostream_R7ostream repup__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PQ2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep update_market__4City get_employed__13Consumer_list rep__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 _._15no_return_error update_employees__7Companydd produce__12Company_list set_prod_const_skill__7Companyd __16Element_consumerP16Element_consumerP8Consumer get_motivated_consumers__13Consumer_list change_invest__7Companyd setprecision__Fi _t24__default_alloc_template2b1i0._S_free_list sell_to_market__12Company_list __dl__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepPv compare__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUi __rtti_si add_company__4CityGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 add_employee__4CityGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0P8Consumer print_company_list__4City what__C13runtime_error _._Q2t24__default_alloc_template2b1i0_5_Lock invest__7Company _init set_items__8Consumerd pay_employees__13Consumer_listddd __15Element_company get_skill__8Consumer __7CompanyGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0P6Market get_motivated_consumers__4City info_head__8Consumer malloc@@GLIBC_2.0 get_marginal__6Market get_prod__FP8Consumer __8ConsumerddddP6Market set_income__8Consumerd get_random_consumer__13Consumer_list __ti13runtime_error _t24__default_alloc_template2b1i0._S_heap_size get_production__7Company add_employee__7CompanyP8Consumer employee_info__7Company get_stock__7Company set_companies__4CityP12Company_list __throw get_capital__6Market __ls__7ostreamPCc __vt_13runtime_error set_skill__8Consumerd __ls__H1ZUl_R7ostreamRCt6smanip1ZX01_R7ostream change_wage_const__7Companyd set_price_in__6Marketd contribution_removing__7CompanyP8Consumer deallocate__t23__malloc_alloc_template1i0PvUi length__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UiUiPCcUi __deregister_frame_info get_capital__7Company terminate__Fv pay_employees__7Company pay_employees__13Consumer_listd employee_info__4CityGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 set_capital__6Marketd __4City __Q2t24__default_alloc_template2b1i0_5_Lock get_spendwill_sum__13Consumer_list __tf15no_return_error __ls__H1Zi_R7ostreamRCt6smanip1ZX01_R7ostream invest__4City time@@GLIBC_2.0 __as__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 _start change_price_in__6Marketd lexicographical_compare__H2ZPCScZPCSc_X01X01X11X11_b copy__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUiPCcUi pthread_mutex_lock@@GLIBC_2.0 info__8Consumer __eq__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21PCX01_b remove_by_motivation__13Consumer_listd set_employment_status__16Element_consumerb get_consumer__16Element_consumer get_items__6Market set_motivation__8Consumerd get_item_sum__12Company_list _t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0.npos get_size__13Consumer_list update_motivation__8Consumer setw__Fi __start_cp_handler update_company_employees__4City set_employment_status__8Consumerb set_capital__7Companyd get_capital_sum__4City get_invest__7Company get_income__16Element_consumer change_capital__8Consumerd get_income__8Consumer __vt_15no_return_error change_spendwill__8Consumerd max_size__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 update_employees2__12Company_listP8Consumer update_skill__8Consumer __fini_array_start update__13Consumer_list __libc_csu_init negotiate_price__6Marketd randomize__FRdd __as__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc __bss_start pay_company_employees__4City set_items__6Marketd _S_round_up__t24__default_alloc_template2b1i0Ui add_consumer__4Citydddd main set_wage_const__7Companyd get_optimal_consumer__13Consumer_listdd __cp_pop_exception get_skill_sum__13Consumer_list _t23__malloc_alloc_template1i0.__malloc_alloc_oom_handler __13runtime_errorRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 invest__12Company_list _t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0.nilRep __7Company buy__8Consumer print_employees__4CityGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 market_info__4City __libc_start_main@@GLIBC_2.0 update_company_employees__12Company_list __init_array_end __13Consumer_listGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 __9bad_allocRC9bad_alloc set_marginal__6Marketd exp@@GLIBC_2.0 __ls__7ostreami set_prod_const_motivation__7Companyd move__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUiPCcUi __8Consumer get_skill__16Element_consumer follow_capital__4City get_random_company__12Company_list follow_capital__4CityP8Consumer change_items__8Consumerd data_start get_price__Fd compare__t18string_char_traits1ZcPCcT1Ui _fini __eh_rtime_match move__t18string_char_traits1ZcPcPCcUi get_norm__Fdd consumer_info__4City length__t18string_char_traits1ZcPCc __tf13runtime_error add_motivated_consumers__4CityP16Element_consumer __length_error__FPCc set_stock__7Companyd srand@@GLIBC_2.0 create__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUi __9exception get_company__4CityGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 grab__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep __4CityGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 info__6Market update_capital__8Consumer get_capital_sum__12Company_list remove_by_skill__13Consumer_listd get_price_out__6Market __nw__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUiUi change_marginal__6Marketd __12Company_listGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 info__4City setiosflags__FUl allocate__t24__default_alloc_template2b1i0Ui change_skill__8Consumerd get_production__7CompanyP8Consumer get_usless_employee__13Consumer_listdd _S_refill__t24__default_alloc_template2b1i0Ui _edata set_invest__7Companyd write__7ostreamPCci __i686.get_pc_thunk.bx sell_to_market__7Company _GLOBAL_OFFSET_TABLE_ free@@GLIBC_2.0 info__7Company _end get_motivation_sum__13Consumer_list print_list__12Company_list negotiate_market_price__4City change_items__6Marketd _._4City __vt_9exception __15no_return_errorRC15no_return_error __8Consumerdddd consumers_buy__13Consumer_list _._13runtime_error add_group_last__13Consumer_listP16Element_consumer _t24__default_alloc_template2b1i0._S_node_allocator_lock set_consumers__4CityP13Consumer_list _._9bad_alloc get_employment_status__16Element_consumer __16Element_consumer __init_array_start __builtin_delete get_motivation__8Consumer _IO_stdin_used get_prod__Fddddd pthread_mutex_unlock@@GLIBC_2.0 get_prod_const_skill__7Company __builtin_new _._t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 deallocate__t24__default_alloc_template2b1i0PvUi assign__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUi labour_info__4City update_employees__12Company_listP8Consumer __15Element_companyP15Element_companyP7Company random_consumer__FP6Market __15no_return_errorRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 remove_consumer_from_labour_market__4CityP8Consumer __data_start change_stock__7Companyd update_employees__12Company_listP8ConsumerGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 rand@@GLIBC_2.0 __13runtime_errorRC13runtime_error change_prod_const_skill__7Companyd cout consumers_buy__4City __register_frame_info get_price_in__6Market capacity__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 frob_size__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUi __eh_alloc get_capital_sum__13Consumer_list excess_slop__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUiUi get_capital__8Consumer __gmon_start__ change_income__8Consumerd                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
