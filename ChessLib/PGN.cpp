#include "PGN.h"

#include <fstream>
#include <sstream>

PGN::PGN()
{
	SetEvent("?");
	SetSite("?");
	SetDate("????.??.??");
	SetRound("?");
	SetWhite("?", "?");
	SetBlack("?", "?");
	SetResult("*");
}


Headers PGN::StringToHeader(std::string key) const
{
	std::string keys[7] = { "Event", "Site", "Date", "Round", "White", "Black", "Result" };
	
	for (int index = 0; index < 7; index++)
		if (keys[index] == key)
			return (Headers) index;
	return Headers::UNKNOWN;
}

void PGN::parseTags(const std::string& tagText) 
{
	Fields fields;
	std::istringstream iss(tagText);
	std::string line;
	std::getline(iss, line);
	
	if (line.empty())
			return;

	if (line[0] == '[')
	{
		line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
		size_t pos = line.find_first_of("\"");

		if (pos != std::string::npos)
		{
			Headers header = StringToHeader(line.substr(1, pos - 1));

			line = line.substr(pos + 1);
			pos = line.find_first_of("\"");

			if (pos != std::string::npos)
			{
				std::string value = line.substr(0, pos);
				m_headers[header] = value;
			}
		}
	}
	else
	{
		m_pgn += line + " ";
	}
}

std::string PGN::Get() const
{
	return m_pgn;
}

bool PGN::Load(std::string path)
{
	std::ifstream file(path);

	if (file.good())
	{
		std::string line;
		while (std::getline(file, line))
			parseTags(line);
		return true;
	}

	return false;
}

bool PGN::Save(std::string path) const
{
	std::ofstream fileRead(path);

	if (fileRead.good())
	{
		for (auto& header : m_headers)
		{
			std::string fields[7] = { "Event", "Site", "Date", "Round", "White", "Black", "Result" };
			fileRead << "[" + fields[(int)header.first] + " \"" + header.second + "\"]\n";
		}
		fileRead << std::endl << GetString();
		return true;
	}

	return false;
}

void PGN::Add(std::string move)
{
	m_moves.push_back(move);
}

void PGN::CompleteLastMove(std::string move)
{
	m_moves[m_moves.size() - 1] += move;
}

PGN* PGN::SetEvent(std::string event)
{
	m_headers[Headers::EVENT] = event;
	return this;
}

PGN* PGN::SetSite(std::string site)
{
	m_headers[Headers::SITE] = site;
	return this;
}

PGN* PGN::SetDate(std::string date)
{
	m_headers[Headers::DATE] = date;
	return this;
}

PGN* PGN::SetRound(std::string round)
{
	m_headers[Headers::ROUND] = round;
	return this;
}

PGN* PGN::SetWhite(std::string firstName, std::string lastName)
{
	m_headers[Headers::WHITE] = lastName + ", " + firstName;
	return this;
}

PGN* PGN::SetBlack(std::string firstName, std::string lastName)
{
	m_headers[Headers::WHITE] = lastName + ", " + firstName;
	return this;
}

PGN* PGN::SetResult(std::string result)
{
	m_headers[Headers::RESULT] = result;
	return this;
}

std::string PGN::GetString() const
{
	std::string pgn = "";
	int counter = 2;
	for (int i = 0; i < m_moves.size(); i++)
	{
		if (i % 2 == 0)
			pgn += std::to_string(counter / 2) + ". ";
		pgn += m_moves[i];
		pgn += " ";

		counter++;
	}
	//pgn.pop_back(); // removes the last empty space

	return pgn;
}

std::string PGN::Back()
{
	return m_moves[m_moves.size() - 1];
}

void PGN::Clear()
{
	m_headers.clear();
	m_moves.clear();
	m_pgn.clear();
}

std::vector<std::string> PGN::GetMoves() const
{
	return m_moves;
}
