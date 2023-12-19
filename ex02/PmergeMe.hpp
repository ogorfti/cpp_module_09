/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:37:38 by ogorfti           #+#    #+#             */
/*   Updated: 2023/12/19 11:59:59 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <ctime>
#include <iomanip>

typedef std::vector< std::vector<int> > vecV;
typedef std::deque< std::deque<int> > deqD;

class PmergeMe
{
	private:
		char **_av;
		std::vector <int> remain;
		std::vector< std::vector<int> > _v;
		
		std::deque <int> remain_deq;
		std::deque< std::deque <int> > _v_deq;
		
	public:
		PmergeMe();
		PmergeMe(const PmergeMe&);
		~PmergeMe();
		PmergeMe &operator=(const PmergeMe&);
		
		PmergeMe(char **av);
		void checkInput();
		void recursion();
		void recursionDeq();

		void runFJMI();
};

void printVectorOfVectors(const std::vector<std::vector<int> >& vec, std::string str);
void printDeqOfDeqs(const std::deque<std::deque<int> >& vec, std::string str);