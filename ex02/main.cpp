#include <iostream>

#include "PmergeMe.hpp"


int main(void)
{
	std::deque<int>	container;

	container.push_back(1);
	container.push_back(7);
	container.push_back(6);
	container.push_back(4);
	container.push_back(5);
	container.push_back(2);
	container.push_back(3);

	std::deque<int>::const_iterator	itr = container.begin();
	while (itr != container.end())
	{
		std::cout << *itr << std::endl;
		++itr;
	}
	fjmi<std::deque<int> >(container);
	itr = container.begin();
	std::cout << "----" << std::endl;
	while (itr != container.end())
	{
		std::cout << *itr << std::endl;
		++itr;
	}
}
