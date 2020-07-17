#pragma once
#include  "libs.h"
//klasa przechowujaca informacje o wycieczce
struct Travel
{
public:
	int travel_id;
	std::string country;
	double price;
	int turnout;
	int office_id;

	Travel() = default;
	Travel(const int& travel_id,const std::string& country,const double& price,const int& turnout,const int& office_id);
	Travel(const std::string& country,const double& price,const int& turnout,const int& office_id);

	
	~Travel() = default;

	Travel operator=(const Travel& t);
	bool operator==(const Travel& t) const;
	friend std::ostream& operator<<(std::ostream& out, const Travel& travel);
};

