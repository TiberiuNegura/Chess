#include "Game.h"
#include "Board.h"

#include "CheckException.h"
#include "InvalidOptionException.h"

IGamePtr IGame::Produce()
{
	return std::make_shared<Game>();
}

// Constructor
Game::Game()
	: m_turn(EColor::WHITE)
	, m_state(EGameState::Playing)
{
	
}

Game::Game(std::array<std::array<char, 8>, 8> mat, EColor turn)
	: m_board(mat)
	, m_turn(turn)
	, m_state(EGameState::Playing)
{
}

void Game::MovePiece(Position start, Position destination)
{
	if (IsGameOver())
		throw GameOverException();

	if (IsTieRequest())
		throw TieRequestException();

	if (IsPawnEvolving())
		throw PawnEvolveException();

	if (m_board.IsEmptyPosition(start))
		throw EmptyPositionException();

	if (Board::IsOutOfBounds(start) || Board::IsOutOfBounds(destination))
		throw OutOfBoundsException();

	PositionList positions = GetMoves(start); // creates pattern

	for (auto& position : positions)
		if (position == destination)
		{
			m_board.MovePiece(start, destination);
			// Castling condition
			if (m_board.Get(destination)->GetType() == EType::KING)
			{
				if (start.second - destination.second == 2)
					m_board.MovePiece({ start.first, 0 }, { start.first, 3 });
				else if (start.second - destination.second == -2)
					m_board.MovePiece({ start.first, 7 }, { start.first, 5 });
			}
			if (m_board.CanPawnEvolve(destination))
				UpdateState(EGameState::PawnEvolving);
			else
			{
				UpdateTurn();
				if (m_board.IsCheckmate(m_turn) && !m_board.IsCheck(m_turn))
					UpdateState(EGameState::Tie);
				else if (m_board.IsCheckmate(m_turn))
					m_turn == EColor::BLACK ? UpdateState(EGameState::WhiteWon) : UpdateState(EGameState::BlackWon);
			}
			return;
		}

	throw IllegalMoveException();
}


void Game::UpdateTurn()
{
	m_turn = (m_turn == EColor::WHITE ? EColor::BLACK : EColor::WHITE);
}

void Game::UpdateState(EGameState state)
{
	m_state = state;
}

class CustomMatrix : public IMatrix
{
public:
	CustomMatrix(const Matrix& mat)
		: m_board(mat)
	{ }
	IPiecePtr GetElement(Position element)
	{
		return m_board[element.first][element.second];
	}
private:
	const Matrix& m_board;
};

MatrixPtr Game::GetBoard() const
{
	return std::make_shared<CustomMatrix>(m_board.GetMatrix());
}

EColor Game::GetTurn() const
{
	return m_turn;
}

EGameState Game::GetState() const
{
	return m_state;
}

PositionList Game::GetMoves(Position piecePos) const
{
	return m_board.GetMoves(piecePos, m_turn);
}

void Game::MakeTieRequest()
{
	UpdateState(EGameState::TieRequest);
}

void Game::TieRequestResponse(bool answer)
{
	answer ? UpdateState(EGameState::Tie) : UpdateState(EGameState::Playing);
}

bool Game::IsTie() const
{
	return m_state == EGameState::Tie;
}

bool Game::BlackWon() const
{
	return m_state == EGameState::BlackWon;
}

bool Game::WhiteWon() const
{
	return m_state == EGameState::WhiteWon;
}

bool Game::IsTieRequest() const
{
	return m_state == EGameState::TieRequest;
}

bool Game::IsPawnEvolving() const
{
	return m_state == EGameState::PawnEvolving;
}

void Game::EvolvePawn(char pieceName)
{
	IPiecePtr piece;
	int row = m_turn == EColor::BLACK ? 0 : 7;
	for (int column = 0; column < 8; column++)
	{
		auto aux = GetBoard()->GetElement({ row, column });
		if (aux->GetType() == EType::PAWN)
			piece = aux;
	}
	switch (tolower(pieceName))
	{
	case 'b':
		piece = Piece::Produce(EType::BISHOP, m_turn);
		break;
	case 'q':
		piece = Piece::Produce(EType::QUEEN, m_turn);
		break;
	case 'r':
		piece = Piece::Produce(EType::ROOK, m_turn);
		break;
	case 'h':
		piece = Piece::Produce(EType::HORSE, m_turn);
		break;
	default:
		throw PieceNotFoundException();
	}
	UpdateTurn();
	if (m_board.IsCheckmate(m_turn) && !m_board.IsCheck(m_turn))
		UpdateState(EGameState::Tie);
	else if (m_board.IsCheckmate(m_turn))
		m_turn == EColor::BLACK ? UpdateState(EGameState::WhiteWon) : UpdateState(EGameState::BlackWon);

}

bool Game::IsGameOver() const
{
	return (WhiteWon() || IsTie() || BlackWon());
}

//void Game::MakeCastling(std::string where)
//{
//	if (m_board.IsCheck(m_turn))
//		throw CheckException();
//	
//	if (where != "left" && where != "right")
//		throw InvalidOptionException();
//
//	m_board.Castling(m_turn, where);
//	UpdateTurn();
//}

