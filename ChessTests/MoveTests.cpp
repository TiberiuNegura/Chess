#include "Board.h"
#include "IPiece.h"
#include "OutOfBoundsException.h"
#include "IllegalMoveException.h"
#include "EmptyPositionException.h"
#include "gtest/gtest.h"

TEST(MoveTests, PawnMoveTest)
{
	Board board;
	auto blackPawn1 = board.GetGameBoard()[1][0];
	auto blackPawn2 = board.GetGameBoard()[1][4];
	auto whitePawn1 = board.GetGameBoard()[6][1];
	auto whitePawn2 = board.GetGameBoard()[6][4];
	auto whitePawn3 = board.GetGameBoard()[6][3];
	auto whitePawn4 = board.GetGameBoard()[6][5];

	// moving black pawns
	EXPECT_NO_THROW(board.MoveOnBoard(blackPawn1->GetPosition(), { 2, 0 }));
	EXPECT_NO_THROW(board.MoveOnBoard(blackPawn1->GetPosition(), { 3, 0 }));
	EXPECT_NO_THROW(board.MoveOnBoard(blackPawn2->GetPosition(), { 3, 4 }));

	EXPECT_THROW(board.MoveOnBoard(blackPawn1->GetPosition(), { 2, 0 }), IllegalMoveException);
	EXPECT_THROW(board.MoveOnBoard(blackPawn1->GetPosition(), { 5,0 }), IllegalMoveException);

	// test if the positions are placed properly
	EXPECT_EQ(blackPawn1->GetPosition().first, 3);
	EXPECT_EQ(blackPawn1->GetPosition().second, 0);

	EXPECT_EQ(blackPawn2->GetPosition().first, 3);
	EXPECT_EQ(blackPawn2->GetPosition().second, 4);

	//moving a white pawn in order for the black pawn to capture and to block a black pawn
	board.MoveOnBoard(whitePawn1->GetPosition(), { 4, 1 });
	board.MoveOnBoard(whitePawn2->GetPosition(), { 4, 4 });

	//black pawn captures the white pawn
	EXPECT_NO_THROW(board.MoveOnBoard(blackPawn1->GetPosition(), { 4, 1 }));
	EXPECT_EQ(board.GetGameBoard()[4][1]->GetColor(), Color::BLACK);

	// illegal move
	EXPECT_NO_THROW(board.MoveOnBoard(whitePawn3->GetPosition(), { 4,3 }));
	EXPECT_NO_THROW(board.MoveOnBoard(whitePawn4->GetPosition(), { 4,5 }));
	EXPECT_THROW(board.MoveOnBoard(blackPawn2->GetPosition(), { 4,4 }), IllegalMoveException);
	EXPECT_NO_THROW(board.MoveOnBoard(blackPawn2->GetPosition(), { 4,5 }));

	// out of bounds
	EXPECT_THROW(board.MoveOnBoard(whitePawn2->GetPosition(), { 1, 9 }), OutOfBoundsException);

	// empty position
	EXPECT_THROW(board.MoveOnBoard({ 4, 7 }, { 7, 7 }), EmptyPositionException);
}

TEST(MoveTests, RookMoveTest)
{
	Board board;
	auto rook = board.GetGameBoard()[7][7];

	// the rook can not move
	EXPECT_THROW(board.MoveOnBoard(rook->GetPosition(), { 5, 7 }), IllegalMoveException);

	// making room for rook to move
	board.MoveOnBoard({ 6, 7 }, { 4, 7 });

	// move
	EXPECT_NO_THROW(board.MoveOnBoard(rook->GetPosition(), { 5, 7 }));
	EXPECT_NO_THROW(board.MoveOnBoard(rook->GetPosition(), { 5, 2 }));

	// cannot go further than first opposite color piece
	EXPECT_THROW(board.MoveOnBoard(rook->GetPosition(), { 0, 2 }), IllegalMoveException);

	// the rook captures an opposite color piece
	EXPECT_NO_THROW(board.MoveOnBoard(rook->GetPosition(), { 1, 2 }));

	// cannot capture a piece of it`s color
	EXPECT_THROW(board.MoveOnBoard(rook->GetPosition(), { 6, 2 }), IllegalMoveException);
}

TEST(MoveTests, BishopMoveTest)
{
	Board board;
	auto bishop = board.GetGameBoard()[0][2];

	// cannot move
	EXPECT_THROW(board.MoveOnBoard(bishop->GetPosition(), { 2,0 }), IllegalMoveException);

	// make room for bishop to move;
	board.MoveOnBoard({ 1, 1 }, { 2, 1 });
	EXPECT_NO_THROW(board.MoveOnBoard(bishop->GetPosition(), { 2, 0 }));
	EXPECT_NO_THROW(board.MoveOnBoard(bishop->GetPosition(), { 6, 4 }));
	EXPECT_NO_THROW(board.MoveOnBoard(bishop->GetPosition(), { 3, 7 }));

	EXPECT_THROW(board.MoveOnBoard(bishop->GetPosition(), { 7, 7 }), IllegalMoveException);
	EXPECT_THROW(board.MoveOnBoard(bishop->GetPosition(), { 10, 20 }), OutOfBoundsException);
	EXPECT_THROW(board.MoveOnBoard(bishop->GetPosition(), { 1, 5 }),IllegalMoveException);

	EXPECT_EQ(bishop->GetPosition().first, 3);
	EXPECT_EQ(bishop->GetPosition().second, 7);

	EXPECT_NO_THROW(board.MoveOnBoard(bishop->GetPosition(), { 2, 6 }));
	EXPECT_NO_THROW(board.MoveOnBoard(bishop->GetPosition(), { 6, 2 }));

	EXPECT_EQ(board.GetGameBoard()[6][2]->GetColor(), Color::BLACK);
}

TEST(MoveTests, HorseMoveTest)
{
	Board board;
	auto horse = board.GetGameBoard()[0][1];

	// move for capture
	EXPECT_NO_THROW(board.MoveOnBoard(horse->GetPosition(), { 2, 0 }));
	EXPECT_NO_THROW(board.MoveOnBoard(horse->GetPosition(), { 4, 1 }));
	EXPECT_NO_THROW(board.MoveOnBoard(horse->GetPosition(), { 6, 0 })); // captures a white pawn

	// get a same color pawn near the horse for the exception test
	board.MoveOnBoard({ 1,1 }, { 3,1 });
	board.MoveOnBoard({ 3,1 }, { 4,1 });

	EXPECT_THROW(board.MoveOnBoard(horse->GetPosition(), { 4,1 }), IllegalMoveException);
	EXPECT_THROW(board.MoveOnBoard(horse->GetPosition(), { -1,8 }), OutOfBoundsException);

}

TEST(MoveTests, KingMoveTest)
{

}

TEST(MoveTests, QueenMoveTest)
{

}