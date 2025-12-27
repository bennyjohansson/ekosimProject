#include <iostream>
#include <sqlite3.h>
#include <stdio.h>
#include <vector>
#include <cstring>
#include <cmath>
#include <fstream>
#include "SQLfunctions.h"
#include "PostgreSQLManager.h"

// Amazon linux
// #include "/usr/include/mysql/mysql.h"

// Mac OSX
// #include "/usr/local/Cellar/mysql/8.0.23_1/include/mysql/mysql.h"

using namespace std;
// namespace fs = std::filesystem;
// using Record = std::vector<std::string>;
// using Records = std::vector<Record>;
using Record = vector<string>;
using Records = vector<Record>;

// int initiateDB()
// {

//     const char *dir = get_sql_string(); //"/var/app/current/myDB/ekosimDB.db";
//     cout << "Using database path: " << dir << endl;
//     //string dir = get_sql_string();
//     sqlite3 *DB;

//     cout << "INITIATING DATABASE" << endl;
//     cout << "-------------------" << endl;
//     //Creating the database
//     createDB(dir);

//     //Creating tables
//     createParameterTable(dir);
//     createDataTable(dir);
//     createMoneyTable(dir);
//     createCompanyTable(dir);
//     createHighScoreTable(dir);

//     cout << endl;

//     //Deleting old data
//     deleteTheData(dir);

//     cout << endl;

//     //Setting initial parameters
//     insertParameterData(dir);
//     initiateCompanyTable(dir);

//     cout << endl;

//     selectData(dir);

//     sqlite3_close(DB);
//     return 0;
// };

int initiateCityDB(string city_name)
{

    string full_path = get_city_sql_string(city_name);
    const char *dir = full_path.c_str();

    cout << "I SQL Functions initiate city db, using database path: " << dir << endl;
    // string dir = get_sql_string();
    // sqlite3* DB;

    cout << "INITIATING CITY DATABASE" << endl;
    cout << "-------------------" << endl;

    // Creating the database
    createDB(dir);

    // Creating tables
    createParameterTable(dir);
    createDataTable(dir);
    createMoneyTable(dir);
    createCompanyTable(dir);
    createConsumerTable(dir);

    // Creating mySQL tables
    createSQLParameterTable("Bennyland");

    cout << endl;

    // Deleting old data
    deleteTheData(dir);

    cout << endl;

    // Setting initial parameters
    insertParameterData(dir);
    initiateCompanyTable(dir);

    // Initialize PostgreSQL company data
    initiateCompanyTablePG(city_name);

    cout << "I SQL functions initiate city db" << endl;

    // selectData(dir);

    // sqlite3_close(DB);
    return 0;
};

int initiateWorldDB(string world_name)
{

    string full_path = get_city_sql_string(world_name);
    const char *dir = full_path.c_str();

    cout << "I SQL Functions initiate World db, using database path: " << dir << endl;
    // string dir = get_sql_string();
    // sqlite3* DB;

    cout << "INITIATING WORLD DATABASE" << endl;
    cout << "-------------------" << endl;

    // Creating the database
    createDB(dir);

    // Creating tables
    createWorldTable(dir);
    createHighScoreTable(dir);

    cout << endl;

    // Deleting old data
    deleteWorldData(dir);

    cout << endl;

    // selectData(dir);

    // sqlite3_close(DB);
    return 0;
};

static int selectData(const char *s)
{

    sqlite3 *DB;

    // int exit = sqlite3_open(s, &DB);
    double myData = 0;

    string sql = "SELECT * FROM MONEY_DATA";

    // string name = "'InterestRateMethod'";
    // sql.append(name);
    // cout <<  sql << endl;
    sqlite3_exec(DB, sql.c_str(), callback, &myData, NULL);
    sqlite3_close(DB);
    return 0;
}

int select_callback(void *p_data, int num_fields, char **p_fields, char **p_col_names)
{
    Records *records = static_cast<Records *>(p_data);
    try
    {
        records->emplace_back(p_fields, p_fields + num_fields);
    }
    catch (...)
    {
        // abort select on failure, don't let exception propogate thru sqlite3 call-stack
        return 1;
    }
    return 0;
}

// PostgreSQL version of select_stmt
Records select_stmt_pg(string sql, string city_name)
{
    Records records;
    PostgreSQLManager pgManager;

    if (!pgManager.connect())
    {
        cerr << "Failed to connect to PostgreSQL for select query: " << pgManager.getLastError() << endl;
        return records;
    }

    // Replace SQLite-style table names with PostgreSQL equivalents
    // PARAMETERS -> parameters, CONSUMER_TABLE -> consumer_data, etc.
    string pg_sql = sql;

    // Convert to lowercase and replace table names
    size_t pos = 0;
    while ((pos = pg_sql.find("PARAMETERS", pos)) != string::npos)
    {
        pg_sql.replace(pos, 10, "parameters");
        pos += 10;
    }
    pos = 0;
    while ((pos = pg_sql.find("CONSUMER_TABLE", pos)) != string::npos)
    {
        pg_sql.replace(pos, 14, "consumer_data");
        pos += 14;
    }
    pos = 0;
    while ((pos = pg_sql.find("COMPANY_TABLE", pos)) != string::npos)
    {
        pg_sql.replace(pos, 13, "company_data");
        pos += 13;
    }
    pos = 0;
    while ((pos = pg_sql.find("TIME_DATA", pos)) != string::npos)
    {
        pg_sql.replace(pos, 9, "time_data");
        pos += 9;
    }
    pos = 0;
    while ((pos = pg_sql.find("MONEY_DATA", pos)) != string::npos)
    {
        pg_sql.replace(pos, 10, "money_data");
        pos += 10;
    }

    // Add WHERE clause for city_name if not already present and if table supports it
    bool has_where = (pg_sql.find("WHERE") != string::npos || pg_sql.find("where") != string::npos);
    bool is_parameters_query = (pg_sql.find("parameters") != string::npos);
    bool is_consumer_query = (pg_sql.find("consumer_data") != string::npos);
    bool is_company_query = (pg_sql.find("company_data") != string::npos);
    bool is_time_query = (pg_sql.find("time_data") != string::npos);
    bool is_money_query = (pg_sql.find("money_data") != string::npos);

    if (!city_name.empty() && !has_where && (is_parameters_query || is_consumer_query || is_company_query || is_time_query || is_money_query))
    {
        // Add city_name filter
        size_t from_pos = pg_sql.find(" FROM ");
        if (from_pos == string::npos)
            from_pos = pg_sql.find(" from ");

        if (from_pos != string::npos)
        {
            // Find the end of the table name
            size_t table_end = pg_sql.find_first_of(" ;", from_pos + 6);
            if (table_end != string::npos)
            {
                pg_sql.insert(table_end, " WHERE city_name = '" + city_name + "'");
            }
            else
            {
                pg_sql += " WHERE city_name = '" + city_name + "'";
            }
        }
    }
    else if (!city_name.empty() && has_where && (is_parameters_query || is_consumer_query || is_company_query || is_time_query || is_money_query))
    {
        // Add AND city_name condition
        size_t where_pos = pg_sql.find("WHERE");
        if (where_pos == string::npos)
            where_pos = pg_sql.find("where");

        if (where_pos != string::npos)
        {
            // Find the end of WHERE clause
            size_t clause_end = pg_sql.find_first_of(";)", where_pos);
            if (clause_end != string::npos)
            {
                pg_sql.insert(clause_end, " AND city_name = '" + city_name + "'");
            }
            else
            {
                pg_sql += " AND city_name = '" + city_name + "'";
            }
        }
    }

    PGresult *result = pgManager.executeQuery(pg_sql);

    if (result && PQresultStatus(result) == PGRES_TUPLES_OK)
    {
        int rows = PQntuples(result);
        int cols = PQnfields(result);

        for (int i = 0; i < rows; i++)
        {
            Record row;
            for (int j = 0; j < cols; j++)
            {
                row.push_back(PQgetvalue(result, i, j));
            }
            records.push_back(row);
        }
        PQclear(result);
    }
    else
    {
        if (result)
        {
            cerr << "Failed to execute select query: " << PQerrorMessage(pgManager.getConnection()) << endl;
            cerr << "SQL: " << pg_sql << endl;
            PQclear(result);
        }
    }

    return records;
}

// SQLite version of select_stmt (deprecated - use select_stmt_pg instead)
Records select_stmt(string stmt, const char *s) // const char*
{
    Records records;
    char *errmsg = new char[250]; //
    sqlite3 *DB;

    try
    {
        int exit = 0;
        exit = sqlite3_open(s, &DB);

        char *messaggeError = new char[150];
        exit = sqlite3_exec(DB, stmt.c_str(), select_callback, &records, &errmsg);
        // int ret = sqlite3_exec(DB, stmt.c_str(), select_callback, &records, &errmsg);
        if (exit != SQLITE_OK)
        {
            std::cerr << "Error in select statement " << stmt << "[" << errmsg << "]" << endl;
            sqlite3_free(errmsg);
        }
        else
        {
            // cout << "Parameter-table created successfully" << endl;
        }
        sqlite3_close(DB);
    }
    catch (const exception &e)
    {

        cerr << e.what();
    }
    return records;
}

static int callback(void *myData, int argc, char **argv, char **azColName)
{

    for (int i = 0; i < argc; i++)
    {

        cout << azColName[i] << "  " << argv[i] << endl;
    }

    cout << argv[0] << endl;
    //*myData = *argv[0];

    return 0;
}

static int updateData(const char *s)
{

    sqlite3 *DB;
    char *messageerror = new char[150];

    int exit = sqlite3_open(s, &DB);
    double dInterstRate = 0;
    dInterstRate = 0.047336;

    string sInterestRate = std::to_string(dInterstRate);
    string endStatement = " WHERE PARAMETER = 'TargetInterestRate'";

    string sql = "UPDATE PARAMETERS SET VALUE = ";
    sql.append(sInterestRate);
    sql.append(endStatement);

    // cout << sql << " " << dInterstRate << endl;

    // string sql("UPDATE PARAMETERS SET VALUE = 2 WHERE PARAMETER = 'InterestRateMethod'");

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageerror);

    if (exit != SQLITE_OK)
    {
        cerr << "Error update" << endl;
        sqlite3_free(messageerror);
    }
    else
    {
        cout << "Records updated successfully" << endl;
    }
    sqlite3_close(DB);
    return 0;
}

static int updateParameter(const char *s, string parameter, double dValue)
{
    // Extract city name from the database path
    string path_str(s);
    size_t last_slash = path_str.find_last_of("/");
    size_t dot_pos = path_str.find_last_of(".");
    string city_name = "";

    if (last_slash != string::npos && dot_pos != string::npos && dot_pos > last_slash)
    {
        city_name = path_str.substr(last_slash + 1, dot_pos - last_slash - 1);
    }

    // Update PostgreSQL first (dual-write pattern)
    if (!city_name.empty())
    {
        insertParameterPG(city_name, parameter, dValue);
    }

    sqlite3 *DB;
    char *messageerror = new char[150];
    int exit = sqlite3_open(s, &DB);
    string sValue = "";
    string sql = "";
    string whereStatement = " WHERE PARAMETER = "; //'TargetInterestRate'";

    sValue = std::to_string(dValue);

    sql = "UPDATE PARAMETERS SET VALUE = ";
    sql.append(sValue);
    sql.append(whereStatement);
    sql.append(parameter);

    cout << sql << " " << dValue << endl;

    // string sql("UPDATE PARAMETERS SET VALUE = 2 WHERE PARAMETER = 'InterestRateMethod'");

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageerror);

    if (exit != SQLITE_OK)
    {
        cerr << "Error update" << endl;
        sqlite3_free(messageerror);
    }
    else
    {
        cout << "Records updated successfully" << endl;
    }
    sqlite3_close(DB);
    return 0;
}

