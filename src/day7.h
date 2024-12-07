#ifndef DAY7_H
#define DAY7_H

#include <vector>
class Day7
{
public:
	Day7() = default;

	long long solve1() const;

private:
	struct Input
	{
		long long testValue;
		std::vector<long long> values;
	};
	std::vector<Input> readInput() const;
};

#endif // DAY7_H
