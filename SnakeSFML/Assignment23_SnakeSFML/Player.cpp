// external includes
#include <iostream>
#include <sstream>

// internal includes
#include "Player.h"
#include "Engine.h"


CSnake::CSnake(CEngine& engine)
{
	m_trailSize = 0;
	m_playerKeyPressedListnerCB = std::bind(&CSnake::PlayerKeyPressedListner, this, std::placeholders::_1);
	engine.GetEventHandler().RegisterEventListner(sf::Event::EventType::KeyPressed, &m_playerKeyPressedListnerCB);

	m_playerKeyReleasedListnerCB = std::bind(&CSnake::PlayerKeyReleasedListner, this, std::placeholders::_1);
	engine.GetEventHandler().RegisterEventListner(sf::Event::EventType::KeyReleased, &m_playerKeyReleasedListnerCB);

}

// listener functions that goes into event handler
void CSnake::PlayerKeyPressedListner(sf::Event event)
{
	HandleKeyPress(event, m_input);
}

void CSnake::PlayerKeyReleasedListner(sf::Event event)
{
	HandleKeyRelease(event, m_input);
}

// actual key press action
void CSnake::KeyPressAction(const float& deltaTime)
{
	// game play movement key events : W and S
	if (m_input.m_w.isPressed)
	{
		// movement opposite to current direction is not allowed
		if (m_headDirection.y != 1) // DOWN
		{
			m_headDirection = { 0, -1 }; // UP
		}
	}
	else if (m_input.m_s.isPressed)
	{
		// movement opposite to current direction is not allowed
		if (m_headDirection.y != -1) // UP
		{
			m_headDirection = { 0, 1 }; // DOWN
		}
	}
	else if (m_input.m_a.isPressed)
	{
		// movement opposite to current direction is not allowed
		if (m_headDirection.x != 1) // RIGHT
		{
			m_headDirection = { -1, 0 }; // LEFT
		}
	}
	else if (m_input.m_d.isPressed)
	{
		// movement opposite to current direction is not allowed
		if (m_headDirection.x != -1) // LEFT
		{
			m_headDirection = { 1, 0 }; // RIGHT
		}
	}
}

// actual key release action
void CSnake::KeyReleaseAction(const float& deltaTime)
{
}

sf::RectangleShape CSnake::CreateSnakeBodyBlock()
{
	sf::RectangleShape bodyBlock;
	bodyBlock.setFillColor(sf::Color(0, 200, 0, 100));
	bodyBlock.setSize({ float(SNAKE_BLOCKSIZE), float(SNAKE_BLOCKSIZE) });
	bodyBlock.setOutlineThickness(-1.0f);
	bodyBlock.setOutlineColor(sf::Color::Black);
	return bodyBlock;
}

void CSnake::InitTextures()
{
	// Head
	for (int i = 0; i < 4; ++i)
	{
		std::stringstream ss;
		ss << "Sprites/head(" << i << ").png";

		sf::Texture texture;

		if (texture.loadFromFile(ss.str()))
		{
			m_snakeHead.push_back(texture);
		}
		else
		{
			std::cout << "Failed to load Texture : " << ss.str() << "\n";
		}
	}

	// tail
	for (int i = 0; i < 4; ++i)
	{
		std::stringstream ss;
		ss << "Sprites/tail(" << i << ").png";

		sf::Texture texture;

		if (texture.loadFromFile(ss.str()))
		{
			m_snakeTail.push_back(texture);
		}
		else
		{
			std::cout << "Failed to load Texture : " << ss.str() << "\n";
		}
	}
	// body static
	for (int i = 0; i < 2; ++i)
	{
		std::stringstream ss;
		ss << "Sprites/body_static(" << i << ").png";

		sf::Texture texture;

		if (texture.loadFromFile(ss.str()))
		{
			m_snakBodyStaight.push_back(texture);
		}
		else
		{
			std::cout << "Failed to load Texture : " << ss.str() << "\n";
		}
	}
	// body curve
	for (int i = 0; i < 4; ++i)
	{
		std::stringstream ss;
		ss << "Sprites/body_curve(" << i << ").png";

		sf::Texture texture;

		if (texture.loadFromFile(ss.str()))
		{
			m_snakeBodyCurve.push_back(texture);
		}
		else
		{
			std::cout << "Failed to load Texture : " << ss.str() << "\n";
		}
	}
}

void CSnake::AddSnakeSprite(sf::Sprite sprite, sf::Vector2f position)
{
	m_snakeSprite.push_back(sprite);
	m_snakeSprite.back().setPosition(position);
	m_snakeSprite.back().setScale({ float(SNAKE_BLOCKSIZE) / float(SNAKE_SPRITESIZE), float(SNAKE_BLOCKSIZE) / float(SNAKE_SPRITESIZE) });
}