static int insertParameterData(const char *s)
{
    // Extract city name from the database path (e.g., "myDB/Bennyland.db" -> "Bennyland")
    string path_str(s);
    size_t last_slash = path_str.find_last_of("/");
    size_t dot_pos = path_str.find_last_of(".");
    string city_name = "";

    if (last_slash != string::npos && dot_pos != string::npos && dot_pos > last_slash)
    {
        city_name = path_str.substr(last_slash + 1, dot_pos - last_slash - 1);
    }

    sqlite3 *DB;
    char *messageerror = new char[150];

    int exit = sqlite3_open(s, &DB);

    // productionParameter = 0.002

    string sql("INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('InterestRateMethod', 2);"
               "INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('TargetInterestRate', 0.04);"
               "INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('CapitalReserveRatio', 0.4);"
               "INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('LiquidityReserveRatio', 0.5);"
               "INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('AverageSpendwill', 0.8);"
               "INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('AverageBorrowwill', 0.05);"
               "INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('FacIncreaseRate_1', 0.05);" // 0.05
               "INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('CapIncreaseParam_1', 15000);"
               "INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('CapIncreaseRate_1', 0.001);"
               "INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('ItemEfficiencyRate', 0.0005);" // 0.000005
               "INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('ProductionParameter', 0.002);" // 0.002
               "INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('IncomeTax', 0.3);"
               "INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('CapitalGainsTax', 0.3);"
               "INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('BudgetBalance', 0.00);"
               "INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('InflationTarget', 0.01);"
               "INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('PayWageInCash', 0);"
               "INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('BankDividendRatio', 0.1);");

    // Insert to PostgreSQL first (dual-write pattern)
    if (!city_name.empty())
    {
        cout << "Inserting parameters to PostgreSQL for city: " << city_name << endl;
        insertParameterPG(city_name, "InterestRateMethod", 2);
        insertParameterPG(city_name, "TargetInterestRate", 0.04);
        insertParameterPG(city_name, "CapitalReserveRatio", 0.4);
        insertParameterPG(city_name, "LiquidityReserveRatio", 0.5);
        insertParameterPG(city_name, "AverageSpendwill", 0.8);
        insertParameterPG(city_name, "AverageBorrowwill", 0.05);
        insertParameterPG(city_name, "FacIncreaseRate_1", 0.05);
        insertParameterPG(city_name, "CapIncreaseParam_1", 15000);
        insertParameterPG(city_name, "CapIncreaseRate_1", 0.001);
        insertParameterPG(city_name, "ItemEfficiencyRate", 0.0005);
        insertParameterPG(city_name, "ProductionParameter", 0.002);
        insertParameterPG(city_name, "IncomeTax", 0.3);
        insertParameterPG(city_name, "CapitalGainsTax", 0.3);
        insertParameterPG(city_name, "BudgetBalance", 0.00);
        insertParameterPG(city_name, "InflationTarget", 0.01);
        insertParameterPG(city_name, "PayWageInCash", 0);
        insertParameterPG(city_name, "BankDividendRatio", 0.1);
    }

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageerror);
    // cout << "I SQL Fcn insterparam data, sql: " << sql << endl;
    if (exit != SQLITE_OK)
    {
        cerr << "Error insert" << endl;
        sqlite3_free(messageerror);
    }
    else
    {
        cout << "Parameter records created successfully" << endl;
    }
    sqlite3_close(DB);

    /*
     *TESTING NEW mySQL
     */
    string city = "Bennyland";

    string sql2("INSERT INTO PARAMETERS_" + city + "(PARAMETER, VALUE) VALUES('InterestRateMethod', 2);");
    //     "INSERT INTO PARAMETERS_" + city + "(PARAMETER, VALUE) VALUES('TargetInterestRate', 0.04);"
    //    "INSERT INTO PARAMETERS_" + city + " (PARAMETER, VALUE) VALUES('CapitalReserveRatio', 0.4);");
    //    "INSERT INTO PARAMETERS_" + city + " (PARAMETER, VALUE) VALUES('LiquidityReserveRatio', 0.5);"
    //    "INSERT INTO PARAMETERS_" + city + "  (PARAMETER, VALUE) VALUES('AverageSpendwill', 0.8);"
    //    "INSERT INTO PARAMETERS_" + city + "  (PARAMETER, VALUE) VALUES('AverageBorrowwill', 0.05);"
    //    "INSERT INTO PARAMETERS_" + city + "  (PARAMETER, VALUE) VALUES('FacIncreaseRate_1', 0.05);"
    //    "INSERT INTO PARAMETERS_" + city + "  (PARAMETER, VALUE) VALUES('CapIncreaseParam_1', 15000);"
    //    "INSERT INTO PARAMETERS_" + city + "  (PARAMETER, VALUE) VALUES('CapIncreaseRate_1', 0.001);"
    //    "INSERT INTO PARAMETERS_" + city + "  (PARAMETER, VALUE) VALUES('ItemEfficiencyRate', 0.000005);"
    //    "INSERT INTO PARAMETERS_" + city + "  (PARAMETER, VALUE) VALUES('ProductionParameter', 0.002);"
    //    "INSERT INTO PARAMETERS_" + city + "  (PARAMETER, VALUE) VALUES('IncomeTax', 0.3);"
    //    "INSERT INTO PARAMETERS_" + city + "  (PARAMETER, VALUE) VALUES('CapitalGainsTax', 0.3);"
    //    "INSERT INTO PARAMETERS_" + city + "  (PARAMETER, VALUE) VALUES('BudgetBalance', 0.00);"
    //    "INSERT INTO PARAMETERS_" + city + "  (PARAMETER, VALUE) VALUES('InflationTarget', 0.01);"
    //    "INSERT INTO PARAMETERS_" + city + "  (PARAMETER, VALUE) VALUES('PayWageInCash', 0);"
    //    "INSERT INTO PARAMETERS_" + city + "  (PARAMETER, VALUE) VALUES('BankDividendRatio', 0.1);");

    /*
     *TESTING NEW mySQL
     */

    // MYSQL_RES *result;
    // MYSQL_ROW row;
    // MYSQL *connection, mysql;

    // int state;

    // mysql_init(&mysql);

    // connection = mysql_real_connect(&mysql, "localhost", "ecosim_db_user", "MyP@ssw0rd!", "ecosim", 0, 0, 0);

    // // cout << connection;
    // if (connection == NULL)
    // {
    //     std::cout << mysql_error(&mysql) << std::endl;
    //     // return tables;
    // }

    // cout << sql2 << endl;

    // mysql_query(connection, sql2.c_str());

    // state = mysql_query(connection, "SELECT * FROM PARAMETERS_Bennyland");
    // if (state != 0)
    // {
    //     std::cout << mysql_error(connection) << std::endl;
    // }

    // result = mysql_store_result(connection);
    // std::cout << "tables: " << mysql_num_rows(result) << std::endl;

    // while ((row = mysql_fetch_row(result)) != NULL)
    // {
    //     cout << " | " << row[0] << " | " << row[1] << " | " << row[2] << " | " << row[3] << " | " << std::endl;
    // }

    // mysql_free_result(result);
    // mysql_close(connection);

    return 0;
}

// PostgreSQL version of initiateCompanyTable
int initiateCompanyTablePG(string city_name)
{
    PostgreSQLManager pgManager;

    if (!pgManager.connect())
    {
        cerr << "Failed to connect to PostgreSQL for company table initialization: " << pgManager.getLastError() << endl;
        return -1;
    }

    // Insert initial company data for the city
    // Schema matches PostgreSQL column names: wage_ch, invest, prod_parm, prod_fcn, cap_vs_eff_split

    vector<string> companies = {
        "INSERT INTO company_data (city_name, company_name, time_stamp, capital, stock, capacity, debts, pcskill, pcmot, wage_const, wage_ch, invest, pbr, decay, prod_parm, prod_fcn, production, employees, item_efficiency, cap_vs_eff_split) "
        "VALUES('" +
            city_name + "', 'johansson_och_johansson', 0, 121, 112500, 620000, 0, 0.7, 0.75, 0.7, 0.03, 1, 0.4, 0.001, 0.002, 1, 0, 0, 0.2, 0.5)",

        "INSERT INTO company_data (city_name, company_name, time_stamp, capital, stock, capacity, debts, pcskill, pcmot, wage_const, wage_ch, invest, pbr, decay, prod_parm, prod_fcn, production, employees, item_efficiency, cap_vs_eff_split) "
        "VALUES('" +
            city_name + "', 'limpan_AB', 0, 12001, 1185, 900000, 0, 0.6, 0.75, 0.7, 0.03, 1, 0.5, 0.001, 0.002, 1, 0, 0, 0.2, 0.5)",

        "INSERT INTO company_data (city_name, company_name, time_stamp, capital, stock, capacity, debts, pcskill, pcmot, wage_const, wage_ch, invest, pbr, decay, prod_parm, prod_fcn, production, employees, item_efficiency, cap_vs_eff_split) "
        "VALUES('" +
            city_name + "', 'bempa_AB', 0, 12100, 1125, 250000, 0, 0.5, 0.75, 0.7, 0.03, 1, 0.5, 0.001, 0.002, 1, 0, 0, 0.2, 0.5)",

        "INSERT INTO company_data (city_name, company_name, time_stamp, capital, stock, capacity, debts, pcskill, pcmot, wage_const, wage_ch, invest, pbr, decay, prod_parm, prod_fcn, production, employees, item_efficiency, cap_vs_eff_split) "
        "VALUES('" +
            city_name + "', 'bempa_CO', 0, 12100, 1125, 420000, 0, 0.8, 0.75, 0.7, 0.03, 1, 0.5, 0.001, 0.002, 1, 0, 0, 0.2, 0.5)",

        "INSERT INTO company_data (city_name, company_name, time_stamp, capital, stock, capacity, debts, pcskill, pcmot, wage_const, wage_ch, invest, pbr, decay, prod_parm, prod_fcn, production, employees, item_efficiency, cap_vs_eff_split) "
        "VALUES('" +
            city_name + "', 'benny_enterprises', 0, 12001, 1125, 750000, 0, 0.9, 0.75, 0.7, 0.03, 1, 0.8, 0.001, 0.002, 1, 0, 0, 0.2, 0.5)",

        "INSERT INTO company_data (city_name, company_name, time_stamp, capital, stock, capacity, debts, pcskill, pcmot, wage_const, wage_ch, invest, pbr, decay, prod_parm, prod_fcn, production, employees, item_efficiency, cap_vs_eff_split) "
        "VALUES('" +
            city_name + "', 'benny_inc', 0, 12100, 1125, 1000000, 0, 0.7, 0.75, 0.5, 0.03, 1, 0.5, 0.001, 0.002, 1, 0, 0, 0.2, 0.5)"};

    for (const auto &sql : companies)
    {
        if (!pgManager.executeCommand(sql))
        {
            cerr << "Failed to insert company data to PostgreSQL" << endl;
            return -1;
        }
    }

    cout << "Company records initiated successfully in PostgreSQL for " << city_name << endl;
    return 0;
}

static int initiateCompanyTable(const char *s)
{

    sqlite3 *DB;
    char *messageerror = new char[150];

    int exit = sqlite3_open(s, &DB);

    string sql("INSERT INTO COMPANY_TABLE (TIME_STAMP, NAME, CAPITAL, STOCK, CAPACITY, DEBTS, PCSKILL, PCMOT, WAGE_CONST, WAGE_CH, INVEST, PBR, DECAY, PROD_PARM, PROD_FCN, PRODUCTION, EMPLOYEES, ITEM_EFFICIENCY, CAP_VS_EFF_SPLIT) VALUES(0, 'johansson_och_johansson', 121, 112500, 620000, 0, 0.7, 0.75, 0.7, 0.03, 1, 0.4, 0.001, 0.002, 1, 0, 0, 0.2, 0.5);"
               "INSERT INTO COMPANY_TABLE (TIME_STAMP, NAME, CAPITAL, STOCK, CAPACITY, DEBTS, PCSKILL, PCMOT, WAGE_CONST, WAGE_CH, INVEST, PBR, DECAY, PROD_PARM, PROD_FCN, PRODUCTION, EMPLOYEES, ITEM_EFFICIENCY, CAP_VS_EFF_SPLIT) VALUES(0, 'limpan_AB', 12001, 1185, 900000, 0, 0.6, 0.75, 0.7, 0.03, 1, 0.5, 0.001, 0.002, 1, 0, 0, 0.2, 0.5);"
               "INSERT INTO COMPANY_TABLE (TIME_STAMP, NAME, CAPITAL, STOCK, CAPACITY, DEBTS, PCSKILL, PCMOT, WAGE_CONST, WAGE_CH, INVEST, PBR, DECAY, PROD_PARM, PROD_FCN, PRODUCTION, EMPLOYEES, ITEM_EFFICIENCY, CAP_VS_EFF_SPLIT) VALUES(0, 'bempa_AB', 12100, 1125, 250000, 0, 0.5, 0.75, 0.7, 0.03, 1, 0.5, 0.001, 0.002, 1, 0, 0, 0.2, 0.5);"
               "INSERT INTO COMPANY_TABLE (TIME_STAMP, NAME, CAPITAL, STOCK, CAPACITY, DEBTS, PCSKILL, PCMOT, WAGE_CONST, WAGE_CH, INVEST, PBR, DECAY, PROD_PARM, PROD_FCN, PRODUCTION, EMPLOYEES, ITEM_EFFICIENCY, CAP_VS_EFF_SPLIT) VALUES(0, 'bempa_CO', 12100, 1125, 420000, 0, 0.8, 0.75, 0.7, 0.03, 1, 0.5, 0.001, 0.002, 1, 0, 0, 0.2, 0.5);"
               "INSERT INTO COMPANY_TABLE (TIME_STAMP, NAME, CAPITAL, STOCK, CAPACITY, DEBTS, PCSKILL, PCMOT, WAGE_CONST, WAGE_CH, INVEST, PBR, DECAY, PROD_PARM, PROD_FCN, PRODUCTION, EMPLOYEES, ITEM_EFFICIENCY, CAP_VS_EFF_SPLIT) VALUES(0, 'benny_enterprises', 12001, 1125, 750000, 0, 0.9, 0.75, 0.7, 0.03, 1, 0.8, 0.001, 0.002, 1, 0, 0, 0.2, 0.5);"
               "INSERT INTO COMPANY_TABLE (TIME_STAMP, NAME, CAPITAL, STOCK, CAPACITY, DEBTS, PCSKILL, PCMOT, WAGE_CONST, WAGE_CH, INVEST, PBR, DECAY, PROD_PARM, PROD_FCN, PRODUCTION, EMPLOYEES, ITEM_EFFICIENCY, CAP_VS_EFF_SPLIT) VALUES(0, 'benny_inc', 12100, 1125, 1000000, 0, 0.7, 0.75, 0.5, 0.03, 1, 0.5, 0.001, 0.002, 1, 0, 0, 0.2, 0.5);");

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageerror);

    if (exit != SQLITE_OK)
    {
        cerr << "Error initiate company records" << endl;
        sqlite3_free(messageerror);
    }
    else
    {
        cout << "Company records initiated successfully" << endl;
    }
    sqlite3_close(DB);
    return 0;
}

