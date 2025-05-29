// external includes

// internal includes
#include "CBoard.h"
#include "CBishop.h"

CBishop::CBishop(const EColor& color, const SPosition& position, const sf::Sprite& pieceSprite)
	: CPiece(color, position, pieceSprite)
{
}

bool CBishop::IsMoveValid(const SPosition& toPosition)
{
	// here we check spaces between current position and target position
	if (abs(int(m_currentPosition.m_row - toPosition.m_row)) == abs(int(m_currentPosition.m_column - toPosition.m_column)))
	{
		short signCol = (toPosition.m_column < m_currentPosition.m_column) ? -1 : 1;
		short signRow = (toPosition.m_row < m_currentPosition.m_row) ? -1 : 1;
		short i = signCol;
		short j = signRow;
		while (i != (toPosition.m_column - m_currentPosition.m_column) && j != (toPosition.m_row - m_currentPosition.m_row))
		{
			if (CBoard::ms_board[m_currentPosition.m_row + j][m_currentPosition.m_column + i][0] != ' ')
			{
				return false;
			}
			i += signCol;
			j += signRow;
		}
		return true;
	}
	else
	{
		return false;
	}
}


void CBishop::CalculatePossibleMoves()
{
	// down right
	SPosition possiblePosition = { m_currentPosition.m_row, m_currentPosition.m_column };
	while (CBoard::BoundaryCheck(possiblePosition) && CBoard::GetPieceColor(possiblePosition) == EColor::None)
	{
		m_possibleMoves.emplace_back(possiblePosition);
		possiblePosition.m_row++;
		possiblePosition.m_column++;
	}

	// up right 
	possiblePosition = { m_currentPosition.m_row, m_currentPosition.m_column };
	while (CBoard::BoundaryCheck(possiblePosition) && CBoard::GetPieceColor(possiblePosition) == EColor::None)
	{
		m_possibleMoves.emplace_back(possiblePosition);
		possiblePosition.m_row--;
		possiblePosition.m_column++;
	}
	possiblePosition = { m_currentPosition.m_row, m_currentPosition.m_column };

	// down left
	possiblePosition = { m_currentPosition.m_row, m_currentPosition.m_column };
	while (CBoard::BoundaryCheck(possiblePosition) && CBoard::GetPieceColor(possiblePosition) == EColor::None)
	{
		m_possibleMoves.emplace_back(possiblePosition);
		possiblePosition.m_row++;
		possiblePosition.m_column--;
	}
	possiblePosition = { m_currentPosition.m_row, m_currentPosition.m_column };

	// up left
	possiblePosition = { m_currentPosition.m_row, m_currentPosition.m_column };
	while (CBoard::BoundaryCheck(possiblePosition) && CBoard::GetPieceColor(possiblePosition) == EColor::None)
	{
		m_possibleMoves.emplace_back(possiblePosition);
		possiblePosition.m_row--;
		possiblePosition.m_column--;
	}
}


CBishop::~CBishop()
{
}
