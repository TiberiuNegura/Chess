#include "Game.h"
#include "IPiece.h"
#include "IGameListener.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::_;


void MakeMovesFrom(std::vector<std::pair<Position, Position>>& moves, Game& game)
{
	for (auto move : moves)
		EXPECT_NO_THROW(game.MovePiece(move.first, move.second));
	moves.clear();
}

class MockObserver : public IGameListener
{
public:
	MOCK_METHOD(void, OnGameOver, (), (override));
	MOCK_METHOD(void, OnCheck, (std::string msg), (override));
	MOCK_METHOD(void, OnPawnEvolve, (), (override));
	MOCK_METHOD(void, OnTieRequest, (), (override)); //
	MOCK_METHOD(void, OnMovePiece, (Position start, Position end), (override));
	MOCK_METHOD(void, OnRestart, (), (override));
	MOCK_METHOD(void, OnPieceCapture, (EType pieceType, EColor pieceColor), (override));
};

class GameMockTests : public ::testing::Test
{
protected:
	void SetUp()
	{
		mock = std::make_shared<MockObserver>();
	}

protected:
	std::shared_ptr<MockObserver> mock;
	std::string msg;
};

TEST_F(GameMockTests, NotifyObserverMove)
{
	EXPECT_CALL(*mock, OnMovePiece(_, _)).Times(2);

	Game game;
	Game game2;

	game.AddListener(mock);
	game2.AddListener(mock);

	game.MovePiece({ 6,0 }, { 5,0 });
	game2.MovePiece({ 6,0 }, { 5,0 });
}

TEST_F(GameMockTests, AddRemoveListenerTest)
{
	Game game;
	Game game2;
	EXPECT_CALL(*mock, OnMovePiece(_, _)).Times(3);

	game.AddListener(mock);
	game2.AddListener(mock);

	game.MovePiece({ 6,0 }, { 5,0 });
	game2.MovePiece({ 6,0 }, { 5,0 });

	game.RemoveListener(mock.get());

	game.MovePiece({ 1,0 }, { 2,0 });
	game2.MovePiece({ 1,0 }, { 2,0 });
}


TEST_F(GameMockTests, NotifyObserverGameOverCheckmate)
{
	Game game({
	'r', 'h', 'b', 'q', 'k', 'b', 'h', 'r',
	'p', 'p', 'p', 'p', ' ', 'p', 'p', 'p',
	' ', ' ', ' ', ' ', 'p', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ', ' ', 'P', ' ',
	' ', ' ', ' ', ' ', ' ', 'P', ' ', ' ',
	'P', 'P', 'P', 'P', 'P', ' ', ' ', 'P',
	'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R'
		}, EColor::BLACK, EGameState::Playing);

	game.AddListener(mock);

	EXPECT_CALL(*mock, OnMovePiece(_, _)).Times(1);
	EXPECT_CALL(*mock, OnCheck(::_));
	EXPECT_CALL(*mock, OnGameOver()).Times(1);


	game.MovePiece({ 0,3 }, { 4,7 });

	EXPECT_TRUE(game.IsGameOver());
	EXPECT_EQ(game.GetState(), EGameState::BlackWon);
}

TEST_F(GameMockTests, NotifyObserverGameOverTie)
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

	game.AddListener(mock);

	EXPECT_CALL(*mock, OnMovePiece(_, _)).Times(1);
	EXPECT_CALL(*mock, OnGameOver()).Times(1);

	game.MovePiece({ 4,1 }, { 4,2 });

	EXPECT_EQ(game.GetState(), EGameState::Tie);
}

TEST_F(GameMockTests, NotifyObserverRestart)
{
	auto game = IGame::Produce();
	game->AddListener(mock);

	EXPECT_CALL(*mock, OnRestart()).Times(1);

	game->Restart();
}

