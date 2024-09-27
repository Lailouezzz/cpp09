#include <iostream>
#include <cstdlib>

#include "BitcoinExchange.hpp"

int	main(void)
{
	for (std::map<std::string, float>::const_iterator itr = BitcoinExchange::m_price_history.begin(); itr != BitcoinExchange::m_price_history.end(); ++itr)
	{
		std::cout << "date : " << itr->first << std::endl;
		std::cout << "price : " << itr->second << std::endl;
	}
	return (EXIT_SUCCESS);
}
