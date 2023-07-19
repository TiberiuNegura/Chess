#include "Game.h"
#include "IPiece.h"
#include "OutOfBoundsException.h"
#include "IllegalMoveException.h"
#include "EmptyPositionException.h"
#include "gtest/gtest.h"

TEST(MoveTests, PawnMoveTest)
{
	//Game game;
	//Position blackPawn1 = { 1, 0 };
	//Position blackPawn2 = { 1, 4 };
	//Position blackPawn3 = { 1, 3 };
	//Position whitePawn1 = { 6, 1 };
	//Position whitePawn2 = { 6, 4 };
	//Position whitePawn3 = { 6, 3 };

	//// moving black pawns
	////moving a white pawn in order for the black pawn to capture and to block a black pawn
	//EXPECT_NO_THROW(game.MovePiece(whitePawn1, { 4, 1 }));
	//EXPECT_NO_THROW(game.MovePiece(blackPawn1, { 2, 0 }));
	//EXPECT_NO_THROW(game.MovePiece(whitePawn2, { 4, 4 }));
	//EXPECT_NO_THROW(game.MovePiece(blackPawn1, { 3, 0 }));
	//EXPECT_NO_THROW(game.MovePiece(whitePawn3, { 4, 3 }));
	//EXPECT_NO_THROW(game.MovePiece(blackPawn2, { 3, 4 }));

	//EXPECT_THROW(game.MovePiece(whitePawn1, { 6, 1 }), IllegalMoveException);
	//EXPECT_THROW(game.MovePiece(blackPawn1, { 5,0 }), IllegalMoveException);

	//EXPECT_EQ(game.GetTurn(), EColor::WHITE);

	//// test if the positions are placed properly
	//EXPECT_EQ(blackPawn1.first, 3);
	//EXPECT_EQ(blackPawn1.second, 0);

	//EXPECT_EQ(whitePawn1.first, 4);
	//EXPECT_EQ(whitePawn1.second, 1);

	////white pawn captures the black pawn
	//EXPECT_NO_THROW(game.MovePiece(whitePawn1, { 3, 0 }));
	//EXPECT_EQ(game.GetBoard()->GetElement({ 3, 0 })->GetColor(), EColor::WHITE);

	//// illegal move
	//EXPECT_THROW(game.MovePiece(blackPawn2, { 4, 4 }), IllegalMoveException);
	//EXPECT_NO_THROW(game.MovePiece(blackPawn3, { 3, 3 }));
	//EXPECT_THROW(game.MovePiece(whitePawn3, { 3, 3 }), IllegalMoveException);

	//// out of bounds
	//EXPECT_THROW(game.MovePiece(blackPawn1, { 1, 9 }), OutOfBoundsException);

	//// empty position
	//EXPECT_THROW(game.MovePiece({ 4, 7 }, { 7, 7 }), EmptyPositionException);
}