int insertMoneyData(std::vector<int> money, string city_name)
{ // std::vector<int> money

    // Use PostgreSQL for money_data (centralized)
    int pgResult = insertMoneyDataPG(money, city_name);

    if (pgResult != 0)
    {
        cerr << "Warning: Failed to insert money data to PostgreSQL" << endl;
    }

    // Keep SQLite write for backward compatibility during migration
    string full_path = get_city_sql_string(city_name);
    const char *dir = full_path.c_str(); //"/var/app/current/myDB/ekosimDB.db";

    sqlite3 *DB;
    char *messageerror = new char[150];

    int exit = sqlite3_open(dir, &DB);

    string sql = "INSERT INTO MONEY_DATA (TIME, BANK_CAPITAL, BANK_LOANS, BANK_DEPOSITS, BANK_LIQUIDITY, CONSUMER_CAPITAL, CONSUMER_DEPOSITS, CONSUMER_DEBTS, COMPANY_DEBTS, COMPANY_CAPITAL, MARKET_CAPITAL, CITY_CAPITAL, TOTAL_CAPITAL) VALUES(";

    sql.append(std::to_string(money[0]) + ", ");
    sql.append(std::to_string(money[1]) + ", ");
    sql.append(std::to_string(money[2]) + ", ");
    sql.append(std::to_string(money[3]) + ", ");
    sql.append(std::to_string(money[4]) + ", ");
    sql.append(std::to_string(money[5]) + ", ");
    sql.append(std::to_string(money[6]) + ", ");
    sql.append(std::to_string(money[7]) + ", ");
    sql.append(std::to_string(money[8]) + ", ");
    sql.append(std::to_string(money[9]) + ", ");
    sql.append(std::to_string(money[10]) + ", ");
    sql.append(std::to_string(money[11]) + ", ");
    sql.append(std::to_string(money[12]) + ");");

    // cout << "I SQL insert money data: " << sql << endl;

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageerror);

    if (exit != SQLITE_OK)
    {
        cerr << "Error insert money data" << endl;
        sqlite3_free(messageerror);
    }
    else
    {
        cout << "Money data updated successfully" << endl;
    }
    sqlite3_close(DB);
    return 0;
}

int insertTimeData(std::vector<double> myData, string city_name)
{ // std::vector<int> money

    // Use PostgreSQL for time_data (centralized)
    int pgResult = insertTimeDataPG(myData, city_name);

    if (pgResult != 0)
    {
        cerr << "Warning: Failed to insert time data to PostgreSQL" << endl;
    }

    // Keep SQLite write for backward compatibility during migration
    string full_path = get_city_sql_string(city_name);
    const char *dir = full_path.c_str();

    sqlite3 *DB;
    char *messageerror = new char[150];

    int exit = sqlite3_open(dir, &DB);

    string sql = "INSERT INTO TIME_DATA (TIME, GDP_ITEMS, DEMAND, PRICE, UNEMPLOYMENT, WAGES, INTEREST_RATE, INVESTMENTS, GDP_NOMINAL, LIQ_RES_RATIO, CAP_RES_RATIO, BANK_DIV_RATIO) VALUES(";

    sql.append(std::to_string((int)round(myData[0])) + ", ");
    sql.append(std::to_string((int)round(myData[1])) + ", ");
    sql.append(std::to_string(myData[2]) + ", ");
    sql.append(std::to_string(myData[3]) + ", ");
    sql.append(std::to_string(myData[4]) + ", ");
    sql.append(std::to_string(myData[5]) + ", ");
    sql.append(std::to_string(myData[6]) + ", ");
    sql.append(std::to_string(myData[7]) + ", ");
    sql.append(std::to_string((int)round(myData[8])) + ", ");
    sql.append(std::to_string(myData[9]) + ", ");
    sql.append(std::to_string(myData[10]) + ", ");
    sql.append(std::to_string(myData[11]) + ");");

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageerror);

    if (exit != SQLITE_OK)
    {
        cerr << "Error insert time data (SQLite)" << endl;
        sqlite3_free(messageerror);
    }
    else
    {
        cout << "Time data updated successfully (SQLite)" << endl;
    }
    sqlite3_close(DB);
    return 0;
}

int insertWorldData(string world_name, string city_name, int consumers, string email, int created)
{ // std::vector<int> money

    // Use PostgreSQL for world_table (centralized)
    int pgResult = insertWorldDataPG(world_name, city_name, consumers, email, created);

    if (pgResult != 0)
    {
        cerr << "Warning: Failed to insert world data to PostgreSQL" << endl;
    }

    // Keep SQLite write for backward compatibility during migration
    string full_path = get_city_sql_string(world_name);
    // full_path += "Bennyworld.db";
    const char *dir = full_path.c_str();

    sqlite3 *DB;
    char *messageerror = new char[150];

    int exit = sqlite3_open(dir, &DB);

    string sql = "INSERT INTO WORLD_TABLE (CITY_NAME, NO_CONSUMERS, EMAIL,  CREATED) VALUES(";

    sql.append("'" + city_name + "', ");
    sql.append("'" + std::to_string(consumers) + "', ");
    sql.append("'" + email + "', ");
    sql.append("'" + std::to_string(created) + "');");

    cout << "I insert world data (SQLite), dir: " << dir << " and sql-string: " << sql << endl;

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageerror);

    if (exit != SQLITE_OK)
    {
        cerr << "Error in insert to world table (SQLite)" << endl;
        sqlite3_free(messageerror);
    }
    else
    {
        cout << "World table updated successfully (SQLite)" << endl;
    }
    sqlite3_close(DB);

    /*
     *TESTING NEW mySQL
     */

    // MYSQL_RES *result;
    // MYSQL_ROW row;
    // MYSQL *connection, mysql;

    // int state;

    // mysql_init(&mysql);

    // connection = mysql_real_connect(&mysql, "localhost", "ecosim_db_user", "MyP@ssw0rd!", "ecosim", 0, 0, 0);

    // // cout << connection;
    // if (connection == NULL)
    // {
    //     std::cout << mysql_error(&mysql) << std::endl;
    //     // return tables;
    // }

    // mysql_query(connection, sql.c_str());

    // state = mysql_query(connection, "SELECT * FROM WORLD_TABLE");
    // if (state != 0)
    // {
    //     std::cout << mysql_error(connection) << std::endl;
    // }

    // result = mysql_store_result(connection);
    // std::cout << "tables: " << mysql_num_rows(result) << std::endl;

    // while ((row = mysql_fetch_row(result)) != NULL)
    // {
    //     cout << " | " << row[0] << " | " << row[1] << " | " << row[2] << " | " << row[3] << " | " << std::endl;
    // }

    // mysql_free_result(result);
    // mysql_close(connection);

    return 0;
}

int insertCompanyTimeData(std::vector<double> myData, string city_name, string company_name)
{ // std::vector<int> money

    // Use PostgreSQL for company_data (centralized)
    // COMMENTED OUT: Now handled by batch insert to avoid duplicate writes
    // int pgResult = insertCompanyTimeDataPG(myData, city_name, company_name);

    // if (pgResult != 0)
    // {
    //     cerr << "Warning: Failed to insert company data to PostgreSQL" << endl;
    // }

    // Keep SQLite write for backward compatibility during migration
    string full_path = get_city_sql_string(city_name);
    const char *dir = full_path.c_str();

    sqlite3 *DB;
    char *messageerror = new char[150];

    int exit = sqlite3_open(dir, &DB);

    string sql = "INSERT INTO COMPANY_TABLE (TIME_STAMP, NAME, CAPITAL, STOCK, CAPACITY, DEBTS, PCSKILL, PCMOT, WAGE_CONST, WAGE_CH, INVEST, PBR, DECAY, PROD_PARM, PROD_FCN, PRODUCTION, EMPLOYEES, ITEM_EFFICIENCY, CAP_VS_EFF_SPLIT) VALUES(";

    sql.append(std::to_string((int)round(myData[0])) + ", ");  // time
    sql.append("'" + company_name + "', ");                    // name
    sql.append(std::to_string((int)round(myData[1])) + ", ");  // capital
    sql.append(std::to_string((int)round(myData[2])) + ", ");  // stock
    sql.append(std::to_string((int)round(myData[3])) + ", ");  // capacity
    sql.append(std::to_string((int)round(myData[4])) + ", ");  // debts
    sql.append(std::to_string(myData[5]) + ", ");              // PC_SKILL
    sql.append(std::to_string(myData[6]) + ", ");              // pc_mot
    sql.append(std::to_string(myData[7]) + ", ");              // wage_const
    sql.append(std::to_string(myData[8]) + ", ");              // wage_ch
    sql.append(std::to_string((int)round(myData[9])) + ", ");  // invest
    sql.append(std::to_string(myData[10]) + ", ");             // pbr
    sql.append(std::to_string(myData[11]) + ", ");             // decay
    sql.append(std::to_string(myData[12]) + ", ");             // prod_param
    sql.append(std::to_string((int)round(myData[13])) + ", "); // prod_fcn
    sql.append(std::to_string((int)round(myData[14])) + ", "); // Production
    sql.append(std::to_string((int)round(myData[15])) + ", "); // employees
    sql.append(std::to_string(myData[16]) + ", ");             // item efficiency
    sql.append(std::to_string(myData[17]) + ");");             // cap eff splie

    // sql.append(std::to_string(myData[11])  + ");");

    // cout << sql << endl;

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageerror);

    if (exit != SQLITE_OK)
    {
        cerr << "Error insert company time data: " << messageerror << endl;
        sqlite3_free(messageerror);
    }
    else
    {
        cout << "Company time data updated successfully" << endl;
    }
    sqlite3_close(DB);
    return 0;
}

int insertCompanyDatapoint(string parameter, int value, int timestamp, string city_name, string company_name)
{ // std::vector<int> money

    string full_path = get_city_sql_string(city_name);
    const char *dir = full_path.c_str();

    sqlite3 *DB;
    char *messageerror = new char[150];

    int exit = sqlite3_open(dir, &DB);

    string sql = "UPDATE COMPANY_TABLE SET " + parameter + " = " + std::to_string(value) + " WHERE TIME = ";
    sql = sql + std::to_string(timestamp) + " AND NAME = '" + company_name + "'";

    cout << sql << endl;

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageerror);

    if (exit != SQLITE_OK)
    {
        cerr << "Error insert company time data" << endl;
        sqlite3_free(messageerror);
    }
    else
    {
        cout << "Company time data updated successfully" << endl;
    }
    sqlite3_close(DB);
    return 0;
}

