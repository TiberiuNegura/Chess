#include <unordered_set>

#include "Game.h"
#include "IPiece.h"
#include "Board.h"

#include "gtest/gtest.h"

class ComputePositionListTests : public ::testing::Test
{
protected:
	void SetUp()
	{
		Board mat({
		' ', ' ',' ','q',' ',' ','k',' ',
		' ', 'p',' ',' ',' ','b',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ','H',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		'R', ' ',' ',' ','K',' ',' ','R'
			});
		board = mat;
	}

protected:
	Board board;
};

struct IntPairHash {
	size_t operator()(const Position& p) const {
		// Use std::hash to get the hashes of both ints
		std::hash<int> hasher;
		size_t hash_first = hasher(p.first);
		size_t hash_second = hasher(p.second);

		// Combine the two hashes using XOR
		return hash_first ^ hash_second;
	}
};

bool ExpectedStatus(PositionList positions, std::unordered_set<Position, IntPairHash> expected)
{
	for (auto position : positions)
	{
		EXPECT_NO_THROW(expected.find(position) != expected.end());

		if (expected.find(position) != expected.end())
			expected.erase(position);

	}

	return expected.empty();
}

TEST_F(ComputePositionListTests, PawnTest)
{
	PositionList positions = board.ComputePositionList({ 1,1 }, board.Get(1, 1));
	std::unordered_set<Position, IntPairHash> expected;
	expected.insert({ 2,1 });
	expected.insert({ 3,1 });
	
	EXPECT_EQ(ExpectedStatus(positions, expected), true);
}

TEST_F(ComputePositionListTests, QueenTest)
{
	PositionList positions = board.ComputePositionList({ 0,3 }, board.Get(0, 3));
	std::unordered_set<Position, IntPairHash> expected;
	
	expected.insert({ 1,3 });
	expected.insert({ 2,3 });
	expected.insert({ 3,3 });
	
	expected.insert({ 0,4 });
	expected.insert({ 0,5 });
	expected.insert({ 0,2 });
	expected.insert({ 0,1 });
	expected.insert({ 0,0 });

	expected.insert({1,2});
	expected.insert({2,1});
	expected.insert({3,0});
	expected.insert({1,4});
	expected.insert({2,5});
	expected.insert({3,6});
	expected.insert({4,7});

	EXPECT_EQ(ExpectedStatus(positions, expected), true);
}

TEST_F(ComputePositionListTests, BishopTest)
{
	PositionList positions = board.ComputePositionList({ 1,5 }, board.Get(1, 5));
	std::unordered_set<Position, IntPairHash> expected;
	
	expected.insert({ 2,4 });
	expected.insert({ 3,3 });
	expected.insert({ 4,2 });
	expected.insert({ 5,1 });
	expected.insert({ 6,0 });

	expected.insert({ 2,6 });
	expected.insert({ 3,7 });
	expected.insert({ 0,4 });

	EXPECT_EQ(ExpectedStatus(positions, expected), true);
}

TEST_F(ComputePositionListTests, HorseTest)
{
	PositionList positions = board.ComputePositionList({ 4,3 }, board.Get(4, 3));
	std::unordered_set<Position, IntPairHash> expected;
	
	expected.insert({ 2,4 });
	expected.insert({ 2,2 });
	expected.insert({ 6,4 });
	expected.insert({ 6,2 });
	expected.insert({ 3,1 });
	expected.insert({ 5,1 });
	expected.insert({ 3,5 });
	expected.insert({ 5,5 });
	
	EXPECT_EQ(ExpectedStatus(positions, expected), true);
}

TEST_F(ComputePositionListTests, KingTest)
{
	PositionList positions = board.ComputePositionList({ 7,4 }, board.Get(7, 4));
	std::unordered_set<Position, IntPairHash> expected;

	expected.insert({ 6,4 });
	expected.insert({ 6,3 });
	expected.insert({ 7,3 });
	expected.insert({ 7,5 });
	expected.insert({ 6,5 });

	EXPECT_EQ(ExpectedStatus(positions, expected), true);
}

TEST_F(ComputePositionListTests, RookTest)
{
	PositionList positions = board.ComputePositionList({ 7,7 }, board.Get(7, 7));
	std::unordered_set<Position, IntPairHash> expected;

	expected.insert({ 6,7 });
	expected.insert({ 5,7 });
	expected.insert({ 4,7 });
	expected.insert({ 3,7 });
	expected.insert({ 2,7 });
	expected.insert({ 1,7 });
	expected.insert({ 0,7 });

	expected.insert({ 7,6 });
	expected.insert({ 7,5 });

	EXPECT_EQ(ExpectedStatus(positions, expected), true);
}