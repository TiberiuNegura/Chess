#include "Game.h"
#include "IPiece.h"

#include "OutOfBoundsException.h"
#include "IllegalMoveException.h"
#include "EmptyPositionException.h"
#include "CheckException.h"

#include "gtest/gtest.h"

class MoveTests : public testing::Test {
protected:
	void SetUp() override {
		game = Game({
		'r', 'h', 'b', 'q', 'k', 'b', 'h', 'r',
		'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
		'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
		'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R'
			}, EColor::WHITE, EGameState::Playing);
	}

	void ChangeTurn() {
		game.UpdateTurn();
	}

protected:
	Game game;
};

TEST_F(MoveTests, BlackPawnMoveTest) {
	Position blackPawn1 = { 1, 0 };
	Position blackPawn2 = { 1, 4 };
	Position blackPawn3 = { 1, 3 };

	ChangeTurn();
	EXPECT_NO_THROW(game.MovePiece(blackPawn1, { 2, 0 })); // Moving a black pawn
	ChangeTurn();
	EXPECT_NO_THROW(game.MovePiece(blackPawn2, { 3, 4 }));
	ChangeTurn();
	EXPECT_NO_THROW(game.MovePiece(blackPawn3, { 3, 3 }));

	EXPECT_THROW(game.MovePiece({ 2, 0 }, { 3, 0 }), IllegalMoveException); // Illegal move
	EXPECT_THROW(game.MovePiece({ 3, 3 }, { 2, 3 }), IllegalMoveException);

	EXPECT_EQ(game.GetTurn(), EColor::WHITE); // Check if it's White's turn
}

TEST_F(MoveTests, WhitePawnMoveTest) {
	Position whitePawn1 = { 6, 1 };
	Position whitePawn2 = { 6, 4 };
	Position whitePawn3 = { 6, 3 };

	EXPECT_NO_THROW(game.MovePiece(whitePawn1, { 4, 1 })); // Moving a white pawn to allow black pawn to capture and block
	ChangeTurn();
	EXPECT_NO_THROW(game.MovePiece(whitePawn2, { 4, 4 }));
	ChangeTurn();
	EXPECT_NO_THROW(game.MovePiece(whitePawn3, { 4, 3 }));

	EXPECT_THROW(game.MovePiece({ 4, 1 }, { 5, 1 }), IllegalMoveException); // Illegal move
	EXPECT_EQ(game.GetTurn(), EColor::BLACK); // Check if it's Black's turn
	ChangeTurn();
	EXPECT_THROW(game.MovePiece({ 4, 4 }, { 5, 4 }), IllegalMoveException);
	ChangeTurn();

	game.MovePiece({ 1, 0 }, { 3, 0 });

	EXPECT_NO_THROW(game.MovePiece({ 4, 1 }, { 3, 0 })); // White pawn captures the black pawn

	// Check if the positions are placed properly after capture
	EXPECT_EQ(game.GetBoard()->GetElement({ 3, 0 })->GetColor(), EColor::WHITE);

	// Test illegal moves, out of bounds, and empty position
	EXPECT_THROW(game.MovePiece({ 3, 0 }, { 3, 0 }), IllegalMoveException); // Moving to the same position
	EXPECT_THROW(game.MovePiece({ 3, 0 }, { 5, 0 }), IllegalMoveException); // Illegal move for a pawn
	EXPECT_THROW(game.MovePiece({ 6, 2 }, { 8, 4 }), OutOfBoundsException); // Out of bounds move
	EXPECT_THROW(game.MovePiece({ 2, 0 }, { 1, 0 }), EmptyPositionException); // Empty position
}

TEST_F(MoveTests, WhiteRookMoveTest)
{

	Position rook = { 7, 7 };
	Position target = { 5, 7 };

	EXPECT_THROW(game.MovePiece(rook, target), IllegalMoveException);

	game.MovePiece({ 6, 7 }, { 4, 7 });
	game.MovePiece({ 1, 7 }, { 2, 7 });

	EXPECT_NO_THROW(game.MovePiece(rook, target));

	game.MovePiece({ 2, 7 }, { 3, 7 });
	game.MovePiece({ 5, 7 }, { 5, 2 });
	game.MovePiece({ 1, 2 }, { 2, 2 });

	EXPECT_NO_THROW(game.MovePiece({ 5, 2 }, { 2, 2 }));
	ChangeTurn();
	EXPECT_THROW(game.MovePiece({ 2, 2 }, { 6, 2 }), IllegalMoveException);
}

