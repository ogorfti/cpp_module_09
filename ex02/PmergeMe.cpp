/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:40:59 by ogorfti           #+#    #+#             */
/*   Updated: 2023/12/08 15:50:42 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <algorithm>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(char **av)
{
	_av = av;
}

PmergeMe::PmergeMe(const PmergeMe& other)
{
	*this = other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
		_av = other._av;
	return (*this);
}

PmergeMe::~PmergeMe() {}


int checkDigit(const std::string& str)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		if (!std::isdigit(str[i]))
			return (1);
	}
	return (0);
}

void PmergeMe::checkInput()
{
	int i = 1;
	while (_av[i])
	{
		std::string str = _av[i];
		if (checkDigit(str))
			throw std::invalid_argument("Error");

		this->_v.push_back(std::atoi(_av[i]));
		i++;
	}
}

typedef std::pair<std::vector<int>, std::vector<int> > test;
bool comparePairs(const test& p1, const test& p2)
{
	return p1.second.back() < p2.second.back();
}

void PmergeMe::initPairs()
{
	if (_v.size() % 2 != 0)
	{
		remain.push_back(_v.back());
		_v.pop_back();
	}
	for (size_t i = 0; i < _v.size(); i+=2)
	{
		std::vector<int> f(1, _v[i]);
		std::vector<int> s(1, _v[i + 1]);
		
		_pairs.push_back(std::make_pair(f, s));
	}
	// std::sort(_pairs.begin(), _pairs.end(), comparePairs);
}

test mergePairs(test& p1, test& p2)
{
	std::vector<int> f = p1.first;

	f.insert(f.end(), p2.first.begin(), p2.first.end());
	
	std::vector<int> s = p1.second;

	f.insert(f.end(), p2.second.begin(), p2.second.end());

	return std::make_pair(f, s);
}

void PmergeMe::recursion()
{
	if (_pairs.size() > 1)
	{
		std::vector<test> mergedPairs;

		for (size_t i = 0; i < _pairs.size(); i+=2)
		{
			if (i + 1 < _pairs.size())
			{
				mergedPairs.push_back(mergePairs(_pairs[i], _pairs[i+1]));
			}
			else
				std::cout << "pend" << '\n'; 
		}
		recursion();
	}
	else
		return;
}

void PmergeMe::runFJMI()
{
	std::cout << "<---- FJMI ---->" << std::endl;

	checkInput();
	initPairs();
	// recursion();
	std::cout << "size: " << _v.size() << '\n';
	for (std::vector<int>::iterator it = _v.begin(); it != _v.end(); it++)
	{
		std::cout << *it << '\n';
	}

	for (size_t i = 0; i < _pairs.size(); i++)
	{
    	std::cout << "[";
    	for (size_t j = 0; j < _pairs[i].first.size(); j++)
		{
        	std::cout << _pairs[i].first[j];
    	}
    	std::cout << ": ";
    	for (size_t j = 0; j < _pairs[i].second.size(); j++)
		{
        std::cout << _pairs[i].second[j];
    	}
   		std::cout << "]" << std::endl;
	}
	if (!this->remain.empty())
		std::cout << "remain: "<< remain.back() << '\n';
	// if (_v.size() % 2 != 0)
	// 	remain.push_back(_v.back());
	// _v.pop_back();
	
	// recursion();
	// std::cout << "<---- R-END ---->" << std::endl;
	// for (size_t i = 0; i < _v.size(); i++)
	// {
	// 	for (size_t j = 0; j < _v[i].size(); j++)
	// 		std::cout << _v[i][j] << " ";
	// 	std::cout << std::endl;
	// }
}
