#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <ctime>

//#include "consumer.h"
//#include "consumer_list.h"
#include "city.h"
//#include "company.h"
//#include "company_list.h"
//#include "element.h"
#include "functions.h"
#include "init_company.h"
#include "functions.h"
//#include "market.h"
//#include "element_consumer.h"
//#include "element_company.h"

using namespace std;

int main() {

  /*
   * Starting a clock for randomizing later on
   */  
  
  srand(static_cast<unsigned>(time(0)));
  
  /*
   * Creating bennyland
   */ 

  City bennyland("Bennyland");

  /*
   * The functions init_companies(land) adds some companies to bennyland. 
   * Have a look at the file init_company.cc to change company parameters. 
   */

  //City * land = 0;  
  //land = &bennyland;
  //init_companies(land);
  bennyland.load_company("bempa_AB");
  bennyland.load_company("bempa_co");
  bennyland.load_company("benny_inc");
  bennyland.load_company("limpan_AB");
  bennyland.load_company("benny_enterprises");
  bennyland.load_company("johansson_och_johansson");

  
  bennyland.print_company_list(); 

  /*
   * Creating 2000 random consumers. See file functions.cc for settings about the consumers.
   */
  

  for(int i = 0; i < 1000; i++) {    
    Consumer * benny = random_consumer(bennyland.get_market(), bennyland.get_bank(), bennyland.get_clock());
    benny -> set_name("Consumer" + std::to_string(i));
    bennyland.add_consumer(benny);    
  }


  /*
   * A check so that no money is lost during the exec.
   */

  double sum_before = bennyland.get_capital_sum();
  
  /*
   * Starting the main loop, the functions in it are quite 
   * clarifying in their names. 
   */
  ofstream empty("gdp_test.txt");
  empty << " " << endl;
  empty.close();
  
  ofstream empty_flash("flash.txt");
  empty_flash << " " << endl;
  empty_flash.close();
  
  ofstream empty_transactions("transactions.txt");
  empty_transactions << " " << endl;
  empty_transactions.close();
  
   ofstream empty_transactions_full("transactions_full.txt");
  empty_transactions_full << " " << endl;
  empty_transactions_full.close();

  ofstream  file2 ("money_test.txt");
   file2 << "bank_capital" << " " << "bank_loans"  << " " << "bank_debts"  << " " << "consumer_capital"  << " "
	 << "company_capital" << " " << "market_capital" << " " << "total_capital" << endl;


  double counter = 0;
  bool invest = false;
  int flashtime = 60;


  for(int j = 0; j < 300; j++) {
    double time_year = bennyland.get_time();
    cout << time_year << endl;

    bennyland.update_employees();
    bennyland.negotiate_market_price();

    bennyland.save_flash(flashtime);

    bennyland.produce();
   
    if(invest) {
      bennyland.update_companies();
    }

    bennyland.save_data();
      
    bennyland.sell_to_market();
    bennyland.save_flash(flashtime);

    bennyland.consumers_buy();
    bennyland.save_flash(flashtime);

    bennyland.pay_company_employees();
    bennyland.save_flash(flashtime);
    
    if(invest) { 
      bennyland.update_interest_rate();
    }

    bennyland.save_flash(flashtime);    
    bennyland.invest(invest);
    bennyland.save_flash(flashtime);    
    
    if(time_year >= 10) {
      invest = true;
    }

    if(invest) {
      bennyland.consumer_get_and_pay_interest();
    }
    bennyland.save_flash(flashtime);    

    if(invest) {
    
        bennyland.company_pay_interest();
    }
    bennyland.save_flash(flashtime);    
    
    if(invest) {
      bennyland.consumers_bank_business();
    }
    bennyland.save_flash(flashtime);    
    
    if(invest) {
      bennyland.company_repay_to_bank();
    }
    bennyland.save_flash(flashtime);    
    
    if(invest) {
      bennyland.consumers_deposit_and_borrow_from_bank();
    }
 

    bennyland.company_pay_dividends();
    
    bennyland.save_money_data();

    bennyland.save_flash(flashtime);

    bennyland.adjust_money();
    bennyland.save_flash(flashtime);
    bennyland.update_consumer_list();

    bennyland.tick();
 
  }

  
  /*
   * Printing info from the main loop. Run "gnuplot gdp.p" and then "gv gdp.eps" to view the output.   
   */
  
  bennyland.print_company_list();  
  bennyland.print_GDP();
  bennyland.market_info();
  bennyland.consumer_info();
  bennyland.bank_info();  

  /*
   * A check again so that no money is lost during the exec.
   */

  //cout <<  bennyland.get_company("bempa AB") -> get_desired_loans() << endl;
  
  //bennyland.get_company("bempa AB") -> save("kallealle");  
  //bennyland.get_company("bempa co") -> save("kallealle");  
  //bennyland.get_company("benny inc.") -> save("kallealle");  
  //bennyland.get_company("limpan AB") -> save("kallealle");  
  //bennyland.get_company("benny enterprises") -> save("kallealle");  
  //bennyland.get_company("johansson och johansson") -> save("kallealle"); 
  
  double sum_after = bennyland.get_capital_sum();
  
  cout << endl << "Capital before: " << sum_before << endl 
       << "Capital after: " << sum_after << endl 
       << "Difference: " << sum_before - sum_after << endl
       << "Added money: " << bennyland.get_loans_to_bank() << endl;
  

  //  bennyland.print_consumer_list();

};

















