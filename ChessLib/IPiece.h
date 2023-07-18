#pragma once

#include <vector>
#include <array>
#include <memory>

// Notations of STL and memory data structures
using PiecePtr = std::shared_ptr<class InteriorIPiece>;
using Matrix = std::array<std::array<PiecePtr, 8>, 8>;
using Position = std::pair<int, int>;
using PositionList = std::vector<Position>;


// Color enum
enum class Color {
	WHITE,
	BLACK,
	NONE
};


// Pieces enum
enum class Type {
	PAWN,
	ROOK,
	BISHOP,
	HORSE,
	QUEEN,
	KING,
	EMPTY
};

class IPiece
{
public:
	// Getters
	virtual char GetName() const = 0;
	virtual Color GetColor() const = 0;
	virtual Type GetType() const = 0;
	virtual Position GetPosition() const = 0;


	// Destructor
	virtual ~IPiece() = default;
};

