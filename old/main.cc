#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>

//#include "consumer.h"
//#include "consumer_list.h"
#include "city.h"
//#include "company.h"
//#include "company_list.h"
//#include "element.h"
#include "functions.h"
//#include "market.h"
//#include "element_consumer.h"
//#include "element_company.h"

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
  // bennyland.add_company(b3);
  //bennyland.add_company(b4);
  //bennyland.add_company(b5);
  //bennyland.add_company(b6);

  //  bennyland.print_company_list();

  bennyland.get_company(b1) -> set_prod_const_skill(50);
  bennyland.get_company(b1) -> set_prod_const_motivation(50);
  bennyland.get_company(b2) -> set_prod_const_skill(60);
  bennyland.get_company(b2) -> set_prod_const_motivation(40);
//   bennyland.get_company(b3) -> set_prod_const_skill(40);
//   bennyland.get_company(b3) -> set_prod_const_motivation(60);
//   bennyland.get_company(b4) -> set_prod_const_skill(50);
//   bennyland.get_company(b4) -> set_prod_const_motivation(70);
//   bennyland.get_company(b5) -> set_prod_const_skill(30);
//   bennyland.get_company(b5) -> set_prod_const_motivation(80);
//   bennyland.get_company(b6) -> set_prod_const_skill(80);
//   bennyland.get_company(b6) -> set_prod_const_motivation(30);

  
  //Gets the consumers with high motivation and adds them to th  
  //the labour market
//  Element_consumer * workers = bennyland.get_motivated_consumers();  
//  bennyland.add_motivated_consumers(workers);

  //Initiering av priser och dylit
  int no_companies = bennyland.get_no_companies();
  double cap_sum = bennyland.get_company_capacity_sum();
  double cons_cap = bennyland.get_consumer_capital_sum();

  double approx_price = 75;
  double price_in = approx_price;
  double marginal =  bennyland.get_market() -> get_marginal(); 
  double price_out =  (1 + marginal)*price_in;
  bennyland.get_market() -> set_price_in(price_in);
  bennyland.get_market() -> set_price_out(price_out);
  cout << "I main" << endl << "price in " << price_in << endl;
  Consumer * random = bennyland.get_random_consumer();

  //  random -> info_head();
  bennyland.market_info();
  double sum_before = bennyland.get_capital_sum();
  int test = 0;  
  bennyland.update_consumer_list();
  

  for(int j = 0; j <3; j++) {
    bennyland.update_employees(b1);
    //bennyland.update_employees(b2); 
    //bennyland.update_employees(b3);
    //bennyland.update_employees(b4);
    //bennyland.update_employees(b5);
    //bennyland.update_employees(b6);
    bennyland.company_pay_dividends();
    bennyland.negotiate_market_price();
    cout << "Vecka: " << j << endl;
    for(int i = 0; i < 5; i++) {
      bennyland.update_consumer_list();
      cout << "I main 2" << endl;
      bennyland.produce();
      //bennyland.negotiate_market_price();
      bennyland.sell_to_market();
      
      bennyland.consumers_buy();

      //      random -> info_short();
      bennyland.pay_company_employees();
    }
    cout << "imain 3" << endl;
  }

  bennyland.print_company_list();  
  bennyland.print_GDP();
  bennyland.market_info();
  bennyland.consumer_info();
  
  double sum_after = bennyland.get_capital_sum();
  
  cout << endl << "Capital before: " << sum_before << endl << "Capital after: " << sum_after << endl << "Difference: " << sum_before - sum_after << endl;
  //bennyland.labour_info();
  // bennyland.employee_info();
};


