int insertHighScore(std::vector<double> myData, string city_name, string world_name, string timenow)
{ // std::vector<int> money

    string full_path = get_city_sql_string(world_name);
    const char *dir = full_path.c_str();

    sqlite3 *DB;
    char *messageerror = new char[150];

    int exit = sqlite3_open(dir, &DB);

    string sql = "INSERT INTO HIGH_SCORE (COUNTRY, GROWTH, PALMA, ENV_IMP, TIMENOW) VALUES(";

    sql.append("'" + city_name + "', ");          // name
    sql.append(std::to_string(myData[0]) + ", "); // GROWTH
    sql.append(std::to_string(myData[1]) + ", "); // PALMA
    sql.append(std::to_string(myData[2]) + ", "); // ENV_IMP
    sql.append("'" + timenow + "');");            // ENV_IMP

    cout << sql << endl;

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageerror);

    if (exit != SQLITE_OK)
    {
        cerr << "Error insert HIGH SCORE" << endl;
        sqlite3_free(messageerror);
    }
    else
    {
        cout << "HIGH SCORE updated successfully" << endl;
    }
    sqlite3_close(DB);
    return 0;
}

// PostgreSQL version of insertHighScore for centralized high scores
int insertHighScorePG(std::vector<double> myData, string city_name, string user_id, string timenow)
{
    PostgreSQLManager pgManager;

    if (!pgManager.connect())
    {
        cerr << "Failed to connect to PostgreSQL: " << pgManager.getLastError() << endl;
        return -1;
    }

    // Since user_id and simulation_id are UUIDs with foreign key constraints,
    // we'll insert with NULL for now (anonymous user)
    string sql = "INSERT INTO high_scores (country, growth_rate, palma_ratio, environmental_impact, achieved_at) "
                 "VALUES ($1, $2, $3, $4, $5)";

    if (!pgManager.prepareStatement("insert_high_score", sql))
    {
        cerr << "Failed to prepare high score statement" << endl;
        return -1;
    }

    vector<string> params = {
        city_name,
        to_string(myData[0]), // growth
        to_string(myData[1]), // palma
        to_string(myData[2]), // environmental impact
        timenow.empty() ? "NOW()" : timenow};

    PGresult *result = pgManager.executePrepared("insert_high_score", params);

    if (!result)
    {
        cerr << "High score insert failed" << endl;
        return -1;
    }

    cout << "High score inserted successfully for " << city_name << endl;
    cout << "Growth: " << myData[0] << ", Palma: " << myData[1] << ", Environmental: " << myData[2] << endl;
    PQclear(result);
    return 0;
}

// Get high scores from PostgreSQL
vector<vector<string>> getHighScoresPG(string country_filter = "", int limit = 10)
{
    vector<vector<string>> results;
    PostgreSQLManager pgManager;

    if (!pgManager.connect())
    {
        cerr << "Failed to connect to PostgreSQL: " << pgManager.getLastError() << endl;
        return results;
    }

    string sql = "SELECT country, growth_rate, palma_ratio, environmental_impact, achieved_at "
                 "FROM high_scores ";

    if (!country_filter.empty())
    {
        sql += "WHERE country = $1 ";
    }

    sql += "ORDER BY growth_rate DESC, environmental_impact ASC LIMIT " + to_string(limit);

    PGresult *result;
    if (!country_filter.empty())
    {
        if (!pgManager.prepareStatement("get_high_scores", sql))
        {
            cerr << "Failed to prepare high scores query" << endl;
            return results;
        }
        vector<string> params = {country_filter};
        result = pgManager.executePrepared("get_high_scores", params);
    }
    else
    {
        result = pgManager.executeQuery(sql);
    }

    if (result)
    {
        int rows = PQntuples(result);
        cout << "Found " << rows << " high score records" << endl;

        for (int i = 0; i < rows; i++)
        {
            vector<string> row;
            for (int j = 0; j < PQnfields(result); j++)
            {
                row.push_back(string(PQgetvalue(result, i, j)));
            }
            results.push_back(row);
        }
        PQclear(result);
    }

    return results;
}

// PostgreSQL version of insertWorldData for centralized world table
int insertWorldDataPG(string world_name, string city_name, int consumers, string email, int created)
{
    PostgreSQLManager pgManager;

    if (!pgManager.connect())
    {
        cerr << "Failed to connect to PostgreSQL: " << pgManager.getLastError() << endl;
        return -1;
    }

    string sql = "INSERT INTO world_table (city_name, no_consumers, email, created) "
                 "VALUES ($1, $2, $3, $4) "
                 "ON CONFLICT (city_name) DO UPDATE SET "
                 "no_consumers = EXCLUDED.no_consumers, "
                 "email = EXCLUDED.email, "
                 "created = EXCLUDED.created";

    if (!pgManager.prepareStatement("insert_world_data", sql))
    {
        cerr << "Failed to prepare world data insert statement" << endl;
        return -1;
    }

    vector<string> params = {
        city_name,
        to_string(consumers),
        email,
        to_string(created)};

    PGresult *result = pgManager.executePrepared("insert_world_data", params);

    if (!result)
    {
        cerr << "Failed to insert world data: " << pgManager.getLastError() << endl;
        return -1;
    }

    cout << "I insert world data (PostgreSQL), city: " << city_name
         << ", consumers: " << consumers << ", email: " << email << endl;

    PQclear(result);
    return 0;
}

// PostgreSQL version of getWorldTable - reads world_table data
Records getWorldTablePG(string world_name)
{
    Records results;
    PostgreSQLManager pgManager;

    if (!pgManager.connect())
    {
        cerr << "Failed to connect to PostgreSQL: " << pgManager.getLastError() << endl;
        return results;
    }

    // Query compatible with the view structure: id, city_name, no_consumers, email, created
    string sql = "SELECT id, city_name, no_consumers, email, created "
                 "FROM world_table "
                 "ORDER BY id";

    PGresult *result = pgManager.executeQuery(sql);

    if (result)
    {
        int rows = PQntuples(result);
        cout << "Found " << rows << " world table records (PostgreSQL)" << endl;

        for (int i = 0; i < rows; i++)
        {
            vector<string> row;
            // Add all 5 columns to match SQLite format
            for (int j = 0; j < 5; j++)
            {
                row.push_back(string(PQgetvalue(result, i, j)));
            }
            results.push_back(row);
        }
        PQclear(result);
    }

    return results;
}

// Insert time series data to PostgreSQL
int insertTimeDataPG(std::vector<double> myData, string city_name)
{
    PostgreSQLManager pgManager;

    if (!pgManager.connect())
    {
        cerr << "Failed to connect to PostgreSQL for time_data insert: " << pgManager.getLastError() << endl;
        return 1;
    }

    string sql = "INSERT INTO time_data (city_name, time, gdp_items, demand, price, unemployment, "
                 "wages, interest_rate, investments, gdp_nominal, liquidity_reserve_ratio, "
                 "capital_reserve_ratio, bank_dividend_ratio) "
                 "VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13) "
                 "ON CONFLICT (city_name, time) DO UPDATE SET "
                 "gdp_items = EXCLUDED.gdp_items, "
                 "demand = EXCLUDED.demand, "
                 "price = EXCLUDED.price, "
                 "unemployment = EXCLUDED.unemployment, "
                 "wages = EXCLUDED.wages, "
                 "interest_rate = EXCLUDED.interest_rate, "
                 "investments = EXCLUDED.investments, "
                 "gdp_nominal = EXCLUDED.gdp_nominal, "
                 "liquidity_reserve_ratio = EXCLUDED.liquidity_reserve_ratio, "
                 "capital_reserve_ratio = EXCLUDED.capital_reserve_ratio, "
                 "bank_dividend_ratio = EXCLUDED.bank_dividend_ratio";

    const char *paramValues[13];
    string values[13];

    values[0] = city_name;                             // city_name
    values[1] = std::to_string((int)round(myData[0])); // time
    values[2] = std::to_string((int)round(myData[1])); // gdp_items
    values[3] = std::to_string(myData[2]);             // demand
    values[4] = std::to_string(myData[3]);             // price
    values[5] = std::to_string(myData[4]);             // unemployment
    values[6] = std::to_string(myData[5]);             // wages
    values[7] = std::to_string(myData[6]);             // interest_rate
    values[8] = std::to_string(myData[7]);             // investments
    values[9] = std::to_string((int)round(myData[8])); // gdp_nominal
    values[10] = std::to_string(myData[9]);            // liquidity_reserve_ratio
    values[11] = std::to_string(myData[10]);           // capital_reserve_ratio
    values[12] = std::to_string(myData[11]);           // bank_dividend_ratio

    for (int i = 0; i < 13; i++)
    {
        paramValues[i] = values[i].c_str();
    }

    PGresult *result = PQexecParams(pgManager.getConnection(),
                                    sql.c_str(),
                                    13,
                                    NULL,
                                    paramValues,
                                    NULL,
                                    NULL,
                                    0);

    if (PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        cerr << "I insert time data (PostgreSQL) ERROR: " << PQerrorMessage(pgManager.getConnection()) << endl;
        PQclear(result);
        return 1;
    }

    cout << "I insert time data (PostgreSQL) for city: " << city_name << " at time: " << values[1] << endl;
    PQclear(result);
    return 0;
}

// Get time series data from PostgreSQL
Records getTimeDataPG(string city_name, int limit)
{
    Records results;
    PostgreSQLManager pgManager;

    if (!pgManager.connect())
    {
        cerr << "Failed to connect to PostgreSQL for time_data read: " << pgManager.getLastError() << endl;
        return results;
    }

    string sql = "SELECT time, gdp_items, demand, price, unemployment, wages, interest_rate, "
                 "investments, gdp_nominal, liquidity_reserve_ratio, capital_reserve_ratio, "
                 "bank_dividend_ratio FROM time_data WHERE city_name = $1 "
                 "ORDER BY time DESC";

    if (limit > 0)
    {
        sql += " LIMIT " + std::to_string(limit);
    }

    const char *paramValues[1] = {city_name.c_str()};

    PGresult *result = PQexecParams(pgManager.getConnection(),
                                    sql.c_str(),
                                    1,
                                    NULL,
                                    paramValues,
                                    NULL,
                                    NULL,
                                    0);

    if (PQresultStatus(result) == PGRES_TUPLES_OK)
    {
        int rows = PQntuples(result);
        int cols = PQnfields(result);

        for (int i = 0; i < rows; i++)
        {
            Record row;
            for (int j = 0; j < cols; j++)
            {
                row.push_back(PQgetvalue(result, i, j));
            }
            results.push_back(row);
        }
        PQclear(result);
    }
    else
    {
        cerr << "Failed to fetch time_data: " << PQerrorMessage(pgManager.getConnection()) << endl;
        PQclear(result);
    }

    return results;
}

// Delete time series data from PostgreSQL for a specific city
int deleteTimeDataPG(string city_name)
{
    PostgreSQLManager pgManager;

    if (!pgManager.connect())
    {
        cerr << "Failed to connect to PostgreSQL for time_data delete: " << pgManager.getLastError() << endl;
        return 1;
    }

    string sql = "DELETE FROM time_data WHERE city_name = $1";

    const char *paramValues[1] = {city_name.c_str()};

    PGresult *result = PQexecParams(pgManager.getConnection(),
                                    sql.c_str(),
                                    1,
                                    NULL,
                                    paramValues,
                                    NULL,
                                    NULL,
                                    0);

    if (PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        cerr << "Failed to delete time_data for " << city_name << ": " << PQerrorMessage(pgManager.getConnection()) << endl;
        PQclear(result);
        return 1;
    }

    cout << "TIME_DATA deleted successfully from PostgreSQL for city: " << city_name << endl;
    PQclear(result);
    return 0;
}

