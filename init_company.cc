#include <iostream>
#include <iomanip> 

#include "city.h"
#include "company.h"
#include "market.h"
#include "clock.h"
#include "init_company.h"
#include "bank.h"

using namespace std;

void init_companies(City * bennyland) {
  
  Company * company = 0;
  string name = "";
  double capital = 0;
  double stock = 0;
  double capacity = 1000;
  double prod_const_skill = 0;
  double prod_const_mot = 0;
  double wage_const = 0.75;
  double pbr = 0.55;
  Market * market = 0;
  Clock * clock = 0;
  Bank * bank = 0;

  // -------------------------------------------------------------------------------------------------------------
  name = "bempa AB";  
  capital = 50000;
  stock = 0;
  //capacity = 500;
  prod_const_skill = 60;  
  prod_const_mot = 50;
  //wage_const = 0.5;
  //pbr = 0.3;
  market = bennyland -> get_market();
  clock = bennyland -> get_clock();
  bank = bennyland -> get_bank();

  company = new Company(name, capital, stock, capacity, prod_const_skill, prod_const_mot, wage_const, pbr, market, bank, clock);
  bennyland -> add_company(company);

  
  // -------------------------------------------------------------------------------------------------------------
  name = "bempa co";
  capital = 50000;
  stock = 0;
  //  capacity = 500;
  prod_const_skill = 60;  
  prod_const_mot = 50;
  //wage_const = 0.5;
  //pbr = 0.6;
  market = bennyland -> get_market();
  clock = bennyland -> get_clock();
  bank = bennyland -> get_bank();

  company = new Company(name, capital, stock, capacity, prod_const_skill, prod_const_mot, wage_const, pbr, market, bank, clock);
  bennyland -> add_company(company);

  // -------------------------------------------------------------------------------------------------------------
  name = "benny inc.";
  capital = 50000;
  stock = 0;
  //capacity =500;
  prod_const_skill = 60;  
  prod_const_mot = 50;
  //wage_const = 0.4;
  //pbr = 0.6;
  market = bennyland -> get_market();
  clock = bennyland -> get_clock();
  bank = bennyland -> get_bank();

  company = new Company(name, capital, stock, capacity, prod_const_skill, prod_const_mot, wage_const, pbr, market, bank, clock);
  bennyland -> add_company(company);

  // -------------------------------------------------------------------------------------------------------------
  name = "limpan AB";
  capital = 50000;
  stock = 0;
  //capacity = 500;
  prod_const_skill = 60;  
  prod_const_mot = 50;
  //wage_const = 0.6;
  //pbr = 0.6;
  market = bennyland -> get_market();
  clock = bennyland -> get_clock();
  bank = bennyland -> get_bank();

  company = new Company(name, capital, stock, capacity, prod_const_skill, prod_const_mot, wage_const, pbr, market, bank, clock);
  bennyland -> add_company(company);

  // -------------------------------------------------------------------------------------------------------------
  name = "benny enterprises";
  capital = 50000;
  stock = 0;
  //capacity = 500;
  prod_const_skill = 60;  
  prod_const_mot = 50;
  //wage_const = 0.5;
  //pbr = 0.6;
  market = bennyland -> get_market();
  clock = bennyland -> get_clock();
  bank = bennyland -> get_bank();

  company = new Company(name, capital, stock, capacity, prod_const_skill, prod_const_mot, wage_const, pbr, market, bank, clock);
  bennyland -> add_company(company);

  // -------------------------------------------------------------------------------------------------------------
  name  = "johansson och johansson";
  capital = 50000;
  stock = 0;
  //capacity = 600;
  prod_const_skill = 60;  
  prod_const_mot = 50;
  //wage_const = 0.5;
  //pbr = 0.6;
  market = bennyland -> get_market();
  clock = bennyland -> get_clock();
  bank = bennyland -> get_bank();

  company = new Company(name, capital, stock, capacity, prod_const_skill, prod_const_mot, wage_const, pbr, market, bank, clock);
  bennyland -> add_company(company);


}
