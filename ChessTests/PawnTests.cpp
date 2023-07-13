#include "PawnTests.h"
#include "Pawn.h"
#include "Game.h"
#include "PieceInterface.h"
#include "gtest/gtest.h"


TEST(PawnTest, MoveTest)
{
	Game game;

	auto blackPawn1 = game.GetGameboard()[1][0];
	auto blackPawn2 = game.GetGameboard()[1][3];
	auto whitePawn1 = game.GetGameboard()[6][7];
	auto whitePawn2 = game.GetGameboard()[6][7];

	EXPECT_NO_THROW(blackPawn1->Move({ 2,0 }, game.GetGameboard()));
	EXPECT_NO_THROW(blackPawn1->Move({ 3,0 }, game.GetGameboard()));
	
	EXPECT_ANY_THROW(blackPawn1->Move({ 2,0 }, game.GetGameboard()));
	

	EXPECT_EQ(blackPawn1->GetPosition().first, 3);
	EXPECT_EQ(blackPawn1->GetPosition().second, 0);


}