#pragma once
#include "darts_player.h"

class CGame
{
private:
	int m_turn;
	int m_rounds;
	bool m_close;
	int m_numberOfPlayers;
	CPlayer* m_player;
	bool m_isRandom;
public:
	CGame(int, int, bool);
	int GetWindFactor();
	void Game();
	~CGame();
};
