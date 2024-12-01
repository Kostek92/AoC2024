#ifndef DAY1_H
#define DAY1_H
#include <vector>
#include <unordered_map>

class Day1
{
public:
	Day1() = default;
	long long solve1() const;
	long long solve2() const;

private:
	struct Input1
	{
		std::vector<int> leftList {};
		std::vector<int> rightList {};
	};
	Input1 readInput1() const;

	std::unordered_map<int, int> countEachNumberRepetitions(const std::vector<int>& data) const;
};

#endif // DAY1_H
