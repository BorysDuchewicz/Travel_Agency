
#include "menu_service.h"

int MenuService::choose_option()
{
	std::cout << "MENU" << std::endl;
	std::cout << "Choose option:" << std::endl;
	std::cout << "1 - Show the office that organized the most trips" << std::endl;
	std::cout << "2 - Show the office that has earned the most" << std::endl;
	std::cout << "3 - Show the most popular country" << std::endl;
	std::cout << "4 - Average travel price and travel price close to average" << std::endl;
	std::cout << "5 - Counties and office that organized the most travels" << std::endl;
	std::cout << "6 - Show travels only to europe" << std::endl;
	std::cout << "7 - Map with turnout in key and in value travel with that turnout without duplication" << std::endl;
	std::cout << "8 - Map with turnout in key and value the most expensive travel " << std::endl;
	std::cout << "9 - exit" << std::endl;
	const int choice = UserDataService::get_int("");
	return choice;
}

void MenuService::option1() const
{
	std::cout<<offer->office_name_with_the_most_travels();
}

void MenuService::option2() const
{
	std::cout << offer->office_name_with_highest_profit();
}

void MenuService::option3() const
{
	std::cout << offer->country_were_travels_most_often_organized();
}

void MenuService::option4() const
{
	for (const auto& i : offer->average_price())
	{
		std::cout << i.first << " " << i.second << " " << offer->close_to_average_price(i.first, i.second) << std::endl;
	}
}

void MenuService::option5() const
{
	for (const auto& i : offer->office_organized_most_travels_to_country())
	{
		std::cout << i.first << " " << i.second << std::endl;
	}
}

void MenuService::option6() const
{
	for (const auto& i : offer->travels_to_europe())
	{
		std::cout << *i;
	}
}

void MenuService::option7() const
{
	for (const auto& i : offer->turnout_in_travel())
	{
		std::cout << i.first << " ";
		for (const auto& j : i.second)
		{
			std::cout << *j << " ";
		}
		std::cout << std::endl;
	}
}

void MenuService::option8() const
{
	for (const auto& i : offer->highest_price_for_turnout())
	{
		std::cout << i.first << " " << i.second << std::endl;


	}
}

MenuService::MenuService(const std::shared_ptr<Offer>& offer):
	offer{offer} {}

void MenuService::main_menu() const
{
	try
	{
		while (true)
		{
			const int option = choose_option();
			switch (option)
			{
			case 1:
				option1();
				std::cin.get();
				system("cls");
				break;
			case 2:
				option2();
				std::cin.get();
				system("cls");
				break;
			case 3:
				option3();
				std::cin.get();
				system("cls");
				break;
			case 4:
				option4();
				std::cin.get();
				system("cls");
				break;
			case 5:
				option5();
				std::cin.get();
				system("cls");
				break;
			case 6:
				option6();
				std::cin.get();
				system("cls");
				break;
			case 7:
				option7();
				std::cin.get();
				system("cls");
				break;
			case 8:
				option8();
				std::cin.get();
				system("cls");
				break;
			case 9:
				std::cout << "Have a nice day!";
				std::cin.get();
				return;
			default:
				std::cout << "No option with number " << option << std::endl;
				std::cin.get();
				system("cls");
			}
		}
	}
	catch (const std::exception & exception)
	{
		std::cout << exception.what() << std::endl;
		std::cin.get();
		system("cls");
		main_menu();
	}
}

