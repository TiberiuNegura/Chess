#include "Pawn.h"

void Pawn::move(Position position)
{
}

bool Pawn::isValid(Position position)
{
    return false;
}

std::unordered_set<Position, Position::comparator> Pawn::createPattern()
{
    return std::unordered_set<Position, Position::comparator>();
}
