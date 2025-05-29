#include "snakes_snake.h"

CSnake::CSnake()
{
	this->m_direction = EDirection::STOP;
	this->m_snake.push_back({ WIDTH / 2 , HEIGHT / 2 });
	this->m_velocity = 1;

}

void CSnake::ChangeDirection(EDirection dir)
{
	this->m_direction = dir;
}

void CSnake::UpdateTrail(COORD headPosition)
{
	COORD temp = headPosition;
	for (size_t i = 1; i < m_snake.size(); i++)
	{
		COORD temp2 = m_snake[i];
		m_snake[i] = temp;
		temp = temp2;
	}
}

void CSnake::AddTrail()
{
	// push another trail to snake 
	//this->m_snake.push_back(this->m_snake.back());
	this->m_snake.push_back({ 0, 0 });
}

void CSnake::MoveSnake()
{
	COORD headPosition = this->m_snake[HEAD];
	// move head according to input
	switch (this->m_direction)
	{
	case EDirection::UP:
		this->m_snake[HEAD].Y -= m_velocity;
		break;
	case EDirection::DOWN:
		this->m_snake[HEAD].Y += m_velocity;
		break;
	case EDirection::LEFT:
		this->m_snake[HEAD].X -= m_velocity;
		break;
	case EDirection::RIGHT:
		this->m_snake[HEAD].X += m_velocity;
		break;
	}
	UpdateTrail(headPosition);
}

COORD CSnake::GetSnakePosition(int index)
{
	return m_snake[index];
}

void CSnake::SetSnakeHeadPositionX(int headpositionX)
{
	this->m_snake[HEAD].X = headpositionX;
}

void CSnake::SetSnakeHeadPositionY(int headpositionY)
{
	this->m_snake[HEAD].Y = headpositionY;
}