TEST_F(MoveTests, BlackRookMoveTest)
{
	ChangeTurn();
	Position rook = { 0, 0 };
	Position target = { 2, 0 };

	EXPECT_THROW(game.MovePiece(rook, target), IllegalMoveException);

	game.MovePiece({ 1, 0 }, { 3, 0 });
	game.MovePiece({ 6, 0 }, { 5, 0 });

	EXPECT_NO_THROW(game.MovePiece(rook, target));

	game.MovePiece({ 5, 0 }, { 4, 0 });
	game.MovePiece({ 2, 0 }, { 2, 5 });
	ChangeTurn();

	// The black rook captures an opposite color piece
	EXPECT_NO_THROW(game.MovePiece({ 2, 5 }, { 6, 5 }));

	ChangeTurn();

	// The black rook cannot capture a piece of its color
	EXPECT_THROW(game.MovePiece({ 6, 5 }, { 1, 5 }), IllegalMoveException);
}

TEST_F(MoveTests, WhiteBishopMoveTest)
{
	Position bishop = { 7, 5 };
	Position target = { 5, 7 };

	EXPECT_THROW(game.MovePiece(bishop, target), IllegalMoveException);

	game.MovePiece({ 6, 6 }, { 4, 6 });
	game.MovePiece({ 1, 1 }, { 3, 1 });

	EXPECT_NO_THROW(game.MovePiece(bishop, target));

	game.MovePiece({ 3, 1 }, { 4, 1 });
	game.MovePiece({ 4, 6 }, { 3, 6 });

	ChangeTurn();

	EXPECT_NO_THROW(game.MovePiece({ 5, 7 }, { 1, 3 }));

	ChangeTurn();

	game.MovePiece({ 6,7 }, { 5,7 });

	ChangeTurn();

	EXPECT_NO_THROW(game.MovePiece({ 1, 3 }, { 0, 2 }));

	ChangeTurn();

	EXPECT_THROW(game.MovePiece({ 0, 2 }, { 5, 7 }), IllegalMoveException);
}

TEST_F(MoveTests, BlackBishopMoveTest)
{
	ChangeTurn();
	Position bishop = { 0, 2 };
	Position target = { 2, 0 };

	EXPECT_THROW(game.MovePiece(bishop, target), IllegalMoveException);

	game.MovePiece({ 1, 1 }, { 2, 1 });
	game.MovePiece({ 6, 6 }, { 4, 6 });

	EXPECT_NO_THROW(game.MovePiece(bishop, target));

	ChangeTurn();

	EXPECT_NO_THROW(game.MovePiece({ 2, 0 }, { 6, 4 }));

	ChangeTurn();

	EXPECT_NO_THROW(game.MovePiece({ 6, 4 }, { 4, 6 }));

	ChangeTurn();
	 
	EXPECT_THROW(game.MovePiece({ 4, 6 }, { 1, 3 }), IllegalMoveException);
}

TEST_F(MoveTests, WhiteHorseMoveTest)
{
	Position whiteHorse = { 0, 1 };

	// White horse cannot move to invalid positions
	EXPECT_THROW(game.MovePiece(whiteHorse, { 7, 7 }), IllegalMoveException);
	EXPECT_THROW(game.MovePiece(whiteHorse, { 6, 6 }), IllegalMoveException);
	EXPECT_THROW(game.MovePiece(whiteHorse, { 5, 7 }), IllegalMoveException);

	// Test valid horse moves
	game.MovePiece({ 6, 7 }, { 5, 7 });
	EXPECT_NO_THROW(game.MovePiece(whiteHorse, { 2, 0 }));
	game.MovePiece({ 5, 7 }, { 4, 7 });
	EXPECT_NO_THROW(game.MovePiece({ 2, 0 }, { 4, 1 }));
	game.MovePiece({ 4, 7 }, { 3, 7 });
	EXPECT_NO_THROW(game.MovePiece({ 4, 1 }, { 6, 0 })); // Captures a white pawn
	game.MovePiece({ 3, 7 }, { 2, 7 });

	// Get a same color pawn near the horse for the exception test
	game.MovePiece({ 1, 1 }, { 3, 1 });
	game.MovePiece({ 2, 7 }, { 1, 6 });
	game.MovePiece({ 3, 1 }, { 4, 1 });
	game.MovePiece({ 6, 6 }, { 5, 6 });

	EXPECT_THROW(game.MovePiece({ 6, 0 }, { 4, 1 }), IllegalMoveException); // Same color cannot capture its own pawn
	EXPECT_THROW(game.MovePiece({ 6, 0 }, { -1, 8 }), OutOfBoundsException); // Move out of bounds
}

