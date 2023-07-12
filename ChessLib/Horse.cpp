#include "Horse.h"

Horse::Horse()
{
	this->m_name = 'H';
}

void Horse::move(std::pair<int, int> destination, std::vector<std::shared_ptr<PieceInterface>>& pieces)
{
	
}

bool Horse::isValid(std::pair<int, int> destination)
{
	return true;
}

std::unordered_set<std::pair<int, int>> Horse::createPattern()
{
	throw std::logic_error("The method or operation is not implemented.");
}
