#include "Game.h"
#include "IPiece.h"

#include "OutOfBoundsException.h"
#include "IllegalMoveException.h"
#include "EmptyPositionException.h"
#include "CheckException.h"

#include "gtest/gtest.h"

bool SameAs(IPiecePtr fp, IPiecePtr sp)
{
	if (!fp && sp || !sp && fp)
		return false;
	else
		if (!fp && !sp)
			return true;

	return (fp->GetColor() == sp->GetColor() && fp->GetName() == sp->GetName() && fp->GetType() == sp->GetType());
}

TEST(PawnEvolveTest, BlackPawn)
{
	Game game({
		' ', ' ',' ',' ',' ',' ','k',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ','p',' ',' ',' ',' ',
		'R', ' ',' ',' ','K',' ',' ','R'
		}, EColor::BLACK, EGameState::Playing);
	game.MovePiece({ 6, 3 }, { 7,3 });

	EXPECT_EQ(game.GetState(), EGameState::PawnEvolving);

	EXPECT_NO_THROW(game.EvolvePawn(EType::QUEEN));

	EXPECT_EQ(game.GetBoard()->GetElement({ 7, 3 })->GetType(), EType::QUEEN);
	EXPECT_EQ(game.GetState(), EGameState::Playing);
}

TEST(PawnEvolveTest, WhitePawn)
{
	Game game({
		' ', ' ',' ',' ',' ',' ','k',' ',
		' ', ' ',' ','P',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		'R', ' ',' ',' ','K',' ',' ','R'
		}, EColor::WHITE, EGameState::Playing);
	game.MovePiece({ 1, 3 }, { 0,3 });

	EXPECT_EQ(game.GetState(), EGameState::PawnEvolving);

	EXPECT_NO_THROW(game.EvolvePawn(EType::HORSE));

	EXPECT_EQ(game.GetBoard()->GetElement({ 0, 3 })->GetType(), EType::HORSE);
	EXPECT_EQ(game.GetState(), EGameState::Playing);
}

TEST(CheckTest, WhiteChecksBlack)
{
	Game game({
		' ', ' ',' ',' ',' ',' ','k',' ',
		' ', ' ',' ','P',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ','Q',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		'R', ' ',' ',' ','K',' ',' ','R'
		}, EColor::WHITE, EGameState::Playing);
	game.MovePiece({ 3, 7 }, { 3, 6 });

	EXPECT_EQ(game.GetState(), EGameState::Check);

	EXPECT_THROW(game.MovePiece({ 0, 6 }, { 1, 6 }), CheckException);

	game.MovePiece({ 0, 6 }, { 0, 5 });
	EXPECT_EQ(game.GetState(), EGameState::Playing);
}

TEST(CheckTest, BlackChecksWhite)
{
	Game game({
		' ', ' ',' ',' ',' ',' ','k',' ',
		' ', ' ',' ','P',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ','r',' ',' ',' ','Q',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		'R', ' ',' ',' ','K',' ',' ','R'
		}, EColor::BLACK, EGameState::Playing);
	game.MovePiece({ 3, 3 }, { 3,4 });

	EXPECT_EQ(game.GetState(), EGameState::Check);

	EXPECT_THROW(game.MovePiece({ 7, 4 }, { 6, 4 }), CheckException);

	game.MovePiece({ 7, 4 }, { 7, 3 });
	EXPECT_EQ(game.GetState(), EGameState::Playing);
}

TEST(CheckmateTest, WhiteChecksmateBlack)
{
	Game game;
	game.Start();

	std::vector<std::pair<Position, Position>> moves = { 
		{{6,4},{5,4}},
		{{1,6},{3,6}},
		{{6,0},{5,0}},
		{{1,5},{2,5}},
		{{7,3},{3,7}} 
	};
	for (auto move : moves)
	{
		EXPECT_NO_THROW(game.MovePiece(move.first, move.second));
	}
	EXPECT_EQ(game.GetState(), EGameState::WhiteWon);
	EXPECT_THROW(game.MovePiece({ 5,0 }, { 4,0 }), GameOverException);
}

