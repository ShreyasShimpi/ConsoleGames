// external includes
#include <iostream>
#include <thread>
#include <chrono>

// internal includes
#include "SpawnManager.h"
#include "Defines.h"
#include "Engine.h"

CSpawnManager::CSpawnManager(CEngine& engine, unsigned int width, unsigned int height)
	:m_engine(engine)
{
	m_isWinner = false;
	m_isBombPlaced = false;
	m_isBombPlaced = false;
	m_isExploding = false;
	m_isDead = false;

	m_bombTime = 0.0f;

	// loading background
	LoadBackground();

	// loading background
	LoadForeGroundTiles();

	// init bomb
	m_bomb = nullptr;
	m_playerKeyPressedListnerCB = std::bind(&CSpawnManager::BombKeyPressedListner, this, std::placeholders::_1); // adding listener for space key
	engine.GetEventHandler().RegisterEventListner(sf::Event::EventType::KeyPressed, &m_playerKeyPressedListnerCB);

	// init player
	m_player = new CPlayer(engine);
	m_player->InitCharacter(16.0f, 16.0f);
	m_player->SetSpriteScale({ 0.95f, 0.95f });

	// init enemies
	InitEnemies();

	// init solid walls
	InitSolidWalls();

	// init brick walls
	InitBrickWalls();

	// init Explosion Texture
	InitExpTexture();

	// init key and door
	m_key = new CKey();
	m_door = new CDoor();
	RandomizeKeyAndDoor();
}


void CSpawnManager::LoadBackground()
{
	std::stringstream ss;
	ss << "Sprites/background.png";

	if (m_bgTexture.loadFromFile(ss.str()))
	{
		m_bgSprite.setTexture(m_bgTexture);
	}
	else
	{
		std::cout << "Failed to load Texture : " << ss.str() << "\n";
	}
	// scaled to 2x
	//m_bgSprite.setScale({ 2.0f, 2.0f });
}

void CSpawnManager::LoadForeGroundTiles()
{
	std::stringstream ss;
	ss << "Sprites/foreground_tiles.png";

	if (m_fgTilesTexture.loadFromFile(ss.str()))
	{
		m_fgTilesSprite.setTexture(m_fgTilesTexture);
	}
	else
	{
		std::cout << "Failed to load Texture : " << ss.str() << "\n";
	}
	// scaled to 2x
	//m_bgSprite.setScale({ 2.0f, 2.0f });
}

void CSpawnManager::InitExpTexture()
{
	for (int i = 0; i < 4; ++i)
	{
		std::stringstream ss;
		ss << "Sprites/Explosion/explosion(" << i << ").png";

		sf::Texture texture;

		if (texture.loadFromFile(ss.str()))
		{
			m_expTexture.push_back(texture);
		}
		else
		{
			std::cout << "Failed to load Texture : " << ss.str() << "\n";
		}
	}
}

void CSpawnManager::InitBrickWalls()
{
	
	// top left coordinate of all bricks (manually hard coded so far)
	std::vector<sf::Vector2i> brickPositions = {
	{ 8, 1},  { 18, 1} ,
	{ 1, 3 } , { 13, 3 } , { 14, 3 } , { 24, 3 } ,
	{ 13, 4 } ,
	{ 10, 5 } ,{ 20, 5 } , { 24, 5 } ,
	{ 4, 7 } , { 13, 7 } , { 14, 7 },
	{ 1, 9 } , { 2, 9 } ,  { 6, 9 } , { 20, 9 } , { 26, 9 } ,
	{ 6, 11 } ,{ 12, 11 } }; 

	// brick walls initiated with given position
	for (const auto& brickPos : brickPositions)
	{
		m_brickWall.push_back(new CBrickWall());
		m_brickWall.back()->InitObject(brickPos.x * IMAGESIZE, brickPos.y * IMAGESIZE);
	}	
}

void CSpawnManager::InitSolidWalls()
{
	for (int solidWallRow = 1; solidWallRow <= 5; solidWallRow++)
	{
		for (int solidWallColumn = 1; solidWallColumn <= 14; solidWallColumn++)
		{
			m_solidWall.push_back(new CSolidWall());
			m_solidWall.back()->InitObject((float)(32 * solidWallColumn), (float)(32 * solidWallRow));
		}
	}
}

