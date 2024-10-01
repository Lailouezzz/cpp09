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
		RPN(RPN const& o);
		~RPN();

		RPN		&operator=(RPN const& o);
		void	operator<<(char const& c);
		void	sub();
		void	add();
		void	div();
		void	mul();
		static void (RPN::*const operatorTable[6])(void);
		std::stack<int>	m_stack;
	
	public:
		class RPNException : public std::exception
		{
		public:
			RPNException(std::string const& message);
			virtual ~RPNException() throw();

			virtual const char* what() const throw();
		private:
			std::string	m_message;
		};
		
};

#endif
