#include "RPN.hpp"

#include <iostream>

RPN::RPNException::RPNException(std::string const& message) :
	std::exception(),
	m_message(message)
{}

RPN::RPNException::~RPNException() throw()
{}

const char *RPN::RPNException::what() const throw()
{
	return (m_message.c_str());
}

void (RPN::*const RPN::operatorTable[6])(void) =
{
/* ASCII: 42 => '*' */
&RPN::mul,
/* ASCII: 43 => '+' */
&RPN::add,
/* ASCII: 44 => ',' */
NULL,
/* ASCII: 45 => '-' */
&RPN::sub,
/* ASCII: 46 => '.' */
NULL,
/* ASCII: 47 => '/' */
&RPN::div,
};

int	RPN::calculate(std::string const& expr)
{
	RPN	rpn;

	for (std::string::const_iterator itr = expr.begin(); itr != expr.end(); ++itr)
		rpn << *itr;
	if (rpn.m_stack.size() != 1)
		throw RPN::RPNException("stack size != 1");
	return (rpn.m_stack.top());
}

RPN::RPN() :
	m_stack()
{
}

RPN::RPN(RPN const& o)
{
	*this = o;
}

RPN::~RPN()
{
}

RPN		&RPN::operator=(RPN const& o)
{
	if (this == &o)
		return (*this);
	this->m_stack = o.m_stack;
	return (*this);
}

void	RPN::operator<<(char const& c)
{
	if (c == ' ')
		return ;
	if (std::isdigit(c))
	{
		m_stack.push(c - '0');
		return ;
	}
	/* MAGIC */
	int	id = c - 42 /* '*' */;
	if (id < 0 || id >= static_cast<int>(sizeof(operatorTable) / sizeof(*operatorTable)) || operatorTable[id] == NULL)
		throw RPN::RPNException("unknown operator");
	if (m_stack.size() < 2)
		throw RPN::RPNException("stack size < 2");
	(this->*operatorTable[id])();
}

void	RPN::sub()
{
	int	a = m_stack.top();
	m_stack.pop();
	m_stack.top() -= a;
}

void	RPN::add()
{
	int	a = m_stack.top();
	m_stack.pop();
	m_stack.top() += a;
}

void	RPN::div()
{
	int	a = m_stack.top();
	if (a == 0)
		throw RPN::RPNException("division by zero");
	m_stack.pop();
	m_stack.top() /= a;
}

void	RPN::mul()
{
	int	a = m_stack.top();
	m_stack.pop();
	m_stack.top() *= a;
}
