#include "Game.h"
#include "IPiece.h"
#include "IGameListener.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

class MockObserver : public IGameListener
{
public:
	MOCK_METHOD(void, OnGameOver, (), (override));
	MOCK_METHOD(void, OnCheck, (CheckException e), (override));
	MOCK_METHOD(void, OnPawnEvolve, (), (override));
	MOCK_METHOD(void, OnTieRequest, (), (override));
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
};

TEST_F(GameMockTests, NotifyObserverMove)
{
	EXPECT_CALL(*mock, OnMovePiece(testing::_, testing::_, testing::_)).Times(2);

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
	EXPECT_CALL(*mock, OnMovePiece(testing::_, testing::_, testing::_)).Times(2);

	game.AddListener(mock);
	game2.AddListener(mock);

	game.MovePiece({ 6,0 }, { 5,0 });
	game2.MovePiece({ 6,0 }, { 5,0 });

	game.RemoveListener(mock.get());

	EXPECT_CALL(*mock, OnMovePiece(testing::_, testing::_, testing::_)).Times(1);


	game.MovePiece({ 1,0 }, { 2,0 });
	game2.MovePiece({ 1,0 }, { 2,0 });
}

TEST_F(GameMockTests, NotifyObserverGameOver)
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

	EXPECT_CALL(*mock, OnMovePiece(testing::_, testing::_, testing::_)).Times(1);
	EXPECT_CALL(*mock, OnGameOver()).Times(1);

	game.MovePiece({ 0,3 }, { 4,7 });
}