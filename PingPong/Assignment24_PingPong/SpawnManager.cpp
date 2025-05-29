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
//#include "pingpong_generated.h"

CSpawnManager::CSpawnManager(CEngine& engine, unsigned int width, unsigned int height)
	:m_engine(engine)
{
	m_score1 = 0;
	m_score2 = 0;
	m_isGameRunning = false;


	// loading background
	LoadBackground();

	// init player
	m_paddle = new CPaddles(m_engine);
	m_paddle->InitPaddles(5.0f ,  HEIGHT / 2, WIDTH - 20.0f, HEIGHT/2);

	//init ball
	m_ball.setRadius(8.0f);
	m_ball.setFillColor(sf::Color::White);
	m_ball.setPosition({ WIDTH / 2, HEIGHT / 2 });
	RandomizeAngle();
}

void CSpawnManager::LoadBackground()
{
	std::stringstream ss;
	ss << "Sprites/pingpong_bg.png";

	if (m_bgTexture.loadFromFile(ss.str()))
	{
		m_bgSprite.setTexture(m_bgTexture);
	}
	else
	{
		std::cout << "Failed to load Texture : " << ss.str() << "\n";
	}
	m_bgTexture.setRepeated(true);
	m_bgSprite.setColor({0, 255, 0, 100});
}

void CSpawnManager::SetGameRunning(bool state)
{
	m_isGameRunning = state;
}

void CSpawnManager::UpdateSpawns(const float& deltaTime)
{
	// take key action from player (WASD)
	if (m_isGameRunning)
	{
		// take player input
		m_paddle->KeyAction(deltaTime);

		// check collision
		CheckCollisionWithBall();
		CheckCollisionWithBoundary();

		// update ball
		if (deltaTime < 0.100) // check
		{
			float offsetX = BALLVELOCITY * float(std::cos(ToRadian(m_angle))) * deltaTime;
			float offsetY = BALLVELOCITY * float(std::sin(ToRadian(m_angle))) * deltaTime;
			m_ball.move(offsetX, offsetY);
		}
		else
		{
			m_ball.move(0.0f, 0.0f);
		}

		// update the player
		m_paddle->Update(deltaTime);
	}
	else
	{
		if (m_paddle->GetInput().m_space.isPressed)
		{
			m_isGameRunning = true;
		}
	}
}

void CSpawnManager::RenderSpawns(sf::RenderTarget& target)
{
	if (m_isGameRunning)
	{
		// background (bottom)
		target.draw(m_bgSprite);

		// snake
		m_paddle->Render(target);

		// fruit
		target.draw(m_ball);

		//text
		DisplayMessage("Score : " + std::to_string(m_score1), sf::Color::Blue, {50.0f, 25.0f }, 24, target);
		DisplayMessage("Score : " + std::to_string(m_score2), sf::Color::Red, {WIDTH - 50.0f, 25.0f }, 24, target);

	}
	else
	{
		// background (bottom)
		target.draw(m_bgSprite);

		// snake
		m_paddle->Render(target);

		// fruit
		target.draw(m_ball);

		// text
		DisplayMessage("PING-PONG", sf::Color::White, { WIDTH / 2, HEIGHT / 2 - 100.0f  }, 96, target);
		DisplayMessage("-- Press SPACE to Start --", sf::Color::White, { WIDTH / 2, HEIGHT / 2 + 70.0f }, 24, target);
		DisplayMessage("-- Press ESC to Exit --", sf::Color::White, { WIDTH / 2, HEIGHT / 2 + 100.0f }, 24, target);

		DisplayMessage("W : P1-UP | S : P1-DOWN | UP : P2-UP | DOWN : P2-DOWN | F2 : SAVE | F3 : LOAD", sf::Color::White, { WIDTH/ 2, HEIGHT - 20.0f }, 18, target);
	}
}

void CSpawnManager::RandomizeAngle()
{
	srand(time(0));
	do 
	{
		m_angle = rand() % 360;
	} while (m_angle == 90 || m_angle == 270 || m_angle == 0 ); // vertical and horizontal shoot is not allowed
}

void CSpawnManager::CheckCollisionWithBall()
{
	if (m_paddle->GetPaddle1Bounds().intersects(m_ball.getGlobalBounds()) || m_paddle->GetPaddle2Bounds().intersects(m_ball.getGlobalBounds()) )
	{

		m_angle = (m_angle >= 180) ? 180 - m_angle : 540 - m_angle;
	}

}

