#include "InputHandler.h"
#include <iostream>
void HandleKeyPress(sf::Event& event, CButton& input)
{
	switch (event.key.code)
	{
	case sf::Keyboard::W:
	{
		input.m_w.isPressed = true;
	}
	break;
	case sf::Keyboard::A:
	{
		input.m_a.isPressed = true;
	}
	break;
	case sf::Keyboard::S:
	{
		input.m_s.isPressed = true;
	}
	break;
	case sf::Keyboard::D:
	{
		input.m_d.isPressed = true;
	}
	break;
	case sf::Keyboard::LShift:
	{
		input.m_leftShift.isPressed = true;
	}
	break;
	case sf::Keyboard::Space:
	{
		input.m_space.isPressed = true;
	}
	break;
	case sf::Keyboard::Up:
	{
		input.m_up.isPressed = true;
	}
	break;
	case sf::Keyboard::Down:
	{
		input.m_down.isPressed = true;
	}
	break;
	default:
		break;
	}
}

void HandleKeyRelease(sf::Event& event, CButton& input)
{
	switch (event.key.code)
	{
	case sf::Keyboard::W:
	{
		input.m_w.isPressed = false;
		input.m_w.isToggled = !input.m_w.isToggled;
	}
	break;
	case sf::Keyboard::A:
	{
		input.m_a.isPressed = false;
		input.m_a.isToggled = !input.m_a.isToggled;
	}
	break;
	case sf::Keyboard::S:
	{
		input.m_s.isPressed = false;
		input.m_s.isToggled = !input.m_s.isToggled;
	}
	break;
	case sf::Keyboard::D:
	{
		input.m_d.isPressed = false;
		input.m_d.isToggled = !input.m_d.isToggled;
	}
	break;
	case sf::Keyboard::LShift:
	{
		input.m_leftShift.isPressed = false;
		input.m_leftShift.isToggled = !input.m_leftShift.isToggled;
	}
	break;
	case sf::Keyboard::Space:
	{
		input.m_space.isPressed = false;
		input.m_space.isToggled = !input.m_space.isToggled;
	}
	break;
	case sf::Keyboard::Up:
	{
		input.m_up.isPressed = false;
		input.m_up.isToggled = !input.m_space.isToggled;
	}
	break;
	case sf::Keyboard::Down:
	{
		input.m_down.isPressed = false;
		input.m_down.isToggled = !input.m_space.isToggled;
	}
	break;
	default:
		break;
	}
}

void HandleMouseClick(sf::Event& event, CMouse& input)
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		input.m_mouseClickPosition = {event.mouseButton.x, event.mouseButton.y};
		input.m_left.isPressed = true;
	}
	if (event.mouseButton.button == sf::Mouse::Right)
	{
		input.m_mouseClickPosition = {event.mouseButton.x, event.mouseButton.y};
		input.m_right.isPressed = true;
	}
}

void HandleMouseClickReleased(sf::Event& event, CMouse& input)
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		input.m_left.isPressed = false;
		input.m_left.isHeld = false;
	}
	if (event.mouseButton.button == sf::Mouse::Right)
	{
		input.m_right.isPressed = false;
		input.m_right.isHeld = false;
	}
}

void HandleMouseMoved(sf::Event& event, CMouse& input)
{
	input.m_mousePosition = { event.mouseMove.x,  event.mouseMove.y };
}
