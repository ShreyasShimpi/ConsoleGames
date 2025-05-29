// external includes

// internal includes
#include "CRook.h"
#include "CBoard.h"

CRook::CRook(const EColor& color, const SPosition& position, const sf::Sprite& pieceSprite)
	: CPiece(color, position, pieceSprite)
{
}

// for rook, the piece can only move in horizontal and vertical direction
bool CRook::IsMoveValid(const SPosition& toPosition)
{
	// here we check spaces between current position and target position
	if (m_currentPosition.m_row == toPosition.m_row && m_currentPosition.m_column != toPosition.m_column)
	{
		short sign = ((toPosition.m_column - m_currentPosition.m_column) < 0) ? -1 : 1;
		short i = sign;
		while (i != (toPosition.m_column - m_currentPosition.m_column))
		{
			if (CBoard::ms_board[m_currentPosition.m_row][m_currentPosition.m_column + i][0] != ' ')
			{
				return false;
			}
			i += sign;
		}
		return true;
	}
	else if (m_currentPosition.m_row != toPosition.m_row && m_currentPosition.m_column == toPosition.m_column)
	{
		short sign = (toPosition.m_row < m_currentPosition.m_row) ? -1 : 1;
		short i = sign;
		while (i != (toPosition.m_row - m_currentPosition.m_row))
		{
			if (CBoard::ms_board[m_currentPosition.m_row + i][m_currentPosition.m_column][0] != ' ')
			{
				return false;
			}
			i += sign;
		} 
		return true;
	}
	else
	{
		return false;
	}
}

void CRook::CalculatePossibleMoves()
{
	// down
	SPosition possiblePosition = { m_currentPosition.m_row, m_currentPosition.m_column };
	while (CBoard::BoundaryCheck(possiblePosition) && CBoard::GetPieceColor(possiblePosition) == EColor::None)
	{
		m_possibleMoves.emplace_back(possiblePosition);
		possiblePosition.m_row++;
	}

	// up
	possiblePosition = { m_currentPosition.m_row, m_currentPosition.m_column };
	while (CBoard::BoundaryCheck(possiblePosition) && CBoard::GetPieceColor(possiblePosition) == EColor::None)
	{
		m_possibleMoves.emplace_back(possiblePosition);
		possiblePosition.m_row--;
	}
	possiblePosition = { m_currentPosition.m_row, m_currentPosition.m_column };

	// right
	possiblePosition = { m_currentPosition.m_row, m_currentPosition.m_column };
	while (CBoard::BoundaryCheck(possiblePosition) && CBoard::GetPieceColor(possiblePosition) == EColor::None)
	{
		m_possibleMoves.emplace_back(possiblePosition);
		possiblePosition.m_column++;
	}
	possiblePosition = { m_currentPosition.m_row, m_currentPosition.m_column };

	// left
	possiblePosition = { m_currentPosition.m_row, m_currentPosition.m_column };
	while (CBoard::BoundaryCheck(possiblePosition) && CBoard::GetPieceColor(possiblePosition) == EColor::None)
	{
		m_possibleMoves.emplace_back(possiblePosition);
		possiblePosition.m_column--;
	}
}

CRook::~CRook()
{
}