TEST_F(MoveTests, BlackHorseMoveTest)
{
	ChangeTurn();
	Position blackHorse = { 0, 1 };

	// Black horse cannot move to invalid positions
	EXPECT_THROW(game.MovePiece(blackHorse, { 2, 4 }), IllegalMoveException);
	EXPECT_THROW(game.MovePiece(blackHorse, { 1, 1 }), IllegalMoveException);
	EXPECT_THROW(game.MovePiece(blackHorse, { 3, 2 }), IllegalMoveException);

	// Test valid horse moves
	EXPECT_NO_THROW(game.MovePiece(blackHorse, { 2, 0 }));
	ChangeTurn();
	EXPECT_NO_THROW(game.MovePiece({ 2, 0 }, { 4, 1 }));
	ChangeTurn();
	EXPECT_NO_THROW(game.MovePiece({ 4, 1 }, { 6, 0 })); // Captures a white pawn

	ChangeTurn();

	// Get a same color pawn near the horse for the exception test
	game.MovePiece({ 1, 1 }, { 3, 1 });
	ChangeTurn();
	game.MovePiece({ 3, 1 }, { 4, 1 });
	ChangeTurn();

	EXPECT_THROW(game.MovePiece({ 6, 0 }, { 4, 1 }), IllegalMoveException); // Same color cannot capture its own pawn
	EXPECT_THROW(game.MovePiece({ 6, 0 }, { -1, 8 }), OutOfBoundsException); // Move out of bounds
}

TEST_F(MoveTests, BlackKingMoveTest)
{
	Position king = { 0, 4 };

	EXPECT_THROW(game.MovePiece(king, { 1, 4 }), IllegalMoveException);

	game.MovePiece({ 6, 7 }, { 5, 7 });
	game.MovePiece({ 1, 4 }, { 3, 4 });
	game.MovePiece({ 6, 5 }, { 5, 5 });

	EXPECT_NO_THROW(game.MovePiece(king, { 1, 4 }));
	game.MovePiece({ 5, 7 }, { 4, 7 });
	EXPECT_NO_THROW(game.MovePiece({ 1, 4 }, { 2, 3 }));

	game.MovePiece({ 4, 7 }, { 3, 7 });

	EXPECT_THROW(game.MovePiece({ 2, 3 }, { 5, 4 }), IllegalMoveException);
	EXPECT_EQ(game.GetBoard()->GetElement({ 2, 3 })->GetType(), EType::KING);
}

TEST_F(MoveTests, WhiteKingMoveTest)
{
	Position king = { 7, 4 };

	EXPECT_THROW(game.MovePiece(king, { 6, 4 }), IllegalMoveException);

	game.MovePiece({ 6, 4 }, { 4, 4 });

	ChangeTurn();
	EXPECT_NO_THROW(game.MovePiece(king, { 6, 4 }));
	ChangeTurn();
	EXPECT_NO_THROW(game.MovePiece({ 6, 4 }, { 5, 4 }));
	ChangeTurn();
	EXPECT_THROW(game.MovePiece({ 5, 4 }, { 4, 4 }), IllegalMoveException);
	EXPECT_EQ(game.GetBoard()->GetElement({ 5, 4 })->GetType(), EType::KING);

	EXPECT_NO_THROW(game.MovePiece({ 5, 4 }, { 4, 5 }));
	ChangeTurn();
	EXPECT_NO_THROW(game.MovePiece({ 4, 5 }, { 3, 4 }));
}

