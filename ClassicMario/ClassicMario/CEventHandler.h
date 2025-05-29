#pragma once

// external includes
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <functional>

// listener function object
#define FUNCTIONHANDLER std::function<void(const sf::Event)>

/*
	Handles the events generated while the program is running
*/
class CEventHandler
{
private:
	std::map<sf::Event::EventType, std::vector<const FUNCTIONHANDLER*>> m_listenerFunctions;
public:
	// constructor
	CEventHandler() = default;

	// getter
	const auto& GetListeners(){return m_listenerFunctions;};

	// register the given listeners to this handler
	void RegisterEventListner(sf::Event::EventType, const FUNCTIONHANDLER*);

	// Poll and call the listeners
	void CallEvent(sf::RenderWindow&);
};
