#include "Enemy.h"

CEnemy::CEnemy()
{
	m_characterType = ECharacterType::ENEMY;
}

void CEnemy::InitTexture()
{
	// Load image from files (left)
	for (int i = 0; i < ENEMYRUNSPRITES; ++i)
	{
		std::stringstream ss;
		ss << "Sprites/Enemy/enemy_left(" << i << ").png";

		sf::Texture texture;

		if (texture.loadFromFile(ss.str()))
		{
			m_leftTexture.push_back(texture);
		}
		else
		{
			std::cout << "Failed to load Texture : " << ss.str() << "\n";
		}
	}

	// Load image from files (left)
	for (int i = 0; i < ENEMYRUNSPRITES; ++i)
	{
		std::stringstream ss;
		ss << "Sprites/Enemy/enemy_right(" << i << ").png";

		sf::Texture texture;

		if (texture.loadFromFile(ss.str()))
		{
			m_rightTexture.push_back(texture);
		}
		else
		{
			std::cout << "Failed to load Texture : " << ss.str() << "\n";
		}
	}
}

void CEnemy::InitSprite()
{
	m_sprite.setTexture(m_rightTexture[0]);
}


void CEnemy::InitCharacter(float initialPositionX, float initialPositionY)
{
	InitTexture();
	InitSprite();

	m_position.x = initialPositionX;
	m_position.y = initialPositionY;

	m_sprite.setPosition(m_position.x, m_position.y);
	
	// to make it go thought the tiles easily
	m_sprite.setScale({ 0.95f, 0.95f });

	// set the velocity of the enemy
	m_velocity.x = ENEMYSPEED;
	m_isAnimationRunning = true;
}

void CEnemy::Move(const float& deltaTime)
{
	m_position.x = m_position.x + m_velocity.x * deltaTime;

	//m_sprite.setPosition(m_position);
	SetPosition(m_position);
}


void CEnemy::RunAnimation(float animationDelay, const float& deltaTime)
{
	// used for animation
	m_totalTime += deltaTime; // delta m_time is in seconds
	m_nextFrameDelay = animationDelay / m_rightTexture.size();

	if (m_isAnimationRunning)
	{
		int index = static_cast<int>(m_totalTime / m_nextFrameDelay) % m_rightTexture.size();
		if (m_velocity.x > 0.0f)
		{
			m_sprite.setTexture(m_rightTexture[index]);
		}
		else
		{
			m_sprite.setTexture(m_leftTexture[index]);
		}
	}
}

void CEnemy::Update(const float& deltaTime)
{
	Move(deltaTime); // delta passed is in seconds
	RunAnimation(ENEMY_ANIMATION_DELAY, deltaTime);
}

void CEnemy::Render(sf::RenderTarget& target)
{
	target.draw(m_sprite);
}
