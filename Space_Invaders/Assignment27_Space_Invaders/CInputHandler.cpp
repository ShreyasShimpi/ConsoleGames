#include "CInputHandler.h"

void CInputHandler::UpdateKeys(sf::Event& evnt)
{
	// check if the event is for either key press or key release
	if (!(evnt.type == sf::Event::KeyPressed || evnt.type == sf::Event::KeyReleased))
	{
		return;
	}

	// check if the key is present in the map
	// if not add it
	auto key = evnt.key.code;
	if (m_keys.find(key) == m_keys.end())
	{
		m_keys[key] = {false, false};
	}

	// key press
	if (evnt.type == sf::Event::KeyPressed)
	{
		// key was already in pressed state, so repeating
		if (m_keys[key].first == true)
		{
			m_keys[key].second = true;
		}
		else
		{
			m_keys[key].first = true;
		}
	}

	// key release
	if (evnt.type == sf::Event::KeyReleased)
	{
		m_keys[key].first = false;
		m_keys[key].second = false;
	}
}

bool CInputHandler::IsPressed(sf::Keyboard::Key key)
{
	if (m_keys.find(key) == m_keys.end())
	{
		return false;
	}
	return m_keys[key].first;
}

bool CInputHandler::IsRepeating(sf::Keyboard::Key key)
{
	if (m_keys.find(key) == m_keys.end())
	{
		return false;
	}
	return m_keys[key].second;
}
