#include "PGN.h"

#include <fstream>
#include <sstream>

static const std::vector<std::string> HEADER_FIELDS = { "Event", "Site", "Date", "Round", "White", "Black", "Result" };

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

std::string PGN::GetFullPgn() const
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
			ParseTags(line);
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
			fileRead << "[" + HEADER_FIELDS[(int)header.first] + " \"" + header.second + "\"]\n";
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
	m_headers[EHeaderType::Event] = event;
	return this;
}

PGN* PGN::SetSite(std::string site)
{
	m_headers[EHeaderType::Site] = site;
	return this;
}

PGN* PGN::SetDate(std::string date)
{
	m_headers[EHeaderType::Date] = date;
	return this;
}

PGN* PGN::SetRound(std::string round)
{
	m_headers[EHeaderType::Round] = round;
	return this;
}

PGN* PGN::SetWhite(std::string firstName, std::string lastName)
{
	m_headers[EHeaderType::White] = lastName + ", " + firstName;
	return this;
}

PGN* PGN::SetBlack(std::string firstName, std::string lastName)
{
	m_headers[EHeaderType::White] = lastName + ", " + firstName;
	return this;
}

PGN* PGN::SetResult(std::string result)
{
	m_headers[EHeaderType::Result] = result;
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

void PGN::Clear()
{
	m_headers.clear();
	m_moves.clear();
	m_pgn.clear();
}

MoveCollection PGN::GetMoves() const
{
	return m_moves;
}

EHeaderType PGN::ParseHeaderName(const std::string& headerName)
{
	for (int index = 0; index < HEADER_FIELDS.size(); index++)
		if (HEADER_FIELDS[index] == headerName)
			return (EHeaderType)index;

	return EHeaderType::Unknown;
}

void PGN::ParseTags(const std::string& tagText)
{
	FieldsCollection fields;
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
			EHeaderType header = ParseHeaderName(line.substr(1, pos - 1));

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