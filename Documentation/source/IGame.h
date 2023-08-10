#pragma once

#include "IGameStatus.h"
#include "IGameListener.h"
#include "IGameControls.h"
#include "IGameStorage.h"

#include "Position.h"
#include "AllChessExceptions.h"

using IGamePtr = std::shared_ptr<class IGame>;

/**
 * @brief The base interface for a chess game.
 *
 * This interface defines the core functionality and methods for interacting with a chess game.
 * It combines aspects related to game controls, storage, and observer/listener management.
 */

class IGame : public IGameControls, public IGameStorage
{
public:
	/**
	 * @brief Creates an instance of the chess game.
	 *
	 * @param timerSeconds The initial time limit for the game in seconds (optional).
	 * @return A shared pointer to the created IGame instance.
	 */
	static IGamePtr Produce(int timerSeconds = 2000);

	virtual ~IGame() = default;

	/**
	 * @brief Adds an observer to the game.
	 *
	 * @param listener A weak pointer to the listener to be added.
	 */
	virtual void AddListener(ListenerWeakPtr listener) = 0;

	/**
	* @brief Removes an observer from the game.
	*
	* @param listener A pointer to the listener to be removed.
	*/
	virtual void RemoveListener(IGameListener* listener) = 0;

	/**
	* @brief Moves a chess piece from the start position to the destination position.
	*
	* @param start The starting position of the piece.
	* @param destination The destination position for the piece.
	* 
	* @throws IllegalMoveException If the move is not allowed by the game rules.
	* @throws GameOverException If the state of the game is either black/white won nor a tie.
	* @throws TieRequestException If a tie proposal has been made and someone tries to move a piece.
	* @throws PawnEvolveException If a pawn is supposed to be upgraded but someone tries to move other piece.
	* @throws EmptyPositionException If an action is requested on a nullptr piece.
	* @throws OutOfBoundsException If start position or the destination is not in the [0,7] interval.
	* @throws CheckException If a player tries to move a piece while in check that does not solve the check state.
	*/
	virtual void MovePiece(Position start, Position destination) = 0;

	/**
	 * @brief Initiates a tie request in the game.
	 */
	virtual void MakeTieRequest() = 0;

	/**
	 * @brief Responds to a tie request.
	 *
	 * @param answer The response to the tie request.
	 */
	virtual void TieRequestResponse(bool answer) = 0;

	/**
	 * @brief Evolves a pawn to a specified piece type.
	 *
	 * @param pieceType The type to which the pawn should be evolved.
	 * @throws PieceNotFoundException If the pawn cannot found.
	 */
	virtual void EvolvePawn(EType pieceType) = 0;

	/**
	* @brief Retrieves the current status of the chess game.
	*
	* @return A const pointer to the IGameStatus object representing the game status.
	*/
	virtual const IGameStatus* Status() const = 0;

	/**
	* @brief Previews the game configuration at a specific move index.
	*
	* @param moveIndex The index of the move for which to preview the configuration.
	*/
	virtual void PreviewPastConfig(int moveIndex) = 0;
};


