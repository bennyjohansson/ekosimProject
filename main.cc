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
  

  for(int i = 0; i < 4000; i++) {    
    Consumer * benny = random_consumer(bennyland.get_market(), bennyland.get_bank(), bennyland.get_clock());
    benny -> set_name("Consumer" + std::to_string(i));
    bennyland.add_consumer(benny);    
  }


  /*
   * A check so that no money is lost during the exec.
   */

  double sum_before = bennyland.get_capital_sum();


   /*
   * Loading money laundring data
   */
   
	bennyland.load_launder_parameters();
	cout << "Param1: " << bennyland.get_laundry_factor() << endl;
  
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


	double simulation_years = 500;
  bool invest = false;
  int flashtime = 5;
  string theThiefString = "";
  double time_to_steal = bennyland.get_time_to_steal();
  string theFraudCompanyString = "benny_enterprises";
  double amount_to_launder = 0;
  double start_investing = 5;
  unsigned int timer0 = 0, timer1 = 0, timer2 = 0, timer3 = 0, timer4 = 0, timer5= 0, timer6 = 0, timer7 = 0, timer8 = 0;




  for(int j = 0; j < simulation_years; j++) {
  
  	//Timer checkpoint
  	timer0 = stopwatch();

    double time_year = bennyland.get_time();
    cout << "------------------------------------------------------------------------------------" << endl;
    cout << "Year: " << time_year << endl;
    cout << "------------------------------------------------------------------------------------" << endl;
        
    cout << endl << "PRICING, EMPLYEES & PRODUCING" << endl;
    cout << "Money: " << bennyland.get_capital_sum() << endl;

    bennyland.update_employees();
    bennyland.negotiate_market_price();

    bennyland.save_flash(flashtime);

	
    bennyland.produce();

	//Timer checkpoint produce
	timer1 = stopwatch();// - timer0;

    cout << endl << "UPDATING COMPANIES, BUYING & SELLING" << endl;
    cout << "Money: " << bennyland.get_capital_sum() << endl;
    
    if(invest) {
      bennyland.update_companies();
    }

    bennyland.save_data();
      
    bennyland.sell_to_market();
    bennyland.save_flash(flashtime);

    bennyland.consumers_buy();
    bennyland.save_flash(flashtime);
   
       
    //Initiating theft
    if(fmod(time_year,time_to_steal) == 0) {
    
    	theFraudCompanyString = bennyland.get_random_company() -> get_name();// -> get_name();
    	
    	//Step 1 steal money (steal from bank or someone with more money)
    	//Set spendwill to small
    	theThiefString = bennyland.steal_money();
    	cout << " I main steal " << time_year << " tts " << time_to_steal << "  Mod: " << fmod(time_year,time_to_steal) << endl;
    	cout << "Year: " << j << " i main steal: " << theThiefString << " " << theFraudCompanyString << endl << endl;
    }

    
    //Launder money
    if(fmod(time_year-2,time_to_steal) == 0) {
    
    	//Step 2.1 buy stuff from the market in small batches from our insider but no goods
    	//Step 2.2 move money from market to company
    	cout << " I main steal 2 " << time_year << " tts " << time_to_steal << "  Mod: " << fmod(time_year,time_to_steal) << endl;
    	amount_to_launder = bennyland.launder_money(theThiefString, theFraudCompanyString);
    	cout << "I main launder money: " << amount_to_launder << endl;
    	
    }
    
    bennyland.pay_company_employees();
    bennyland.save_flash(flashtime);
    
    //Timer checkpoint buy/sell
	timer2 = stopwatch();
	
	cout << endl << "INTERST RATE & INVESTING" << endl;
	cout << "Money: " << bennyland.get_capital_sum() << endl;

    
    if(invest) { 
      bennyland.update_interest_rate();
    }


    bennyland.save_flash(flashtime);   
    bennyland.invest(invest);
    bennyland.save_flash(flashtime);    
    
    if(time_year >= start_investing) {
      invest = true;
    }

	
	//Timer checkpoint update interest & invest
	timer3 = stopwatch();
	
	cout << endl << "BANK BUSINESS" << endl;	
    cout << "Money: " << bennyland.get_capital_sum() << endl;

    if(invest) {
    
		//bennyland.consumer_get_and_pay_interest();  		
   		bennyland.consumers_bank_business();
		//bennyland.consumers_deposit_and_borrow_from_bank();
    	
 		bennyland.company_pay_interest();
 		bennyland.company_repay_to_bank();


    	//bennyland.save_flash(flashtime);  
          
    }
    
   
    //Timer checkpoint bank business
		timer4 = stopwatch();
 
    cout << endl << "DIVIDENDS" << endl;
    cout << "Money: " << bennyland.get_capital_sum() << endl;

 
	//Pay stolen dividends
 	if(fmod(time_year-2,time_to_steal) == 0) {
    
    	//Step 3 generate dividend payment in small batches to our thief
    	bennyland.company_pay_dividends(theFraudCompanyString, theThiefString, amount_to_launder);
    	bennyland.randomize_laundry_parameters();
    	cout << " I main steal 3 " << time_year << " tts " << time_to_steal << "  Mod: " << fmod(time_year,time_to_steal) << endl;
    }
    	

    bennyland.company_pay_dividends();
    
    //Timer checkpoint last part
    timer5 = stopwatch();// - timer4;
	cout << endl << "SAVING DATA" << endl;

    
    bennyland.save_money_data();
    

    bennyland.save_flash(flashtime);

    bennyland.adjust_money();
    bennyland.save_flash(flashtime);
    bennyland.update_consumer_list();

    bennyland.tick();
   
   //Timer checkpoint last part
	timer6 = stopwatch();// - timer5;
   
   
   cout << endl << "TIME MEASUREMENTS" << endl;
 	cout << "Produce:  " << timer1/10000 << endl;
 	cout << "Buy/sell: " << timer2/10000 << endl;
 	cout << "Int & Iv: " << timer3/10000 << endl;
 	cout << "Bank bus: " << timer4/10000 << endl;
 	cout << "Divs:     " << timer5/10000 << endl;
 	cout << "Sav&up:   " << timer6/10000 << endl;
 	cout << "Total:    " << (timer1 +  timer2 +  timer3 +  timer4 +  timer5)/10000 << endl << endl;
  }

  
  /*
   * Printing info from the main loop. Run "gnuplot gdp.p" and then "gv gdp.eps" to view the output.   
   */
  
  
  bennyland.print_GDP();
  bennyland.print_company_list();  
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
  

  //bennyland.print_consumer_list();

};

















