#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"

// Constructor
Queen::Queen(
	int row,
	int column,
	Color color
): Piece('Q', row, column, color, Type::QUEEN)
{ }

std::vector<PositionList> Queen::CreatePattern() const 
{
	std::unique_ptr<Bishop> b = std::make_unique<Bishop>(m_position.first, m_position.second);
	std::unique_ptr<Rook> r = std::make_unique<Rook>(m_position.first, m_position.second);
	std::vector<PositionList> bishopPattern = b->CreatePattern();
	std::vector<PositionList> rookPattern = r->CreatePattern();
	bishopPattern.insert(bishopPattern.end(), rookPattern.begin(), rookPattern.end()); // concatenates rook pattern into bishop's pattern, resulting the queen's pattern
	return bishopPattern; 
}


