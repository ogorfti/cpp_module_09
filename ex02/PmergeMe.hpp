/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:37:38 by ogorfti           #+#    #+#             */
/*   Updated: 2023/12/12 17:36:52 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

typedef std::pair<std::vector<int>, std::vector<int> > onePair;

typedef std::vector < onePair > vecP;

class PmergeMe
{
	private:
		char **_av;
		std::vector <int> remain;
		std::vector <int> _v;
		
		vecP _pairs;
		bool done;
		std::vector< std::vector<int> > _collection;
	public:
		PmergeMe();
		PmergeMe(const PmergeMe&);
		~PmergeMe();
		PmergeMe &operator=(const PmergeMe&);
		
		PmergeMe(char **av);
		void checkInput();
		void recursion(size_t index);
		void initPairs();
		void pairToVec(std::vector<onePair>& pairs);

		void runFJMI();
};

void printPairs(vecP _pairs);
void printPair(const std::pair<std::vector<int>, std::vector<int> >& pair);
void printVector(const std::vector<int>& vec);
void printVectorOfVectors(const std::vector<std::vector<int> >& vec);