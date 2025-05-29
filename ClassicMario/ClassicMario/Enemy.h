#pragma once
#include"SFML/Graphics.hpp"
#include"Player.h"

//enum used for direction
enum class EDirection
{
	Left, Right
};

//abstract class for enemies
class CEnemy
{
protected:
	sf::Sprite m_enemySprite;// sprite corresponding to enemy
	sf::Vector2f m_velocity;
	EDirection m_direction = EDirection::Left;
	int m_deathScore = 100;//death score corresponding to the specific enemy
public:
	//Setters
	void SetDirection(EDirection direction);
	void SetVelocity(sf::Vector2f speed);
	void SetSprite(sf::Sprite enemySprite);
	void SetScore(int score);
	void SetPosition(sf::Vector2f pos);

	//Getters
	inline sf::Sprite& GetSprite() { return m_enemySprite; };
	sf::Vector2f GetVelocity() { return m_velocity; }
	void Draw(sf::RenderWindow& window);
	inline sf::Vector2f GetPosition() { return m_enemySprite.getPosition(); }

	//If you hit the enemy from top, state changes accordingly
	virtual void HitFromTop(CPlayer& mario) = 0;

	//if the enemy is hit from the bottom, the state changes accordingly
	virtual void HitFromBottom(CPlayer& mario) = 0;

	//if fireball hits the enemy, the state changes accordingly
	virtual void HitFromFireball(CPlayer& mario) = 0;

	//checks if the enemy is alive
	virtual bool IsAlive() const = 0;

	//Changing enemy direction in x direction
	virtual void ChangeDirection() = 0;

	//Update function for updating states, position and velocities
	virtual void Update(float delta_time) = 0;

	//void UpdateDeathPoints(CPlayer& mario);


};

