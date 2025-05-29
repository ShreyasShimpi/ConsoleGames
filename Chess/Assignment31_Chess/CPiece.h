#pragma once

// external includes
#include <vector>

// internal includes
#include "Defines.h"

class CPiece
{
protected:
	EColor m_color;
	SPosition m_currentPosition;
	sf::Sprite m_pieceSprite;

	std::vector<SPosition> m_possibleMoves;
public:
	// constructor
	CPiece() = delete;
	CPiece(const EColor& color,const SPosition& position, const sf::Sprite& pieceSprite);

	// functions
	inline const EColor& GetPieceColor() { return m_color; }
	inline bool HasValidMoves() { return !(m_possibleMoves.size() == 0); }
	inline const SPosition& GetCurrentPosition() { return m_currentPosition; }
	const SPosition& GetMoveFromPossibleMove();
	void RenderPieceSprite(sf::RenderTarget& target);
	void MovePiece(const SPosition& toPosition);

	// virtual function
	virtual bool IsMoveValid(const SPosition& toPosition) = 0;
	virtual void CalculatePossibleMoves() = 0;

	// destructor
	virtual ~CPiece() {};
};



