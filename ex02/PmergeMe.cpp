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
	done = false;
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

void PmergeMe::backToMonkey()
{
	for (size_t i = 0; i < _pairs.size(); i++)
	{
		std::vector<int> tmp;
		for (std::vector<int>::iterator it = _pairs[i].first.begin(); it != _pairs[i].first.end(); it++)
		{
			tmp.push_back(*it);
		}
		for (std::vector<int>::iterator it = _pairs[i].second.begin(); it != _pairs[i].second.end(); it++)
		{
			tmp.push_back(*it);
		}
		_collection.push_back(tmp);
	}
}

std::vector<int> pairToVec(const onePair& pair)
{
    std::vector<int> vec;

    vec.insert(vec.end(), pair.first.begin(), pair.first.end());
    vec.insert(vec.end(), pair.second.begin(), pair.second.end());

    return vec;
}

struct 	Compare
{
    bool operator()(const std::vector<int>& lhs, const std::vector<int>& rhs) const
	{
        return lhs.back() < rhs.back();
    }
};

void PmergeMe::recursion()
{
	onePair tmp;

	if (_pairs.size() > 1)
	{
		vecP mergedPairs;

		for (size_t i = 0; i < _pairs.size(); i+=2)
		{
			if (i + 1 < _pairs.size())
			{
				printPair(_pairs[i]);
				printPair(_pairs[i+1]);
				std::cout << "--------------\n";
				if (_pairs[i].second.back() > _pairs[i+1].second.back())
					std::swap(_pairs[i], _pairs[i+1]);
				mergedPairs.push_back(mergePairs(_pairs[i], _pairs[i+1]));
			}
			else
				tmp = _pairs[i];
		}
		_pairs = mergedPairs;
		printPairs(_pairs);
		recursion();
	}
	else if (!done)
	{
		done = true;
		backToMonkey();
		std::cout << "DONE FORWARD!!" << '\n';
	}
	
	std::vector<std::vector<int> > pend;
	std::vector<std::vector<int> > mainchain;
	for (size_t i = 0; i < _collection.size(); i++)
	{
		std::vector<int> oneV = _collection[i];


		std::vector<int> f,s;

		for (size_t i = 0; i < oneV.size() / 2; i++)
		{
			f.push_back(oneV[i]);
		}
		for (size_t i = oneV.size() / 2; i < oneV.size(); i++)
		{
			s.push_back(oneV[i]);
		}
		pend.push_back(f);
		// pend.push_back(s);
		mainchain.push_back(s);
	}
	if (!tmp.first.empty())
	{
		std::vector<int> here = pairToVec(tmp);
		std::vector<int> f,s;

		for (size_t i = 0; i < here.size() / 2; i++)
		{
			f.push_back(here[i]);
		}
		for (size_t i = here.size() / 2; i < here.size(); i++)
		{
			s.push_back(here[i]);
		}
		pend.push_back(f);
		pend.push_back(s);

		// std::cout << "here\n";
		// pend.push_back(pairToVec(tmp));
	}

	for (size_t i = 0; i < pend.size(); i++)
	{
		std::vector<int> x = pend[i];

		Compare comparator;
		std::vector<std::vector<int> >::iterator it = std::lower_bound(mainchain.begin(), mainchain.end(), x, comparator);

		mainchain.insert(it, x);
	}
	_collection = mainchain;
	std::cout << "PEND!!" << '\n';
	printPair(tmp);
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
	for (std::vector<std::vector<int> >::iterator it = _collection.begin(); it != _collection.end(); it++)
	{
		std::vector<int> tmp = *it;

		for (std::vector<int>::iterator it = tmp.begin(); it != tmp.end(); it++)
		{
			std::cout << *it << '\n';
		}
		std::cout << "***\n";
	}

	
	// printPairs(_pairs);
	// if (!this->remain.empty())
	// 	std::cout << "remain: "<< remain.back() << '\n';
}
