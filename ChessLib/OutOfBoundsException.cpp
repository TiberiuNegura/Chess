#include "OutOfBoundsException.h"

OutOfBoundsException::OutOfBoundsException() : message("[Out Of Bounds] Matrix indices are out of bounds.")
{
}

std::string OutOfBoundsException::GetMessage() const
{
    return message;
}
