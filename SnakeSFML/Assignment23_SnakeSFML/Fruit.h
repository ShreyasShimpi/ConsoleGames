#pragma once
// external includes
#include <SFML/Graphics.hpp>


#define FRUIT_BLOCKSIZE 30
#define FRUIT_SPRITESIZE 64

class CFruit
{
private:
	sf::Sprite m_fruitSprite;
	sf::Texture m_fruitTexture;

public:
	// constructor
	CFruit(sf::Vector2f position);

	// getter
	inline sf::FloatRect GetFruitGlobalBounds() { return m_fruitSprite.getGlobalBounds(); };
	//inline sf::Vector2i GetSize() { return sf::Vector2i(m_fruitSprite.ge()); };

	// setter
	void SetPosition(sf::Vector2f position);

	// render
	void Render(sf::RenderTarget& target);
};