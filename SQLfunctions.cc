#include <iostream>
#include <sqlite3.h>
#include <stdio.h>
#include <vector>
#include <cstring>
#include <cmath>
#include <fstream>
#include "SQLfunctions.h"


//Amazon linux
//#include "/usr/include/mysql/mysql.h"

//Mac OSX
//#include "/usr/local/Cellar/mysql/8.0.23_1/include/mysql/mysql.h"


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
    //string dir = get_sql_string();
    //sqlite3* DB;

    cout << "INITIATING CITY DATABASE" << endl;
    cout << "-------------------" << endl;

    //Creating the database
    createDB(dir);

    //Creating tables
    createParameterTable(dir);
    createDataTable(dir);
    createMoneyTable(dir);
    createCompanyTable(dir);
    createConsumerTable(dir);

    // Creating mySQL tables
    createSQLParameterTable("Bennyland");

    cout << endl;

    //Deleting old data
    deleteTheData(dir);

    cout << endl;

    //Setting initial parameters
    insertParameterData(dir);
    initiateCompanyTable(dir);

    cout << "I SQL functions initiate city db" << endl;

    //selectData(dir);

    //sqlite3_close(DB);
    return 0;
};

int initiateWorldDB(string world_name)
{

    string full_path = get_city_sql_string(world_name);
    const char *dir = full_path.c_str();

    cout << "I SQL Functions initiate World db, using database path: " << dir << endl;
    //string dir = get_sql_string();
    //sqlite3* DB;

    cout << "INITIATING WORLD DATABASE" << endl;
    cout << "-------------------" << endl;

    //Creating the database
    createDB(dir);

    //Creating tables
    createWorldTable(dir);
    createHighScoreTable(dir);

    cout << endl;

    //Deleting old data
    deleteWorldData(dir);

    cout << endl;

    //selectData(dir);

    //sqlite3_close(DB);
    return 0;
};

