#include "Board.h"
#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "Horse.h"
#include "Queen.h"
#include "King.h"

Board::Board()
{
	// Board initialize

	// Pawns
	for (int column = 0; column < 8; column++) {
		m_board[1][column] = std::make_shared<Pawn>(1, column, Color::BLACK);
		m_board[6][column] = std::make_shared<Pawn>(6, column, Color::WHITE);
	}

	// Rooks
	m_board[0][0] = std::make_shared<Rook>(0, 0, Color::BLACK);
	m_board[0][7] = std::make_shared<Rook>(0, 7, Color::BLACK);
	m_board[7][0] = std::make_shared<Rook>(7, 0, Color::WHITE);
	m_board[7][7] = std::make_shared<Rook>(7, 7, Color::WHITE);

	// Horses
	m_board[0][1] = std::make_shared<Horse>(0, 1, Color::BLACK);
	m_board[0][6] = std::make_shared<Horse>(0, 6, Color::BLACK);
	m_board[7][1] = std::make_shared<Horse>(7, 1, Color::WHITE);
	m_board[7][6] = std::make_shared<Horse>(7, 6, Color::WHITE);

	// Bishops
	m_board[0][2] = std::make_shared<Bishop>(0, 2, Color::BLACK);
	m_board[0][5] = std::make_shared<Bishop>(0, 5, Color::BLACK);
	m_board[7][2] = std::make_shared<Bishop>(7, 2, Color::WHITE);
	m_board[7][5] = std::make_shared<Bishop>(7, 5, Color::WHITE);

	// Queens
	m_board[0][3] = std::make_shared<Queen>(0, 3, Color::BLACK);
	m_board[7][3] = std::make_shared<Queen>(7, 3, Color::WHITE);

	// Kings
	m_board[0][4] = std::make_shared<King>(0, 4, Color::BLACK);
	m_board[7][4] = std::make_shared<King>(7, 4, Color::WHITE);
}

Matrix& Board::GetGameBoard()
{
	return m_board;
}

void Board::MoveOnBoard(Position start, Position destination)
{
	m_board[start.first][start.second]->Move(destination, m_board);
	//TODO: implement exception
}
