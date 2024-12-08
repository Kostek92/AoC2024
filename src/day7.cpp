#include "day7.h"
#include "config.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>

long long Day7::solve1() const
{
	long long result = 0;
	const auto& input = readInput();
	for(const auto& equation : input)
	{
		const auto& values = equation.values;
		const auto n = values.size();
		if(!n)
		{
			continue;
		}
		const int nCombinationCount = pow(2, (n-1));
		for (int attempt = 0; attempt <= nCombinationCount-1; ++attempt)
		{
			long long equationResult = values[0];
			for(int i = 1; i < n; ++i)
			{
				if((attempt >> (i-1)) & 1)
				{
					equationResult += values[i];
				}
				else
				{
					equationResult *= values[i];
				}
			}
			if (equationResult == equation.testValue)
			{
				result += equationResult;
				break;
			}
		}
	}
	return result;
}

long long Day7::solve2() const
{
	long long result = 0;
	const auto& input = readInput();
	for(const auto& equation : input)
	{
		const auto& values = equation.values;
		const auto n = values.size();
		if(!n)
		{
			continue;
		}
		auto operationsSet = getNextOperationsSet(n);
		const int nCombinationCount = pow(2, (n-1));
		for (int attempt = 0; attempt <= nCombinationCount-1; ++attempt)
		{
			long long equationResult = values[0];
			for(int i = 1; i < n; ++i)
			{
				if((attempt >> (i-1)) & 1)
				{
					equationResult += values[i];
				}
				else
				{
					equationResult *= values[i];
				}
			}
			if (equationResult == equation.testValue)
			{
				result += equationResult;
				break;
			}
		}
	}
	return result;
}

std::vector<std::vector<Day7::OperationType>> Day7::getNextOperationsSet(int valuesCount) const
{
	const int nCombinationCount = pow(3, (valuesCount-1));
	std::vector<std::vector<OperationType>> result;

	std::vector<OperationType> operationBitsCzyChujWiecCo(valuesCount - 1);
	int nieChceMiSieWymyslacZmiennych = 0;

	for (int i = 0; i < nCombinationCount; ++i)
	{
		std::vector<OperationType> operationsSet;
		for(int j = 0; j < valuesCount - 1; ++j)
		{

			operationBitsCzyChujWiecCo[j] = static_cast<OperationType>((operationBitsCzyChujWiecCo[j] + 1) % 3);
			++nieChceMiSieWymyslacZmiennych;
			operationsSet.push_back(operationBitsCzyChujWiecCo[j]);
		}
		result.push_back(operationsSet);
	}

	return result;
}

std::vector<Day7::Input> Day7::readInput() const
{
	std::vector<Input> result;
	const std::string fileName = std::string(config::INPUT_DIR_PATH) + "\\Day7.txt";
	std::ifstream file(fileName);

	if (!file) {
		std::cerr << "Error: Unable to open file " << fileName << std::endl;
		return result;
	}

	std::string line;

	while (std::getline(file, line) && !line.empty()) {
		std::istringstream ss(line);
		long long testValue;
		char delimiter;
		bool firstValue = true;

		Input equation;
		while (ss >> testValue) {
			if(firstValue)
			{
				equation.testValue = testValue;
				ss >> delimiter;
				firstValue = false;
			}
			else
			{
				equation.values.push_back(testValue);
			}
		}
		result.push_back(equation);
	}
	return result;
}
