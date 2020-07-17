#pragma once
#include"offer.h"
#include"user_data_service.h"

// menu g³ówne ktore umozliwia uzytkownikowi wybor jaka akcje chce wykonac
class MenuService
{
private:
	std::shared_ptr<Offer> offer;
	static int choose_option();
	void option1()const;
	void option2()const;
	void option3()const;
	void option4()const;
	void option5()const;
	void option6()const;
	void option7()const;
	void option8()const;
public:
	MenuService(const std::shared_ptr<Offer>& offer);
	void main_menu()const;
	~MenuService() = default;
};

