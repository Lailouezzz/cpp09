#ifndef  PMERGEME_HPP
# define PMERGEME_HPP

# include <deque>
# include <vector>

template<class T>
void	_sortPairs(T& container)
{
	if (container.size() < 2) return ;

	for (std::size_t k = 0; k + 1 < container.size(); k += 2)
		if (container[k] > container[k + 1])
			std::swap(container[k], container[k + 1]);
}

template<class T>
void	fjmi(T& container)
{
	// std::deque<int>	container;
	_sortPairs(container);
}

#endif
