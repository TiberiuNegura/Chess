#include "Piece.h"

Piece::Piece(
	char name,
	char row,
	char column,
	Color color
) : name(name), position(Position(row, column)), color(color)
{
};
