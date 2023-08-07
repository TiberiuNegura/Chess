#include <map>
#include <set>
#include <regex>
#include <fstream>

#include "Game.h"
#include "Board.h"
#include "FileUtils.h"

#include "CheckException.h"
#include "InvalidOptionException.h"
#include "InvalidFileException.h"

IGamePtr IGame::Produce()
{
	return std::make_shared<Game>();
}

IGamePtr IGame::Produce(PGN backup)
{
	return std::make_shared<Game>(backup);
}

// Constructor
Game::Game()
	: m_turn(EColor::WHITE)
	, m_state(EGameState::Playing)
	, m_isLoading(false)
{
	m_boardConfigs.push_back(m_board.GetBoardConfiguration());
}

Game::Game(CharBoardRepresentation mat, EColor turn, EGameState state)
	: m_board(mat)
	, m_turn(turn)
	, m_state(state)
	, m_isLoading(false)
{

}

Game::Game(const PGN& backup)
	: m_pgn(backup)
	, m_turn(EColor::WHITE)
	, m_state(EGameState::Playing)
	, m_isLoading(false)
{

}

PGN Game::MakeBackup() const
{
	return m_pgn;
}

void Game::LoadBackup(PGN backup)
{
	Restart();
	m_pgn = backup;
	LoadFromPGN(backup.ComputeMovesPgn(), true);
}

bool Game::LoadFromFormat(std::string path)
{
	PGN backup = m_pgn;

	try
	{
		if (!FileUtils::HasAnyExtension(path, "pgn", "fen"))
			return false;

		Restart();

		if (FileUtils::HasAnyExtension(path, "pgn"))
			LoadFromPGN(path);

		if (FileUtils::HasAnyExtension(path, "fen"))
			LoadFromFEN(path);
		
	}
	catch (...)
	{
		Restart();
		LoadFromPGN(backup.ComputeMovesPgn(), true);
		m_pgn = backup;

		return false;
	}

	return true;
}

void Game::LoadFromFEN(std::string path)
{
	
	std::ifstream file(path);
	if (file.good())
	{
		std::string fen;

		std::getline(file, fen);
		file.close();

		m_board.LoadFromFEN(fen);
		m_turn = fen.back() == 'w' ? EColor::WHITE : EColor::BLACK;
	}
}

void Game::LoadFromPGN(std::string path, bool loadFromBackup)
{
	m_isLoading = true;
	std::string pgn;

	if (!loadFromBackup)
	{
		if (m_pgn.Load(path))
			pgn = m_pgn.GetFullPgn();
		else
			throw InvalidFileException();
	}
	else
		pgn = path;

	static const std::set<std::string> evolve = { "=Q","=B","=H","=R" };
	pgn = std::regex_replace(pgn, std::regex("\\b\\d+\\. |[+#x]"), "");
	std::string pgnMove;
	Move move;

	for (int i = 0; i < pgn.size(); i++)
	{
		if (pgn[i] == ' ' || (i == pgn.size() - 1))
		{
			int row = m_turn == EColor::WHITE ? 7 : 0;
			bool isEvolving = FindSubstring(pgnMove, evolve);
			char upgrade;

			if (pgnMove == "O-O" || pgnMove == "0-0")
				MovePiece({ row, 4 }, {row, 6});
			else if (pgnMove == "O-O-O" || pgnMove == "0-0-0")
				MovePiece({ row, 4 }, { row, 2 });
			else
			{
				if (isEvolving)
				{
					upgrade = pgnMove[pgnMove.size() - 1];
					pgnMove.erase(pgnMove.size() - 2);
				}

				move = ChessMoveToMatrix(pgnMove);
				MovePiece(move.first, move.second);

				if (isEvolving)
				{
					EType upgradeTo = m_board.CharToType(upgrade);
					EvolvePawn(upgradeTo);
				}
			}
			pgnMove.clear();
		}
		if (pgn[i] != ' ')
			pgnMove += pgn[i];
	}
	m_isLoading = false;
}

Move Game::ChessMoveToMatrix(const std::string& move)
{
	static const std::set<char> validChars = { 'B' ,'R' ,'Q' ,'K' ,'H' };
	Position end, start;

	end.first = '8' - move[move.size() - 1];
	end.second = move[move.size() - 2] - 'a';

	if (move.size() == 5)
	{
		start.first = '8' - move[2];
		start.second = move[1] - 'a';
	}
	else if (move.size() == 4)
		start = m_board.FindForPGN(move[0], end, m_turn, move[1]);
	else
		start = m_board.FindForPGN(move[0], end, m_turn);
	
	return { start, end };
}


