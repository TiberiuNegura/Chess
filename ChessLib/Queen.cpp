#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"

// Constructor
Queen::Queen(EColor color)
	: Piece('Q', color, EType::QUEEN)
{ 

}

Directions Queen::GetDirections(Position pos) const
{
	std::unique_ptr<Bishop> b = std::make_unique<Bishop>();
	std::unique_ptr<Rook> r = std::make_unique<Rook>();
	Directions bishopPattern = b->GetDirections(pos);
	Directions rookPattern = r->GetDirections(pos);
	bishopPattern.insert(bishopPattern.end(), rookPattern.begin(), rookPattern.end()); // concatenates rook pattern into bishop's pattern, resulting the queen's pattern
	return bishopPattern; 
}


