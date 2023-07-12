#include "Bishop.h"

Bishop::Bishop()
{
}

void Bishop::move(std::pair<int, int> destination, std::vector<std::shared_ptr<PieceInterface>>& pieces)
{
}

bool Bishop::isValid(std::pair<int, int> destination)
{
    return false;
}

std::unordered_set<std::pair<int, int>> Bishop::createPattern()
{
    return std::unordered_set<std::pair<int, int>>();
}
