// external includes
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include <cmath>
#include <fstream>

// internal includes
#include "SpawnManager.h"
#include "Engine.h"

CSpawnManager::CSpawnManager(CEngine& engine, unsigned int width, unsigned int height)
	:m_engine(engine)
{
	m_player1Score = 0;
	m_player2Score = 0;

	m_player1Shots = TOTAL_SHOTS;
	m_player2Shots = TOTAL_SHOTS;

	m_gameState = EGameState::MainMenu;

	// loading foreground
	LoadForeground();

	// init player
	m_shooter = std::make_unique<CShooter>(m_engine);
	m_shooter->InitShooter(5.0f ,  HEIGHT / 2, WIDTH - 20.0f, HEIGHT/2);

	// create duck
	m_duck = std::make_unique<CDucks>();
	RandomizeDuck();
}

void CSpawnManager::LoadForeground()
{
	std::stringstream ss;
	ss << "Sprites/dh_foreground.png";

	if (m_fgTexture.loadFromFile(ss.str()))
	{
		m_fgSprite.setTexture(m_fgTexture);
	}
	else
	{
		std::cout << "Failed to load Texture : " << ss.str() << "\n";
	}
}


void CSpawnManager::SetGameState(EGameState state)
{
	m_gameState = state;
}

void CSpawnManager::ResetGameProperties()
{
	m_player1Score = 0;
	m_player2Score = 0;

	m_player1Shots = TOTAL_SHOTS;
	m_player2Shots = TOTAL_SHOTS;

	RandomizeDuck();
}

void CSpawnManager::UpdateSpawns(const float& deltaTime)
{
	switch (m_gameState)
	{
	case EGameState::MainMenu:
	{
		if (m_shooter->GetKeyInput().m_space.isPressed)
		{
			m_gameState = EGameState::Player1Turn;
		}
	}
	break;
	case EGameState::Player1Turn:
	{
		// take player input
		m_shooter->InputAction(deltaTime);

		// update the player
		m_shooter->Update(deltaTime);

		// check collision
		ChcekBoundaryforDuck();
		if (m_shooter->IsBulletShot())
		{
			ChcekBulletDuckColiision();
			m_player1Shots--;
		}

		// update the duck
		m_duck->Update(deltaTime);

		if (m_player1Shots == 0)
		{
			m_gameState = EGameState::TurnOver;
		}
	}
	break;
	case EGameState::Player2Turn:
	{
		// take player input
		m_shooter->InputAction(deltaTime);

		// update the player
		m_shooter->Update(deltaTime);

		// check collision
		ChcekBoundaryforDuck();
		if (m_shooter->IsBulletShot())
		{
			ChcekBulletDuckColiision();
			m_player2Shots--;
		}

		// update the duck
		m_duck->Update(deltaTime);

		if (m_player2Shots <= 0)
		{
			m_gameState = EGameState::GameOver;
		}
	}
	break;
	case EGameState::DuckHit:
	{

	}
	break;
	case EGameState::TurnOver:
	{
		if (m_shooter->GetKeyInput().m_space.isPressed)
		{
			m_gameState = EGameState::Player2Turn;
		}
	}
	break;
	case EGameState::GameOver:
	{
		if (m_shooter->GetKeyInput().m_space.isPressed)
		{
			m_gameState = EGameState::Player1Turn;
		}
	}
	break;
	default:
		break;
	}
}

