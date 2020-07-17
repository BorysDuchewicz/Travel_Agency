#pragma once
#include "office.h"

//klasa przechowuj¹ca wiele biur podró¿y 
class Offices
{
private:
	std::vector<std::unique_ptr<Office>> offices;//zmienna przechowuj¹ca biura
	std::vector<std::unique_ptr<Office>> read_from_json(const std::string& file_name);//metoda wczytujaca biura z pliku json
public:
	Offices(const std::string& file_name);
	~Offices() = default;

	//konstruktory i operatory przenoszace i kopiujace aby mozna bylo bez problemow operowac na unique_ptr
	Offices(const Offices& offices);
	Offices(Offices&& offices);
	Offices operator=(const Offices& offices);
	Offices& operator=(Offices&& offices);

	std::vector<std::unique_ptr<Office>> get_all_offices();//metoda zwracajaca wszystkie biura 
	friend std::ostream& operator<<(std::ostream& out, const Offices& offices);


};