// Insert money data to PostgreSQL
int insertMoneyDataPG(std::vector<int> money, string city_name)
{
    PostgreSQLManager pgManager;

    if (!pgManager.connect())
    {
        cerr << "Failed to connect to PostgreSQL for money_data insert: " << pgManager.getLastError() << endl;
        return 1;
    }

    string sql = "INSERT INTO money_data (city_name, time, bank_capital, bank_loans, bank_deposits, "
                 "bank_liquidity, consumer_capital, consumer_deposits, consumer_debts, company_debts, "
                 "company_capital, market_capital, city_capital, total_capital) "
                 "VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14) "
                 "ON CONFLICT (city_name, time) DO UPDATE SET "
                 "bank_capital = EXCLUDED.bank_capital, "
                 "bank_loans = EXCLUDED.bank_loans, "
                 "bank_deposits = EXCLUDED.bank_deposits, "
                 "bank_liquidity = EXCLUDED.bank_liquidity, "
                 "consumer_capital = EXCLUDED.consumer_capital, "
                 "consumer_deposits = EXCLUDED.consumer_deposits, "
                 "consumer_debts = EXCLUDED.consumer_debts, "
                 "company_debts = EXCLUDED.company_debts, "
                 "company_capital = EXCLUDED.company_capital, "
                 "market_capital = EXCLUDED.market_capital, "
                 "city_capital = EXCLUDED.city_capital, "
                 "total_capital = EXCLUDED.total_capital";

    const char *paramValues[14];
    string values[14];

    values[0] = city_name;                  // city_name
    values[1] = std::to_string(money[0]);   // time
    values[2] = std::to_string(money[1]);   // bank_capital
    values[3] = std::to_string(money[2]);   // bank_loans
    values[4] = std::to_string(money[3]);   // bank_deposits
    values[5] = std::to_string(money[4]);   // bank_liquidity
    values[6] = std::to_string(money[5]);   // consumer_capital
    values[7] = std::to_string(money[6]);   // consumer_deposits
    values[8] = std::to_string(money[7]);   // consumer_debts
    values[9] = std::to_string(money[8]);   // company_debts
    values[10] = std::to_string(money[9]);  // company_capital
    values[11] = std::to_string(money[10]); // market_capital
    values[12] = std::to_string(money[11]); // city_capital
    values[13] = std::to_string(money[12]); // total_capital

    for (int i = 0; i < 14; i++)
    {
        paramValues[i] = values[i].c_str();
    }

    PGresult *result = PQexecParams(pgManager.getConnection(),
                                    sql.c_str(),
                                    14,
                                    NULL,
                                    paramValues,
                                    NULL,
                                    NULL,
                                    0);

    if (PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        cerr << "I insert money data (PostgreSQL) ERROR: " << PQerrorMessage(pgManager.getConnection()) << endl;
        PQclear(result);
        return 1;
    }

    cout << "I insert money data (PostgreSQL) for city: " << city_name << " at time: " << values[1] << endl;
    PQclear(result);
    return 0;
}

// Get money data from PostgreSQL
Records getMoneyDataPG(string city_name, int limit)
{
    Records results;
    PostgreSQLManager pgManager;

    if (!pgManager.connect())
    {
        cerr << "Failed to connect to PostgreSQL for money_data read: " << pgManager.getLastError() << endl;
        return results;
    }

    string sql = "SELECT time, bank_capital, bank_loans, bank_deposits, bank_liquidity, "
                 "consumer_capital, consumer_deposits, consumer_debts, company_debts, "
                 "company_capital, market_capital, city_capital, total_capital "
                 "FROM money_data WHERE city_name = $1 "
                 "ORDER BY time DESC";

    if (limit > 0)
    {
        sql += " LIMIT " + std::to_string(limit);
    }

    const char *paramValues[1] = {city_name.c_str()};

    PGresult *result = PQexecParams(pgManager.getConnection(),
                                    sql.c_str(),
                                    1,
                                    NULL,
                                    paramValues,
                                    NULL,
                                    NULL,
                                    0);

    if (PQresultStatus(result) == PGRES_TUPLES_OK)
    {
        int rows = PQntuples(result);
        int cols = PQnfields(result);

        for (int i = 0; i < rows; i++)
        {
            Record row;
            for (int j = 0; j < cols; j++)
            {
                row.push_back(PQgetvalue(result, i, j));
            }
            results.push_back(row);
        }
        PQclear(result);
    }
    else
    {
        cerr << "Failed to fetch money_data: " << PQerrorMessage(pgManager.getConnection()) << endl;
        PQclear(result);
    }

    return results;
}

// Delete money data from PostgreSQL for a specific city
int deleteMoneyDataPG(string city_name)
{
    PostgreSQLManager pgManager;

    if (!pgManager.connect())
    {
        cerr << "Failed to connect to PostgreSQL for money_data delete: " << pgManager.getLastError() << endl;
        return 1;
    }

    string sql = "DELETE FROM money_data WHERE city_name = $1";

    const char *paramValues[1] = {city_name.c_str()};

    PGresult *result = PQexecParams(pgManager.getConnection(),
                                    sql.c_str(),
                                    1,
                                    NULL,
                                    paramValues,
                                    NULL,
                                    NULL,
                                    0);

    if (PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        cerr << "Failed to delete money_data for " << city_name << ": " << PQerrorMessage(pgManager.getConnection()) << endl;
        PQclear(result);
        return 1;
    }

    cout << "MONEY_DATA deleted successfully from PostgreSQL for city: " << city_name << endl;
    PQclear(result);
    return 0;
}

// Insert company time data to PostgreSQL
int insertCompanyTimeDataPG(std::vector<double> myData, string city_name, string company_name)
{
    PostgreSQLManager pgManager;

    if (!pgManager.connect())
    {
        cerr << "Failed to connect to PostgreSQL for company_data insert: " << pgManager.getLastError() << endl;
        return 1;
    }

    string sql = "INSERT INTO company_data (city_name, company_name, time_stamp, capital, stock, capacity, "
                 "debts, pcskill, pcmot, wage_const, wage_ch, invest, pbr, decay, prod_parm, prod_fcn, "
                 "production, employees, item_efficiency, cap_vs_eff_split) "
                 "VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14, $15, $16, $17, $18, $19, $20) "
                 "ON CONFLICT (city_name, company_name, time_stamp) DO UPDATE SET "
                 "capital = EXCLUDED.capital, "
                 "stock = EXCLUDED.stock, "
                 "capacity = EXCLUDED.capacity, "
                 "debts = EXCLUDED.debts, "
                 "pcskill = EXCLUDED.pcskill, "
                 "pcmot = EXCLUDED.pcmot, "
                 "wage_const = EXCLUDED.wage_const, "
                 "wage_ch = EXCLUDED.wage_ch, "
                 "invest = EXCLUDED.invest, "
                 "pbr = EXCLUDED.pbr, "
                 "decay = EXCLUDED.decay, "
                 "prod_parm = EXCLUDED.prod_parm, "
                 "prod_fcn = EXCLUDED.prod_fcn, "
                 "production = EXCLUDED.production, "
                 "employees = EXCLUDED.employees, "
                 "item_efficiency = EXCLUDED.item_efficiency, "
                 "cap_vs_eff_split = EXCLUDED.cap_vs_eff_split";

    const char *paramValues[20];
    string values[20];

    values[0] = city_name;                               // city_name
    values[1] = company_name;                            // company_name
    values[2] = std::to_string((int)round(myData[0]));   // time_stamp
    values[3] = std::to_string((int)round(myData[1]));   // capital
    values[4] = std::to_string((int)round(myData[2]));   // stock
    values[5] = std::to_string((int)round(myData[3]));   // capacity
    values[6] = std::to_string((int)round(myData[4]));   // debts
    values[7] = std::to_string(myData[5]);               // pcskill
    values[8] = std::to_string(myData[6]);               // pcmot
    values[9] = std::to_string(myData[7]);               // wage_const
    values[10] = std::to_string(myData[8]);              // wage_ch
    values[11] = std::to_string((int)round(myData[9]));  // invest
    values[12] = std::to_string(myData[10]);             // pbr
    values[13] = std::to_string(myData[11]);             // decay
    values[14] = std::to_string(myData[12]);             // prod_parm
    values[15] = std::to_string((int)round(myData[13])); // prod_fcn
    values[16] = std::to_string((int)round(myData[14])); // production
    values[17] = std::to_string((int)round(myData[15])); // employees
    values[18] = std::to_string(myData[16]);             // item_efficiency
    values[19] = std::to_string(myData[17]);             // cap_vs_eff_split

    for (int i = 0; i < 20; i++)
    {
        paramValues[i] = values[i].c_str();
    }

    PGresult *result = PQexecParams(pgManager.getConnection(),
                                    sql.c_str(),
                                    20,
                                    NULL,
                                    paramValues,
                                    NULL,
                                    NULL,
                                    0);

    if (PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        cerr << "I insert company data (PostgreSQL) ERROR: " << PQerrorMessage(pgManager.getConnection()) << endl;
        PQclear(result);
        return 1;
    }

    cout << "I insert company data (PostgreSQL) for " << company_name << " in " << city_name << " at time: " << values[2] << endl;
    PQclear(result);
    return 0;
}

// Batch insert multiple companies' data in a single transaction
int batchInsertCompanyTimeDataPG(const vector<tuple<string, vector<double>>> &companies_data, string city_name)
{
    if (companies_data.empty())
    {
        return 0;
    }

    cout << "[BATCH INSERT] Starting batch insert of " << companies_data.size() << " companies for " << city_name << "..." << endl;

    PostgreSQLManager pgManager;

    if (!pgManager.connect())
    {
        cerr << "Failed to connect to PostgreSQL for batch company_data insert: " << pgManager.getLastError() << endl;
        return 1;
    }

    // Start transaction for batch insert
    PGresult *result = PQexec(pgManager.getConnection(), "BEGIN");
    if (PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        cerr << "BEGIN transaction failed: " << PQerrorMessage(pgManager.getConnection()) << endl;
        PQclear(result);
        return 1;
    }
    PQclear(result);

    // Build multi-row INSERT statement
    string sql = "INSERT INTO company_data (city_name, company_name, time_stamp, capital, stock, capacity, "
                 "debts, pcskill, pcmot, wage_const, wage_ch, invest, pbr, decay, prod_parm, prod_fcn, "
                 "production, employees, item_efficiency, cap_vs_eff_split) VALUES ";

    vector<string> value_rows;
    for (const auto &company : companies_data)
    {
        const string &company_name = std::get<0>(company);
        const vector<double> &myData = std::get<1>(company);

        string row = "('" + city_name + "', '" + company_name + "', " +
                     std::to_string((int)round(myData[0])) + ", " +  // time_stamp
                     std::to_string((int)round(myData[1])) + ", " +  // capital
                     std::to_string((int)round(myData[2])) + ", " +  // stock
                     std::to_string((int)round(myData[3])) + ", " +  // capacity
                     std::to_string((int)round(myData[4])) + ", " +  // debts
                     std::to_string(myData[5]) + ", " +              // pcskill
                     std::to_string(myData[6]) + ", " +              // pcmot
                     std::to_string(myData[7]) + ", " +              // wage_const
                     std::to_string(myData[8]) + ", " +              // wage_ch
                     std::to_string((int)round(myData[9])) + ", " +  // invest
                     std::to_string(myData[10]) + ", " +             // pbr
                     std::to_string(myData[11]) + ", " +             // decay
                     std::to_string(myData[12]) + ", " +             // prod_parm
                     std::to_string((int)round(myData[13])) + ", " + // prod_fcn
                     std::to_string((int)round(myData[14])) + ", " + // production
                     std::to_string((int)round(myData[15])) + ", " + // employees
                     std::to_string(myData[16]) + ", " +             // item_efficiency
                     std::to_string(myData[17]) + ")";               // cap_vs_eff_split

        value_rows.push_back(row);
    }

    // Join all rows with commas
    sql += value_rows[0];
    for (size_t i = 1; i < value_rows.size(); i++)
    {
        sql += ", " + value_rows[i];
    }

    sql += " ON CONFLICT (city_name, company_name, time_stamp) DO UPDATE SET "
           "capital = EXCLUDED.capital, "
           "stock = EXCLUDED.stock, "
           "capacity = EXCLUDED.capacity, "
           "debts = EXCLUDED.debts, "
           "pcskill = EXCLUDED.pcskill, "
           "pcmot = EXCLUDED.pcmot, "
           "wage_const = EXCLUDED.wage_const, "
           "wage_ch = EXCLUDED.wage_ch, "
           "invest = EXCLUDED.invest, "
           "pbr = EXCLUDED.pbr, "
           "decay = EXCLUDED.decay, "
           "prod_parm = EXCLUDED.prod_parm, "
           "prod_fcn = EXCLUDED.prod_fcn, "
           "production = EXCLUDED.production, "
           "employees = EXCLUDED.employees, "
           "item_efficiency = EXCLUDED.item_efficiency, "
           "cap_vs_eff_split = EXCLUDED.cap_vs_eff_split";

    result = PQexec(pgManager.getConnection(), sql.c_str());

    if (PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        cerr << "Batch insert company data (PostgreSQL) ERROR: " << PQerrorMessage(pgManager.getConnection()) << endl;
        PQclear(result);
        // Rollback transaction
        PQexec(pgManager.getConnection(), "ROLLBACK");
        return 1;
    }

    PQclear(result);

    // Commit transaction
    result = PQexec(pgManager.getConnection(), "COMMIT");
    if (PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        cerr << "COMMIT transaction failed: " << PQerrorMessage(pgManager.getConnection()) << endl;
        PQclear(result);
        return 1;
    }

    PQclear(result);
    cout << "[BATCH INSERT] Successfully inserted " << companies_data.size() << " companies to PostgreSQL for " << city_name << endl;
    return 0;
}

