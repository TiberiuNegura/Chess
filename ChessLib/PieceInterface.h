#pragma once
#include <iostream>
#include <vector>
#include <memory>

using PiecePtr = std::shared_ptr<class PieceInterface>;


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
		virtual void move(std::pair<int, int> destination,std::array<std::array<PiecePtr, 8>, 8>& board) = 0;
		virtual bool isValid(std::pair<int, int> destination, const std::array<std::array<PiecePtr, 8>, 8>& board) = 0;
		virtual std::vector<std::pair<int, int>> createPattern(const std::array<std::array<PiecePtr, 8>, 8>& board) = 0;
		
		virtual char getName() = 0;
		virtual int getColor() = 0;

		virtual ~PieceInterface() = default;

};

