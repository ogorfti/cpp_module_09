/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:25:09 by ogorfti           #+#    #+#             */
/*   Updated: 2023/12/19 11:58:35 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void printVectorOfVectors(const std::vector<std::vector<int> >& vec, std::string str)
{
	std::cout << str;

    for (size_t i = 0; i < vec.size(); i++)
    {
        for (size_t j = 0; j < vec[i].size(); j++)
        {
            std::cout << vec[i][j] << " ";
        }
    }
    std::cout << std::endl;
}

void printDeqOfDeqs(const std::deque<std::deque<int> >& vec, std::string str)
{
	std::cout << str;

    for (size_t i = 0; i < vec.size(); i++)
    {
        for (size_t j = 0; j < vec[i].size(); j++)
        {
            std::cout << vec[i][j] << " ";
        }
    }
    std::cout << std::endl;
}
