#ifndef  BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <string>

extern "C" const char _binary_data_csv_start[];
extern "C" const char _binary_data_csv_end[];

class BitcoinExchange
{
	public:
		static float		getPriceOfDay(int const& date);

	private:
		BitcoinExchange();
		static std::map<int, float, std::greater<int> >	parseBdd();
		static const std::map<int, float, std::greater<int> > m_price_history;
};

#endif
