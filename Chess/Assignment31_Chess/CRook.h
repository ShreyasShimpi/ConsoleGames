#pragma once

// external includes

// internal includes
#include "Defines.h"
#include "CPiece.h"

// forward declaration

class CRook : public CPiece
{
public:
	// constructor
	CRook() = delete;
	CRook(const EColor& color, const SPosition& position, const sf::Sprite& pieceSprite);

	// functions
	bool IsMoveValid(const SPosition& toPosition) override;
	void CalculatePossibleMoves() override;

	// destructor
	~CRook();
};

