#include <unordered_set>

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

EColor Board::CharToColor(char c) const
{
	return (islower(c) ? EColor::BLACK : EColor::WHITE);
}

EType Board::CharToType(char c) const
{
	switch (tolower(c))
	{
	case 'r':
		return EType::ROOK;
	case 'h':
		return EType::HORSE;
	case 'b':
		return EType::BISHOP;
	case 'q':
		return EType::QUEEN;
	case 'k':
		return EType::KING;
	case 'p':
		return EType::PAWN;
	default:
		return EType::EMPTY;
	}
}

Board::Board(std::array<std::array<char, 8>, 8> alternateMat)
{
	// UPPERCASE - WHITE, lowercase - black
	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 8; column++)
		{
			if (alternateMat[row][column] == ' ') 
				continue;

			auto color = CharToColor(alternateMat[row][column]);
			auto type = CharToType(alternateMat[row][column]);

			m_board[row][column] = Piece::Produce(type, color);
		}
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

void Board::Set(Position pos, PiecePtr newPiece) 
{
	m_board[pos.first][pos.second] = newPiece;
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

std::bitset<256> Board::GetBoardConfiguration() const
{
	std::bitset<256> config;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			int k = (8 * i) + j;
			if (auto piece = m_board[i][j])
			{

				int type = (int)piece->GetType();
				config[4 * k] = (int)piece->GetColor();
				config[4 * k + 1] = type % 2;
				config[4 * k + 2] = type / 2 % 2;
				config[4 * k + 3] = type / 4 % 2;
			}
			else
				for (int x = 0; x < 4; x++)
					config[4 * k + x] = 1;
		}
	return config;
}

void Board::MovePiece(Position start, Position end)
{
	m_board[end.first][end.second] = m_board[start.first][start.second];
	m_board[start.first][start.second] = {};
}

bool Board::IsCastlingPossible(std::string where, EColor color) const
{
	int row = (color == EColor::BLACK ? 0 : 7);
	auto leftRook = Get(row, 0);
	auto rightRook = Get(row, 7);
	auto king = Get(row, 4);
	
	if (!king || !king->Is(EType::KING, color))
		return false;

	if (where != "left" && where != "right") 
		return false;

	if (king->HasMoved())
		return false;

	if (where == "left" && leftRook && leftRook->Is(EType::ROOK, color))
	{
		if (leftRook->HasMoved())
			return false;

		for (int i = 3; i > 0; i--)
			if (!IsEmptyPosition({ row,i }))
				return false;

		return true;
	}
	else if (where == "right" && rightRook && rightRook->Is(EType::ROOK, color))
	{
		if (rightRook->HasMoved())
			return false;

		for (int i = 5; i < 7; i++)
			if (!IsEmptyPosition({ row,i }))
				return false;

		return true;
	}

	return false;
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
	EColor oppositeColor = (color == EColor::BLACK ? EColor::WHITE : EColor::BLACK);

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
	if (IsOutOfBounds(piecePos))
		throw OutOfBoundsException();

	auto boardClone = Clone();
	auto piece = boardClone->GetMatrix()[piecePos.first][piecePos.second];

	if (!piece || piece->GetColor() != turn)
		return PositionList();


	PositionList positions = ComputePositionList(piecePos, piece);


	// Castling pattern without validation
	if (piece->GetType() == EType::KING && !IsCheck(piece->GetColor()))
	{
		int row = (piece->GetColor() == EColor::BLACK ? 0 : 7);
		bool kingMoveLeft = std::find(positions.begin(), positions.end(), std::make_pair(row, 3)) != positions.end();

		if (kingMoveLeft && IsCastlingPossible("left", piece->GetColor()))
			positions.emplace_back(row, 2);

		bool kingMoveRight = std::find(positions.begin(), positions.end(), std::make_pair(row, 5 )) != positions.end();

		if (kingMoveRight && IsCastlingPossible("right", piece->GetColor()))
			positions.emplace_back(row, 6);
	}

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
	
	// Castling validation
	if (piece->GetType() == EType::KING)
	{
		int row = (piece->GetColor() == EColor::BLACK ? 0 : 7);
		bool kingMoveLeft = std::find(positions.begin(), positions.end(), std::make_pair(row, 3)) != positions.end();
		auto castlingLeft = std::find(positions.begin(), positions.end(), std::make_pair(row, 2));

		if (!kingMoveLeft && castlingLeft != positions.end()) // if King can't move left, castle can't happen
			positions.erase(castlingLeft);

		bool kingMoveRight = std::find(positions.begin(), positions.end(), std::make_pair(row, 5 )) != positions.end();
		auto castlingRight = std::find(positions.begin(), positions.end(), std::make_pair(row, 6));

		if (!kingMoveRight && castlingRight != positions.end()) // if King can't move right, castle can't happen
			positions.erase(castlingRight);

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

bool Board::CanBeCaptured(Position pos, EColor color) const
{
	EColor oppositeColor = (color == EColor::BLACK ? EColor::WHITE : EColor::BLACK);
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (m_board[i][j] && m_board[i][j]->GetColor() == oppositeColor)
			{
				auto moves = GetMoves({ i,j }, oppositeColor);
				for (auto move : moves)
					if (move == pos)
						return true;
			}
	return false;
}

bool Board::CanPawnEvolve(Position pos) const
{
	auto piece = Get(pos);
	int row = (piece->GetColor() == EColor::BLACK ? 7 : 0);
	return (piece->GetType() == EType::PAWN && pos.first == row);
}

bool Board::IsThreeFold(std::vector<std::bitset<256>> boardConfigs, std::bitset<256> config) const
{
	return (std::count(boardConfigs.begin(), boardConfigs.end(), config) >= 3);
}

Position Board::FindEvolvingPawn(EColor color)
{
	int row = color == EColor::WHITE ? 0 : 7;
	for (int column = 0; column < 8; column++)
	{
		auto piece = Get(row, column);
		if (piece && piece->GetType() == EType::PAWN)
			return {row, column};
	}
	throw PieceNotFoundException();
}
