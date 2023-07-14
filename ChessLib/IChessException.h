#pragma once

#include <exception>
#include <string>

class IChessException : public std::exception
{
public:
	virtual std::string GetMessage() const = 0;
};