#include "Helper.h"

using IntPairHash = Helper::IntPairHash;

class ComputePositionListTests : public ::testing::Test
{
protected:
	void SetUp()
	{
		Board mat(CharBoardRepresentation{
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
	Helper helper;
};



TEST_F(ComputePositionListTests, PawnTest)
{
	PositionList positions = board.ComputePositionList({ 1,1 });
	std::unordered_set<Position, IntPairHash> expected;
	expected.insert(Position(2, 1));
	expected.insert(Position(3, 1));
	
	EXPECT_EQ(helper.ExpectedStatus(positions, expected), true);
}

TEST_F(ComputePositionListTests, QueenTest)
{
	PositionList positions = board.ComputePositionList({ 0,3 });
	std::unordered_set<Position, IntPairHash> expected;
	
	expected.insert(Position(1,3));
	expected.insert(Position(2,3));
	expected.insert(Position(3,3));
	expected.insert(Position(4,3));
	
	expected.insert(Position(0,4));
	expected.insert(Position(0,5));
	expected.insert(Position(0,2));
	expected.insert(Position(0,1));
	expected.insert(Position(0,0));

	expected.insert(Position(1,2));
	expected.insert(Position(2,1));
	expected.insert(Position(3,0));
	expected.insert(Position(1,4));
	expected.insert(Position(2,5));
	expected.insert(Position(3,6));
	expected.insert(Position(4,7));

	EXPECT_EQ(helper.ExpectedStatus(positions, expected), true);
}

TEST_F(ComputePositionListTests, BishopTest)
{
	PositionList positions = board.ComputePositionList({ 1,5 });
	std::unordered_set<Position, IntPairHash> expected;
	
	expected.insert(Position(2,4));
	expected.insert(Position(3,3));
	expected.insert(Position(4,2));
	expected.insert(Position(5,1));
	expected.insert(Position(6,0));

	expected.insert(Position(2,6));
	expected.insert(Position(3,7));
	expected.insert(Position(0,4));

	EXPECT_EQ(helper.ExpectedStatus(positions, expected), true);
}

TEST_F(ComputePositionListTests, HorseTest)
{
	PositionList positions = board.ComputePositionList({ 4,3 });
	std::unordered_set<Position, IntPairHash> expected;
	
	expected.insert(Position(2, 4));
	expected.insert(Position(2, 2));
	expected.insert(Position(6, 4));
	expected.insert(Position(6, 2));
	expected.insert(Position(3, 1));
	expected.insert(Position(5, 1));
	expected.insert(Position(3, 5));
	expected.insert(Position(5, 5));
	
	EXPECT_EQ(helper.ExpectedStatus(positions, expected), true);
}

TEST_F(ComputePositionListTests, KingTest)
{
	PositionList positions = board.ComputePositionList({ 7,4 });
	std::unordered_set<Position, IntPairHash> expected;

	expected.insert(Position(6,4));
	expected.insert(Position(6,3));
	expected.insert(Position(7,3));
	expected.insert(Position(7,5));
	expected.insert(Position(6,5));

	EXPECT_EQ(helper.ExpectedStatus(positions, expected), true);
}

TEST_F(ComputePositionListTests, RookTest)
{
	PositionList positions = board.ComputePositionList({ 7,7 });
	std::unordered_set<Position, IntPairHash> expected;

	expected.insert(Position(6, 7));
	expected.insert(Position(5, 7));
	expected.insert(Position(4, 7));
	expected.insert(Position(3, 7));
	expected.insert(Position(2, 7));
	expected.insert(Position(1, 7));
	expected.insert(Position(0, 7));
	expected.insert(Position(7, 6));
	expected.insert(Position(7, 5));

	EXPECT_EQ(helper.ExpectedStatus(positions, expected), true);
}