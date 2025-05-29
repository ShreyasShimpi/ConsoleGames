// external includes

// internal includes
#include "CBoard.h"
#include "CPawn.h"

CPawn::CPawn(const EColor& color, const SPosition& position, const sf::Sprite& pieceSprite)
	: CPiece(color, position, pieceSprite)
{
	m_firstMove = true;
}



bool CPawn::IsMoveValid(const SPosition& toPosition)
{
	short dir = (m_color == EColor::White) ? -1 : 1;
	if (m_currentPosition.m_row + dir + dir == toPosition.m_row &&
		m_currentPosition.m_column == toPosition.m_column &&
		m_firstMove)
	{
		m_firstMove = false;
		return true;
	}
	else if (m_currentPosition.m_row + dir == toPosition.m_row)
	{
		// no promotion so far
		if ((m_currentPosition.m_column - 1 == toPosition.m_column ||
			m_currentPosition.m_column + 1 == toPosition.m_column) &&
			(CBoard::GetPieceColor(toPosition) != EColor::None &&
			CBoard::GetPieceColor(toPosition) != m_color))
		{
			m_firstMove = false;
			return true;
		}
		else if (m_currentPosition.m_column == toPosition.m_column &&
			CBoard::GetPieceColor(toPosition) == EColor::None)
		{
			m_firstMove = false;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

void CPawn::CalculatePossibleMoves()
{
	m_possibleMoves.clear();

	short dir = (m_color == EColor::White) ? -1 : 1;
	if (m_firstMove)
	{
		m_possibleMoves.push_back(SPosition({ m_currentPosition.m_row + dir + dir, m_currentPosition.m_column}));
	}

	SPosition possiblePosition = { m_currentPosition.m_row + dir, m_currentPosition.m_column };
	if (CBoard::BoundaryCheck(possiblePosition) && CBoard::GetPieceColor(possiblePosition) == EColor::None)
	{
		m_possibleMoves.emplace_back(possiblePosition);
	}

	possiblePosition = { m_currentPosition.m_row + dir, m_currentPosition.m_column - 1 };
	if (CBoard::BoundaryCheck(possiblePosition) &&
		(CBoard::GetPieceColor(possiblePosition) != EColor::None &&
			CBoard::GetPieceColor(possiblePosition) != m_color)) // it should be of opposite color only
	{
		m_possibleMoves.emplace_back(possiblePosition);
	}
	possiblePosition = { m_currentPosition.m_row + dir, m_currentPosition.m_column + 1 };
	if (CBoard::BoundaryCheck(possiblePosition) &&
		(CBoard::GetPieceColor(possiblePosition) != EColor::None &&
			CBoard::GetPieceColor(possiblePosition) != m_color)) // it should be of opposite color only
	{
		m_possibleMoves.emplace_back(possiblePosition);
	}
}

CPawn::~CPawn()
{
}
