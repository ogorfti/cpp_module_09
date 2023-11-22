/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:45:46 by ogorfti           #+#    #+#             */
/*   Updated: 2023/11/22 13:16:56 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() {}

RPN& RPN::operator=(const RPN& other)
{
	if (this != &other)
	{
		_stack = other._stack;
		_str = other._str;
	}
	return *this;
}

RPN::RPN(const RPN& other)
{
	*this = other;
}

RPN::~RPN() {}

RPN::RPN(const std::string& str)
{
	_str = str;
}

bool RPN::isOperands(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
		return true;
	return false;
}

void RPN::calculateRPN(char c)
{
	if (c == '*')
	{
		int a = _stack.top();
		_stack.pop();
		int b = _stack.top();
		_stack.pop();
		_stack.push(a * b);
	}
	else if (c == '/')
	{
		int a = _stack.top();
		_stack.pop();
		int b = _stack.top();
		_stack.pop();
		if (a != 0)
			_stack.push(b / a);
		else
		    throw std::runtime_error("Infinity");
	}
	else if (c == '+')
	{
		int a = _stack.top();
		_stack.pop();
		int b = _stack.top();
		_stack.pop();
		_stack.push(a + b);
	}
	else if (c == '-')
	{
		int a = _stack.top();
		_stack.pop();
		int b = _stack.top();
		_stack.pop();
		_stack.push(b - a);
	}
	else if (c == '%')
	{
		int a = _stack.top();
		_stack.pop();
		int b = _stack.top();
		_stack.pop();
		_stack.push(b % a);
	}
}

void RPN::runRPN()
{
	std::stringstream ss(_str);
	std::string tmp;

	while (ss >> tmp)
	{
		if (std::isdigit(tmp[0]) && tmp.size() == 1)
		{
			int nbr = std::atoi(tmp.c_str());
			_stack.push(nbr);
		}
		else if (isOperands(tmp[0]) && tmp.size() == 1)
		{
			if (_stack.size() < 2)
				throw std::runtime_error("Insufficient operands on the stack");
			else
				calculateRPN(tmp[0]);
		}
		else
			throw std::runtime_error("Invalid input: \'" + tmp + "\'");
	}
	if (_stack.size() != 1)
		throw std::runtime_error("Invalid RPN expression");
	std::cout << _stack.top() << std::endl;
}
