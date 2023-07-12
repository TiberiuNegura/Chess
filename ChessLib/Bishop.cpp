#include "Bishop.h"

Bishop::Bishop()
{
    this->m_name = 'B';
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
    throw std::logic_error("The method or operation is not implemented.");
}
