#include "travels_repository.h"

std::string TravelsRepository::from_unsigned_char_to_string(const unsigned char* value)
{
	std::string result;
	for(int i=0;i<strlen(reinterpret_cast<const char*>(value));++i)
	{
		result += value[i];
	}
	return result;
}

std::optional<Travel> TravelsRepository::add(const std::unique_ptr<Travel>& travel) const
{
	const std::string SQL = "insert into travels (country,price,turnout,office_id) values (?,?,?,?)";
	sqlite3_stmt* stmt = nullptr;
	sqlite3_prepare_v2(connection->get_connection(), SQL.c_str(), -1, &stmt, nullptr);
	sqlite3_bind_text(stmt, 1, travel->country.c_str(),-1,SQLITE_STATIC);
	sqlite3_bind_double(stmt, 2, travel->price);
	sqlite3_bind_int(stmt, 3, travel->turnout);
	sqlite3_bind_int(stmt, 4, travel->office_id);
	const auto result = sqlite3_step(stmt);

	if (result != SQLITE_DONE)
	{
		sqlite3_errmsg(connection->get_connection());
		throw std::exception(sqlite3_errmsg(connection->get_connection()));
	}
	sqlite3_finalize(stmt);
	return find_last();
}

std::optional<Travel> TravelsRepository::find_last() const
{
	const std::string SQL = "select travel_id,country,price,turnout,office_id from travels order by id desc limit 1";
	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(connection->get_connection(), SQL.c_str(), -1, &stmt, nullptr);
	const auto result = sqlite3_step(stmt);

	while (result == SQLITE_ROW)
	{
		return std::make_optional(Travel{
			sqlite3_column_int(stmt,0),
			from_unsigned_char_to_string(sqlite3_column_text(stmt,1)),
			sqlite3_column_double(stmt,2),
			sqlite3_column_int(stmt,3),
			sqlite3_column_int(stmt,4)
			});
	}
	sqlite3_finalize(stmt);
	return std::nullopt;
}

std::vector<std::unique_ptr<Travel>> TravelsRepository::find_all() const
{
	std::vector<std::unique_ptr<Travel>> travels;
	const std::string SQL = "select travel_id,country,price,turnout,office_id from travels";
	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(connection->get_connection(), SQL.c_str(), -1, &stmt, nullptr);
	auto result = 0;
	while ((result = sqlite3_step(stmt)) == SQLITE_ROW)
	{

		travels.emplace_back(std::make_unique<Travel>(Travel{
			sqlite3_column_int(stmt,0),
			from_unsigned_char_to_string(sqlite3_column_text(stmt,1)),
			sqlite3_column_double(stmt,2),
			sqlite3_column_int(stmt,3),
			sqlite3_column_int(stmt,4)
			}));
	}
	sqlite3_finalize(stmt);
	return travels;
}
