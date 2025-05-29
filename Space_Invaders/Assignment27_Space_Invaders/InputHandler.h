#pragma once
// internal included
#include "SFML/Graphics.hpp"

// keyboard
class CKeyState
{
public:
	bool isPressed = false;
	bool isToggled = false;
};

class CButton
{
public:
	CKeyState m_w, m_a, m_s, m_d, m_space, m_leftShift, m_up, m_down, m_enter;
	
};

// mouse
class CClickstate
{
public:
	bool isPressed = false;
	bool isHeld = false;
};

class CMouse
{
public:
	sf::Vector2i m_mousePosition;
	sf::Vector2i m_mouseClickPosition;
	CClickstate m_left, m_right;
};

// keyboard
void HandleKeyPress(sf::Event& event, CButton& input);
void HandleKeyRelease(sf::Event& event, CButton& input);

// mouse
void HandleMouseClick(sf::Event& event, CMouse& input);
void HandleMouseClickReleased(sf::Event& event, CMouse& input);
void HandleMouseMoved(sf::Event& event, CMouse& input);