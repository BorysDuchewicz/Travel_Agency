#pragma once
#include  "db_connection.h"
#include "travel.h"
//klasa pobierajaca wycieczki z bd i umozliwiajaca operacje na nich
class TravelsRepository
{
private:
	DbConnection* connection = DbConnection::get_instance();
	static std::string from_unsigned_char_to_string(const unsigned char* value);
public:
	std::optional<Travel> add(const std::unique_ptr<Travel>& travel)const;//pozwala na dodanie wycieczki do bd
	std::optional<Travel> find_last()const;//znajduje ostatnia wycieczke wpisana do bd
	std::vector<std::unique_ptr<Travel>> find_all()const;//znajduje wszystkei wycieczki w bd

};

