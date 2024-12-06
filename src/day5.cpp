#include "day5.h"
#include "config.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <algorithm>

int Day5::solve1() const
{
	auto input = readInput();
	const auto& rules = input.rules;
	const auto& instructions = input.instructions;

	std::unordered_map<int, std::vector<int>> rules_map;
	for(const auto& rule : rules)
	{
		rules_map[rule.first].push_back(rule.second);
	}

	int result = 0;
	for(const auto& instruction : instructions)
	{
		bool instructionValid = true;
		for (int i = 1; i < instruction.size(); ++i)
		{
			const std::vector<int>& rulesPerPage = rules_map[instruction[i]];
			if(!rulesPerPage.empty())
			{
				for(int j = i - 1; j >=0; --j)
				{
					if(std::find(rulesPerPage.begin(), rulesPerPage.end(), instruction[j]) != rulesPerPage.end())
					{
						instructionValid = false;
						break;
					}
				}
			}
			if(!instructionValid)
			{
				break;
			}
		}
		if(instructionValid)
		{
			int middleIndex = instruction.size()/2;
			result+= instruction[middleIndex];
		}
	}

	return result;
}

Day5::Input Day5::readInput() const
{
	Input result;
	const std::string fileName = std::string(config::INPUT_DIR_PATH) + "\\Day5.txt";
	std::ifstream file(fileName);

	if (!file) {
		std::cerr << "Error: Unable to open file " << fileName << std::endl;
		return result;
	}

	std::string line;

	while (std::getline(file, line) && !line.empty()) {
		std::istringstream ss(line);
		int first, second;
		char delimiter;

		if (ss >> first >> delimiter >> second && delimiter == '|') {
			result.rules.emplace_back(first, second);
		}
	}

	while (std::getline(file, line) && !line.empty()) {
			std::istringstream ss(line);
			std::vector<int> instruction;
			int number;
			char delimiter;

			while (ss >> number) {
				instruction.push_back(number);
				ss >> delimiter; // Skip the comma
			}
			result.instructions.push_back(instruction);
	}
	return result;
}