//TEST(MoveTests, RookMoveTest)
//{
//	Game game;
//	auto rook = game.GetBoard()->GetElement({ 7,7 });
//
//	// the rook can not move
//	EXPECT_THROW(game.MovePiece(rook, { 5, 7 }), IllegalMoveException);
//
//	// making room for rook to move
//	game.MovePiece({ 6, 7 }, { 4, 7 });
//
//	// move
//	EXPECT_NO_THROW(game.MovePiece(rook, { 5, 7 }));
//	EXPECT_NO_THROW(game.MovePiece(rook, { 5, 2 }));
//
//	// cannot go further than first opposite color piece
//	EXPECT_THROW(game.MovePiece(rook, { 0, 2 }), IllegalMoveException);
//
//	// the rook captures an opposite color piece
//	EXPECT_NO_THROW(game.MovePiece(rook, { 1, 2 }));
//
//	// cannot capture a piece of it`s color
//	EXPECT_THROW(game.MovePiece(rook, { 6, 2 }), IllegalMoveException);
//}
//
//TEST(MoveTests, BishopMoveTest)
//{
//	Game game;
//	auto bishop = game.GetBoard()->GetElement({ 0,2 });
//
//	// cannot move
//	EXPECT_THROW(game.MovePiece(bishop, { 2,0 }), IllegalMoveException);
//
//	// make room for bishop to move;
//	game.MovePiece({ 1, 1 }, { 2, 1 });
//	EXPECT_NO_THROW(game.MovePiece(bishop, { 2, 0 }));
//	EXPECT_NO_THROW(game.MovePiece(bishop, { 6, 4 }));
//	EXPECT_NO_THROW(game.MovePiece(bishop, { 3, 7 }));
//
//	EXPECT_THROW(game.MovePiece(bishop, { 7, 7 }), IllegalMoveException);
//	EXPECT_THROW(game.MovePiece(bishop, { 10, 20 }), OutOfBoundsException);
//	EXPECT_THROW(game.MovePiece(bishop, { 1, 5 }),IllegalMoveException);
//
//	EXPECT_EQ(bishop.first, 3);
//	EXPECT_EQ(bishop.second, 7);
//
//	EXPECT_NO_THROW(game.MovePiece(bishop, { 2, 6 }));
//	EXPECT_NO_THROW(game.MovePiece(bishop, { 6, 2 }));
//
//	EXPECT_EQ(game.GetBoard()->GetElement({ 6,2 })->GetColor(), EColor::BLACK);
//}
//
//TEST(MoveTests, HorseMoveTest)
//{
//	Game game;
//	auto horse = game.GetBoard()->GetElement({ 0,1 });
//
//	// move for capture
//	EXPECT_NO_THROW(game.MovePiece(horse, { 2, 0 }));
//	EXPECT_NO_THROW(game.MovePiece(horse, { 4, 1 }));
//	EXPECT_NO_THROW(game.MovePiece(horse, { 6, 0 })); // captures a white pawn
//
//	// get a same color pawn near the horse for the exception test
//	game.MovePiece({ 1,1 }, { 3,1 });
//	game.MovePiece({ 3,1 }, { 4,1 });
//
//	EXPECT_THROW(game.MovePiece(horse, { 4,1 }), IllegalMoveException);
//	EXPECT_THROW(game.MovePiece(horse, { -1,8 }), OutOfBoundsException);
//
//}
//
//TEST(MoveTests, KingMoveTest)
//{
//	Game game;
//	auto king = game.GetBoard()->GetElement({ 0,4 });
//
//	EXPECT_THROW(game.MovePiece(king, { 1,4 }), IllegalMoveException);// it cannot move
//	game.MovePiece({ 1,4 }, { 3, 4 }); // making room
//	EXPECT_NO_THROW(game.MovePiece(king, { 1,4 }));
//	EXPECT_NO_THROW(game.MovePiece(king, { 2,3 }));
//
//	EXPECT_THROW(game.MovePiece(king, { 5,4 }), IllegalMoveException);
//	EXPECT_EQ(king.first, 2);
//	EXPECT_EQ(king.second, 3);
//}
//
//TEST(MoveTests, QueenMoveTest)
//{
//	Game game;
//	auto queen = game.GetBoard()->GetElement({ 0,3 });
//
//	EXPECT_THROW(game.MovePiece(queen, { 5,3 }), IllegalMoveException);
//	game.MovePiece({ 1,3 }, { 3,3 });
//	EXPECT_NO_THROW(game.MovePiece(queen, { 2,3 }));
//	EXPECT_NO_THROW(game.MovePiece(queen, { 2,5 }));
//	EXPECT_THROW(game.MovePiece(queen, { 1,5 }), IllegalMoveException);
//	EXPECT_NO_THROW(game.MovePiece(queen, { 6,5 }));
//	EXPECT_NO_THROW(game.MovePiece(queen, { 4,5 }));
//	
//}