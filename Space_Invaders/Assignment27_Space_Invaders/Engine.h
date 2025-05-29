#pragma once
// external includes
#include <SFML/Graphics.hpp>
#include <vector>

// internal includes
#include "time.h"
#include "EventHandler.h"
#include "SpawnManager.h"

class CEngine
{
private:
	// variables
	std::unique_ptr<sf::VideoMode> m_videoMode;
	std::unique_ptr<sf::RenderWindow> m_window;
	//CEventHandler* m_event;
	//CSpawnManager* m_spawnManager;
	std::unique_ptr<CEventHandler> m_event;
	std::unique_ptr<CSpawnManager> m_spawnManager;
	CTime m_time;

	// listener function objects
	FUNCTIONHANDLER m_windowCloseListenerCB;
	FUNCTIONHANDLER m_keyPressedListnerCB;

	// listener functions
	void WindowCloseListener(sf::Event);
	void KeyPressedListner(sf::Event);
	void RegisterEvents();

public:
	//constructor/ destructor
	CEngine(unsigned int width, unsigned int height);
	~CEngine();

	//member functions
	inline const bool IsWindowRunning() const { return m_window->isOpen(); };
	void Update();
	void Render();

	// setter

	// getter for event handler
	inline CEventHandler& GetEventHandler() { return *m_event; };
};

