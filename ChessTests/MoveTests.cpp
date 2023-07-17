#include "Board.h"
#include "IPiece.h"
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

	EXPECT_ANY_THROW(board.MoveOnBoard(blackPawn1->GetPosition(), { 2, 0 }));
	EXPECT_ANY_THROW(board.MoveOnBoard(blackPawn1->GetPosition(), { 5,0 }));

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

	//add another two white pawns in front of the black pawn
	EXPECT_NO_THROW(whitePawn3->GetPosition(), { 4,3 });
	EXPECT_NO_THROW(whitePawn4->GetPosition(), { 4,5 });
	EXPECT_ANY_THROW(blackPawn2->GetPosition(), { 4,4 });
	EXPECT_NO_THROW(blackPawn2->GetPosition(), { 4,5 });

	EXPECT_ANY_THROW(whitePawn2->GetPosition(), { 5, 4 });
}