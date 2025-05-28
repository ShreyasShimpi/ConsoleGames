#pragma once
#include <array>
#include <vector>

#define NUMBEROFPLAYERS 2

class CGame
{
private:
	int m_rows;
	int m_columns;

	// actual board
	std::vector<std::vector<char>> m_board;

	// height to maintain the stack
	std::vector<int> m_height;

	std::array<char, NUMBEROFPLAYERS> m_playerCharacter{ 'O', '@' };
	int m_winner = 0;
	int m_turn = 0;

public:

	CGame(int, int);
	void GameLoop();
	int PlayerInput();
	void StackPlayerInput(int);
	bool IsBoardFull();
	int CheckConnect(int);
	void DisplayBoard();
};

void GameMenu();