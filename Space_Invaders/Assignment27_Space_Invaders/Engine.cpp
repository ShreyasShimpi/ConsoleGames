// external includes
#include <iostream>

// internal includes
#include "Engine.h"


CEngine::CEngine(unsigned int width, unsigned int height)
{
	m_videoMode = std::make_unique<sf::VideoMode>(width, height);
	m_window = std::make_unique<sf::RenderWindow>(*m_videoMode, "Player Bullet", sf::Style::Resize | sf::Style::Close);
	
	//m_event = new CEventHandler();
	//m_spawnManager = new CSpawnManager(*this, width, height);

	m_event = std::make_unique<CEventHandler>();
	m_spawnManager = std::make_unique<CSpawnManager>(*this);

	// register in-game event listeners
	RegisterEvents();
}

void CEngine::Update()
{
	m_time.Tick();
	m_event->CallEvent(*m_window);
	m_spawnManager->UpdateSpawns((float)m_time.DeltaTime());
}

void CEngine::Render()
{
	// Start of the frame
	m_window->clear();        // clear previous content

	m_spawnManager->RenderSpawns(*m_window);

	m_window->display();            // display everything after drawing done
	// End of the frame

	//DEBUG DELTATIME
	//std::cout << "delta : " << m_time.DeltaTime() << "\n";
}

void CEngine::RegisterEvents()
{
	// to bind listener function to callback listener functions
	m_windowCloseListenerCB = std::bind(&CEngine::WindowCloseListener, this, std::placeholders::_1);
	m_event->RegisterEventListner(sf::Event::EventType::Closed, &m_windowCloseListenerCB);

	m_keyPressedListnerCB = std::bind(&CEngine::KeyPressedListner, this, std::placeholders::_1);
	m_event->RegisterEventListner(sf::Event::EventType::KeyPressed, &m_keyPressedListnerCB);
}

void CEngine::WindowCloseListener(sf::Event event)
{
	std::cout << "Window Closed!\n";
	m_window->close();
}

void CEngine::KeyPressedListner(sf::Event event)
{
	
	if (event.key.code == sf::Keyboard::Key::Escape)
	{
		std::cout << "Window Closed With Escape!\n"; // else, close event
		m_window->close();
	}

	// save game
	//if (event.key.code == sf::Keyboard::Key::F2)
	//{
	//	m_spawnManager->SaveGameState();
	//}

	//// load game
	//if (event.key.code == sf::Keyboard::Key::F3)
	//{
	//	m_spawnManager->LoadGameState();
	//}
}

CEngine::~CEngine()
{
	//delete m_spawnManager;
	//delete m_event;
}