TEST_F(GameMockTests, NotifyObserverPawnEvolve)
{
	Game game({
	'r', ' ', ' ', 'q', 'k', 'b', 'h', 'r',
	'p', 'P', ' ', 'p', 'p', 'p', 'p', 'p',
	' ', ' ', 'h', ' ', ' ', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	'P', 'P', ' ', 'P', 'P', 'P', 'P', 'P',
	'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R'
		}, EColor::WHITE, EGameState::Playing);

	game.AddListener(mock);

	EXPECT_CALL(*mock, OnMovePiece(_, _)).Times(1);
	EXPECT_CALL(*mock, OnPawnEvolve()).Times(1);

	game.MovePiece({ 1,1 }, { 0,1 });
}

TEST_F(GameMockTests, NotifyObserverCheck)
{
	Game game({
	'r', 'h', 'b', 'q', 'k', 'b', 'h', 'r',
	' ', 'p', 'p', 'p', ' ', 'p', 'p', 'p',
	'p', ' ', ' ', ' ', 'p', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ', ' ', 'P', ' ',
	' ', ' ', ' ', ' ', 'P', 'P', ' ', ' ',
	'P', 'P', 'P', 'P', ' ', ' ', ' ', 'P',
	'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R'
		}, EColor::BLACK, EGameState::Playing);

	game.AddListener(mock);

	EXPECT_CALL(*mock, OnMovePiece(_, _)).Times(2);
	EXPECT_CALL(*mock, OnCheck(_)).Times(1);

	game.MovePiece({ 0,3 }, { 4,7 });
	game.MovePiece({ 7,4 }, { 6,4 });

	EXPECT_EQ(game.GetState(), EGameState::Playing);
}

TEST_F(GameMockTests, NotifyObserverTieRequest)
{
	Game game({
	'r', 'h', 'b', 'q', 'k', 'b', 'h', 'r',
	' ', 'p', 'p', 'p', ' ', 'p', 'p', 'p',
	'p', ' ', ' ', ' ', 'p', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ', ' ', 'P', ' ',
	' ', ' ', ' ', ' ', 'P', 'P', ' ', ' ',
	'P', 'P', 'P', 'P', ' ', ' ', ' ', 'P',
	'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R'
		}, EColor::BLACK, EGameState::Playing);

	game.AddListener(mock);
	EXPECT_CALL(*mock, OnTieRequest);

	game.MakeTieRequest();
}

TEST_F(GameMockTests, NotifyObserver)
{
	Game game;
	game.AddListener(mock);

	EXPECT_CALL(*mock, OnMovePiece).Times(25);
	EXPECT_CALL(*mock, OnCheck).Times(4);
	EXPECT_CALL(*mock, OnPawnEvolve).Times(1);
	EXPECT_CALL(*mock, OnRestart).Times(1);
	EXPECT_CALL(*mock, OnGameOver).Times(1);

	std::vector<std::pair<Position, Position>> moves = {
		{{6,3},{4,3}},{{1,4},{3,4}},{{7,4},{6,3}},{{0,3},{3,6}}, // black checks white
	};
	MakeMovesFrom(moves, game);

	EXPECT_THROW(game.MovePiece({ 3,6 }, { 9,12 }), OutOfBoundsException);
	EXPECT_THROW(game.MovePiece({ 7,7 }, { 6,6 }), CheckException);

	moves = {
		{{6,4},{5,4}},{{3,6},{5,4}},{{6,3},{5,4}},{{0,4},{1,4}},
		{{7,3},{5,3}},{{0,1},{2,2}},{{6,0},{4,0}},{{2,2},{4,1}},
		{{4,0},{3,0}},{{1,1},{2,1}},{{3,0},{2,1}},{{0,2},{2,0}},
		{{2,1},{1,2}},{{1,4},{2,5}},{{1,2},{0,2}}
	}; // pawn evolve

	MakeMovesFrom(moves, game);
	game.EvolvePawn(EType::QUEEN);

	moves = {
		{{4,1},{5,3}},{{0,2},{2,2}} // white checks black
	};

	MakeMovesFrom(moves, game);
	EXPECT_THROW(game.MovePiece({ 7,2 }, { 3,6 }), CheckException);

	game.Restart();

	moves = {
		{{6,6},{4,6}},{{1,4},{2,4}},{{6,5},{5,5}},{{0,3},{4,7}} // black checkmate white
	};
	MakeMovesFrom(moves, game);
}