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
		char name;
		Position position;
		Color color;
	public:
		Piece(
			char name = '*',
			char row = '0',
			char column = 'A',
			Color color = Color::NONE
		);
		virtual ~Piece() = default;
};

