#pragma once
#include "travels_repository.h"
#include "offices.h"

//klasa przechowujaca oferty poszczegolnych biur podrozy i wykonujca na nich kilka operacji
class Offer
{
private:
	std::map<Office, std::vector<std::unique_ptr<Travel>>> offer;
	std::map<Office, std::vector<std::unique_ptr<Travel>>> init( const std::shared_ptr<Offices>& offices, const std::shared_ptr<TravelsRepository>& travels_repository);

	std::vector<std::unique_ptr<Travel>> travels_vector();
	bool is_exist(const std::vector<std::unique_ptr<Travel>>& travels,const Travel& travel);
	Travel highest_price(const std::vector<std::unique_ptr<Travel>>& travels);
	std::unordered_map<int, Travel> sort_map_values(std::unordered_map<int, Travel> map);
	std::list<std::string> europe_countries();
	bool is_europe_country(const Travel& travel);
public:
	Offer() = default;
	Offer( const std::shared_ptr<Offices>& offices,const std::shared_ptr<TravelsRepository>& travels_repository);

	//konstruktory i operatory przenoszace i kopiujace aby latwiej obslugiwalo sie uniqueptr
	Offer(const Offer& offer);
	Offer(Offer&& offer);
	Offer operator=(const Offer& offer);
	Offer& operator=(Offer&& offer);

	
	std::string office_name_with_the_most_travels();//metoda znajdujaca biuro podrozy najchetniej wybierane
	std::string office_name_with_highest_profit();//metoda znajdujaca biuro podrozy ktore zarobilo najwiecej
	std::string country_were_travels_most_often_organized();//mnetoda znajdujaca kraj do ktorego najchetniej podrozowano
	std::map<std::string, double> average_price();//metoda wyznacza srednia cene kazdego biura podrozy
	Travel close_to_average_price(const std::string& office,const double& average_price);//metoda wyznacza wycieczke ktora jest najblizej sredniej ceny wycieczek w danym biurze podrozy
	std::map<std::string,std::string> office_organized_most_travels_to_country();//zwraca do jakiego miejsca najczesciej dane biuro podrozy organizuje wycieczki  
	std::map<int, std::vector< std::unique_ptr<Travel>>> turnout_in_travel(); //zwraca mape ktorej kluczem jest ilosc osob a wartoscia wycieczki na ktorych bylo tyle osob
	std::list<std::unique_ptr<Travel>> travels_to_europe();//metoda zwraca wycieczki do europy
	std::unordered_map<int, Travel> highest_price_for_turnout();//zwraca mape gdzie kluczem jest ilosc osob a wartoscia najdrozsza wycieczka na ktorej bylo tyle osob
	
	~Offer() = default;
};

