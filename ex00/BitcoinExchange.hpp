#ifndef  BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <string>

extern "C" const char _binary_data_csv_start[];
extern "C" const char _binary_data_csv_end[];

class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(BitcoinExchange const& o);
		~BitcoinExchange();

		BitcoinExchange		&operator=(BitcoinExchange const& o);

	// private:
		static std::map<std::string, float>	parseBdd();
		static const std::map<std::string, float> m_price_history;
};

#endif
