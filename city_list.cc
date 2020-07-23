#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <exception>
#include <stdexcept>

#include "city_list.h"
#include "error_no_return.h"

using namespace std;

City_list::City_list(string name) :
list_(new Element_city(0, new City("Bennyland"))),
size_(1), 
name_(name)
{}

/*
 * Functions to add cities
 */ 

City * City_list::get_city(string name) {
    Element_city * p;
    
    if(list_) {
        for(p = list_; p; p = p -> next_) {
            if (p ->get_name() == name) {
                return p -> get_city() ;
            }
        }
        throw no_return_error("Cant find the city");
    }
    else {
        throw no_return_error("no list"); 
    } 
}

/*
 * Functions to add cities
 */ 

void City_list::add_city(City * city) {
    Element_city * p;
    size_++;
    
    if(list_) {
        list_ = new Element_city(list_, city);
    }
    else {
        list_ = new Element_city(0, city);
    }
}


/*
 * Info-functions
 */

void City_list::info() {
    cout << endl << "CITIES" << endl << "----------------------------------------------------------" << endl; 
    cout << "Number of cities: " << size_ << endl << endl;
}


void City_list::print_list() {
    
    info();
    if(list_) {
        for (Element_city *p = list_; p; p = p -> next_) {
            p->city_->info();
        }
    }
    
    cout << endl; 
}
