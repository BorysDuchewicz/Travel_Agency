#include "user_data_service.h"

int UserDataService::get_int(const std::string& message)
{
	std::cout << message << std::endl;
	std::string text;
	std::getline(std::cin, text);

	if (!std::regex_match(text, std::regex("\\d+")))
	{
		throw std::exception("incorrect int value");
	}

	return std::stoi(text);
}

std::string UserDataService::get_string(const std::string& message)
{
	std::cout << message << std::endl;
	std::string text;
	std::getline(std::cin, text);

	return text;
}
