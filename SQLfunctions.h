#ifndef SQL_FUNCTIONS_H
#define SQL_FUNCTIONS_H

#include <iostream>
#include <sqlite3.h>
#include <stdio.h>

using namespace std;
using Record = std::vector<std::string>;
using Records = std::vector<Record>;

int initiateDB();
static int createDB(const char* s);
static int createParameterTable(const char* s);
static int createDataTable(const char* s);
static int createMoneyTable(const char* s);
static int insertParameterData(const char* s);
int insertMoneyData(std::vector<int> money); //
int insertTimeData(std::vector<double> timeData); //

static int updateData(const char* s);
static int updateParameter(const char* s, string, double);
static int deleteTheData(const char* s);
static int selectData(const char* s);
static int callback(void* NotUsed, int argc, char** argv, char** azColName);
int testFunction();

int select_callback(void *p_data, int num_fields, char **p_fields, char **p_col_names);
Records select_stmt(const char* stmt, const char* s);

#endif