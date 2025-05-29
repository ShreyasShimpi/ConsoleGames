
#include "Player.h"
#include "AssetManager.h"
#include "CInputHandler.h"
#include "CAnimationManager.h"

// defining major values 
constexpr int height = 400;
constexpr float g_gravity = 1000.0f;

constexpr float g_horizontalVelocity = 150.0f;
constexpr float g_horizontalVelocityMax = 250.0f; // when sprint

constexpr float g_jumpSpeed = 400.0f;
constexpr float g_acceleration = 400.0f;

constexpr float g_deathSpeed = 300.0f; // when dies, goes up 


CPlayer::CPlayer(CAssetManager& assetmanager, CGame& game, CAnimationManager& animationManager) :
	m_assetManager(&assetmanager), m_game(game), m_animationManager(&animationManager)
{
	// initializing mario sprite
	this->m_targetVelocity = { 0.f,0.f };
	this->m_velocity = { 0.f,0.f };
	this->m_position = { 50.0f, 184.0f };
	this->m_playerSprite = assetmanager.GetSprite(EItems::Mario_Standing_R);

	// registering key events
	onKeyPressedCB = std::bind(&CPlayer::OnKeyPressed, this, std::placeholders::_1);
	m_game.GetEventHandler().RegisterEventListner(sf::Event::KeyPressed, &onKeyPressedCB);

	onKeyReleasedCB = std::bind(&CPlayer::OnKeyReleased, this, std::placeholders::_1);
	m_game.GetEventHandler().RegisterEventListner(sf::Event::KeyReleased, &onKeyReleasedCB);

	m_state = EMarioState::Alive;
	m_isJumping = false;
}

// for smooth movement 
float Lerp(float target, float current, float deltaTime)
{
	float diff = target - current;
	if (diff > deltaTime)
	{
		return current + deltaTime;
	}
	if (diff < -deltaTime)
	{
		return current - deltaTime;
	}
	return target;
}


// when Mario dies, fn called and set the velocity, sprite, position
void CPlayer::MakeDead()
{
	m_velocity.y = -g_deathSpeed;
	m_velocity.x = 0.0f;
	m_animationManager->AnimationDeath(m_playerSprite);
	m_playerSprite.setPosition(m_position);
}

// Movement when mario dies by hitting an enemy 
void CPlayer::UpdateDeath(const float& deltaTime)
{
	m_velocity.y += g_gravity * deltaTime;

	// updating the position
	m_position.x = m_position.x + m_velocity.x * deltaTime;
	m_position.y = m_position.y + m_velocity.y * deltaTime;
	m_playerSprite.setPosition(m_position);
}

// setting position
void CPlayer::SetPosition(const sf::Vector2f position)
{
	m_position = position;
	m_playerSprite.setPosition(m_position);
}

// setting velocity
void CPlayer::SetVelocity(sf::Vector2f velocity)
{
	m_velocity = velocity;
}

// setting velocity x
void CPlayer::SetVelocityX(const float velocityX)
{
	m_velocity.x = velocityX;
}

// setting velocity y
void CPlayer::SetVelocityY(const float velocityY)
{
	m_velocity.y = velocityY;
}

// set state, alive, dead etc
void CPlayer::SetMarioState(const EMarioState& state)
{
	m_state = state;
}

// change position depending on target velocity
void CPlayer::Move(const float& deltaTime)
{
	// vertical velocity
	m_velocity.x = Lerp(m_targetVelocity.x, m_velocity.x, g_acceleration * deltaTime);

	// velocity will be changed only if target velocity is there
	if (m_targetVelocity.y != 0.0f)
	{
		m_velocity.y = m_targetVelocity.y;
	}

	// gravity
	m_velocity.y += g_gravity * deltaTime;

	// updating the position
	m_position.x = m_position.x + m_velocity.x * deltaTime;
	m_position.y = m_position.y + m_velocity.y * deltaTime;
	m_playerSprite.setPosition(m_position);
}

