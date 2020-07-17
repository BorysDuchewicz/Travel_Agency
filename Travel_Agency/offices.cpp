#include "offices.h"

std::vector<std::unique_ptr<Office>> Offices::read_from_json(const std::string& file_name)
{
	std::vector<std::unique_ptr<Office>> offices;
	std::ifstream reader;

	reader.open(file_name + ".json");
	if(reader.is_open())
	{
		json j;
		reader >> j;
		for(const auto& file:j)
		{
			Office office;

			office.office_id = file["office_id"].get<int>();
			office.name = file["name"].get<std::string>();
			office.location = file["location"].get<std::string>();

			offices.emplace_back(std::make_unique<Office>(office));
		}
	}
	else
	{
		std::cout << "Path error"<<std::endl;
	}
	return offices;
}

Offices::Offices(const std::string& file_name)
{
	this->offices = read_from_json(file_name);
}

Offices::Offices(const Offices& offices)
{
	for(const auto& office:offices.offices)
	{
		this->offices.emplace_back(std::make_unique<Office>(*office));
	}
}

Offices::Offices(Offices&& offices)
{
	this->offices = std::move(offices.offices);
}

Offices Offices::operator=(const Offices& offices)
{
	if(this != &offices)
	{
		for (const auto& office : offices.offices)
		{
			this->offices.emplace_back(std::make_unique<Office>(*office));
		}
	}
	return *this;
}

Offices& Offices::operator=(Offices&& offices)
{
	if (this != &offices)
	{
			this->offices=std::move(offices.offices);		
	}
	return *this;
}

std::vector<std::unique_ptr<Office>> Offices::get_all_offices()
{
	std::vector<std::unique_ptr<Office>> offices;
	for(const auto& office:this->offices)
	{
		offices.emplace_back(std::make_unique<Office>(*office));
	}
	return offices;
}

std::ostream& operator<<(std::ostream& out, const Offices& offices)
{
	for (const auto& office : offices.offices)
	{
		out << *office << std::endl;
	}
	return out;
}
