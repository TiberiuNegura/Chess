#pragma once

#include "IPiece.h"

class Piece : public IPiece
{
public:
	// Constructor
	Piece(char name = '*', EColor color = EColor::NONE, EType type = EType::EMPTY);
	
	// Destructor
	virtual ~Piece() = default;

	// Getters
	virtual std::vector<PositionList> GetDirections(Position pos) const = 0;
	char GetName() const override;
	EColor GetColor() const override;
	EType GetType() const override;
protected:
	char m_name;
	EColor m_color;
	EType m_type;

};

