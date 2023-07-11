#include "PieceInterface.h"
#include "PositionInterface.h"
#include "Position.h"
#include <memory>
#include <iostream>
int main()
{
	std::shared_ptr<PositionInterface> ptr = std::make_shared<Position>('a', '3');
	std::cout << ptr->getColumn();
	
	return 0;

	
}