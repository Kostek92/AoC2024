#include "day6.h"
#include "config.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

Day6::coordinates move(const Day6::coordinates& from, const Day6::coordinates& dir) {
	return {from.first + dir.first, from.second + dir.second};
}

Day6::coordinates undo(const Day6::coordinates& from, const Day6::coordinates& dir) {
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
		currentPosition = move(currentPosition, m_moves[currentDirection]);
		if(currentPosition.first >= 0 && currentPosition.first < n
		&& currentPosition.second >= 0 && currentPosition.second < n)
		{
			auto& place = labMap[currentPosition.first][currentPosition.second];
			if(place == m_obstacleSymbol)
			{
				currentPosition = undo(currentPosition, m_moves[currentDirection]);
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

int Day6::solve2()
{
	int result = 0;

	auto labMap = readInput();
	std::vector<HitObstacle> seenObstacles;
	const int n = labMap.size();

	Direction currentDirection = Direction::UP;
	auto currentPosition = findGuard(labMap);

	while (true)
	{
		currentPosition = move(currentPosition, m_moves[currentDirection]);
		if(currentPosition.first >= 0 && currentPosition.first < n
		&& currentPosition.second >= 0 && currentPosition.second < n)
		{
			if(willHitObstacle(seenObstacles, currentPosition, getNextDirection(currentDirection)))
			{
				++result;
			}

			auto& place = labMap[currentPosition.first][currentPosition.second];
			if(place == m_obstacleSymbol)
			{
				seenObstacles.push_back({currentPosition, currentDirection});
				currentPosition = undo(currentPosition, m_moves[currentDirection]);
				currentDirection = getNextDirection(currentDirection);
			}
			else if(place == m_notSeenSymbol)
			{
				place = m_seenSymbol;
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

Day6::coordinates Day6::findGuard(const labMap &map) const
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

bool Day6::willHitObstacle(const std::vector<HitObstacle> &obstacles, const coordinates &currentCoordinates, Direction currentDirection) const
{

	for(const auto& obstacle : obstacles)
	{
		if(obstacle.dir != currentDirection)
		{
			continue;
		}
		if(obstacle.coordinates.first == currentCoordinates.first)
		{
			if((obstacle.coordinates.second < currentCoordinates.second && currentDirection == Direction::LEFT)
			|| (obstacle.coordinates.second > currentCoordinates.second && currentDirection == Direction::RIGHT))
			{
				extras.push_back(currentCoordinates);
				return true;
			}
		}
		if(obstacle.coordinates.second == currentCoordinates.second)
		{
			if((obstacle.coordinates.first < currentCoordinates.first && currentDirection == Direction::UP)
			|| (obstacle.coordinates.first > currentCoordinates.first && currentDirection == Direction::DOWN))
			{
				extras.push_back(currentCoordinates);
				return true;
			}
		}
	}
	return false;
}
