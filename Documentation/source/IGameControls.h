#pragma once

/**
 * @brief The interface for controlling the state of a game.
 *
 * This interface defines methods for starting, pausing, resuming, stopping, and restarting a game.
 */
class IGameControls
{
public:
	/**
	* @brief Starts the game.
	*
	* This method initiates the game and transitions it into an active state.
	*/
	virtual void Start() = 0;
	/**
	* @brief Pauses the game.
	*
	* This method pauses the game, temporarily halting any ongoing gameplay.
	*/
	virtual void Pause() = 0;
	/**
	 * @brief Resumes the game.
	 *
	 * This method resumes the game from a paused state, allowing gameplay to continue.
	 */
	virtual void Resume() = 0;
	/**
	 * @brief Stops the game.
	 *
	 * This method stops the game and brings it to a complete halt.
	 */
	virtual void Stop() = 0;
	/**
	 * @brief Restarts the game.
	 *
	 * This method restarts the game, resetting it to its initial state.
	 */
	virtual void Restart() = 0;
};