void CSpawnManager::InitEnemies()
{
	// init enemies (4)
	std::vector<sf::Vector2i> enemyPositions = {
	{ 8, 3 },
	{ 16, 5 },
	{ 22, 7 },
	{ 8, 11 } };

	for (const auto& enemyPos : enemyPositions)
	{
		m_enemies.push_back(new CEnemy());
		m_enemies.back()->InitCharacter(enemyPos.x * IMAGESIZE, enemyPos.y * IMAGESIZE);
	}
}

void CSpawnManager::RandomizeKeyAndDoor()
{
	srand(time(0));
	int randomIndexForDoor = rand() % m_brickWall.size();
	int randomIndexForKey;
	do 
	{
		randomIndexForKey = rand() % m_brickWall.size();
	} while (randomIndexForDoor == randomIndexForKey);

	// initialize door and key with that random position
	m_door->InitObject(m_brickWall[randomIndexForDoor]->GetPosition().x, m_brickWall[randomIndexForDoor]->GetPosition().y);
	m_key->InitObject(m_brickWall[randomIndexForKey]->GetPosition().x, m_brickWall[randomIndexForKey]->GetPosition().y);
}


void CSpawnManager::BombKeyPressedListner(sf::Event event)
{
	HandleKeyPress(event, m_player->GetInput());
}

void CSpawnManager::BombAction(const float& deltaTime)
{
	if (m_player->GetInput().m_space.isPressed && !m_isBombPlaced)
	{
		m_bomb = new CBomb();
		sf::Vector2f bombPosition;

		// to keep the bomb in the grid only
		bombPosition.x = ((int)(m_player->GetPosition().x / IMAGESIZE)) * IMAGESIZE;
		bombPosition.y = ((int)(m_player->GetPosition().y / IMAGESIZE)) * IMAGESIZE;

		m_bomb->InitObject(bombPosition.x, bombPosition.y);

		m_isBombPlaced = true;
	}
}

void CSpawnManager::ActivateBomb(const float& deltaTime)
{
	m_bombTime += deltaTime;

	if (m_bombTime >= BOMB_TIMER)
	{
		m_isExploding = true;
		RunExplosionAnimation(EXPLODING_TIME);
	}
}

void CSpawnManager::RunExplosionAnimation(float animationDelay)
{
	float nextFrameDelay = animationDelay / m_expTexture.size();

	if (m_isExploding)
	{
		int index = static_cast<int>(m_bombTime / nextFrameDelay) % m_expTexture.size();
		m_expSprite.setTexture(m_expTexture[index]);
		m_expSprite.setPosition({ m_bomb->GetPosition().x - IMAGESIZE,m_bomb->GetPosition().y - IMAGESIZE });

		if (index == m_expTexture.size() - 1)
		{
			m_isExploding = false;
			m_bombTime = 0;
			m_isBombPlaced = false;
			m_bomb = nullptr;
		}
	}
}


void CSpawnManager::UpdateSpawns(const float& deltaTime)
{
	// take key action from player (WASD)
	if (!m_isDead && !m_isWinner)
	{
		// take player input
		m_player->KeyAction(deltaTime);

		// take key action from player (SPACE)
		BombAction(deltaTime);
		if (m_isBombPlaced)
		{
			ActivateBomb(deltaTime);
		}
		if (m_isExploding)
		{
			CheckBombBrickWallCollision();
			CheckBombPlayerCollision();
			CheckBombEnemyCollision();
		}

		// collision player
		CheckSolidWallCollision(*m_player, deltaTime);
		CheckBrickWallCollision(*m_player, deltaTime);
		CheckBoundaryCollision(*m_player, deltaTime);
		CheckPlayerEnemyCollision();

		// collision enemies
		for (auto& enemy : m_enemies)
		{
			CheckBrickWallCollision(*enemy, deltaTime);
			CheckBoundaryCollision(*enemy, deltaTime);
		}

		// check collision of door and key for player
		CheckKeyCollision();
		CheckDoorCollision();

		// update the characters
		m_player->Update(deltaTime);
		for (auto& enemy : m_enemies)
		{
			enemy->Update(deltaTime);
		}
	}
	else if(m_isDead)
	{
		// update the characters
		m_player->RunDeathAnimation(PLAYER_DEATH_ANIMATION_DELAY, deltaTime);
		m_engine.SetGameState(true);
	}
	else if(m_isWinner)
	{
		m_engine.SetGameState(true);
	}
}

