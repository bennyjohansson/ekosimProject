#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <random>
#include "functions.h"
#include "consumer.h"
#include "market.h"
#include "clock.h"

using namespace std;

void randomize(double &average, double deviation) {
    
    //std::default_random_engine generator;

    

    //for (int i = 0; i<3; i++) {
        
        //cout << "In functions randomize, my rand: " << number << endl;
    //}
    //int randvalue;
    int randsign;
    double randv;
    
    double limit = deviation*average;
    randv = ((rand()%10))*limit/10;
    
    randsign = (rand()%3);
    if(randsign == 1) {
        randv = -randv;
    }  
    average += randv;
}

double randnorm(double average, double std){

    std::random_device rd;
    std::mt19937 e2(rd());
    std::normal_distribution<double> distribution(average,std);

    double number = distribution(e2);

    number = fmax(0, fmin(1,number));

    return number;


}

void normalize(double & value) {
    if(value < 0) {
        value = 0;
    }
    if(value > 1) {
        value = 1;
    }
}

double get_prod(double sk_sum, double sk, double mot_sum, 
                double mot, double employees, double capacity) {
    

    double rate1 = 0.00000005;  //Funkar bra med 0.000000010;
    double rate2 = 0.000100;
    double rate4 = 0.001; 
//    double rate1 =0.10;
//    double rate2 = 0.0500;


    double prod = 0;
    
    int prod_function = 1;
    //cout << "in functins get prod " << capacity << endl;
    switch (prod_function) {
            
        case 1:
            prod = capacity*atan((sk_sum*sk + mot_sum*mot)*rate4);
            break;
            
        case 2:
            prod = 2*capacity*log((rate2*sk_sum*sk) + (rate2*mot_sum*mot)+1);
            break;
            
        case 3:
            prod = capacity*atan((sk_sum*sk + mot_sum*mot)*rate1*capacity);
            break;
             
        case 4:
            prod = capacity*atan(((rate1*sk_sum*sk) + (rate1*mot_sum*mot)));
            break;    
        
            
        default:
        	cout << "I functions get_prod, no valid production function set" << endl;
            prod = 0;
            break;
    } 
     
    
    return prod;
}

double get_prod(Consumer * consumer, double capacity) {
    
    double skill = consumer -> get_skill();
    double mot = consumer -> get_motivation(); 
    //  cout << "Hej i functions get_prod(Consumer) " << endl;
    return get_prod(skill, skill, mot, mot, 1, capacity);
    //THE 150 ABOVE SHOLUD NOT BE; IS THIS IN USE; TESTING
}

double capacity_increase(double items, double capacity) {
    
    double increase = 0;
    int function_select = 2;
    
    switch (function_select) {
        case 1:
            increase = 30000/capacity*log(items*50/capacity + 1);
            break;
            
        case 2:
        //30 works fine
            increase = 100*log(items + 1);
            break;
            
        case 3:
        //Suitable when using factor increase
            increase = 0.6*items;
            break;
            
        case 4:
        //0.01 ger sjunkande GDP och 0.05 ökande 
            increase = 0.1*items;
            break;
            
            
        default:
            increase = 0;
            break;
    }
    
       
    return increase;
}

double factor_increase(double items, double sk, double mot, double capacity) {

 //Function not completed
 //Best idea is probably to call both capacity increase and factor increase from company etc. 
//Bör sannolikt vara korrelerad med capacity - dyrare att effektivisera något stort än något litet
// Bör inte finnas något tak typ att 1 är max
//Kan man tänka sig att kostnad för typ 5% ökning är direkt proportionell mot capacity eller behövs någon icke-linjär funktion?
    double f_increase = 0;
    int function_select = 3;
    
    
    switch (function_select) {
        case 1:
            f_increase = 2;
            break;
            
        case 2:
        //Used
            f_increase = 0.5*log(0.1*items/capacity + 1);
            break;
            
        case 3:
        //Used 0.025 which was good
            f_increase = 0.25*items/capacity;
            break;     
            
        default:
            f_increase = 0;
            break;
    }
    
       
    return f_increase;
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
    
    double price = 0;
    if(excess != 0) {
        return price = sum_spend/excess;
    }
    else {
        return 1000000;
    }
}

