#include "Game.h"

Game::Game()
{
	for (int column = 0; column < 8; column++) {
		m_board[1][column] = std::make_shared<Pawn>();
		m_board[6][column] = std::make_shared<Pawn>();
	}
	m_board[0][0] = std::make_shared<Rook>();
	m_board[0][7] = std::make_shared<Rook>();
	m_board[7][0] = std::make_shared<Rook>();
	m_board[7][7] = std::make_shared<Rook>();

	m_board[0][1] = std::make_shared<Horse>();
	m_board[0][6] = std::make_shared<Horse>();
	m_board[7][1] = std::make_shared<Horse>();
	m_board[7][6] = std::make_shared<Horse>();

	m_board[0][2] = std::make_shared<Bishop>();
	m_board[0][5] = std::make_shared<Bishop>();
	m_board[7][2] = std::make_shared<Bishop>();
	m_board[7][5] = std::make_shared<Bishop>();

	m_board[0][3] = std::make_shared<Queen>();
	m_board[7][3] = std::make_shared<Queen>();

	m_board[0][4] = std::make_shared<King>();
	m_board[7][4] = std::make_shared<King>();

}

PiecePtr Game::getElement(int row, int column)
{
	return m_board[row][column];
}
