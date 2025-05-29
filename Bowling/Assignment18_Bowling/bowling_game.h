#pragma once
#include "bowling_player.h"
#include "bowling_arena.h"


class CGame
{
private:
	CPlayer* m_player;
	CBowlingArena* m_bowlingArena;
	int m_numberOfPlayers;
	bool m_autoBowl;
	int m_angle;

	int m_angleForAuto;

public:
	CGame(int , bool);
	int RollTheBall(int);
	void NormalFrame(int);
	void TenthFrame(int);

	void Game();

	void CalculateScores();
	void DisplayScores();
	void DisplayWinner();
	~CGame();
};
