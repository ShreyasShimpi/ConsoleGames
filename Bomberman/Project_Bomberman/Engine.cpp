// external includes
#include <iostream>

// internal includes
#include "Engine.h"


CEngine::CEngine(unsigned int width, unsigned int height)
{
	m_isGameOver = false;

	m_videoMode = new sf::VideoMode(width, height);
	m_window = new sf::RenderWindow(*m_videoMode, "!!BomberMan!!", sf::Style::Resize | sf::Style::Close);

	m_event = new CEventHandler();
	m_spawnManager = new CSpawnManager(*this, width, height);

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
	m_window->clear();              // clear previous content
	m_spawnManager->RenderSpawns(*m_window);

	m_window->display();            // display everything after drawing done
	// End of the frame


	//DEBUG DELTATIME
	//std::cout << "delta : " << m_time.DeltaTime() << "\n";
}

void CEngine::SetGameState(bool gameState)
{
	m_isGameOver = gameState;
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
	// closing event
	if (event.key.code == sf::Keyboard::Key::Escape)
	{
		std::cout << "Window Closed With Escape!\n";
		m_window->close();
	}
	if (event.key.code == sf::Keyboard::Key::Enter && m_isGameOver)
	{
		m_isGameOver = false;

		m_spawnManager = nullptr;
		m_event = nullptr;

		m_event = new CEventHandler();
		RegisterEvents();
		m_spawnManager = new CSpawnManager(*this, m_videoMode->width, m_videoMode->height);
	}
}

CEngine::~CEngine()
{
	delete m_window;
	delete m_videoMode;
	delete m_spawnManager;
	delete m_event;
}
