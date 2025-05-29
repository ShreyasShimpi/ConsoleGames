
// internal includes
#include "Bomb.h"

void CBomb::InitTexture()
{
	// Load image from files
	for (int i = 0; i < 3; ++i)
	{
		std::stringstream ss;
		ss << "Sprites/Explosion/bomb(" << i << ").png";

		if (m_texture.loadFromFile(ss.str()))
		{
			m_bombTexture.push_back(m_texture);
		}
		else
		{
			std::cout << "Failed to load Texture : " << ss.str() << "\n";
		}
	}

}

void CBomb::InitSprite()
{
	m_sprite.setTexture(m_bombTexture[0]);
}


void CBomb::InitObject(float initialPositionX, float initialPositionY)
{
	InitTexture();
	InitSprite();
	SetPosition({ initialPositionX, initialPositionY });
}

