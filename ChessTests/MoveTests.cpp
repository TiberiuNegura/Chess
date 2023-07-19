#include "Game.h"
#include "IPiece.h"
#include "OutOfBoundsException.h"
#include "IllegalMoveException.h"
#include "EmptyPositionException.h"
#include "gtest/gtest.h"

TEST(MoveTests, PawnMoveTest)
{
	Game game;
	Position blackPawn1 = { 1, 0 };
	Position blackPawn2 = { 1, 4 };
	Position blackPawn3 = { 1, 3 };
	Position whitePawn1 = { 6, 1 };
	Position whitePawn2 = { 6, 4 };
	Position whitePawn3 = { 6, 3 };

	// moving black pawns
	//moving a white pawn in order for the black pawn to capture and to block a black pawn
	EXPECT_NO_THROW(game.MovePiece(whitePawn1, { 4, 1 }));
	EXPECT_NO_THROW(game.MovePiece(blackPawn1, { 2, 0 }));
	EXPECT_NO_THROW(game.MovePiece(whitePawn2, { 4, 4 }));
	EXPECT_NO_THROW(game.MovePiece({ 2, 0 }, { 3, 0 }));
	EXPECT_NO_THROW(game.MovePiece(whitePawn3, { 4, 3 }));
	EXPECT_NO_THROW(game.MovePiece({ 1, 4 }, { 3, 4 }));

	EXPECT_THROW(game.MovePiece({ 4, 1 }, { 6, 1 }), IllegalMoveException);
	EXPECT_THROW(game.MovePiece({ 3, 0 }, { 5,0 }), IllegalMoveException);

	EXPECT_EQ(game.GetTurn(), EColor::WHITE);

	// test if the positions are placed properly
	EXPECT_EQ(game.GetBoard()->GetElement({ 3,0 })->GetColor(), EColor::BLACK);
	EXPECT_EQ(game.GetBoard()->GetElement({ 4,1 })->GetColor(), EColor::WHITE);

	//white pawn captures the black pawn
	EXPECT_NO_THROW(game.MovePiece({ 4,1 }, { 3, 0 }));
	EXPECT_EQ(game.GetBoard()->GetElement({ 3, 0 })->GetColor(), EColor::WHITE);

	// illegal move
	EXPECT_THROW(game.MovePiece({ 3,4 }, { 4, 4 }), IllegalMoveException);
	EXPECT_NO_THROW(game.MovePiece(blackPawn3, { 3, 3 }));
	EXPECT_THROW(game.MovePiece({ 4,3 }, { 3, 3 }), IllegalMoveException);

	// out of bounds
	EXPECT_THROW(game.MovePiece({ 4,3 }, { 1, 9 }), OutOfBoundsException);

	// empty position
	EXPECT_THROW(game.MovePiece({ 4, 7 }, { 7, 7 }), EmptyPositionException);
}

TEST(MoveTests, RookMoveTest)
{
	Game game;
	Position rook = { 7,7 };

	// the rook can not move
	EXPECT_THROW(game.MovePiece(rook, { 5, 7 }), IllegalMoveException);

	// making room for rook to move
	game.MovePiece({ 6, 7 }, { 4, 7 });
	game.MovePiece({ 1, 7 }, { 2, 7 });

	// move
	EXPECT_NO_THROW(game.MovePiece(rook, { 5, 7 }));

	game.MovePiece({ 2, 7 }, { 3, 7 });

	EXPECT_NO_THROW(game.MovePiece({ 5,7 }, { 5, 2 }));

	game.MovePiece({ 1, 2 }, { 2, 2 });

	// cannot go further than first opposite color piece
	EXPECT_THROW(game.MovePiece({ 5,2 }, { 0, 2 }), IllegalMoveException);

	EXPECT_EQ(game.GetBoard()->GetElement({2, 2})->GetType(), EType::PAWN);

	// the rook captures an opposite color piece
	EXPECT_NO_THROW(game.MovePiece({ 5,2 }, { 2, 2 }));
	game.MovePiece({ 1, 5 }, { 2, 5 });

	// cannot capture a piece of it`s color
	EXPECT_THROW(game.MovePiece({ 2,2 }, { 6, 2 }), IllegalMoveException);
}

TEST(MoveTests, BishopMoveTest)
{
	Game game;
	Position blackBishop = { 0,2 };
	Position whiteBishop = { 7,5 };

	// cannot move
	EXPECT_THROW(game.MovePiece(whiteBishop, { 5,7 }), IllegalMoveException);

	// make room for bishop to move;
	game.MovePiece({ 6, 6 }, { 4, 6 });
	game.MovePiece({ 1, 1 }, { 3, 1 });

	EXPECT_NO_THROW(game.MovePiece(whiteBishop, { 5, 7 }));
	EXPECT_NO_THROW(game.MovePiece(blackBishop, { 2, 0 }));
	EXPECT_THROW(game.MovePiece({ 5,7 }, { 3,5 }), IllegalMoveException);

	game.MovePiece({ 4,6 }, { 3,6 });
	game.MovePiece({ 3,1 }, { 4,1 });
	
	EXPECT_NO_THROW(game.MovePiece({ 5,7 }, { 1,3 }));
	game.MovePiece({ 0,3 }, { 1,3 });
	game.MovePiece({ 6,7 }, { 5,7 });
	EXPECT_NO_THROW(game.MovePiece({ 2,0 }, { 6,4 }));
	EXPECT_THROW(game.MovePiece({ 1,2 }, { 10, 20 }), OutOfBoundsException);

	EXPECT_EQ(game.GetBoard()->GetElement({ 6,4 })->GetColor(), EColor::BLACK);
	EXPECT_EQ(game.GetBoard()->GetElement({ 6,4 })->GetType(), EType::BISHOP);

	game.MovePiece({ 5,7 }, { 4,7 });
	EXPECT_NO_THROW(game.MovePiece({ 6,4 }, { 4,6 }));

	EXPECT_EQ(game.GetBoard()->GetElement({ 4,6 })->GetColor(), EColor::BLACK);
}

TEST(MoveTests, HorseMoveTest)
{
	Game game;
	Position horse = { 0,1 };

	// move for capture
	game.MovePiece({ 6,7 }, { 5,7 });
	EXPECT_NO_THROW(game.MovePiece(horse, { 2, 0 }));
	game.MovePiece({ 5,7 }, { 4,7 });
	EXPECT_NO_THROW(game.MovePiece({ 2,0 }, { 4, 1 }));
	game.MovePiece({ 4,7 }, { 3,7 });
	EXPECT_NO_THROW(game.MovePiece({ 4,1 }, { 6, 0 })); // captures a white pawn
	game.MovePiece({ 3,7 }, { 2,7 });

	// get a same color pawn near the horse for the exception test
	game.MovePiece({ 1,1 }, { 3,1 });
	game.MovePiece({ 2,7 }, { 1,6 });
	game.MovePiece({ 3,1 }, { 4,1 });
	game.MovePiece({ 6,6 }, { 5,6 });

	EXPECT_THROW(game.MovePiece({ 6,0 }, { 4,1 }), IllegalMoveException);
	EXPECT_THROW(game.MovePiece({ 6,0 }, { -1,8 }), OutOfBoundsException);

}

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