#ifndef  RPN_HPP
# define RPN_HPP

# include <string>
# include <stack>

class RPN
{
	public:
		static int	calculate(std::string const& expr);

	private:
		RPN();
		~RPN();

		void	operator<<(char const& c);
		void	sub();
		void	add();
		void	div();
		void	mul();
		static void (RPN::*const operatorTable[6])(void);
		std::stack<int>	m_stack;
};

#endif