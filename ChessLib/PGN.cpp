#include "PGN.h"

#include <fstream>
#include <sstream>

static const std::vector<std::string> HEADER_FIELDS = { "Event", "Site", "Date", "Round", "White", "Black", "Result" };

PGN::PGN()
{

	SetHeader(EHeaderType::Event, "?");
	SetHeader(EHeaderType::Site, "?");
	SetHeader(EHeaderType::Date, "????.??.??");
	SetHeader(EHeaderType::Round, "?");
	SetHeader(EHeaderType::White, "?");
	SetHeader(EHeaderType::Black, "?");
	SetHeader(EHeaderType::Result, "*");
}

std::string PGN::GetMovesString() const
{
	return m_pgn;
}

PGN* PGN::SetHeader(EHeaderType headerType, const std::string& value)
{
	m_headers[headerType] = value;
	return this;
}

bool PGN::Load(std::string path)
{
	std::ifstream file(path);

	if (!file.good())
		return false;

	std::string line;
	while (std::getline(file, line))
		ParseTags(line);

	return true;
}

bool PGN::Save(std::string path) const
{
	std::ofstream file(path);

	if (!file.good())
		return false;

	for (auto& header : m_headers)
		file << "[" + HEADER_FIELDS[(int)header.first] + " \"" + header.second + "\"]" << std::endl;
	file << std::endl; 
	
	std::string pgnMoves = ComputeMovesPgn();
	pgnMoves.pop_back(); // removes the last empty space

	file << pgnMoves;

	file.close();

	return true;
}

void PGN::Add(std::string move)
{
	m_moves.push_back(move);
}

void PGN::AppendToLastMove(std::string move)
{
	m_moves[m_moves.size() - 1] += move;
}

std::string PGN::ComputeMovesPgn() const
{
	std::string pgn = "";

	for (int i = 0; i < m_moves.size(); i++)
	{
		if (i % 2 == 0)
			pgn += std::to_string(i / 2 + 1) + ". ";

		pgn += ( m_moves[i] + " ");
	}


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