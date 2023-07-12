#include "Queen.h"

void Queen::move(std::pair<int, int> destination, std::vector<std::shared_ptr<PieceInterface>>& pieces)
{
}

bool Queen::isValid(std::pair<int, int> destination)
{
    return false;
}

std::unordered_set<std::pair<int, int>> Queen::createPattern()
{
    return std::unordered_set<std::pair<int, int>>();
}
