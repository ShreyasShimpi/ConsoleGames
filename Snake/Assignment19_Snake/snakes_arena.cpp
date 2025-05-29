#include <iostream>
#include <conio.h>
#include <cmath>
#include <ctime>

#include "snakes_arena.h"


void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void set_cursor(bool visible) {
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = visible;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

CBoard::CBoard(bool boundaryCollision, bool selfCollision)
{
	this->m_snake = std::make_unique<CSnake>();
	this->m_score = 0;
	this->m_trail = 1;
	this->m_over = false;
	this->m_goThroughWall = !boundaryCollision;
	this->m_goThroughItself = !selfCollision;
	this->RandomizeApple();
}

void CBoard::RandomizeApple()
{
	srand(time(0));
	m_applePosition.X = rand() % (WIDTH - 1) + 1;
	m_applePosition.Y = rand() % (HEIGHT - 1) + 1;;
}

void CBoard::PrintBoard()
{
	for (int row = 0; row <= HEIGHT; row++)
	{
		if (row == 0 || row == HEIGHT)
		{
			// top and bottom border
			for (int column = 0; column <= WIDTH + 1; column++)
			{
				std::cout << "#";
			}
		}
		else
		{
			for (int column = 0; column <= WIDTH; column++)
			{

				// side borders
				if (column == 0 || column == WIDTH)
				{
					std::cout << '#';
				}
				// apple position
				if (column == this->m_applePosition.X && row == this->m_applePosition.Y)
				{
					std::cout << '@';
				}
				else
				{
					bool printed = false;
					for (int i = 0; i < m_trail; i++)
					{
						if (column == this->m_snake->GetSnakePosition(i).X && row == this->m_snake->GetSnakePosition(i).Y)
						{
							std::cout << 'O';
							printed = true;
						}
					}
					if (!printed)
					{
						std::cout << ' ';
					}
				}
			}
		}
		std::cout << "\n";
	}
}

void CBoard::CheckColllisionWithApple()
{
	if (this->m_snake->GetSnakePosition(HEAD).X == this->m_applePosition.X && this->m_snake->GetSnakePosition(HEAD).Y == this->m_applePosition.Y)
	{
		this->m_score += 10;
		RandomizeApple();
		m_trail++;
		m_snake->AddTrail();
	}
}

void CBoard::CheckColllisionWithWall(bool goThroughWall)
{
	if (!goThroughWall)
	{
		if (this->m_snake->GetSnakePosition(HEAD).X <= 0 || this->m_snake->GetSnakePosition(HEAD).X >= WIDTH || this->m_snake->GetSnakePosition(HEAD).Y <= 0 || this->m_snake->GetSnakePosition(HEAD).Y >= HEIGHT)
		{
			m_over = true;
		}
	}
	else
	{
		// for X
		if (this->m_snake->GetSnakePosition(HEAD).X <= 0)
		{
			this->m_snake->SetSnakeHeadPositionX(WIDTH - 1);
		}
		else if (this->m_snake->GetSnakePosition(HEAD).X >= WIDTH)
		{
			this->m_snake->SetSnakeHeadPositionX(1);
		}

		// for Y
		if (this->m_snake->GetSnakePosition(HEAD).Y <= 0)
		{
			this->m_snake->SetSnakeHeadPositionY(HEIGHT - 1);
		}
		else if (this->m_snake->GetSnakePosition(HEAD).Y >= HEIGHT)
		{
			this->m_snake->SetSnakeHeadPositionY(1);
		}
	}
}

void CBoard::CheckColllisionWithItself()
{

	for (int index = 1; index < m_trail; index++)
	{
		if (this->m_snake->GetSnakePosition(HEAD).X == this->m_snake->GetSnakePosition(index).X && this->m_snake->GetSnakePosition(HEAD).Y == this->m_snake->GetSnakePosition(index).Y)
		{
			m_over = true;
			break;
		}
	}
}

void CBoard::UpdateBoard()
{
	// hide the cursor
	set_cursor(false);
	while (!m_over)
	{
		PrintBoard();
		if (_kbhit())
		{
			switch (_getch())
			{
				// WASD movement
			case 's':
			case 'S':
				this->m_snake->ChangeDirection(EDirection::DOWN);
				break;
			case 'w':
			case 'W':
				this->m_snake->ChangeDirection(EDirection::UP);
				break;
			case 'd':
			case 'D':
				this->m_snake->ChangeDirection(EDirection::RIGHT);
				break;
			case 'a':
			case 'A':
				this->m_snake->ChangeDirection(EDirection::LEFT);
				break;
			case KEY_ESC:
				m_over = true;
				break;
			}
		}

		this->m_snake->MoveSnake();

		// snake gets an apple
		CheckColllisionWithApple();

		// snake gets a wall or itself
		CheckColllisionWithWall(m_goThroughWall);
		// if cannot go though itself but min length should be 5 to cross
		if (!m_goThroughItself && m_trail >= 5)
		{
			CheckColllisionWithItself();
		}

		printf("\n\n\t----------------------------------------------------------------\n");
		printf("\t-------------------|      SCORE : %4d    |---------------------\n", this->m_score);
		printf("\t----------------------------------------------------------------\n");
		gotoxy(0, 0);
	}
	system("cls");
	printf("----------------------------------------------------------------\n");
	printf("-------------------|      Game OVER      |----------------------\n");
	printf("----------------------------------------------------------------\n\n\n");
	printf("\n\n----------------------------------------------------------------\n");
	printf("-------------------|      SCORE : %4d    |---------------------\n", this->m_score);
	printf("----------------------------------------------------------------\n");
}