#pragma once

/**
 * @brief The interface for storing and loading game data using different formats.
 *
 * This interface defines methods for saving and loading game data in different formats,
 * such as PGN (Portable Game Notation) and FEN (Forsyth-Edwards Notation).
 */
class IGameStorage
{
public:
	/**
	* @brief Saves the game data in PGN format to the specified file path.
	*
	* It makes a call to the Save method in a PGN class that handles the file operations
	* such as open, validation, write and close. It also uses the ComputeMovesPgn to put it
	* in the desired format.
	*
	* @param path The file path where the PGN data will be saved.
	* @return True if the data was successfully saved, false otherwise.
	*/
	virtual bool SavePGN(const std::string& path) const = 0;
	/**
	 * @brief Saves the game data in FEN format to the specified file path.
	 *
	 * @param path The file path where the FEN data will be saved.
	 */
	virtual void SaveFEN(const std::string& path) const = 0;
	/**
	* @brief Loads game data from a specified file path and format.
	*
	* This method loads game data from a file in a specific format (e.g., PGN or FEN).
	* Based on the extension (.pgn or .fen) it determines which load method to call and if
	* it is not successful, it reverts back to the current state.
	*
	* Since it simulates the whole game, it may throw some exceptions if the moves are not valid.
	*
	*
	*
	* @param path The file path from which to load the data.
	* @return True if the data was successfully loaded, false otherwise.
	*
	* @throws IllegalMoveException If the move is not allowed by the game rules.
	* @throws GameOverException If the state of the game is either black/white won nor a tie.
	* @throws TieRequestException If a tie proposal has been made and someone tries to move a piece.
	* @throws PawnEvolveException If a pawn is supposed to be upgraded but someone tries to move other piece.
	* @throws EmptyPositionException If an action is requested on a nullptr piece.
	* @throws OutOfBoundsException If start position or the destination is not in the [0,7] interval.
	* @throws CheckException If a player tries to move a piece while in check that does not solve the check state.
	*/
	virtual bool LoadFromFormat(const std::string& path) = 0;
};