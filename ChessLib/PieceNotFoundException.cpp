#include "PieceNotFoundException.h"


PieceNotFoundException::PieceNotFoundException() 
	: ChessException("[Piece Not Found] The piece is not on the game board.")
{

}

