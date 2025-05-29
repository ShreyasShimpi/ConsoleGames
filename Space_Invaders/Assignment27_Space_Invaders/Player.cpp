// external includes
#include <iostream>
#include <sstream>

// internal includes
#include "Player.h"
#include "AssetManager.h"
#include "Defines.h"
#include "Engine.h"


CPlayer::CPlayer(const sf::Vector2f playerPosition, CEngine& engine, CAssetManager& assetmanager)
	: m_assetManager(&assetmanager)
{
	// key pressed
	m_playerKeyPressedListnerCB = std::bind(&CPlayer::PlayerKeyPressedListner, this, std::placeholders::_1);
	engine.GetEventHandler().RegisterEventListner(sf::Event::EventType::KeyPressed, &m_playerKeyPressedListnerCB);

	// key released
	m_playerKeyReleasedListnerCB = std::bind(&CPlayer::PlayerKeyReleasedListner, this, std::placeholders::_1);
	engine.GetEventHandler().RegisterEventListner(sf::Event::EventType::KeyReleased, &m_playerKeyReleasedListnerCB);


	// player construct
	m_playerSprite = m_assetManager->GetSprite(ESprite::Player);
	m_playerSprite.setOrigin({ m_playerSprite.getGlobalBounds().width / 2, m_playerSprite.getGlobalBounds().height / 2 });
	m_playerSprite.setPosition(playerPosition);

	// bullet construct
	m_bulletSprite = m_assetManager->GetSprite(ESprite::Player_Bullet);
	m_bulletSprite.setOrigin({ m_bulletSprite.getGlobalBounds().width / 2, m_bulletSprite.getGlobalBounds().height / 2 });
	m_bulletSprite.setPosition(playerPosition);

	// settings
	m_bulletVelocity =  0.0f;
	m_playerVelocity =  0.0f;
	m_isBulletShot = false;
}

// listener functions that goes into event handler
void CPlayer::PlayerKeyPressedListner(sf::Event event)
{
	HandleKeyPress(event, m_keyInput);
}

void CPlayer::PlayerKeyReleasedListner(sf::Event event)
{
	HandleKeyRelease(event, m_keyInput);
}

// actual key press action
void CPlayer::KeyPressAction(const float& deltaTime)
{
	// game play movement key events : W and S
	if (m_keyInput.m_a.isPressed && m_keyInput.m_d.isPressed)
	{
		m_playerVelocity = 0.0f;
	}
	else if (m_keyInput.m_a.isPressed)
	{
		m_playerVelocity = -g_playerSpeed;
	}
	else if (m_keyInput.m_d.isPressed)
	{
		m_playerVelocity = g_playerSpeed;;
	}
	else
	{
		m_playerVelocity = 0.0f;
	}

	// bullet shoot
	if (m_keyInput.m_space.isPressed && !m_isBulletShot)
	{
		m_bulletSprite.setPosition(m_playerSprite.getPosition());
		m_bulletVelocity = -g_playerBulletSpeed;
		m_isBulletShot = true;
	}
}

void CPlayer::SetPlayerPosition(const sf::Vector2f& position)
{
	m_playerSprite.setPosition(position);
}

void CPlayer::ResetBullet()
{
	m_bulletVelocity = 0.0f;
	m_bulletSprite.setPosition(m_playerSprite.getPosition());
	m_isBulletShot = false;
}

void CPlayer::Move(const float& deltaTime)
{
	// player movement
	m_playerSprite.move( m_playerVelocity * deltaTime , 0.0f );

	// bullet movement
	if (m_isBulletShot)
	{
		m_bulletSprite.move( 0.0f , m_bulletVelocity * deltaTime );
	}
}

void CPlayer::Update(const float& deltaTime)
{
	KeyPressAction(deltaTime);
	Move(deltaTime); // delta passed is in seconds
}

void CPlayer::Render(sf::RenderTarget& target)
{
	if (m_isBulletShot)
	{
		target.draw(m_bulletSprite);
	}
	target.draw(m_playerSprite);
}