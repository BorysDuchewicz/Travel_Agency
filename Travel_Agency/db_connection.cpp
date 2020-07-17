#include "db_connection.h"

DbConnection::DbConnection()
{
	const auto results = sqlite3_open(database_name.c_str(), &connection);
	if(SQLITE_OK!=results)
	{
		throw std::exception(sqlite3_errmsg(connection));
	}
	create_table();
}

void DbConnection::create_table() const
{
	const std::string sql_travels =
		"create table if not exists travels("
		"travel_id integer primary key autoincrement,"
		"country varchar(30) not null,"
		"price double not null,"
		"turnout integer not null,"
		"office_id integer not null);";
	char** error_message = nullptr;
	auto results = sqlite3_exec(connection, sql_travels.c_str(), nullptr, nullptr, error_message);
	if(SQLITE_OK!=results)
	{
		std::cout << sqlite3_errmsg(connection) << std::endl;
		sqlite3_free(error_message);
		throw std::exception("travels table creation error");
	}
	
}

DbConnection* DbConnection::get_instance()
{
	return instance;
}

sqlite3* DbConnection::get_connection()
{
	return connection;
}

DbConnection::~DbConnection()
{
	free(connection);
}

DbConnection* DbConnection::instance = new DbConnection();
