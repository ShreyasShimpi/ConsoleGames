#include "CBoard.h"

std::array<std::array<char[3], SIZE>, SIZE> CBoard::ms_board =
{ {{"BR", "BN", "BB", "BQ", "BK", "BB", "BN", "BR"},
   {"BP", "BP", "BP", "BP", "BP", "BP", "BP", "BP"},
   {"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
   {"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
   {"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
   {"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
   {"WP", "WP", "WP", "WP", "WP", "WP", "WP", "WP"},
   {"WR", "WN", "WB", "WQ", "WK", "WB", "WN", "WR"}} };

bool CBoard::BoundaryCheck(const SPosition& position)
{
	return (position.m_row > 0 && position.m_column > 0 && position.m_row < SIZE && position.m_column < SIZE);
}

void CBoard::Move(const SPosition& fromPosition, const SPosition& toPosition)
{
	// overwrite the piece at ToPosition
	ms_board[toPosition.m_row][toPosition.m_column][0] = ms_board[fromPosition.m_row][fromPosition.m_column][0];
	ms_board[toPosition.m_row][toPosition.m_column][1] = ms_board[fromPosition.m_row][fromPosition.m_column][1];

	// empty the initial position
	ms_board[fromPosition.m_row][fromPosition.m_column][0] = ' ';
	ms_board[fromPosition.m_row][fromPosition.m_column][1] = ' ';

}

SPosition CBoard::DecodeMove(const char* move)
{
	int column = int(move[0]) - 65;
	int row = int(move[1]) - 49;

	return { SIZE - 1 - row, column };
}


const EColor CBoard::GetPieceColor(const SPosition& position)
{
	if (ms_board[position.m_row][position.m_column][0] == 'W')
	{
		return EColor::White;
	}
	else if (ms_board[position.m_row][position.m_column][0] == 'B')
	{
		return EColor::Black;
	}
	else
	{
		return EColor::None;
	}
}

void CBoard::DrawBoard()
{
	std::cout << "CHESS BOARD : \n";
	

	std::cout << "\n\t  ";

	for (int j = 0; j < SIZE; j++)
	{
		std::cout << "____ ";
	}
	std::cout << "\n";

	for (int i = 0; i < SIZE; i++)
	{
		std::cout << "\t |";
		for (int j = 0; j < SIZE; j++)
		{

			std::cout << "    |";
		}
		std::cout << "\n\t" << SIZE - i << "|";
		for (int j = 0; j < SIZE; j++)
		{
			std::cout << " " << ms_board[i][j] << " |";
		}
		std::cout << "\n\t |";
		for (int j = 0; j < SIZE; j++)
		{
			std::cout << "____|";
		}
		std::cout << "\n";
	}

	std::cout << "\t ";
	for (char i = 'A'; i < 'A' + SIZE; i++)
	{
		std::printf("  %-3c", i);
	}
	std::cout << "\n";
}
