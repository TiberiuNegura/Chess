#include "Piece.h"

// Constructor
Piece::Piece(
	char name,
	int row,
	int column,
	Color color,
	Type type
) : m_name(name), m_position({row, column}), m_color(color), m_type(type)
{ }

// Getters
char Piece::GetName() const
{
	return m_name;
}

Color Piece::GetColor() const
{
	return m_color;
}
Type Piece::GetType() const
{
	return m_type;
}

Position Piece::GetPosition() const
{
	return m_position;
}

// Setters
void Piece::SetPosition(Position position)
{
	m_position = position;
}
