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

Pawn::Pawn()
{
}

void Pawn::move(std::pair<int, int> destination, std::vector<std::shared_ptr<PieceInterface>>& pieces)
{
}

bool Pawn::isValid(std::pair<int, int> destination)
{
    return false;
}

std::unordered_set<std::pair<int, int>> Pawn::createPattern()
{
    return std::unordered_set<std::pair<int, int>>();
}