// Get company data from PostgreSQL
Records getCompanyDataPG(string city_name, string company_name, int limit)
{
    Records results;
    PostgreSQLManager pgManager;

    if (!pgManager.connect())
    {
        cerr << "Failed to connect to PostgreSQL for company_data read: " << pgManager.getLastError() << endl;
        return results;
    }

    string sql = "SELECT time_stamp, capital, stock, capacity, debts, pcskill, pcmot, "
                 "wage_const, wage_ch, invest, pbr, decay, prod_parm, prod_fcn, "
                 "production, employees, item_efficiency, cap_vs_eff_split "
                 "FROM company_data WHERE city_name = $1 AND company_name = $2 "
                 "ORDER BY time_stamp DESC";

    if (limit > 0)
    {
        sql += " LIMIT " + std::to_string(limit);
    }

    const char *paramValues[2] = {city_name.c_str(), company_name.c_str()};

    PGresult *result = PQexecParams(pgManager.getConnection(),
                                    sql.c_str(),
                                    2,
                                    NULL,
                                    paramValues,
                                    NULL,
                                    NULL,
                                    0);

    if (PQresultStatus(result) == PGRES_TUPLES_OK)
    {
        int rows = PQntuples(result);
        int cols = PQnfields(result);

        for (int i = 0; i < rows; i++)
        {
            Record row;
            for (int j = 0; j < cols; j++)
            {
                row.push_back(PQgetvalue(result, i, j));
            }
            results.push_back(row);
        }
        PQclear(result);
    }
    else
    {
        cerr << "Failed to fetch company_data: " << PQerrorMessage(pgManager.getConnection()) << endl;
        PQclear(result);
    }

    return results;
}

// Batch load all companies' latest data for a city in a single query
Records getAllCompaniesLatestDataPG(string city_name)
{
    Records records;
    PostgreSQLManager pgManager;

    cout << "[BATCH LOAD] Fetching all companies data for " << city_name << "..." << endl;

    if (!pgManager.connect())
    {
        cerr << "Failed to connect to PostgreSQL for batch company data fetch: " << pgManager.getLastError() << endl;
        return records;
    }

    // Get all companies' latest data in one query using DISTINCT ON
    string sql = "SELECT DISTINCT ON (company_name) "
                 "id, city_name, company_name, time_stamp, capital, stock, capacity, debts, "
                 "pcskill, pcmot, wage_const, wage_ch, invest, pbr, decay, prod_parm, "
                 "prod_fcn, production, employees, item_efficiency, cap_vs_eff_split, "
                 "created_at, updated_at "
                 "FROM company_data "
                 "WHERE city_name = '" +
                 city_name + "' "
                             "ORDER BY company_name, time_stamp DESC";

    PGresult *result = pgManager.executeQuery(sql);

    if (result && PQresultStatus(result) == PGRES_TUPLES_OK)
    {
        int rows = PQntuples(result);
        int cols = PQnfields(result);

        for (int i = 0; i < rows; i++)
        {
            Record row;
            for (int j = 0; j < cols; j++)
            {
                row.push_back(PQgetvalue(result, i, j));
            }
            records.push_back(row);
        }
        PQclear(result);
        cout << "[BATCH LOAD] Successfully loaded " << rows << " companies for " << city_name << endl;
    }
    else
    {
        if (result)
        {
            cerr << "Failed to fetch batch company data: " << PQerrorMessage(pgManager.getConnection()) << endl;
            PQclear(result);
        }
    }

    return records;
}

// Delete company data from PostgreSQL for a specific city
int deleteCompanyDataPG(string city_name)
{
    PostgreSQLManager pgManager;

    if (!pgManager.connect())
    {
        cerr << "Failed to connect to PostgreSQL for company_data delete: " << pgManager.getLastError() << endl;
        return 1;
    }

    string sql = "DELETE FROM company_data WHERE city_name = $1";

    const char *paramValues[1] = {city_name.c_str()};

    PGresult *result = PQexecParams(pgManager.getConnection(),
                                    sql.c_str(),
                                    1,
                                    NULL,
                                    paramValues,
                                    NULL,
                                    NULL,
                                    0);

    if (PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        cerr << "Failed to delete company_data for " << city_name << ": " << PQerrorMessage(pgManager.getConnection()) << endl;
        PQclear(result);
        return 1;
    }

    cout << "COMPANY_DATA deleted successfully from PostgreSQL for city: " << city_name << endl;
    PQclear(result);
    return 0;
}

// ========== PostgreSQL PARAMETERS Functions ==========

int insertParameterPG(string city_name, string parameter, double value)
{
    PostgreSQLManager pgManager;

    if (!pgManager.connect())
    {
        cerr << "Failed to connect to PostgreSQL for parameter insert: " << pgManager.getLastError() << endl;
        return 1;
    }

    string sql = "INSERT INTO parameters (city_name, parameter, value) "
                 "VALUES ($1, $2, $3) "
                 "ON CONFLICT (city_name, parameter) "
                 "DO UPDATE SET value = EXCLUDED.value, updated_at = CURRENT_TIMESTAMP";

    string value_str = std::to_string(value);
    const char *paramValues[3] = {
        city_name.c_str(),
        parameter.c_str(),
        value_str.c_str()};

    PGresult *result = PQexecParams(pgManager.getConnection(),
                                    sql.c_str(),
                                    3,
                                    NULL,
                                    paramValues,
                                    NULL,
                                    NULL,
                                    0);

    if (PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        cerr << "Failed to insert parameter " << parameter << " for " << city_name << ": " << PQerrorMessage(pgManager.getConnection()) << endl;
        PQclear(result);
        return 1;
    }

    PQclear(result);
    return 0;
}

double getParameterPG(string city_name, string parameter)
{
    PostgreSQLManager pgManager;

    if (!pgManager.connect())
    {
        cerr << "Failed to connect to PostgreSQL for parameter get: " << pgManager.getLastError() << endl;
        return -1;
    }

    string sql = "SELECT value FROM parameters WHERE city_name = $1 AND parameter = $2";

    const char *paramValues[2] = {
        city_name.c_str(),
        parameter.c_str()};

    PGresult *result = PQexecParams(pgManager.getConnection(),
                                    sql.c_str(),
                                    2,
                                    NULL,
                                    paramValues,
                                    NULL,
                                    NULL,
                                    0);

    if (PQresultStatus(result) != PGRES_TUPLES_OK)
    {
        cerr << "Failed to get parameter " << parameter << " for " << city_name << ": " << PQerrorMessage(pgManager.getConnection()) << endl;
        PQclear(result);
        return -1;
    }

    double value = -1;
    if (PQntuples(result) > 0)
    {
        value = atof(PQgetvalue(result, 0, 0));
    }

    PQclear(result);
    return value;
}

int deleteParametersPG(string city_name)
{
    PostgreSQLManager pgManager;

    if (!pgManager.connect())
    {
        cerr << "Failed to connect to PostgreSQL for parameters delete: " << pgManager.getLastError() << endl;
        return 1;
    }

    string sql = "DELETE FROM parameters WHERE city_name = $1";

    const char *paramValues[1] = {city_name.c_str()};

    PGresult *result = PQexecParams(pgManager.getConnection(),
                                    sql.c_str(),
                                    1,
                                    NULL,
                                    paramValues,
                                    NULL,
                                    NULL,
                                    0);

    if (PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        cerr << "Failed to delete parameters for " << city_name << ": " << PQerrorMessage(pgManager.getConnection()) << endl;
        PQclear(result);
        return 1;
    }

    cout << "PARAMETERS deleted successfully from PostgreSQL for city: " << city_name << endl;
    PQclear(result);
    return 0;
}

// ========== PostgreSQL CONSUMER_DATA Functions ==========

// Batch insert function for better performance (single connection, single transaction)
int batchInsertConsumerDataPG(const vector<tuple<string, string, string, int, double, double, double, double, double, double, double, double, double, double, double>> &consumers, string city_name)
{
    if (consumers.empty())
        return 0;

    PostgreSQLManager pgManager;

    if (!pgManager.connect())
    {
        cerr << "Failed to connect to PostgreSQL for batch consumer_data insert: " << pgManager.getLastError() << endl;
        return 1;
    }

    // Begin transaction
    PGresult *beginResult = pgManager.executeQuery("BEGIN");
    if (!beginResult || PQresultStatus(beginResult) != PGRES_COMMAND_OK)
    {
        cerr << "Failed to begin transaction for batch insert" << endl;
        if (beginResult)
            PQclear(beginResult);
        return 1;
    }
    PQclear(beginResult);

    string sql = "INSERT INTO consumer_data (city_name, consumer_name, employer, items, "
                 "capital, deposits, debts, skill, mot, spendwill, savewill, borrowwill, "
                 "income, dividends, transfers) "
                 "VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14, $15) "
                 "ON CONFLICT (city_name, consumer_name) "
                 "DO UPDATE SET employer = EXCLUDED.employer, items = EXCLUDED.items, "
                 "capital = EXCLUDED.capital, deposits = EXCLUDED.deposits, debts = EXCLUDED.debts, "
                 "skill = EXCLUDED.skill, mot = EXCLUDED.mot, spendwill = EXCLUDED.spendwill, "
                 "savewill = EXCLUDED.savewill, borrowwill = EXCLUDED.borrowwill, "
                 "income = EXCLUDED.income, dividends = EXCLUDED.dividends, transfers = EXCLUDED.transfers, "
                 "updated_at = CURRENT_TIMESTAMP";

    int success_count = 0;
    int fail_count = 0;

    for (const auto &consumer : consumers)
    {
        string consumer_name, employer;
        int items;
        double capital, deposits, debts, skill, mot, spendwill, savewill, borrowwill, income, dividends, transfers;

        tie(consumer_name, employer, ignore, items, capital, deposits, debts, skill, mot, spendwill, savewill, borrowwill, income, dividends, transfers) = consumer;

        string items_str = to_string(items);
        string capital_str = to_string(capital);
        string deposits_str = to_string(deposits);
        string debts_str = to_string(debts);
        string skill_str = to_string(skill);
        string mot_str = to_string(mot);
        string spendwill_str = to_string(spendwill);
        string savewill_str = to_string(savewill);
        string borrowwill_str = to_string(borrowwill);
        string income_str = to_string(income);
        string dividends_str = to_string(dividends);
        string transfers_str = to_string(transfers);

        const char *paramValues[15] = {
            city_name.c_str(),
            consumer_name.c_str(),
            employer.c_str(),
            items_str.c_str(),
            capital_str.c_str(),
            deposits_str.c_str(),
            debts_str.c_str(),
            skill_str.c_str(),
            mot_str.c_str(),
            spendwill_str.c_str(),
            savewill_str.c_str(),
            borrowwill_str.c_str(),
            income_str.c_str(),
            dividends_str.c_str(),
            transfers_str.c_str()};

        PGresult *result = PQexecParams(pgManager.getConnection(),
                                        sql.c_str(),
                                        15,
                                        NULL,
                                        paramValues,
                                        NULL,
                                        NULL,
                                        0);

        if (PQresultStatus(result) != PGRES_COMMAND_OK)
        {
            cerr << "Failed to insert consumer " << consumer_name << ": " << PQerrorMessage(pgManager.getConnection()) << endl;
            PQclear(result);
            fail_count++;
        }
        else
        {
            success_count++;
        }

        if (result)
            PQclear(result);
    }

    // Commit transaction
    PGresult *commitResult = pgManager.executeQuery("COMMIT");
    if (!commitResult || PQresultStatus(commitResult) != PGRES_COMMAND_OK)
    {
        cerr << "Failed to commit transaction, rolling back" << endl;
        pgManager.executeQuery("ROLLBACK");
        if (commitResult)
            PQclear(commitResult);
        return 1;
    }
    PQclear(commitResult);

    cout << "Batch inserted " << success_count << " consumers to PostgreSQL (" << fail_count << " failed)" << endl;
    return fail_count > 0 ? 1 : 0;
}

