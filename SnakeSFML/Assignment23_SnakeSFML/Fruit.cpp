// internal includes
#include "Fruit.h"
// external includes
#include <sstream>
#include <iostream>

CFruit::CFruit(sf::Vector2f position)
{
	std::stringstream ss;
	ss << "Sprites/fruit.png";

	if (m_fruitTexture.loadFromFile(ss.str()))
	{
		m_fruitSprite.setTexture(m_fruitTexture);
	}
	else
	{
		std::cout << "Failed to load Texture : " << ss.str() << "\n";
	}
	m_fruitSprite.setPosition(position);
	m_fruitSprite.setScale({ float(FRUIT_BLOCKSIZE) / float(FRUIT_SPRITESIZE), float(FRUIT_BLOCKSIZE) / float(FRUIT_SPRITESIZE) });
}

void CFruit::SetPosition(sf::Vector2f position)
{
	m_fruitSprite.setPosition(position);
}

void CFruit::Render(sf::RenderTarget& target)
{
	target.draw(m_fruitSprite);
}
