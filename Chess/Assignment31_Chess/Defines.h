#pragma once
// external includes
#include <SFML/Graphics.hpp>
#include <iostream>

#define WIDTH 640
#define HEIGHT 640
#define SPRITESIZE 80

#define SIZE 8
#define AI_Sleep 2

enum class EColor
{
	White, Black, None
};

// AI parameters
constexpr bool g_hasAI = true;
constexpr EColor g_AIcolor = EColor::Black;

struct SPosition
{
	int m_row;
	int m_column;

	// operator == is required to compare keys in case of a hash collision
	bool operator == (const SPosition& coord) const
	{
		return m_row == coord.m_row && m_column == coord.m_column;
	}
};


// custom hashing function for grid coordinates as a key
class CCustomHashForPos
{
public:
	// operator overloading for custom hash function
	size_t operator () (const SPosition& coord) const
	{
		auto hash1 = std::hash<size_t>{}(coord.m_row);
		auto hash2 = std::hash<size_t>{}(coord.m_column);
		return hash1 ^ hash2;
	}
};


static bool ValidateInput(char* square)
{
	return ((square[0] >= 'A' && square[0] <= 'H') && (square[1] >= '1' && square[1] <= '8'));
}

static short s_moveNumber = 1;