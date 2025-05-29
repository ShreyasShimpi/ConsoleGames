#pragma once

// external includes
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <sstream>

// internal includes


enum class EColliderType
{
	TRIGGER,
	COLLIDER
};

enum class ECollisionType
{
	STOP,
	BOUNCE,
	SLIDE
};

class CRectShape
{

protected:
	EColliderType m_colliderType = EColliderType::COLLIDER;
	ECollisionType m_collisionType = ECollisionType::SLIDE;

	// texture
	sf::Vector2f m_position;
	sf::Sprite m_sprite;

public:
	CRectShape();

	void SetSpriteScale(sf::Vector2f scale);
	void SetPosition(sf::Vector2f position);

	inline sf::Vector2f GetPosition() { return m_sprite.getPosition(); };
	inline sf::FloatRect GetGlobalBounds() { return m_sprite.getGlobalBounds(); };
	inline EColliderType GetColliderType() { return m_colliderType; };
	inline ECollisionType GetCollisionType() { return m_collisionType; };

	void Render(sf::RenderTarget& target);

};

