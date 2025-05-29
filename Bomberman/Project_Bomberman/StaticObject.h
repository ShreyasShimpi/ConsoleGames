#pragma once

// internal includes
#include "RectShape.h"

class CStaticObject : public CRectShape
{
protected:
	sf::Texture m_texture;
public:
	virtual void InitTexture() = 0;
	virtual void InitSprite() = 0;
	virtual void InitObject(float initialPositionX, float initialPositionY) = 0;
};
