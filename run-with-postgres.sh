#!/bin/bash

# Test script to run the ekosim simulation with PostgreSQL high scores
# This sets the required environment variables and runs the main application

echo "Setting up environment for PostgreSQL high score integration..."

export POSTGRES_HOST=localhost
export POSTGRES_PORT=5432
export POSTGRES_DB=ekosim
export POSTGRES_USER=ekosim
export POSTGRES_PASSWORD=secure_dev_password_2025!
export DATABASE_PATH=/data/ekosim.db

echo "Environment variables set:"
echo "  POSTGRES_HOST=$POSTGRES_HOST"
echo "  POSTGRES_PORT=$POSTGRES_PORT" 
echo "  POSTGRES_DB=$POSTGRES_DB"
echo "  POSTGRES_USER=$POSTGRES_USER"
echo "  DATABASE_PATH=$DATABASE_PATH"

echo ""
echo "Testing PostgreSQL connection first..."
./test_postgres

if [ $? -eq 0 ]; then
    echo ""
    echo "PostgreSQL connection successful! Ready to run simulation with dual high score storage."
    echo ""
    echo "When the simulation completes, high scores will be saved to:"
    echo "  1. SQLite database (existing functionality)"
    echo "  2. PostgreSQL centralized database (new functionality)"
    echo ""
    echo "To run the main simulation, compile with:"
    echo "  make"
    echo ""
    echo "Then run with:"
    echo "  ./main"
    echo ""
    echo "High scores will be automatically saved to both databases when save_high_score() is called."
else
    echo "PostgreSQL connection failed. Please check your database container is running:"
    echo "  podman ps | grep postgres"
    echo ""
    echo "If not running, start it with your docker-compose setup."
fi