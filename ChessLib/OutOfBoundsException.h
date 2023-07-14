#pragma once

#include "IException.h"
#include <string>

class OutOfBoundsException : public IChessException
{
public:
	OutOfBoundsException();
	// Inherited via Exception
	virtual std::string GetMessage() const override;
private:
	std::string message;
};