TEST_F(MoveTests, WhiteQueenMoveTest)
{
	Position whiteQueen = { 7, 3 };

	// White queen cannot move to an invalid position
	EXPECT_THROW(game.MovePiece(whiteQueen, { 5, 3 }), IllegalMoveException);

	// Make room for the white queen to move
	game.MovePiece({ 6, 3 }, { 4, 3 });
	game.MovePiece({ 1, 3 }, { 3, 3 });

	// Test valid queen moves
	EXPECT_NO_THROW(game.MovePiece(whiteQueen, { 5, 3 }));
	EXPECT_NO_THROW(game.MovePiece({ 0, 3 }, { 2, 3 }));
	EXPECT_THROW(game.MovePiece({ 5, 3 }, { 1, 5 }), IllegalMoveException);
	EXPECT_NO_THROW(game.MovePiece({ 5, 3 }, { 5, 0 }));
	ChangeTurn();
	EXPECT_NO_THROW(game.MovePiece({ 5, 0 }, { 2, 3 }));

	// Test queen capturing a piece
	EXPECT_TRUE(game.GetBoard()->GetElement({ 2, 3 })->Is(EType::QUEEN));
}

// Test for the black queen
TEST_F(MoveTests, BlackQueenMoveTest)
{
	ChangeTurn(); // Change to black's turn
	Position blackQueen = { 0, 3 };

	// Black queen cannot move to an invalid position
	EXPECT_THROW(game.MovePiece(blackQueen, { 2, 3 }), IllegalMoveException);

	// Make room for the black queen to move
	game.MovePiece({ 1, 3 }, { 3, 3 });
	ChangeTurn();

	// Test valid queen moves
	EXPECT_NO_THROW(game.MovePiece(blackQueen, { 2, 3 }));
	ChangeTurn();
	EXPECT_NO_THROW(game.MovePiece({ 2, 3 }, { 2, 0 }));
	ChangeTurn();
	EXPECT_NO_THROW(game.MovePiece({ 2, 0 }, { 6, 0 }));
	ChangeTurn();
	EXPECT_THROW(game.MovePiece({ 6, 0 }, { 1, 0 }), IllegalMoveException);


	EXPECT_TRUE(game.GetBoard()->GetElement({ 6, 0 })->Is(EType::QUEEN));
}

TEST(CastlingTest, WhiteLeftTest)
{
	Game game({
		' ', ' ',' ',' ',' ',' ','k',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		'R', ' ',' ',' ','K',' ',' ','R'
		}, EColor::WHITE, EGameState::Playing);
	
	EXPECT_EQ(game.GetBoard()->GetElement({ 7,0 })->GetType(), EType::ROOK);
	EXPECT_EQ(game.GetBoard()->GetElement({ 7,0 })->GetColor(), EColor::WHITE);
	EXPECT_EQ(game.GetTurn(), EColor::WHITE);

	EXPECT_NO_THROW(game.MovePiece({7, 4}, {7, 2}));
	
	EXPECT_EQ(game.GetTurn(), EColor::BLACK);
	EXPECT_EQ(game.GetBoard()->GetElement({ 7,2 })->GetType(), EType::KING);
	EXPECT_EQ(game.GetBoard()->GetElement({ 7,2 })->GetColor(), EColor::WHITE);
	EXPECT_EQ(game.GetBoard()->GetElement({ 7,3 })->GetType(), EType::ROOK);
	EXPECT_EQ(game.GetBoard()->GetElement({ 7,3 })->GetColor(), EColor::WHITE);
}

TEST(CastlingTest, WhiteLeftTest2)
{
	Game game({
		' ', ' ',' ',' ',' ',' ','k',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		'R',' ','Q',' ','K',' ',' ','R'
		}, EColor::WHITE, EGameState::Playing);

	EXPECT_THROW(game.MovePiece({ 7, 4 }, { 7, 2 }), IllegalMoveException);

	EXPECT_EQ(game.GetBoard()->GetElement({ 7,4 })->GetType(), EType::KING);
	EXPECT_EQ(game.GetBoard()->GetElement({ 7,4 })->GetColor(), EColor::WHITE);
	EXPECT_EQ(game.GetBoard()->GetElement({ 7,0 })->GetType(), EType::ROOK);
	EXPECT_EQ(game.GetBoard()->GetElement({ 7,0 })->GetColor(), EColor::WHITE);
}

