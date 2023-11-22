/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:01:31 by ogorfti           #+#    #+#             */
/*   Updated: 2023/11/22 13:08:20 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>
#include <stack>

class RPN
{
	private:
		std::stack<int> _stack;
		std::string _str;
	public:
		RPN();
		RPN(const RPN&);
		RPN(const std::string&);
		RPN& operator=(const RPN&);
		~RPN();

		bool isOperands(char c);
		void calculateRPN(char c);
		void runRPN();
};
