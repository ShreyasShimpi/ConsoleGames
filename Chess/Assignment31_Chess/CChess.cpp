// external includes
#include <iostream>
#include <chrono>
#include <thread>

// internal includes
#include "CChess.h"
#include "CBoard.h"
#include "CPieceFactory.h"
#include "AssetManager.h"

CChess::CChess()
{
	m_turn = EColor::White;

	// init squares
	m_isSelectedFrom = false;
	m_isSelectedTo = false;
	m_selectSquare.setSize(sf::Vector2f(SPRITESIZE, SPRITESIZE));
	m_selectSquare.setPosition(-SPRITESIZE, -SPRITESIZE);
	m_selectSquare.setFillColor(sf::Color(0, 255, 0, 100));
	m_selectSquare.setOutlineThickness(-2);

	m_hoverSquare.setSize(sf::Vector2f(SPRITESIZE, SPRITESIZE));
	m_hoverSquare.setPosition(-SPRITESIZE, -SPRITESIZE);

	// setup bg
	char bg[3] = "BG";
	m_assetManager = std::make_unique<CAssetManager>();
	m_backgroundSprite = m_assetManager->GetSprite(bg);

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			const char pieceCode = CBoard::ms_board[i][j][1];
			const char pieceColor = CBoard::ms_board[i][j][0];

			EColor decodedColor = DecodeColor(pieceColor);
			if (decodedColor != EColor::None)
			{
				m_pieces.insert(std::make_pair(
					SPosition({ i, j }),
					CPieceFactory::CreateShape(pieceCode, decodedColor, SPosition({ i, j }), m_assetManager->GetSprite(CBoard::ms_board[i][j]))));

				// store the pieces for ai for randomization
				if (decodedColor == g_AIcolor)
				{
					m_aiPiecePositions.insert(std::make_pair(SPosition({ i, j }), true));
				}
			}
		}
	}
}


const EColor& CChess::DecodeColor(const char& colorCode)
{
	switch (colorCode)
	{
	case 'W':
		return EColor::White;
		break;
	case 'B':
		return EColor::Black;
		break;
	case ' ':
		return EColor::None;
		break;
	default:
		break;
	}
}

void CChess::RunAIPlayer()
{
	CBoard::DrawBoard();

	std::printf("Turn : %s", (m_turn == EColor::White) ? "White" : "Black");

	std::cout << "\n\nWaiting for AI to play...\n";

	auto randomPiece = m_aiPiecePositions.begin();
	SPosition randomPiecePos = randomPiece->first;
	do
	{
		randomPiece = m_aiPiecePositions.begin();
		std::advance(randomPiece, rand() % m_aiPiecePositions.size());
		randomPiecePos = randomPiece->first;
		m_pieces.at(randomPiecePos)->CalculatePossibleMoves();

	} while (!m_pieces.at(randomPiecePos)->HasValidMoves());

	SPosition toPosition = m_pieces.at(randomPiecePos)->GetMoveFromPossibleMove();

	// we are executing the move
	if (CBoard::GetPieceColor(toPosition) == EColor::None) // if upcoming position is empty
	{
		// then insert
		m_pieces.insert(std::make_pair(
			toPosition,
			std::move(m_pieces.at(randomPiecePos))));
		m_pieces.erase(randomPiecePos);
		m_pieces.at(toPosition)->MovePiece(toPosition);
	}
	else // piece capture
	{
		m_pieces.at(toPosition) = std::move(m_pieces.at(randomPiecePos));
		m_pieces.erase(randomPiecePos);
		m_pieces.at(toPosition)->MovePiece(toPosition);
	}

	// update ai piece position
	m_aiPiecePositions.insert(std::make_pair(toPosition, true));
	m_aiPiecePositions.erase(randomPiecePos);
	CBoard::Move(randomPiecePos, toPosition);

	// after execution is complete, set the turn, increase the number of moves
	m_turn = (m_turn == EColor::White) ? EColor::Black : EColor::White;
	s_moveNumber++;


	// wait for 2 sec for ai to play
	std::this_thread::sleep_for(std::chrono::seconds(AI_Sleep));
}

void CChess::RunNormalPlayer()
{
	char fromSquare[3]; // 2 for move instruction, 3rd for newline char
	char toSquare[3];
	bool isMoveValid;

	isMoveValid = true;
	system("cls");

	do
	{	
		CBoard::DrawBoard();

		std::printf("Turn : %s", (m_turn == EColor::White) ? "White" : "Black");
		std::cout << "\nEnter the starting piece position: ";
		std::cout << "\nFrom: ";
		std::cin >> fromSquare;

		std::cout << "To: ";
		std::cin >> toSquare;

		if (ValidateInput(fromSquare) && ValidateInput(toSquare) // characters should be from A to H and 1 to 8)
			&& std::string(fromSquare) != std::string(toSquare))  // from and to should not be same squares
		{
			SPosition fromPosition = CBoard::DecodeMove(fromSquare);
			SPosition toPosition = CBoard::DecodeMove(toSquare);

			if (CBoard::GetPieceColor(fromPosition) != m_turn) // white should only play white piece,  
			{
				isMoveValid = false;
				std::cout << "\nError 102: Invalid Initial Piece Choice.\n";
			}
			else if (CBoard::GetPieceColor(toPosition) == m_turn)// ToPosition should not contain piece of same color
			{
				isMoveValid = false;
				std::cout << "\nError 103: Invalid Target Position.\n";
			}
			else
			{
				if (m_pieces.at(fromPosition)->IsMoveValid(toPosition))
				{
					// we are executing the move
					if (CBoard::GetPieceColor(toPosition) == EColor::None) // if upcoming position is empty
					{
						// then insert
						m_pieces.insert(std::make_pair(
							toPosition,
							std::move(m_pieces.at(fromPosition))));
						m_pieces.erase(fromPosition);
						m_pieces.at(toPosition)->MovePiece(toPosition);
					}
					else // piece capture
					{
						m_pieces.at(toPosition) = std::move(m_pieces.at(fromPosition));
						m_pieces.erase(fromPosition);
						m_pieces.at(toPosition)->MovePiece(toPosition);

						// erase from ai piece as its captured, O(1) operation
						m_aiPiecePositions.erase(fromPosition);
					}

					CBoard::Move(fromPosition, toPosition);

					// after execution is complete, set the turn, increase the number of moves
					m_turn = (m_turn == EColor::White) ? EColor::Black : EColor::White;
					s_moveNumber++;
				}
				else
				{
					isMoveValid = false;
					std::cout << "\nError 104: Invalid Move.\n";
				}
			}
		}
		else
		{
			isMoveValid = false;
			std::cout << "\nError 101: Invalid Input.\n";
		}

	} while (!isMoveValid);
}

