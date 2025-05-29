#pragma once

// internal includes
#include "StaticObject.h"

class CSolidWall : public CStaticObject
{
protected:
	
public:
	void InitTexture();
	void InitSprite();
	void InitObject(float initialPositionX, float initialPositionY);
};

////////////////////////////////////////////////////////////////////////////////////////


class CBrickWall : public CStaticObject
{
protected:
	
public:
	void InitTexture();
	void InitSprite();
	void InitObject(float initialPositionX, float initialPositionY);
};


