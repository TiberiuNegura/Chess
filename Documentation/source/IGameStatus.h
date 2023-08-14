#pragma once

#include "IPiece.h"
#include "Position.h"
/**
 * @brief Represents a move from one position to another on the chessboard.
 */
using Move = std::pair<Position, Position>;
/**
 * @brief A list of moves representing a sequence of chess moves.
 */
using MovesList = std::vector<Move>;
/**
 * @brief The interface for accessing elements of a matrix, such as a chessboard.
 *
 * This interface provides methods to retrieve elements (pieces) from a matrix at specific positions.
 */
class IMatrix
{
public:
	/**
	 * @brief Retrieves the element (piece) at the specified position.
	 *
	 * @param element The position of the element to retrieve.
	 * @return A shared pointer to the retrieved element (piece).
	 */
	virtual IPiecePtr GetElement(Position element) = 0;
	/**
	 * @brief Virtual destructor to ensure proper cleanup in derived classes.
	 */
	virtual ~IMatrix() = default;
};
/**
 * @brief A shared pointer to an IMatrix instance.
 */
using MatrixPtr = std::shared_ptr<IMatrix>;
/**
 * @brief The interface for accessing and managing the status of a chess game.
 *
 * This interface provides methods to query various aspects of the game status, such as the current turn,
 * available moves, missing pieces, game-over states, and more.
 */
class IGameStatus
{
public:
	/**
	 * @brief Virtual destructor to ensure proper cleanup in derived classes.
	 */
	virtual ~IGameStatus() = default;
	/**
	 * Checks whether the timer is enabled.
	 *
	 * @return True if the timer is enabled (time is not zero), false otherwise.
	 */
	virtual bool IsTimerEnabled() const = 0;
	/**
	 * @brief Checks if the game has started.
	 *
	 * @return True if the game has started, false otherwise.
	 */
	virtual bool IsStarted() const = 0;
	/**
	 * @brief Checks if the game is currently paused.
	 *
	 * @return True if the game is paused, false otherwise.
	 */
	virtual bool IsPaused() const = 0;
	/**
	 * @brief Gets the color of the player whose turn it is.
	 *
	 * @return The color of the current player's turn.
	 */
	virtual EColor GetTurn() const = 0;
	/**
	* @brief Gets a shared pointer to the matrix (chessboard) of the game.
	*
	* @return A shared pointer to the game's matrix.
	*/
	virtual MatrixPtr GetBoard() const = 0;
	/**
	* @brief Gets a list of valid moves for the specified piece position.
	*
	* @param piecePos The position of the piece for which to retrieve valid moves.
	* @return A list of valid move positions.
	*/
	virtual PositionList GetMoves(Position piecePos) const = 0;
	/**
	* @brief Gets a list of missing pieces for the specified color.
	*
	* @param color The color of the player for which to retrieve missing pieces.
	* @return A list of missing piece types for the specified color.
	*/
	virtual TypeList GetMissingPieces(EColor color) const = 0;
	/**
	 * @brief Gets a list of moves representing the game's moves history.
	 *
	 * @return A list of moves representing the game's history.
	 */
	virtual MovesList GetMovesList() const = 0;
	/**
	* @brief Checks if a pawn is currently eligible for evolution.
	*
	* @return True if a pawn is eligible for evolution, false otherwise.
	*/
	virtual bool IsPawnEvolving() const = 0;
	/**
	 * @brief Checks the current state of the game in order to decide if a tie request has been made in the game.
	 *
	 * @return True if a tie request has been made, false otherwise.
	 */
	virtual bool IsTieRequest() const = 0;
	/**
	* @brief Checks if the current state is a check (one player's king is under threat).
	*
	* @return True if the game is in check, false otherwise.
	*/
	virtual bool IsCheck() const = 0;
	/**
	 * @brief Checks if the game has ended in a tie.
	 *
	 * @return True if the game is a tie, false otherwise.
	 */
	virtual bool IsTie() const = 0;
	/**
	 * @brief Checks if the white player has won the game.
	 *
	 * @return True if the white player has won, false otherwise.
	 */
	virtual bool BlackWon() const = 0;
	/**
	 * @brief Checks if the white player has won the game.
	 *
	 * @return True if the white player has won, false otherwise.
	 */
	virtual bool WhiteWon() const = 0;
	/**
	 * @brief Checks if the game has ended (either in checkmate, stalemate, or a tie).
	 *
	 * @return True if the game has ended, false otherwise.
	 */
	virtual bool IsGameOver() const = 0;


};
