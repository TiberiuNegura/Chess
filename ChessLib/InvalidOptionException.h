#pragma once
#include "ChessException.h"
class InvalidOptionException : public ChessException
{
public:
	InvalidOptionException();
};

