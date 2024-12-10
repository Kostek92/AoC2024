#ifndef DAY8_H
#define DAY8_H

#include <unordered_map>
#include <vector>
class Day8
{
public:
	Day8() = default;

	int solve1();
	int solve2();

private:
	using antenasMap = std::vector<std::vector<char>>;
	using coordinates = std::pair<int, int>;

	std::unordered_map<char, std::vector<coordinates>> parseAntenas(const antenasMap &labMap);
	antenasMap readInput() const;
	std::pair<coordinates, coordinates> createAntinodes(const coordinates& antena1, const coordinates& antena2) const;
	bool isAntinodeOnMap(const coordinates& antinode, const antenasMap &labMap) const;

	bool shouldSaveAntinode(const coordinates& antinode, const antenasMap& labMap, const std::vector<coordinates>& allAntenas) const;
};

#endif // DAY8_H
