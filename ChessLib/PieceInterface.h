#pragma once
#include "Position.h"
#include <unordered_set>

class PieceInterface
{
public:
	virtual void move(Position position) = 0;
	virtual bool isValid(Position position) = 0;
	//virtual std::unordered_set<Position> createPattern() = 0;

	virtual ~PieceInterface() = default;
};

