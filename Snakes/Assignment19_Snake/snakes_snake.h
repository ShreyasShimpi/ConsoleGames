#pragma once
#include <Windows.h>
#include <vector>

#define WIDTH 80
#define HEIGHT 40

#define HEAD 0

enum class EDirection
{
	UP, DOWN, LEFT, RIGHT, STOP
};

class CSnake
{
private:
	std::vector<COORD> m_snake;
	EDirection m_direction;
	int m_velocity;
public:
	CSnake();
	COORD GetSnakePosition(int index);

	void SetSnakeHeadPositionX(int);
	void SetSnakeHeadPositionY(int);

	void ChangeDirection(EDirection dir);
	void UpdateTrail(COORD);
	void AddTrail();
	void MoveSnake();
};

