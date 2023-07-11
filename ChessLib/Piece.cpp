#include "Piece.h"

void Piece::move(Position position)
{

}

bool Piece::isValid(Position position)
{
	return false;
}

std::unordered_set<Position, Position::comparator> Piece::createPattern()
{
	return std::unordered_set<Position, Position::comparator>();
}

