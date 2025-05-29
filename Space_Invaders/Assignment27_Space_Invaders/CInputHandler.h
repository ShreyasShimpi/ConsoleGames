#pragma once
#include <SFML/Graphics.hpp>
#include <map>

/*
	Stores all the key inputs
*/
class CInputHandler
{
private:	// is key pressed?, is key repeating.
	std::map<sf::Keyboard::Key, std::pair<bool, bool>> m_keys;

public:
	CInputHandler() = default;
	~CInputHandler() = default;

	// checks the event and update which key to keep pressing and which to release
	void UpdateKeys(sf::Event& evnt);

	// returns if the given key is currently in pressed state
	bool IsPressed(sf::Keyboard::Key key);

	// returns if the given key press is being repeated
	bool IsRepeating(sf::Keyboard::Key key);
};