void CSpawnManager::RenderSpawns(sf::RenderTarget& target)
{
	// background (bottom)
	target.draw(m_bgSprite);

	// solid walls
	for (const auto& solidwall : m_solidWall)
	{
		solidwall->Render(target);
	}

	// door and key
	m_door->Render(target);
	if (!m_player->HasKey())
	{
		m_key->Render(target);
	}

	// brick walls
	for (auto& brickwall : m_brickWall)
	{
		brickwall->Render(target);
	}

	if (m_bomb != nullptr)
	{
		m_bomb->Render(target);
	}

	// explosion
	if (m_isExploding)
	{
		target.draw(m_expSprite);
	}

	// player
	m_player->Render(target);

	// enemies
	for (auto& enemy : m_enemies)
	{
		enemy->Render(target);
	}

	// foreground tiles (top)
	target.draw(m_fgTilesSprite);

	// if player has key, it should display on top right
	if (m_player->HasKey())
	{
		m_key->Render(target);
	}

	// display the massage
	if (m_isWinner)
	{
		// black fade before the text
		sf::RectangleShape fade;
		fade.setSize({ WIDTH, HEIGHT });
		fade.setFillColor(sf::Color(0, 0, 0, 150));
		target.draw(fade);
		
		// hard coded position for text (trial and error)
		DisplayMessage("YOU WIN!", sf::Color::Green, { WIDTH / 2 - 75.0f, HEIGHT/2 - 50.0f }, 48, target);
		DisplayMessage("Press ENTER to Restart", sf::Color::Green, { WIDTH / 2 - 90.f, HEIGHT - 50.0f}, 18, target);
		DisplayMessage("Press ESCAPE to close", sf::Color::Green, { WIDTH / 2 - 85.f, HEIGHT - 30.0f }, 18, target);
	}
	else if (m_isDead)
	{
		// black fade before the text
		sf::RectangleShape fade;
		fade.setSize({ WIDTH, HEIGHT });
		fade.setFillColor(sf::Color(0, 0, 0, 150));
		target.draw(fade);

		// hard coded position for text (trial and error)
		DisplayMessage("YOU DIED!", sf::Color::Red, { WIDTH / 2 - 75.0f, HEIGHT/2  - 50.0f }, 48, target);
		DisplayMessage("Press ENTER to Restart", sf::Color::Red, { WIDTH / 2 - 90.f, HEIGHT - 50.0f }, 18, target);
		DisplayMessage("Press ESCAPE to close", sf::Color::Red, { WIDTH / 2 - 85.f, HEIGHT - 30.0f }, 18, target);
	}
}

void CSpawnManager::CheckSolidWallCollision(CCharacter& character, const float& deltatime)
{
	sf::FloatRect nextPos;
	sf::Vector2f offsetPosition = { character.GetVelocity().x * deltatime,  character.GetVelocity().y * deltatime };

	for (const auto& solidWall : m_solidWall)
	{
		sf::FloatRect playerBounds = character.GetGlobalBounds();
		sf::FloatRect wallBounds = solidWall->GetGlobalBounds();

		nextPos = playerBounds;
		
		nextPos.left += offsetPosition.x;
		nextPos.top += offsetPosition.y;

		if (wallBounds.intersects(nextPos))
		{
			//Bottom collision
			if (playerBounds.top < wallBounds.top
				&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
				&& playerBounds.left < wallBounds.left + wallBounds.width
				&& playerBounds.left + playerBounds.width > wallBounds.left
				)
			{
				character.SetVelocity({ character.GetVelocity().x, 0.0f });
				character.SetPosition({ playerBounds.left, wallBounds.top - playerBounds.height });
			}

			//Top collision
			else if (playerBounds.top > wallBounds.top
				&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
				&& playerBounds.left < wallBounds.left + wallBounds.width
				&& playerBounds.left + playerBounds.width > wallBounds.left
				)
			{
				character.SetVelocity({ character.GetVelocity().x, 0.0f });
				character.SetPosition({ playerBounds.left, wallBounds.top + wallBounds.height });
			}

			//Right collision
			if (playerBounds.left < wallBounds.left
				&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
				&& playerBounds.top < wallBounds.top + wallBounds.height
				&& playerBounds.top + playerBounds.height > wallBounds.top
				)
			{

				character.SetVelocity({ 0.0f , character.GetVelocity().y });
				character.SetPosition({ wallBounds.left - playerBounds.width, playerBounds.top });
		
			}

			//Left collision
			else if (playerBounds.left > wallBounds.left
				&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
				&& playerBounds.top < wallBounds.top + wallBounds.height
				&& playerBounds.top + playerBounds.height > wallBounds.top
				)
			{
				

				character.SetVelocity({ 0.0f , character.GetVelocity().y });
				character.SetPosition({ wallBounds.left + wallBounds.width, playerBounds.top });

			}
		}
	}
}

