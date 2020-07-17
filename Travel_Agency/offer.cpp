#include "offer.h"

std::map<Office, std::vector<std::unique_ptr<Travel>>> Offer::init(
	const std::shared_ptr<Offices>& offices,const std::shared_ptr<TravelsRepository>& travels_repository)
{
	std::map<Office, std::vector<std::unique_ptr<Travel>>> offer;
	std::vector<std::unique_ptr<Travel>> travels = travels_repository->find_all();
	std::vector<std::unique_ptr<Travel>> help;
	

	for(const auto& office:offices->get_all_offices())
	{
		
		for(const auto& travel:travels)
		{
			
			if(travel->office_id==office->office_id)
			{
				help.emplace_back(std::make_unique<Travel>(*travel));
			}
		}
		
		offer.emplace(*office, std::move(help));
		
		help.clear();
	}
	
	return offer;
}

std::vector<std::unique_ptr<Travel>> Offer::travels_vector()
{
	std::vector<std::unique_ptr<Travel>> travels;
	for (const auto& i : this->offer)
	{
		for (const auto& travel : i.second)
		{
			travels.emplace_back(std::make_unique<Travel>(*travel));
		}
	}
	return travels;
}


bool Offer::is_exist(const std::vector<std::unique_ptr<Travel>>& travels, const Travel& travel)
{

	for (const auto& i : travels)
	{
		if(*i==travel)
		{
			return true;
		}
	}
	return false;
}

Travel Offer::highest_price(const std::vector<std::unique_ptr<Travel>>& travels)
{
	Travel t;
	double price = 0;
	for(const auto& travel:travels)
	{
		if(travel->price>price)
		{
			price = travel->price;
			t = *travel;
		}
	}
	return t;
}

std::unordered_map<int, Travel> Offer::sort_map_values(std::unordered_map<int, Travel> map)
{
	std::vector<std::pair<int, Travel>> vec;
	std::copy(map.begin(), map.end(), std::back_inserter<std::vector<std::pair<int, Travel>>>(vec));

	std::sort(vec.begin(), vec.end(), [](const std::pair<int, Travel>& l, const std::pair<int, Travel>& r)
		{
			if (l.second.price != r.second.price)
			{
				return l.second.price > r.second.price;
			}
			return l.first < r.first;
		});


	map.clear();
	for (int i = 0; i < vec.size(); ++i)
	{
		map.emplace(std::make_pair(vec[i].first, vec[i].second));
	}

	return map;
}

std::list<std::string> Offer::europe_countries()
{
	std::list<std::string> europe_countries;
	std::string txt;
	std::ifstream reader;
	reader.open("europe.txt");
	if(reader.is_open())
	{
		while(!reader.eof())
		{
			std::getline(reader, txt);
			europe_countries.emplace_back(txt);
		}
		reader.close();
	}
	else
	{
		std::cout << "path error";
	}
	
	return europe_countries;
}

bool Offer::is_europe_country(const Travel& travel)
{
	std::list<std::string> europe_countries = Offer::europe_countries();

	for(const auto& country:europe_countries)
	{
		if(country==travel.country)
		{
			return true;
		}
	}
	return false;
}

Offer::Offer(const std::shared_ptr<Offices>& offices, const std::shared_ptr<TravelsRepository>& travels_repository)
{

	this->offer = init(offices, travels_repository);
}

Offer::Offer(const Offer& offer)
{
	std::vector<std::unique_ptr<Travel>> help;
	for (const auto& i : offer.offer)
	{

		for (const auto& travel : i.second)
		{
				help.emplace_back(std::make_unique<Travel>(*travel));
		}
		this->offer.emplace(std::make_pair(i.first,std::move(help)));
		help.clear();
	}	
}

Offer::Offer(Offer&& offer)
{
	this->offer = std::move(offer.offer);
}

Offer Offer::operator=(const Offer& offer)
{
	if(this!=&offer)
	{
		std::vector<std::unique_ptr<Travel>> help;
		for (const auto& i : offer.offer)
		{
			for (const auto& travel : i.second)
			{
				help.emplace_back(std::make_unique<Travel>(*travel));
			}
			this->offer.emplace(std::make_pair(i.first, std::move(help)));
			help.clear();
		}
	}
	return *this;
}

Offer& Offer::operator=(Offer&& offer)
{
	if (this != &offer)
	{
		this->offer = std::move(offer.offer);
	}
	return *this;
}

std::string Offer::office_name_with_the_most_travels()
{
	std::string office_name;
	int size = 0;
	for(const auto& i:this->offer)
	{
		if(size<i.second.size())
		{
			office_name = i.first.name;
			size = i.second.size();
		}
	}
	return office_name;
}

