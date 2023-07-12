#include "Piece.h"

Piece::Piece(
	char name,
	int row,
	int column,
	Color color,
	Type type
) : m_name(name), m_position({row, column}), m_color(color), m_type(type)
{
}

char Piece::getName()
{
	return m_name;
}

Color Piece::getColor()
{
	return m_color;
}
Type Piece::getType()
{
	return m_type;
}

Position Piece::getPosition()
{
	return m_position;
};