void CSpawnManager::CheckBrickWallCollision(CCharacter& character, const float& deltatime)
{
	sf::FloatRect nextPos;
	sf::Vector2f offsetPosition = { character.GetVelocity().x * deltatime,  character.GetVelocity().y * deltatime };

	for (const auto& brickWall : m_brickWall)
	{
		sf::FloatRect playerBounds = character.GetGlobalBounds();
		sf::FloatRect wallBounds = brickWall->GetGlobalBounds();

		nextPos = playerBounds;

		nextPos.left += offsetPosition.x;
		nextPos.top += offsetPosition.y;

		if (wallBounds.intersects(nextPos))
		{
			//Bottom collision
			if (playerBounds.top < wallBounds.top
				&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
				&& playerBounds.left < wallBounds.left + wallBounds.width
				&& playerBounds.left + playerBounds.width > wallBounds.left
				)
			{
				character.SetVelocity({ character.GetVelocity().x, 0.0f });
				character.SetPosition({ playerBounds.left, wallBounds.top - playerBounds.height });
			}

			//Top collision
			else if (playerBounds.top > wallBounds.top
				&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
				&& playerBounds.left < wallBounds.left + wallBounds.width
				&& playerBounds.left + playerBounds.width > wallBounds.left
				)
			{
				character.SetVelocity({ character.GetVelocity().x, 0.0f });
				character.SetPosition({ playerBounds.left, wallBounds.top + wallBounds.height });
			}

			//Right collision
			if (playerBounds.left < wallBounds.left
				&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
				&& playerBounds.top < wallBounds.top + wallBounds.height
				&& playerBounds.top + playerBounds.height > wallBounds.top
				)
			{

				if (character.GetCharacterType() == ECharacterType::PLAYER)
				{
					character.SetVelocity({ 0.0f , character.GetVelocity().y });
					character.SetPosition({ wallBounds.left - playerBounds.width, playerBounds.top });
				}
				else if (character.GetCharacterType() == ECharacterType::ENEMY)
				{
					character.SetVelocity({ -1.0f * character.GetVelocity().x, character.GetVelocity().y });
				}
			}

			//Left collision
			else if (playerBounds.left > wallBounds.left
				&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
				&& playerBounds.top < wallBounds.top + wallBounds.height
				&& playerBounds.top + playerBounds.height > wallBounds.top
				)
			{
				if (character.GetCharacterType() == ECharacterType::PLAYER)
				{
					character.SetVelocity({ 0.0f , character.GetVelocity().y });
					character.SetPosition({ wallBounds.left + wallBounds.width, playerBounds.top });
				}
				else if (character.GetCharacterType() == ECharacterType::ENEMY)
				{
					character.SetVelocity({ -1.0f * character.GetVelocity().x, character.GetVelocity().y });
				}
			}
		}
	}
}


