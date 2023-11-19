/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:02:13 by ogorfti           #+#    #+#             */
/*   Updated: 2023/11/19 20:48:17 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	*this = other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
	{
		this->data = other.data;
		this->iFile = other.iFile;
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::readData()
{
	std::ifstream dataFile("data.csv");

	if (!dataFile.is_open())
		throw std::runtime_error("Error: could not open database file.");
	std::string line;
	while (std::getline(dataFile, line))
	{
		size_t pos = line.find(',');
		if (pos != std::string::npos && line.compare("date,exchange_rate"))
		{
			std::string date = line.substr(0, pos);
			std::string tmp =  line.substr(pos + 1);
			
			double rate = std::atof(tmp.c_str());

			data[date] = rate;
		}
	}
	dataFile.close();
}

int	checkRate(const std::string& rate)
{
	double nbr = std::atof(rate.c_str());
	if (nbr < 0)
	{
		std::cout << "Error: not a positive number." << '\n';
		return (1);
	}
	else if (nbr > MAX_RATE)
	{
		std::cout << "Error: too large a number." << '\n';
		return (1);
	}
	return (0);
}

int	checkYear(double _day, double _month, double _year)
{
	std::time_t currentTime = std::time(NULL); // function to get the current time in seconds since the epoch
	std::tm* localTime = std::localtime(&currentTime); //function to convert the std::time_t value to y/m/d

	int year = localTime->tm_year + 1900;
	int month = localTime->tm_mon + 1;
	int day = localTime->tm_mday;
	
	if (_year > year || (_year == year && (_month > month || (_month == month && _day > day))))
		return 1;
	else if (_year < 2009 || (_year == 2009 && (_month < 1 || (_month == 1 && _day < 3))))
		return 1;
	return (0);
}

int checkDay(int month, int year)
{
	switch (month)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			return 31;
		case 4:
		case 6:
		case 9:
		case 11:
			return 30;
		case 2: // February
			if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
				return 29;
			else
				return 28;
		default:
			return -1;
	}
}

int checkRange(double day, double month, double year)
{
	if (day > checkDay(month, year) || day < 1 || month > 12 || month < 1
		|| checkYear(day, month, year))
	{
		std::cout << "Error: Invalid date value." << std::endl;
		return 1;
	}
	return (0);
}

int	checkDate(const std::string& date)
{
	if (date != "date")
	{
		size_t begin = date.find('-');
		if (begin == std::string::npos)
		{
			std::cout << "Error: invalid date format." << '\n';
			return 1;
		}
		std::string year = date.substr(0, begin);
		
		size_t end = date.find('-', begin + 1);
		if (end == std::string::npos)
		{
			std::cout << "Error: invalid date format." << '\n';
			return 1;
		}
		std::string month = date.substr(begin + 1, end - begin - 1);
		
		std::string day = date.substr(end + 1);
		if (day.empty())
		{
			std::cout << "Error: invalid date format." << '\n';
			return 1;
		}
		if (checkRange(std::atof(day.c_str()), std::atof(month.c_str()), std::atof(year.c_str())))
			return (1);
	}
	return (0);
}

BitcoinExchange::BitcoinExchange(const std::string& inputFile)
{
	this->iFile = inputFile;
	this->readData();

	std::ifstream file(iFile);
	if (!file.is_open())
		throw std::runtime_error("Error: could not open input file.");
	
	std::string line;
	while (std::getline(file, line))
	{

		size_t pos = line.find('|');
		if (pos != std::string::npos)
		{
			std::string date = line.substr(0, pos - 1);
			std::string rate = line.substr(pos + 2);
			
			if (!checkRate(rate) && !checkDate(date) && date != "date" && rate != "value")
			{
				//* success case
				
				std::map<std::string, double>::iterator it = this->data.lower_bound(date);
				if (it->first != date)
					it--;
				double exchange = std::atof(rate.c_str()) * it->second;
				std::cout << date << " => " << rate << " = " << exchange << std::endl;
			}
		}
		else
			std::cout << "Error: bad input => " << line << '\n';
	}
}
