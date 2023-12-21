/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:40:59 by ogorfti           #+#    #+#             */
/*   Updated: 2023/12/21 10:04:51 by ogorfti          ###   ########.fr       */
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
	{
		_av = other._av;
		_v = other._v;
		_v_deq = other._v_deq;
		remain = other.remain;
		remain_deq = other.remain_deq;	
	}
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

		std::vector<int> tmp1;
		std::deque<int> tmp2;
		
		tmp1.push_back(std::atoi(_av[i]));
		tmp2.push_back(std::atoi(_av[i]));
		_v.push_back(tmp1);
		_v_deq.push_back(tmp2);
		i++;
	}
}

bool compare(const std::vector<int>& lhs, const std::vector<int>& rhs) 
{
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

std::vector<int> mergeVec(std::vector<int>& f, std::vector<int>& s)
{
	std::vector<int> merged;

	merged.insert(merged.end(), f.begin(), f.end());
	merged.insert(merged.end(), s.begin(), s.end());

	return merged;
}

void PmergeMe::recursion()
{

	std::vector<int> remain;

	if (_v.size() % 2 != 0)
	{
		remain = _v.back();
		_v.pop_back();
	}
	vecV hold;
	for (vecV::iterator it = _v.begin(); it != _v.end(); it +=2)
	{
		std::vector<int> f = *it;
		std::vector<int> s = *(it + 1);

		if (f.back() > s.back())
			std::swap(f, s);

		hold.push_back(mergeVec(f, s));
	}
	_v = hold;
	
	if (_v.size() > 1)
		recursion();
	
	std::vector<std::vector<int> > mainchain;
	std::vector<std::vector<int> > pend;

	for (size_t i = 0; i < _v.size(); i++)
	{
		std::vector<int> vec = _v[i];
		std::vector<int> f,s;

		f.insert(f.end(), vec.begin(), vec.begin() + (vec.size() / 2));
		s.insert(s.end(), vec.begin() + (vec.size() / 2), vec.end());
	
		pend.push_back(f);
		mainchain.push_back(s);

	}

	if (remain.size())
	{
		pend.push_back(remain);
	}

	std::vector<int> v = jacobstall(pend.size());
	size_t prev = 0;
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
					kk++;
				}
				else
				{
					it = std::lower_bound(mainchain.begin(), mainchain.begin() + index + kk - 1, x, compare);
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
	_v = mainchain;
}

void PmergeMe::runFJMI()
{
	checkInput();
	
	printVectorOfVectors(_v, "\nBefore: ");
	clock_t start = clock(); 
	recursion();
	printVectorOfVectors(_v, "After: ");
	std::cout << "\nTime to process a range of " << _v.size() << " elements with std::vector : " << std::fixed << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " us\n";
	
	start = clock(); 
	recursionDeq();
	std::cout << "Time to process a range of " << _v_deq.size() << " elements with std::deque : " << std::fixed << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " us\n\n";
}
