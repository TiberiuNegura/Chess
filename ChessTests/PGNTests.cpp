#include "PGN.h"
#include <gtest/gtest.h>

//// Test loading from a valid PGN file
//TEST(PGNTest, LoadValidPGNFile)
//{
//	PGN pgn;
//	EXPECT_TRUE(pgn.Load("C:/Users/tnegura/Documents/PGN/valid.pgn"));
//	// Add more expectations to validate the loaded data
//}
//
//// Test loading from an invalid PGN file
//TEST(PGNTest, LoadInvalidPGNFile)
//{
//	PGN pgn;
//	EXPECT_FALSE(pgn.Load("C:/Users/tnegura/Documents/PGN/invalid.pgn"));
//}
//
//// Test saving to a valid PGN file
//TEST(PGNTest, SaveValidPGNFile)
//{
//	PGN pgn;
//	// Set up the PGN object with data
//	// ...
//
//	EXPECT_TRUE(pgn.Save("C:/Users/tnegura/Documents/PGN/save.pgn"));
//	// Add more expectations to verify the saved data
//}
//
//// Test adding and completing moves
//TEST(PGNTest, AddAndCompleteMoves)
//{
//	PGN pgn;
//	pgn.Add("e4");
//	EXPECT_EQ(pgn.GetString(), "1. e4 ");
//	pgn.CompleteLastMove("e5");
//	EXPECT_EQ(pgn.GetString(), "1. e4 e5 ");
//	// Add more expectations to test other moves
//}
//
//// Test setting headers and retrieving moves
//TEST(PGNTest, SetHeadersAndGetMoves)
//{
//	PGN pgn;
//
//	pgn.SetEvent("Example Event");
//	pgn.SetSite("Example Site");
//	pgn.SetDate("2023.08.01");
//	pgn.SetRound("1");
//	pgn.SetWhite("John", "Doe");
//	pgn.SetBlack("Jane", "Smith");
//	pgn.SetResult("1-0");
//
//	pgn.Add("e4");
//	pgn.Add("e5");
//	pgn.Add("Nf3");
//	pgn.Add("Nc6");
//
//	std::vector<std::string> expectedMoves = { "e4", "e5", "Nf3", "Nc6" };
//	EXPECT_EQ(pgn.GetMoves(), expectedMoves);
//}
//
//// Test clearing the PGN object
//TEST(PGNTest, ClearPGN)
//{
//	PGN pgn;
//	// Set up the PGN object with data
//	// ...
//	pgn.Clear();
//	EXPECT_TRUE(pgn.GetMoves().empty());
//	EXPECT_TRUE(pgn.Get().empty());
//	// Add more expectations to verify headers are cleared too
//}
// there is still work to be done here