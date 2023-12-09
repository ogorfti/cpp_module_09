/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:37:38 by ogorfti           #+#    #+#             */
/*   Updated: 2023/12/09 17:19:09 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

// #include <pa
typedef std::pair<std::vector<int>, std::vector<int> > onePair;

typedef std::vector < std::pair<std::vector<int>, std::vector<int> > > vecP;
class PmergeMe
{
	private:
		char **_av;
		std::vector <int> remain;
		std::vector <int> _v;
		// std::vector<std::vector<int> > _pairs 1;
		
		vecP _pairs;
		vecP _test;
		// std::vector<_pairs> _collection;
	public:
		PmergeMe();
		PmergeMe(const PmergeMe&);
		~PmergeMe();
		PmergeMe &operator=(const PmergeMe&);
		
		PmergeMe(char **av);
		void checkInput();
		void recursion();
		void initPairs();
		void runFJMI();
};

/*
4 6 9 2 3

[4 6] [9 2] | Remain = 3

sort
[4 6] [2 9] [ 8 11 ] [3 14] - -

[ 4 6 2 9 ] [8 11 3 14] --

[4 6 2 9 8 11 3 14]


func()
{
	if (size > 1)
	{
		...
		func();
	}
	...
}	

*/