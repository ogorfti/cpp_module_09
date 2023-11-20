/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:57:08 by ogorfti           #+#    #+#             */
/*   Updated: 2023/11/19 20:50:26 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define MAX_RATE 1000
#include <iostream>
#include <fstream>
#include <map>

class BitcoinExchange
{
    private:
        std::map <std::string, double> data;
        std::string iFile;
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange&);
        BitcoinExchange& operator=(const BitcoinExchange&);
        
        BitcoinExchange(const std::string&);
        ~BitcoinExchange();
        void readData();
};
