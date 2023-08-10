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

using namespace std::literals::chrono_literals;

IGamePtr IGame::Produce(int timerSeconds)
{
	return std::make_shared<Game>(timerSeconds);
}

// Constructor
Game::Game(int timerTime)
	: m_turn(EColor::WHITE)
	, m_currentState(EGameState::Paused)
	, m_lastState(EGameState::Paused)
	, m_bEnableNotifications(true)
	, m_timerTime(timerTime)
	, m_whiteTimer(timerTime)
	, m_blackTimer(timerTime)
	, m_roundTime(0s)
{
	m_boardConfigs.push_back(m_board.GetBoardConfiguration());
}

Game::Game(CharBoardRepresentation mat, EColor turn, EGameState state)
	: m_board(mat)
	, m_turn(turn)
	, m_currentState(state)
	, m_lastState(state)
	, m_bEnableNotifications(true)
	, m_blackTimer(0s)
	, m_whiteTimer(0s)
	, m_timerTime(0s)
	, m_roundTime(0s)
{

}


bool Game::LoadFromFormat(const std::string& path)
{
	PGN currentPGN = m_pgn;
	try
	{
		if (!FileUtils::HasAnyExtension(path, "pgn", "fen"))
			return false;

		Restart();

		if (FileUtils::HasAnyExtension(path, "pgn"))
		{
			m_currentState = EGameState::Playing;
			if (m_pgn.Load(path))
				LoadFromPGN(m_pgn);
		}

		if (FileUtils::HasAnyExtension(path, "fen"))
		{
			LoadFromFEN(path);
			m_whiteMissing = m_board.SearchMissingPieces(EColor::WHITE);
			m_blackMissing = m_board.SearchMissingPieces(EColor::BLACK);
		}
		
	}
	catch (...)
	{
		Restart();
		LoadFromPGN(currentPGN, true);
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

void Game::LoadFromPGN(PGN pgnObj, bool loadFromBackup)
{
	m_bEnableNotifications = false;

	std::string pgn = loadFromBackup ? pgnObj.ComputeMovesPgn() : pgnObj.GetMovesString();

	static const std::set<std::string> evolve = { "=Q","=B","=H","=R", "=N"};
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
					if (upgrade == 'N')
						upgrade = 'H';
					EType upgradeTo = m_board.CharToType(upgrade);
					EvolvePawn(upgradeTo);
				}
			}
			pgnMove.clear();
		}
		if (pgn[i] != ' ')
			pgnMove += pgn[i];
	}
	m_bEnableNotifications = true;
}

