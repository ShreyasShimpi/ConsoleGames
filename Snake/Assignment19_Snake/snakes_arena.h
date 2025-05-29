#pragma once
#include <memory>
#include "snakes_snake.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27

void gotoxy(int x, int y);

void set_cursor(bool visible);

class CBoard
{
private:
	std::unique_ptr<CSnake> m_snake;
	COORD m_applePosition;
	int m_score;
	int m_trail;
	bool m_over;
	// if snake can go through wall
	bool m_goThroughWall;
	// if snake can go through itself
	bool m_goThroughItself;
public:
	CBoard(bool, bool);
	void RandomizeApple();
	void PrintBoard();

	void CheckColllisionWithApple();
	void CheckColllisionWithWall(bool);
	void CheckColllisionWithItself();

	void UpdateBoard();
};