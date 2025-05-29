#pragma once

// external includes
#include <array>

// internal includes
#include "Defines.h"

// all members are static 
class CBoard
{
private:
	

public:
	// constructor
	CBoard() = delete;

	// public variables
	static std::array<std::array<char[3], SIZE>, SIZE> ms_board;

	// for singleton
	CBoard(const CBoard&) = delete;
	void operator = (const CBoard&) = delete;

	// functions
	static bool BoundaryCheck(const SPosition& position);
	static void Move(const SPosition& fromPosition, const SPosition& toPosition);
	static SPosition DecodeMove(const char* move);
	static const EColor GetPieceColor(const SPosition& position);
	static void DrawBoard();
};

