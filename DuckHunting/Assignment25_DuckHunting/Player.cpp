// external includes
#include <iostream>
#include <sstream>

// internal includes
#include "Player.h"
#include "Defines.h"
#include "Engine.h"


CShooter::CShooter(CEngine& engine)
{
	m_isBulletShot = false;

	// key pressed
	m_playerKeyPressedListnerCB = std::bind(&CShooter::PlayerKeyPressedListner, this, std::placeholders::_1);
	engine.GetEventHandler().RegisterEventListner(sf::Event::EventType::KeyPressed, &m_playerKeyPressedListnerCB);

	// key released
	m_playerKeyReleasedListnerCB = std::bind(&CShooter::PlayerKeyReleasedListner, this, std::placeholders::_1);
	engine.GetEventHandler().RegisterEventListner(sf::Event::EventType::KeyReleased, &m_playerKeyReleasedListnerCB);

	// mouse clicked
	m_playerMouseClickedListnerCB = std::bind(&CShooter::PlayerMouseClickedListner, this, std::placeholders::_1);
	engine.GetEventHandler().RegisterEventListner(sf::Event::EventType::MouseButtonPressed, &m_playerMouseClickedListnerCB);

	// mouse clicked released
	m_playerMouseClickReleasedListnerCB = std::bind(&CShooter::PlayerMouseClickReleasedListner, this, std::placeholders::_1);
	engine.GetEventHandler().RegisterEventListner(sf::Event::EventType::MouseButtonReleased, &m_playerMouseClickReleasedListnerCB);

	// mouse moved
	m_playerMouseMovedListnerCB = std::bind(&CShooter::PlayerMouseMovedListner, this, std::placeholders::_1);
	engine.GetEventHandler().RegisterEventListner(sf::Event::EventType::MouseMoved, &m_playerMouseMovedListnerCB);

}

// listener functions that goes into event handler
void CShooter::PlayerKeyPressedListner(sf::Event event)
{
	HandleKeyPress(event, m_keyInput);
}

void CShooter::PlayerKeyReleasedListner(sf::Event event)
{
	HandleKeyRelease(event, m_keyInput);
}

void CShooter::PlayerMouseClickedListner(sf::Event event)
{
	HandleMouseClick(event, m_mouseInput);
}

void CShooter::PlayerMouseClickReleasedListner(sf::Event event)
{
	HandleMouseClickReleased(event, m_mouseInput);
}

void CShooter::PlayerMouseMovedListner(sf::Event event)
{
	HandleMouseMoved(event, m_mouseInput);
}

// actual key press action
void CShooter::KeyPressAction(const float& deltaTime)
{
}

void CShooter::MouseClickeAction(const float& deltaTime)
{
	if (m_mouseInput.m_left.isPressed && !m_mouseInput.m_left.isHeld)
	{
		m_mouseInput.m_left.isHeld = true;
		m_isBulletShot = true;
		m_crosshairSprite.setColor(sf::Color::Green);
	}
	else
	{
		m_crosshairSprite.setColor(sf::Color::Red);
		m_isBulletShot = false;
	}
}

void CShooter::MouseMovedAction(const float& deltaTime)
{
}


void CShooter::InitShooter(float paddle1posX, float paddle1posY, float paddle2posX, float paddle2posY)
{
	// setting cross hair texture
	std::stringstream ss;
	ss << "Sprites/crosshair.png";

	if (m_crosshairTexture.loadFromFile(ss.str()))
	{
		m_crosshairSprite.setTexture(m_crosshairTexture);
	}
	else
	{
		std::cout << "Failed to load Texture : " << ss.str() << "\n";
	}
	m_crosshairSprite.setScale({0.5f, 0.5f});
}

void CShooter::InputAction(const float& deltaTime)
{
	KeyPressAction(deltaTime);
	MouseClickeAction(deltaTime);
	MouseMovedAction(deltaTime);
}

void CShooter::Move(const float& deltaTime)
{
	// move cross hair according to mouse 
	m_crosshairSprite.setPosition(float(m_mouseInput.m_mousePosition.x - m_crosshairSprite.getGlobalBounds().width/2), float(m_mouseInput.m_mousePosition.y - m_crosshairSprite.getGlobalBounds().height / 2));
}

void CShooter::Update(const float& deltaTime)
{
	Move(deltaTime); // delta passed is in seconds
}

void CShooter::Render(sf::RenderTarget& target)
{
	target.draw(m_crosshairSprite);
}