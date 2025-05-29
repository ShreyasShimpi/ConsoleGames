#pragma once

#include <SFML\Graphics.hpp>
#include <memory>
#include "CEventHandler.h"
#include "CTime.h"

class CSpawnManager;
class CInputHandler;

class CGame
{
public:

	CGame(int resX, int resY, std::string appName);
	
	void OnWindowClose(sf::Event event); 
	void SetTotalTime(int value) { m_totalTime = value; }

	// getter
	sf::RenderWindow& GetRenderWindow() { return *m_window; }
	sf::View& GetView() { return m_view; }
	CEventHandler& GetEventHandler() { return *m_eventHandler; }
	CInputHandler& GetInputHandler() { return *m_inputHandler; }
	float GetTotalTime() { return m_totalTime; }

	void Draw(); // render sprites
	void Run(); // game loop

	~CGame();

private:
	std::shared_ptr<sf::RenderWindow> m_window;
	sf::View m_view;
	sf::VideoMode m_videoMode;
	sf::Event m_event;

	// window title
	std::string m_winTitle;

	// time class obj
	CTime m_time;
	// pointer to event handler
	CEventHandler* m_eventHandler;

	// events
	FUNCTIONHANDLER onWindowCloseCB;

	// pointer to spawnManager obj
	std::shared_ptr<CSpawnManager> m_spawnManager;
	// pointer to InputHandler obj
	std::shared_ptr<CInputHandler> m_inputHandler;

	float m_totalTime;
};
