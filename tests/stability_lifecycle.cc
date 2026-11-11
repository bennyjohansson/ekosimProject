#include "world.h"

#include <cassert>
#include <cstdlib>

int main()
{
    std::srand(42);
    World world("stability regression");
    City& city = *world.get_city("Bennyland");
    city.add_random_consumers(20);
    city.update_parameters_from_database();
    city.add_company("Bankrupt");
    city.get_company("Bankrupt")->set_capital(0);
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