void CSpawnManager::CheckCollisionWithBoundary()
{
	// paddle 1
	if (m_paddle->GetPaddle1Bounds().top < 0.0f)
	{
		m_paddle->SetPaddle1Position({ m_paddle->GetPaddle1Bounds().left, 0.0f });
		m_paddle->SetPaddle1Velocity(0.0f);
	}
	else if (m_paddle->GetPaddle1Bounds().top + m_paddle->GetPaddle1Bounds().height > HEIGHT)
	{
		m_paddle->SetPaddle1Position({ m_paddle->GetPaddle1Bounds().left, HEIGHT - m_paddle->GetPaddle1Bounds().height });
		m_paddle->SetPaddle1Velocity(0.0f);
	}

	// paddle 2
	if (m_paddle->GetPaddle2Bounds().top < 0.0f)
	{
		m_paddle->SetPaddle2Position({ m_paddle->GetPaddle2Bounds().left, 0.0f });
		m_paddle->SetPaddle2Velocity(0.0f);
	}
	else if (m_paddle->GetPaddle2Bounds().top + m_paddle->GetPaddle2Bounds().height > HEIGHT)
	{
		m_paddle->SetPaddle2Position({ m_paddle->GetPaddle2Bounds().left, HEIGHT - m_paddle->GetPaddle2Bounds().height });
		m_paddle->SetPaddle2Velocity(0.0f);
	}

	// ball
	if (m_ball.getGlobalBounds().top < 0.0f || m_ball.getGlobalBounds().top + m_ball.getGlobalBounds().height > HEIGHT) // top and bottom
	{
		m_angle = 360 - m_angle;
	}
	else if (m_ball.getGlobalBounds().left < 0.0f) // left
	{
		m_angle = (m_angle >= 180) ? 180 - m_angle : 540 - m_angle;
		m_score2++;
	}
	else if (m_ball.getGlobalBounds().left + m_ball.getGlobalBounds().width > WIDTH) //right
	{
		m_angle = (m_angle >= 180) ? 180 - m_angle : 540 - m_angle;
		m_score1++;
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

void CSpawnManager::ResetGameState()
{
	// paddle reset
	m_paddle->SetPaddle1Position({ 5.0f, HEIGHT / 2 });
	m_paddle->SetPaddle2Position({ WIDTH - 20.0f, HEIGHT / 2 });

	// ball reset
	m_ball.setPosition({ WIDTH / 2, HEIGHT / 2 });
	RandomizeAngle();
}

//void CSpawnManager::SaveGameState()
//{
//	if (m_isGameRunning)
//	{
//		flatbuffers::FlatBufferBuilder builder;
//
//		// storing : enemy position
//
//		// Shortcut for creating monster with all fields set:
//		// storing :  has key boolean
//		auto gameData = CreateGameState(builder, m_score1, m_score2);
//
//		builder.Finish(gameData);  // Serialize the root of the object.
//
//		// We now have a FlatBuffer we can store on disk or send over a network. 
//		std::ofstream ofs("pingpong.sav", std::ofstream::binary);
//		ofs.write((char*)builder.GetBufferPointer(), builder.GetSize());
//		ofs.close();
//
//		// confirm on console
//		std::cout << "Game Saved! Save File Created Successfully!\n";
//	}
//}
//
//void CSpawnManager::LoadGameState()
//{
//
//	std::ifstream infile;
//	infile.open("pingpong.sav", std::ios::binary | std::ios::in);
//	if (infile)
//	{
//		infile.seekg(0, std::ios::end);
//		int length = infile.tellg();
//		infile.seekg(0, std::ios::beg);
//		char* data = new char[length];
//		infile.read(data, length);
//		infile.close();
//		auto gamedata = GetGameState(data);
//
//		int score1 = gamedata->bluescore();
//		int score2 = gamedata->redscore();
//
//		m_score1 = score1;
//		m_score2 = score2;
//
//		ResetGameState();
//		// confirm on console
//		std::cout << "Save File Loaded Successfully!\n";
//	}
//
//}

CSpawnManager::~CSpawnManager()
{
}

