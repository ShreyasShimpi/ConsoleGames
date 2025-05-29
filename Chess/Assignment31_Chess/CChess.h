#pragma once

// external includes
#include <unordered_map>
#include <memory>

// internal includes
#include "Defines.h"

// forward declaration
class CBoard;
class CPiece;
class CAssetManager;

class CChess
{
private:
	// turn
	EColor m_turn;
	std::unordered_map<SPosition, std::unique_ptr<CPiece>, CCustomHashForPos> m_pieces;
	
	// reason for choosing map : frequent delete and insert operation
	std::unordered_map<SPosition, bool, CCustomHashForPos> m_aiPiecePositions; // AI, needed for randomization

	// sprites
	sf::Sprite m_backgroundSprite;
	std::unique_ptr<CAssetManager> m_assetManager;
	sf::RectangleShape m_hoverSquare;
	sf::RectangleShape m_selectSquare;
	bool m_isSelectedFrom;
	bool m_isSelectedTo;
	SPosition fromPosition;
	SPosition toPosition;

	// functions
	const EColor& DecodeColor(const char& colorCode);
	void RunAIPlayer();
	void RunNormalPlayer();
public:
	// constructor
	CChess();

	// function
	void UpdateConsole();
	void UpdateSFML(sf::RenderWindow& m_window, sf::Event& event);
	void Render(sf::RenderTarget& target);

	// destructor
	~CChess();
};