Move Game::ChessMoveToMatrix(const std::string& move)
{
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

void Game::Start()
{
	if (!m_timer.HadStarted() && m_blackTimer != 0s && m_whiteTimer != 0s)
	{
		m_timer.AddListener(shared_from_this());
		m_timer.Start();
	}
	m_currentState = EGameState::Playing;
}

void Game::Pause()
{
	m_lastState = m_currentState;
	m_timer.Pause();
	m_currentState = EGameState::Paused;
}

void Game::Resume()
{
	m_timer.Resume();
	m_currentState = m_lastState;
}

void Game::Stop()
{
	m_timer.Stop();
}

bool Game::IsStarted() const
{
	return m_timer.HadStarted();
}

bool Game::IsPaused() const
{
	return m_currentState == EGameState::Paused;
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
			m_gameMoves.emplace_back(start, destination);
			m_board[destination]->SetHasMoved();
			
			// Castling condition
			if (m_board[destination]->Is(EType::KING))
			{
				if (start.second - destination.second == 2)
					m_board.MovePiece({ start.first, 0 }, { start.first, 3 });
				else if (start.second - destination.second == -2)
					m_board.MovePiece({ start.first, 7 }, { start.first, 5 });
			}

			BoardConfig configuration = m_board.GetBoardConfiguration();
			m_boardConfigs.push_back(configuration);

			if (m_board.CanPawnEvolve(destination))
			{
				UpdateState(EGameState::PawnEvolving);
				Notify(EResponse::PawnUpgrade);
				return;
			}

			UpdateTurn();
			bool opponentInCheck = m_board.IsCheck(m_turn);
			bool opponentInStalemate = m_board.IsStalemate(m_turn);
			if (opponentInCheck)
			{
				UpdateState(EGameState::Check);
				Notify(EResponse::Check);
			}
			if (opponentInStalemate && !opponentInCheck)
			{
				UpdateState(EGameState::Tie);
				Notify(EResponse::Tie);
			}
			else if (opponentInStalemate)
			{
				if (m_turn == EColor::BLACK)
				{
					UpdateState(EGameState::WhiteWon);
					Notify(EResponse::WhiteWon);
				}
				else
				{
					UpdateState(EGameState::BlackWon);
					Notify(EResponse::BlackWon);
				}
			}
			else if (!opponentInCheck)
				UpdateState(EGameState::Playing);

			if (m_board.IsThreeFold(m_boardConfigs, configuration))
			{
				UpdateState(EGameState::Tie);
				Notify(EResponse::Tie);
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
	m_currentState = state;
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
	return m_currentState;
}

PositionList Game::GetMoves(Position piecePos) const
{
	if (IsGameOver())
		return PositionList();
	else if (IsPaused())
		return PositionList();
	return m_board.GetMoves(piecePos, m_turn);
}

TypeList Game::GetMissingPieces(EColor color) const
{
	return color == EColor::WHITE ? m_whiteMissing : m_blackMissing;;
}


MovesList Game::GetMovesList() const
{
	return m_gameMoves;
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

bool Game::SavePGN(const std::string& path) const
{
	return m_pgn.Save(path);
}

void Game::SaveFEN(const std::string& path) const
{
	std::ofstream file(path);
	if (file.good())
	{
		file << GetFenString();
	}
}

const IGameStatus* Game::Status() const
{
	return this;
}

void Game::MakeTieRequest()
{
	UpdateState(EGameState::TieRequest);
	Notify(EResponse::TieRequest);
}

void Game::TieRequestResponse(bool answer)
{
	answer ? UpdateState(EGameState::Tie) : UpdateState(EGameState::Playing);
}

bool Game::IsTie() const
{
	return m_currentState == EGameState::Tie;
}

bool Game::BlackWon() const
{
	return m_currentState == EGameState::BlackWon;
}

bool Game::WhiteWon() const
{
	return m_currentState == EGameState::WhiteWon;
}

bool Game::IsTieRequest() const
{
	return m_currentState == EGameState::TieRequest;
}

bool Game::IsPawnEvolving() const
{
	return m_currentState == EGameState::PawnEvolving;
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
	bool opponentInStalemate = m_board.IsStalemate(m_turn);

	if (opponentInCheck)
		m_pgn.AppendToLastMove("+");
	if (opponentInStalemate && !opponentInCheck)
		UpdateState(EGameState::Tie);
	else if (m_board.IsStalemate(m_turn)) 
	{
		m_pgn.AppendToLastMove("#");
		m_turn == EColor::BLACK ? UpdateState(EGameState::WhiteWon) : UpdateState(EGameState::BlackWon);
	}
	else
		UpdateState(EGameState::Playing);

}

bool Game::IsCheck() const
{
	return m_currentState == EGameState::Check;
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
	m_currentState = EGameState::Paused;
	m_whiteMissing.clear();
	m_blackMissing.clear();
	m_boardConfigs.clear();
	m_pgn.Clear();
	m_gameMoves.clear();
	
	m_timer.Stop();

	m_blackTimer = m_timerTime;
	m_whiteTimer = m_timerTime;

	Notify(EResponse::Restart);
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

void Game::Notify(EResponse response)
{
	if (!m_bEnableNotifications)
		return;
	for (auto listener : m_listeners)
	{
		switch (response)
		{
		case EResponse::Check:
			listener.lock()->OnCheck(CheckException().what());
				break;
		case EResponse::PawnUpgrade:
			listener.lock()->OnPawnEvolve();
			break;
		case EResponse::TieRequest:
			listener.lock()->OnTieRequest();
			break;
		case EResponse::WhiteWon:
		case EResponse::BlackWon:
		case EResponse::Tie:
			listener.lock()->OnGameOver();
			break;
		case EResponse::Restart:
			listener.lock()->OnRestart();
			break;
		}
	}
}

void Game::Notify(Position start, Position end)
{
	if (!m_bEnableNotifications)
		return;
	for (auto listener : m_listeners)
		listener.lock()->OnMovePiece(start, end);
}

void Game::Notify(EType pieceType, EColor pieceColor)
{
	if (!m_bEnableNotifications)
		return;
	for (auto listener : m_listeners)
		listener.lock()->OnPieceCapture(pieceType, pieceColor);
} 

void Game::Notify(TimeSeconds whiteTimer, TimeSeconds blackTimer)
{
	if (!m_bEnableNotifications)
		return;
	for (auto listener : m_listeners)
		listener.lock()->OnTimerTick(whiteTimer, blackTimer);
}


void Game::OnSecondPass()
{
	m_turn == EColor::BLACK ? --m_blackTimer : --m_whiteTimer;
	m_roundTime++;
	Notify(m_whiteTimer, m_blackTimer);
	if (m_blackTimer == 0s)
	{
		UpdateState(EGameState::WhiteWon);
		Notify(EResponse::WhiteWon);
		m_timer.RemoveListener(this);
	}
	else if (m_whiteTimer == 0s)
	{
		UpdateState(EGameState::BlackWon);
		Notify(EResponse::BlackWon);
		m_timer.RemoveListener(this);
	}
}

