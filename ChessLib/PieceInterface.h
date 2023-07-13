#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <memory>

using PiecePtr = std::shared_ptr<class PieceInterface>;
using Matrix = std::array<std::array<PiecePtr, 8>, 8>;
using Position = std::pair<int, int>;
using PositionList = std::vector<Position>;


enum class Color {
	WHITE,
	BLACK,
	NONE
};

enum class Type {
	PAWN,
	ROOK,
	BISHOP,
	HORSE,
	QUEEN,
	KING,
	EMPTY
};

class PieceInterface
{
	public:
		virtual void move(Position destination, Matrix& board) = 0;
		virtual bool isValid(Position destination, const Matrix& board) = 0;
		virtual PositionList createPattern(const Matrix& board) = 0;
		
		virtual char getName() = 0;
		virtual Color getColor() = 0;
		virtual Type getType() = 0; 
		virtual Position getPosition() = 0;

		virtual ~PieceInterface() = default;

};

