#pragma once

#include "IPiece.h"

using PiecePtr = std::shared_ptr<class Piece>;

class Piece : public IPiece
{
public:
	// Constructor
	Piece(char name = '*', EColor color = EColor::NONE, EType type = EType::EMPTY);

	static PiecePtr Produce(EType type, EColor color);

	// Getters
	virtual Directions GetDirections(Position pos) const = 0;
	char GetName() const override;
	EColor GetColor() const override;
	EType GetType() const override;
	bool HasMoved() const;

	// Setter
	void SetHasMoved();

	bool Is(EType type, EColor color) const override;
	static bool Is(EType type, const std::vector<EType>& typeList);



protected:
	char m_name;
	EColor m_color;
	EType m_type;
	bool hasMoved;

};

