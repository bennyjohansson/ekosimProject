#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <ctime>

#include "world.h"
#include "city.h"
#include "functions.h"
// #include "init_company.h"
#include "functions.h"
#include "SQLfunctions.h"

using namespace std;

int main()
{

	/*
   	* Starting a clock for randomizing later on
   	*/

	srand(static_cast<unsigned>(time(0)));

	while (1)
	{
		/*
   	* Creating bennyworld
   	*/

		World bennyworld("Bennyworld");
		initiateWorldDB("Bennyworld");

		/*
	* Adding default country
	*/

		initiateCityDB("Bennyland");
		bennyworld.initiate_city("Bennyland");

		/*
	* Adding another city
	*/
		bennyworld.add_city("Saraland", "eriksson.sara83@gmail.com");

		/*
	* Printing world database
	*/
		bennyworld.printWorldDB();
		/*
   	* A check so that no money is lost during the exec.
   	*/
		double sum_before_BL = bennyworld.get_city("Bennyland")->get_capital_sum();
		double sum_before_SL = bennyworld.get_city("Saraland")->get_capital_sum();
		/*
	* Setting parameters
	*/

		int simulation_cycles = 100;
		int current_cycle = 0;
		unsigned int timer0 = 0, timer1 = 0, timer2 = 0, timer3 = 0, timer4 = 0, timer5 = 0, timer6 = 0;

		for (int j = 0; j < simulation_cycles; j++)
		{

			//Timer checkpoint
			timer0 = stopwatch();

			current_cycle = bennyworld.get_time();

			cout << "---------------------------------------------------------------------------------------------------" << endl;
			cout << "Year: " << current_cycle << endl;
			cout << "---------------------------------------------------------------------------------------------------" << endl;

			cout << endl
				 << "PRICING, EMPLYEES & PRODUCING" << endl;
			cout << "-----------------------------" << endl;

			bennyworld.run_production_cycle();

			//Timer checkpoint produce
			timer1 = stopwatch();

			cout << endl
				 << "UPDATING COMPANIES, BUYING & SELLING" << endl;
			cout << "------------------------------------" << endl;

			bennyworld.run_sales_cycle();

			//Timer checkpoint buy/sell
			timer2 = stopwatch();

			cout << endl
				 << "INTERST RATE & INVESTING" << endl;
			cout << "------------------------" << endl;

			bennyworld.run_investment_cycle();

			//Timer checkpoint update interest & invest
			timer3 = stopwatch();

			cout << endl
				 << "BANK BUSINESS" << endl;
			cout << "-------------" << endl;

			bennyworld.run_banking_cycle();

			//Timer checkpoint bank business
			timer4 = stopwatch();

			cout << endl
				 << "DIVIDENDS & TRANSFERS" << endl;
			cout << "---------" << endl;

			bennyworld.run_dividend_cycle();
			bennyworld.run_adjust_money_and_consumer_cycle();

			//Timer checkpoint last part
			timer5 = stopwatch(); // - timer4;
			cout << endl
				 << "SAVING DATA" << endl;
			cout << "-----------" << endl;

			bennyworld.run_save_cycle();

			bennyworld.tick();

			//Timer checkpoint last part
			timer6 = stopwatch(); // - timer5;

			cout << endl
				 << "UPDATING AND ADDING COMPETITION & CONSUMERS" << endl;
			cout << "------------------------------" << endl;
			bennyworld.update_companies_from_database();
			bennyworld.write_time_data_to_company_database();
			bennyworld.update_country_from_database();

			cout << "Money: " << bennyworld.get_city("Bennyland")->get_capital_sum() << " Change: " << bennyworld.get_city("Bennyland")->get_capital_sum() - sum_before_BL << " Added money: " << bennyworld.get_city("Bennyland")->get_loans_to_bank() << endl;
			cout << "Money: " << bennyworld.get_city("Saraland")->get_capital_sum() << " Change: " << bennyworld.get_city("Saraland")->get_capital_sum() - sum_before_SL << " Added money: " << bennyworld.get_city("Saraland")->get_loans_to_bank() << endl;

			// if(current_cycle == 20) {

			// 	City * Saraland = bennyworld.get_city("Saraland");
			// 	City * Bennyland = bennyworld.get_city("Bennyland");
			// 	Market * BMarket = Bennyland -> get_market();
			// 	Saraland->set_market(BMarket);

			// }

			cout << endl
				 << "TIME MEASUREMENTS" << endl;
			cout << "--------------------" << endl;
			cout << "Produce:  " << timer1 / 10000 << endl;
			cout << "Buy/sell: " << timer2 / 10000 << endl;
			cout << "Int & Iv: " << timer3 / 10000 << endl;
			cout << "Bank bus: " << timer4 / 10000 << endl;
			cout << "Divs:     " << timer5 / 10000 << endl;
			cout << "Sav&up:   " << timer6 / 10000 << endl;
			cout << "Total:    " << (timer1 + timer2 + timer3 + timer4 + timer5) / 10000 << endl
				 << endl;

			/*
		* END OF MAIN LOOP
		*/
		}

		/*
	* SAVING CONSUMERS
	*/
		cout << endl
			 << "SAVING CONSUMERS" << endl;
		cout << "------------------------------" << endl;
		if (1)
		{
			bennyworld.save_consumers();
		}

		/*
	* UPDATING HIGH-SCORE
	*/
		cout << endl
			 << "SAVING HIGH-SCORE" << endl;
		cout << "------------------------------" << endl;
		bennyworld.save_high_score();

		/*
	* Closing functions
	*/

		bennyworld.print_GDP();
	}
}