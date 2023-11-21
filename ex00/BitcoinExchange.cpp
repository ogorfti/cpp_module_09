/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:02:13 by ogorfti           #+#    #+#             */
/*   Updated: 2023/11/21 11:54:27 by ogorfti          ###   ########.fr       */
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

int checkDigits(const std::string& str, const std::string& fLine)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		if (!std::isdigit(str[i]) && str != fLine && str[i] != '.'
			&& str[i] != '-' && str[i] != '+')
		{
			std::cerr << "Error: invalid date format." << '\n';
			return (1);
		}
	}
	return (0);
}

int	checkRate(const std::string& rate, bool check)
{
	char *end;
	double nbr = std::strtod(rate.c_str(), &end);
	
	if (rate == "value")
		return 0;
	else if (nbr < 0)
	{
		std::cerr << "Error: not a positive number." << '\n';
		return (1);
	}
	else if (check && nbr > MAX_RATE)
	{
		std::cerr << "Error: too large a number." << '\n';
		return (1);
	}
	else if (end != rate.c_str() + rate.length())
	{
		std::cerr << "Error: invalid number." << '\n';
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
	else if (_year < 2009 || (_year == 2009 && (_month < 1 || (_month == 1 && _day < 2))))
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
		std::cerr << "Error: Invalid date value." << std::endl;
		return 1;
	}
	return (0);
}

int	checkDate(const std::string& date)
{
	if (date != "date")
	{
		size_t begin = date.find('-');
		if (begin == std::string::npos || begin != 4)
		{
			std::cerr << "Error: invalid date format." << '\n';
			return 1;
		}
		std::string year = date.substr(0, begin);
		
		size_t end = date.find('-', begin + 1);
		if (end == std::string::npos || end != 7)
		{
			std::cerr << "Error: invalid date format." << '\n';
			return 1;
		}
		std::string month = date.substr(begin + 1, end - begin - 1);
		
		std::string day = date.substr(end + 1);
		if (day.empty())
		{
			std::cerr << "Error: invalid date format." << '\n';
			return 1;
		}
		if (checkDigits(year, "value") || checkDigits(month, "value") || checkDigits(day, "value") ||
			checkRange(std::atof(day.c_str()), std::atof(month.c_str()), std::atof(year.c_str())))
			return (1);
	}
	return (0);
}

void BitcoinExchange::readData()
{
	std::ifstream dataFile("data.csv");

	if (!dataFile.is_open())
		throw std::runtime_error("Error: could not open database file.");
	else if (dataFile.peek() == std::ifstream::traits_type::eof())
		throw std::runtime_error("Error: database file is empty.");
	std::string line;
	bool check = true;
	while (std::getline(dataFile, line))
	{
		size_t pos = line.find(',');

		if (check && line == "date,exchange_rate")
		{
			check = false;
			continue;
		}
		else if (check)
			throw std::runtime_error("Error: invalid format in the database file.");
		else if (pos != std::string::npos && std::strcmp(line.c_str(), "date,exchange_rate"))
		{
			std::string date = line.substr(0, pos);
			std::string tmp =  line.substr(pos + 1);
			
			if (!checkDate(date) && !checkDigits(tmp, "exchange_rate") && !checkRate(tmp, false))
			{
				double rate = std::atof(tmp.c_str());
				data[date] = rate;
			}
			else
				throw std::runtime_error("check the database!");
		}
		else
			throw std::runtime_error("Error: invalid format in the database file.");
	}
	dataFile.close();
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
		if (line.empty())
		{
			std::cerr << "Error: empty line." << '\n';
			continue ;
		}
		size_t pos = line.find('|');
		if (pos != std::string::npos && (pos == 11 || pos == 5))
		{
			std::string date = line.substr(0, pos - 1);
			std::string rate = line.substr(pos + 2);
			
			if (!checkDigits(rate, "value") && !checkRate(rate, true) && !checkDate(date) && date != "date" && rate != "value")
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
			std::cerr << "Error: bad input => " << line << '\n';
	}
}
