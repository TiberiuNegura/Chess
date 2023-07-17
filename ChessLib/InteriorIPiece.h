#pragma once

#include "IPiece.h"

class InteriorIPiece : public IPiece
{
public:
	virtual std::vector<PositionList> CreatePattern() const = 0;
	
	// Getters
	virtual char GetName() const = 0;
	virtual Color GetColor() const override = 0;
	virtual Type GetType() const override = 0; 
	virtual Position GetPosition() const = 0;

	// Setters
	virtual void SetPosition(Position position) = 0;

	// Destructor
	virtual ~InteriorIPiece() = default;
};

