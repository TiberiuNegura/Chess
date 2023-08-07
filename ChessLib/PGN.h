#pragma once

#include <string>
#include <vector>
#include <map>


enum class EHeaderType
{
	Event,
	Site,
	Date,
	Round,
	White,
	Black,
	Result,
	Unknown
};

using MoveString = std::string;
using MoveCollection = std::vector<MoveString>;
using FieldsCollection = std::map<EHeaderType, std::string>;

class PGN
{
public:

	PGN();

	// LOADING
	bool Load(std::string path);

	std::string GetFullPgn() const;

	// CREATING A NEW PGN
	// TODO PGN* SetHeader(EHeaderType headerType, const std::string& value); 
	PGN* SetEvent(std::string event);
	PGN* SetSite(std::string site);
	PGN* SetDate(std::string date);
	PGN* SetRound(std::string round);
	PGN* SetWhite(std::string firstName, std::string lastName);
	PGN* SetBlack(std::string firstName, std::string lastName);
	PGN* SetResult(std::string result);

	void Add(std::string move);
	void AppendToLastMove(std::string move);


	bool Save(std::string path) const;
	
	// ??????????????
	std::string ComputeMovesPgn() const;
	
	// FOR BOTH
	MoveCollection GetMoves() const;

	void Clear();

private:

	static EHeaderType ParseHeaderName(const std::string& header);
	
	void ParseTags(const std::string& tagText);

private:
	std::string m_pgn;

	FieldsCollection m_headers;
	MoveCollection m_moves;
};

