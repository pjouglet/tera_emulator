#ifndef MYSQL_DRIVER_H
#define MYSQL_DRIVER_H

#include <vector>
#include <mutex>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <mysql_error.h>
#include <cppconn\resultset.h>
#include <cppconn\statement.h>
#include <cppconn\datatype.h>
#include <cppconn\prepared_statement.h>


#define MAX_CLIENTS_PER_CONNECTION 50

class MySqlDriver
{
public:
	MySqlDriver();
	~MySqlDriver();

public:
	sql::Connection * GetConnection();

	const bool initDriver(const char* hostAddress, const char* hostUsername, const char * hostPassword, const char* databaseName);

	sql::ResultSet* ExecuteQuery(const char* query);
	int ExecuteNonQuery(const char* query);
	bool ExecuteUpdate(const char* query);
	void InsertBlob(std::istream * blob);

	sql::PreparedStatement * GetPreparedStatement(std::string query);
	const bool Lock();
	const bool Unlock();

private:
	void ReleaseStatement();


	sql::Driver * _driver; 
	sql::Connection * _connection; 
	sql::Statement *_statement; 
	sql::PreparedStatement * _prepStatement;

	bool _isValid = false;

	const char * _hostAddress;
	const char * _hostUsername;
	const char * _hostPassword;
	std::mutex _locked;
};
#endif