TEST(CastlingTest, WhiteLeftTest3)
{
	Game game({
		' ', ' ','q',' ',' ',' ','k',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		'R', ' ',' ',' ','K',' ',' ','R'
		}, EColor::WHITE, EGameState::Playing);

	EXPECT_THROW(game.MovePiece({ 7, 4 }, { 7, 2 }), IllegalMoveException);

	EXPECT_EQ(game.GetBoard()->GetElement({ 7,4 })->GetType(), EType::KING);
	EXPECT_EQ(game.GetBoard()->GetElement({ 7,4 })->GetColor(), EColor::WHITE);
	EXPECT_EQ(game.GetBoard()->GetElement({ 7,0 })->GetType(), EType::ROOK);
	EXPECT_EQ(game.GetBoard()->GetElement({ 7,0 })->GetColor(), EColor::WHITE);
}

TEST(CastlingTest, WhiteLeftTest4)
{
	Game game({
		' ', ' ',' ',' ','q',' ','k',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		'R',' ',' ',' ','K',' ',' ','R'
		}, EColor::WHITE, EGameState::Check);
	EXPECT_THROW(game.MovePiece({ 7, 4 }, { 7, 2 }), CheckException);

	EXPECT_EQ(game.GetBoard()->GetElement({ 7,4 })->GetType(), EType::KING);
	EXPECT_EQ(game.GetBoard()->GetElement({ 7,4 })->GetColor(), EColor::WHITE);
	EXPECT_EQ(game.GetBoard()->GetElement({ 7,0 })->GetType(), EType::ROOK);
	EXPECT_EQ(game.GetBoard()->GetElement({ 7,0 })->GetColor(), EColor::WHITE);
}

TEST(CastlingTest, WhiteRightTest)
{
	Game game({
		' ', ' ','q',' ',' ',' ','k',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		'R',' ',' ',' ','K',' ',' ','R'
		}, EColor::WHITE, EGameState::Playing);

	EXPECT_NO_THROW(game.MovePiece({ 7, 4 }, { 7, 6 }));

	EXPECT_EQ(game.GetBoard()->GetElement({ 7,6 })->GetType(), EType::KING);
	EXPECT_EQ(game.GetBoard()->GetElement({ 7,6 })->GetColor(), EColor::WHITE);
	EXPECT_EQ(game.GetBoard()->GetElement({ 7,5 })->GetType(), EType::ROOK);
	EXPECT_EQ(game.GetBoard()->GetElement({ 7,5 })->GetColor(), EColor::WHITE);
}

TEST(CastlingTest, WhiteRightTest2)
{


	Game game({
		' ', ' ','q',' ',' ','r','k',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		'R', ' ',' ',' ','K',' ',' ','R'
		}, EColor::WHITE, EGameState::Playing);


	EXPECT_THROW(game.MovePiece({ 7, 4 }, { 7, 6 }), IllegalMoveException);

	EXPECT_EQ(game.GetBoard()->GetElement({ 7,4 })->GetType(), EType::KING);
	EXPECT_EQ(game.GetBoard()->GetElement({ 7,4 })->GetColor(), EColor::WHITE);
	EXPECT_EQ(game.GetBoard()->GetElement({ 7,7 })->GetType(), EType::ROOK);
	EXPECT_EQ(game.GetBoard()->GetElement({ 7,7 })->GetColor(), EColor::WHITE);
}

TEST(CastlingTest, WhiteRightTest3)
{
	Game game({
		' ', ' ',' ',' ',' ',' ','k',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		'R',' ',' ',' ','K',' ','Q','R'
		}, EColor::WHITE, EGameState::Playing);

	EXPECT_THROW(game.MovePiece({ 7, 4 }, { 7, 6 }), IllegalMoveException);

	EXPECT_EQ(game.GetBoard()->GetElement({ 7,4 })->GetType(), EType::KING);
	EXPECT_EQ(game.GetBoard()->GetElement({ 7,4 })->GetColor(), EColor::WHITE);
	EXPECT_EQ(game.GetBoard()->GetElement({ 7,7 })->GetType(), EType::ROOK);
	EXPECT_EQ(game.GetBoard()->GetElement({ 7,7 })->GetColor(), EColor::WHITE);
}

TEST(CastlingTest, WhiteRightTest4)
{
	Game game({
		' ', ' ','q',' ','r',' ','k',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		'R',' ',' ',' ','K',' ',' ','R'
		}, EColor::WHITE, EGameState::Check);
	EXPECT_THROW(game.MovePiece({ 7, 4 }, { 7, 6 }), CheckException);

	EXPECT_EQ(game.GetBoard()->GetElement({ 7,4 })->GetType(), EType::KING);
	EXPECT_EQ(game.GetBoard()->GetElement({ 7,4 })->GetColor(), EColor::WHITE);
	EXPECT_EQ(game.GetBoard()->GetElement({ 7,7 })->GetType(), EType::ROOK);
	EXPECT_EQ(game.GetBoard()->GetElement({ 7,7 })->GetColor(), EColor::WHITE);
}

