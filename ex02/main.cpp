/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:49:34 by ogorfti           #+#    #+#             */
/*   Updated: 2023/11/27 11:28:40 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char **av)
{
	if (ac > 1)
	{
		try
		{
			// std::string str = av[1];
			PmergeMe p(av);
			p.runFJMI();
			// int i = 1;
			// while (av[i])
			// {
			// 	std::string str = av[i];
			// 	if (checkDigit(str))
			// 		throw std::invalid_argument("Error");
			// 	i++;
			// }
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	else
		std::cout << "Usage: ./PmergeMe [Numbers]" << std::endl;
	return (0);
}
