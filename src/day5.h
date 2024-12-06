#ifndef DAY5_H
#define DAY5_H

#include <vector>
class Day5
{
public:
	Day5() = default;
	int solve1() const;

private:
	struct Input
	{
		std::vector<std::pair<int, int>> rules;
		std::vector<std::vector<int>> instructions;
	};

	Input readInput() const;
};

#endif // DAY5_H
