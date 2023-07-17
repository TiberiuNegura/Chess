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
		Color color = Color::NONE,
		Type type = Type::EMPTY
	);
	
	// Destructor
	virtual ~Piece() = default;

	// Getters
	char GetName() const override;
	Color GetColor() const override;
	Type GetType() const override;
	Position GetPosition() const override;

	// Setters
	void SetPosition(Position position);
protected:
	char m_name;
	Position m_position;
	Color m_color;
	Type m_type;

};

