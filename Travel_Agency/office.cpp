#include "office.h"

Office::Office(const int& office_id, const std::string& name, const std::string& location) :
office_id{ office_id }, name{ name }, location{location} {}

bool Office::operator<(const Office& office) const
{
	return this->office_id < office.office_id;
}

std::ostream& operator<<(std::ostream& out, const Office& office)
{
	return out << office.office_id << " " << office.name << " " << office.location << std::endl;
}