void Game::PreviewPastConfig(int moveIndex)
{
	BoardConfig config = m_boardConfigs[++moveIndex];
	m_board.SetBoardConfiguration(config);
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
	bool captures = false;
	
	for (auto& position : positions)
	{
		if (position == destination)
		{
			if (auto capturedPiece = m_board[destination])
			{
				auto& missing = m_turn == EColor::BLACK ? m_whiteMissing : m_blackMissing;
				missing.push_back(capturedPiece->GetType());

				Notify(capturedPiece->GetType(), capturedPiece->GetColor());
				captures = true;
			}

			std::string lineOrCol = m_board.SharedLineOrColumn(start, destination);

			m_board.MovePiece(start, destination);
			m_pgn.Add(m_board.MatrixToChessMove(start, destination, captures, lineOrCol)); // pgn
			Notify(start, destination);
			m_board[destination]->SetHasMoved();
			
			// Castling condition
			if (m_board[destination]->Is(EType::KING))
			{
				if (start.second - destination.second == 2)
					m_board.MovePiece({ start.first, 0 }, { start.first, 3 });
				else if (start.second - destination.second == -2)
					m_board.MovePiece({ start.first, 7 }, { start.first, 5 });
			}

			if (m_board.CanPawnEvolve(destination))
			{
				UpdateState(EGameState::PawnEvolving);
				if (!m_isLoading)
					Notify(Response::PAWN_UPGRADE);
				return;
			}

			UpdateTurn();
			bool opponentInCheck = m_board.IsCheck(m_turn);
			bool opponentInCheckmate = m_board.IsCheckmate(m_turn);
			if (opponentInCheck)
			{
				UpdateState(EGameState::Check);
				Notify(Response::CHECK);
			}
			if (opponentInCheckmate && !opponentInCheck)
			{
				UpdateState(EGameState::Tie);
				Notify(Response::TIE);
			}
			else if (opponentInCheckmate)
			{
				if (m_turn == EColor::BLACK)
				{
					UpdateState(EGameState::WhiteWon);
					Notify(Response::WHITE_WON);
				}
				else
				{
					UpdateState(EGameState::BlackWon);
					Notify(Response::BLACK_WON);
				}
			}
			else if (!opponentInCheck)
				UpdateState(EGameState::Playing);

			BoardConfig configuration = m_board.GetBoardConfiguration();
			m_boardConfigs.push_back(configuration);
			if (m_board.IsThreeFold(m_boardConfigs, configuration))
			{
				UpdateState(EGameState::Tie);
				Notify(Response::TIE);
			}
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

TypeList Game::GetMissingPieces(EColor color) const
{
	return color == EColor::WHITE ? m_whiteMissing : m_blackMissing;;
}


std::string Game::GetFenString() const
{
	std::string output = m_board.GetFenString();
	output.push_back(' ');
	m_turn == EColor::BLACK ? output.push_back('b') : output.push_back('w');
	return output;
}

PGN Game::GetPGN() const
{
	return m_pgn;
}

void Game::SavePGN(std::string path) const
{
	m_pgn.Save(path);
}

void Game::SaveFEN(std::string path) const
{
	std::ofstream file(path);
	if (file.good())
	{
		file << GetFenString();
	}
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

void Game::EvolvePawn(EType pieceType)
{
	Position piecePos = m_board.FindEvolvingPawn(m_turn);
	
	if (pieceType == EType::BISHOP)
	{
		m_pgn.AppendToLastMove("=B");
		m_board.Set(piecePos, Piece::Produce(EType::BISHOP, m_turn));
	}
	else if (pieceType == EType::QUEEN)
	{
		m_pgn.AppendToLastMove("=Q");
		m_board.Set(piecePos, Piece::Produce(EType::QUEEN, m_turn));
	}
	else if (pieceType == EType::ROOK)
	{
		m_pgn.AppendToLastMove("=R");
		m_board.Set(piecePos, Piece::Produce(EType::ROOK, m_turn));
	}
	else if (pieceType ==  EType::HORSE)
	{
		m_pgn.AppendToLastMove("=H");
		m_board.Set(piecePos, Piece::Produce(EType::HORSE, m_turn));
	}
	else 
		throw PieceNotFoundException();

	UpdateTurn();
	bool opponentInCheck = m_board.IsCheck(m_turn);
	bool opponentInCheckmate = m_board.IsCheckmate(m_turn);

	if (opponentInCheck)
		m_pgn.AppendToLastMove("+");
	if (opponentInCheckmate && !opponentInCheck)
		UpdateState(EGameState::Tie);
	else if (m_board.IsCheckmate(m_turn)) 
	{
		m_pgn.AppendToLastMove("#");
		m_turn == EColor::BLACK ? UpdateState(EGameState::WhiteWon) : UpdateState(EGameState::BlackWon);
	}
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

bool Game::FindSubstring(std::string input, const std::set<std::string>& substrings) const
{
	for (const auto& substring : substrings) {
		if (input.find(substring) != std::string::npos) {
			return true;
		}
	}
	return false;
}

void Game::Restart()
{
	m_board.Reset();
	m_board.Init();
	m_turn = EColor::WHITE;
	m_state = EGameState::Playing;
	m_whiteMissing.clear();
	m_blackMissing.clear();
	m_boardConfigs.clear();
	m_pgn.Clear();

	Notify(Response::RESTART);
}

void Game::AddListener(ListenerWeakPtr listener)
{
	m_listeners.push_back(listener);
}

void Game::RemoveListener(IGameListener* listener)
{
	m_listeners.erase(
		std::remove_if(
			m_listeners.begin(),
			m_listeners.end(),
			[listener](ListenerWeakPtr& weak)
			{
				auto sp = weak.lock();
				return !sp || sp.get() == listener;
			}
	));
}

void Game::Notify(Response response)
{
	for (auto listener : m_listeners)
	{
		switch (response)
		{
		case Response::CHECK:
			listener.lock()->OnCheck(CheckException().what());
				break;
		case Response::PAWN_UPGRADE:
			listener.lock()->OnPawnEvolve();
			break;
		case Response::TIE_REQUEST:
			listener.lock()->OnTieRequest();
			break;
		case Response::WHITE_WON:
		case Response::BLACK_WON:
		case Response::TIE:
			listener.lock()->OnGameOver();
			break;
		case Response::RESTART:
			listener.lock()->OnRestart();
			break;
		}
	}
}

void Game::Notify(Position start, Position end)
{
	for (auto listener : m_listeners)
		listener.lock()->OnMovePiece(start, end);
}

void Game::Notify(EType pieceType, EColor pieceColor)
{
	for (auto listener : m_listeners)
		listener.lock()->OnPieceCapture(pieceType, pieceColor);
} // TODO: test

