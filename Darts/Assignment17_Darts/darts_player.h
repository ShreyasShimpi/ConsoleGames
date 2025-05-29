#pragma once
#include <array>
#include <vector>

class CPlayer
{
private:
	std::array<short, 3> m_playerRoundScores;
	std::vector<short> m_playerTurnScores;
	int m_currentTotal = 501;
	int m_turnTotal = 0;
public:
	CPlayer() = default;
	CPlayer(int);

	void PrintCurrentTotal();
	void PrintTurnTotal();

	void SetTurnTotal();
	void SetCurrentTotal(bool);

	void AddRoundScore(int, short);
	void EmptyScores();
	bool CheckWin(int, bool);
};