int insertConsumerDataPG(string city_name, string consumer_name, string employer,
                         int items, double capital, double deposits, double debts, double skill,
                         double mot, double spendwill, double savewill, double borrowwill,
                         double income, double dividends, double transfers)
{
    PostgreSQLManager pgManager;

    if (!pgManager.connect())
    {
        cerr << "Failed to connect to PostgreSQL for consumer_data insert: " << pgManager.getLastError() << endl;
        return 1;
    }

    string sql = "INSERT INTO consumer_data (city_name, consumer_name, employer, items, "
                 "capital, deposits, debts, skill, mot, spendwill, savewill, borrowwill, "
                 "income, dividends, transfers) "
                 "VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14, $15) "
                 "ON CONFLICT (city_name, consumer_name) "
                 "DO UPDATE SET employer = EXCLUDED.employer, items = EXCLUDED.items, "
                 "capital = EXCLUDED.capital, deposits = EXCLUDED.deposits, debts = EXCLUDED.debts, "
                 "skill = EXCLUDED.skill, mot = EXCLUDED.mot, spendwill = EXCLUDED.spendwill, "
                 "savewill = EXCLUDED.savewill, borrowwill = EXCLUDED.borrowwill, "
                 "income = EXCLUDED.income, dividends = EXCLUDED.dividends, transfers = EXCLUDED.transfers, "
                 "updated_at = CURRENT_TIMESTAMP";

    string items_str = std::to_string(items);
    string capital_str = std::to_string(capital);
    string deposits_str = std::to_string(deposits);
    string debts_str = std::to_string(debts);
    string skill_str = std::to_string(skill);
    string mot_str = std::to_string(mot);
    string spendwill_str = std::to_string(spendwill);
    string savewill_str = std::to_string(savewill);
    string borrowwill_str = std::to_string(borrowwill);
    string income_str = std::to_string(income);
    string dividends_str = std::to_string(dividends);
    string transfers_str = std::to_string(transfers);

    const char *paramValues[15] = {
        city_name.c_str(),
        consumer_name.c_str(),
        employer.c_str(),
        items_str.c_str(),
        capital_str.c_str(),
        deposits_str.c_str(),
        debts_str.c_str(),
        skill_str.c_str(),
        mot_str.c_str(),
        spendwill_str.c_str(),
        savewill_str.c_str(),
        borrowwill_str.c_str(),
        income_str.c_str(),
        dividends_str.c_str(),
        transfers_str.c_str()};

    PGresult *result = PQexecParams(pgManager.getConnection(),
                                    sql.c_str(),
                                    15,
                                    NULL,
                                    paramValues,
                                    NULL,
                                    NULL,
                                    0);

    if (PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        cerr << "Failed to insert consumer_data for " << consumer_name << " in " << city_name << ": " << PQerrorMessage(pgManager.getConnection()) << endl;
        PQclear(result);
        return 1;
    }

    PQclear(result);
    return 0;
}

Records getConsumerDataPG(string city_name, string consumer_name)
{
    PostgreSQLManager pgManager;
    Records records;

    if (!pgManager.connect())
    {
        cerr << "Failed to connect to PostgreSQL for consumer_data get: " << pgManager.getLastError() << endl;
        return records;
    }

    string sql = "SELECT consumer_name, employer, items, capital, deposits, debts, "
                 "skill, mot, spendwill, savewill, borrowwill, income, dividends, transfers "
                 "FROM consumer_data WHERE city_name = $1";

    if (!consumer_name.empty())
    {
        sql += " AND consumer_name = $2";
    }

    const char *paramValues[2] = {
        city_name.c_str(),
        consumer_name.c_str()};

    int numParams = consumer_name.empty() ? 1 : 2;

    PGresult *result = PQexecParams(pgManager.getConnection(),
                                    sql.c_str(),
                                    numParams,
                                    NULL,
                                    paramValues,
                                    NULL,
                                    NULL,
                                    0);

    if (PQresultStatus(result) != PGRES_TUPLES_OK)
    {
        cerr << "Failed to get consumer_data for " << consumer_name << " in " << city_name << ": " << PQerrorMessage(pgManager.getConnection()) << endl;
        PQclear(result);
        return records;
    }

    int nrows = PQntuples(result);
    for (int i = 0; i < nrows; i++)
    {
        Record record;
        for (int j = 0; j < PQnfields(result); j++)
        {
            record.push_back(PQgetvalue(result, i, j));
        }
        records.push_back(record);
    }

    PQclear(result);
    return records;
}

int deleteConsumerDataPG(string city_name)
{
    PostgreSQLManager pgManager;

    if (!pgManager.connect())
    {
        cerr << "Failed to connect to PostgreSQL for consumer_data delete: " << pgManager.getLastError() << endl;
        return 1;
    }

    string sql = "DELETE FROM consumer_data WHERE city_name = $1";

    const char *paramValues[1] = {city_name.c_str()};

    PGresult *result = PQexecParams(pgManager.getConnection(),
                                    sql.c_str(),
                                    1,
                                    NULL,
                                    paramValues,
                                    NULL,
                                    NULL,
                                    0);

    if (PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        cerr << "Failed to delete consumer_data for " << city_name << ": " << PQerrorMessage(pgManager.getConnection()) << endl;
        PQclear(result);
        return 1;
    }

    cout << "CONSUMER_DATA deleted successfully from PostgreSQL for city: " << city_name << endl;
    PQclear(result);
    return 0;
}

int insertConsumerData(std::vector<double> myData, string country, string name, string employer)
{ // std::vector<int> money

    string full_path = get_city_sql_string(country);
    const char *dir = full_path.c_str();

    // NOTE: PostgreSQL insert is now handled by batch insert in Consumer_list::save_consumers()
    // This function only writes to SQLite for backward compatibility
    // Remove the following line to avoid duplicate PostgreSQL inserts:
    // insertConsumerDataPG(country, name, employer, ...);

    sqlite3 *DB;
    char *messageerror = new char[150];

    int exit = sqlite3_open(dir, &DB);

    string sql = "INSERT INTO CONSUMER_TABLE (NAME, EMPLOYER, ITEMS, CAPITAL, DEPOSITS, DEBTS, SKILL, MOT, SPENDWILL, SAVEWILL, BORROWWILL, INCOME, DIVIDENDS, TRANSFERS) VALUES(";

    sql.append("'" + name + "', ");                           // name
    sql.append("'" + employer + "', ");                       // employer
    sql.append(std::to_string((int)round(myData[0])) + ", "); // items
    sql.append(std::to_string(myData[1]) + ", ");             // capital
    sql.append(std::to_string(myData[2]) + ", ");             // loans
    sql.append(std::to_string(myData[3]) + ", ");             // debts
    sql.append(std::to_string(myData[4]) + ", ");             // skill
    sql.append(std::to_string(myData[5]) + ", ");             // mot
    sql.append(std::to_string(myData[6]) + ", ");             // spendwill
    sql.append(std::to_string(myData[7]) + ", ");             // savewill
    sql.append(std::to_string(myData[8]) + ", ");             // borrowwill
    sql.append(std::to_string(myData[9]) + ", ");             // INCOME
    sql.append(std::to_string(myData[10]) + ", ");            // dividends
    sql.append(std::to_string(myData[11]) + ");");            // transfers

    // cout << sql << endl;

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageerror);

    if (exit != SQLITE_OK)
    {
        cerr << "Error insert CONSUMER_TABLE: " << messageerror << endl;
        cerr << "SQL: " << sql << endl;
        sqlite3_free(messageerror);
    }
    else
    {
        // cout << "CONSUMER_TABLE updated successfully" << endl;
    }
    sqlite3_close(DB);
    return 0;
}

double getDatabaseParameter(string parameter, string city_name)
{

    using Record = vector<string>;
    using Records = vector<Record>;

    // Use PostgreSQL version
    double myParameterValue = 0;

    string stmt = "SELECT * FROM PARAMETERS WHERE PARAMETER = "; // 'AverageSpendwill'";
    stmt.append(parameter);

    Records records = select_stmt_pg(stmt, city_name);
    // cout << "i SQLF getdatabaseparam3" << parameter << endl;
    try
    {
        if (not(records.empty()))
        {
            // PostgreSQL parameters table: 0:id, 1:city_name, 2:parameter, 3:value
            myParameterValue = std::stod(records[0][3]);
        }
        else
        {
            cout << "Empty return from database for parameter " << parameter << " in city " << city_name << endl;
        }
    }
    catch (const exception &e)
    {

        cerr << "Error in getDatabaseParameter: " << e.what() << " for parameter " << parameter << " in city " << city_name << endl;
    }

    // cout << "i SQLF getdatabaseparam4" << endl;
    return myParameterValue;
}

// Test PostgreSQL connection
int testPostgreSQLConnection()
{
    cout << "Testing PostgreSQL connection..." << endl;

    PostgreSQLManager pgManager;

    if (!pgManager.connect())
    {
        cerr << "Failed to connect to PostgreSQL: " << pgManager.getLastError() << endl;
        return -1;
    }

    cout << "Successfully connected to PostgreSQL!" << endl;

    // Test a simple query
    PGresult *result = pgManager.executeQuery("SELECT version()");

    if (result)
    {
        int rows = PQntuples(result);
        if (rows > 0)
        {
            cout << "PostgreSQL version: " << PQgetvalue(result, 0, 0) << endl;
        }
        PQclear(result);
        cout << "Connection test successful!" << endl;
        return 0;
    }
    else
    {
        cerr << "Failed to execute test query" << endl;
        return -1;
    }
}

static int deleteTheData(const char *s)
{
    // Extract city name from the database path (e.g., "myDB/Bennyland.db" -> "Bennyland")
    string path_str(s);
    size_t last_slash = path_str.find_last_of("/");
    size_t dot_pos = path_str.find_last_of(".");
    string city_name = "";

    if (last_slash != string::npos && dot_pos != string::npos && dot_pos > last_slash)
    {
        city_name = path_str.substr(last_slash + 1, dot_pos - last_slash - 1);
        cout << "Extracted city name: " << city_name << " from path: " << path_str << endl;

        // Delete from PostgreSQL first
        deleteTimeDataPG(city_name);
        deleteMoneyDataPG(city_name);
        deleteCompanyDataPG(city_name);
        deleteParametersPG(city_name);
        deleteConsumerDataPG(city_name);
    }

    sqlite3 *DB;
    char *messageerror = new char[150];

    int exit = sqlite3_open(s, &DB);

    string sql = "DELETE FROM PARAMETERS";
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageerror);

    if (exit != SQLITE_OK)
    {
        cerr << "Error delete PARAMETERS" << endl;
        sqlite3_free(messageerror);
    }
    else
    {
        cout << "PARAMETERS records deleted successfully" << endl;
    }

    sql = "DELETE FROM TIME_DATA";
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageerror);

    if (exit != SQLITE_OK)
    {
        cerr << "Error delete TIME_DATA" << endl;
        sqlite3_free(messageerror);
    }
    else
    {
        cout << "TIME_DATA records deleted successfully" << endl;
    }

    sql = "DELETE FROM MONEY_DATA";
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageerror);

    if (exit != SQLITE_OK)
    {
        cerr << "Error delete MONEY_DATA" << endl;
        sqlite3_free(messageerror);
    }
    else
    {
        cout << "MONEY_DATA records deleted successfully" << endl;
    }

    sql = "DELETE FROM COMPANY_TABLE";
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageerror);

    if (exit != SQLITE_OK)
    {
        cerr << "Error delete COMPANY_TABLE" << endl;
        sqlite3_free(messageerror);
    }
    else
    {
        cout << "COMPANY_TABLE records deleted successfully" << endl;
    }

    sql = "DELETE FROM CONSUMER_TABLE";
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageerror);

    if (exit != SQLITE_OK)
    {
        cerr << "Error delete CONSUMER_TABLE" << endl;
        sqlite3_free(messageerror);
    }
    else
    {
        cout << "CONSUMER_TABLE records deleted successfully" << endl;
    }
    sqlite3_close(DB);
    return 0;
}

static int deleteWorldData(const char *s)
{

    sqlite3 *DB;
    char *messageerror = new char[150];

    int exit = sqlite3_open(s, &DB);

    string sql = "DELETE FROM WORLD_TABLE";
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageerror);

    if (exit != SQLITE_OK)
    {
        cerr << "Error delete WORLD_TABLE" << endl;
        sqlite3_free(messageerror);
    }
    else
    {
        cout << "WORLD_TABLE records deleted successfully" << endl;
    }

    sqlite3_close(DB);

    /*
     *TESTING NEW mySQL
     */

    // MYSQL *connection, mysql;

    // mysql_init(&mysql);

    // connection = mysql_real_connect(&mysql, "localhost", "ecosim_db_user", "MyP@ssw0rd!", "ecosim", 0, 0, 0);

    // // cout << connection;
    // if (connection == NULL)
    // {
    //     std::cout << mysql_error(&mysql) << std::endl;
    //     // return tables;
    // }

    // mysql_query(connection, sql.c_str());

    // mysql_close(connection);

    return 0;
}