Consumer * random_consumer(Market * market, Bank * bank, Clock * clock) {
    
    /* 
     * Default values for consumers
     *
     *
     */
    
    double mot = 0.6;
    double sk = 0.5;
    double cap = 100; 
    double spe = 0.7;
    double save = 0.7; //1-spe; Was 0.05 2020-03-26
    double borrow = 0.010; //Was 0.02 2020-04-01
    
    
    randomize(mot, 0.7);
    randomize(sk, 0.7);
    randomize(cap, 1);
    randomize(spe, 0.5);
    randomize(save, 0.5);
    randomize(borrow, 0.2);
    normalize(spe);
    normalize(sk);
    normalize(mot);
    normalize(save);
    normalize(borrow);
    return new Consumer(mot,sk,cap,spe, save, borrow, market, bank, clock);
}




double item_cost(double production) {
    
    double items = 0;
    const double factor = 0.1;
    
    items = factor*production;//log(production + 1)*(factor);
    
    return items;
}



double get_consumer_deposit(double savewill, double capital, double interest) {
    
    double amount = 0;
    int function_select = 2;
    
    
    switch (function_select) {
        case 1:
            if(capital > 0) {
                amount = fmax(savewill*capital*interest, 0);
            }
            else {
                amount = 0;
            }
            
            break;
        case 2:
            if(capital > 0) {
                amount = fmax(savewill*capital*atan(100*interest)/(3.1415/2), 0);
                //cout << "I functions get_cons_dep atan, depositing " << amount/capital << " %" << endl;
            }
            else {
                amount = 0;
            }
        
        case 3:
            if(capital > 0) {
            	amount = 0;
            }
            else {
                amount = 0;
            }
            
        default:
            break;
    }
    
    return amount;
    
}

double get_consumer_borrow(double borrowwill, double assets, double loans, double debt, double interest) {
    
    double amount = 0;
    //double factor = 5;
    double max_leverage = 1;
    
    int function_select = 2;
    
    switch (function_select) {
        case 1:
            if(assets > 0) {
                amount = fmax(borrowwill*assets/(1+100*interest), 0);
            }
            else {
                amount = 0;
            }
            
            break;
		case 2:
            if(assets > 0) {
                amount = fmax(borrowwill*exp(-0.1*interest)*((1+max_leverage)*(assets + loans) - debt), 0);
            }
            else {
                amount = 0;
            }
            
            break;
        case 3:
            amount = 0;
            break;
        
        default:
            break;
    }
    return amount;
}

double get_consumer_demand_cash(double spendwill, double capital) {

	double amount_cash = 0;
	
	amount_cash = capital * spendwill;
	
	
	return amount_cash;

}

double get_consumer_demand_deposit(double spendwill, double loans, double interest) {

	double amount_bank = 0;
	
	amount_bank = loans * spendwill*fmin(1,exp(-interest));
	//amount_bank = loans_ * spendwill_;
	
	
	return amount_bank;

}





void log_transaction(string party, double amount, string type, double time) {

    bool writeToFile = false;

    if(writeToFile) {
        ofstream  file1 ("transactions.txt", ios::app);
        
        file1 << time << " " << party << " " << amount << " " << type << endl;
        
        file1.close();
    }

}

void log_transaction_full(string party_pay, string party_receive, double amount, string type, double time, int fraud /* = 42 */) {

     bool writeToFile = false;

    if(writeToFile) {
        ofstream  file1 ("transactions_full.txt", ios::app);
        
        file1 << time << " " << amount << " " << party_pay << " " << party_receive << " "  << type << " " << fraud << endl;
        
        file1.close();
    }

}

void log_launder_parameters(double shareToSteal, double laundry_factor, int no_years_laundry, int time_to_steal) {


	ofstream  file1 ("launder_data.txt", ios::app);
	
    file1 << shareToSteal << " "  << laundry_factor << " " << no_years_laundry << " "  << time_to_steal << endl;
    
    file1.close();

}

unsigned int stopwatch() {


	static auto start_time = chrono::steady_clock::now();
	
	auto end_time = chrono::steady_clock::now();
	
	auto delta = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
	
	start_time =  end_time;
	
	return delta.count();
	

}

string getTimeStr(){
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    std::string s(30, '\0');
    std::strftime(&s[0], s.size(), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return s;
}