void CSnake::InitCharacter(float initialPositionX, float initialPositionY)
{
	// initialize textures
	InitTextures();

	// set head position
	m_headPosition.x = initialPositionX;
	m_headPosition.y = initialPositionY;
	m_headDirection = { 0, 0 };

	// sprite
	//head
	sf::Sprite headSprite;
	AddSnakeSprite(headSprite, { initialPositionX, initialPositionY });

	//tail
	sf::Sprite tailSprite;
	AddSnakeSprite(tailSprite, { initialPositionX, initialPositionY + SNAKE_BLOCKSIZE });
}

void CSnake::KeyAction(const float& deltaTime)
{
	KeyPressAction(deltaTime);
}

sf::FloatRect CSnake::GetBodyGlobalBounds(int index)
{
	if (index < m_trailSize)
	{
		return m_snakeSprite[index].getGlobalBounds();
	}
}

void CSnake::SetSnakeHeadPosition(sf::Vector2f position)
{
	m_headPosition = position;
	m_snakeSprite[HEAD].setPosition(m_headPosition);
}

void CSnake::AddTrail()
{
	// push another trail to snake 
	m_trailSize += 1;
	sf::Sprite snakeBody;
	AddSnakeSprite(snakeBody, { 0.0f, 0.0f });
}

void CSnake::UpdateTrail(sf::Vector2f headPosition)
{
	sf::Vector2f temp = headPosition;
	for (size_t i = 1; i < m_snakeSprite.size(); i++)
	{
		sf::Vector2f temp2 = m_snakeSprite[i].getPosition();
		m_snakeSprite[i].setPosition(temp);
		temp = temp2;
	}
}

