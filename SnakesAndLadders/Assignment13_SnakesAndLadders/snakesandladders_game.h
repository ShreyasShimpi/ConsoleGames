#pragma once

#include <unordered_map>



class CGame
{
private:
	int* m_playerPositions;
	/*
		Map implementation
	*/
	//std::unordered_map<int, int> snakes;
	//std::unordered_map<int, int> ladders;


	/*
		Array Implementation
	*/
	int* m_snakeHeads;
	int* m_snakeTails;
	int* m_ladderStart;
	int* m_ladderEnd;
	int m_turn = 0;

	int m_numberOfSnakes;
	int m_numberOfLadders;
	int m_numberOfPlayers;

	bool m_close = false;

public:

	

	CGame() = delete;

	/*
		Paramentrized Constructor
	*/
	CGame(int players, int snakes = 9, int ladders = 9);

	/*
		Destructor
	*/
	~CGame()
	{
	}

	int RollTheDice();

	/*
		Checks for snakes in the board : uses Linear search
	*/
	void CheckForSnake();

	/*
		Checks for ladders in the board : uses Linear search
	*/
	void CheckForLadder();

	/*
		Checks the winner
	*/
	bool CheckWinner();

	/*
		Game loop
	*/

	void GameLoop();

};

void GameMenu();