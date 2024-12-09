#include "day8.h"
#include "config.h"
#include <fstream>
#include <iostream>
#include <unordered_set>

struct pair_hash {
	inline std::size_t operator()(const std::pair<int,int> & v) const {
		return v.first*31+v.second;
	}
};

std::unordered_map<char, std::vector<Day8::coordinates>> Day8::parseAntenas(const antenasMap &labMap) {
	std::unordered_map<char, std::vector<Day8::coordinates>> antenas{};
	const int n = labMap.size();

	for (int row = 0; row < n; ++row) {
		for (int column = 0; column < n; ++column) {
			const auto elem = labMap[row][column];
			if (elem != '.') {
				antenas[elem].push_back(std::make_pair(row, column));
			}
		}
	}
	return antenas;
}

int Day8::solve1() {
	auto labMap = readInput();
	const int n = labMap.size();

	std::unordered_set<coordinates, pair_hash> allAntinodes{};
	const auto allAntenasByType = parseAntenas(labMap);

	for(const auto& antenasOfType : allAntenasByType)
	{
		const auto antenas = antenasOfType.second;
		for (int i = 0; i < antenas.size(); ++i) {
			for (int j = i+1; j < antenas.size(); ++j) {
				const auto antinodes = createAntinodes(antenas[i], antenas[j]);
				if(isAntinodeOnMap(antinodes.first, labMap))
				{
					allAntinodes.insert(antinodes.first);
				}
				if(isAntinodeOnMap(antinodes.second, labMap))
				{
					allAntinodes.insert(antinodes.second);
				}
			}
		}
	}

	return allAntinodes.size();
}

Day8::antenasMap Day8::readInput() const
{
	const std::string fileName = std::string(config::INPUT_DIR_PATH) + "\\Day8.txt";
	std::ifstream file(fileName);

	if (!file) {
		std::cerr << "Error: Unable to open file " << fileName << std::endl;
		return {};
	}

	antenasMap map;
	std::string line;

	while (std::getline(file, line)) {
		std::vector<char> row(line.begin(), line.end());
		map.push_back(row);
	}
	return map;
}

std::pair<Day8::coordinates, Day8::coordinates> Day8::createAntinodes(const coordinates &antena1, const coordinates &antena2) const
{
	const coordinates diff = std::make_pair(std::abs(antena1.first - antena2.first), std::abs(antena1.second - antena2.second));

	coordinates andinode1, antinode2;

	if(antena1.first < antena2.first)
	{
		andinode1.first = antena1.first - diff.first;
		antinode2.first = antena2.first + diff.first;
	}
	else
	{
		andinode1.first = antena1.first + diff.first;
		antinode2.first = antena2.first - diff.first;
	}

	if(antena1.second < antena2.second)
	{
		andinode1.second = antena1.second - diff.second;
		antinode2.second = antena2.second + diff.second;
	}
	else
	{
		andinode1.second = antena1.second + diff.second;
		antinode2.second = antena2.second - diff.second;
	}

	return std::make_pair(andinode1, antinode2);
}

bool Day8::isAntinodeOnMap(const coordinates &antinode, const antenasMap &labMap) const
{
	return antinode.first < labMap.size() && antinode.second < labMap[0].size();
}
