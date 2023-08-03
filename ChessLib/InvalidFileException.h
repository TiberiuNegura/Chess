#pragma once
#include "ChessException.h"
class InvalidFileException : public ChessException
{
public:
	InvalidFileException();
};

