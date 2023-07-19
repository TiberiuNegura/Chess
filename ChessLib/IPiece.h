#pragma once

#include <vector>
#include <array>
#include <memory>

// Notations of STL and memory data structures
using IPiecePtr = std::shared_ptr<class IPiece>;
using Position = std::pair<int, int>;
using PositionList = std::vector<Position>;


// Color enum
enum class EColor {
	WHITE,
	BLACK,
	NONE
};


// Pieces enum
enum class EType {
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
	virtual EColor GetColor() const = 0;
	virtual EType GetType() const = 0;

	virtual bool Is(EType type, EColor color) const = 0;


	// Destructor
	virtual ~IPiece() = default;
};

