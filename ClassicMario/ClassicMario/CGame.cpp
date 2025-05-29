#include "CGame.h"
#include <iostream>
#include "CSpawnManager.h"
#include "CInputHandler.h"

CGame::CGame(int resX, int resY, std::string appName)
{
	// create game window
	m_videoMode.width = resX;
	m_videoMode.height = resY;
	m_winTitle = appName;
	m_window = std::make_shared<sf::RenderWindow>(m_videoMode, m_winTitle);

	// setting view
	m_view.setCenter(sf::Vector2f(150.0f, 112.0f));
	m_view.setSize(sf::Vector2f(300.0f, 224.0f));
	m_window->setView(m_view);

	// creating event handler obj.
	m_eventHandler = new CEventHandler();

	// subscribing to close window event
	onWindowCloseCB = std::bind(&CGame::OnWindowClose, this, std::placeholders::_1);
	m_eventHandler->RegisterEventListner(sf::Event::EventType::Closed, &onWindowCloseCB);

	// creating spawn manager obj.
	m_spawnManager = std::make_shared<CSpawnManager>(*this);

	// creating input handler obj.
	m_inputHandler = std::make_shared<CInputHandler>();
	
}

void CGame::Run()
{
	// single loop represents to a single frame
	m_totalTime = 0.0f;

	while (m_window->isOpen())
	{
		// calculating the delta time for each frame using time class
		m_time.Tick();

		sf::Event event;
		while (m_window->pollEvent(event))
		{
			// update the input handler
			m_inputHandler->UpdateKeys(event);

			const auto funtionsIter = m_eventHandler->GetListeners().find(event.type);
			if (funtionsIter != m_eventHandler->GetListeners().end())
			{
				// runs all the functions serially inside the vector
				for (const auto& function : funtionsIter->second)
				{
					(*function)(event);
				}
			}
		}
		// calling spawn manager update
		m_spawnManager->Update(m_time.GetFrameTime(), *m_window);
		Draw();
	}
}

void CGame::Draw()
{
	m_window->clear();
	m_spawnManager->Draw();
	m_window->display();
}

void CGame::OnWindowClose(sf::Event event)
{
	std::cout << " window closing\n";
	m_window->close();

}

CGame :: ~CGame()
{
	delete m_eventHandler;
	std::cout << " Engine Destructor Called\n";
}