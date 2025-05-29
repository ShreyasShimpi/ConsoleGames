// external includes
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>

// internal includes
#include "SpawnManager.h"
#include "Engine.h"

CSpawnManager::CSpawnManager(CEngine& engine, unsigned int width, unsigned int height)
	:m_engine(engine)
{
	m_score = 0;
	m_lives = LIVES;
	m_isDead = false;

	// loading background
	LoadBackground();

	// init player
	m_snake = std::make_unique<CSnake>(engine);
	m_snake->InitCharacter(WIDTH / 2, HEIGHT / 2);

	// init fruit
	sf::Vector2f v = { 0.0f, 0.0f };
	m_fruit = std::make_unique<CFruit>(v);
	RandomizeFruit();
}

void CSpawnManager::LoadBackground()
{
	std::stringstream ss;
	ss << "Sprites/snake_bg1.png";

	if (m_bgTexture.loadFromFile(ss.str()))
	{
		m_bgSprite.setTexture(m_bgTexture);
	}
	else
	{
		std::cout << "Failed to load Texture : " << ss.str() << "\n";
	}
	m_bgTexture.setRepeated(true);
	m_bgSprite.setColor(sf::Color::Blue);
}

void CSpawnManager::UpdateSpawns(const float& deltaTime)
{
	// take key action from player (WASD)
	if (!m_isDead)
	{
		// take player input
		m_snake->KeyAction(deltaTime);

		// check collision
		CheckCollisionWithFruit();
		CheckCollisionWithBoundary();
		CheckCollisionWithItself();

		// update the player
		m_snake->Update(deltaTime);
	}
	else
	{
		m_engine.SetGameState(false);
	}
}

void CSpawnManager::RenderSpawns(sf::RenderTarget& target)
{
	if (!m_isDead)
	{
		// background (bottom)
		target.draw(m_bgSprite);

		// snake
		m_snake->Render(target);

		// fruit
		m_fruit->Render(target);

		DisplayMessage("Score : " + std::to_string(m_score), sf::Color::White, { WIDTH / 2, 5.0f }, 24, target);
		DisplayMessage("Lives : " + std::to_string(m_lives), sf::Color::White, { 50.0f, 5.0f }, 24, target);

	}
	else
	{
		// background (bottom)
		target.draw(m_bgSprite);

		// hard coded position for text (trial and error)
		DisplayMessage("YOU DIED!", sf::Color::White, { WIDTH / 2 , HEIGHT / 2 - 50.0f }, 48, target);
		DisplayMessage("Final Score : " + std::to_string(m_score), sf::Color::White, { WIDTH / 2, HEIGHT / 2 - 10.0f }, 48, target);
		DisplayMessage("Press ENTER to Restart", sf::Color::White, { WIDTH / 2, HEIGHT - 50.0f }, 18, target);
		DisplayMessage("Press ESCAPE to close", sf::Color::White, { WIDTH / 2, HEIGHT - 30.0f }, 18, target);
	}
}

void CSpawnManager::RandomizeFruit()
{
	srand(time(0));
	sf::Vector2f fruitPosition = { (float)(rand() % (WIDTH - (int)(m_fruit->GetFruitGlobalBounds().width)) + 1), (float)(rand() % (HEIGHT - (int)(m_fruit->GetFruitGlobalBounds().height)) + 1) };
	m_fruit->SetPosition(fruitPosition);
}

void CSpawnManager::CheckCollisionWithFruit()
{
	if (m_snake->GetHeadGlobalBounds().intersects(m_fruit->GetFruitGlobalBounds()))
	{
		m_score += SCORE;
		m_snake->AddTrail();
		RandomizeFruit();

		//std::cout << "Current Score : " << m_score << ".\n";
		//std::cout << m_snake->GetTrailSize() << "\n";
	}
}

void CSpawnManager::CheckCollisionWithBoundary()
{
	// for X
	if (this->m_snake->GetHeadPosition().x < 0)
	{
		this->m_snake->SetSnakeHeadPosition({ WIDTH - 1 , m_snake->GetHeadPosition().y });
	}
	else if (this->m_snake->GetHeadPosition().x > WIDTH)
	{
		this->m_snake->SetSnakeHeadPosition({ 1 , m_snake->GetHeadPosition().y });
	}

	// for Y
	if (this->m_snake->GetHeadPosition().y < 0)
	{
		this->m_snake->SetSnakeHeadPosition({ m_snake->GetHeadPosition().x, HEIGHT - 1 });
	}
	else if (this->m_snake->GetHeadPosition().y > HEIGHT)
	{
		this->m_snake->SetSnakeHeadPosition({ m_snake->GetHeadPosition().x, 1 });
	}
}

void CSpawnManager::CheckCollisionWithItself()
{
	for (size_t index = 1; index < m_snake->GetTrailSize(); index++)
	{
		if (m_snake->GetHeadGlobalBounds().intersects(m_snake->GetBodyGlobalBounds(index)))
		{
			//std::cout << "Collided!\n";
			if (m_lives == 0)
			{
				m_isDead = true;
			}
			m_lives--;
			std::this_thread::sleep_for(std::chrono::seconds(2));
			break;
		}
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

