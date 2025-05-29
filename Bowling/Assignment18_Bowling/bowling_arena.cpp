#include <iostream>
#include <algorithm>
#include <Windows.h>
#include <ctime>
#include <cmath>

#include "bowling_arena.h"


void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

double ToRadian(int degree)
{
	double radian = degree * PI / 180;
	return radian;
}

void DelayMessage(int seconds)
{
	std::cout << "\n\n";
	for (int i = seconds; i >= 0; i--)
	{
		std::cout << "Next Turn in ... "<< i <<"\r";
		Sleep(1000);
	}
}

CBowlingArena::CBowlingArena()
{
	m_offset = 5;
	initialBallPositionX = m_offset + 2;
	initialBallPositionY = m_offset + WIDTH / 2;

	m_angleLowerLimit = atan(LENGTH / WIDTH) * 180 / PI - 2;
	m_angleUpperLimit = 180 - m_angleLowerLimit;
}

int CBowlingArena::GetScoreByAngle(int pinsOnArena, int angle)
{
	srand(time(0));
	if (angle < m_angleLowerLimit || angle > m_angleUpperLimit)
	{
		return 0;
	}
	// in this angle range only 
	else if (angle > m_angleLowerLimit || angle < m_angleUpperLimit)
	{
		return rand() % (pinsOnArena + 1);
	}
}

void CBowlingArena::PrintPins(int numberofPins)
{
	for (int pin = 1; pin <= PINS; pin++)
	{
		if (pin <= numberofPins)
		{
			m_pinsState.push_back('&');
		}
		else
		{
			m_pinsState.push_back(' ');
		}
	}
	// shuffle the pins position
	std::random_shuffle(m_pinsState.begin(), m_pinsState.end());

	// draw pins
	int index = 0;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4 - x && index < PINS; y++)
		{
			/*
				2x -1 gives space to pins,
				x + 2y gives proper gap from top
			*/
			gotoxy(m_offset + LENGTH - 2 * x - 1, m_offset + (WIDTH / 7) * x + 2 * (WIDTH / 7) * y + 1);
			std::cout << m_pinsState[index];
			index++;
		}
	}
}
void CBowlingArena::PrintBall(int x, int y)
{
	gotoxy(x, y);
	std::cout << 'O';
}

void CBowlingArena::PrintBoard()
{
	for (int row = m_offset; row <= WIDTH + m_offset; row++)
	{
		if (row == m_offset || row == WIDTH + m_offset)
		{
			for (int i = m_offset; i <= LENGTH + m_offset + 1; i++)
			{
				gotoxy(i, row);
				std::cout << "#";
			}
		}
		else
		{
			gotoxy(m_offset, row);
			std::cout << "#";
			gotoxy(m_offset + LENGTH + 1, row);
			std::cout << "#";
		}
	}
}

void CBowlingArena::PrintArena(int x, int y, int numberOfPins)
{
	PrintBoard();
	PrintPins(numberOfPins);
	PrintBall(x, y);
	gotoxy(0, m_offset + WIDTH + 1);
	std::cout << "\n\n\n";
}

void CBowlingArena::AnimateArena(int angle, int numberOfPins)
{
	double ballPositionX = initialBallPositionX;
	double ballPositionY = initialBallPositionY;
	bool collision = false;
	while (!collision)
	{
		system("cls");
		PrintArena(round(ballPositionX), round(ballPositionY), numberOfPins);

		// check collision
		if ((int)ballPositionX >= m_offset + LENGTH - 1 || (int)ballPositionY <= m_offset || (int)ballPositionY >= m_offset + WIDTH)
		{
			collision = true;
		}

		// 8 and 2 are factors by trail and error , because of console pixel
		ballPositionX = ballPositionX + 8.0 * sin(ToRadian(angle));
		ballPositionY = ballPositionY + 2.0 * cos(ToRadian(angle));
	}

	gotoxy(0, m_offset + WIDTH + 1);
	std::cout << "\n\n\n";
}