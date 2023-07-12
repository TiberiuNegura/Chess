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
		char getName()
		{
			return m_name;
		}
		int getColor()
		{
			return (int)m_color;
		}



		virtual ~Piece() = default;
	protected:
		char m_name;
		std::pair<int, int> m_position;
		Color m_color;
		Type m_type;


};

