#include "company.h"

#include <cassert>
#include <limits>

int main()
{
    Market market("test");
    Bank bank("test", 0.04, 3);
    Clock clock;
    Consumer employee(1, 1, 0, 0, 0, 0, "Bennyland", &market, nullptr, &bank, &clock);
    Company company("test", "Bennyland", 100000, 0, 100000, 50, 50,
                    0.2, 0.5, &market, nullptr, &bank, &clock);
    company.add_employee(&employee);

    const auto decision = [&] {
        return company.get_desired_investment(0.002, 1e9, 1e-6, 0.001);
    };
    market.set_items(100000);
    market.set_price_out(2);
    assert(company.get_desired_investment(0, 0, 0, 0) == 0); // The first candidate has a negative NPV.

    assert(decision() == 100000); // Positive NPV through the available stock.
    market.set_items(5001);
    assert(decision() == 5001);
    market.set_items(3.5);
    assert(decision() <= 3);
    market.set_items(0);
    assert(decision() == 0);

    market.set_items(std::numeric_limits<double>::max());
    market.set_price_out(0.000000002);
    assert(decision() == 2550004);
    assert(company.invest(0.002, 1e9, 1e-6, 0.001) > 0);
    market.set_items(std::numeric_limits<double>::quiet_NaN());
    assert(decision() == 0);
    market.set_items(10000);
    market.set_price_out(std::numeric_limits<double>::infinity());
    assert(decision() == 0);
    assert(company.invest(0.002, 1e9, 1e-6, 0.001) == 0);

    market.set_price_out(0.1);
    company.set_debts(2 * company.get_capital());
    assert(decision() == 0);
    Company borrower("borrower", "Bennyland", 100000, 0, 100000, 50, 50,
                     0.2, 0, &market, nullptr, &bank, &clock);
    Consumer borrower_employee(1, 1, 0, 0);
    borrower.add_employee(&borrower_employee);
    bank.set_capital(0);
    assert(borrower.get_desired_investment(0.002, 1e9, 1e-6, 0.001) == 0);
    bank.set_capital(30);
    const int financed = borrower.get_desired_investment(0.002, 1e9, 1e-6, 0.001);
    assert(financed > 0 && financed <= 300);
    bank.set_capital(100000);
    bank.set_payback_time(std::numeric_limits<double>::max());
    assert(borrower.get_desired_investment(0.002, 1e9, 1e-6, 0.001) == 0);
}
