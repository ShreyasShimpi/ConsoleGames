// external includes
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include <fstream>

// internal includes
#include "SpawnManager.h"
#include "AssetManager.h"
#include "Engine.h"

CSpawnManager::CSpawnManager(CEngine& engine)
	:m_engine(engine)
{
	m_assetManager = new CAssetManager();
	
	// menu graphic
	m_menu = m_assetManager->GetSprite(ESprite::Menu_Graphic);
	m_menu.setPosition({6.0f, 100.0f});

	// init player
	m_player = std::make_unique<CPlayer>(sf::Vector2f(WIDTH / 2, DEFENCE_HEIGHT - 10), m_engine, *m_assetManager);

	// init enemies
	std::vector<EEnemyType> enemyRow = {EEnemyType::Squid, EEnemyType::Crab, EEnemyType::Crab, EEnemyType::Flat, EEnemyType::Flat, };
	
	// making enemy grid
	sf::Vector2f tempPosition;
	for (int i = 0; i < ENEMY_GRID_ROWS; i++)
	{
		for (int j = 0; j < ENEMY_GRID_COLUMNS; j++)
		{
			tempPosition.x = ENEMY_GRID_OFFSET_X + j * ENEMY_GRID_SIZE;
			tempPosition.y = ENEMY_GRID_OFFSET_Y + i * ENEMY_GRID_SIZE;
			m_enemies.emplace_back(std::make_unique<CEnemy>(tempPosition, *m_assetManager, enemyRow[i]));
		}
	}
	m_enemyBulletSprite = m_assetManager->GetSprite(ESprite::Enemy_Bullet);
	
	m_isEnemyBulletShot = false;
	m_isMovingLeft = false;
	m_moveDown = false;
	m_elapsedTime = 0.0f;
	m_playerScore = 0;
	m_enemiesAlive = ENEMY_GRID_ROWS * ENEMY_GRID_COLUMNS;
	m_gameState = EGameState::MainMenu;

	// init shield
	m_shields.emplace_back(std::make_unique<CShield>(sf::Vector2f{58.0f, DEFENCE_HEIGHT - 110.0f }, *m_assetManager));
	m_shields.emplace_back(std::make_unique<CShield>(sf::Vector2f{218.0f, DEFENCE_HEIGHT - 110.0f }, *m_assetManager));
	m_shields.emplace_back(std::make_unique<CShield>(sf::Vector2f{378.0f, DEFENCE_HEIGHT - 110.0f }, *m_assetManager));
	m_shields.emplace_back(std::make_unique<CShield>(sf::Vector2f{538.0f, DEFENCE_HEIGHT - 110.0f }, *m_assetManager));

	// lives sprite
	for (int i = 0; i < g_playerTotalLives; i++)
	{
		m_playerLives.emplace_back(m_assetManager->GetSprite(ESprite::Player));
		m_playerLives.back().setPosition({ 530.0f + i * 30, 15.0f });
	}
}


void CSpawnManager::MoveEnemyGrid()
{
	bool moveDown = false;
	for (auto& enemy : m_enemies)
	{
		// dont check is enemy is dead
		if (enemy->IsDead())
		{
			continue;
		}

		// check if any alive enemy crosses the bounds
		if (enemy->GetEnemyBounds().left < g_enemySidewardStep)
		{
			moveDown = true;
			m_isMovingLeft = false;
			break;
		}
		else if (enemy->GetEnemyBounds().left + enemy->GetEnemyBounds().width > WIDTH - g_enemySidewardStep)
		{
			moveDown = true;
			m_isMovingLeft = true;
			break;
		}
		else
		{
			moveDown = false;
		}
	}

	// finally do the necessary movement
	m_moveDown = moveDown;
	float step = m_isMovingLeft ? -g_enemySidewardStep : g_enemySidewardStep;
	for (auto& enemy : m_enemies)
	{
		// dont check is enemy is dead
		if (enemy->IsDead())
		{
			continue;
		}

		// sideward movement
		enemy->Move({ step, 0.0f });

		// downward movement
		if (m_moveDown)
		{
			enemy->Move({ 0.0f, g_enemyDownwardStep });
		}
	}
}


void CSpawnManager::AddToScore(EEnemyType type)
{
	srand(time(0));

	switch (type)
	{
	case EEnemyType::Squid:
		m_playerScore += g_squidPoints;
		break;
	case EEnemyType::Crab:
		m_playerScore += g_crabPoints;
		break;
	case EEnemyType::Flat:
		m_playerScore += g_flatPoints;
		break;
	case EEnemyType::UFO:
		m_playerScore += rand() % 21 + 200; // result will be between 200 to 400 in multiple of 10.
		break;
	default:
		break;
	}
}

