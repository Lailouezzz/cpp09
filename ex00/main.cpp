#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include "BitcoinExchange.hpp"

bool isdigit(std::string const& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it))
		++it;
	return (!s.empty() && it == s.end());
}

float to_float(std::string const& ratio)
{
	std::stringstream	ss;
	float				r;

	ss << ratio.substr(0, ratio.find_last_not_of(' ') + (ratio.find_last_not_of(' ') != std::string::npos ? 1 : 0));
	if (!(ss >> r) || !ss.eof())
		throw std::exception();
	return (r);
}

bool checkDate(std::string const& date)
{
	std::string year(date.substr(0, 4));
	std::string month(date.substr(5, 2));
	std::string day(date.substr(8, 2));

	if (!isdigit(year) || !isdigit(month) || !isdigit(day) || date[4] != '-' || date[7] != '-')
		return (false);
	int d = atoi(day.c_str());
	int m = atoi(month.c_str());
	int y = atoi(year.c_str());
	if (!(1 <= m && m <= 12))
		return (false);
	if (!(1 <= d && d <= 31))
		return (false);
	if ((d == 31) && (m == 2 || m == 4 || m == 6 || m == 9 || m == 11))
		return (false);
	if ((d == 30) && (m == 2))
		return (false);
	if ((m == 2) && (d == 29) && (y % 4 != 0))
		return (false);
	if ((m == 2) && (d == 29) && (y % 400 == 0))
		return (true);
	if ((m == 2) && (d == 29) && (y % 100 == 0))
		return (false);
	if ((m == 2) && (d == 29) && (y % 4 == 0))
		return (true);
	return (true);
}

static void	_treatFile(const char *fn);
static void	_treatLine(std::string const& line);
static void	_computeLine(std::string const& date, std::string const& ratio);

int main(int argc, char **argv)
{

	if (argc != 2)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return (EXIT_FAILURE);
	}
	_treatFile(argv[1]);
	return (EXIT_SUCCESS);
}

void	_treatFile(const char *fn)
{
	std::ifstream	file;
	file.open(fn);
	std::string	line;
	std::getline(file, line);
	while (std::getline(file, line))
	{
		_treatLine(line);
	}
}

#define DATE_SIZE (10)

void	_treatLine(std::string const& line)
{
	std::size_t	date_start = line.find_first_not_of(' ');
	std::size_t	ratio_start = line.find_first_of('|');
	if (date_start + DATE_SIZE > ratio_start || ratio_start == std::string::npos)
	{
		std::cerr << "Error: bad input => " << line << std::endl;
		return ;
	}
	std::string	date(line.substr(date_start, DATE_SIZE));
	ratio_start = line.find_first_not_of(' ', ratio_start + 1);
	std::string	ratio;
	try
	{
		ratio = line.substr(ratio_start);
	}
	catch (std::out_of_range const& e)
	{
		std::cerr << "Error: bad input => " << line << std::endl;
		return ;
	}
	_computeLine(date, ratio);
}

void	_computeLine(std::string const& date, std::string const& ratio)
{
	if (!checkDate(date))
	{
		std::cerr << "Error: bad day format => " << date << std::endl;
		return ;
	}
	std::string	subdate = date.substr(0, 4) + date.substr(5, 2) + date.substr(8, 2);
	float	price = BitcoinExchange::getPriceOfDay(atoi(subdate.c_str()));
	float	fratio;
	try
	{
		fratio = to_float(ratio);
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: not a number => " << ratio << std::endl;
		return ;
	}
	if (fratio < 0.f)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return ;
	}
	if (fratio > 1000.f)
	{
		std::cerr << "Error: too large a number." << std::endl;
		return ;
	}
	std::cout << date << " => " << fratio  << " = " << price * fratio << std::endl;
}
