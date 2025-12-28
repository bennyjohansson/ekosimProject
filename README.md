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
