#pragma once

// internal includes
#include "StaticObject.h"

class CKey : public CStaticObject
{
protected:

public:
	void InitTexture();
	void InitSprite();
	void InitObject(float initialPositionX, float initialPositionY);
};


////////////////////////////////////////////////////////////////////////////////////////


class CDoor : public CStaticObject
{
protected:

public:
	void InitTexture();
	void InitSprite();
	void InitObject(float initialPositionX, float initialPositionY);
};
