#pragma once

#include "PieceInterface.h"

enum class Color {
	WHITE,
	BLACK,
	NONE
};

class Piece : public PieceInterface
{
	protected:
		char m_name;
		std::pair<int, int> m_position;
		Color m_color;
	public:
		Piece(
			char name = '*',
			int row = 0,
			int column = 0,
			Color color = Color::NONE
		);
		virtual ~Piece() = default;
};

