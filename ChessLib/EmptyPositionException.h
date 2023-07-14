#pragma once

#include "IChessException.h"

class EmptyPositionException : public IChessException
{
public:
	EmptyPositionException();
	// Inherited via Exception
	virtual std::string GetMessage() const override;
private:
	std::string message;
};

