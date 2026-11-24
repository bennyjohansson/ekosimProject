#include "world.h"

#include <cassert>
#include <cstdlib>

void test_bankruptcy_and_reporting()
{
    World world("stability regression");
    City& city = *world.get_city("Bennyland");
    city.add_random_consumers(20);
    city.update_parameters_from_database();
    city.add_company("Bankrupt");
    Company& bankrupt = *city.get_company("Bankrupt");
    assert(bankrupt.get_average_wage() == 0);
    assert(bankrupt.get_average_wage_historical(6) == 0);
    bankrupt.wages_.push_front(3);
    bankrupt.wages_.push_front(5);
    assert(bankrupt.get_average_wage_historical(6) == 4);
    bankrupt.set_capital(0);
    city.adjust_money();
    city.print_GDP();

    assert(world.run_dividend_cycle());
    assert(city.get_no_companies() == 0);
    assert(city.get_random_company() == nullptr);

    for (int cycle = 0; cycle < 12; ++cycle)
    {
        assert(world.run_employee_cycle());
        assert(world.run_pricing_cycle());
        assert(world.run_production_cycle());
        assert(world.run_sales_cycle());
        assert(world.run_investment_cycle());
        assert(world.run_banking_cycle());
        assert(world.run_dividend_cycle());
        assert(world.run_adjust_money_and_consumer_cycle());
        assert(world.run_save_cycle());
        world.tick();
    }
    assert(city.get_no_companies() == 0);
    assert(city.GDP_.size() == 12);
    assert(city.get_loans_to_bank() == 0);
    world.print_GDP();
}

int main()
{
    std::srand(42);
    test_bankruptcy_and_reporting();

    for (int reset = 0; reset < 20; ++reset)
    {
        World world("reset regression");
        world.add_city(new City("second", world.get_clock(), world.get_global_market()));
        for (const char* name : {"Bennyland", "second"})
        {
            City& city = *world.get_city(name);
            city.add_random_consumers(3000);
            city.add_capital_owners(0.3);
            city.add_company("Bankrupt");
            city.add_company("Survivor");
            city.add_random_shareholders(20);
            Company* bankrupt = city.get_company("Bankrupt");
            Consumer* employee = city.get_random_consumer();
            bankrupt->add_employee(employee);
            bankrupt->set_capital(0);
        }
        assert(world.run_dividend_cycle());
        assert(world.get_city("Bennyland")->get_no_companies() == 1);
        assert(world.get_city("second")->get_no_companies() == 1);
    }
}
