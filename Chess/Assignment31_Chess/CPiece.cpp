#include "CPiece.h"
#include <ctime>

CPiece::CPiece(const EColor& color, const SPosition& position, const sf::Sprite& pieceSprite)
	:m_color(color), m_currentPosition(position), m_pieceSprite(pieceSprite)
{
	m_pieceSprite.setPosition(float(m_currentPosition.m_column * SPRITESIZE), float(m_currentPosition.m_row * SPRITESIZE));
}

const SPosition& CPiece::GetMoveFromPossibleMove()
{
	srand(time(NULL));

	if (m_possibleMoves.size() != 0)
	{
		int randMoveIndex = rand() % m_possibleMoves.size();
		return m_possibleMoves[randMoveIndex];
	}
}

void CPiece::RenderPieceSprite(sf::RenderTarget& target)
{
	target.draw(m_pieceSprite);
}

void CPiece::MovePiece(const SPosition& toPosition)
{
	m_currentPosition = toPosition;
	m_pieceSprite.setPosition(float(m_currentPosition.m_column * SPRITESIZE), float(m_currentPosition.m_row * SPRITESIZE));
}
