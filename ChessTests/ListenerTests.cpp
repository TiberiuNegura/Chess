#include "Game.h"
#include "IPiece.h"
#include "IGameListener.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::_;

class MockObserver : public IGameListener
{
public:
	MOCK_METHOD(void, OnGameOver, (), (override));
	MOCK_METHOD(void, OnCheck, (std::string msg), (override));
	MOCK_METHOD(void, OnPawnEvolve, (), (override));
	MOCK_METHOD(void, OnTieRequest, (), (override)); //
	MOCK_METHOD(void, OnMovePiece, (Position start, Position end, const PositionList& possibleMoves), (override));
	MOCK_METHOD(void, OnRestart, (), (override));
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
	EXPECT_CALL(*mock, OnMovePiece(_, _, _)).Times(2);

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
	EXPECT_CALL(*mock, OnMovePiece(_, _, _)).Times(2);

	game.AddListener(mock);
	game2.AddListener(mock);

	game.MovePiece({ 6,0 }, { 5,0 });
	game2.MovePiece({ 6,0 }, { 5,0 });

	game.RemoveListener(mock.get());

	EXPECT_CALL(*mock, OnMovePiece(_, _, _)).Times(1);


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

	EXPECT_CALL(*mock, OnMovePiece(_, _, _)).Times(1);
	EXPECT_CALL(*mock, OnCheck(::_));
	EXPECT_CALL(*mock, OnGameOver()).Times(1);


	game.MovePiece({ 0,3 }, { 4,7 });

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

	EXPECT_CALL(*mock, OnMovePiece(_, _, _)).Times(1);
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

	EXPECT_CALL(*mock, OnMovePiece(_, _, _)).Times(1);
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

	EXPECT_CALL(*mock, OnMovePiece(_, _, _)).Times(2);
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

}
// TODO: combine exception handling (EXPECT_THROW(...)) and mock with EXPECT_CALL(...).Times(0)