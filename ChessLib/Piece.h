#pragma once

#include "PieceInterface.h"


class Piece : public PieceInterface
{
	public:
		Piece(
			char name = '*',
			int row = 0,
			int column = 0,
			Color color = Color::NONE,
			Type type = Type::EMPTY
		);
		char getName() override;
		Color getColor() override;
		Type getType() override;
		Position getPosition() override;


		virtual ~Piece() = default;
	protected:
		char m_name;
		Position m_position;
		Color m_color;
		Type m_type;
		static bool IsOutOfBounds(int row, int column);


};

