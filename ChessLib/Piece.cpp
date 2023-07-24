#include "Piece.h"

#include "Rook.h"
#include "Bishop.h"
#include "Horse.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"

// Constructor
Piece::Piece(
	char name,
	EColor color,
	EType type
) : m_name(name), m_color(color), m_type(type), hasMoved(false)
{

}

PiecePtr Piece::Produce(EType type, EColor color)
{
	switch (type)
	{
	case EType::PAWN:
		return std::make_shared<Pawn>(color);
	case EType::ROOK:
		return std::make_shared<Rook>(color);
	case EType::BISHOP:
		return std::make_shared<Bishop>(color);
	case EType::HORSE:
		return std::make_shared<Horse>(color);
	case EType::QUEEN:
		return std::make_shared<Queen>(color);
	case EType::KING:
		return std::make_shared<King>(color);
	}

	return {};
}

// Getters
char Piece::GetName() const
{
	return m_name;
}

EColor Piece::GetColor() const
{
	return m_color;
}
EType Piece::GetType() const
{
	return m_type;
}

bool Piece::HasMoved() const
{
	return hasMoved;
}

void Piece::SetHasMoved()
{
	hasMoved = true;
}

bool Piece::Is(EType type, EColor color) const
{
	return m_type == type && m_color == color;
}