void CSpawnManager::ShootBullet(const float& deltaTime)
{
	srand(time(0));
	// is bullet is not shot
	if (!m_isEnemyBulletShot)
	{
		short enemyIndex = 0;
		do
		{
			enemyIndex = rand() % m_enemies.size();

		} while (m_enemies[enemyIndex]->IsDead()); // to get random enemy index who is alive

		m_enemyBulletSprite.setPosition(m_enemies[enemyIndex]->GetPlayerPosition());
		m_isEnemyBulletShot = true;
	}
	// if bullet is shot
	else
	{
		m_enemyBulletSprite.move(0.0f, g_enemyBulletSpeed * deltaTime);
	}
}

void CSpawnManager::UpdateSpawns(const float& deltaTime)
{
	switch (m_gameState)
	{
	case EGameState::MainMenu:
	{
		if (m_player->GetKeyInput().m_enter.isPressed)
		{
			m_gameState = EGameState::InGame;
		}
	}
	break;
	case EGameState::InGame:
	{
		// player update
		m_player->Update(deltaTime);

		// enemy Update
		if (m_elapsedTime > g_enemyStepTime)
		{
			MoveEnemyGrid();
			m_elapsedTime = 0.0f;
		}
		for (auto& enemy : m_enemies)
		{
			enemy->Update(deltaTime);
		}

		// enemy bullet
		ShootBullet(deltaTime);

		// Collision
		CheckBoundaryForAll();

		CheckPlayerBulletShieldColiision();
		CheckPlayerBulletEnemyCollision();

		CheckEnemyBulletPlayerCollision();
		CheckEnemyBulletShieldCollision();
		CheckEnemyDefenceCollision();

		// update elapsed time
		m_elapsedTime += deltaTime;

		// if all enemies are dead
		if (m_enemiesAlive == 0)
		{
			m_gameState = EGameState::Winner;
		}

		// if all lives are gone
		if (m_playerLives.size() == 0)
		{
			m_gameState = EGameState::GameOver;
		}
	}
	break;
	case EGameState::Winner:
	{
		if (m_player->GetKeyInput().m_enter.isPressed)
		{
			m_gameState = EGameState::MainMenu;
		}
	}
	break;
	case EGameState::GameOver:
	{
		if (m_player->GetKeyInput().m_enter.isPressed)
		{
			m_gameState = EGameState::MainMenu;
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
		// main menu graphic
		target.draw(m_menu);
		DisplayMessage("Press  ENTER  to  Play", sf::Color::White, 1, { WIDTH / 2, HEIGHT / 2 + 100.0f }, 32, target);
		DisplayMessage("Press  ESC  to  Quit", sf::Color::White, 1, { WIDTH / 2, HEIGHT / 2 + 130.0f }, 32, target);
	}
	break;
	case EGameState::InGame:
	{
		// player spawn
		m_player->Render(target);

		// enemy spawn
		for (auto& enemy : m_enemies)
		{
			enemy->Render(target);
		}

		// shields spawn
		for (auto& shield : m_shields)
		{
			shield->Render(target);
		}

		// enmey bullet
		target.draw(m_enemyBulletSprite);

		// score
		DisplayMessage("SCORE    " + std::to_string(m_playerScore), sf::Color::White, 0, { 10.0f, 0.0f }, 32, target);
		
		// lives
		DisplayMessage("LIVES", sf::Color::White, 0, { 430.0f, 0.0f }, 32, target);
		for (auto& lives : m_playerLives)
		{
			target.draw(lives);
		}
	}
	break;
	case EGameState::Winner:
	{
		DisplayMessage("YOU  WIN!", sf::Color::White, 1, { WIDTH/2, HEIGHT/2 - 100.0f}, 64, target);
		DisplayMessage("SCORE    " + std::to_string(m_playerScore), sf::Color::White, 1, { WIDTH / 2, HEIGHT / 2}, 48, target);
		DisplayMessage("Press  ENTER  to  Play", sf::Color::White, 1, { WIDTH / 2, HEIGHT / 2 + 100.0f }, 32, target);
		DisplayMessage("Press  ESC  to  Quit", sf::Color::White, 1, { WIDTH / 2, HEIGHT / 2 + 130.0f }, 32, target);
	}
	break;
	case EGameState::GameOver:
	{
		DisplayMessage("GAME  OVER!", sf::Color::White, 1, { WIDTH / 2, HEIGHT / 2 - 100.0f}, 64, target);
		DisplayMessage("SCORE    " + std::to_string(m_playerScore), sf::Color::White, 1, { WIDTH / 2, HEIGHT / 2}, 48, target);
		DisplayMessage("Press  ENTER  to  Play", sf::Color::White, 1, { WIDTH / 2, HEIGHT / 2 + 100.0f }, 32, target);
		DisplayMessage("Press  ESC  to  Quit", sf::Color::White, 1, { WIDTH / 2, HEIGHT / 2 + 130.0f }, 32, target);

	}
	break;
	default:
		break;
	}
	
}

void CSpawnManager::CheckBoundaryForAll()
{
	// bullet
	if (m_player->GetBulletBounds().top < 0.0f)
	{
		// if bullet goes out of the window. reset it
		m_player->ResetBullet();
	}

	// enemy bullet
	if (m_enemyBulletSprite.getGlobalBounds().top > HEIGHT)
	{
		// if bullet goes out of the window. reset it
		m_isEnemyBulletShot = false;
	}

	// player
	// if player goes out of the window. stop it
	if (m_player->GetPlayerBounds().left < 0.0f)
	{
		m_player->SetPlayerPosition({ m_player->GetPlayerBounds().width / 2, m_player->GetPlayerPosition().y });
	}
	else if (m_player->GetPlayerBounds().left + m_player->GetPlayerBounds().width > WIDTH)
	{
		m_player->SetPlayerPosition({ WIDTH - m_player->GetPlayerBounds().width / 2, m_player->GetPlayerPosition().y });
	}
}

void CSpawnManager::CheckPlayerBulletEnemyCollision()
{
	if (m_player->IsBulletShot())
	{
		for (auto& enemy : m_enemies)
		{
			if (!enemy->IsDead() && RectToRectCollision(m_player->GetBulletBounds(), enemy->GetEnemyBounds()))
			{
				m_player->ResetBullet();
				AddToScore(enemy->GetEnemyType());
				enemy->Hit();
				m_enemiesAlive -= 1;
			}
		}
	}
}

void CSpawnManager::CheckEnemyDefenceCollision()
{
	// optimization needed
	for (auto& enemy : m_enemies)
	{
		if (!enemy->IsDead() && enemy->GetEnemyBounds().top + enemy->GetEnemyBounds().height > DEFENCE_HEIGHT)
		{
			m_gameState = EGameState::GameOver;
		}
	}
}

void CSpawnManager::CheckEnemyBulletShieldCollision()
{
	for (auto& shield : m_shields)
	{
		if (!shield->IsDestroyed() && RectToRectCollision(m_enemyBulletSprite.getGlobalBounds(), shield->GetShieldBounds()))
		{
			shield->Hit();
			m_isEnemyBulletShot = false;
		}
	}
}

void CSpawnManager::CheckEnemyBulletPlayerCollision()
{
	if (RectToRectCollision(m_enemyBulletSprite.getGlobalBounds(), m_player->GetPlayerBounds()))
	{
		m_playerLives.pop_back();
		m_isEnemyBulletShot = false;
	}
}

void CSpawnManager::CheckPlayerBulletShieldColiision()
{
	for (auto& shield : m_shields)
	{
		if (!shield->IsDestroyed() && RectToRectCollision(m_player->GetBulletBounds(), shield->GetShieldBounds()))
		{
			m_player->ResetBullet();
			shield->Hit();
		}
	}
}


/*
	The input position is the center position of the text box
*/
void CSpawnManager::DisplayMessage(std::string massage, sf::Color color, bool isCenter, sf::Vector2f position, unsigned int charSize, sf::RenderTarget& target)
{
	sf::Font font;
	if (font.loadFromFile("ARCADECLASSIC.TTF"))
	{
		m_message.setFont(font);
	}
	m_message.setFillColor(color);
	m_message.setCharacterSize(charSize);
	m_message.setString(massage);

	// setting position
	if (isCenter)
	{
		// center
		m_message.setPosition({ position.x - m_message.getGlobalBounds().width / 2, position.y - m_message.getGlobalBounds().height / 2 });
	}
	else
	{
		// top left
		m_message.setPosition({ position.x, position.y});
	}
	
	

	m_message.setStyle(sf::Text::Bold);
	target.draw(m_message);
}


CSpawnManager::~CSpawnManager()
{
}

