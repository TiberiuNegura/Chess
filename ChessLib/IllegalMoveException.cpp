#include "IllegalMoveException.h"

IllegalMoveException::IllegalMoveException(): message("Illegal move. The move is not allowed.")
{
}

std::string IllegalMoveException::GetMessage() const
{
    return message;
}
