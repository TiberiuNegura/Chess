#pragma once
#include <iostream>
#include <vector>
#include <memory>

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
		virtual void move(std::pair<int, int> destination, std::vector<std::shared_ptr<PieceInterface>>& pieces) = 0;
		virtual bool isValid(std::pair<int, int> destination) = 0;
		virtual std::vector<std::pair<int, int>> createPattern() = 0;
		
		virtual char getName() = 0;
		virtual int getColor() = 0;

		virtual ~PieceInterface() = default;

};

