#pragma once

// internal includes

// external includes
#include <map>
#include <list>
#include <vector>
#include <SFML/Graphics.hpp>


// enum for each object
enum class EObject
{
	BRICK, QUESTION, VERTICAL_PIPE, GROUND, PIT, INVISIBLE_BLOCK, STAIR_BLOCK, FLAG, FLAG_POLE, FLAG_BALL
};

class CLevelData
{
private:
	// level data map
	std::map<EObject, std::list<sf::FloatRect>> m_spriteData;

public:
	// constructor
	CLevelData();
	// destructor
	~CLevelData() = default;

	// Get data for a type of objects
	const std::list<sf::FloatRect>& GetObjectData(EObject object);
};

