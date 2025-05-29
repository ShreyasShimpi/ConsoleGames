#include <iostream>
#include <array>
#include <ctime>

#include "darts_game.h"
#include "darts_board.h"

CGame::CGame(int numberOfPLayers, int gameMode, bool isRandom)
	:m_numberOfPlayers(numberOfPLayers), m_isRandom(isRandom)
{
	this->m_turn = 0;
	this->m_rounds = 3;
	this->m_player = new CPlayer[numberOfPLayers];
	for (int i = 0; i < numberOfPLayers; i++)
	{
		this->m_player[i] = CPlayer(gameMode);
	}
}

int CGame::GetWindFactor()
{
	srand(time(0));
	// priority is given to zero
	std::array<int, 12> windOptions = { -1,-2,-3,0,0,0,0,0,0,1,2,3 };
	int index = rand() % 10;
	return windOptions[index];
}

void CGame::Game()
{
	int radius = 40;
	while (!this->m_close)
	{
		system("cls");
		PrintDartBoard(radius);
		std::cout << "<----------------------- Player " << m_turn + 1 << " Turn ------------------------------>";
		NewLine();
		NewLine();

		bool isCurrentDouble = false;

		int windFactor = this->GetWindFactor();
		std::cout << "\tThe Wind Factor is " << windFactor << ".";
		NewLine();
		NewLine();

		for (int round = 0; round < this->m_rounds; round++)
		{
			std::cout << "<-------------------------- Round " << round + 1 << " --------------------------------->";
			NewLine();
			NewLine();

			SDartPosition dart = GetDartPosition(radius, this->m_isRandom, windFactor);
			int roundScore = GetScore(dart, radius);
			m_player[m_turn].AddRoundScore(round, roundScore);

			std::cout << "\tDart Position > Radius : " << dart.radiusOfDart << ".";
			NewLine();
			std::cout << "\tDart Position > Angle  : " << dart.thetaOfDart << ".";
			NewLine();
			NewLine();


			std::cout << "<----------------------- Round " << round + 1 << " Over ------------------------------->";
			NewLine();
			NewLine();

			ThrowDart(dart, radius);

			isCurrentDouble = IsDouble(dart, radius);
			if (m_player[m_turn].CheckWin(round, isCurrentDouble))
			{
				this->m_close = true;
				break;
			}
		}

		m_player[m_turn].SetTurnTotal();
		m_player[m_turn].SetCurrentTotal(isCurrentDouble);

		m_player[m_turn].PrintTurnTotal();
		m_player[m_turn].PrintCurrentTotal();

		m_player[m_turn].EmptyScores();
		std::cout << "\n<---------------------- Player " << m_turn + 1 << " Turn Over -------------------------->\n\n";
		system("pause");
		m_turn = (m_turn + 1) % m_numberOfPlayers;
	}
}

CGame::~CGame()
{
	delete[] m_player;
}