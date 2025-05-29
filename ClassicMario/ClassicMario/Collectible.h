#pragma once
#include <SFML/Graphics.hpp>
#include <chrono>

typedef std::chrono::high_resolution_clock::time_point TimePoint;

// type of collectible
enum class ECollectible
{
	Growth_Power,
	OneUp_Power,
	Star_Power,
	FireFlower,
	Coin
};

// class declarations
class CAnimationManager;

/*
	The parent class for all collectibles
*/

class CCollectible
{
protected:
	float m_timePassed;			// time passed since creation. Used for spawning animation.
	sf::Vector2f m_growthSpeed;	// speed in pixels with which if comes out of a block
	short m_growthTime;			// time in seconds for which it comes out of the block
	TimePoint m_creationTime;	// time point of creation
	
	// Sprite variables
	sf::Vector2f m_velocity;	
	sf::Vector2f m_position;

	sf::Sprite m_collectibleSprite;
	ECollectible m_collectibleType;
	CAnimationManager* m_animationManager;

public:
	// Constructor
	CCollectible(const sf::Vector2f& initialPosition, const sf::Sprite& collectibleSprite, CAnimationManager& animationManager);

	CCollectible() = delete;	// deleting default constructor

	// getters
	inline sf::Sprite& GetSprite() { return m_collectibleSprite; };
	sf::Vector2f GetVelocity() { return m_velocity; };
	sf::Vector2f GetPosition() { return m_position; };

	// reverses velocity in x direction
	void ChangeDirection();

	// setters
	virtual inline void SetVelocity(const sf::Vector2f& newVelocity) { this->m_velocity = newVelocity; };
	virtual void SetPosition(const sf::Vector2f& newPosition);

	// update function
	virtual void Update(float frameTime) = 0;

	// draw function
	virtual inline void Draw(sf::RenderWindow& window) { window.draw(m_collectibleSprite); };

};

