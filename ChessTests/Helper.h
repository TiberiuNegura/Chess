#pragma once

#include "IPiece.h"

#include <unordered_set>

#include "Game.h"
#include "Board.h"

#include "gtest/gtest.h"

class Helper
{
public:

	struct IntPairHash {
		size_t operator()(const Position& p) const;
	};
	bool ExpectedStatus(PositionList positions, std::unordered_set<Position, IntPairHash> expected);
};

