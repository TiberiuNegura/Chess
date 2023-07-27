#include <unordered_set>

#include "Board.h"
#include "Piece.h"

#include "PieceNotFoundException.h"

Board::Board()
{	
	Init();
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

Board::Board(CharBoardRepresentation alternateMat)
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
	return !m_board[p.first][p.second];
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

PositionList Board::ComputePositionList(Position start) const
{
	PositionList validPattern;
	PiecePtr piece = Get(start);
	Directions positions = piece->GetDirections(start);
	
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

				if (piece->Is(EType::PAWN) && abs(start.first - row) >= 1 && abs(start.second - column) == 0)
					continue; // pawn can't overtake a frontal piece

				if (!piece->Is(obstacleColor))
					validPattern.emplace_back(row, column);

				if (piece->Is({ EType::HORSE, EType::PAWN, EType::KING }))
					continue; // if horse, pawn or king, continue to next position
				else
					break; // if queen, bishop or rook, break the tile loop when adversary piece found
			}
			else
			{
				if (piece->Is(EType::PAWN) && abs(start.first - row) == 1 && abs(start.second - column) == 1)
					continue; // if pawn and diagonal path is empty, skip the 2 diagonal path considering isFirstMove
				validPattern.emplace_back(row, column);
			}
		}

	}
	return validPattern;
}

BoardConfig Board::GetBoardConfiguration() const
{
	BoardConfig config;
	for (int row = 0; row < 8; row++)
		for (int column = 0; column < 8; column++)
		{
			int index = (8 * row) + column;
			int bits[4] = { 4 * index, 4 * index + 1, 4 * index + 2, 4 * index + 3 }; // 4k, 4k+1, 4k+2, 4k+3
			if (auto piece = m_board[row][column])
			{
				int type = (int)piece->GetType();
				config[bits[0]] = (int)piece->GetColor(); // color bit
				config[bits[1]] = type % 2;               // first type bit
				config[bits[2]] = type / 2 % 2;           // second type bit
				config[bits[3]] = type / 4 % 2;           // third type bit
			}
			else
				for (int x = 0; x < 4; x++)
					config[bits[x]] = 1;                  // all bits are 1 for empty square
		}
	return config;
}

void Board::MovePiece(Position start, Position end)
{
	m_board[end.first][end.second] = m_board[start.first][start.second];
	m_board[start.first][start.second] = {};
}

bool Board::IsCastlingPossible(ECastling option, EColor color) const
{
	int row = (color == EColor::BLACK ? 0 : 7);
	auto leftRook = Get(row, 0);
	auto rightRook = Get(row, 7);
	auto king = Get(row, 4);
	
	if (!king || !king->Is(EType::KING, color))
		return false;

	if (option != ECastling::Left && option != ECastling::Right) 
		return false;

	if (king->HasMoved())
		return false;

	if (option == ECastling::Left && leftRook && leftRook->Is(EType::ROOK, color))
	{
		if (leftRook->HasMoved())
			return false;

		for (int i = 3; i > 0; i--)
			if (!IsEmptyPosition({ row,i }))
				return false;

		return true;
	}
	else if (option == ECastling::Right && rightRook && rightRook->Is(EType::ROOK, color))
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

	for (int row = 0; row < 8; row++)
		for (int column = 0; column < 8; column++)
		{
			auto piece = m_board[row][column];

			if (piece && piece->Is(oppositeColor))
			{
				PositionList list = ComputePositionList({ row,column });
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

	if (!piece || !piece->Is(turn))
		return PositionList();


	PositionList positions = ComputePositionList(piecePos);


	// Castling pattern without validation
	if (piece->Is(EType::KING) && !IsCheck(piece->GetColor()))
	{
		int row = (piece->GetColor() == EColor::BLACK ? 0 : 7);
		bool kingMoveLeft = std::find(positions.begin(), positions.end(), std::make_pair(row, 3)) != positions.end();

		if (kingMoveLeft && IsCastlingPossible(ECastling::Left, piece->GetColor()))
			positions.emplace_back(row, 2);

		bool kingMoveRight = std::find(positions.begin(), positions.end(), std::make_pair(row, 5 )) != positions.end();

		if (kingMoveRight && IsCastlingPossible(ECastling::Right, piece->GetColor()))
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
	if (piece->Is(EType::KING))
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

void Board::Init()
{
	// Pawns
	for (int column = 0; column < 8; column++)
	{
		m_board[1][column] = Piece::Produce(EType::PAWN, EColor::BLACK);
		m_board[6][column] = Piece::Produce(EType::PAWN, EColor::WHITE);
	}

	// other pieces
	const std::vector<EType> TYPES = { EType::ROOK, EType::HORSE, EType::BISHOP, EType::QUEEN, EType::KING, EType::BISHOP, EType::HORSE, EType::ROOK };

	for (int i = 0; i < TYPES.size(); i++)
	{
		m_board[0][i] = Piece::Produce(TYPES[i], EColor::BLACK);
		m_board[7][i] = Piece::Produce(TYPES[i], EColor::WHITE);
	}
}

void Board::Reset()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			m_board[i][j].reset();
}

Position Board::FindKing(EColor color) const
{
	for (int row = 0; row < 8; row++)
		for (int column = 0; column < 8; column++)
			if (Get(row, column) && Get(row, column)->Is(EType::KING, color))
				return { row, column };
	throw PieceNotFoundException();
}

BoardPtr Board::Clone() const
{
	return std::make_shared<Board>(m_board);
}

bool Board::IsCheckmate(EColor color) const
{
	for (int row = 0; row < 8; row++)
		for (int column = 0; column < 8; column++)
		{
			auto piece = GetMatrix()[row][column];

			if (!piece || piece->GetColor() != color)
				continue;

			PositionList list = GetMoves({ row,column }, color);
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
			if (m_board[i][j] && m_board[i][j]->Is(oppositeColor))
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
	return (piece->Is(EType::PAWN) && pos.first == row);
}

bool Board::IsThreeFold(BoardConfigList boardConfigs, BoardConfig config) const
{
	return (std::count(boardConfigs.begin(), boardConfigs.end(), config) >= 3);
}

Position Board::FindEvolvingPawn(EColor color)
{
	int row = color == EColor::WHITE ? 0 : 7;
	for (int column = 0; column < 8; column++)
	{
		auto piece = Get(row, column);
		if (piece && piece->Is(EType::PAWN))
			return {row, column};
	}
	throw PieceNotFoundException();
}
