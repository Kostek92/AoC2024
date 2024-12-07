#ifndef DAY6_H
#define DAY6_H

#include <vector>

class Day6
{
public:
	Day6() = default;

	int solve1();

private:
	using labMap = std::vector<std::vector<char>>;
	labMap readInput() const;
	std::pair<int, int> findGuard(const labMap& map) const;
	enum Direction
	{
		RIGHT,
		DOWN,
		LEFT,
		UP
	};
	Direction getNextDirection(Direction currentDirection) const;
	static constexpr char m_wallSymbol = '#';
	static constexpr char m_seenSymbol = 'X';
	static constexpr char m_notSeenSymbol = '.';

	const std::vector<std::pair<int, int>> m_dir =
	{{0,1}		//right
	,{1,0}		//down
	,{0,-1}		//left
	,{-1,0}		//up
	};



};

#endif // DAY6_H
