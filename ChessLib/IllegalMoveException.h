#pragma once
#include "IException.h"
class IllegalMoveException : public IChessException
{
public:
	IllegalMoveException();
	// Inherited via Exception
	virtual std::string GetMessage() const override;
private:
	std::string message;
};

