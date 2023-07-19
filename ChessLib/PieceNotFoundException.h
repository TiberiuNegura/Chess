#pragma once

#include "ChessException.h"

class PieceNotFoundException : public ChessException
{
public:
	PieceNotFoundException();
};

