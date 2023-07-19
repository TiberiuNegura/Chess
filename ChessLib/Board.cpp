#include "Board.h"
#include "Piece.h"

#include "PieceNotFoundException.h"

Board::Board()
{
	// Board initialize

	// Pawns
	for (int column = 0; column < 8; column++) 
	{
		m_board[1][column] = Piece::Produce(EType::PAWN, EColor::BLACK);
		m_board[6][column] = Piece::Produce(EType::PAWN, EColor::WHITE);
	}

	// other pieces
	const std::vector<EType> TYPES = {EType::ROOK, EType::HORSE, EType::BISHOP, EType::QUEEN, EType::KING, EType::BISHOP, EType::HORSE, EType::ROOK };

	for (int i = 0; i < TYPES.size(); i++)
	{
		m_board[0][i] = Piece::Produce(TYPES[i], EColor::BLACK);
		m_board[7][i] = Piece::Produce(TYPES[i], EColor::WHITE);
	}
}

Board::Board(const Matrix& mat)
{
	m_board = mat;
}

const Matrix& Board::GetMatrix() const
{
	return m_board;
}

bool Board::IsEmptyPosition(Position p) const
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

PositionList Board::ComputePositionList(Position start, PiecePtr piece) const
{
	PositionList validPattern;

	Directions positions = piece->GetDirections(start);
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
			
			if (auto possiblePiece = m_board[row][column])
			{
				EColor obstacleColor = possiblePiece->GetColor();
				if (pieceType == EType::PAWN && abs(start.first - row) >= 1 && abs(start.second - column) == 0)
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
			auto piece = m_board[i][j];

			if (piece && piece->GetColor() == oppositeColor)
			{
				PositionList list = ComputePositionList({ i,j }, piece);
				for (auto position : list)
				{
					if (position == kingPos)
						return true;
				}
			}
		}

	return false;
}

PositionList Board::GetMoves(Position piecePos, EColor turn) const
{
	if (Board::IsOutOfBounds(piecePos))
		throw OutOfBoundsException();

	auto boardClone = Clone();
	auto piece = boardClone->GetMatrix()[piecePos.first][piecePos.second];

	if (!piece || piece->GetColor() != turn)
		return PositionList();


	PositionList positions = ComputePositionList(piecePos, piece);

	auto king = FindKing(turn);

	for (auto it = positions.begin(); it != positions.end();)
	{
		Position currentPos = *it;

		auto aux = Get(currentPos);
		
		boardClone->MovePiece(piecePos, currentPos); // simulate the move

		if (boardClone->IsCheck(piece->GetColor()))
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
			if (m_board[i][j] && m_board[i][j]->Is(EType::KING, color))
				return { i, j };
		}
	throw PieceNotFoundException();
}

BoardPtr Board::Clone() const
{
	return std::make_shared<Board>(m_board);
}

bool Board::IsCheckmate(EColor color) const
{
	if (!IsCheck(color))
		return false;

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			auto piece = GetMatrix()[i][j];

			if (!piece || piece->GetColor() != color)
				continue;

			PositionList list = GetMoves({ i,j }, color);
			if (!list.empty())
				return false;
		}
	return true;
}
