#ifndef  PMERGEME_HPP
# define PMERGEME_HPP

# include <deque>
# include <vector>

template<class T>
void	_sortPairs(T& container, std::size_t unit)
{
	if (container.size() < unit * 2) return ;

	for (std::size_t k = 0; k + unit * 2 - 1 < container.size(); k += unit * 2)
		if (container[k + unit - 1] > container[k + unit * 2 - 1])
			std::swap_ranges(container.begin()+k, container.begin()+k+unit, container.begin()+k+unit);
}

template<class T>
T	_mainChain(T& container, std::size_t unit)
{
	// if (container.size() < unit * 2) return ;
	T	main_chain;

	for (std::size_t k = 0; k + unit * 2 - 1 < container.size(); k += unit * 2)
		main_chain.insert(main_chain.end(), container.begin()+k+unit, container.begin()+k+unit*2);
	return (main_chain);
}

template<class T>
T	_pendingChain(T& container, std::size_t unit)
{
	// if (container.size() < unit * 2) return ;
	T	pending_chain;

	for (std::size_t k = 0; k + unit * 2 - 1 < container.size(); k += unit * 2)
		pending_chain.insert(pending_chain.end(), container.begin()+k, container.begin()+k+unit);
	// Leave extra elements
	pending_chain.insert(pending_chain.end(), container.begin()+(unit*2*(container.size()/(unit*2))), container.end());
	return (pending_chain);
}

template<class T>
void	_binaryInsertion(T& main_chain, typename T::const_iterator itbeg, typename T::const_iterator itend, std::size_t unit)
{
	int	b = *(itend-1);
	std::size_t	start = 0;
	std::size_t	end = (main_chain.size() / unit);

	while (start != end)
	{
		std::size_t	middle = (start + end) / 2;

		if (b > main_chain[middle*unit+unit-1])
			start = middle + 1;
		else
			end = middle;
	}
	main_chain.insert(main_chain.begin()+start*unit, itbeg, itend);
}

template<class T>
void	_insertPairs(T& container, T const& pending_chain, std::size_t unit)
{
	for(std::size_t k = 0; k + unit - 1 < pending_chain.size(); k += unit)
		_binaryInsertion<T>(container, pending_chain.begin()+k, pending_chain.begin()+k+unit, unit);
	// Insert remaining elements
	container.insert(container.end(), pending_chain.begin()+(unit*(pending_chain.size()/unit)), pending_chain.end());
}

template<class T>
void	fjmi(T& container, std::size_t unit=1)
{
	if (container.size() / unit <= 1) return ;
	_sortPairs(container, unit);
	fjmi<T>(container, unit * 2);

	// Binary insertion
	T	pending_chain(_pendingChain<T>(container, unit));
	container = _mainChain<T>(container, unit);
	_insertPairs<T>(container, pending_chain, unit);
}

#endif
