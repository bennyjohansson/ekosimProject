#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>

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

  City * land = 0;  
  land = &bennyland;
  init_companies(land);
 

  /*
   * Creating 2000 random consumers. See file functions.cc for settings about the consumers.
   */
  for(int i = 0; i < 2000; i++) {    
    Consumer * benny = random_consumer(bennyland.get_market(), bennyland.get_bank(), bennyland.get_clock());
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

  ofstream  file2 ("money_test.txt");
   file2 << "bank_capital" << " " << "bank_loans"  << " " << "bank_debts"  << " " << "consumer_capital"  << " "
	 << "company_capital" << " " << "market_capital" << " " << "total_capital" << endl;


  double counter = 0;
  bool invest = false;
  int flashtime = 202;


  for(int j = 0; j < 1000; j++) {
    double time = bennyland.get_time();
    cout << time << endl;

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
    
    bennyland.invest(invest);
    bennyland.save_flash(flashtime);    
   
    bennyland.update_consumer_list();
   
    if(time > 0) {
      invest = true;
    }
    
    if(invest) {
      cout << "Total_cap1: " << bennyland.get_capital_sum() << endl;
      bennyland.consumers_deposit_to_bank();    
      cout << "Total_cap2: " << bennyland.get_capital_sum() << endl;
      bennyland.save_flash(flashtime);
      
      bennyland.consumers_borrow_from_bank();
      cout << "Total_cap3: " << bennyland.get_capital_sum() << endl;
      bennyland.consumer_get_interest();
      cout << "Total_cap4: " << bennyland.get_capital_sum() << endl;
      bennyland.save_flash(flashtime);
      bennyland.company_pay_interest();
      cout << "Total_cap5: " << bennyland.get_capital_sum() << endl;
      bennyland.consumers_bank_business();
      cout << "Total_cap6: " << bennyland.get_capital_sum() << endl;
      // bennyland.consumers_repay_and_recieve_bank();
      bennyland.company_repay_to_bank();
      cout << "Total_cap7: " << bennyland.get_capital_sum() << endl;
      bennyland.save_flash(flashtime);
    }
   

    bennyland.save_money_data();
    bennyland.company_pay_dividends();
    bennyland.save_flash(flashtime);
    bennyland.adjust_money();

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

  cout <<  bennyland.get_company("bempa AB") -> get_desired_loans() << endl;
  
  double sum_after = bennyland.get_capital_sum();
  
  cout << endl << "Capital before: " << sum_before << endl 
       << "Capital after: " << sum_after << endl 
       << "Difference: " << sum_before - sum_after << endl
       << "Added money: " << bennyland.get_loans_to_bank() << endl;
  
};


















