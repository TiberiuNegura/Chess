#include "Position.h"

const Position Position::EMPTY = Position(-1, -1);

Position::Position(int x /*= -1*/, int y /*= -1*/)
	: first(x)
	, second(y)
{

}

bool Position::IsValid() const
{
	return first >= 0 && first < 8 && second >= 0 && second < 8;
}

bool Position::operator!=(const Position& other) const
{
	return !(*this == other);
}

bool Position::operator==(const Position& other) const
{
	return first == other.first && second == other.second;
}