std::string Offer::office_name_with_highest_profit()
{
	std::string office_name;
	double profit = 0;
	double highest_profit = 0;
	const double tax = 0.19;
	const double profit_percent = 0.1;
	for (const auto& i : this->offer)
	{
		profit = 0;
		for(const auto& travel:i.second)
		{
			profit += 0.1*travel->price * travel->turnout * (1-tax);
			if(profit>highest_profit)
			{
				highest_profit = profit;
				office_name = i.first.name;
			}
		}
	}
	return office_name;
}

std::string Offer::country_were_travels_most_often_organized()
{
	std::string most_visited_country;
	int count = 0;
	int visits = 0;
	std::string country_name;
	std::vector<std::unique_ptr<Travel>> travels=travels_vector();
	
	for(const auto& i:travels)
	{
		count = 0;
		country_name = i->country;
		for (const auto& travel : travels)
		{
			if (country_name == travel->country)
			{
				count++;
			}
			if(count>visits)
			{
				visits = count;
				most_visited_country = travel->country;
			}
		}
	}
	return most_visited_country;
}

std::map<std::string, double> Offer::average_price()
{
	std::map<std::string, double> average_price;
	double price = 0;
	for(const auto& i:this->offer)
	{
		price = 0;
		for(const auto& travel:i.second)
		{
			price += travel->price;
		}
		average_price.emplace(std::make_pair(i.first.name, price / i.second.size()));
	}
	return average_price;
}

Travel Offer::close_to_average_price(const std::string& office,const double& average_price)
{
	Travel t;
	double diff=DBL_MAX;
	
	for(const auto& i:this->offer)
	{
		if (i.first.name == office)
		{
			for (const auto& travel : i.second)
			{
				if (abs(travel->price - average_price) < diff)
				{
					t = *travel;
					diff = abs(travel->price - average_price);
				}
			}
		}
	}
	
	return t;
}

std::map<std::string, std::string> Offer::office_organized_most_travels_to_country()
{
	std::map<std::string, std::string> office_organized_most_travels_to_country;

	for(const auto& i:this->offer)
	{
		for(const auto& travel:i.second)
		{
			office_organized_most_travels_to_country.emplace(std::make_pair(travel->country,""));
		}
	}
	int count = 0;
	int how = 0;
	for(const auto& i:office_organized_most_travels_to_country)
	{
		for (const auto& j : this->offer)
		{
			for (const auto& travel : j.second)
			{
				if(i.first==travel->country)
				{
					count++;
				}
			}
			if(count>how)
			{
				how = count;
				office_organized_most_travels_to_country[i.first] = j.first.name;
			}
		}
	}
	return office_organized_most_travels_to_country;
}

std::map<int, std::vector<std::unique_ptr<Travel>>> Offer::turnout_in_travel()
{
	std::map<int, std::vector<std::unique_ptr<Travel>>> turnout_in_travel;
	std::vector<std::unique_ptr<Travel>> travels;
	for(const auto& i:this->offer)
	{
		for(const auto& travel:i.second)
		{
			turnout_in_travel.emplace(std::make_pair(travel->turnout, 0));
		}
	}

	for(const auto& people:turnout_in_travel)
	{
		for(const auto& i:this->offer)
		{
			for(const auto& travel:i.second)
			{
				if(people.first==travel->turnout && !is_exist(travels,*travel))
				{
					travels.emplace_back(std::make_unique<Travel>(*travel));
				}
			}
		}
		turnout_in_travel[people.first] = std::move(travels);
		travels.clear();
	}
	return turnout_in_travel;
}

std::list<std::unique_ptr<Travel>> Offer::travels_to_europe()
{
	std::list<std::unique_ptr<Travel>> travels_to_europe;
	

	for(const auto& i:this->offer)
	{
		for(const auto& travel:i.second)
		{
			if(is_europe_country(*travel))
			{
				travels_to_europe.emplace_back(std::make_unique<Travel>(*travel));
			}
		}
	}
	return travels_to_europe;
}

std::unordered_map<int, Travel> Offer::highest_price_for_turnout()
{
	std::map<int, std::vector<std::unique_ptr<Travel>>> turnout_in_travel = Offer::turnout_in_travel();
	std::unordered_map<int, Travel> highest_price_for_turnout;
	std::vector <std::unique_ptr<Travel>> travels;
	
	for(const auto& travel:turnout_in_travel)
	{
		for(const auto& i:travel.second)
		{
			travels.emplace_back(std::make_unique<Travel>(*i));
		}
		highest_price_for_turnout.emplace(std::make_pair(travel.first, Offer::highest_price(travels)));
		travels.clear();
	}
	highest_price_for_turnout = Offer::sort_map_values(highest_price_for_turnout);
	return highest_price_for_turnout;
}


