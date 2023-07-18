#include "PieceNotFoundException.h"


PieceNotFoundException::PieceNotFoundException() : message("[Piece Not Found] The piece is not on the game board.")
{
}

std::string PieceNotFoundException::GetMessage() const
{
	return message;
}
