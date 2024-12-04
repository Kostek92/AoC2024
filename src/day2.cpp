#include "day2.h"
#include "config.h"
#include <fstream>
#include <sstream>
#include <iostream>

int Day2::solve1() const
{
	int result = 0;
	const auto& reports = readInput1();
	const bool useDamper = false;
	for(const auto& report : reports)
	{
		if(validateReport(report, useDamper))
		{
			++result;
		}
	}
	return result;
}

int Day2::solve2() const
{
	int result = 0;
	auto reports = readInput1();
	const bool useDamper = true;
	for(const auto& report : reports)
	{
		if(validateReport(report, useDamper))
		{
			++result;
		}
	}
	return result;
}

Day2::Input1 Day2::readInput1() const
{
	Input1 result;
	const std::string fileName = std::string(config::INPUT_DIR_PATH) + "\\Day2.txt";
	std::ifstream file(fileName);

	if (!file) {
		std::cerr << "Error: Unable to open file " << fileName << std::endl;
		return {};
	}

	std::string line;
	while (std::getline(file, line)) {
		std::vector<int> row;
		std::stringstream ss(line);
		int value;
		while (ss >> value) {
			row.push_back(value);
		}
		result.push_back(row);
	}
	file.close();
	return result;
}

bool Day2::isEntrySafe(int leftValue, int rightValue, bool increasing) const
{
	const auto diff = std::abs(leftValue - rightValue);

	return (diff >= 1 && diff <= 3)
					   && (increasing ? leftValue < rightValue : leftValue > rightValue);
}

bool Day2::validateReport(const std::vector<int> &report, bool useDamper) const
{
	if(report.size() < 2)
	{
		return true;
	}
	bool increasing = report[0] < report[1];
	bool reportSafe = true;
	for(int i = 1; i < report.size(); ++i)
	{
		reportSafe = isEntrySafe(report[i-1], report[i], increasing);
		if(!reportSafe)
		{
			if(useDamper)
			{
				if(removeAndValidate(report, i))
				{
					return true;
				}

				if(removeAndValidate(report, 0))
				{
					return true;
				}

				return removeAndValidate(report, i-1);
			}
			break;
		}
	}
	return reportSafe;
}

bool Day2::removeAndValidate(const std::vector<int> &report, int indexElemToRemove) const
{
	std::vector<int> reportWithoutElem = report;
	reportWithoutElem.erase(reportWithoutElem.begin() + indexElemToRemove);
	return validateReport(reportWithoutElem, false);
}


