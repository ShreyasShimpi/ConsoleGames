// external includes
#include <iostream>
#include <sstream>

// internal includes
#include "Player.h"
#include "Defines.h"
#include "Engine.h"


CPaddles::CPaddles(CEngine& engine)
{
	m_paddle1Velocity = 0.0f;
	m_paddle1TargetVelocity = 0.0f;
	m_paddle2Velocity = 0.0f;
	m_paddle2TargetVelocity = 0.0f;

	m_playerKeyPressedListnerCB = std::bind(&CPaddles::PlayerKeyPressedListner, this, std::placeholders::_1);
	engine.GetEventHandler().RegisterEventListner(sf::Event::EventType::KeyPressed, &m_playerKeyPressedListnerCB);

	m_playerKeyReleasedListnerCB = std::bind(&CPaddles::PlayerKeyReleasedListner, this, std::placeholders::_1);
	engine.GetEventHandler().RegisterEventListner(sf::Event::EventType::KeyReleased, &m_playerKeyReleasedListnerCB);
}

// listener functions that goes into event handler
void CPaddles::PlayerKeyPressedListner(sf::Event event)
{
	HandleKeyPress(event, m_input);
}

void CPaddles::PlayerKeyReleasedListner(sf::Event event)
{
	HandleKeyRelease(event, m_input);
}

// actual key press action
void CPaddles::KeyPressAction(const float& deltaTime)
{
	// game play movement key events : W and S
	if (m_input.m_w.isPressed && m_input.m_s.isPressed)
	{
		m_paddle1TargetVelocity = 0.0f;
	}
	else if (m_input.m_w.isPressed)
	{
		m_paddle1TargetVelocity = -MAXSPEED;
	}
	else if (m_input.m_s.isPressed)
	{
		m_paddle1TargetVelocity = MAXSPEED;
	}
	else
	{
		m_paddle1TargetVelocity = 0.0f;// stopping is taken care of
	}

	// game play movement key events : A and D
	if (m_input.m_up.isPressed && m_input.m_down.isPressed)
	{
		m_paddle2TargetVelocity = 0.0f;
	}
	else if (m_input.m_up.isPressed)
	{
		m_paddle2TargetVelocity = -MAXSPEED;
	}
	else if (m_input.m_down.isPressed)
	{
		m_paddle2TargetVelocity = MAXSPEED;
	}
	else
	{
		m_paddle2TargetVelocity = 0.0f; // stopping is taken care of
	}

	m_paddle1Velocity = Lerp(m_paddle1Velocity, m_paddle1TargetVelocity, ACCELERATION * deltaTime);
	m_paddle2Velocity = Lerp(m_paddle2Velocity, m_paddle2TargetVelocity, ACCELERATION * deltaTime);
}

// actual key release action
void CPaddles::KeyReleaseAction(const float& deltaTime)
{
	// when all the keys are released then only stop the animation
	if (!m_input.m_w.isPressed && !m_input.m_s.isPressed && !m_input.m_up.isPressed && !m_input.m_down.isPressed)
	{
		m_paddle1TargetVelocity = 0.0f;
		m_paddle2TargetVelocity = 0.0f;
	}
}


void CPaddles::CreatePaddles()
{
	m_paddle1.setSize({15.0f, 90.0f});
	m_paddle1.setFillColor(sf::Color::Blue);
	m_paddle1.setOutlineColor(sf::Color::White);
	m_paddle1.setOutlineThickness(-2.0f);

	m_paddle2.setSize({ 15.0f, 90.0f });
	m_paddle2.setFillColor(sf::Color::Red);
	m_paddle2.setOutlineColor(sf::Color::White);
	m_paddle2.setOutlineThickness(-2.0f);
}

void CPaddles::InitPaddles(float paddle1posX, float paddle1posY, float paddle2posX, float paddle2posY)
{
	// initialize paddles
	CreatePaddles();
	m_paddle1.setPosition({ paddle1posX, paddle1posY });
	m_paddle2.setPosition({ paddle2posX, paddle2posY });
}

void CPaddles::KeyAction(const float& deltaTime)
{
	KeyPressAction(deltaTime);
}

void CPaddles::SetPaddle1Velocity(float velocity)
{
	m_paddle1TargetVelocity = velocity;
}

void CPaddles::SetPaddle2Velocity(float velocity)
{
	m_paddle2TargetVelocity = velocity;
}

void CPaddles::SetPaddle1Position(sf::Vector2f position)
{
	m_paddle1.setPosition(position);
}

void CPaddles::SetPaddle2Position(sf::Vector2f position)
{
	m_paddle2.setPosition(position);
}

void CPaddles::Move(const float& deltaTime)
{
	m_paddle1.move({ 0.0f, m_paddle1Velocity * deltaTime });
	m_paddle2.move({ 0.0f, m_paddle2Velocity * deltaTime });
}

void CPaddles::Update(const float& deltaTime)
{
	Move(deltaTime); // delta passed is in seconds
}

void CPaddles::Render(sf::RenderTarget& target)
{
	target.draw(m_paddle1);
	target.draw(m_paddle2);
}