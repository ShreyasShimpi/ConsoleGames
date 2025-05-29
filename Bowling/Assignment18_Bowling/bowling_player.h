#pragma once
#include <array>
#include <vector>

#define PINS 10
#define FRAMES 10

enum class EScore
{
	ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, STRIKE, SPARE
};

class CPlayer
{
private:
	int m_totalScore;
	std::vector<int> m_rollScore;
public:
	CPlayer();
	void AggregateScore();
	void DisplayScore();
	int GetScore();
	void AddRollScore(int);
};