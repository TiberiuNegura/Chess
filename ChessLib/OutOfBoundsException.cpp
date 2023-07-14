#include "OutOfBoundsException.h"

OutOfBoundsException::OutOfBoundsException() : message("Matrix indices are out of bounds.")
{
}

std::string OutOfBoundsException::GetMessage() const
{
    return message;
}