// Creating a Database if not exist
static int createDB(const char *s)
{

    sqlite3 *DB;
    try
    {
        int exit = 0;
        char *messageerror = new char[150];

        exit = sqlite3_open(s, &DB);
        if (exit != SQLITE_OK)
        {
            cerr << "Error create inital Database" << endl;
            sqlite3_free(messageerror);
        }
        else
        {
            cout << "Initial Database successfully created" << endl;
        }
        sqlite3_close(DB);
    }
    catch (const exception &e)
    {

        cerr << e.what();
    }
    return 0;
}

// Creating the table for parameters
static int createParameterTable(const char *s)
{

    sqlite3 *DB;

    string sql = "CREATE TABLE IF NOT EXISTS PARAMETERS("
                 "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                 "PARAMETER  TEXT    NOT NULL, "
                 "VALUE      DECIMAL     NOT NULL );";
    //        "GRADE      CHAR(1) );";

    try
    {
        int exit = 0;
        exit = sqlite3_open(s, &DB);

        char *messaggeError = new char[150];
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

        if (exit != SQLITE_OK)
        {
            cerr << "Error create table" << endl;
            sqlite3_free(messaggeError);
        }
        else
        {
            cout << "Parameter-table created successfully" << endl;
        }
        sqlite3_close(DB);
    }
    catch (const exception &e)
    {

        cerr << e.what();
    }

    return 0;
}

// Creating the table for parameters
static int createSQLParameterTable(string country)
{

    string sql = "CREATE TABLE IF NOT EXISTS PARAMETERS_Bennyland("
                 "ID INT PRIMARY KEY AUTO_INCREMENT, "
                 "PARAMETER  TEXT    NOT NULL, "
                 "VALUE      DECIMAL     NOT NULL );";
    cout << sql << endl;

    // MYSQL_RES *result;
    // MYSQL_ROW row;
    // MYSQL *connection, mysql;

    // mysql_init(&mysql);

    // connection = mysql_real_connect(&mysql, "localhost", "ecosim_db_user", "MyP@ssw0rd!", "ecosim", 0, 0, 0);

    // if (connection == NULL)
    // {
    //     std::cout << mysql_error(&mysql) << std::endl;
    // }

    // mysql_query(connection, sql.c_str());

    // cout << "Parameter table created" << endl;

    // string sql2 = "SHOW TABLES";
    // mysql_query(connection, sql2.c_str());
    // cout << "SQL2 i cereate parameter" << endl;
    // mysql_close(connection);

    return 0;
}

// Creating the table for high-score
static int createHighScoreTable(const char *s)
{

    sqlite3 *DB;

    string sql = "CREATE TABLE IF NOT EXISTS HIGH_SCORE("
                 "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                 "COUNTRY  TEXT    NOT NULL, "
                 "GROWTH   DECIMAL    NOT NULL, "
                 "PALMA     DECIMAL    NOT NULL, "
                 "ENV_IMP  DECIMAL    NOT NULL, "
                 "TIMENOW  TEXT     NOT NULL );";
    try
    {
        int exit = 0;
        exit = sqlite3_open(s, &DB);

        char *messaggeError = new char[150];
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

        if (exit != SQLITE_OK)
        {
            cerr << "Error create high-score table" << endl;
            sqlite3_free(messaggeError);
        }
        else
        {
            cout << "High-score-table created successfully" << endl;
        }
        sqlite3_close(DB);
    }
    catch (const exception &e)
    {

        cerr << e.what();
    }

    return 0;
}

// Creating the table for the city-data
static int createDataTable(const char *s)
{

    sqlite3 *DB;

    string sql = "CREATE TABLE IF NOT EXISTS TIME_DATA("
                 "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                 "TIME           INTEGER    NOT NULL, "
                 "GDP_ITEMS      INTEGER    NOT NULL, "
                 "DEMAND         INTEGER    NOT NULL, "
                 "PRICE          DECIMAL    NOT NULL, "
                 "UNEMPLOYMENT   DECIMAL    NOT NULL, "
                 "WAGES          DECIMAL    NOT NULL, "
                 "INTEREST_RATE  DECIMAL    NOT NULL, "
                 "INVESTMENTS    DECIMAL    NOT NULL, "
                 "GDP_NOMINAL    INTEGER    NOT NULL, "
                 "LIQ_RES_RATIO  DECIMAL    NOT NULL, "
                 "CAP_RES_RATIO  DECIMAL    NOT NULL, "
                 "BANK_DIV_RATIO DECIMAL    NOT NULL );";

    try
    {
        int exit = 0;
        exit = sqlite3_open(s, &DB);

        char *messaggeError = new char[150];
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

        if (exit != SQLITE_OK)
        {
            cerr << "Error create table" << endl;
            sqlite3_free(messaggeError);
        }
        else
        {
            cout << "Data-table created successfully" << endl;
        }
        sqlite3_close(DB);
    }
    catch (const exception &e)
    {

        cerr << e.what();
    }

    return 0;
}

// Creating the table for the city-data
static int createMoneyTable(const char *s)
{

    sqlite3 *DB;

    string sql = "CREATE TABLE IF NOT EXISTS MONEY_DATA("
                 "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                 "TIME               INTEGER    NOT NULL, "
                 "BANK_CAPITAL       INTEGER    NOT NULL, "
                 "BANK_LOANS         INTEGER    NOT NULL, "
                 "BANK_DEPOSITS      INTEGER    NOT NULL, "
                 "BANK_LIQUIDITY     INTEGER    NOT NULL, "
                 "CONSUMER_CAPITAL   INTEGER    NOT NULL, "
                 "CONSUMER_DEPOSITS  INTEGER    NOT NULL, "
                 "CONSUMER_DEBTS     INTEGER    NOT NULL, "
                 "COMPANY_DEBTS      INTEGER    NOT NULL, "
                 "COMPANY_CAPITAL    INTEGER    NOT NULL, "
                 "MARKET_CAPITAL     INTEGER    NOT NULL, "
                 "CITY_CAPITAL       INTEGER    NOT NULL, "
                 "TOTAL_CAPITAL      INTEGER     NOT NULL );";

    try
    {
        int exit = 0;
        exit = sqlite3_open(s, &DB);

        char *messaggeError = new char[150];
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

        if (exit != SQLITE_OK)
        {
            cerr << "Error create table" << endl;
            sqlite3_free(messaggeError);
        }
        else
        {
            cout << "Money-table created successfully" << endl;
        }
        sqlite3_close(DB);
    }
    catch (const exception &e)
    {

        cerr << e.what();
    }

    return 0;
}

// Creating the table for companies
static int createCompanyTable(const char *s)
{

    sqlite3 *DB;

    string sql = "CREATE TABLE IF NOT EXISTS COMPANY_TABLE("
                 "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                 "TIME_STAMP INTEGER    NOT NULL, "
                 "NAME       TEXT       NOT NULL, "
                 "CAPITAL    DECIMAL    NOT NULL, "
                 "STOCK      INTEGER    NOT NULL, "
                 "CAPACITY   INTEGER    NOT NULL, "
                 "DEBTS      INTEGER    NOT NULL, "
                 "PCSKILL    DECIMAL    NOT NULL, "
                 "PCMOT      DECIMAL    NOT NULL, "
                 "WAGE_CONST DECIMAL    NOT NULL, "
                 "WAGE_CH    DECIMAL    NOT NULL, "
                 "INVEST     DECIMAL    NOT NULL, "
                 "PBR        DECIMAL    NOT NULL, "
                 "DECAY      DECIMAL    NOT NULL, "
                 "PROD_PARM  DECIMAL    NOT NULL, "
                 "PROD_FCN   INTEGER    NOT NULL, "
                 "PRODUCTION INTEGER    NOT NULL, "
                 "EMPLOYEES  INTEGER    NOT NULL, "
                 "ITEM_EFFICIENCY  INTEGER    NOT NULL, "
                 "CAP_VS_EFF_SPLIT  DECIMAL    NOT NULL );";

    try
    {
        int exit = 0;
        exit = sqlite3_open(s, &DB);

        char *messaggeError = new char[150];
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

        if (exit != SQLITE_OK)
        {
            cerr << "Error create table" << endl;
            sqlite3_free(messaggeError);
        }
        else
        {
            cout << "Company-table created successfully" << endl;
        }
        sqlite3_close(DB);
    }
    catch (const exception &e)
    {

        cerr << e.what();
    }

    return 0;
}

static int createConsumerTable(const char *s)
{

    sqlite3 *DB;

    string sql = "CREATE TABLE IF NOT EXISTS CONSUMER_TABLE("
                 "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                 "NAME       TEXT       NOT NULL, "
                 "EMPLOYER   TEXT    NOT NULL, "
                 "ITEMS      INTEGER    NOT NULL, "
                 "CAPITAL    DECIMAL    NOT NULL, "
                 "DEPOSITS   DECIMAL    NOT NULL, "
                 "DEBTS      DECIMAL    NOT NULL, "
                 "SKILL      DECIMAL    NOT NULL, "
                 "MOT        DECIMAL    NOT NULL, "
                 "SPENDWILL  DECIMAL    NOT NULL, "
                 "SAVEWILL   DECIMAL    NOT NULL, "
                 "BORROWWILL DECIMAL    NOT NULL, "
                 "INCOME    DECIMAL    NOT NULL, "
                 "DIVIDENDS DECIMAL    NOT NULL, "
                 "TRANSFERS  DECIMAL    NOT NULL );";
    try
    {
        int exit = 0;
        exit = sqlite3_open(s, &DB);

        char *messaggeError = new char[150];
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

        if (exit != SQLITE_OK)
        {
            cerr << "Error create consumer table" << endl;
            sqlite3_free(messaggeError);
        }
        else
        {
            cout << "Consumer-table created successfully" << endl;
        }
        sqlite3_close(DB);
    }
    catch (const exception &e)
    {

        cerr << e.what();
    }

    return 0;
}

// Creating the world-table for cities/countries
static int createWorldTable(const char *s)
{

    sqlite3 *DB;

    string sql = "CREATE TABLE IF NOT EXISTS WORLD_TABLE("
                 "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                 "CITY_NAME      TEXT    NOT NULL, "
                 "NO_CONSUMERS   INTEGER    NOT NULL, "
                 "EMAIL          TEXT    NOT NULL, "
                 "CREATED        INTEGER    NOT NULL );";

    try
    {
        int exit = 0;
        exit = sqlite3_open(s, &DB);

        char *messaggeError = new char[150];
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

        if (exit != SQLITE_OK)
        {
            cerr << "Error create world table" << endl;
            sqlite3_free(messaggeError);
        }
        else
        {
            cout << "World-table created successfully" << endl;
        }
        sqlite3_close(DB);
    }
    catch (const exception &e)
    {

        cerr << e.what();
    }

    return 0;
}

const char *get_sql_string()
{

    string myOS = "";
    const char *sql_string = "";
    bool run_locally = false;

#ifdef _WIN32
    myOS "Windows 32-bit";
#elif _WIN64
    myOS "Windows 64-bit";
#elif __APPLE__ || __MACH__
    myOS = "Mac OSX";
    run_locally = true;
#elif __linux__
    myOS = "Linux";
    run_locally = false;
#endif

    if (run_locally)
    {
        sql_string = "myDB/ekosimDB.db";
    }
    else
    {
        // sql_string = "/var/app/current/myDB/ekosimDB.db";
        sql_string = "/home/ecosim/myDB/ekosimDB.db";
    }

    // cout << "I SQL Functions get sql string " << sql_string << typeid(sql_string).name() << endl;

    return sql_string;
}

string get_city_sql_string(string city_name)
{

    string myOS = "";

    string full_path = "";

    bool run_locally = false;

#ifdef _WIN32
    myOS "Windows 32-bit";
#elif _WIN64
    myOS "Windows 64-bit";
#elif __APPLE__ || __MACH__
    myOS = "Mac OSX";
    run_locally = true;
#elif __linux__
    myOS = "Linux";
    run_locally = false;
#endif

    if (run_locally)
    {
        full_path = "myDB/";
    }
    else
    {
        full_path = "/var/app/current/myDB/";
        // full_path = "/home/ec2-user/ekosimProject/myDB/";
    }

    full_path += city_name;
    full_path += ".db";

    const char *sql_string = full_path.c_str();

    // cout << "I SQL Functions get city sql string " << sql_string << " and as string: " << full_path << endl;

    return full_path;
}
