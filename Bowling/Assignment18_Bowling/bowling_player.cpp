#include <iostream>

#include "bowling_player.h"


CPlayer::CPlayer() 
{
	m_totalScore = 0;
}

void CPlayer::AggregateScore()
{
	int frameScore;
	int frameNumnber = 1;
	int roll = 0;
	for (; roll < m_rollScore.size() && frameNumnber != FRAMES; frameNumnber++, roll++)
	{
		frameScore = 0;

		// strike of first roll
		if (m_rollScore[roll] == PINS)
		{
			// add score of next two rolls
			frameScore = 10 + m_rollScore[roll + 1] + m_rollScore[roll + 2];
		}
		// strike in second roll
		else if (m_rollScore[roll + 1] == PINS && m_rollScore[roll] == 0)
		{
			// start counting from next roll
			roll += 1;
			frameScore = 10 + m_rollScore[roll + 1] + m_rollScore[roll + 2];
		}
		// spare
		else if (m_rollScore[roll + 1] + m_rollScore[roll] == PINS)
		{
			// start counting from next roll
			roll += 1;
			frameScore = 10 + m_rollScore[roll + 1];
		}
		else
		{
			frameScore = m_rollScore[roll];
			// move to next roll
			roll += 1;
			frameScore += m_rollScore[roll];
		}
		
		m_totalScore += frameScore;
	}

	// score for 10th frame
	for (; roll < m_rollScore.size(); roll++)
	{
		m_totalScore += m_rollScore[roll];
	}
}

void CPlayer::DisplayScore()
{
	std::cout << m_totalScore;
}

int CPlayer::GetScore()
{
	return m_totalScore;
}

void CPlayer::AddRollScore(int pinsDropped)
{
	m_rollScore.push_back(pinsDropped);
	std::cout << "\tYou Got " << pinsDropped << " pins!                                                     \n\n";
}