TEST(CheckmateTest, BlackChecksmateWhite)
{
	Game game;
	game.Start();

	std::vector<std::pair<Position, Position>> moves = {
		{{6,6},{4,6}},
		{{1,4},{2,4}},
		{{6,5},{5,5}},
		{{0,3},{4,7}}
	};
	for (auto move : moves)
	{
		EXPECT_NO_THROW(game.MovePiece(move.first, move.second));
	}
	EXPECT_EQ(game.GetState(), EGameState::BlackWon);
	EXPECT_THROW(game.MovePiece({ 6,0 }, { 5,0 }), GameOverException);
}

TEST(DrawProposalTest,Proposal)
{
	Game game;
	game.MakeTieRequest();
	game.TieRequestResponse(true);

	EXPECT_EQ(game.GetState(), EGameState::Tie);
}

TEST(StalemateTest, TieCase)
{
	Game game({
		' ', ' ',' ','r',' ','r','k',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', 'q',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ','K',' ',' ',' '
		}, EColor::BLACK, EGameState::Playing);
	game.MovePiece({ 4,1 }, { 4,2 });

	EXPECT_EQ(game.GetState(), EGameState::Tie);
}

TEST(ThreeFoldRepetitionTest, Test)
{
	Game game({
		' ', 'r',' ',' ',' ','r','k',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ','q',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ','K',' ',' ',' '
		}, EColor::BLACK, EGameState::Playing);
	
	game.MovePiece({ 4,3 }, { 4,4 });
	game.MovePiece({ 7,4 }, { 7,3 });
	
	game.MovePiece({ 4,4 }, { 4,3 });
	game.MovePiece({ 7,3 }, { 7,4 });
	
	game.MovePiece({ 4,3 }, { 4,4 });
	game.MovePiece({ 7,4 }, { 7,3 });
	
	game.MovePiece({ 4,4 }, { 4,3 });
	game.MovePiece({ 7,3 }, { 7,4 });

	game.MovePiece({ 4,3 }, { 4,4 });
	
	EXPECT_EQ(game.GetState(), EGameState::Tie);
	EXPECT_THROW(game.MovePiece({ 7,4 }, { 7,3 }), GameOverException);
}

TEST(PGNGameTest, Load)
{
	Game game, expectedGame({
	' ', 'h', 'B', ' ', ' ', 'b', ' ', 'q',
	'p', ' ', 'p', ' ', ' ', ' ', ' ', ' ',
	'B', ' ', 'B', ' ', ' ', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ', ' ', 'p', ' ',
	' ', ' ', ' ', ' ', 'p', ' ', ' ', 'k',
	' ', ' ', ' ', ' ', 'P', ' ', ' ', 'p',
	' ', 'P', ' ', 'P', 'B', 'P', ' ', 'P',
	'R', 'H', 'B', 'Q', 'K', ' ', 'H', 'R'
		}, EColor::BLACK, EGameState::Playing);

	game.LoadFromFormat("files/gabi.pgn");

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			EXPECT_TRUE(SameAs(game.GetBoard()->GetElement({ i,j }), expectedGame.GetBoard()->GetElement({ i,j })));
		}
}

TEST(PGNGameTest, Save)
{
	Game game;
	game.Start();

	std::vector<std::pair<Position, Position>> moveList = {
		{{6,0},{4,0}}, {{1,1},{3,1}}, {{7,1},{5,2}}, {{3,1},{4,0}},
		{{5,2},{4,0}}, {{1,0},{3,0}}, {{7,0},{5,0}}, {{1,2},{3,2}}
	};

	for (const auto& move : moveList) {
		game.MovePiece(move.first, move.second);
	}

	EXPECT_TRUE(game.SavePGN("files/game_save.pgn"));
}
