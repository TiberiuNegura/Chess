#include <unordered_set>
#include <unordered_map>
#include <fstream>

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

void Board::LoadFromFEN(std::string& fen)
{
	Reset();

	int row = 0, column = 0;
	for (auto& c : fen)
	{
		if (c == ' ') // just the first part of the string contains piece positions
			break;

		if (isdigit(c))
			column += c - '0';

		else if (c == '/')
		{
			row++;
			column = 0;
		}

		else
		{
			auto color = CharToColor(c);
			auto type = CharToType(c);

			m_board[row][column] = Piece::Produce(type, color);
			column++;
		}
	}
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

//void Board::SetBoardConfiguration(BoardConfig board)
//{
//	for (int index = 0; index < 256; index += 4)
//	{
//		int bits[4] = { index, index + 1, index + 2, index + 3 };
//
//		int color = board[bits[0]];
//		int type = board[bits[1]] + 2 * board[bits[2]] + 4 * board[bits[3]];
//
//		int row = (index / 4 / 8);
//		int column = (index / 4 % 8);
//
//		if ((EType)type == EType::EMPTY)
//			m_board[row][column] = nullptr;
//		else 
//			m_board[row][column] = Piece::Produce((EType) type, (EColor) color);
//	}
//}

void Board::SetBoardConfiguration(BoardConfig board)
{
	for (int index = 0; index < 256; index += 4)
	{
		int bits[4] = { index, index + 1, index + 2, index + 3 };

		int color = board[bits[0]];
		int type = board[bits[1]] + 2 * board[bits[2]] + 4 * board[bits[3]];

		int row = index / 32;      // Calculate the row
		int column = (index / 4) % 8; // Calculate the column

		if ((EType)type == EType::EMPTY)
			m_board[row][column] = nullptr;
		else
			m_board[row][column] = Piece::Produce((EType)type, (EColor)color);
	}
}

std::string Board::GetFenString() const
{
	std::string output;
	for (int row = 0; row < 8; row++)
	{
		int cnt = 0;
		for (int column = 0; column < 8; column++)
		{
			if (auto piece = Get(row, column))
			{
				if (cnt)
				{
					output.push_back((char)'0' + cnt);
					cnt = 0;
				}
				char pieceName = piece->GetName();
				piece->Is(EColor::BLACK) ? output.push_back(tolower(pieceName)) : output.push_back(toupper(pieceName));
			}
			else
				cnt++;

		}
		if (cnt)
			output.push_back((char) '0' + cnt);
		if (row != 7)
			output.push_back('/');
	}
	return output;
}

TypeList Board::SearchMissingPieces(EColor color) const
{
	TypeList missingPieces;
	std::unordered_map<EType, int> pieces = { {EType::PAWN, 8}, {EType::ROOK, 2}, {EType::HORSE, 2}, {EType::BISHOP, 2}, {EType::QUEEN, 1}, {EType::KING, 1} };

	for (int row = 0; row < 8; row++)
		for (int column = 0; column < 8; column++)
		{
			if (auto piece = Get(row, column))
			{
				auto it = pieces.find(piece->GetType());
				if (it != pieces.end() && piece->Is(color))
				{
					it->second--;
					if(!it->second)
						pieces.erase(it);
				}
			}
		}
	for (auto& it : pieces)
		missingPieces.insert(missingPieces.end(), it.second, it.first);

	return missingPieces;
}

std::string Board::SharedLineOrColumn(Position start, Position end) const
{
	std::string output = "";

	bool sameColumn = false;
	bool sameRow = false;
	bool sameAttackPosition = false;
	
	if (auto piece = m_board[start.first][start.second])
	{
		auto color = piece->GetColor();
		auto list = GetMoves(start, color);

		if (piece->Is(EType::PAWN))
			return output;


		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
			{
				if (m_board[i][j])
				{
					bool sameColor = (color == m_board[i][j]->GetColor());
					bool sameType = (piece->GetType() == m_board[i][j]->GetType());
					bool samePosition = (start.first == i && start.second == j);

					if (sameColor && sameType && !samePosition)
					{
						auto moves = GetMoves({ i,j }, color);

						for (const auto& move : moves)
							if (move == end)
							{
								sameAttackPosition = true;

								if (start.first == i)
									sameRow = true;
								if (start.second == j)
									sameColumn = true;
							}
					}
				}
			}
	}

	if (sameColumn && sameRow)
	{
		output += CharifyColumn(start.second);
		output += CharifyRow(start.first);
	}
	else if (sameColumn)
		output = CharifyRow(start.first);
	else if (sameRow || sameAttackPosition)
		output = CharifyColumn(start.second);

	return output;
}

char Board::CharifyRow(int row) const
{
	return ('1' + (7 - row));
}

char Board::CharifyColumn(int col) const
{
	return ('a' + col);
}

std::string Board::MatrixToChessMove(Position start, Position end, bool capture, std::string lineOrCol) const
{
	std::string move = "";
	std::string endString = "";
	std::string startString = "";

	endString += CharifyColumn(end.second);
	endString += CharifyRow(end.first);

	auto piece = m_board[end.first][end.second];
	auto enemyColor = (piece->GetColor() == EColor::BLACK) ? EColor::WHITE : EColor::BLACK;

	int castlingRow = piece->GetColor() == EColor::BLACK ? 0 : 7;

	if (start == Position(castlingRow, 4) && end == Position(castlingRow, 6))
		return "O-O";

	if (start == Position(castlingRow, 4) && end == Position(castlingRow, 2))
		return "O-O-O";

	if (!piece->Is(EType::PAWN))
		move += toupper(piece->GetName());

	if (lineOrCol != "")
		move += lineOrCol;

	if (capture)
	{
		if (piece->Is(EType::PAWN))
			move += CharifyColumn(start.second);
		move += 'x';
	}
	
	move += endString;

	if (IsCheck(enemyColor))
		move += IsStalemate(enemyColor) ? '#' : '+';
	else
		if (IsStalemate(enemyColor))
			move += '#';

	return move;
}

PiecePtr Board::operator[](Position pos)
{
	return Get(pos);
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

void Board::AddCastlingPattern(IPiecePtr piece, PositionList& positions) const
{
	int row = (piece->GetColor() == EColor::BLACK ? 0 : 7);
	bool kingMoveLeft = std::find(positions.begin(), positions.end(), Position(row, 3)) != positions.end();

	if (kingMoveLeft && IsCastlingPossible(ECastling::Left, piece->GetColor()))
		positions.emplace_back(row, 2);

	bool kingMoveRight = std::find(positions.begin(), positions.end(), Position(row, 5)) != positions.end();

	if (kingMoveRight && IsCastlingPossible(ECastling::Right, piece->GetColor()))
		positions.emplace_back(row, 6);
}

void Board::SimulateMove(BoardPtr boardClone, PositionList& positions, Position pos) const
{
	auto piece = boardClone->GetMatrix()[pos.first][pos.second];
	for (auto it = positions.begin(); it != positions.end();)
	{
		Position currentPos = *it;

		auto aux = Get(currentPos);

		boardClone->MovePiece(pos, currentPos); // simulate the move

		if (boardClone->IsCheck(piece->GetColor()))
			it = positions.erase(it);
		else
			++it;

		boardClone->MovePiece(currentPos, pos); // rollback to initial position
		boardClone->SetPosition(aux, currentPos);
	}
}

void Board::ValidateCastling(IPiecePtr piece, PositionList& positions, int row) const
{
	bool kingMoveLeft = std::find(positions.begin(), positions.end(), Position(row, 3)) != positions.end();
	auto castlingLeft = std::find(positions.begin(), positions.end(), Position(row, 2));

	if (!kingMoveLeft && castlingLeft != positions.end()) // if King can't move left, castle can't happen
		positions.erase(castlingLeft);

	bool kingMoveRight = std::find(positions.begin(), positions.end(), Position(row, 5)) != positions.end();
	auto castlingRight = std::find(positions.begin(), positions.end(), Position(row, 6));

	if (!kingMoveRight && castlingRight != positions.end()) // if King can't move right, castle can't happen
		positions.erase(castlingRight);
}

void Board::ValidatePawnMove(Position pos, PositionList& positions) const
{
	int direction = Get(pos)->Is(EColor::BLACK) ? 1 : -1;
	Position forwardOnePos(pos.first + direction, pos.second);
	Position forwardTwoPos(pos.first + 2 * direction, pos.second);

	auto forwardOneIt = std::find(positions.begin(), positions.end(), forwardOnePos);
	auto forwardTwoIt = std::find(positions.begin(), positions.end(), forwardTwoPos);

	if (forwardOneIt == positions.end() && forwardTwoIt != positions.end())
		positions.erase(forwardTwoIt);
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

	if (piece->Is(EType::KING) && !IsCheck(piece->GetColor()))
	{
		AddCastlingPattern(piece, positions);
	}

	auto king = FindKing(turn);

	SimulateMove(boardClone, positions, piecePos);
	
	// Castling validation
	int row = (piece->GetColor() == EColor::BLACK ? 0 : 7);
	if (piece->Is(EType::KING) && piecePos == Position(row, 4))
		ValidateCastling(piece, positions, row);
	
	if (piece->Is(EType::PAWN))
		ValidatePawnMove(piecePos, positions);

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
	m_moves.clear();
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

Position Board::FindStart(char name, Position end, EColor turn, Position pos) const
{
	if (IsOutOfBounds(pos) || IsOutOfBounds(end))
		throw OutOfBoundsException();

	auto piece = m_board[pos.first][pos.second];
	if (piece && piece->GetName() == name && piece->Is(turn))
	{
		auto list = GetMoves(pos, turn);
		for (const auto& move : list)
			if (move == end)
				return pos;
	}

	return { -1,-1 };
}

Position Board::FindForPGN(char name, Position end, EColor turn, char lineOrCol) const
{
	if (islower(name))
		name = 'P';
	else if (name == 'N')
		name = 'H';

	if (isdigit(lineOrCol)) // is row
	{
		int row = '8' - lineOrCol;
		for (int column = 0; column < 8; column++)
		{
			auto startPos = FindStart(name, end, turn, { row, column });
			if (startPos.IsValid())
				return startPos;
		}
	}
	else if (isalpha(lineOrCol)) // is column
	{
		int column = lineOrCol - 'a';
		for (int row = 0; row < 8; row++)
		{
			auto startPos = FindStart(name, end, turn, { row, column });
			if (startPos.IsValid())
				return startPos;
		}
	}
	else
	{
		for (int row = 0; row < 8; row++)
			for (int column = 0; column < 8; column++)
			{
				auto startPos = FindStart(name, end, turn, { row, column });
				if (startPos.IsValid())
					return startPos;
			}
	}

	return {};
}

BoardPtr Board::Clone() const
{
	return std::make_shared<Board>(m_board);
}

bool Board::IsStalemate(EColor color) const
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
