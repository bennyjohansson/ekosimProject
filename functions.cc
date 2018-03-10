#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "functions.h"
#include "consumer.h"
#include "market.h"
#include "clock.h"

using namespace std;

void randomize(double &average, double deviation) {
    
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
    
    double rate1 =0.10;
    double rate2 = 0.0500;
    double prod = 0;
    
    int prod_function = 1;
    
    switch (prod_function) {
            
        case 1:
            prod = capacity*atan(((rate1*sk_sum*sk) + (rate1*mot_sum*mot)));
            break;
            
        case 2:
            prod = 2*capacity*log((rate2*sk_sum*sk) + (rate2*mot_sum*mot)+1);
            break;
            
        
            
        default:
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

Consumer * random_consumer(Market * market, Bank * bank, Clock * clock) {
    
    /* 
     * Default values for consumers
     *
     *
     */
    
    double mot = 0.6;
    double sk = 0.5;
    double cap = 70; 
    double spe = 0.4;
    double save = 0.05; //1-spe;
    double borrow = 0.080;
    
    
    randomize(mot, 0.7);
    randomize(sk, 0.7);
    randomize(cap, 1);
    randomize(spe, 0.5);
    randomize(save, 0.4);
    randomize(borrow, 0.2);
    normalize(spe);
    normalize(sk);
    normalize(mot);
    normalize(save);
    normalize(borrow);
    return new Consumer(mot,sk,cap,spe, save, borrow, market, bank, clock);
}


double capacity_increase(double items, double capacity) {
    
    double increase = 0;
    int function_select = 2;
    
    
    switch (function_select) {
        case 1:
            increase = 30000/capacity*log(items*50/capacity + 1);
            break;
            
        case 2:
            increase = 30*log(items*0.003 + 1);
            break;
            
            
        default:
            increase = 0;
            break;
    }
    
    return increase;
}

double item_cost(double production) {
    
    double items = 0;
    const double factor = 0.1;
    
    items = factor*production;//log(production + 1)*(factor);
    
    return items;
}



double get_consumer_loan(double loanwill, double capital, double interest) {
    
    double amount = 0;
    int function_select = 1;
    
    switch (function_select) {
        case 1:
            if(capital > 0) {
                amount = loanwill*capital*interest;
            }
            else {
                amount = 0;
            }
            
            break;
        case 2:
            if(capital > 0) {
                amount = loanwill*capital*atan(10*interest)/(3.1415/2);
            }
            else {
                amount = 0;
            }
            
        default:
            break;
    }
    
    
    return amount;
    
}


double get_consumer_borrow(double borrowwill, double capital, double interest) {
    
    double amount = 0;
    double factor = 5;
    
    int function_select = 2;
    
    switch (function_select) {
        case 1:
            if(capital > 0) {
                amount = borrowwill*capital/(1+100*interest);
            }
            else {
                amount = 0;
            }
            
            break;
            
        case 2:
            amount = 0;
            break;
            
        default:
            break;
    }
    return amount;
}


void log_transaction(string party, double amount, string type, double time) {


	ofstream  file1 ("transactions.txt", ios::app);
	
    file1 << time << " " << party << " " << amount << " " << type << endl;
    
    file1.close();

}

void log_transaction_full(string party_pay, string party_receive, double amount, string type, double time) {


	ofstream  file1 ("transactions_full.txt", ios::app);
	
    file1 << time << " " << amount << " " << party_pay << " " << party_receive << " "  << type << endl;
    
    file1.close();

}