void CSpawnManager::CheckBoundaryCollision(CCharacter& character, const float& deltatime)
{
	sf::Vector2f offsetPosition = { character.GetVelocity().x * deltatime,  character.GetVelocity().y * deltatime };

	//Collision screen
	//Left collision
	if (character.GetPosition().x + offsetPosition.x < IMAGESIZE)
	{
		if (character.GetCharacterType() == ECharacterType::PLAYER)
		{
			character.SetVelocity({ 0.0f, character.GetVelocity().y });
			character.SetPosition({ IMAGESIZE, character.GetPosition().y });
		}
		else if(character.GetCharacterType() == ECharacterType::ENEMY)
		{
			character.SetVelocity({ -1.0f * character.GetVelocity().x, character.GetVelocity().y });
		}
		
	}
	//Top collision
	if (character.GetPosition().y + offsetPosition.y < IMAGESIZE)
	{
		character.SetVelocity({ character.GetVelocity().x,  0.0f });
		character.SetPosition({ character.GetPosition().x, IMAGESIZE });
	}
	//Right collision
	if (character.GetPosition().x + character.GetGlobalBounds().width + offsetPosition.x > WIDTH - IMAGESIZE)
	{

		if (character.GetCharacterType() == ECharacterType::PLAYER)
		{
			character.SetVelocity({ 0.0f, character.GetVelocity().y });
			character.SetPosition({ WIDTH - IMAGESIZE - character.GetGlobalBounds().width, character.GetPosition().y });
		}
		else if (character.GetCharacterType() == ECharacterType::ENEMY)
		{
			character.SetVelocity({ -1.0f * character.GetVelocity().x, character.GetVelocity().y });
		}
	}
	//Bottom collision
	if (character.GetPosition().y + character.GetGlobalBounds().height + offsetPosition.y > HEIGHT - IMAGESIZE)
	{
		character.SetVelocity({ character.GetVelocity().x,  0.0f });
		character.SetPosition({ character.GetPosition().x, HEIGHT - IMAGESIZE - character.GetGlobalBounds().height });
	}
}

void CSpawnManager::CheckBombBrickWallCollision()
{
	std::vector<int> brickWallIndices;

	for (int i = 0; i < m_brickWall.size(); i++)
	{
		if (m_bomb->GetPosition().x + IMAGESIZE == m_brickWall[i]->GetPosition().x && m_bomb->GetPosition().y == m_brickWall[i]->GetPosition().y)
		{
			brickWallIndices.push_back(i);
		}

		if (m_bomb->GetPosition().x == m_brickWall[i]->GetPosition().x && m_bomb->GetPosition().y + IMAGESIZE == m_brickWall[i]->GetPosition().y)
		{
			brickWallIndices.push_back(i);
		}

		if (m_bomb->GetPosition().x == m_brickWall[i]->GetPosition().x && m_bomb->GetPosition().y - IMAGESIZE == m_brickWall[i]->GetPosition().y)
		{
			brickWallIndices.push_back(i);
		}

		if (m_bomb->GetPosition().x - IMAGESIZE == m_brickWall[i]->GetPosition().x && m_bomb->GetPosition().y == m_brickWall[i]->GetPosition().y)
		{
			brickWallIndices.push_back(i);
		}
	}

	for (int i = brickWallIndices.size() - 1;i >= 0; i--)
	{
		m_brickWall.erase(m_brickWall.begin() + brickWallIndices[i]);
	}
}

void CSpawnManager::CheckBombPlayerCollision()
{

	sf::RectangleShape explosionArea;
	explosionArea.setSize({ 16.0f,16.0f });

	explosionArea.setPosition(m_bomb->GetPosition());
	if (m_player->GetGlobalBounds().intersects(explosionArea.getGlobalBounds()))
	{
		m_isDead = true;
	}

	explosionArea.setPosition({ m_bomb->GetPosition().x - IMAGESIZE,m_bomb->GetPosition().y });
	if (m_player->GetGlobalBounds().intersects(explosionArea.getGlobalBounds()))
	{
		m_isDead = true;
	}

	explosionArea.setPosition({ m_bomb->GetPosition().x + IMAGESIZE,m_bomb->GetPosition().y });
	if (m_player->GetGlobalBounds().intersects(explosionArea.getGlobalBounds()))
	{
		m_isDead = true;
	}

	explosionArea.setPosition({ m_bomb->GetPosition().x ,m_bomb->GetPosition().y - IMAGESIZE });
	if (m_player->GetGlobalBounds().intersects(explosionArea.getGlobalBounds()))
	{
		m_isDead = true;
	}

	explosionArea.setPosition({ m_bomb->GetPosition().x ,m_bomb->GetPosition().y + IMAGESIZE });
	if (m_player->GetGlobalBounds().intersects(explosionArea.getGlobalBounds()))
	{
		m_isDead = true;
	}
}

