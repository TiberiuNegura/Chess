#include "Piece.h"

// Constructor
Piece::Piece(
	char name,
	EColor color,
	EType type
) : m_name(name), m_color(color), m_type(type)
{ }

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

bool Piece::Is(EType type, EColor color) const
{
	return m_type == type && m_color == color;
}
