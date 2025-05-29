#pragma once
// external includes
#include <SFML/Graphics.hpp>
#include <vector>

// internal includes
#include "time.h"
#include "CChess.h"

class CEngine
{
private:
	// variables
	std::unique_ptr<sf::VideoMode> m_videoMode;
	std::unique_ptr<sf::RenderWindow> m_window;
	std::unique_ptr<CChess> m_chess;

	sf::Event m_event;
	CTime m_time;

	// functions
	void PollCloseEvents();

public:
	//constructor/ destructor
	CEngine(unsigned int width, unsigned int height);
	~CEngine();

	//member functions
	inline const bool IsWindowRunning() const { return m_window->isOpen(); };
	void Update();
	void Render();

	// setter
};

