#include "day1.h"
#include "config.h"
#include <algorithm>
#include <fstream>
#include <iostream>

long long Day1::solve1() const
{
	long long result = 0;
	auto input = readInput1();
	auto& leftList = input.leftList;
	auto& rightList = input.rightList;

	if(leftList.size() != rightList.size())
	{
		std::cerr << "List sizes are not equal. Left size: " << leftList.size() << " right rize: " << rightList.size();
	}

	std::sort(leftList.begin(), leftList.end());
	std::sort(rightList.begin(), rightList.end());

	for(int i = 0; i < leftList.size(); ++i)
	{
		result += std::abs(leftList.at(i) - rightList.at(i));
	}
	return result;
}

long long Day1::solve2() const
{
	long long result = 0;
	auto input = readInput1();

	const auto leftListRepeatCounter = countEachNumberRepetitions(input.leftList);
	const auto rightListRepeatCounter = countEachNumberRepetitions(input.rightList);

	for(const auto& repeatedNumberAndCount : leftListRepeatCounter)
	{
		int repeatCountOnRightList = 0;
		if(const auto it = rightListRepeatCounter.find(repeatedNumberAndCount.first); it != rightListRepeatCounter.end())
		{
			repeatCountOnRightList = it->second;
		}
		result += repeatedNumberAndCount.first * repeatedNumberAndCount.second * repeatCountOnRightList;;
	}
	return result;
}


Day1::Input1 Day1::readInput1() const
{
	Input1 result;
	const std::string fileName = std::string(config::INPUT_DIR_PATH) + "\\day1.txt";
	std::ifstream file(fileName);

	if (!file) {
		std::cerr << "Error: Unable to open file " << fileName << std::endl;
		return {};
	}
	int value1, value2;

	while (file >> value1 >> value2) {
		result.leftList.push_back(value1);
		result.rightList.push_back(value2);
	}

	file.close();
	return result;
}

std::unordered_map<int, int> Day1::countEachNumberRepetitions(const std::vector<int> &data) const
{
	std::unordered_map<int, int> dataRepetitionsCounter;
	for(const auto number : data)
	{
		dataRepetitionsCounter[number]++;
	}
	return dataRepetitionsCounter;
}
