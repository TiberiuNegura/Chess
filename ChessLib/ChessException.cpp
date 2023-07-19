#include "ChessException.h"

ChessException::ChessException(const std::string& error) 
	: std::runtime_error(error)
{

}
