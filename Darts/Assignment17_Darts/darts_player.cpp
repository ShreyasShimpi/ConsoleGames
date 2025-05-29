#include <iostream>

#include "darts_player.h"

/*
	Set Current Total according to game mode 301/ 501
*/
CPlayer::CPlayer(int gameMode)
{
	this->m_playerRoundScores.fill(0);
	this->m_currentTotal = gameMode;
	this->m_turnTotal = 0;
}

// prints current total of player
void CPlayer::PrintCurrentTotal()
{
	std::cout << "\n\tYour Current Total is " << this->m_currentTotal << ".\n";
}

// prints turn total of player
void CPlayer::PrintTurnTotal()
{
	std::cout << "\n\tYour Recent Turn Total is " << this->m_turnTotal << ".\n";
}

// this is to empty the array of rounds values after one turn
void CPlayer::EmptyScores()
{
	this->m_playerRoundScores.fill(0);
}

// add the round score to the array 
void CPlayer::AddRoundScore(int index, short score)
{
	this->m_playerRoundScores[index] = score;
}

// sets the turn total
void CPlayer::SetTurnTotal()
{
	short total = 0;
	for (int i = 0; i < this->m_playerRoundScores.size(); i++)
	{
		total += this->m_playerRoundScores[i];
	}
	this->m_turnTotal = total;
	this->m_playerTurnScores.push_back(m_turnTotal);
}

/*
	conditions according to the game rules:
*/
void CPlayer::SetCurrentTotal(bool isCurrentDouble)
{
	if (m_currentTotal - m_turnTotal < 0)
	{
		std::cout << "Total should land on Exact 0.\n";
	}
	else
	{
		if (m_currentTotal - m_turnTotal == 0 && isCurrentDouble)
		{
			std::cout << "You should End with the Double.\n";
		}
		else
		{
			m_currentTotal -= m_turnTotal;
		}
	}
}

// check if player won or not
bool CPlayer::CheckWin(int round, bool isCurrentDouble)
{
	int tempRoundTotal = 0;
	for (int i = 0; i <= round; i++)
	{
		tempRoundTotal += m_playerRoundScores[i];
		if (m_currentTotal - tempRoundTotal == 0 && isCurrentDouble)
		{
			return true;
		}
	}
	return false;
}