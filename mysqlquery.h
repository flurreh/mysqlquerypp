#ifndef MYSQLQUERY_H
#define MYSQLQUERY_H
#include <mysql.h>
#include <stdint.h>
#include <string>
#include <algorithm>
#include <map>
#include <iostream>
#include <sstream>

class MySQLConnection
{

public:
    MySQLConnection();
    ~MySQLConnection();
    // connects to a MySQL-server
    bool Connect(std::string sHostname, uint16_t wPort, std::string sUsername, std::string sPassword, std::string sDB);
    // selects a DB
    bool SelectDB(std::string sSchemaName);
    // disconnects (huh, who guessed this?)
    void Disconnect();
    // returns the last error string
    std::string GetLastError();
    // gets a pointer to the MySQL connection
    MYSQL *getConn();
    // returns true when connected
    bool IsConnected();
    // returns an escaped string
    std::string EscapeString(std::string value);

private:
    MYSQL *m_MySQLConn;
    bool m_bIsConnected;
    std::string m_sHostname;
    std::string m_sUsername;
    std::string m_sPassword;
    std::string m_sSchemaName;
    uint16_t m_wPort;
};

class MySQLQuery
{

public:

    MySQLQuery(MySQLConnection *mConn, std::string sStatement);
    ~MySQLQuery();

    // sets the value of idx to a given string (also adds quotation marks and escapes the string)
    bool setString(unsigned int idx, std::string value);
    // sets the value of idx to a given int
    bool setInt(unsigned int idx, int value);
    // sets the value of idx to a given double
    bool setDouble(unsigned int idx, double value);
    // sets the value of idx to a given time_t
    bool setTime(unsigned int idx, time_t value);
    // sets the value of idx to NULL
    bool setNull(unsigned int idx);

    // executes a SELECT-statement
    bool ExecuteQuery();
    // executes an UPDATE-statement
    bool ExecuteUpdate();
    // executes an INSERT-statement and returns the last inserted ID
    int ExecuteInsert();

    // builds the query string with filled-in arguments and returns it
    std::string BuildQueryString();

    // returns a field name
    std::string getFieldName(unsigned int field);
    // gets a string value from the given row and field
    std::string getString(unsigned int row, unsigned int field);
    std::string getString(unsigned int row, std::string field);
    // gets an int value from the given row and field
    int getInt(unsigned int row, unsigned int field);
    int getInt(unsigned int row, std::string field);
    // gets a double value from the given row and field
    double getDouble(unsigned int row, unsigned int field);
    double getDouble(unsigned int row, std::string field);
    // gets a time value from the given row and field
    time_t getTime(unsigned int row, unsigned int field);
    time_t getTime(unsigned int row, std::string field);

    // returns the result row count
    unsigned int GetResultRowCount();
    unsigned int GetFieldCount();


private:
    typedef std::map<int, std::string> TResultRow;
    MySQLConnection *m_sqlConn;
    int m_iResultRowCount;
    std::string m_sStatement;
    std::map<int, std::string> m_mArgMap;
    std::map<int, TResultRow> m_mResultMap;
    std::map<int, std::string> m_mFieldMap;
    std::map<std::string, int> m_mFieldStringToIntMap;

};

#endif // MYSQLQUERY_H
