/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:40:59 by ogorfti           #+#    #+#             */
/*   Updated: 2023/12/16 15:58:59 by ogorfti          ###   ########.fr       */
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
	std::vector<onePair> hold;

	for (size_t i = 0; i < _collection.size(); i++)
	{
		std::vector<int> vec = _collection[i];
		std::vector<int> f,s;

		f.insert(f.end(), vec.begin(), vec.begin() + (vec.size() / 2));
		s.insert(s.end(), vec.begin() + (vec.size() / 2), vec.end());
	
		pend.push_back(f);
		mainchain.push_back(s);

		onePair test(f, s);

		hold.push_back(test);
		// onePair get;
		// get.first = 
		// get.first.insert(f.begin, f.end);
	}
	if (!tmp.empty())
	{
		std::cout << "tmp : ";
		printVector(tmp);
		pend.push_back(tmp);
	}

	/*
		vec < pair <pend, main> >
		vec < pair <vec, vec> >
		find his pair vec
		and find it in mainchain and get the index
	*/


	std::vector<int> v = jacobstall(pend.size());
	size_t prev = 0;
	// 0 1 1 3 5
	// [] []
		int kk = 0;
	for (size_t i = 2; i < v.size(); i++)
	{
		size_t index = v[i];
		while (index > prev)
		{
			if (index - 1 < pend.size())
			{
				std::vector<int> x = pend[index - 1];
				
				std::vector<std::vector<int> >::iterator it;
				if (index - 1 == 0)
				{
					mainchain.insert(mainchain.begin(), x);
					// std::cout << "9999999999999999"  << kk << '\n';
					kk++;
				}
				else
				{
					// std::vector<int> tmp2;
					// for (std::vector< onePair >::iterator it = hold.begin(); it != hold.end(); it++)
					// {
					// 	std::vector<int> tmp1 = it->first;
					// 	if (tmp1.back() == x.back())
					// 	{
					// 		std::cout << "Morrrras\n"; 
					// 		tmp2 = it->second;
					// 	}
					// }
					// std::vector< std::vector<int> >::iterator ite = mainchain.begin();
					// for (; ite != mainchain.end(); ite++)
					// {
					// 	std::vector<int> vec = *ite;
					// 	if (tmp2.empty()) {
					// 		std::cout << "hell\n";
					// 		ite = mainchain.end();
					// 		break;
					// 	}
					// 	if (vec.back() == tmp2.back())
					// 		break;
					// }
					// 	std::cout << "########\n";
					// if (index+kk-1 >= mainchain.size() - 1)
					// 	it = std::lower_bound(mainchain.begin(), mainchain.end(), x, compare);
					// else
					it = std::lower_bound(mainchain.begin(), mainchain.begin() + index + kk - 1, x, compare);

					// std::cout << "main: " << mainchain.size() << "  gggg: " << kk << '\n';
					mainchain.insert(it, x);
					kk++;
				}			
			index--;
			}
			else
				index = pend.size();
		}
		prev = v[i];
	}


	_collection = mainchain;
	printVectorOfVectors(_collection);
	std::cout << "REVERSE!!" << '\n';
}

//11 1 4 0 21
/* 0 1 3 5
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
