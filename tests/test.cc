#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <ctime>

//#include "consumer.h"
//#include "consumer_list.h"
//#include "city.h"
//#include "company.h"
//#include "company_list.h"
//#include "element.h"
#include "functions.h"
#include "city.h"
//#include "company.h"
//#include "company_list.h"
//#include "element.h"
#include "functions.h"

using namespace std;

int main() {

	City bennyland("Bennyland");
	
	bennyland.load_company("benny_enterprises");
	
	cout << "CF: " << bennyland.get_random_company() -> get_investment_cashflow(1000, 0) << endl;

	cout << "hello world!" << endl;
	cout << get_consumer_loan(3,3,3) << endl;
	
	double loanwill = 0.7;
	double borrowwill = 0.1;
	double loans = 0;
	double debt = 0;
	double capital = 1000;
	double interest = 0;
	
	
	for (int i = 0; i<100; i++) {
	
		cout << "Ir: " << interest << "  " << get_consumer_loan( loanwill,  capital,  interest) << "  " <<  get_consumer_borrow( borrowwill,  capital,  loans,  debt,  interest) << endl;
		interest += 0.01;
	
	}

};