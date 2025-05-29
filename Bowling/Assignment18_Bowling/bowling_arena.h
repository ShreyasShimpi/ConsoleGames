#pragma once
#include <vector>

#define PI 3.14159

#define WIDTH 14
#define LENGTH 120

#define PINS 10
#define MAXANGLE 180

class CBowlingArena
{
private:
	std::vector<char> m_pinsState;
	int m_angleUpperLimit;
	int m_angleLowerLimit;
	int m_offset;
	
public:
	int initialBallPositionX;
	int initialBallPositionY;
	CBowlingArena();
	int GetScoreByAngle(int, int);
	void PrintBall(int x, int y);
	void PrintPins(int numberofPins);
	void PrintBoard();
	void PrintArena(int x, int y , int numberOfPins);
	void AnimateArena(int angle, int numberOfPins);
};

void gotoxy(int x, int y);

double ToRadian(int degree);

void DelayMessage(int seconds);