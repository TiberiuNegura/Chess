#pragma once

#include <string>
#include <vector>
#include <map>


enum class Headers
{
	EVENT,
	SITE,
	DATE,
	ROUND,
	WHITE,
	BLACK,
	RESULT,
	UNKNOWN
};

using Fields = std::map<Headers, std::string>;

class PGN
{
public:

	PGN();

	bool Load(std::string path);
	void parseTags(const std::string& tagText);
	std::string Get() const;

	bool Save(std::string path) const;
	void Add(std::string move);
	PGN* SetEvent(std::string event);
	PGN* SetSite(std::string site);
	PGN* SetDate(std::string date);
	PGN* SetRound(std::string round);
	PGN* SetWhite(std::string firstName, std::string lastName);
	PGN* SetBlack(std::string firstName, std::string lastName);
	PGN* SetResult(std::string result);
	std::string GetString() const;
	std::vector<std::string> GetMoves() const;

	Headers StringToHeader(std::string header) const;
	std::string Back();

private:
	std::string m_pgn;
	Fields m_headers;
	std::vector<std::string> m_moves;
};

