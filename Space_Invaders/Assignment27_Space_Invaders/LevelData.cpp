// internal includes
#include "LevelData.h"

CLevelData::CLevelData()
{
	/*
		Storing the Game Data in the LevelData class, such as
		Positions of each brick and question block and where the powerups are.
	*/
	// brick blocks
	std::list<sf::FloatRect> brickBlocks
	{
		{ 320,136,16,16 },
		{ 352,136,16,16 },
		{ 384,136,16,16 },
		{ 1232,136,16,16 },
		{ 1264,136,16,16 },

		// row of 8 blocks
		{ 1280 + (16 * 0),72,16,16 },
		{ 1280 + (16 * 1),72,16,16 },
		{ 1280 + (16 * 2),72,16,16 },
		{ 1280 + (16 * 3),72,16,16 },
		{ 1280 + (16 * 4),72,16,16 },
		{ 1280 + (16 * 5),72,16,16 },
		{ 1280 + (16 * 6),72,16,16 },
		{ 1280 + (16 * 7),72,16,16 },

		// row of 3 blocks
		{ 1456 + (16 * 0),72,16,16 },
		{ 1456 + (16 * 1),72,16,16 },
		{ 1456 + (16 * 2),72,16,16 },

		{ 1504,136,16,16 },

		// row of 2 blocks
		{ 1600 + (16 * 0),136,16,16 },
		{ 1600 + (16 * 1),136,16,16 },

		{ 1888,136,16,16 },

		// row of 3 blocks
		{ 1936 + (16 * 0),72,16,16 },
		{ 1936 + (16 * 1),72,16,16 },
		{ 1936 + (16 * 2),72,16,16 },

		{ 2048,72,16,16 },
		{ 2096,72,16,16 },

		// row of 2 blocks
		{ 2064 + (16 * 0),136,16,16 },
		{ 2064 + (16 * 1),136,16,16 },

		// row of 2 blocks
		{ 2688 + (16 * 0),136,16,16 },
		{ 2688 + (16 * 1),136,16,16 },

		{ 2736,136,16,16 }
	};
	m_spriteData[EObject::BRICK] = brickBlocks;

	// question blocks
	std::list<sf::FloatRect> questionBlocks
	{
		{ 256,136,16,16 },
		{ 336,136,16,16 },
		{ 368,136,16,16 },
		{ 352,72,16,16 },
		{ 1248,136,16,16 },
		{ 1504,72,16,16 },
		{ 1744,72,16,16 },
		{ 1696,136,16,16 },
		{ 1744,136,16,16 },
		{ 1792,136,16,16 },
		{ 2064,72,16,16 },
		{ 2080,72,16,16 },
		{ 2720,136,16,16 }
	};
	m_spriteData[EObject::QUESTION] = questionBlocks;


	// vertical pipes
	std::list<sf::FloatRect> verticalPipes
	{
		{ 448,168,32,32 },
		{ 608,152,32,48 },
		{ 736,136,32,64 },
		{ 912,136,32,64 },
		{ 2608,168,32,32 },
		{ 2864,168,32,32 }
	};
	m_spriteData[EObject::VERTICAL_PIPE] = verticalPipes;

	// ground data
	std::list<sf::FloatRect> grounds
	{
		{ 0,200,1104,32 },
		{ 1136,200,240,32 },
		{ 1424,200,1024,32 },
		{ 2480,200,900,32 }
	};
	m_spriteData[EObject::GROUND] = grounds;

	// pits
	std::list<sf::FloatRect> pits
	{
		{1104,200,32,32},
		{1376,200,48,32},
		{2448,200,32,32}
	};
	m_spriteData[EObject::PIT] = pits;

	// invisible block
	std::list<sf::FloatRect> invisibleBlocks
	{
		{ 1024,120,16,16 }
	};
	m_spriteData[EObject::INVISIBLE_BLOCK] = invisibleBlocks;

	// stairs' data
	std::list<sf::FloatRect> staircases	// each row behaves like a solid block
	{
		// staircase 1
		{ 2144,184,64,16 },
		{ 2160,168,48,16 },
		{ 2176,152,32,16 },
		{ 2192,136,16,16 },

		// staircase 2
		{ 2240,184,64,16 },
		{ 2240,168,48,16 },
		{ 2240,152,32,16 },
		{ 2240,136,16,16 },

		// staircase 3
		{ 2368,184,80,16 },
		{ 2384,168,64,16 },
		{ 2400,152,48,16 },
		{ 2416,136,32,16 },

		// staircase 4
		{ 2480,184,64,16 },
		{ 2480,168,48,16 },
		{ 2480,152,32,16 },
		{ 2480,136,16,16 },

		// staircase 5
		{ 2896, 184, 144, 16 },
		{ 2912, 168, 128, 16 },
		{ 2928, 152, 112, 16 },
		{ 2944, 136, 96, 16 },
		{ 2960, 120, 80, 16 },
		{ 2976, 104, 64, 16 },
		{ 2992, 88,	48, 16 },
		{ 3008, 72, 32, 16 },

	};
	m_spriteData[EObject::STAIR_BLOCK] = staircases;

	// flag data
	std::list<sf::FloatRect> flagBall
	{
		{ 3172,32,8,8 }
	};
	m_spriteData[EObject::FLAG_BALL] = flagBall;

	std::list<sf::FloatRect> flagpole
	{
		{ 3175,40,2,144 },
	};
	m_spriteData[EObject::FLAG_POLE] = flagpole;
}

/*
	returns a list of floatRect objects corresponding to the object user asked the data for
*/
const std::list<sf::FloatRect>& CLevelData::GetObjectData(EObject object)
{
	if (m_spriteData.find(object) == m_spriteData.end())
	{
		return std::list<sf::FloatRect>();
	}
	return m_spriteData[object];
}