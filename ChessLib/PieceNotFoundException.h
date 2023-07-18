#pragma once

#include "IChessException.h"

class PieceNotFoundException : public IChessException
{
public:
	PieceNotFoundException();
	// Inherited via Exception
	virtual std::string GetMessage() const override;
private:
	std::string message;
};

