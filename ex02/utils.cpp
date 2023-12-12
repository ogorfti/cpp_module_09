/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:25:09 by ogorfti           #+#    #+#             */
/*   Updated: 2023/12/12 17:29:31 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void printPairs(vecP _pairs)
{
	for (size_t i = 0; i < _pairs.size(); i++)
	{
		std::cout << "[ ";
		for (size_t j = 0; j < _pairs[i].first.size(); j++)
		{
			std::cout << _pairs[i].first[j] << " ";
		}
		std::cout << " : ";
		for (size_t j = 0; j < _pairs[i].second.size(); j++)
		{
		std::cout << _pairs[i].second[j] << " ";
		}
		std::cout << " ]" << std::endl;
	}
}

void printPair(const std::pair<std::vector<int>, std::vector<int> >& pair)
{
	std::cout << "[ ";
	for (std::vector<int>::const_iterator it = pair.first.begin(); it != pair.first.end(); ++it) {
		std::cout << *it << " ";
	}
	// std::cout << std::endl;

	std::cout << ": ";
	for (std::vector<int>::const_iterator it = pair.second.begin(); it != pair.second.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << " ]" << std::endl;
	std::cout << std::endl;
}

void printVector(const std::vector<int>& vec)
{
    for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it)
	{
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void printVectorOfVectors(const std::vector<std::vector<int> >& vec)
{
	std::cout << "\n---===VoV===---\n";
    for (size_t i = 0; i < vec.size(); i++) {
        for (size_t j = 0; j < vec[i].size(); j++) {
            std::cout << vec[i][j] << " ";
        }
        std::cout << std::endl;
	// std::cout << "**\n";
    }
	std::cout << "---======---\n\n";
}

