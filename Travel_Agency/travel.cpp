
#include "travel.h"
Travel::Travel(const int& travel_id, const std::string& country, const double& price, const int& turnout,
	const int& office_id):
	travel_id{ travel_id }, country{ country }, price{ price }, turnout{ turnout }, office_id{office_id} {}

Travel::Travel(const std::string& country, const double& price, const int& turnout, const int& office_id):
	country{ country }, price{ price }, turnout{ turnout }, office_id{ office_id }{}

Travel Travel::operator=(const Travel& t)
{
	if(this!=&t)
	{
		this->travel_id = t.travel_id;
		this->country = t.country;
		this->price = t.price;
		this->turnout = t.turnout;
		this->office_id = t.office_id;
	}
	return *this;
}

bool Travel::operator==(const Travel& t) const
{
	return  this->country == t.country && this->price == t.price && this->turnout == t.turnout && this->office_id == t.office_id;
}

std::ostream& operator<<(std::ostream& out, const Travel& travel)
{
	return out << travel.travel_id << " " << travel.country << " " << travel.price << " " << travel.turnout << " " << travel.office_id << std::endl;
}
