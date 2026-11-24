# EkoSim - Economic Simulation Engine

**C++ Backend & Simulation Core**

## Overview

This is the core simulation engine of EkoSim - a sophisticated economic simulation system written in C++17. It models macroeconomic systems including cities, companies, consumers, banks, and markets with realistic economic cycles.

## What It Does

- **Economic Modeling**: Simulates complete economic systems with multiple interacting agents
- **Multi-City Support**: Each city (country) has independent economic parameters and markets
- **Company Simulation**: Production, pricing, employment, and market dynamics
- **Consumer Behavior**: Individual consumers with employment, consumption, and savings
- **Banking System**: Interest rates, loans, deposits, and monetary policy
- **Market Dynamics**: Supply/demand equilibrium, price discovery, and trade cycles
- **Time-Based Evolution**: Discrete time steps with production, sales, and pricing cycles

## Architecture

### Core Classes

- `World` - Global simulation container managing all cities
- `City` - Individual economic region with local parameters
- `Company` - Production entities with employees and inventory
- `Consumer` - Economic agents with consumption and employment
- `Bank` - Financial institution managing monetary policy
- `Market` - Price discovery and trade matching engine
- `Clock` - Time management and simulation cycles

### Simulation Cycles

1. **Employee Cycle** - Hiring, firing, wage adjustments
2. **Pricing Cycle** - Market price discovery based on supply/demand
3. **Production Cycle** - Companies produce goods
4. **Sales Cycle** - Consumers purchase from companies

## Technology Stack

- **Language**: C++17
- **Compiler**: clang++ with -std=c++17
- **Databases**:
  - SQLite (legacy data storage)
  - PostgreSQL (primary database for multi-user support)
- **Build System**: Make
- **Container**: Dockerized for consistent deployment

## Database Schema

Writes simulation state to PostgreSQL tables:

- `parameters` - Economic parameters per city
- `company_data` - Company metrics over time
- `time_data` - Economic indicators time series
- `money_data` - Monetary metrics time series
- `world_table` - Cross-city rankings
- `high_scores` - Historical performance metrics

## Running the Simulation

### Local Development

```bash
make clean && make
./main
```

### Docker (Production)

```bash
docker-compose up ekosim-backend
```

The simulation runs continuously, executing economic cycles and writing results to the database for visualization by the frontend.

## Key Features

- **Real-time Economics**: Continuous simulation with configurable time steps
- **Multi-tenancy**: Support for multiple isolated economic worlds
- **Persistent State**: All state stored in PostgreSQL for durability
- **API Integration**: Reads parameters from and writes results to database
- **Scalable Design**: Can simulate hundreds of companies and thousands of consumers

## Configuration

Economic parameters are stored in the PostgreSQL `parameters` table and can be modified in real-time through the web API, allowing users to experiment with different economic policies.

## Dependencies

- libsqlite3-dev
- libpq-dev (PostgreSQL client)
- Standard C++ libraries

---

**Part of the EkoSim Platform** - See also:

- [EkoWeb](../EkoWeb/README.md) - API server and web frontend
- [EkoSim-Infrastructure](../EkoSim-Infrastructure/README.md) - Docker orchestration

## Stability behavior

The GDP report uses the city's recorded wage totals for each cycle and displays
zero for missing samples. GDP growth is zero until there is a nonzero prior GDP
sample. Wage history averages the samples available within the requested
window. The simulator skips wage-based monetary adjustments until it has
positive current and historical wages and the initial ten cycles have passed.

PostgreSQL waits default to 5,000 ms per connection attempt and 10,000 ms per
statement. Set `POSTGRES_CONNECT_TIMEOUT_MS` and
`POSTGRES_STATEMENT_TIMEOUT_MS` to positive integers up to 3,600,000 to
override them. The connection deadline covers socket polling and the PostgreSQL
handshake. Hostname lookup uses the system resolver. Set
`POSTGRES_HOSTADDR` to a numeric address to avoid that lookup.

The server and client both enforce the statement limit. The client closes the
connection if the server stops responding. PostgreSQL then rolls back any
uncommitted work on that connection. A failed consumer write rolls back that
city's whole snapshot. The simulator reports failed snapshots and continues
with the next world run. It does not retry individual statements or an
ambiguous commit.

Investment evaluates up to 256 candidate quantities using the existing
10,000-item step, starting with four items. The last candidate may be smaller
when stock or financing is limited. The company selects the last feasible
quantity whose net present value did not decline. Invalid inputs or a negative
first net present value produce a zero investment. Loan cost calculations
accept terms up to 1,200 monthly payments.

Build the simulator and the stability regressions with:

```sh
make -B main stability-tests
```

Run `./test_stability_investment` for investment cases. Run
`./test_stability_lifecycle` and `./test_stability_postgres` with
`POSTGRES_*` set for a disposable database. The PostgreSQL regression creates
and drops its own `consumer_data` table and requires that table to be absent
at startup. Test an unavailable endpoint with
`POSTGRES_PORT=1 POSTGRES_CONNECT_TIMEOUT_MS=150 ./test_stability_postgres --unavailable`
when the configured host has nothing listening on port 1.
