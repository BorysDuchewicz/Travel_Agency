#pragma once
#include  "libs.h"
//klasa ktora laczy sie z baza danych oraz tworzy tabele o ile nie istnieja
class DbConnection
{
private:
	static DbConnection* instance;
	const std::string database_name = "travels";//zmienna przechowujaca nazwe bazy danych

	DbConnection();//jest prywatny aby nie mozna bylo tworzyc obiektow
	sqlite3* connection;//zmienna sluzaca do ³aczenia sie z bd
	void create_table()const;//metoda tworzaca tablice w bd
public:
	static DbConnection* get_instance(); //metoda pozwalajaca wyciagnac nam wskaznik do jedynego obiektu tej klasy
	sqlite3* get_connection();//metoda pozwalajaca nam odwolanie sie do sqlite3*
	~DbConnection();
};

