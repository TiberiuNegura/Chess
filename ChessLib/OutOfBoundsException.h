#pragma once

#include "IChessException.h"

class OutOfBoundsException : public IChessException
{
public:
	OutOfBoundsException();
	// Inherited via Exception
	virtual std::string GetMessage() const override;
private:
	std::string message;
};