void CSnake::UpdateTextures()
{
	for (size_t index = 0; index < m_snakeSprite.size(); index++)
	{
		// head
		if (index == HEAD)
		{
			if (m_headDirection == sf::Vector2i({ 1, 0 }))
			{
				m_snakeSprite[index].setTexture(m_snakeHead[RIGHT]);
			}
			if (m_headDirection == sf::Vector2i({ -1, 0 }))
			{
				m_snakeSprite[index].setTexture(m_snakeHead[LEFT]);
			}
			if (m_headDirection == sf::Vector2i({ 0, 1 }))
			{
				m_snakeSprite[index].setTexture(m_snakeHead[DOWN]);
			}
			if ((m_headDirection == sf::Vector2i({ 0, -1 })) || (m_headDirection == sf::Vector2i({ 0, 0 })))
			{
				m_snakeSprite[index].setTexture(m_snakeHead[UP]);
			}
		}

		// tail
		else if (index == m_snakeSprite.size() - 1)
		{
			if ((m_snakeSprite[index].getPosition().x > m_snakeSprite[index - 1].getPosition().x) && (m_snakeSprite[index].getPosition().y == m_snakeSprite[index - 1].getPosition().y))
			{
				m_snakeSprite[index].setTexture(m_snakeTail[LEFT]);
			}
			else if ((m_snakeSprite[index].getPosition().x < m_snakeSprite[index - 1].getPosition().x) && (m_snakeSprite[index].getPosition().y == m_snakeSprite[index - 1].getPosition().y))
			{
				m_snakeSprite[index].setTexture(m_snakeTail[RIGHT]);
			}
			else if ((m_snakeSprite[index].getPosition().x == m_snakeSprite[index - 1].getPosition().x) && (m_snakeSprite[index].getPosition().y > m_snakeSprite[index - 1].getPosition().y))
			{
				m_snakeSprite[index].setTexture(m_snakeTail[UP]);
			}
			else if ((m_snakeSprite[index].getPosition().x == m_snakeSprite[index - 1].getPosition().x) && (m_snakeSprite[index].getPosition().y < m_snakeSprite[index - 1].getPosition().y))
			{
				m_snakeSprite[index].setTexture(m_snakeTail[DOWN]);
			}
		}

		// body
		else
		{
			// straight body part
			if ((m_snakeSprite[index].getPosition().y == m_snakeSprite[index - 1].getPosition().y) && (m_snakeSprite[index].getPosition().y == m_snakeSprite[index + 1].getPosition().y))
			{
				m_snakeSprite[index].setTexture(m_snakBodyStaight[HORIZONTAL]);
			}
			else if ((m_snakeSprite[index].getPosition().x == m_snakeSprite[index - 1].getPosition().x) && (m_snakeSprite[index].getPosition().x == m_snakeSprite[index + 1].getPosition().x))
			{
				m_snakeSprite[index].setTexture(m_snakBodyStaight[VERTICAL]);
			}

			// curved body part
			else if ((((m_snakeSprite[index].getPosition().x == m_snakeSprite[index - 1].getPosition().x) && (m_snakeSprite[index].getPosition().x > m_snakeSprite[index + 1].getPosition().x)) &&  // moving up
				(((m_snakeSprite[index].getPosition().y > m_snakeSprite[index - 1].getPosition().y) && (m_snakeSprite[index].getPosition().y == m_snakeSprite[index + 1].getPosition().y))))
				||
				((((m_snakeSprite[index].getPosition().x > m_snakeSprite[index - 1].getPosition().x) && (m_snakeSprite[index].getPosition().x == m_snakeSprite[index + 1].getPosition().x)) &&  // moving left
				((m_snakeSprite[index].getPosition().y == m_snakeSprite[index - 1].getPosition().y) && (m_snakeSprite[index].getPosition().y > m_snakeSprite[index + 1].getPosition().y)))))
			{
				m_snakeSprite[index].setTexture(m_snakeBodyCurve[DOWN_TO_LEFT]);
			}




			else if ((((m_snakeSprite[index].getPosition().x == m_snakeSprite[index - 1].getPosition().x) && (m_snakeSprite[index].getPosition().x < m_snakeSprite[index + 1].getPosition().x)) &&  // moving up
				(((m_snakeSprite[index].getPosition().y > m_snakeSprite[index - 1].getPosition().y) && (m_snakeSprite[index].getPosition().y == m_snakeSprite[index + 1].getPosition().y))))
				||
				((((m_snakeSprite[index].getPosition().x < m_snakeSprite[index - 1].getPosition().x) && (m_snakeSprite[index].getPosition().x == m_snakeSprite[index + 1].getPosition().x)) &&  // moving left
				((m_snakeSprite[index].getPosition().y == m_snakeSprite[index - 1].getPosition().y) && (m_snakeSprite[index].getPosition().y > m_snakeSprite[index + 1].getPosition().y)))))
			{
				m_snakeSprite[index].setTexture(m_snakeBodyCurve[DOWN_TO_RIGHT]);
			}



			else if ((((m_snakeSprite[index].getPosition().x > m_snakeSprite[index - 1].getPosition().x) && (m_snakeSprite[index].getPosition().x == m_snakeSprite[index + 1].getPosition().x)) &&  // moving up
				(((m_snakeSprite[index].getPosition().y == m_snakeSprite[index - 1].getPosition().y) && (m_snakeSprite[index].getPosition().y < m_snakeSprite[index + 1].getPosition().y))))
				||
				((((m_snakeSprite[index].getPosition().x == m_snakeSprite[index - 1].getPosition().x) && (m_snakeSprite[index].getPosition().x > m_snakeSprite[index + 1].getPosition().x)) &&  // moving left
				((m_snakeSprite[index].getPosition().y < m_snakeSprite[index - 1].getPosition().y) && (m_snakeSprite[index].getPosition().y == m_snakeSprite[index + 1].getPosition().y)))))
			{
				m_snakeSprite[index].setTexture(m_snakeBodyCurve[UP_TO_LEFT]);
			}



			else if ((((m_snakeSprite[index].getPosition().x < m_snakeSprite[index - 1].getPosition().x) && (m_snakeSprite[index].getPosition().x == m_snakeSprite[index + 1].getPosition().x)) &&  // moving up
				(((m_snakeSprite[index].getPosition().y == m_snakeSprite[index - 1].getPosition().y) && (m_snakeSprite[index].getPosition().y < m_snakeSprite[index + 1].getPosition().y))))
				||
				((((m_snakeSprite[index].getPosition().x == m_snakeSprite[index - 1].getPosition().x) && (m_snakeSprite[index].getPosition().x < m_snakeSprite[index + 1].getPosition().x)) &&  // moving left
				((m_snakeSprite[index].getPosition().y < m_snakeSprite[index - 1].getPosition().y) && (m_snakeSprite[index].getPosition().y == m_snakeSprite[index + 1].getPosition().y)))))
			{
				m_snakeSprite[index].setTexture(m_snakeBodyCurve[UP_TO_RIGHT]);
			}
		}
	}
}


void CSnake::Move(const float& deltaTime)
{
	//m_headPosition.x += (MAXSPEED * m_headDirection.x * deltaTime);
	//m_headPosition.y += (MAXSPEED * m_headDirection.y * deltaTime);

	m_headPosition.x += m_headDirection.x * SNAKE_BLOCKSIZE;
	m_headPosition.y += m_headDirection.y * SNAKE_BLOCKSIZE;

	m_snakeSprite[HEAD].setPosition({ m_headPosition.x, m_headPosition.y });
}

void CSnake::Update(const float& deltaTime)
{
	sf::Vector2f prevHeadPosition = m_headPosition;
	Move(deltaTime); // delta passed is in seconds
	if (m_headPosition != prevHeadPosition)
	{
		UpdateTrail(prevHeadPosition);
	}
	UpdateTextures();
}

void CSnake::Render(sf::RenderTarget& target)
{
	for (const auto& snakeSprite : m_snakeSprite)
	{
		target.draw(snakeSprite);
	}

}