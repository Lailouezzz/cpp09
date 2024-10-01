#include <cstdlib>
#include <iostream>
#include <sstream>
#include <time.h>

#include "PmergeMe.hpp"

int to_int(std::string const& ratio)
{
	std::stringstream	ss;
	int				r;

	ss << ratio.substr(0, ratio.find_last_not_of(' ') + (ratio.find_last_not_of(' ') != std::string::npos ? 1 : 0));
	if (!(ss >> r) || !ss.eof())
		throw std::exception();
	return (r);
}

#define NUM_DISPLAYED_ITEMS (5)

template<class T>
void	printTab(T const& container)
{
	typename T::const_iterator itr = container.begin();
	for (int k = 0; k < NUM_DISPLAYED_ITEMS && itr != container.end(); ++k, ++itr)
		std::cout << " " << *itr;
	if (container.size() > NUM_DISPLAYED_ITEMS)
	{
		std::cout << " [...]";
	}
}

time_t	getCurTime()
{
	struct timespec	ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (((time_t)ts.tv_sec * 1000000000) + ts.tv_nsec);
}

void usage(const char *pn)
{
	std::cout << "Usage: " << pn << " [numbers]" << std::endl;
	exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
	if (argc == 1)
		usage(*argv);
	std::deque<int>	deque;
	std::vector<int>	vector;
	for (int k = 1; k < argc; ++k)
	{
		int	t;
		try
		{
			t = to_int(argv[k]);
		}
		catch (std::exception const& e)
		{
			std::cerr << *argv << ": " << argv[k] << " is not an integer" << std::endl;
			return (EXIT_FAILURE);
		}
		deque.push_back(t);
		vector.push_back(t);
	}
	std::cout << "Before :";
	printTab<std::vector<int> >(vector);
	std::cout << std::endl;
	time_t	dequeTime = getCurTime();
	fjmi<std::deque<int> >(deque);
	dequeTime = getCurTime() - dequeTime;
	time_t	vectorTime = getCurTime();
	fjmi<std::vector<int> >(vector);
	vectorTime = getCurTime() - vectorTime;
	std::cout << "After :";
	printTab<std::vector<int> >(vector);
	std::cout << std::endl;
	std::cout << "Time to process a range of " << vector.size() << " elements with std::vector : " << (double)vectorTime/1000 << " us" << std::endl;
	std::cout << "Time to process a range of " << deque.size() << " elements with std::deque : " << (double)dequeTime/1000 << " us" << std::endl;
	return (EXIT_SUCCESS);
}
