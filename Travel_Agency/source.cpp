
#include "menu_service.h"

int main()
{
	try
	{
		Offices offices{ "offices" };
		TravelsRepository travels_repository;

		const std::shared_ptr<Offices> offices_ptr{ std::make_shared<Offices>(offices) };
		const std::shared_ptr<TravelsRepository> travels{ std::make_shared<TravelsRepository>(travels_repository) };

		Offer offer{ offices_ptr,travels };
		const std::shared_ptr<Offer> offer_ptr{ std::make_shared<Offer>(offer) };

		MenuService menu{ offer_ptr };
		menu.main_menu();
	}
	catch(const std::exception& e)
	{
		std::cout << e.what()<<std::endl;
	}

	return 0;
}