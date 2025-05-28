#include <iostream>
#include <time.h>
#include <unordered_map>
#include <Windows.h>
#include "snakesandladders_game.h"


CGame::CGame(int players, int snakes, int ladders)
{
	/*
		syntax for initialization with 0 for stat of the game
	*/
	this->m_playerPositions = new int[players]();

	/*
		intializing the arrays on heap with some values
	*/
	m_snakeHeads = new int[snakes] {17, 35, 54, 62, 64, 87, 92, 95, 98};
	m_snakeTails = new int[snakes] {7, 13, 34, 19, 60, 36, 73, 75, 26};

	m_ladderStart = new int[ladders] {2, 4, 9, 21, 28, 45, 51, 72, 80};
	m_ladderEnd = new int[ladders] {38, 26, 31, 42, 84, 63, 67, 97, 99};

	this->m_numberOfSnakes = snakes;
	this->m_numberOfLadders = ladders;
	this->m_numberOfPlayers = players;

	/*
		fixed position of snakes and ladders
	*/
	//this->snakes = { {17, 7}, {35, 13}, {54, 34}, {62, 19}, {87, 60},{87, 36} ,{93, 73}, {95, 75}, {98, 26} };
	//this->ladders = { {2, 38}, {4, 26}, {9, 31}, {21, 42}, {28, 84},{45, 63} ,{51, 67}, {72, 97}, {80, 99} };
}

/*
	Rolls the dice, retrurns the value from 1 to 6
*/
int CGame::RollTheDice()
{
	srand(time(0));
	std::cout << "<-- Press Enter To Roll The Dice -->\n";
	std::cin.ignore();

	int diceValue = rand() % 6 + 1;

	std::cout << "Rolling";
	for (int i = 3; i > 0; i--)
	{
		std::cout << ".";
		Sleep(1000);
	}

	std::cout << "\nYou got " << diceValue << "!\n";
	return diceValue;
}

/*
	Checks for snakes in the board : uses Linear search
*/
void CGame::CheckForSnake()
{

	for (int i = 0; i < m_numberOfSnakes; i++)
	{
		/*
			Map Implementation
		*/
		//auto isSnakeFound = snakes.find(m_playerPositions[m_turn]);
		//if (isSnakeFound != snakes.end())
		//{
		//	std::cout << "But Sadly, You have been caught by a snake!\n";

		//	m_playerPositions[m_turn] = isSnakeFound->second;

		//	std::cout << "Sliding Down";
		//	for (int i = 3; i > 0; i--)
		//	{
		//		std::cout << ".";
		//		Sleep(1000);
		//	}
		//	std::cout << "\nDone! Your Position now is " << m_playerPositions[m_turn] << "\n";
		//}

		/*
			Array Implementation
		*/
		if (m_playerPositions[m_turn] == m_snakeHeads[i])
		{
			std::cout << "But Sadly, You have been caught by a snake!\n";

			m_playerPositions[m_turn] = m_snakeTails[i];

			std::cout << "Sliding Down";
			for (int i = 3; i > 0; i--)
			{
				std::cout << ".";
				Sleep(1000);
			}
			std::cout << "\nDone! Your Position now is " << m_playerPositions[m_turn] << "\n";

			return;
		}
	}
}


/*
	Checks for ladders in the board : uses Linear search
*/
void CGame::CheckForLadder()
{

	for (int i = 0; i < m_numberOfLadders; i++)
	{
		/*
			Map Implementation
		*/
		//auto isLadderFound = ladders.find(m_playerPositions[m_turn]);
		//if (isLadderFound != ladders.end())
		//{
		//	std::cout << "Oh Wait! You just found a Ladder!\n";

		//	m_playerPositions[m_turn] = isLadderFound->second;

		//	std::cout << "Climbing up";
		//	for (int i = 3; i > 0; i--)
		//	{
		//		std::cout << ".";
		//		Sleep(1000);
		//	}
		//	std::cout << "\nDone! Your Position now is " << m_playerPositions[m_turn] << "\n";
		//}

		/*
			Array Implementation
		*/
		if (m_playerPositions[m_turn] == m_ladderStart[i])
		{
			std::cout << "Oh Wait! You just found a Ladder!\n";

			m_playerPositions[m_turn] = m_ladderEnd[i];

			std::cout << "Climbing up";
			for (int i = 3; i > 0; i--)
			{
				std::cout << ".";
				Sleep(1000);
			}
			std::cout << "\nDone! Your Position now is " << m_playerPositions[m_turn] << "\n";

			return;
		}
	}
}

