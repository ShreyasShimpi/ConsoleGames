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
	sf::VideoMode* m_videoMode;
	sf::RenderWindow* m_window;
	CEventHandler* m_event;
	CTime m_time;
	CSpawnManager* m_spawnManager;

	bool m_isGameOver;

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

	// setter for game state
	void SetGameState(bool gameState);

	// getter for event handler
	inline CEventHandler& GetEventHandler() { return *m_event; };
};

