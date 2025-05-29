#pragma once
// internal included
#include "SFML/Graphics.hpp"

class CKeyState
{
public:
	bool isPressed = false;
	bool isToggled = false;
};

class CButton
{
public:
	CKeyState m_w, m_a, m_s, m_d, m_space, m_leftShift, m_up, m_down;
	
};

void HandleKeyPress(sf::Event& event, CButton& input);
void HandleKeyRelease(sf::Event& event, CButton& input);