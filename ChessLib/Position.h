#pragma once

#include<vector>

struct Position
{
	int first;
	int second;

	Position(int x = -1, int y = -1);
	Position(double x, double y)
		: first(static_cast<int>(x))
		, second(static_cast<int>(y))
	{

	}

	bool operator==(const Position& other) const;
	bool operator!=(const Position& other) const;

	bool IsValid() const;

	static const Position EMPTY;
};

using PositionList = std::vector<Position>;
using Directions = std::vector<PositionList>;