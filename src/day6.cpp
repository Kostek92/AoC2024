#include "day6.h"
#include "config.h"
#include <iostream>
#include <string>
#include <fstream>

std::pair<int, int> move(const std::pair<int, int>& from, const std::pair<int, int>& dir) {
	return {from.first + dir.first, from.second + dir.second};
}

std::pair<int, int> undo(const std::pair<int, int>& from, const std::pair<int, int>& dir) {
	return {from.first - dir.first, from.second - dir.second};
}

int Day6::solve1()
{
	int result = 1;
	auto labMap = readInput();
	const int n = labMap.size();

	Direction currentDirection = Direction::UP;
	auto currentPosition = findGuard(labMap);

	while (true)
	{
		currentPosition = move(currentPosition, m_dir[currentDirection]);
		if(currentPosition.first >= 0 && currentPosition.first < n
		&& currentPosition.second >= 0 && currentPosition.second < n)
		{
			auto& place = labMap[currentPosition.first][currentPosition.second];
			if(place == m_wallSymbol)
			{
				currentPosition = undo(currentPosition, m_dir[currentDirection]);
				currentDirection = getNextDirection(currentDirection);
			}
			else if(place == m_notSeenSymbol)
			{
				place = m_seenSymbol;
				++result;
			}
		}
		else
		{
			break;
		}

	}
	return result;
}


Day6::labMap Day6::readInput() const
{
	const std::string fileName = std::string(config::INPUT_DIR_PATH) + "\\Day6.txt";
	std::ifstream file(fileName);

	if (!file) {
		std::cerr << "Error: Unable to open file " << fileName << std::endl;
		return {};
	}

	labMap map;
	std::string line;

	while (std::getline(file, line)) {
		std::vector<char> row(line.begin(), line.end());
		map.push_back(row);
	}
	return map;
}

std::pair<int, int> Day6::findGuard(const labMap &map) const
{

	for(int rowIndex = 0; rowIndex < map.size(); ++rowIndex)
	{
		for(int colIndex = 0; colIndex < map[rowIndex].size(); ++colIndex)
		{
			if(map[rowIndex][colIndex] == '^')
			{
				return {rowIndex,colIndex};
			}
		}
	}
	std::cerr << "Error: Guard not found" << std::endl;
	return {0,0};
}

Day6::Direction Day6::getNextDirection(Direction currentDirection) const
{
	return static_cast<Direction>((currentDirection + 1) % 4);
}
