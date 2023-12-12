/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:40:59 by ogorfti           #+#    #+#             */
/*   Updated: 2023/12/12 17:42:07 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int count = 0;

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

void PmergeMe::pairToVec(std::vector<onePair>& pairs)
{
	for (size_t i = 0; i < pairs.size(); i++)
	{
		std::vector<int> tmp;
		
		tmp.insert(tmp.end(), pairs[i].first.begin(), pairs[i].first.end());
		tmp.insert(tmp.end(), pairs[i].second.begin(), pairs[i].second.end());
		_collection.push_back(tmp);
	}
}

bool compare(const std::vector<int>& lhs, const std::vector<int>& rhs) 
{
	count++;
	return lhs.back() < rhs.back();
}

void PmergeMe::recursion(size_t index)
{
	std::vector<onePair> pairs;
	std::vector<int> tmp;

	if (index * 2 > _v.size())
		return ;
	if (_v.size() % (index * 2) != 0)
	{
		//? _v.size() % (index * 2) = index
		tmp.insert(tmp.begin(), _v.end() - index, _v.end());
		_v.erase( _v.end() - index, _v.end());
	}
	
	//* start pairing and the size of each pair is <index, index>
	for (size_t i = 0; i < _v.size(); i+=index*2)
	{
		std::vector<int> f,s;

		f.insert(f.end(), _v.begin() + i, _v.begin()+ index + i);

		s.insert(s.end(), _v.begin() + i + index, _v.begin()+ index*2 + i);

		count++;
		if (f.back() > s.back())
			std::swap(f, s);
		pairs.push_back(std::make_pair(f, s));
	}
	_v.clear();

	//* convert the vec of pairs to _v <int>
	for (size_t i = 0; i < pairs.size(); i++)
	{
		std::vector<int> f = pairs[i].first, s = pairs[i].second;

		_v.insert(_v.end(), f.begin(), f.end());
		_v.insert(_v.end(), s.begin(), s.end());
	}	

	printPairs(pairs);
	recursion(index * 2);
	if (!done)
	{
		done = true;
		std::cout << "DONE FORWARD!!" << '\n';
		pairToVec(pairs);
		// printVectorOfVectors(_collection);
	}

	std::vector<std::vector<int> > mainchain;
	std::vector<std::vector<int> > pend;

	for (size_t i = 0; i < _collection.size(); i++)
	{
		std::vector<int> vec = _collection[i];
		std::vector<int> f,s;

		f.insert(f.end(), vec.begin(), vec.begin() + (vec.size() / 2));
		s.insert(s.end(), vec.begin() + (vec.size() / 2), vec.end());
	
		pend.push_back(f);
		mainchain.push_back(s);
	}
	if (!tmp.empty())
	{
		std::cout << "tmp : ";
		printVector(tmp);
		pend.push_back(tmp);
	}

	for (size_t i = 0; i < pend.size(); i++)
	{
		std::vector<int> x = pend[i];
		
		std::vector<std::vector<int> >::iterator it = std::lower_bound(mainchain.begin(), mainchain.end(), x, compare);

		mainchain.insert(it, x);
	}
	_collection = mainchain;
	printVectorOfVectors(_collection);
	std::cout << "REVERSE!!" << '\n';
}

//11 1 4 0 21 10 9 5 7 26 23 2
void PmergeMe::runFJMI()
{
	std::cout << "<---- FJMI ---->" << std::endl;

	checkInput();
	recursion(1);

	std::cout << "count : " << count << '\n';
}
