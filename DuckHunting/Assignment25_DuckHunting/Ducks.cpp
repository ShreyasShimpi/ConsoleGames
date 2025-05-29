// external includes
#include "Ducks.h"

// internal includes
#include <iostream>
#include <sstream>


CDucks::CDucks()
{
	m_isDeathAnimationRunning = false;
	m_isDead = false;
	m_angle = 0;

	// inti texture and sprite
	InitTexture();
	InitSprite();

	m_nextFrameDelay = DUCK_ANIMATION_DELAY / m_flightTexture.size();
}

void CDucks::InitTexture()
{
	
	// flight
	for (int i = 0; i < 3; ++i)
	{
		std::stringstream ss;
		ss << "Sprites/duck/black_duck(" << i << ").png";

		sf::Texture texture;

		if (texture.loadFromFile(ss.str()))
		{
			m_flightTexture.push_back(texture);
		}
		else
		{
			std::cout << "Failed to load Texture : " << ss.str() << "\n";
		}
	}

	// death
	std::stringstream ss;
	ss << "Sprites/duck/black_duck(10).png";

	if (m_deathTexture.loadFromFile(ss.str()))
	{
	}
	else
	{
		std::cout << "Failed to load Texture : " << ss.str() << "\n";
	}
}

void CDucks::InitSprite()
{
	m_duckSprite.setTexture(m_flightTexture[0]);
}


void CDucks::SetDuckProperties(float PositionX, float PositionY, int angle)
{
	m_duckSprite.setPosition(PositionX, PositionY);
	m_angle = angle;
}

void CDucks::Move(const float& deltaTime)
{
	if (!m_isDeathAnimationRunning)
	{
		float offsetX = DUCKVELOCITY * float(std::cos(ToRadian(m_angle))) * deltaTime;
		float offsetY = DUCKVELOCITY * float(std::sin(ToRadian(m_angle))) * deltaTime;
		m_duckSprite.move(offsetX, offsetY);
	}
	else
	{
		float offsetY = DUCKDOWNVELOCITY * deltaTime;
		m_duckSprite.move(0.0f, offsetY); // downward fall
	}
	
}


void CDucks::RunAnimation(const float& deltaTime)
{
	// used for animation
	m_totalTime += deltaTime; // delta m_time is in seconds

	// cycle through index
	int index = static_cast<int>(m_totalTime / m_nextFrameDelay) % m_flightTexture.size();

	// going left
	if (m_angle <= 270 && m_angle >=  180)
	{
		m_duckSprite.setTexture(m_flightTexture[index]);
		m_duckSprite.setScale({ -1.0f, 1.0f });
	}
	// going right
	else if(m_angle >= 270 && m_angle <= 360)
	{
		m_duckSprite.setTexture(m_flightTexture[index]);
		m_duckSprite.setScale({ 1.0f, 1.0f });
	}
	
}

void CDucks::RunDeathAnimation(const float& deltaTime)
{

	m_duckSprite.setTexture(m_deathTexture);
}

void CDucks::SetDuckLife(bool state)
{
	m_isDeathAnimationRunning = state;
}

void CDucks::Update(const float& deltaTime)
{
	Move(deltaTime);// delta passed is in seconds

	if (!m_isDeathAnimationRunning)
	{
		RunAnimation(deltaTime);
	}
	else
	{
		RunDeathAnimation(deltaTime);
	}
}

void CDucks::Render(sf::RenderTarget& target)
{
	target.draw(m_duckSprite);
}
