#include "PGN.h"
#include <gtest/gtest.h>

TEST(PGNTest, LoadValidPGNFile)
{
	PGN pgn;
	EXPECT_TRUE(pgn.Load("files/valid.pgn"));
}

TEST(PGNTest, LoadInvalidPGNFile)
{
	PGN pgn;
	EXPECT_FALSE(pgn.Load("files/invdsalid.pgn"));
}

TEST(PGNTest, SaveValidPGNFile)
{
	PGN pgn;
	
	pgn.SetHeader(EHeaderType::Event, "Chess Tournament");
	pgn.SetHeader(EHeaderType::Site, "City");
	pgn.SetHeader(EHeaderType::Date, "2023.08.10");
	pgn.SetHeader(EHeaderType::Round, "1");
	pgn.SetHeader(EHeaderType::White, "Player1");
	pgn.SetHeader(EHeaderType::Black, "Player2");
	pgn.SetHeader(EHeaderType::Result, "1-0");

	pgn.Add("e4");
	pgn.Add("e5");
	pgn.Add("Hf3");

	std::string filePath = "files/save.pgn";
	EXPECT_TRUE(pgn.Save(filePath));
}

TEST(PGNTest, Add)
{
	PGN pgn;
	pgn.Add("e4");
	EXPECT_EQ(pgn.ComputeMovesPgn(), "1. e4 ");
	pgn.Add("e5");
	EXPECT_EQ(pgn.ComputeMovesPgn(), "1. e4 e5 ");
}

TEST(PGNTest, SetHeadersAndGetMoves)
{
	PGN pgn;

	pgn.SetHeader(EHeaderType::Event, "Chess Tournament");
	pgn.SetHeader(EHeaderType::Site, "City");
	pgn.SetHeader(EHeaderType::Date, "2023.08.10");
	pgn.SetHeader(EHeaderType::Round, "1");
	pgn.SetHeader(EHeaderType::White, "Player1");
	pgn.SetHeader(EHeaderType::Black, "Player2");
	pgn.SetHeader(EHeaderType::Result, "1-0");

	pgn.Add("e4");
	pgn.Add("e5");
	pgn.Add("Hf3");
	pgn.Add("Hc6");

	std::vector<std::string> expectedMoves = { "e4", "e5", "Hf3", "Hc6" };
	EXPECT_EQ(pgn.GetMoves(), expectedMoves);
}

TEST(PGNTest, ClearPGN)
{
	PGN pgn;

	pgn.Add("e4");
	pgn.Add("e5");
	pgn.Add("Hf3");
	pgn.Add("Hc6");

	pgn.Clear();
	EXPECT_TRUE(pgn.ComputeMovesPgn().empty());
}
// there is still work to be done here