#pragma once

// internal includes
#include "StaticObject.h"

class CBomb : public CStaticObject
{
protected:
	std::vector<sf::Texture> m_explosionTexture;
	std::vector<sf::Texture> m_bombTexture;
public:
	void InitTexture();
	void InitSprite();
	void InitObject(float initialPositionX, float initialPositionY);
};