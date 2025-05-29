// internal includes
#include "Wall.h"

void CSolidWall::InitTexture()
{
	// Load image from files

	std::stringstream ss;
	ss << "Sprites/Wall/solid_wall.png";

	sf::Texture texture;
	if (texture.loadFromFile(ss.str()))
	{
		m_texture = texture;
	}
	else
	{
		std::cout << "Failed to load Texture : " << ss.str() << "\n";
	}

}

void CSolidWall::InitSprite()
{
	m_sprite.setTexture(m_texture);
}


void CSolidWall::InitObject(float initialPositionX, float initialPositionY)
{
	InitTexture();
	InitSprite();
	SetPosition({ initialPositionX, initialPositionY });
}




////////////////////////////////////////////////////////////////////////////////////////






void CBrickWall::InitTexture()
{
	// Load image from files

	std::stringstream ss;
	ss << "Sprites/Wall/brick_wall.png";

	sf::Texture texture;
	if (texture.loadFromFile(ss.str()))
	{
		m_texture = texture;
	}
	else
	{
		std::cout << "Failed to load Texture : " << ss.str() << "\n";
	}

}

void CBrickWall::InitSprite()
{
	m_sprite.setTexture(m_texture);
}


void CBrickWall::InitObject(float initialPositionX, float initialPositionY)
{
	InitTexture();
	InitSprite();
	SetPosition({ initialPositionX, initialPositionY });
}