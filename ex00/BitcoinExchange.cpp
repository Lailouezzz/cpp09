#include "BitcoinExchange.hpp"

#include <sstream>
#include <iostream>
#include <cstdlib>

const std::map<std::string, float>	BitcoinExchange::m_price_history = BitcoinExchange::parseBdd();

std::map<std::string, float>	BitcoinExchange::parseBdd()
{
	std::map<std::string, float>	bdd;
	std::string						s(_binary_data_csv_start, _binary_data_csv_end - _binary_data_csv_start);
	std::istringstream				iss(s);

	std::string						line;
	std::getline(iss, line); // Ignore first line
	while (std::getline(iss, line))
	{
		std::string	date(line.substr(0, 10));
		std::string	price(line.substr(11));
		bdd[date] = atof(price.c_str());
	}
	return (bdd);
}

BitcoinExchange::BitcoinExchange()
{

}

BitcoinExchange::BitcoinExchange(BitcoinExchange const& o)
{
	*this = o;
}

BitcoinExchange::~BitcoinExchange()
{

}

BitcoinExchange		&BitcoinExchange::operator=(BitcoinExchange const& o)
{
	if (&o == this)
		return (*this);
	return (*this);
}