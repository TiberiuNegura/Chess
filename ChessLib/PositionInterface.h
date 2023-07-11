#pragma once

#include <tuple>

class PositionInterface
{
public:
	// Getters
	virtual char getRow() const = 0;
	virtual char getColumn() const = 0;

	// Methods
	virtual std::pair<int, int> getMatrixPos() const = 0;


	virtual ~PositionInterface() = default;
};