#pragma once

// external includes

// internal includes
#include "Defines.h"
#include "CPiece.h"

// forward declaration

class CPawn : public CPiece
{
private:
	bool m_firstMove;
public:
	// constructor
	CPawn() = delete;
	CPawn(const EColor& color, const SPosition& position, const sf::Sprite& pieceSprite);

	// functions
	bool IsMoveValid(const SPosition& toPosition) override;
	void CalculatePossibleMoves() override;

	// destructor
	~CPawn();
};

