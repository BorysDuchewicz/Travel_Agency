#pragma once
#include "libs.h"
//klasa s³uz¹ca do pobierania danych od uzytkownika
class UserDataService
{
	public:
	UserDataService() = delete;
	~UserDataService() = delete;
	static int get_int(const std::string& message);
	static std::string get_string(const std::string& message);
};

