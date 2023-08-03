#include "InvalidFileException.h"

InvalidFileException::InvalidFileException() 
	: ChessException("[Invalid File] The file provided cannot be opened.")
{
}
