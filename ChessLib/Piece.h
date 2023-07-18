#pragma once

#include "InteriorIPiece.h"

class Piece : public InteriorIPiece
{
public:
	// Constructor
	Piece(
		char name = '*',
		int row = 0,
		int column = 0,
		EColor color = EColor::NONE,
		EType type = EType::EMPTY
	);
	
	// Destructor
	virtual ~Piece() = default;

	// Getters
	char GetName() const override;
	EColor GetColor() const override;
	EType GetType() const override;
	Position GetPosition() const override;

	// Setters
	void SetPosition(Position position);
protected:
	char m_name;
	Position m_position;
	EColor m_color;
	EType m_type;

};

