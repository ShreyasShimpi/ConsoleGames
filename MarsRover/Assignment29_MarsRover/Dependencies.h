#pragma once
#include <iostream>

// DATA
// number of rovers
constexpr short g_groundRovers = 0;
constexpr short g_flyingRovers = 1;

// IPS : instructions per seconds to execute
constexpr short g_groundRoverIPS = 1;
constexpr short g_flyingRoverIPS = 2;


// rover direction
enum class ERoverDirection
{
	North, South, East, West
};

// rover data
struct SRoverData
{
	int m_x;
	int m_y;
	char m_dir;

	// ostream operator overload for printing rover data
	friend std::ostream& operator << (std::ostream& os, const SRoverData& roverData);

};

// grid coordinates
struct SGridCoordinates
{
	int m_row;
	int m_column;

	// `operator==` is required to compare keys in case of a hash collision
	bool operator == (const SGridCoordinates& coord) const
	{
		return m_row == coord.m_row && m_column == coord.m_column;
	}

	bool operator < (SGridCoordinates const& coord) const
	{
		return m_column < coord.m_column || (m_column == coord.m_column && m_row < coord.m_row);
	}

	bool operator > (SGridCoordinates const& coord) const
	{
		return m_column > coord.m_column || (m_column == coord.m_column && m_row > coord.m_row);
	}
};


// custom hashing function for grid coordinates as a key
class CCoordinatesHashFunction
{
public:
	// operator overloading for custom hash function
	size_t operator () (const SGridCoordinates& coord) const
	{
		auto hash1 = std::hash<int>{}(coord.m_row);
		auto hash2 = std::hash<int>{}(coord.m_column);
		return hash1 ^ hash2;
	}
};
