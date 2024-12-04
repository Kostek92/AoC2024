#ifndef DAY2_H
#define DAY2_H
#include <vector>

class Day2
{
public:
	Day2() = default;
	int solve1() const;
	int solve2() const;

private:
	using Input1 = std::vector<std::vector<int>>;
	Input1 readInput1() const;
	bool isEntrySafe(int leftValue, int rightValue, bool increasing) const;

	bool validateReport(const std::vector<int>& report, bool useDamper) const;
	bool removeAndValidate(const std::vector<int>& report, int indexElemToRemove) const;
};

#endif // DAY2_H
