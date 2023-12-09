/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:40:59 by ogorfti           #+#    #+#             */
/*   Updated: 2023/12/09 17:31:49 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

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

bool comparePairs(const onePair& p1, const onePair& p2)
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
		if (_v[i] > _v[i + 1])
			std::swap(_v[i], _v[i + 1]);
		std::vector<int> f(1, _v[i]);
		std::vector<int> s(1, _v[i + 1]);
		
		_pairs.push_back(std::make_pair(f, s));
	}
	// std::sort(_pairs.begin(), _pairs.end(), comparePairs);
}

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

void printPair(const std::pair<std::vector<int>, std::vector<int> >& pair) {
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

onePair mergePairs(onePair& p1, onePair& p2)
{
	std::vector<int> f = p1.first;
	std::vector<int> s = p2.first;

	f.insert(f.end(), p1.second.begin(), p1.second.end());
	s.insert(s.end(), p2.second.begin(), p2.second.end());

	return std::make_pair(f, s);
}

void PmergeMe::recursion()
{
	if (_pairs.size() > 1)
	{
		vecP mergedPairs;

		std::sort(_pairs.begin(), _pairs.end(), comparePairs);
		for (size_t i = 0; i < _pairs.size(); i+=2)
		{
			if (i + 1 < _pairs.size())
			{
				printPair(_pairs[i]);
				printPair(_pairs[i+1]);
				std::cout << "--------------\n";
				mergedPairs.push_back(mergePairs(_pairs[i], _pairs[i+1]));
			}
			else
			{
				// std::cout << "PEND!!" << '\n'; 
				// std::cout << "--- PEND START ---" << '\n'; 
				// _test = _pairs[i];
				_test.push_back(_pairs[i]);
				// printPair(_test);
				// std::cout << "--- PEND END ---" << '\n'; 
			}
		}
		_pairs = mergedPairs;
		printPairs(_pairs);
		recursion();
	}
	
	std::cout << "reverse recursion start" << std::endl;
	// std::cout << "PEND!!" << '\n';
	// printPairs(_test);
	// if (_test.first)
		
}

//11 1 4 0 21 10 9 5 7 26 23 2
void PmergeMe::runFJMI()
{
	std::cout << "<---- FJMI ---->" << std::endl;

	checkInput();
	initPairs();
	recursion();
	// std::cout << "size: " << _v.size() << '\n';
	// for (std::vector<int>::iterator it = _v.begin(); it != _v.end(); it++)
	// {
	// 	std::cout << *it << '\n';
	// }

	
	// printPairs(_pairs);
	// if (!this->remain.empty())
	// 	std::cout << "remain: "<< remain.back() << '\n';
}
