
// internal includes
#include "KeyDoor.h"

void CKey::InitTexture()
{
	// Load image from files

	std::stringstream ss;
	ss << "Sprites/Extras/key2.png";

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

void CKey::InitSprite()
{
	m_sprite.setTexture(m_texture);
}


void CKey::InitObject(float initialPositionX, float initialPositionY)
{
	InitTexture();
	InitSprite();
	SetPosition({ initialPositionX, initialPositionY });
}




////////////////////////////////////////////////////////////////////////////////////////






void CDoor::InitTexture()
{
	// Load image from files

	std::stringstream ss;
	ss << "Sprites/Extras/door.png";

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

void CDoor::InitSprite()
{
	m_sprite.setTexture(m_texture);
}


void CDoor::InitObject(float initialPositionX, float initialPositionY)
{
	InitTexture();
	InitSprite();
	SetPosition({ initialPositionX, initialPositionY });
}