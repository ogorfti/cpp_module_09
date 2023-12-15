/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:40:59 by ogorfti           #+#    #+#             */
/*   Updated: 2023/12/15 19:52:08 by ogorfti          ###   ########.fr       */
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

std::vector<int> jacobstall(int n)
{
	std::vector<int> v;
	v.push_back(0);
	v.push_back(1);
	int tmp;


	int i = 2;
	tmp = 0;
	while (tmp < n)
	{
		tmp = v[i - 1] + 2 * v[i - 2];
		v.push_back(tmp);
		i++;
	}
	return v;
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
	/*
	jacob 0 2 1 3

	
	1 2. 5 6. 8 9. 7 10
	
	main: 2 6 9 10
	pend: 1 5 8 7

	arr = 0 1 2 3
	  = 1 2 3 4
	  = 1 2 3 5
	
	main: 1 2 6 9 10
	pend: [1] 5 8 7
	
	
	
	main: 1 2 6 8 9 10
	pend: [1] 5 [8] 7
	*/


	std::vector <int> arr;
	for (size_t i = 0; i < pend.size(); i++)
	{
		arr.push_back(i);
		// std::cout << "jaa------> :" << arr[i] << '\n';
	}
	
	std::vector<int> v = jacobstall(pend.size());
	size_t prev = 0;
	for (size_t i = 2; i < v.size(); i++)
	{
		size_t index = v[i];
		while (index > prev)
		{
			// std::cout << index << '\n';
			// std::vector< std::vector<int> > copy = mainchain;
	
			if (index - 1 < pend.size())
			{
				std::vector<int> x = pend[index - 1];
				
				std::vector<std::vector<int> >::iterator it;
				// std::cout << "jaa------> :" << arr[index - 1] << '\n';
				if (index - 1 == 0)
					mainchain.insert(mainchain.begin(), x);
				else
				{
					it = std::lower_bound(mainchain.begin(), mainchain.end(), x, compare);
					mainchain.insert(it, x);
				}
				/*
					update the arr
				*/
				// for (size_t i = 0; i < copy.size(); i++)
				// {
				// 	std::vector<int> vec1 = mainchain[i];
				// 	std::vector<int> vec2 = copy[i];

				// 	if (vec1.back() != vec2.back())
				// 	{
				// 		for (size_t j = 0; j < arr.size(); j++)
				// 		{
				// 			arr[j] += 1;
				// 		}
				// 		break;
				// 	}
				// }
				// for (size_t i = 0; i < arr.size(); i++)
				// {
				// 	std::cout << "jaa------> :" << arr[i] << '\n';
				// }
				
			}		
			index--;
		}
		prev = v[i];
	}


	_collection = mainchain;
	printVectorOfVectors(_collection);
	std::cout << "REVERSE!!" << '\n';
}

//11 1 4 0 21
/* 3 2
1- generate sequence untill J(n) >= pend.size() return vec <int> (1 3 5 11 ...)
2- the first element in the pend should always push  before comaparaison
3- generate index based on the vec and the pend size
*/
void PmergeMe::runFJMI()
{
	std::cout << "<---- FJMI ---->" << std::endl;

	checkInput();
	recursion(1);

	std::cout << "count : " << count << '\n';
}
