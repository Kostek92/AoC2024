#include "day3.h"
#include "config.h"
#include "config.h"
#include <fstream>
#include <iostream>
#include <regex>

int Day3::solve1() const
{
	const auto& input = readInput();
	int result = 0;
	std::regex instructionPattern(R"(mul\((\d+),(\d+)\))");

	auto begin = std::sregex_iterator(input.begin(), input.end(), instructionPattern);
	auto end = std::sregex_iterator();

	for (auto it = begin; it != end; ++it) {
		int x = std::stoi((*it)[1].str());
		int y = std::stoi((*it)[2].str());
		result += x*y;
	}
	return result;
}

int Day3::solve2() const
{
	const auto& input = readInput();
	int result = 0;
	std::regex instructionPattern(R"(mul\((\d+),(\d+)\)|do\(\)|don't\(\))");

	auto begin = std::sregex_iterator(input.begin(), input.end(), instructionPattern);
	auto end = std::sregex_iterator();
	bool enabled = true;

	for (auto it = begin; it != end; ++it)
	{
		const auto actionString = (*it)[0].str();
		if( actionString == "do()")
		{
			enabled = true;
			continue;
		}
		else if(actionString == "don't()")
		{
			enabled = false;
			continue;
		}
		if(enabled)
		{
			int x = std::stoi((*it)[1].str());
			int y = std::stoi((*it)[2].str());
			result += x*y;
		}
	}
	return result;
}


std::string Day3::readInput() const
{
	const std::string fileName = std::string(config::INPUT_DIR_PATH) + "\\Day3.txt";
	std::ifstream file(fileName);

	if (!file) {
		std::cerr << "Error: Unable to open file " << fileName << std::endl;
		return {};
	}

	// Read the entire file content into a string
	std::string result((std::istreambuf_iterator<char>(file)),
						(std::istreambuf_iterator<char>()));
	file.close();
	return result;
}