/*
	Checks the winner
*/
bool CGame::CheckWinner()
{
	if (m_playerPositions[m_turn] == 100)
	{
		std::cout << "Player " << m_turn + 1 << " is the Winner!\n\n\n";
		return true;
	}
	return false;
}

/*
	Game loop
*/

void CGame::GameLoop()
{

	while (!m_close)
	{
		system("cls");
		/*
			Snakes and Ladders Arrays printed
		*/
		std::cout << "Snakes on the Board : \n\n";
		for (int i = 0; i < m_numberOfSnakes; i++)
		{
			std::cout << "(" << m_snakeTails[i] << ") ~<{}|{}|{}|{}|{}|{}|{}|{}|{}(O_O) (" << m_snakeHeads[i] << ")\n";
		}

		std::cout << "\n\nLadders on the Board : \n\n";
		for (int i = 0; i < m_numberOfLadders; i++)
		{
			std::cout << "[" << m_ladderStart[i] << "] ]]]]]]]]]]]]]]]]]]]]]]]]]]]]] [" << m_ladderEnd[i] << "]\n";
		}

		/*
			Snakes and Ladders Map Printed
		*/
		//for (auto& snake : snakes)
		//{
		//	std::cout << "(" << snake.first << ") ~<{}|{}|{}|{}|{}|{}|{}|{}|{}(OO) (" << snake.second << ")\n";
		//}

		//for (auto& ladder : ladders)
		//{
		//	std::cout << "[" << ladder.first << "] |]]]]]]]]]]]]]]]]]]]]]]]]]]]| [" << ladder.second << "]\n";
		//}


		std::cout << "\n\n<---------------- Player " << m_turn + 1 << " Turn ---------------->\n\n\n";

		int diceValue = RollTheDice();

		/*
				overflow edge case: if the total is going beyond 100, skip the m_turn;
		*/
		if (m_playerPositions[m_turn] + diceValue > 100)
		{
			std::cout << "Oops! The Dice Value is little higher! Keep Trying!\n";
		}

		else
		{
			m_playerPositions[m_turn] += diceValue;

			std::cout << "Moving your Piece";
			for (int i = 3; i > 0; i--)
			{
				std::cout << ".";
				Sleep(1000);
			}
			std::cout << "\nDone! Your Position now is " << m_playerPositions[m_turn] << "\n";
		}

		/*
			check for snakes and ladders
		*/
		CheckForSnake();
		CheckForLadder();

		m_close = CheckWinner();
		std::cout << "<-------------------------------------------------->\n";
		m_turn = (m_turn + 1) % m_numberOfPlayers;
	}

}


/*
	Game Menu
*/

void GameMenu()
{

	bool exit = false;
	while (!exit)
	{
		system("cls");
		std::cout << "----------------------------------------------------------------\n";
		std::cout << "---------|        Welcome To Snakes and Ladders        |--------\n";
		std::cout << "----------------------------------------------------------------\n\n\n\n";

		std::cout << "Rules : \n";
		std::cout << "\t1: Its a simplet dice game played on 10X10 board.\n";
		std::cout << "\t2:Each player will roll the dice and move forward by that number.\n";
		std::cout << "\t3: If you find a ladder, you climb up to the top of the ladder.\n";
		std::cout << "\t4: If you find a snake, you slide down to its tail.\n";
		std::cout << "\t5: There are 9 snakes and 9 ladders in the game.\n";
		std::cout << "\t6: The player who reach to the end, wins.\n\n\n";

		std::cout << "Options : \n";
		std::cout << "\t1: Start Game\n";
		std::cout << "\t2: Exit	\n";

		short choice = 0;
		std::cout << "Your Choice : ";
		std::cin >> choice;

		switch (choice)
		{
		case 1:
		{
			system("cls");
			int numberOfPLayers;
			std::cout << "Enter the Number of Players : ";
			std::cin >> numberOfPLayers;

			CGame gameObject(numberOfPLayers);

			std::cout << "Setting up the Board";
			for (int i = 3; i > 0; i--)
			{
				std::cout << ".";
				Sleep(1000);
			}

			gameObject.GameLoop();

			break;
		}
		case 2:
		{
			std::cout << "Thanks For Playing!\n";
			system("pause");
			exit = true;
			break;
		}
		default:
			std::cout << "Invalid Input! Try Again!\n";
			break;
		}
	}
}