#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"

// Constructor
Queen::Queen(
	int row,
	int column,
	EColor color
): Piece('Q', row, column, color, EType::QUEEN)
{ }

std::vector<PositionList> Queen::GetDirections() const 
{
	std::unique_ptr<Bishop> b = std::make_unique<Bishop>(m_position.first, m_position.second);
	std::unique_ptr<Rook> r = std::make_unique<Rook>(m_position.first, m_position.second);
	std::vector<PositionList> bishopPattern = b->GetDirections();
	std::vector<PositionList> rookPattern = r->GetDirections();
	bishopPattern.insert(bishopPattern.end(), rookPattern.begin(), rookPattern.end()); // concatenates rook pattern into bishop's pattern, resulting the queen's pattern
	return bishopPattern; 
}


