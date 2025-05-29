// external includes
#include <iostream>
#include <sstream>

// internal includes
#include "Player.h"
#include "Engine.h"


CPlayer::CPlayer(CEngine& engine)
{
	m_hasKey = false;
	m_isDeathAnimationRunning = true;
	m_characterType = ECharacterType::PLAYER;

	m_playerKeyPressedListnerCB = std::bind(&CPlayer::PlayerKeyPressedListner, this, std::placeholders::_1);
	engine.GetEventHandler().RegisterEventListner(sf::Event::EventType::KeyPressed, &m_playerKeyPressedListnerCB);

	m_playerKeyReleasedListnerCB = std::bind(&CPlayer::PlayerKeyReleasedListner, this, std::placeholders::_1);
	engine.GetEventHandler().RegisterEventListner(sf::Event::EventType::KeyReleased, &m_playerKeyReleasedListnerCB);
}

// listener functions that goes into event handler
void CPlayer::PlayerKeyPressedListner(sf::Event event)
{
	HandleKeyPress(event, m_input);
}
void CPlayer::PlayerKeyReleasedListner(sf::Event event)
{
	HandleKeyRelease(event, m_input);
}

// actual key press action
void CPlayer::KeyPressAction(const float& deltaTime)
{
	// game play movement key events : W and S
	if (m_input.m_w.isPressed && m_input.m_s.isPressed)
	{
		SetTargetVelocityY(0.0f);

		StartAnimation();
	}
	else if (m_input.m_w.isPressed)
	{
		SetTargetVelocityY(-MAXSPEED);
		SetPlayerMovementTexture();
		StartAnimation();
	}
	else if (m_input.m_s.isPressed)
	{
		SetTargetVelocityY(MAXSPEED);
		SetPlayerMovementTexture();
		StartAnimation();
	}
	else
	{
		SetTargetVelocityY(0.0f); // stopping is taken care of
	}

	// game play movement key events : A and D
	if (m_input.m_a.isPressed && m_input.m_d.isPressed)
	{
		SetTargetVelocityX(0.0f);
		StartAnimation();
	}
	else if (m_input.m_a.isPressed)
	{
		SetTargetVelocityX(-MAXSPEED);
		SetPlayerMovementTexture();
		StartAnimation();
	}
	else if (m_input.m_d.isPressed)
	{
		SetTargetVelocityX(MAXSPEED);
		SetPlayerMovementTexture();
		StartAnimation();
	}
	else
	{
		SetTargetVelocityX(0.0f); // stopping is taken care of
	}

	//m_velocity.x = Lerp(m_velocity.x, m_targetVelocity.x, ACCELERATION * deltaTime);
	//m_velocity.y = Lerp(m_velocity.y, m_targetVelocity.y, ACCELERATION * deltaTime);
	m_velocity.x = m_targetVelocity.x;
	m_velocity.y = m_targetVelocity.y;
}

// actual key release action
void CPlayer::KeyReleaseAction(const float& deltaTime)
{
	// when all the keys are released then only stop the animation
	if (!m_input.m_w.isPressed && !m_input.m_s.isPressed && !m_input.m_a.isPressed && !m_input.m_d.isPressed)
	{
		SetTargetVelocityX(0.0f);
		SetTargetVelocityY(0.0f);
		StopAnimation();
	}
}

void CPlayer::InitTexture()
{
	// Load image from files
	for (int i = 0; i < RUNSPRITES; ++i)
	{
		std::stringstream ss;
		ss << "Sprites/Player/player_down(" << i << ").png";

		sf::Texture texture;

		if (texture.loadFromFile(ss.str()))
		{
			m_texture.push_back(texture);
		}
		else
		{
			std::cout << "Failed to load Texture : " << ss.str() << "\n";
		}
	}

	// load death sprites
	for (int i = 0; i < DEATHSPRITES; ++i)
	{
		std::stringstream ss;
		ss << "Sprites/Player/player_death(" << i << ").png";

		sf::Texture texture;

		if (texture.loadFromFile(ss.str()))
		{
			m_deathTexture.push_back(texture);
		}
		else
		{
			std::cout << "Failed to load Texture : " << ss.str() << "\n";
		}
	}
}

void CPlayer::InitSprite()
{
	m_sprite.setTexture(m_texture[0]);
}


void CPlayer::InitCharacter(float initialPositionX, float initialPositionY)
{
	InitTexture();
	InitSprite();

	m_position.x = initialPositionX;
	m_position.y = initialPositionY;

	m_sprite.setPosition(m_position.x, m_position.y);
}

void CPlayer::KeyAction(const float& deltaTime)
{
	KeyPressAction(deltaTime);
	KeyReleaseAction(deltaTime);
}

void CPlayer::Move(const float& deltaTime)
{
	m_position.x = m_position.x + m_velocity.x * deltaTime;
	m_position.y = m_position.y + m_velocity.y * deltaTime;

	SetPosition(m_position);
}


void CPlayer::RunAnimation(float animationDelay, const float& deltaTime)
{
	m_totalTime += deltaTime;
	m_nextFrameDelay = animationDelay / m_texture.size();

	if (m_isAnimationRunning)
	{
		int index = static_cast<int>(m_totalTime / m_nextFrameDelay) % m_texture.size();
		m_sprite.setTexture(m_texture[index]);
	}
}

void CPlayer::RunDeathAnimation(float animationDelay, const float& deltaTime)
{
	m_totalTime += deltaTime;
	m_nextFrameDelay = animationDelay / m_deathTexture.size();

	if (m_isDeathAnimationRunning)
	{
		int index = static_cast<int>(m_totalTime / m_nextFrameDelay) % m_deathTexture.size();
		m_sprite.setTexture(m_deathTexture[index]);

		if (index == m_deathTexture.size() - 1)
		{
			m_isDeathAnimationRunning = false;
		}
	}
}

void CPlayer::StartAnimation()
{
	m_isAnimationRunning = true;
}

void CPlayer::StopAnimation()
{
	m_isAnimationRunning = false;
	m_totalTime = 0.0f;
}

void CPlayer::SetPlayerMovementTexture()
{
	m_texture.clear();

	for (int i = 0; i < RUNSPRITES; ++i)
	{
		std::stringstream ss;

		if (m_input.m_w.isPressed)
		{
			ss << "Sprites/Player/player_up(" << i << ").png";
		}

		else if (m_input.m_s.isPressed)
		{
			ss << "Sprites/Player/player_down(" << i << ").png";
		}

		else if (m_input.m_a.isPressed)
		{
			ss << "Sprites/Player/player_left(" << i << ").png";
		}

		else if (m_input.m_d.isPressed)
		{
			ss << "Sprites/Player/player_right(" << i << ").png";
		}

		sf::Texture texture;

		if (texture.loadFromFile(ss.str()))
		{
			m_texture.push_back(texture);
		}
		else
		{
			std::cout << "Failed to load Texture : " << ss.str() << "\n";
		}
	}
}
void CPlayer::AcquireKey()
{
	std::cout << "got the key!\n";
	m_hasKey = true;
}

void CPlayer::Update(const float& deltaTime)
{
	// used for animation
	//m_totalTime += deltaTime; // delta m_time is in seconds

	Move(deltaTime); // delta passed is in seconds
	RunAnimation(PLAYER_ANIMATION_DELAY, deltaTime);
}

void CPlayer::Render(sf::RenderTarget& target)
{
	target.draw(m_sprite);
}