static int selectData(const char *s)
{

    sqlite3 *DB;

    //int exit = sqlite3_open(s, &DB);
    double myData = 0;

    string sql = "SELECT * FROM MONEY_DATA";

    //string name = "'InterestRateMethod'";
    //sql.append(name);
    //cout <<  sql << endl;
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

Records select_stmt(string stmt, const char *s) //const char*
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
        //int ret = sqlite3_exec(DB, stmt.c_str(), select_callback, &records, &errmsg);
        if (exit != SQLITE_OK)
        {
            std::cerr << "Error in select statement " << stmt << "[" << errmsg << "]" << endl;
            sqlite3_free(errmsg);
        }
        else
        {
            //cout << "Parameter-table created successfully" << endl;
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

    //cout << sql << " " << dInterstRate << endl;

    //string sql("UPDATE PARAMETERS SET VALUE = 2 WHERE PARAMETER = 'InterestRateMethod'");

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

    //string sql("UPDATE PARAMETERS SET VALUE = 2 WHERE PARAMETER = 'InterestRateMethod'");

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

    sqlite3 *DB;
    char *messageerror = new char[150];

    int exit = sqlite3_open(s, &DB);

    string sql("INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('InterestRateMethod', 2);"
               "INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('TargetInterestRate', 0.04);"
               "INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('CapitalReserveRatio', 0.4);"
               "INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('LiquidityReserveRatio', 0.5);"
               "INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('AverageSpendwill', 0.8);"
               "INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('AverageBorrowwill', 0.05);"
               "INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('FacIncreaseRate_1', 0.05);"
               "INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('CapIncreaseParam_1', 15000);"
               "INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('CapIncreaseRate_1', 0.001);"
               "INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('ItemEfficiencyRate', 0.000005);"
               "INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('ProductionParameter', 0.002);"
               "INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('IncomeTax', 0.3);"
               "INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('CapitalGainsTax', 0.3);"
               "INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('BudgetBalance', 0.00);"
               "INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('InflationTarget', 0.01);"
               "INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('PayWageInCash', 0);"
               "INSERT INTO PARAMETERS (PARAMETER, VALUE) VALUES('BankDividendRatio', 0.1);");

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageerror);
    //cout << "I SQL Fcn insterparam data, sql: " << sql << endl;
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
{ //std::vector<int> money

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

    //cout << "I SQL insert money data: " << sql << endl;

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
{ //std::vector<int> money

    string full_path = get_city_sql_string(city_name);
    const char *dir = full_path.c_str();

    sqlite3 *DB;
    char *messageerror;

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
        cerr << "Error insert" << endl;
        sqlite3_free(messageerror);
    }
    else
    {
        cout << "Time data updated successfully" << endl;
    }
    sqlite3_close(DB);
    return 0;
}

int insertWorldData(string world_name, string city_name, int consumers, string email, int created)
{ //std::vector<int> money

    string full_path = get_city_sql_string(world_name);
    //full_path += "Bennyworld.db";
    const char *dir = full_path.c_str();

    sqlite3 *DB;
    char *messageerror;

    int exit = sqlite3_open(dir, &DB);

    string sql = "INSERT INTO WORLD_TABLE (CITY_NAME, NO_CONSUMERS, EMAIL,  CREATED) VALUES(";

    sql.append("'" + city_name + "', ");
    sql.append("'" + std::to_string(consumers) + "', ");
    sql.append("'" + email + "', ");
    sql.append("'" + std::to_string(created) + "');");

    cout << "I insert world data, dir: " << dir << " and sql-string: " << sql << endl;

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageerror);

    if (exit != SQLITE_OK)
    {
        cerr << "Error in insert to world table" << endl;
        sqlite3_free(messageerror);
    }
    else
    {
        cout << "World table updated successfully" << endl;
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
{ //std::vector<int> money

    string full_path = get_city_sql_string(city_name);
    const char *dir = full_path.c_str();

    sqlite3 *DB;
    char *messageerror;

    int exit = sqlite3_open(dir, &DB);

    string sql = "INSERT INTO COMPANY_TABLE (TIME_STAMP, NAME, CAPITAL, STOCK, CAPACITY, DEBTS, PCSKILL, PCMOT, WAGE_CONST, WAGE_CH, INVEST, PBR, DECAY, PROD_PARM, PROD_FCN, PRODUCTION, EMPLOYEES, ITEM_EFFICIENCY, CAP_VS_EFF_SPLIT) VALUES(";

    sql.append(std::to_string((int)round(myData[0])) + ", ");  //time
    sql.append("'" + company_name + "', ");                    //name
    sql.append(std::to_string((int)round(myData[1])) + ", ");  //capital
    sql.append(std::to_string((int)round(myData[2])) + ", ");  //stock
    sql.append(std::to_string((int)round(myData[3])) + ", ");  //capacity
    sql.append(std::to_string((int)round(myData[4])) + ", ");  //debts
    sql.append(std::to_string(myData[5]) + ", ");              //PC_SKILL
    sql.append(std::to_string(myData[6]) + ", ");              //pc_mot
    sql.append(std::to_string(myData[7]) + ", ");              //wage_const
    sql.append(std::to_string(myData[8]) + ", ");              //wage_ch
    sql.append(std::to_string((int)round(myData[9])) + ", ");  //invest
    sql.append(std::to_string(myData[10]) + ", ");             //pbr
    sql.append(std::to_string(myData[11]) + ", ");             //decay
    sql.append(std::to_string(myData[12]) + ", ");             //prod_param
    sql.append(std::to_string((int)round(myData[13])) + ", "); //prod_fcn
    sql.append(std::to_string((int)round(myData[14])) + ", "); //Production
    sql.append(std::to_string((int)round(myData[15])) + ", "); //employees
    sql.append(std::to_string(myData[16]) + ", ");             //item efficiency
    sql.append(std::to_string(myData[17]) + ");");             //cap eff splie

    //sql.append(std::to_string(myData[11])  + ");");

    //cout << sql << endl;

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

int insertCompanyDatapoint(string parameter, int value, int timestamp, string city_name, string company_name)
{ //std::vector<int> money

    string full_path = get_city_sql_string(city_name);
    const char *dir = full_path.c_str();

    sqlite3 *DB;
    char *messageerror;

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
{ //std::vector<int> money

    string full_path = get_city_sql_string(world_name);
    const char *dir = full_path.c_str();

    sqlite3 *DB;
    char *messageerror;

    int exit = sqlite3_open(dir, &DB);

    string sql = "INSERT INTO HIGH_SCORE (COUNTRY, GROWTH, PALMA, ENV_IMP, TIMENOW) VALUES(";

    sql.append("'" + city_name + "', ");          //name
    sql.append(std::to_string(myData[0]) + ", "); //GROWTH
    sql.append(std::to_string(myData[1]) + ", "); //PALMA
    sql.append(std::to_string(myData[2]) + ", "); //ENV_IMP
    sql.append("'" + timenow + "');");            //ENV_IMP

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

int insertConsumerData(std::vector<double> myData, string country, string name, string employer)
{ //std::vector<int> money

    string full_path = get_city_sql_string(country);
    const char *dir = full_path.c_str();

    sqlite3 *DB;
    char *messageerror;

    int exit = sqlite3_open(dir, &DB);

    string sql = "INSERT INTO CONSUMER_TABLE (NAME, EMPLOYER, ITEMS, CAPITAL, DEPOSITS, DEBTS, SKILL, MOT, SPENDWILL, SAVEWILL, BORROWWILL, INCOME, DIVIDENDS, TRANSFERS) VALUES(";

    sql.append("'" + name + "', ");                           //name
    sql.append("'" + employer + "', ");                       //employer
    sql.append(std::to_string((int)round(myData[0])) + ", "); //items  (int)round(myData[1]))
    sql.append(std::to_string(myData[1]) + ", ");             //capital
    sql.append(std::to_string(myData[2]) + ", ");             //loans
    sql.append(std::to_string(myData[3]) + ", ");             //debts
    sql.append(std::to_string(myData[4]) + ", ");             //skill
    sql.append(std::to_string(myData[5]) + ", ");             //mot
    sql.append(std::to_string(myData[6]) + ", ");             //spendwill
    sql.append(std::to_string(myData[7]) + ", ");             //savewill
    sql.append(std::to_string(myData[8]) + ", ");             //borrowwill
    sql.append(std::to_string(myData[9]) + ", ");             //INCOME
    sql.append(std::to_string(myData[10]) + ", ");            //dividends
    sql.append(std::to_string(myData[11]) + ");");            //transfers

    //cout << sql << endl;

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageerror);

    if (exit != SQLITE_OK)
    {
        cerr << "Error insert CONSUMER_TABLE" << endl;
        sqlite3_free(messageerror);
    }
    else
    {
        //cout << "CONSUMER_TABLE updated successfully" << endl;
    }
    sqlite3_close(DB);
    return 0;
}

double getDatabaseParameter(string parameter, string city_name)
{

    using Record = vector<string>;
    using Records = vector<Record>;

    //cout << "i SQLF getdatabaseparam1" << endl;
    string full_path = get_city_sql_string(city_name);
    const char *dir = full_path.c_str();
    //cout << "i SQLF getdatabaseparam2" << endl;
    //cout << city_name << endl;

    double myParameterValue = 0;

    string stmt = "SELECT * FROM PARAMETERS WHERE PARAMETER = "; // 'AverageSpendwill'";
    stmt.append(parameter);

    Records records = select_stmt(stmt, dir);
    //cout << "i SQLF getdatabaseparam3" << parameter << endl;
    try
    {
        if (not(records.empty()))
        {
            myParameterValue = std::stod(records[0][2]);
        }
        else
        {
            cout << "Empty return from database" << endl;
        }
    }
    catch (const exception &e)
    {

        cerr << e.what();
    }

    //cout << "i SQLF getdatabaseparam4" << endl;
    return myParameterValue;
}

static int deleteTheData(const char *s)
{

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

//Creating a Database if not exist
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



//Creating the table for parameters
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

//Creating the table for parameters
static int createSQLParameterTable(string country)
{


    string sql = "CREATE TABLE IF NOT EXISTS PARAMETERS_Bennyland("
                 "ID INT PRIMARY KEY AUTO_INCREMENT, "
                 "PARAMETER  TEXT    NOT NULL, "
                 "VALUE      DECIMAL     NOT NULL );";
    cout << sql <<  endl;

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

//Creating the table for high-score
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

//Creating the table for the city-data
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

//Creating the table for the city-data
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

//Creating the table for companies
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

//Creating the world-table for cities/countries
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
        //sql_string = "/var/app/current/myDB/ekosimDB.db";
        sql_string = "/home/ecosim/myDB/ekosimDB.db";
    }

    //cout << "I SQL Functions get sql string " << sql_string << typeid(sql_string).name() << endl;

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
        //full_path = "/home/ec2-user/ekosimProject/myDB/";
    }

    full_path += city_name;
    full_path += ".db";

    const char *sql_string = full_path.c_str();

    //cout << "I SQL Functions get city sql string " << sql_string << " and as string: " << full_path << endl;

    return full_path;
}
