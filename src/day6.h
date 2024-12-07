#ifndef DAY6_H
#define DAY6_H

#include <vector>

class Day6
{
public:
	using labMap = std::vector<std::vector<char>>;
	using coordinates = std::pair<int, int>;

	Day6() = default;

	int solve1();
	int solve2();

private:
	enum Direction
	{
		RIGHT,
		DOWN,
		LEFT,
		UP
	};
	struct HitObstacle
	{
		coordinates coordinates;
		Direction dir;
	};


	labMap readInput() const;
	coordinates findGuard(const labMap& map) const;
	Direction getNextDirection(Direction currentDirection) const;

	bool willHitObstacle(const std::vector<HitObstacle>& obstacles
	, const coordinates& currentCoordinates
	, Direction currentDirection) const;

	static constexpr char m_obstacleSymbol = '#';
	static constexpr char m_seenSymbol = 'X';
	static constexpr char m_notSeenSymbol = '.';

	mutable std::vector<coordinates> extras = {};


	const std::vector<coordinates> m_moves =
	{{0,1}		//right
	,{1,0}		//down
	,{0,-1}		//left
	,{-1,0}		//up
	};



};

#endif // DAY6_H