void CSpawnManager::CheckBombEnemyCollision()
{
	sf::RectangleShape explosionArea;
	explosionArea.setSize({ 16.0f,16.0f });

	explosionArea.setPosition(m_bomb->GetPosition());

	for (int i = m_enemies.size() - 1; i >= 0; --i )
	{
		if (m_enemies[i]->GetGlobalBounds().intersects(explosionArea.getGlobalBounds()))
		{
			m_enemies.erase(m_enemies.begin() + i);
		}

		explosionArea.setPosition({ m_bomb->GetPosition().x - IMAGESIZE,m_bomb->GetPosition().y });
		if (m_enemies[i]->GetGlobalBounds().intersects(explosionArea.getGlobalBounds()))
		{
			m_enemies.erase(m_enemies.begin() + i);
		}

		explosionArea.setPosition({ m_bomb->GetPosition().x + IMAGESIZE,m_bomb->GetPosition().y });
		if (m_enemies[i]->GetGlobalBounds().intersects(explosionArea.getGlobalBounds()))
		{
			m_enemies.erase(m_enemies.begin() + i);
		}

		explosionArea.setPosition({ m_bomb->GetPosition().x ,m_bomb->GetPosition().y - IMAGESIZE });
		if (m_enemies[i]->GetGlobalBounds().intersects(explosionArea.getGlobalBounds()))
		{
			m_enemies.erase(m_enemies.begin() + i);
		}

		explosionArea.setPosition({ m_bomb->GetPosition().x ,m_bomb->GetPosition().y + IMAGESIZE });
		if (m_enemies[i]->GetGlobalBounds().intersects(explosionArea.getGlobalBounds()))
		{
			m_enemies.erase(m_enemies.begin() + i);
		}
	}
}

void CSpawnManager::CheckPlayerEnemyCollision()
{
	for (const auto& enemy : m_enemies)
	{
		if (m_player->GetGlobalBounds().intersects(enemy->GetGlobalBounds()))
		{
			m_isDead = true;
		}
	}
}

void CSpawnManager::CheckKeyCollision()
{
	sf::FloatRect playerRect = m_player->GetGlobalBounds();
	sf::FloatRect keyRect = m_key->GetGlobalBounds();
	if (playerRect.intersects(keyRect) && !m_player->HasKey())
	{
		m_player->AcquireKey();
		// if player has key, it should display on top right
		m_key->SetPosition({ WIDTH - IMAGESIZE - 5.0f, 0.0f + 5.0f });
	}
}

void CSpawnManager::CheckDoorCollision()
{
	if (m_player->HasKey())
	{
		sf::FloatRect playerRect = m_player->GetGlobalBounds();
		sf::FloatRect doorRect = m_door->GetGlobalBounds();
		if (playerRect.intersects(doorRect))
		{
			m_isWinner = true;
		}
	}
}

void CSpawnManager::DisplayMessage(std::string massage, sf::Color color, sf::Vector2f position, unsigned int charSize, sf::RenderTarget& target)
{
	sf::Font font;
	if (font.loadFromFile("Font/Cheapsman_Regular.ttf"))
	{
		m_winnerMessage.setFont(font);
	}
	m_winnerMessage.setFillColor(color);
	m_winnerMessage.setCharacterSize(charSize);
	m_winnerMessage.setString(massage);
	m_winnerMessage.setPosition(position);
	m_winnerMessage.setOutlineColor(sf::Color::Black);
	m_winnerMessage.setOutlineThickness(1.0f);

	m_winnerMessage.setStyle(sf::Text::Bold | sf::Text::Underlined);
	target.draw(m_winnerMessage);
}


CSpawnManager::~CSpawnManager()
{
	delete m_player;
	for (auto& enemy : m_enemies)
	{
		delete enemy;
	}
	delete m_bomb;
	delete m_door;
	delete m_key;

	for (auto& solidWall : m_solidWall)
	{
		delete solidWall;
	}
	for (auto& brickWall : m_brickWall)
	{
		delete brickWall;
	}
}