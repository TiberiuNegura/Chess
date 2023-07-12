#include "Piece.h"

Piece::Piece(
	char name,
	int row,
	int column,
	Color color,
	Type type
) : m_name(name), m_position({row, column}), m_color(color), m_type(type)
{
};
