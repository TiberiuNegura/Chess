#pragma once

#include "IPiece.h"

using PiecePtr = std::shared_ptr<class InteriorIPiece>;

class InteriorIPiece : public IPiece
{
public:
	virtual std::vector<PositionList> GetDirections() const = 0;
	
	// Getters
	virtual char GetName() const = 0;
	virtual EColor GetColor() const override = 0;
	virtual EType GetType() const override = 0; 
	virtual Position GetPosition() const = 0;

	// Setters
	virtual void SetPosition(Position position) = 0;

	// Destructor
	virtual ~InteriorIPiece() = default;
};

