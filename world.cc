#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <cstring>

// #include "SQLfunctions.h"
// #include "functions.h"
#include "world.h"

using namespace std;

World::World(string name) : name_(name),
                          cities_(new City_list("CITIES"))
{}

void World::print_cities() {

    cities_ -> print_list();


}

void World::initiate_city(string city_name) {

    City * myCity;
    
    myCity = cities_ -> get_city(city_name);

    /*
   	* Creating random consumers. See file functions.cc for settings about the consumers.
   	*/
	myCity -> add_random_consumers(3000);
  	
  	/*
   	* Adding capital owners
   	*/
  	myCity -> add_capital_owners(0.1);



}
