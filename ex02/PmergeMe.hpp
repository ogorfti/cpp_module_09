/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:37:38 by ogorfti           #+#    #+#             */
/*   Updated: 2023/11/27 10:40:33 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

class PmergeMe
{
	private:
		std::string _str;
	public:
		PmergeMe();
		PmergeMe(const std::string&);
		PmergeMe(const PmergeMe&);
		~PmergeMe();
		PmergeMe &operator=(const PmergeMe&);
};