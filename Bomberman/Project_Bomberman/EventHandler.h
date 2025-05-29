#pragma once

// external includes
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <functional>

// listener function object
#define FUNCTIONHANDLER std::function<void(const sf::Event)>

class CEventHandler
{
private:
	std::map<sf::Event::EventType, std::vector<const FUNCTIONHANDLER*>> m_listenerFunctions;
public:
	// constructor
	CEventHandler();
	void RegisterEventListner(sf::Event::EventType, const FUNCTIONHANDLER*);
	void DeregisterEventListner(sf::Event::EventType, const FUNCTIONHANDLER*);
	void CallEvent(sf::RenderWindow&);
};
