#include <iostream>
#include <vector>
#include <array>
#include <Windows.h>

#include "connect4_game.h"

/*
	Constructor: creates the space' ' filled matrix of input rows and columns
*/
CGame::CGame(int rows, int columns)
{
	//vector =  can take values;
	m_rows = rows;
	m_columns = columns;

	for (int i = 0; i < m_rows; i++)
	{
		std::vector<char> temp(m_columns, ' ');
		m_board.push_back(temp);
	}

	/*
		Initialize height
	*/
	m_height.reserve(m_columns);
	for (int i = 0; i < m_columns; i++)
	{
		m_height.push_back(0);
	}
}

/*
	Handles player input
*/
int CGame::PlayerInput()
{
	int choice = 0;
	do
	{
		std::cout << "Select the Column (1 - " << m_columns << ") : ";
		std::cin >> choice;
		std::cout << "\n";

		if (m_height[choice - 1] == m_rows)
		{
			std::cout << "This Column is Filled! Try Another Column!\n";
			choice = 0;
		}

	} while (choice < 1 || choice > 8);

	return choice;
}

/*
	Stacks the player input to particular column
*/
void CGame::StackPlayerInput(int choice)
{
	int index = m_height[choice - 1];
	m_board[index][choice - 1] = m_playerCharacter[m_turn];
	m_height[choice - 1] += 1;
}

/*
	Checks the board is full or not in order to draw the game
*/
bool CGame::IsBoardFull()
{
	int currentFill = 0;
	int maxFill = m_rows * m_columns;
	for (int i = 0; i < m_columns; i++)
	{
		currentFill += m_height[i];
	}
	return (currentFill == maxFill) ? true : false;

}

/*
	Checks the surrounding of the current chip inserted to find the connect 4
*/
int CGame::CheckConnect(int choice)
{
	char currentCharacter = m_playerCharacter[m_turn];
	int currentRowIndex = m_height[choice - 1] - 1;
	int currentColumnIndex = choice - 1;
	/*
		Check Horizontal ( 4 conditions ) => 4 possible scenarios [ 1: O*** ][ 2: *O** ][ 3: **O* ][ 4: ***O ]

	*/
	if ((currentColumnIndex + 3 < m_columns && // Out Of Bound Check
			m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex][currentColumnIndex + 1] &&
			m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex][currentColumnIndex + 2] &&
			m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex][currentColumnIndex + 3])
		||
		((currentColumnIndex + 2 < m_columns && currentColumnIndex - 1 >= 0) && // Out Of Bound Check
			m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex][currentColumnIndex - 1] &&
			m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex][currentColumnIndex + 1] &&
			m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex][currentColumnIndex + 2])
		||
		((currentColumnIndex + 1 < m_columns && currentColumnIndex - 2 >= 0) && // Out Of Bound Check
			m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex][currentColumnIndex - 2] &&
			m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex][currentColumnIndex - 1] &&
			m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex][currentColumnIndex + 1])
		||
		((currentColumnIndex < m_columns && currentColumnIndex - 3 >= 0) && // Out Of Bound Check
			m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex][currentColumnIndex - 3] &&
			m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex][currentColumnIndex - 2] &&
			m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex][currentColumnIndex - 1]))
	{
		return m_turn + 1;
	}
	/*
		height should be at least 4 for checking vertical and diagonal connect
	*/
	if (currentRowIndex >= 3)
	{
		/*
			Check Vertical ( 1 condition) => last element could be added on top so we check only below ones
		*/
		if ((m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex - 1][currentColumnIndex] &&
			 m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex - 2][currentColumnIndex] &&
			 m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex - 3][currentColumnIndex]))
		{
			return m_turn + 1;
		}

		/*
			Check Diagonal ( / ) => 4 possible scenarios => (same anology as horizontal)
		*/

		if (((currentColumnIndex + 3 < m_columns) && // Out Of Bound Check
				m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex - 1][currentColumnIndex + 1] &&
				m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex - 2][currentColumnIndex + 2] &&
				m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex - 3][currentColumnIndex + 3])
			||
			((currentRowIndex + 1 < m_rows && (currentColumnIndex + 2 < m_columns && currentColumnIndex - 1 >= 0)) && // Out Of Bound Check
				m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex + 1][currentColumnIndex - 1] &&
				m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex - 1][currentColumnIndex + 1] &&
				m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex - 2][currentColumnIndex + 2])
			||
			((currentRowIndex + 2 < m_rows && (currentColumnIndex + 1 < m_columns && currentColumnIndex - 2 >= 0)) && // Out Of Bound Check
				m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex + 2][currentColumnIndex - 2] &&
				m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex + 1][currentColumnIndex - 1] &&
				m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex - 1][currentColumnIndex + 1])
			||
			((currentRowIndex + 3 < m_rows && (currentColumnIndex < m_columns && currentColumnIndex - 3 >= 0)) && // Out Of Bound Check
				m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex + 3][currentColumnIndex - 3] &&
				m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex + 2][currentColumnIndex - 2] &&
				m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex + 1][currentColumnIndex - 1]))
		{
			return m_turn + 1;
		}

		/*
			Check Diagonal ( \ ) => 4 possible scenarios => (same anology as horizontal)
		*/
		if (((currentRowIndex + 3 < m_rows && (currentColumnIndex + 3 < m_columns && currentColumnIndex >= 0)) && // Out Of Bound Check
				m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex + 1][currentColumnIndex + 1] &&
				m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex + 2][currentColumnIndex + 2] &&
				m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex + 3][currentColumnIndex + 3])
			||
			((currentRowIndex + 2 < m_rows && (currentColumnIndex + 2 < m_columns && currentColumnIndex - 1 >= 0)) && // Out Of Bound Check
				m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex - 1][currentColumnIndex - 1] &&
				m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex + 1][currentColumnIndex + 1] &&
				m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex + 2][currentColumnIndex + 2])
			||
			((currentRowIndex + 1 < m_rows && (currentColumnIndex + 1 < m_columns && currentColumnIndex - 2 >= 0)) && // Out Of Bound Check
				m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex - 2][currentColumnIndex - 2] &&
				m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex - 1][currentColumnIndex - 1] &&
				m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex + 1][currentColumnIndex + 1])
			||
			((currentRowIndex < m_rows && (currentColumnIndex < m_columns && currentColumnIndex - 3 >= 0)) && // Out Of Bound Check
				m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex - 3][currentColumnIndex - 3] &&
				m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex - 2][currentColumnIndex - 2] &&
				m_board[currentRowIndex][currentColumnIndex] == m_board[currentRowIndex - 1][currentColumnIndex - 1]))
		{
			return m_turn + 1;
		}
	}

	return 0;
}