TEST(CastlingTest, BlackLeftTest)
{
	Game game({
		'r', ' ',' ',' ','k',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ',' ',' ',' ','K',' ',' ',' '
		}, EColor::BLACK, EGameState::Playing);

	EXPECT_NO_THROW(game.MovePiece({ 0, 4 }, { 0, 2 }));

	EXPECT_EQ(game.GetBoard()->GetElement({ 0,2 })->GetType(), EType::KING);
	EXPECT_EQ(game.GetBoard()->GetElement({ 0,2 })->GetColor(), EColor::BLACK);
	EXPECT_EQ(game.GetBoard()->GetElement({ 0,3 })->GetType(), EType::ROOK);
	EXPECT_EQ(game.GetBoard()->GetElement({ 0,3 })->GetColor(), EColor::BLACK);
}

TEST(CastlingTest, BlackLeftTest2)
{
	Game game({
		'r', ' ',' ',' ','k',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		'Q',' ',' ',' ','K',' ',' ',' '
		}, EColor::BLACK, EGameState::Playing);

	EXPECT_NO_THROW(game.MovePiece({ 0, 4 }, { 0, 2 }));

	EXPECT_EQ(game.GetBoard()->GetElement({ 0,2 })->GetType(), EType::KING);
	EXPECT_EQ(game.GetBoard()->GetElement({ 0,2 })->GetColor(), EColor::BLACK);
	EXPECT_EQ(game.GetBoard()->GetElement({ 0,3 })->GetType(), EType::ROOK);
	EXPECT_EQ(game.GetBoard()->GetElement({ 0,3 })->GetColor(), EColor::BLACK);
}

TEST(CastlingTest, BlackLeftTest3)
{
	Game game({
		'r', ' ',' ',' ','k',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ','Q',' ',' ','K',' ',' ',' '
		}, EColor::BLACK, EGameState::Playing);

	EXPECT_NO_THROW(game.MovePiece({ 0, 4 }, { 0, 2 }));

	EXPECT_EQ(game.GetBoard()->GetElement({ 0,2 })->GetType(), EType::KING);
	EXPECT_EQ(game.GetBoard()->GetElement({ 0,2 })->GetColor(), EColor::BLACK);
	EXPECT_EQ(game.GetBoard()->GetElement({ 0,3 })->GetType(), EType::ROOK);
	EXPECT_EQ(game.GetBoard()->GetElement({ 0,3 })->GetColor(), EColor::BLACK);
}

TEST(CastlingTest, BlackLeftTest4)
{
	Game game({
		'r', ' ',' ',' ','k',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ','Q',' ',' ',' ',
		' ',' ',' ',' ', 'K',' ',' ',' '
		}, EColor::BLACK, EGameState::Check);

	EXPECT_THROW(game.MovePiece({ 0, 4 }, { 0, 2 }), CheckException);

	EXPECT_EQ(game.GetBoard()->GetElement({ 0,4 })->GetType(), EType::KING);
	EXPECT_EQ(game.GetBoard()->GetElement({ 0,4 })->GetColor(), EColor::BLACK);
	EXPECT_EQ(game.GetBoard()->GetElement({ 0,0 })->GetType(), EType::ROOK);
	EXPECT_EQ(game.GetBoard()->GetElement({ 0,0 })->GetColor(), EColor::BLACK);
}

TEST(CastlingTest, BlackLeftTest5)
{
	Game game({
		'r', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ','k',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ',' ',' ',' ', 'K',' ',' ',' '
		}, EColor::BLACK, EGameState::Playing);
	EXPECT_THROW(game.MovePiece({ 1, 4 }, { 0, 2 }), IllegalMoveException);
}

