#ifndef  PMERGEME_HPP
# define PMERGEME_HPP

# include <deque>
# include <vector>

template<class T>
void	_sortPairs(T& container, std::size_t unit)
{
	if (container.size() < (2ul << unit)) return ;

	for (std::size_t k = 0; k + (2 << unit) - 1 < container.size(); k += (2 << unit))
		if (container[k + (1 << unit) - 1] > container[k + (2 << unit) - 1])
			std::swap_ranges(container.begin()+k, container.begin()+k+(1 << unit), container.begin()+k+(1 << unit));
}

template<class T>
T	_mainChain(T& container, std::size_t unit)
{
	T	main_chain;

	for (std::size_t k = 0; k + (2 << unit) - 1 < container.size(); k += (2 << unit))
		main_chain.insert(main_chain.end(), container.begin()+k+(1 << unit), container.begin()+k+(2 << unit));
	return (main_chain);
}

template<class T>
T	_pendingChain(T& container, std::size_t unit)
{
	T	pending_chain;

	for (std::size_t k = 0; k + (2 << unit) - 1 < container.size(); k += (2 << unit))
		pending_chain.insert(pending_chain.end(), container.begin()+k, container.begin()+k+(1 << unit));
	// Leave extra elements
	pending_chain.insert(pending_chain.end(), container.begin()+((2 << unit)*(container.size()/(2 << unit))), container.end());
	return (pending_chain);
}

template<class T>
void	_binaryInsertion(T& main_chain, typename T::const_iterator itbeg, typename T::const_iterator itend, std::size_t unit)
{
	int	b = *(itend-1);
	std::size_t	start = 0;
	std::size_t	end = (main_chain.size() / (1 << unit));

	while (start != end)
	{
		std::size_t	middle = (start + end) / 2;

		if (b > main_chain[middle*(1 << unit)+(1 << unit)-1])
			start = middle + 1;
		else
			end = middle;
	}
	main_chain.insert(main_chain.begin()+start*(1 << unit), itbeg, itend);
}

template<class T>
void	_insertPairs(T& container, T const& pending_chain, std::size_t unit)
{
	for(std::size_t k = 0; k + (1 << unit) - 1 < pending_chain.size(); k += (1 << unit))
		_binaryInsertion<T>(container, pending_chain.begin()+k, pending_chain.begin()+k+(1 << unit), unit);
	// Insert remaining elements
	container.insert(container.end(), pending_chain.begin()+((1 << unit)*(pending_chain.size()/(1 << unit))), pending_chain.end());
}

template<class T>
void	fjmi(T& container, std::size_t unit=0)
{
	if (container.size() / (1 << unit) <= 1) return ;
	_sortPairs(container, unit);
	fjmi<T>(container, unit + 1);

	// Binary insertion
	T	pending_chain(_pendingChain<T>(container, unit));
	container = _mainChain<T>(container, unit);
	_insertPairs<T>(container, pending_chain, unit);
}

#endif
