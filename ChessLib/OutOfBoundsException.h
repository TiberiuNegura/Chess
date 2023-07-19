#pragma once

#include "ChessException.h"

class OutOfBoundsException : public ChessException
{
public:
	OutOfBoundsException();
};

