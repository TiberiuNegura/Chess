#include "Board.h"
#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "Horse.h"
#include "Queen.h"
#include "King.h"
#include "Piece.h"

#include "PieceNotFoundException.h"


Board::Board()
{
	// Board initialize

	// Pawns
	for (int column = 0; column < 8; column++) {
		m_board[1][column] = std::make_shared<Pawn>(EColor::BLACK);
		m_board[6][column] = std::make_shared<Pawn>(EColor::WHITE);
	}

	// Rooks
	m_board[0][0] = std::make_shared<Rook>(EColor::BLACK);
	m_board[0][7] = std::make_shared<Rook>(EColor::BLACK);
	m_board[7][0] = std::make_shared<Rook>(EColor::WHITE);
	m_board[7][7] = std::make_shared<Rook>(EColor::WHITE);

	// Horses
	m_board[0][1] = std::make_shared<Horse>(EColor::BLACK);
	m_board[0][6] = std::make_shared<Horse>(EColor::BLACK);
	m_board[7][1] = std::make_shared<Horse>(EColor::WHITE);
	m_board[7][6] = std::make_shared<Horse>(EColor::WHITE);

	// Bishops
	m_board[0][2] = std::make_shared<Bishop>(EColor::BLACK);
	m_board[0][5] = std::make_shared<Bishop>(EColor::BLACK);
	m_board[7][2] = std::make_shared<Bishop>(EColor::WHITE);
	m_board[7][5] = std::make_shared<Bishop>(EColor::WHITE);

	// Queens
	m_board[0][3] = std::make_shared<Queen>(EColor::BLACK);
	m_board[7][3] = std::make_shared<Queen>(EColor::WHITE);

	// Kings
	m_board[0][4] = std::make_shared<King>(EColor::BLACK);
	m_board[7][4] = std::make_shared<King>(EColor::WHITE);

}

Board::Board(const Matrix& mat)
{
	m_board = mat;
}

const Matrix& Board::GetGameBoard() const
{
	return m_board;
}

bool Board::IsEmpty(Position p) const
{
	if (!m_board[p.first][p.second])
		return true;
	return false;
}

PiecePtr Board::Get(int i, int j) const
{
	return m_board[i][j];
}

PiecePtr Board::Get(Position pos) const
{
	return Get(pos.first, pos.second);
}

PositionList Board::ComputePositionList(Position start, std::vector<PositionList> positions) const
{
	PositionList validPattern;
	EColor pieceColor = m_board[start.first][start.second]->GetColor();
	EType pieceType = m_board[start.first][start.second]->GetType();
	for (int direction = 0; direction < positions.size(); direction++)
	{
		for (int tile = 0; tile < positions[direction].size(); tile++)
		{
			int row = positions[direction][tile].first;
			int column = positions[direction][tile].second;

			if (IsOutOfBounds(positions[direction][tile]))
				continue;
			
			if (auto possiblePosition = m_board[row][column])
			{
				EColor obstacleColor = possiblePosition->GetColor();
				if (pieceType == EType::PAWN && abs(start.first - row) == 1 && abs(start.second - column) == 0)
					continue; // pawn can't overtake a frontal piece
				if (obstacleColor != pieceColor)
					validPattern.emplace_back(row, column);
				if (pieceType == EType::HORSE || pieceType == EType::PAWN || pieceType == EType::KING)
					continue; // if horse, pawn or king, continue to next position
				else
					break; // if queen, bishop or rook, break the tile loop when adversary piece found
			}
			else
			{
				if (pieceType == EType::PAWN && abs(start.first - row) == 1 && abs(start.second - column) == 1)
					continue; // if pawn and diagonal path is empty, skip the 2 diagonal path considering isFirstMove
				validPattern.emplace_back(row, column);
			}
		}
	}
	return validPattern;
}


void Board::MovePiece(Position start, Position end)
{
	m_board[end.first][end.second] = m_board[start.first][start.second];
	m_board[start.first][start.second] = {};
}

void Board::SetPosition(PiecePtr toRevert, Position pos)
{
	if (toRevert)
		m_board[pos.first][pos.second] = toRevert;
}


bool Board::IsOutOfBounds(Position p)
{
	return !(0 <= p.first && p.first < 8 && 0 <= p.second && p.second < 8);
}

bool Board::IsCheck(EColor color) const
{
	EColor oppositeColor = color == EColor::BLACK ? EColor::WHITE : EColor::BLACK;

	auto kingPos = FindKing(color);

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (auto piece = m_board[i][j])
			{
				if (piece->GetColor() == oppositeColor)
				{
					PositionList list = ComputePositionList({ i,j }, piece->GetDirections({ i, j }));
					for (auto position : list)
					{
						if (position == kingPos)
							return true;
					}
				}
			}
		}

	return false;
}

PositionList Board::GetMoves(Position piecePos, EColor turn) const
{
	if (Board::IsOutOfBounds(piecePos))
		throw OutOfBoundsException();

	auto piece = m_board[piecePos.first][piecePos.second];

	if (!piece || piece->GetColor() != turn)
		return PositionList();


	PositionList positions = ComputePositionList(piecePos, piece->GetDirections(piecePos));

	auto king = FindKing(turn);

	auto boardClone = Clone();

	//auto boardClone = std::make_shared<Matrix>(m_board);

	for (auto it = positions.begin(); it != positions.end();)
	{
		Position currentPos = *it;

		auto aux = Get(currentPos);
		

		boardClone->MovePiece(piecePos, currentPos); // simulate the move

		if (IsCheck(piece->GetColor()))
			it = positions.erase(it);
		else
			++it;

		boardClone->MovePiece(currentPos, piecePos); // rollback to initial position
		boardClone->SetPosition(aux, currentPos);
	}

	return positions;
}

Position Board::FindKing(EColor color) const
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (auto currentPiece = m_board[i][j])
			{
				if (currentPiece->Is(EType::KING, color))
					return { i, j };
			}
		}
	throw PieceNotFoundException();
}

std::shared_ptr<Board> Board::Clone() const
{
	return std::make_shared<Board>(m_board);
}

PiecePtr Board::operator[](Position pos) const
{
	return m_board[pos.first][pos.second];
}
