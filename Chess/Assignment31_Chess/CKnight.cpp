// external includes

// internal includes
#include "CBoard.h"
#include "CKnight.h"

// for knight movement
const short g_sizeKnightMove = 8;
const short g_rowKnightMove[] = { 2, 2, -2, -2, 1, 1, -1, -1 };
const short g_colknightMove[] = { -1, 1, 1, -1, 2, -2, 2, -2 };

CKnight::CKnight(const EColor& color, const SPosition& position, const sf::Sprite& pieceSprite)
	: CPiece(color, position, pieceSprite)
{
}

bool CKnight::IsMoveValid(const SPosition& toPosition)
{
	for (int i = 0; i < g_sizeKnightMove; i++)
	{
		if ((m_currentPosition.m_row + g_rowKnightMove[i] == toPosition.m_row &&
			m_currentPosition.m_column +  g_colknightMove [i] == toPosition.m_column) &&
			CBoard::GetPieceColor(toPosition) != m_color)
		{
			return true;
		}
	}
	return false;
}

void CKnight::CalculatePossibleMoves()
{
	SPosition possiblePosition = { m_currentPosition.m_row, m_currentPosition.m_column };
	for (int i = 0; i < g_sizeKnightMove; i++)
	{
		possiblePosition = { m_currentPosition.m_row + g_rowKnightMove[i], m_currentPosition.m_column + g_colknightMove[i] };
		if (CBoard::GetPieceColor(possiblePosition) != m_color &&
			CBoard::BoundaryCheck(possiblePosition))
		{
			m_possibleMoves.emplace_back(std::move(possiblePosition));
		}
	}
}

CKnight::~CKnight()
{
}
