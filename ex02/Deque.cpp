/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Deque.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:15:28 by ogorfti           #+#    #+#             */
/*   Updated: 2023/12/19 11:59:08 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

bool compareDeq(const std::deque<int>& lhs, const std::deque<int>& rhs) 
{
	return lhs.back() < rhs.back();
}

std::deque<int> jacobstallDeq(int n)
{
	std::deque<int> v;
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

std::deque<int> mergeDeq(std::deque<int>& f, std::deque<int>& s)
{
	std::deque<int> merged;

	merged.insert(merged.end(), f.begin(), f.end());
	merged.insert(merged.end(), s.begin(), s.end());

	return merged;
}

void PmergeMe::recursionDeq()
{

	std::deque<int> remain;

	if (_v_deq.size() % 2 != 0)
	{
		remain = _v_deq.back();
		_v_deq.pop_back();
	}
	deqD hold;
	for (deqD::iterator it = _v_deq.begin(); it != _v_deq.end(); it +=2)
	{
		std::deque<int> f = *it;
		std::deque<int> s = *(it + 1);

		if (f.back() > s.back())
			std::swap(f, s);

		hold.push_back(mergeDeq(f, s));
	}
	_v_deq = hold;
	
	if (_v_deq.size() > 1)
		recursionDeq();
	
	std::deque<std::deque<int> > mainchain;
	std::deque<std::deque<int> > pend;

	for (size_t i = 0; i < _v_deq.size(); i++)
	{
		std::deque<int> vec = _v_deq[i];
		std::deque<int> f,s;

		f.insert(f.end(), vec.begin(), vec.begin() + (vec.size() / 2));
		s.insert(s.end(), vec.begin() + (vec.size() / 2), vec.end());
	
		pend.push_back(f);
		mainchain.push_back(s);

	}

	if (remain.size())
	{
		pend.push_back(remain);
	}

	std::deque<int> v = jacobstallDeq(pend.size());
	size_t prev = 0;
	int kk = 0;

	for (size_t i = 2; i < v.size(); i++)
	{
		size_t index = v[i];
		while (index > prev)
		{
			if (index - 1 < pend.size())
			{
				std::deque<int> x = pend[index - 1];
				
				std::deque<std::deque<int> >::iterator it;
				if (index - 1 == 0)
				{
					mainchain.insert(mainchain.begin(), x);
					kk++;
				}
				else
				{
					it = std::lower_bound(mainchain.begin(), mainchain.begin() + index + kk - 1, x, compareDeq);
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
	_v_deq = mainchain;
}
