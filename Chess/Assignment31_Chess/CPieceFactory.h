#pragma once
// external includes
#include <memory>

// internal includes
#include "Defines.h"
#include "CPiece.h"
#include "CRook.h"
#include "CKnight.h"
#include "CBishop.h"
#include "CQueen.h"
#include "CKing.h"
#include "CPawn.h"

class CPieceFactory
{
public:
	// constructor
	CPieceFactory() = default;

	// static function
	static std::unique_ptr<CPiece> CreateShape(const char pieceCode, const EColor& color, const SPosition& position, const sf::Sprite& pieceSprite)
	{
		std::unique_ptr<CPiece> ptr;
		if (pieceCode == 'R') // rook
		{
			ptr = std::make_unique<CRook>(color, position,pieceSprite);

		}
		else if (pieceCode == 'N') // knight
		{
			ptr = std::make_unique<CKnight>(color, position, pieceSprite);
		}
		else if (pieceCode == 'B') // bishop
		{
			ptr = std::make_unique<CBishop>(color, position, pieceSprite);
		}
		else if (pieceCode == 'Q') // queen
		{
			ptr = std::make_unique<CQueen>(color, position, pieceSprite);
		}
		else if (pieceCode == 'K') // king
		{
			ptr = std::make_unique<CKing>(color, position, pieceSprite);
		}
		else if (pieceCode == 'P') // pawn
		{
			ptr = std::make_unique<CPawn>(color, position, pieceSprite);
		}
		
		return ptr;
	}

	// destructor
	~CPieceFactory()
	{
	}
};