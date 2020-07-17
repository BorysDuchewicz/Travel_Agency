#pragma once
#include "libs.h"

//structura przerdchowujaca informacje o biurach podruzy 
struct Office
{
public:
	int office_id;
	std::string name;
	std::string location;

	Office() = default;
	Office(const int& office_id, const std::string& name, const std::string& location);

	bool operator<(const Office& office)const;// prze�adowany operator < aby mozna by�o por�wnywa�z �atwo�ci� obiekty Office
	
	~Office() = default;

	friend std::ostream& operator<<(std::ostream& out, const Office& office);
};

