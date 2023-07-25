#include <map>

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
	boardConfigs.push_back(m_board.GetBoardConfiguration());
}

Game::Game(CharBoardRepresentation mat, EColor turn, EGameState state)
	: m_board(mat)
	, m_turn(turn)
	, m_state(state)
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
	{
		if (position == destination)
		{
			m_board.MovePiece(start, destination);
			m_board.Get(destination)->SetHasMoved();
			
			
			// Castling condition

			if (m_board.Get(destination)->GetType() == EType::KING)
			{
				if (start.second - destination.second == 2)
					m_board.MovePiece({ start.first, 0 }, { start.first, 3 });
				else if (start.second - destination.second == -2)
					m_board.MovePiece({ start.first, 7 }, { start.first, 5 });
			}

			if (m_board.CanPawnEvolve(destination))
			{
				UpdateState(EGameState::PawnEvolving);
				return;
			}

			UpdateTurn();
			bool opponentInCheck = m_board.IsCheck(m_turn);
			bool opponentInCheckmate = m_board.IsCheckmate(m_turn);
			if (opponentInCheck)
				UpdateState(EGameState::Check);
			if (opponentInCheckmate && !opponentInCheck)
				UpdateState(EGameState::Tie);
			else if (opponentInCheckmate)
				m_turn == EColor::BLACK ? UpdateState(EGameState::WhiteWon) : UpdateState(EGameState::BlackWon);
			else if (!opponentInCheck)
				UpdateState(EGameState::Playing);

			std::bitset<256> configuration = m_board.GetBoardConfiguration();
			boardConfigs.push_back(configuration);
			if (m_board.IsThreeFold(boardConfigs, configuration))
				UpdateState(EGameState::Tie);


			return;
		}
	}

	if (IsCheck())
		throw CheckException();
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
	if (IsGameOver())
		return PositionList();
	return m_board.GetMoves(piecePos, m_turn);
}

void Game::MakeTieRequest()
{
	UpdateState(EGameState::TieRequest);
	Notify(Response::TIE_REQUEST);
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

void Game::EvolvePawn(const std::string& pieceName)
{
	Position piecePos = m_board.FindEvolvingPawn(m_turn);
	if (pieceName == "Bishop")
		m_board.Set(piecePos, Piece::Produce(EType::BISHOP, m_turn));
	else if (pieceName == "Queen")
		m_board.Set(piecePos, Piece::Produce(EType::QUEEN, m_turn));
	else if (pieceName == "Rook")
		m_board.Set(piecePos, Piece::Produce(EType::ROOK, m_turn));
	else if (pieceName == "Horse")
		m_board.Set(piecePos, Piece::Produce(EType::HORSE, m_turn));
	else 
		throw PieceNotFoundException();

	UpdateTurn();
	if (m_board.IsCheckmate(m_turn) && !m_board.IsCheck(m_turn))
		UpdateState(EGameState::Tie);
	else if (m_board.IsCheckmate(m_turn))
		m_turn == EColor::BLACK ? UpdateState(EGameState::WhiteWon) : UpdateState(EGameState::BlackWon);
	else
		UpdateState(EGameState::Playing);

}

bool Game::IsCheck() const
{
	return m_state == EGameState::Check;
}

bool Game::IsGameOver() const
{
	return (WhiteWon() || IsTie() || BlackWon());
}

void Game::AddListener(IGameListener* listener)
{
	listeners.push_back(listener);
}

void Game::RemoveListener(IGameListener* listener)
{
	for (auto it = listeners.begin(); it != listeners.end();)
		if (*it == listener)
			it = listeners.erase(it);
		else
			++it;
}

void Game::Notify(Response response)
{
	for (auto listener : listeners)
	{
		switch (response)
		{
		case Response::CHECK:
			listener->OnCheck();
				break;
		case Response::PAWN_UPGRADE:
			listener->OnPawnEvolve();
			break;
		case Response::TIE_REQUEST:
			listener->OnTieRequest();
			break;
		case Response::MOVE:
			listener->OnMovePiece();
			break;
		case Response::WHITE_WON:
		case Response::BLACK_WON:
		case Response::TIE:
			listener->OnGameOver();
			break;
		default:
			break;
		}
	}
}