void CSpawnManager::RenderSpawns(sf::RenderTarget& target)
{

	switch (m_gameState)
	{
	case EGameState::MainMenu:
	{
		// Load Foreground (top)
		target.draw(m_fgSprite);

		// text
		DisplayMessage("DUCK HUNTING", sf::Color::Black, { WIDTH / 2,  50.0f  }, 96, target);
		DisplayMessage("-- Press SPACE to Start --", sf::Color::Black, { WIDTH / 2, HEIGHT / 2 - 100.0f }, 24, target);
		DisplayMessage("-- Press ESC to Exit --", sf::Color::Black, { WIDTH / 2, HEIGHT / 2 - 70.0f }, 24, target);

		DisplayMessage("MOUSE : MOVEMENT | LEFT-CLICK : SHOOT ", sf::Color::White, { WIDTH/ 2, HEIGHT - 20.0f }, 24, target);
	
	}
	break;
	case EGameState::Player1Turn:
	{
		// shooter
		m_shooter->Render(target);

		// duck
		m_duck->Render(target);

		// foreground (top)
		target.draw(m_fgSprite);

		// text
		DisplayMessage("SCORE : " + std::to_string(m_player1Score), sf::Color::White, { WIDTH - 100.0f,  HEIGHT - 55.0f }, 24, target);
		DisplayMessage(std::to_string(m_player1Shots), sf::Color::White, { 90.0f, HEIGHT - 55.0f }, 24, target);
		DisplayMessage("BULLETS", sf::Color::White, { 90.0f, HEIGHT - 92.0f }, 12, target);
		DisplayMessage("PLAYER 1 PLAYING", sf::Color::White, { WIDTH/2 - 15.0f, HEIGHT - 55.0f }, 24, target);
	}
	break;
	case EGameState::Player2Turn:
	{
		// shooter
		m_shooter->Render(target);

		// duck
		m_duck->Render(target);

		// foreground (top)
		target.draw(m_fgSprite);

		// text
		DisplayMessage("SCORE : " + std::to_string(m_player2Score), sf::Color::White, { WIDTH - 100.0f,  HEIGHT - 55.0f }, 24, target);
		DisplayMessage(std::to_string(m_player2Shots), sf::Color::White, { 90.0f, HEIGHT - 55.0f }, 24, target);
		DisplayMessage("BULLETS", sf::Color::White, { 90.0f, HEIGHT - 92.0f }, 12, target);
		DisplayMessage("PLAYER 2 PLAYING", sf::Color::White, { WIDTH/2 - 15.0f, HEIGHT - 55.0f }, 24, target);
	}
	break;
	case EGameState::DuckHit:
	{

	}
	break;
	case EGameState::TurnOver:
	{
		// foreground (top)
		target.draw(m_fgSprite);

		// text
		DisplayMessage("Player 1 Turn Over", sf::Color::Black, { WIDTH / 2 , 50.0f }, 48, target);
		DisplayMessage("Press SPACE to Continue ", sf::Color::Black, { WIDTH / 2, HEIGHT / 2 - 100.0f }, 24, target);
	}
	break;
	case EGameState::GameOver:
	{
		// foreground (top)
		target.draw(m_fgSprite);

		// text
		DisplayMessage("GAME OVER", sf::Color::Black, { WIDTH / 2,  50.0f }, 96, target);
		DisplayMessage("Player 1 Score : " + std::to_string(m_player1Score), sf::Color::Black, { WIDTH / 2, 150.0f }, 32, target);
		DisplayMessage("Player 2 Score : " + std::to_string(m_player2Score), sf::Color::Black, { WIDTH / 2, 180.0f }, 32, target);
		
		DisplayMessage("-- Press SPACE to PlayAgain --", sf::Color::Black, { WIDTH / 2, HEIGHT / 2 + 20.0f }, 24, target);
		DisplayMessage("-- Press ESC to Exit --", sf::Color::Black, { WIDTH / 2, HEIGHT / 2 + 50.0f }, 24, target);
	}
	break;
	default:
		break;
	}
}

void CSpawnManager::RandomizeDuck()
{
	srand(time(0));

	int positionX = rand() % WIDTH + 1;
	int angle = 0;
	if (positionX >= 0 && positionX < WIDTH / 3) // left part ( angle 285 - 345 )
	{
		angle = (rand() % (345 - 285 + 1)) + 285;
	}
	else if(positionX >= WIDTH / 3 && positionX < 2 * WIDTH / 3) // middle part ( angle 195 - 345 )
	{
		angle = (rand() % (345 - 195 + 1)) + 195;
	}
	else // right part ( angle 195 - 255 )
	{
		angle = (rand() % (255 - 195 + 1)) + 195;
	}

	// init duck
	m_duck->SetDuckProperties((float)(positionX), SCOPE_BOTTOM, angle);
}

void CSpawnManager::ChcekBoundaryforDuck()
{
	// when duck goes out of scope boundary ( WIDTH - SCOPE_BOTTOM ), randomize duck
	if (m_duck->GetDuckBounds().top + m_duck->GetDuckBounds().height < 0.0f || m_duck->GetDuckBounds().top > SCOPE_BOTTOM ||
		m_duck->GetDuckBounds().left + m_duck->GetDuckBounds().width < 0.0f || m_duck->GetDuckBounds().left > WIDTH)
	{
		if (m_duck->IsDead())
		{
			m_duck->SetDuckLife(false);
		}
		RandomizeDuck();
	}
}

void CSpawnManager::ChcekBulletDuckColiision()
{
	// when we click on duck (bullet hits) 
	if (m_shooter->GetMouseInput().m_mouseClickPosition.x > m_duck->GetDuckBounds().left &&
		m_shooter->GetMouseInput().m_mouseClickPosition.x < m_duck->GetDuckBounds().left + m_duck->GetDuckBounds().width &&
		m_shooter->GetMouseInput().m_mouseClickPosition.y > m_duck->GetDuckBounds().top &&
		m_shooter->GetMouseInput().m_mouseClickPosition.y < m_duck->GetDuckBounds().top + m_duck->GetDuckBounds().height)
	{
		std::cout << "HIT!\n";
		if (m_gameState == EGameState::Player1Turn)
		{
			m_player1Score += SCORE;
		}

		else if (m_gameState == EGameState::Player2Turn)
		{
			m_player2Score += SCORE;
		}
		m_duck->SetDuckLife(true);
	}
}


/*
	The input position is the center position of the text box
*/
void CSpawnManager::DisplayMessage(std::string massage, sf::Color color, sf::Vector2f position, unsigned int charSize, sf::RenderTarget& target)
{
	sf::Font font;
	if (font.loadFromFile("Font/Cheapsman_Regular.ttf"))
	{
		m_message.setFont(font);
	}
	m_message.setFillColor(color);
	m_message.setCharacterSize(charSize);
	m_message.setString(massage);
	m_message.setPosition({ position.x - m_message.getGlobalBounds().width / 2, position.y - m_message.getGlobalBounds().height / 2 });

	m_message.setStyle(sf::Text::Bold);
	target.draw(m_message);
}


CSpawnManager::~CSpawnManager()
{
}