// updates the sprites and add animations
void CPlayer::Update(const float& deltaTime)
{
	if (m_isJumping)
	{
		if (m_targetVelocity.x > 0.0f || m_facing == EFacing::Right) // if in right
		{
			m_animationManager->SetMarioRightJump(m_playerSprite, m_isJumping);
		}
		else if (m_targetVelocity.x < 0.0f || (m_facing == EFacing::Left)) // if in left
		{
			m_animationManager->SetMarioLeftJump(m_playerSprite, m_isJumping);
		}
	}
	else // not jumping
	{
		if (m_velocity.x > 0.0f && m_targetVelocity.x > 0.0f) // right
		{
			m_animationManager->RightMarioAnimation(m_playerSprite, deltaTime);
		}
		else if (m_velocity.x < 0.0f && m_targetVelocity.x < 0.0f) // left
		{
			m_animationManager->LeftMarioAnimation(m_playerSprite, deltaTime);
		}
		else if (m_velocity.x < 0.0f && m_targetVelocity.x > 0.0f) // right drag
		{
			m_animationManager->SetMarioRightDrag(m_playerSprite);
		}
		else if (m_velocity.x > 0.0f && m_targetVelocity.x < 0.0f) // left drag
		{
			m_animationManager->SetMarioLeftDrag(m_playerSprite);
		}
		else // if nothing 
		{
			if (m_facing == EFacing::Left) // left standing
			{
				m_animationManager->SetMarioLeftStatic(m_playerSprite);
			}
			else if (m_facing == EFacing::Right) // right standing
			{
				m_animationManager->SetMarioRightStatic(m_playerSprite);
			}
		}
	}

	Move(deltaTime);

	// setting y zero
	if (m_isJumping)
	{
		m_targetVelocity.y = 0.0f;
	}
}

// drawing Mario
void CPlayer::Render(sf::RenderTarget& target)
{
	target.draw(this->m_playerSprite);
}


void CPlayer::OnKeyPressed(sf::Event event)
{
	CInputHandler* inputHandler = &m_game.GetInputHandler();
	
	//horizontal movement Player
	if (inputHandler->IsPressed(sf::Keyboard::LShift))
	{
		if (inputHandler->IsPressed(sf::Keyboard::A) && inputHandler->IsPressed(sf::Keyboard::D))
		{
			m_targetVelocity.x = 0.0f;
			m_facing = EFacing::Right;
		}
		else if (inputHandler->IsPressed(sf::Keyboard::A)) // left
		{
			m_targetVelocity.x = -g_horizontalVelocityMax;
			m_facing = EFacing::Left;
		}
		else if (inputHandler->IsPressed(sf::Keyboard::D)) // right
		{
			m_targetVelocity.x = g_horizontalVelocityMax;
			m_facing = EFacing::Right;
		}
		else
		{
			m_targetVelocity.x = 0.0f;
		}
	}
	else
	{
		if (inputHandler->IsPressed(sf::Keyboard::A) && inputHandler->IsPressed(sf::Keyboard::D))
		{
			m_targetVelocity.x = 0.0f;
			m_facing = EFacing::Right;
		}
		else if (inputHandler->IsPressed(sf::Keyboard::A))
		{
			m_targetVelocity.x = -g_horizontalVelocity;
			m_facing = EFacing::Left;
		}
		else if (inputHandler->IsPressed(sf::Keyboard::D))
		{
			m_targetVelocity.x = g_horizontalVelocity;
			m_facing = EFacing::Right;
		}
		else
		{
			m_targetVelocity.x = 0.0f;
		}
	}

	
	// jumping
	if (inputHandler->IsPressed(sf::Keyboard::Space) && !inputHandler->IsRepeating(sf::Keyboard::Space) && !m_isJumping)
	{
		m_targetVelocity.y = -g_jumpSpeed;
		m_isJumping = true;
	}
}

void CPlayer::OnKeyReleased(sf::Event event)
{
	//Move Player
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_targetVelocity.x = 0.0f;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_targetVelocity.y = 0.0f;
	}
}

CPlayer::~CPlayer()
{

}