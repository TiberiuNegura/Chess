#include "EmptyPositionException.h"

EmptyPositionException::EmptyPositionException(): message("The input provided is an empty position.")
{
}

std::string EmptyPositionException::GetMessage() const
{
	return message;
}
