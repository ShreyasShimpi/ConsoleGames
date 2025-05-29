// external includes

// internal includes
#include "CBoard.h"
#include "CKing.h"

// for king movement
const short g_sizeKingMove = 8;
const short g_rowKingMove[] = { -1, -1, -1, -0, 1, 1, 1, 0 };
const short g_colkingMove[] = { -1, 0, 1, 1, 1, 0, -1, -1 };

CKing::CKing(const EColor& color, const SPosition& position, const sf::Sprite& pieceSprite)
	: CPiece(color, position, pieceSprite)
{
}

bool CKing::IsMoveValid(const SPosition& toPosition)
{
	if (CBoard::GetPieceColor(toPosition) != m_color &&
		(m_currentPosition.m_row + 1 >= toPosition.m_row &&
		m_currentPosition.m_row - 1 <= toPosition.m_row) &&
		(m_currentPosition.m_column + 1 >= toPosition.m_column &&
		m_currentPosition.m_column - 1 <= toPosition.m_column))
	{
			return true;
	}
	else
	{
		return false;
	}
}

void CKing::CalculatePossibleMoves()
{
	SPosition possiblePosition = { m_currentPosition.m_row, m_currentPosition.m_column };
	for (int i = 0; i < g_sizeKingMove; i++)
	{
		possiblePosition = { m_currentPosition.m_row + g_rowKingMove[i], m_currentPosition.m_column + g_colkingMove[i] };
		if (CBoard::GetPieceColor(possiblePosition) != m_color &&
			CBoard::BoundaryCheck(possiblePosition))
		{
			m_possibleMoves.emplace_back(std::move(possiblePosition));
		}
	}
}

CKing::~CKing()
{
}
