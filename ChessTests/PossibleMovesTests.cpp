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