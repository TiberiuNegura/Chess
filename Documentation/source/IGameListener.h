#pragma once

#include "IPiece.h"

#include <vector>
#include <memory>
#include <string>
#include <chrono>

using TimeSeconds = std::chrono::seconds;

/**
 * @brief The interface for receiving game-related events and notifications.
 *
 * This interface defines methods to be implemented by classes that wish to receive notifications
 * about various events that occur during a game, such as game over, check, pawn evolution, tie requests,
 * piece movement, captures, restarts, and timer ticks.
 */
class IGameListener
{
public:
	/**
	* @brief Called when the game is over.
	*/
	virtual void OnGameOver() = 0;
	/**
	* @brief Called when a check condition is detected.
	*
	* @param msg A message providing additional information about the check.
	*/
	virtual void OnCheck(std::string msg) = 0;
	/**
	* @brief Called when a pawn is eligible for evolution.
	*/
	virtual void OnPawnEvolve() = 0;
	/**
	* @brief Called when a tie request is made.
	*/
	virtual void OnTieRequest() = 0;
	/**
	* @brief Called when a chess piece is moved on the board.
	*
	* @param start The starting position of the moved piece.
	* @param end The destination position of the moved piece.
	*/
	virtual void OnMovePiece(Position start, Position end) = 0;
	/**
	 * @brief Called when a chess piece is captured.
	 *
	 * @param pieceType The type of the captured piece.
	 * @param pieceColor The color of the captured piece.
	 */
	virtual void OnPieceCapture(EType pieceType, EColor pieceColor) = 0;
	/**
	 * @brief Called when the game is restarted.
	 */
	virtual void OnRestart() = 0;
	/**
	 * @brief Called when a timer tick occurs.
	 *
	 * @param whiteTimer The remaining time for the white player.
	 * @param blackTimer The remaining time for the black player.
	 */
	virtual void OnTimerTick(TimeSeconds whiteTimer, TimeSeconds blackTimer) = 0;
	/**
	* @brief Virtual destructor to ensure proper cleanup in derived classes.
	*/
	virtual ~IGameListener() = default;
};
/**
 * @brief A weak pointer to an IGameListener.
 */
using ListenerWeakPtr = std::weak_ptr<IGameListener>;
/**
 * @brief A list of weak pointers to IGameListeners.
 */
using ListenerList = std::vector<ListenerWeakPtr>;