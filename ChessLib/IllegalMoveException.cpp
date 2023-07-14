#include "IllegalMoveException.h"

IllegalMoveException::IllegalMoveException() : message("[Illegal Move] The move is not allowed.")
{
}

std::string IllegalMoveException::GetMessage() const
{
    return message;
}
