#include <iostream>
#include <Windows.h>
#include <ctime>

#include "bowling_game.h"

CGame::CGame(int numberOfPlayers, bool autoBowl)
	: m_numberOfPlayers(numberOfPlayers), m_autoBowl(autoBowl)
{
	m_angle = 0;
	m_angleForAuto = 70;
	this->m_player = new CPlayer[m_numberOfPlayers];
	this->m_bowlingArena = new CBowlingArena();
	for (int i = 0; i < m_numberOfPlayers; i++)
	{
		this->m_player[i] = CPlayer();
	}
}

int CGame::RollTheBall(int pinsOnArena)
{
	srand(time(0));

	if (m_autoBowl)
	{
		std::cout << "\t<-- Press Any key to Roll the Ball -->";
		system("pause>nul");

		// adding 70 for increasing probability : so m_angle will be 70 to 110
		m_angle = rand() % (MAXANGLE - 2 * m_angleForAuto + 1) + m_angleForAuto;
		m_bowlingArena->AnimateArena(m_angle, pinsOnArena);
		m_bowlingArena->PrintArena(m_bowlingArena->initialBallPositionX, m_bowlingArena->initialBallPositionY, pinsOnArena);
		return m_bowlingArena->GetScoreByAngle(pinsOnArena, m_angle);
	}
	else
	{
		do
		{
			std::cout << "Select The Angle of Rolling (0 - 180) : ";
			std::cin >> m_angle;
		} while (!(m_angle >= 0 && m_angle <= 180));

		m_bowlingArena->AnimateArena(m_angle, pinsOnArena);
		m_bowlingArena->PrintArena(m_bowlingArena->initialBallPositionX, m_bowlingArena->initialBallPositionY, pinsOnArena);
		return m_bowlingArena->GetScoreByAngle(pinsOnArena, m_angle);
	}
}

void CGame::NormalFrame(int turn)
{
	std::cout << "First Roll : \n";
	// first roll
	int pinsDroppedFirst = RollTheBall(PINS);
	m_player[turn].AddRollScore(pinsDroppedFirst);
	

	// strike on first roll
	if (pinsDroppedFirst == 10)
	{
		std::cout << "\tIts a Strike! You got all of 'em in Roll! Excellent!\n\n";
		// roll over for current player
		return;
	}
	else
	{
		// second roll
		std::cout << "Second Roll : \n";
		int pinsDroppedSecond = RollTheBall(PINS - pinsDroppedFirst);
		m_player[turn].AddRollScore(pinsDroppedSecond);

		if (pinsDroppedSecond == PINS)
		{
			std::cout << "\tIts a Strike! You got all of 'em in Second Roll! Excellent!\n\n";
		}
		// spare on second roll
		else if (pinsDroppedFirst + pinsDroppedSecond == PINS)
		{
			std::cout << "\tIts a Spare! You got all of 'em! Well Done!\n\n";
		}
		else
		{
			std::cout << "\tIts an Open Frane! Your Turn Ends here!\n\n";
		}
	}
}



void CGame::TenthFrame(int turn)
{
	std::cout << "First Roll : \n";
	// first roll = full pins
	int pinsDroppedFirst = RollTheBall(PINS);
	m_player[turn].AddRollScore(pinsDroppedFirst);

	// if strike on first roll
	if (pinsDroppedFirst == 10)
	{
		std::cout << "\tIts a Strike! You get another 2 rolls!\n\n";

		// second roll = full pins
		std::cout << "Second Roll : \n";
		int pinsDroppedSecond = RollTheBall(PINS);
		m_player[turn].AddRollScore(pinsDroppedSecond);

		// if strike on second roll
		if (pinsDroppedSecond == 10)
		{
			std::cout << "\tIts a Strike Again! You are on a streak!\n\n";
			// third roll = full pins
			std::cout << "Third Roll : \n";
			int pinsDroppedThird = RollTheBall(PINS);
			m_player[turn].AddRollScore(pinsDroppedThird);
		}
		else
		{
			// third roll =  remaining pins
			std::cout << "Third Roll : \n";
			int pinsDroppedThird = RollTheBall(PINS - pinsDroppedSecond);
			m_player[turn].AddRollScore(pinsDroppedThird);
		}
		if (pinsDroppedSecond == 10)
		{
			std::cout << "\tA Third Strike! You owned it!\n\n";
		}
	}
	else
	{
		// second roll = remaining pins
		std::cout << "Second Roll : \n";
		int pinsDroppedSecond = RollTheBall(PINS - pinsDroppedFirst);
		m_player[turn].AddRollScore(pinsDroppedSecond);

		// spare on second roll
		if (pinsDroppedFirst + pinsDroppedSecond == PINS)
		{
			std::cout << "\tIts a Spare! You get another roll!\n\n";
			// third roll = full pins
			std::cout << "Third Roll : \n";
			int pinsDroppedThird = RollTheBall(PINS);
			m_player[turn].AddRollScore(pinsDroppedThird);

			if (pinsDroppedSecond == 10)
			{
				std::cout << "\tA Final Strike! Nice!\n\n";
			}
		}
		else
		{
			std::cout << "\tIts an Open Frane! Your Turn Ends here! Good Game!\n\n";
			return;
		}
	}
}

void CGame::CalculateScores()
{
	for (int turn = 0; turn < m_numberOfPlayers; turn++)
	{
		m_player[turn].AggregateScore();
	}
}
void CGame::DisplayScores()
{
	std::cout << "Final Scores : \n";
	for (int turn = 0; turn < m_numberOfPlayers; turn++)
	{
		Sleep(1000);
		std::cout << "\tPlayer " << turn + 1 << " : ";
		m_player[turn].DisplayScore();
		std::cout << "\n";
	}
}

void CGame::DisplayWinner()
{
	int maxPlayerIndex = 0;
	for (int turn = 0; turn < m_numberOfPlayers; turn++)
	{
		if (m_player[maxPlayerIndex].GetScore() < m_player[turn].GetScore())
		{
			maxPlayerIndex = turn;
		}
	}
	std::cout << "The Winner of the Game : Player " << maxPlayerIndex + 1 << "\n\n";
}

void CGame::Game()
{
	
	for (int frame = 1; frame <= FRAMES; frame++)
	{
		for (int turn = 0; turn < m_numberOfPlayers; turn++)
		{
			system("cls");
			m_bowlingArena->PrintArena(m_bowlingArena->initialBallPositionX, m_bowlingArena->initialBallPositionY, PINS);
			printf("-----------------------------------------\n");
			printf("--------------- Frame %2d ----------------\n", frame);
			printf("-----------------------------------------\n");
			std::cout << "\n\n<--------- Player " << turn + 1 << " Turn --------->\n\n";

			if (frame != 10)
			{
				NormalFrame(turn);
			}
			else
			{
				TenthFrame(turn);
			}
			DelayMessage(3);
		}

		printf("-----------------------------------------\n");
		printf("------------ Frame %2d Over --------------\n", frame);
		printf("-----------------------------------------\n");
		DelayMessage(3);
	}
	CalculateScores();
	DisplayScores();
	DisplayWinner();
}

CGame::~CGame()
{
	delete[] m_player;
	delete m_bowlingArena;
}