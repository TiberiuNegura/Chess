#pragma once

#include "PieceInterface.h"

enum class Color {
	WHITE,
	BLACK,
	NONE
};

class Piece : public PieceInterface
{
	public:
		Piece(
			char name = '*',
			int row = 0,
			int column = 0,
			Color color = Color::NONE
		);
		char getName()
		{
			return m_name;
		}



		virtual ~Piece() = default;
	protected:
		char m_name;
		std::pair<int, int> m_position;
		Color m_color;


};