void CChess::UpdateConsole()
{
	srand(time(NULL));
	if (g_hasAI)
	{
		if (m_turn != g_AIcolor) // player turn white
		{
			RunNormalPlayer();
		}
		else // ai turn
		{
			RunAIPlayer();
		}
	}
	else
	{
		RunNormalPlayer();
	}
	
}

void CChess::UpdateSFML(sf::RenderWindow& window, sf::Event& event)
{
	static bool pressed = false;

	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	if (mousePos.x <= 0 || mousePos.y <= 0 || mousePos.x >= WIDTH || mousePos.y >= HEIGHT)
	{
		return;
	}

	SPosition mouseHoverSquarePos = { int(mousePos.y / SPRITESIZE), int(mousePos.x / SPRITESIZE) };

	m_hoverSquare.setPosition((int(mousePos.x / SPRITESIZE) * SPRITESIZE), (int(mousePos.y / SPRITESIZE) * SPRITESIZE));
	/*
		The hoverSquare will be red if hovered on empty block and opposite turn block
	*/
	if (!m_isSelectedFrom && !m_isSelectedTo)
	{
		if (CBoard::GetPieceColor(mouseHoverSquarePos) != m_turn)
		{
			m_hoverSquare.setFillColor(sf::Color(255, 0, 0, 50));
		}
		else // allowed click
		{
			m_hoverSquare.setFillColor(sf::Color(0, 255, 0, 50));

			// if clicked mouse button
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				m_selectSquare.setPosition((int(mousePos.x / SPRITESIZE) * SPRITESIZE), (int(mousePos.y / SPRITESIZE) * SPRITESIZE));
				fromPosition = { int(mousePos.y / SPRITESIZE), int(mousePos.x / SPRITESIZE) };
				m_isSelectedFrom = true;
				m_isSelectedTo = false;
				pressed = true;
			}
		}
	}
	else if(m_isSelectedFrom && !m_isSelectedTo)
	{	
		m_hoverSquare.setFillColor(sf::Color(255, 0, 0, 50));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			m_selectSquare.setPosition(float(-SPRITESIZE), float(-SPRITESIZE));
			fromPosition = { 0, 0 };
			m_isSelectedFrom = false;
		}
		
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && !pressed)
		{
			toPosition = { int(mousePos.y / SPRITESIZE), int(mousePos.x / SPRITESIZE) };
			std::cout << toPosition.m_row << " " << toPosition.m_column << "\n";
			m_isSelectedTo = true;
		} 
		else
		{
			pressed = false;
		}
	}
	else if (m_isSelectedFrom && m_isSelectedTo)
	{
		if (CBoard::GetPieceColor(toPosition) != m_turn &&
			!(toPosition == fromPosition) &&
			m_pieces.at(fromPosition)->IsMoveValid(toPosition))
		{
			// we are executing the move
			if (CBoard::GetPieceColor(toPosition) == EColor::None) // if upcoming position is empty
			{
				// then insert
				m_pieces.insert(std::make_pair(
					toPosition,
					std::move(m_pieces.at(fromPosition))));
				m_pieces.erase(fromPosition);
				m_pieces.at(toPosition)->MovePiece(toPosition);
			}
			else // piece capture
			{
				m_pieces.at(toPosition) = std::move(m_pieces.at(fromPosition));
				m_pieces.erase(fromPosition);
				m_pieces.at(toPosition)->MovePiece(toPosition);
			}

			CBoard::Move(fromPosition, toPosition);

			// after execution is complete, set the turn, increase the number of moves
			m_turn = (m_turn == EColor::White) ? EColor::Black : EColor::White;
			s_moveNumber++;
			m_isSelectedFrom = false;
			m_isSelectedTo = false;
		}
		else
		{
			m_isSelectedFrom = false;
			m_isSelectedTo = false;
		}
	}
}


void CChess::Render(sf::RenderTarget& target)
{
	// render background
	target.draw(m_backgroundSprite);

	// hover square
	target.draw(m_hoverSquare);
	if (m_isSelectedFrom)
	{
		target.draw(m_selectSquare);
	}

	// render pieces
	for (auto& piece : m_pieces)
	{
		piece.second->RenderPieceSprite(target);
	}

	
}

CChess::~CChess()
{
}
