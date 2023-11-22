/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:49:50 by ogorfti           #+#    #+#             */
/*   Updated: 2023/11/22 13:15:24 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int ac, char **av)
{
	if (ac == 2)
	{
		try
		{
			std::string	str = av[1];
			RPN	rpn(str);
			rpn.runRPN();
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	else
		std::cerr << "Error: wrong number of arguments\n";
	return 0;
}
