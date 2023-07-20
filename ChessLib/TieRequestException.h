#pragma once

#include "ChessException.h"

class TieRequestException : public ChessException
{
public:
	TieRequestException();
};

