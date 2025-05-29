#include <iostream>
#include "CEventHandler.h"

void CEventHandler::RegisterEventListner(sf::Event::EventType eventType, const FUNCTIONHANDLER* function)
{
	m_listenerFunctions[eventType].push_back(function);
}

void CEventHandler::CallEvent(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		const auto funtionsIter = m_listenerFunctions.find(event.type);
		if (funtionsIter != m_listenerFunctions.end())
		{
			// runs all the functions serially inside the vector
			for (const auto& function : funtionsIter->second)
			{
				(*function)(event);
			}
		}
	}
}
