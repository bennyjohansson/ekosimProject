#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <ctime>

#include "city.h"
#include "functions.h"
#include "init_company.h"
#include "functions.h"
#include "SQLfunctions.h"

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

   /*
  	bennyland.load_company("bempa_AB");
  	bennyland.load_company("bempa_co");
  	bennyland.load_company("benny_inc");
  	bennyland.load_company("limpan_AB");
  	bennyland.load_company("benny_enterprises");
  	bennyland.load_company("johansson_och_johansson");
	*/
	initiateCityDB("Bennyland");
	//initiateDB();


	bennyland.add_companies_from_database();
  
  	bennyland.print_company_list(); 

	/*
	* Initiating Database
	*/
	
	//vector<int> vect(13, 10); 
	//insertMoneyData(vect);


  	/*
   	* Creating random consumers. See file functions.cc for settings about the consumers.
   	*/
	bennyland.add_random_consumers(3000);
  	
  	/*
   	* Adding capital owners
   	*/
  	bennyland.add_capital_owners(0.1);
  


  	/*
   	* A check so that no money is lost during the exec.
   	*/
  	double sum_before = bennyland.get_capital_sum();


   	/*
   	* Loading money laundring data
   	*/
	bennyland.load_launder_parameters();
  
  	/*
  	*Preparing output files
   	*/
 	// ofstream empty("gdp_test.txt");
  	// empty << " " << endl;
  	// empty.close();
  
  	// ofstream empty_flash("flash.txt");
  	// empty_flash << " " << endl;
  	// empty_flash.close();
  
  	// ofstream empty_transactions("transactions.txt");
  	// empty_transactions << " " << endl;
  	// empty_transactions.close();
  
   	// ofstream empty_transactions_full("transactions_full.txt");
  	// empty_transactions_full << " " << endl;
  	// empty_transactions_full.close();
	
  	// ofstream  file2 ("money_test.txt");
   	// file2 << "bank_capital" << " " << "bank_loans"  << " " << "bank_debts"  << " " << "consumer_capital"  << " "
	//  << "company_capital" << " " << "market_capital" << " " << "total_capital" << endl;

	/*
  	* Setting basic parameters
   	*/
  	
  	double simulation_years = 2000;
  	bool invest = false;
  	int flashtime = 5;
  	string theThiefString = "";
  	double time_to_steal = bennyland.get_time_to_steal();
  	string theFraudCompanyString = "benny_enterprises";
  	double amount_to_launder = 0;
  	double start_investing = 2;
  	unsigned int timer0 = 0, timer1 = 0, timer2 = 0, timer3 = 0, timer4 = 0, timer5= 0, timer6 = 0;


  	/*
   	* Starting the simulation loop, the functions in it are quite 
   	* clarifying in their names. 
   	*/
 
  	for(int j = 0; j < simulation_years; j++) {
  
  		//Timer checkpoint
  		timer0 = stopwatch();
		cout << "The time is: " <<  getTimeStr() << endl;
  		

    	double time_year = bennyland.get_time();
    	cout << "---------------------------------------------------------------------------------------------------" << endl;
    	cout << "Year: " << time_year << endl;
   		cout << "---------------------------------------------------------------------------------------------------" << endl;
        
        
        
    	cout << endl << "PRICING, EMPLYEES & PRODUCING" << endl;
    	cout << 		"-----------------------------" << endl;
    	cout << "Money: " << bennyland.get_capital_sum() << " Change: " << bennyland.get_capital_sum() - sum_before <<  " Added money: " << bennyland.get_loans_to_bank() << endl;

    	bennyland.update_employees();
    	bennyland.negotiate_market_price();

	
    	bennyland.produce();

		//Timer checkpoint produce
		timer1 = stopwatch();// - timer0;

    	cout << endl << "UPDATING COMPANIES, BUYING & SELLING" << endl;
    	cout << 		"------------------------------------" << endl;
    	cout << "Money: " << bennyland.get_capital_sum() << " Change: " << bennyland.get_capital_sum() - sum_before <<  " Added money: " << bennyland.get_loans_to_bank() << endl;
    
    	if(invest) {
    		//Depreciation of production parameters
      		bennyland.update_companies();
    	}

    	bennyland.save_data();

    	bennyland.sell_to_market();

    	bennyland.consumers_buy();

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
    
    	//Timer checkpoint buy/sell
		timer2 = stopwatch();
	
		cout << endl << "INTERST RATE & INVESTING" << endl;
		cout << 		"------------------------" << endl;
    	cout << "Money: " << bennyland.get_capital_sum() << " Change: " << bennyland.get_capital_sum() - sum_before <<  " Added money: " << bennyland.get_loans_to_bank() << endl;

		bennyland.update_interest_parameters();

		//TESTING OUT INTEREST RATE
		// if (fmod(time_year, 10) == 0) {
	
		// 	if(bennyland.get_bank() -> get_target_interest() == 0.04) {
		// 		bennyland.get_bank() -> set_target_interest(0.02);
		// 	}
		// 	else {
		// 		bennyland.get_bank() -> set_target_interest(0.04);
		// 	}
		// }
    
   		if(invest) { 
      		bennyland.update_interest_rate();
    	}


    	bennyland.invest(invest);
    
    	if(time_year >= start_investing) {
      		invest = true;
    	}

	
		//Timer checkpoint update interest & invest
		timer3 = stopwatch();
	
		cout << endl << "BANK BUSINESS" << endl;	
		cout << 		"-------------" << endl;
    	cout << "Money: " << bennyland.get_capital_sum() << " Change: " << bennyland.get_capital_sum() - sum_before <<  " Added money: " << bennyland.get_loans_to_bank() << endl;

    	if(invest) {
    	
    
   			bennyland.consumers_bank_business();
   			//cout << "Money: " << bennyland.get_capital_sum() << " Change: " << bennyland.get_capital_sum() - sum_before <<  " Added money: " << bennyland.get_loans_to_bank() << endl;
 			bennyland.company_pay_interest();
 			//cout << "Money: " << bennyland.get_capital_sum() << " Change: " << bennyland.get_capital_sum() - sum_before <<  " Added money: " << bennyland.get_loans_to_bank() << endl;
 			bennyland.company_repay_to_bank();
          
    	}
    
   
    	//Timer checkpoint bank business
		timer4 = stopwatch();
 
    	cout << endl << "DIVIDENDS" << endl;
    	cout << 		"---------" << endl;
    	cout << "Money: " << bennyland.get_capital_sum() << " Change: " << bennyland.get_capital_sum() - sum_before <<  " Added money: " << bennyland.get_loans_to_bank() << endl;

 
		//Pay stolen dividends
 		if(fmod(time_year-2,time_to_steal) == 0) {
    
    		//Step 3 generate dividend payment in small batches to our thief
    		bennyland.company_pay_dividends(theFraudCompanyString, theThiefString, amount_to_launder);
    		bennyland.randomize_laundry_parameters();
    		cout << " I main steal 3 " << time_year << " tts " << time_to_steal << "  Mod: " << fmod(time_year,time_to_steal) << endl;
    	}
    	

    	bennyland.company_pay_dividends();
    	bennyland.pay_transfers();
    
		//Timer checkpoint last part
    	timer5 = stopwatch();// - timer4;
		cout << endl << "SAVING DATA" << endl;
		cout << 		"-----------" << endl;
    	cout << "Money: " << bennyland.get_capital_sum() << " Change: " << bennyland.get_capital_sum() - sum_before <<  " Added money: " << bennyland.get_loans_to_bank() << endl;
    
    


    	bennyland.save_money_data();
    	bennyland.adjust_money();
    	bennyland.update_consumer_list();

    	bennyland.tick();
   
   		//Timer checkpoint last part
		timer6 = stopwatch();// - timer5;
		
		cout << endl << "ADDING COMPETITION & CONSUMERS" << endl;
    	cout << 		"------------------------------" << endl;
    // if(time_year == 100) {
//         	bennyland.invest_in_new_company("sara_inc", 25000);
//         	bennyland.add_random_consumers(100, 0);
// 		}

   		cout << endl << "TIME MEASUREMENTS" << endl;
   		cout << 		"--------------------" << endl;
 		cout << "Produce:  " << timer1/10000 << endl;
 		cout << "Buy/sell: " << timer2/10000 << endl;
 		cout << "Int & Iv: " << timer3/10000 << endl;
 		cout << "Bank bus: " << timer4/10000 << endl;
 		cout << "Divs:     " << timer5/10000 << endl;
 		cout << "Sav&up:   " << timer6/10000 << endl;
 		cout << "Total:    " << (timer1 +  timer2 +  timer3 +  timer4 +  timer5)/10000 << endl << endl;
	
	//End of simulation loop
	}

  
  	/*
   	 *  Printing info from the simulation loop. Run "gnuplot gdp.p" and then "gv gdp.eps" to view the output.   
   	 */
  
  
	bennyland.print_GDP();
  	bennyland.print_company_list();  
  	bennyland.market_info();
  	bennyland.consumer_info();
  	bennyland.capital_owners_info();
  	bennyland.bank_info();  

  	/*
   	* A check again so that no money is lost during the exec.
   	*/

  
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
  
};

















