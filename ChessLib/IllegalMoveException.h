#pragma once

#include "ChessException.h"

class IllegalMoveException : public ChessException
{
public:
	IllegalMoveException();

};