TEST(CastlingTest, BlackRightTest)
{
	Game game({
		'r', ' ',' ',' ','k',' ',' ','r',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ',' ',' ',' ','K',' ',' ',' '
		}, EColor::BLACK, EGameState::Playing);

	EXPECT_NO_THROW(game.MovePiece({ 0, 4 }, { 0, 6 }));

	EXPECT_EQ(game.GetBoard()->GetElement({ 0,6 })->GetType(), EType::KING);
	EXPECT_EQ(game.GetBoard()->GetElement({ 0,6 })->GetColor(), EColor::BLACK);
	EXPECT_EQ(game.GetBoard()->GetElement({ 0,5 })->GetType(), EType::ROOK);
	EXPECT_EQ(game.GetBoard()->GetElement({ 0,5 })->GetColor(), EColor::BLACK);
}

TEST(CastlingTest, BlackRightTest2)
{
	Game game({
		'r', ' ',' ',' ','k',' ','b','r',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ',' ',' ',' ','K',' ',' ',' '
		}, EColor::BLACK, EGameState::Playing);

	EXPECT_THROW(game.MovePiece({ 0, 4 }, { 0, 6 }), IllegalMoveException);

	EXPECT_EQ(game.GetBoard()->GetElement({ 0,4 })->GetType(), EType::KING);
	EXPECT_EQ(game.GetBoard()->GetElement({ 0,4 })->GetColor(), EColor::BLACK);
	EXPECT_EQ(game.GetBoard()->GetElement({ 0,7 })->GetType(), EType::ROOK);
	EXPECT_EQ(game.GetBoard()->GetElement({ 0,7 })->GetColor(), EColor::BLACK);
}

TEST(CastlingTest, BlackRightTest3)
{
	Game game({
		'r', ' ',' ',' ','k',' ',' ','r',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ','Q',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ',' ',' ',' ','K',' ',' ',' '
		}, EColor::BLACK, EGameState::Playing);

	EXPECT_THROW(game.MovePiece({ 0, 4 }, { 0, 6 }), IllegalMoveException);

	EXPECT_EQ(game.GetBoard()->GetElement({ 0,4 })->GetType(), EType::KING);
	EXPECT_EQ(game.GetBoard()->GetElement({ 0,4 })->GetColor(), EColor::BLACK);
	EXPECT_EQ(game.GetBoard()->GetElement({ 0,7 })->GetType(), EType::ROOK);
	EXPECT_EQ(game.GetBoard()->GetElement({ 0,7 })->GetColor(), EColor::BLACK);
}

TEST(CastlingTest, BlackRightTest4)
{
	Game game({
		'r', ' ',' ',' ','k',' ','b','r',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ','Q',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ',' ',' ',' ','K',' ',' ',' '
		}, EColor::BLACK, EGameState::Check);

	EXPECT_THROW(game.MovePiece({ 0, 4 }, { 0, 6 }), CheckException);

	EXPECT_EQ(game.GetBoard()->GetElement({ 0,4 })->GetType(), EType::KING);
	EXPECT_EQ(game.GetBoard()->GetElement({ 0,4 })->GetColor(), EColor::BLACK);
	EXPECT_EQ(game.GetBoard()->GetElement({ 0,7 })->GetType(), EType::ROOK);
	EXPECT_EQ(game.GetBoard()->GetElement({ 0,7 })->GetColor(), EColor::BLACK);
}

TEST(CastlingTest, KingMovedTest)
{
	Game game({
		'r', ' ',' ',' ','k',' ',' ','r',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ',' ',' ',' ','K',' ',' ',' '
		}, EColor::BLACK, EGameState::Playing);

	game.MovePiece({ 0, 4 }, { 1, 4 });
	game.MovePiece({ 7, 4 }, { 7, 5 });
	game.MovePiece({ 1, 4 }, { 0, 4 });
	game.MovePiece({ 7, 5 }, { 7, 4 });


	EXPECT_THROW(game.MovePiece({ 0, 4 }, { 0, 6 }), IllegalMoveException);
	EXPECT_THROW(game.MovePiece({ 0, 4 }, { 0, 2 }), IllegalMoveException);
}

TEST(CastlingTest, RookMovedTest)
{
	Game game({
		'r', ' ',' ',' ','k',' ',' ','r',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ',' ',' ',' ','K',' ',' ',' '
		}, EColor::BLACK, EGameState::Playing);

	game.MovePiece({ 0, 7 }, { 5, 7 });
	game.MovePiece({ 7, 4 }, { 7, 5 });
	game.MovePiece({ 5, 7 }, { 0, 7 });
	game.MovePiece({ 7, 5 }, { 7, 4 });


	EXPECT_THROW(game.MovePiece({ 0, 4 }, { 0, 6 }), IllegalMoveException);
}

