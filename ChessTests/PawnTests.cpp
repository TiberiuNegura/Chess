#include "PawnTests.h"
#include "Pawn.h"
#include "Game.h"
#include "PieceInterface.h"
#include "gtest/gtest.h"



TEST(PawnTest, MoveTest)
{
	Game game; // instantiate the game for the board [a board class is yet to be implemented]

	auto blackPawn1 = game.GetGameboard()[1][0];
	auto blackPawn2 = game.GetGameboard()[1][4];
	auto whitePawn1 = game.GetGameboard()[6][1];
	auto whitePawn2 = game.GetGameboard()[6][4];
	auto whitePawn3 = game.GetGameboard()[6][3];
	auto whitePawn4 = game.GetGameboard()[6][5];

	// black pawns
	EXPECT_NO_THROW(blackPawn1->Move({ 2,0 }, game.GetGameboard()));
	EXPECT_NO_THROW(blackPawn1->Move({ 3,0 }, game.GetGameboard()));
	EXPECT_NO_THROW(blackPawn2->Move({ 3,4 }, game.GetGameboard()));
	
	EXPECT_ANY_THROW(blackPawn1->Move({ 2,0 }, game.GetGameboard()));
	EXPECT_ANY_THROW(blackPawn1->Move({ 5,0 }, game.GetGameboard()));
	
	// test if the positions are placed properly
	EXPECT_EQ(blackPawn1->GetPosition().first, 3);
	EXPECT_EQ(blackPawn1->GetPosition().second, 0);
	
	//moving a white pawn in order for the black pawn to capture and to block a black pawn
	whitePawn1->Move({ 4,1 }, game.GetGameboard());
	whitePawn2->Move({ 4, 4 }, game.GetGameboard());

	
	//black pawn captures the white pawn
	EXPECT_NO_THROW(blackPawn1->Move({ 4,1 }, game.GetGameboard()));
	EXPECT_EQ(game.GetGameboard()[4][1]->GetColor(), Color::BLACK);
	
	//add another two white pawns in front of the black pawn
	EXPECT_NO_THROW(whitePawn3->Move({ 4,3 }, game.GetGameboard()));
	EXPECT_NO_THROW(whitePawn4->Move({ 4,5 }, game.GetGameboard()));
	EXPECT_ANY_THROW(blackPawn2->Move({ 4,4 }, game.GetGameboard()));
	EXPECT_NO_THROW(blackPawn2->Move({ 4,5 }, game.GetGameboard()));
}