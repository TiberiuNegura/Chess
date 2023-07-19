#pragma once

#include <stdexcept>
#include <string>

class ChessException : public std::runtime_error
{
public:
	ChessException(const std::string& error = "Problem occured");
};