TEST(FenStringTest, FromFenToBoard)
{
	Game game;
	game.LoadFromFormat("files/FromFenToBoard1.fen");
	Board board(CharBoardRepresentation{
		' ', ' ','r',' ',' ','k',' ','r',
		'p', 'p',' ',' ','b','p','p','p',
		' ', ' ',' ','p',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ','b',' ',
		'P', 'Q','B',' ','h',' ','b',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', 'P',' ',' ',' ','P',' ','P',
		' ', ' ','K',' ',' ',' ','H',' '
		});

	for (int row = 0; row < 8; row++)
		for (int column = 0; column < 8; column++)
		{
			if (board.Get({ row,column }) && game.GetBoard()->GetElement({ row, column }))
				EXPECT_TRUE(board.Get({ row,column })->Is(game.GetBoard()->GetElement({ row, column })->GetType()));
		}
	EXPECT_TRUE(game.GetTurn() == EColor::WHITE);
}

TEST(FenStringTest, FromBoardToFen)
{
	Game game(CharBoardRepresentation{
		' ', ' ','r',' ',' ','k',' ','r',
		'p', 'p',' ',' ','b','p','p','p',
		' ', ' ',' ','p',' ',' ',' ',' ',
		' ', ' ',' ',' ',' ',' ','B',' ',
		'P', 'Q','B',' ','h',' ','b',' ',
		' ', ' ',' ',' ',' ',' ',' ',' ',
		' ', 'P',' ',' ',' ','P',' ','P',
		' ',' ','K',' ',' ',' ','H',' '
		}, EColor::WHITE, EGameState::Playing);

	EXPECT_EQ(game.GetFenString(), "2r2k1r/pp2bppp/3p4/6B1/PQB1h1b1/8/1P3P1P/2K3H1 w");
}

TEST(PgnStringTest, FromPgnToBoard1)
{
	Game game;
	game.LoadFromFormat("files/FromPgnToBoard1.pgn");
	Board board(CharBoardRepresentation{
		'Q', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
		' ', ' ', ' ', ' ', ' ', 'R', ' ', 'k',
		' ', ' ', ' ', 'P', ' ', 'Q', ' ', ' ',
		' ', ' ', ' ', ' ', 'p', ' ', ' ', ' ',
		' ', ' ', ' ', 'P', ' ', ' ', ' ', ' ',
		' ', ' ', ' ', ' ', 'B', 'H', ' ', ' ',
		' ', ' ', ' ', ' ', 'P', 'P', ' ', ' ',
		' ', 'b', ' ', ' ', 'K', 'B', ' ', ' '
		});

	for (int row = 0; row < 8; row++)
		for (int column = 0; column < 8; column++)
		{
			if (board.Get({ row,column }) && game.GetBoard()->GetElement({ row, column }))
				EXPECT_TRUE(board.Get({ row,column })->Is(game.GetBoard()->GetElement({ row, column })->GetType()));
		}
	EXPECT_TRUE(game.GetState() == EGameState::WhiteWon);
}

TEST(PgnStringTest, FromPgnToBoard2)
{
	Game game;
	game.LoadFromFormat("files/FromPgnToBoard2.pgn");
	Board board(CharBoardRepresentation{
		' ', 'h', 'B', ' ', ' ', 'b', ' ', 'q',
		'p', ' ', 'p', ' ', ' ', ' ', ' ', ' ',
		'B', ' ', 'B', ' ', ' ', ' ', ' ', ' ',
		' ', ' ', ' ', ' ', ' ', ' ', 'p', ' ',
		' ', ' ', ' ', ' ', 'p', ' ', ' ', 'k',
		' ', ' ', ' ', ' ', 'P', ' ', ' ', 'p',
		' ', 'P', ' ', 'P', 'B', 'P', ' ', 'P',
		'R', 'H', 'B', 'Q', 'K', ' ', 'H', 'R'
		});

	for (int row = 0; row < 8; row++)
		for (int column = 0; column < 8; column++)
		{
			if (board.Get({ row,column }) && game.GetBoard()->GetElement({ row, column }))
				EXPECT_TRUE(board.Get({ row,column })->Is(game.GetBoard()->GetElement({ row, column })->GetType()));
		}
	EXPECT_TRUE(game.GetTurn() == EColor::BLACK);
}

