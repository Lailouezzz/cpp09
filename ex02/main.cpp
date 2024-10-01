#include <cstdlib>
#include <iostream>
#include <sstream>

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
}

int main(int argc, char **argv)
{
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
	fjmi<std::deque<int> >(deque);
	fjmi<std::vector<int> >(vector);
	std::cout << "After :";
	printTab<std::vector<int> >(vector);
	std::cout << std::endl;
	
	return (EXIT_SUCCESS);
}
