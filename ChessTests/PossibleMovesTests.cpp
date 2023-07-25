#include <unordered_set>

#include "Game.h"
#include "IPiece.h"
#include "Board.h"

#include "gtest/gtest.h"

class PossibleMovesTests : public ::testing::Test
{
protected:
	void SetUp()
	{
		Board mat({
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
};

TEST_F(PossibleMovesTests, KingTest)
{

}