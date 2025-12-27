#ifndef SQL_FUNCTIONS_H
#define SQL_FUNCTIONS_H

#include <iostream>
#include <sqlite3.h>
#include <stdio.h>
#include <vector>

using namespace std;
using Record = std::vector<std::string>;
using Records = std::vector<Record>;

int initiateDB();
int initiateCityDB(string city_name);
int initiateWorldDB(string world_name);

static int createDB(const char *s);
static int createParameterTable(const char *s);
static int createDataTable(const char *s);
static int createMoneyTable(const char *s);
static int createCompanyTable(const char *s);
static int createHighScoreTable(const char *s);
static int createConsumerTable(const char *s);
static int createWorldTable(const char *s);
static int insertParameterData(const char *s);
static int initiateCompanyTable(const char *s);

static int createSQLParameterTable(string);
static int createSQLDataTable(const char *s);
static int createSQLMoneyTable(const char *s);
static int createSQLCompanyTable(const char *s);
static int createSQLHighScoreTable(const char *s);
static int createSQLConsumerTable(const char *s);
static int createSQLWorldTable(const char *s);

int insertMoneyData(std::vector<int> money, string);      //
int insertTimeData(std::vector<double> timeData, string); //
int insertWorldData(string world_name, string city_name, int consumers, string email, int created);
int insertCompanyTimeData(std::vector<double> timeData, string city_name, string company_name);
int insertCompanyDatapoint(string parameter, int value, int timestamp, string city_name, string company_name);
int insertHighScore(std::vector<double> myData, string city_name, string world_name, string timenow);
int insertHighScorePG(std::vector<double> myData, string city_name, string user_id, string timenow);
int insertConsumerData(std::vector<double> myData, string, string, string);
int batchInsertConsumerDataPG(const vector<tuple<string, string, string, int, double, double, double, double, double, double, double, double, double, double, double>> &consumers, string city_name);

double getDatabaseParameter(string, string);

// PostgreSQL functions
int testPostgreSQLConnection();
int insertHighScorePG(std::vector<double> myData, string city_name, string user_id, string timenow);
vector<vector<string>> getHighScoresPG(string country_filter, int limit);
int insertWorldDataPG(string world_name, string city_name, int consumers, string email, int created);
Records getWorldTablePG(string world_name);
int insertTimeDataPG(std::vector<double> myData, string city_name);
Records getTimeDataPG(string city_name, int limit);
int deleteTimeDataPG(string city_name);
int insertMoneyDataPG(std::vector<int> money, string city_name);
Records getMoneyDataPG(string city_name, int limit);
int deleteMoneyDataPG(string city_name);
int insertCompanyTimeDataPG(std::vector<double> myData, string city_name, string company_name);
int batchInsertCompanyTimeDataPG(const vector<tuple<string, vector<double>>> &companies_data, string city_name);
Records getCompanyDataPG(string city_name, string company_name, int limit);
Records getAllCompaniesLatestDataPG(string city_name);
int deleteCompanyDataPG(string city_name);

// PostgreSQL PARAMETERS functions
int insertParameterPG(string city_name, string parameter, double value);
double getParameterPG(string city_name, string parameter);
int deleteParametersPG(string city_name);

// PostgreSQL CONSUMER_DATA functions
int insertConsumerDataPG(string city_name, string consumer_name, string employer,
                         int items, double capital, double deposits, double debts, double skill,
                         double mot, double spendwill, double savewill, double borrowwill,
                         double income, double dividends, double transfers);
Records getConsumerDataPG(string city_name, string consumer_name);
int deleteConsumerDataPG(string city_name);

// PostgreSQL COMPANY_DATA initialization
int initiateCompanyTablePG(string city_name);

static int updateData(const char *s);
static int updateParameter(const char *s, string, double);
static int deleteTheData(const char *s);
static int deleteWorldData(const char *s);

static int selectData(const char *s);
static int callback(void *NotUsed, int argc, char **argv, char **azColName);

int select_callback(void *p_data, int num_fields, char **p_fields, char **p_col_names);
Records select_stmt(string stmt, const char *s);      // const char* - SQLite version (deprecated)
Records select_stmt_pg(string sql, string city_name); // PostgreSQL version

const char *get_sql_string();
string get_city_sql_string(string city_name);

#endif