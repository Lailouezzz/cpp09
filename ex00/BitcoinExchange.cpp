#include "BitcoinExchange.hpp"

#include <sstream>
#include <iostream>
#include <cstdlib>
#include <algorithm>

const std::map<int, float, std::greater<int> >	BitcoinExchange::m_price_history = BitcoinExchange::parseBdd();

std::map<int, float, std::greater<int> >	BitcoinExchange::parseBdd()
{
	std::map<int, float, std::greater<int> >	bdd;
	std::string						s(_binary_data_csv_start, _binary_data_csv_end - _binary_data_csv_start);
	std::istringstream				iss(s);

	std::string						line;
	std::getline(iss, line); // Ignore first line
	while (std::getline(iss, line))
	{
		std::string	date = line.substr(0, 4) + line.substr(5, 2) + line.substr(8, 2);
		std::string	price(line.substr(11));
		bdd[atoi(date.c_str())] = atof(price.c_str());
	}
	return (bdd);
}

float	BitcoinExchange::getPriceOfDay(int const& date)
{
	std::map<int, float, std::greater<int> >::const_iterator	itr = m_price_history.lower_bound(date);
	return (itr->second);
}