/*
	Displays the board on the console
*/
void CGame::DisplayBoard()
{
	std::cout << "BOARD : \n\n";
	std::cout << "\t ";
	for (int i = 1; i <= m_columns; i++)
	{
		std::printf(" %-2d ", i);
	}
	std::cout << "\n";
	for (int i = m_rows - 1; i >= 0; i--)
	{
		std::cout << "\t|";
		for (int j = 0; j < m_columns; j++)
		{
			std::cout << "___|";
		}
		std::cout << "\n\t|";
		for (int j = 0; j < m_columns; j++)
		{

			std::cout << "   |";
		}
		std::cout << "\n\t|";
		for (int j = 0; j < m_columns; j++)
		{
			std::cout << " " << m_board[i][j] << " |";
		}
		std::cout << "\n";
	}

	std::cout << "\t|";
	for (int j = 0; j < m_columns; j++)
	{
		std::cout << "___|";
	}

	std::cout << "\n";
	std::cout << "\t||" << std::string(4 * m_columns - 3, ' ') << "||\n";
	std::cout << "\t||" << std::string(4 * m_columns - 3, ' ') << "||\n";
	std::cout << "\t||" << std::string(4 * m_columns - 3, ' ') << "||\n";
	std::cout << "\n\n\n";
}

/*
	Actual game Loop
*/
void CGame::GameLoop()
{
	while (!m_winner)
	{
		system("cls");

		// Display the board
		DisplayBoard();

		std::cout << "\n\n<---------------- Player " << m_turn + 1 << " turn --------------->\n\n";

		// take input from player
		int choice = PlayerInput();

		// Delay - just for fun
		std::cout << "Sliding Down the Chip";
		for (int i = 2; i > 0; i--)
		{
			std::cout << ".";
			Sleep(1000);
		}
		// stack the player input on top of the column
		StackPlayerInput(choice);
		std::cout << "\nDone!\n";

		// check connect for current player, returns winner index
		m_winner = CheckConnect(choice);

		std::cout << "\n\n<------------- Player " << m_turn + 1 << " turn over ------------->\n\n";
		Sleep(1000);
		m_turn = (m_turn + 1) % NUMBEROFPLAYERS;

		// Check for Draw
		if (IsBoardFull())
		{
			std::cout << "The Board is Full! The Game is Draw!\n";
		}
	}
	system("cls");
	// display board to see the sequence
	DisplayBoard();
	std::cout << "\n\n\nPlayer " << m_winner << " has managed to CONNECT 4!! \n";
	std::cout << "\nPlayer " << m_winner << " Wins!\n";
	system("pause");
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
		std::cout << "-------------|        Welcome To Connect 4        |-------------\n";
		std::cout << "----------------------------------------------------------------\n\n\n\n";
		std::cout << "Options : \n";
		std::cout << "\t1: Start Game\n";
		std::cout << "\t2: Rules\n";
		std::cout << "\t3: Exit	\n";

		short choice = 0;
		std::cout << "\nYour Choice : ";
		std::cin >> choice;

		//Menu
		switch (choice)
		{
		case 1:
		{
			system("cls");
			std::cout << "Information : ";
			std::cout << "\n\tPlayer 1 Chip: 'O'\n";
			std::cout << "\n\tPlayer 2 Chip: '@'\n\n";
			std::cout << "Input : ";
			int numberOfRows;
			int numberOfColumns;

			std::cout << "\n\tEnter the Number of Rows : ";
			std::cin >> numberOfRows;

			std::cout << "\n\tEnter the Number of Columns : ";
			std::cin >> numberOfColumns;

			CGame gameObject(numberOfRows, numberOfColumns);

			std::cout << "\n\nInitializing the Board";
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
			system("cls");
			std::cout << "Rules : \n";
			std::cout << "\t1: Its a simple but tricky game played between 2 people.\n";
			std::cout << "\t2: You and opponent have chips of different colors.\n";
			std::cout << "\t3: There is a table where you drop your chips for top and they will stack.\n";
			std::cout << "\t4: Objective of the game is to connect 4 of your chips horizontally/ vertically/ diagonally.\n";
			std::cout << "\t5: The player who does this first, wins.\n\n\n\n";
			system("pause");
			break;
		}
		case 3:
		{
			system("cls");
			std::cout << "Thanks For Playing!\n";
			exit = true;
			system("pause");
			break;
		}
		default:
			std::cout << "Invalid Input! Try Again!\n";
			break;
		}
	}
}