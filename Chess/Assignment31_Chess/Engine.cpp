// external includes
#include <iostream>

// internal includes
#include "Engine.h"


void CEngine::PollCloseEvents()
{
	while (m_window->pollEvent(m_event))
	{
		switch (m_event.type)
		{
		case sf::Event::Closed:
		{
			m_window->close();
			break;
		}
		case sf::Event::KeyPressed:
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
			{
				m_window->close();
				break;
			}
			break;
		}
		default:
			break;
		}
	}
}

CEngine::CEngine(unsigned int width, unsigned int height)
{
	m_videoMode = std::make_unique<sf::VideoMode>(width, height);
	m_window = std::make_unique<sf::RenderWindow>(*m_videoMode, "CHESS", sf::Style::Resize | sf::Style::Close);
	m_window->setKeyRepeatEnabled(false);
	m_chess = std::make_unique<CChess>();
}

void CEngine::Update()
{
	m_time.Tick();
	PollCloseEvents();

	m_chess->UpdateSFML(*m_window, m_event);
	//m_chess->UpdateConsole();
}

void CEngine::Render()
{
	// Start of the frame
	m_window->clear();        // clear previous content

	m_chess->Render(*m_window);

	m_window->display();            // display everything after drawing done
	// End of the frame

	//DEBUG DELTATIME
	//std::cout << "delta : " << m_time.DeltaTime() << "\n";
}

CEngine::~CEngine()
{
}
