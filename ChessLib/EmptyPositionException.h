#pragma once

#include "ChessException.h"

class EmptyPositionException : public ChessException
{
public:
	EmptyPositionException();
};

