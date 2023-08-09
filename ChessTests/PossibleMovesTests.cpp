#include "Helper.h"

using IntPairHash = Helper::IntPairHash;

class PossibleMovesTests : public ::testing::Test
{
protected:
	void SetUp()
	{
		Board mat(CharBoardRepresentation{
		'r', ' ', ' ', ' ', ' ', 'b', 'h', 'r',
		'p', 'p', ' ', 'b', ' ', 'p', 'p', 'p',
		'h', ' ', ' ', 'p', 'p', 'k', ' ', ' ',
		' ', ' ', 'p', ' ', ' ', ' ', ' ', ' ',
		'B', ' ', 'P', 'P', 'q', ' ', ' ', ' ',
		' ', 'Q', ' ', ' ', ' ', ' ', ' ', ' ',
		'P', 'P', 'H', 'B', ' ', 'P', 'P', 'P',
		'R', ' ', ' ', ' ', 'K', ' ', 'H', 'R'
			});
		board = mat;
	}

protected:
	Board board;
	Helper helper;
};


TEST_F(PossibleMovesTests, KingTest)
{
	PositionList positions = board.GetMoves({7, 4}, EColor::WHITE);
	std::unordered_set<Position, IntPairHash> expected;

	expected.insert(Position(7, 3));
	expected.insert(Position(7, 5));

	EXPECT_EQ(helper.ExpectedStatus(positions, expected), true);
}

TEST_F(PossibleMovesTests, BishopTest)
{
	PositionList positions = board.GetMoves({ 6, 3 }, EColor::WHITE);
	std::unordered_set<Position, IntPairHash> expected;

	expected.insert(Position(5, 4 ));

	EXPECT_EQ(helper.ExpectedStatus(positions, expected), true);
}

TEST_F(PossibleMovesTests, QueenTest)
{
	PositionList positions = board.GetMoves({ 4, 4 }, EColor::BLACK);
	std::unordered_set<Position, IntPairHash> expected;

	expected.insert(Position(4, 5));
	expected.insert(Position(4, 6));
	expected.insert(Position(4, 7));

	expected.insert(Position(5, 4));
	expected.insert(Position(6, 4));
	expected.insert(Position(7, 4));

	expected.insert(Position(3, 4));

	expected.insert(Position(4, 3));

	expected.insert(Position(3, 3));
	expected.insert(Position(2, 2));

	expected.insert(Position(5, 5));
	expected.insert(Position(6, 6));

	expected.insert(Position(3, 5));
	expected.insert(Position(2, 6));

	expected.insert(Position(5, 3));
	expected.insert(Position(6, 2));

	EXPECT_EQ(helper.ExpectedStatus(positions, expected), true);
}

TEST_F(PossibleMovesTests, PawnTest)
{
	std::unordered_set<Position, IntPairHash> expected;
	board.MovePiece({ 7,4 }, { 7,5 });

	PositionList positions = board.GetMoves({ 6, 7 }, EColor::WHITE);

	expected.insert(Position(5, 7));
	expected.insert(Position(4, 7));

	EXPECT_EQ(helper.ExpectedStatus(positions, expected), true);
}

TEST_F(PossibleMovesTests, RookTest)
{
	std::unordered_set<Position, IntPairHash> expected;
	board.MovePiece({ 7,4 }, { 7,5 });

	PositionList positions = board.GetMoves({ 7, 0 }, EColor::WHITE);

	expected.insert(Position(7, 1));
	expected.insert(Position(7, 2));
	expected.insert(Position(7, 3));
	expected.insert(Position(7, 4));

	EXPECT_EQ(helper.ExpectedStatus(positions, expected), true);
}

TEST_F(PossibleMovesTests, HorseTest)
{
	std::unordered_set<Position, IntPairHash> expected;
	board.MovePiece({ 7,4 }, { 7,5 });

	PositionList positions = board.GetMoves({ 6, 2 }, EColor::WHITE);

	expected.insert(Position(7, 4));
	expected.insert(Position(5, 4));
	expected.insert(Position(5, 0));
	expected.insert(Position(4, 1));

	EXPECT_EQ(helper.ExpectedStatus(positions, expected), true);
}