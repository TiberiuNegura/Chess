#pragma once

#include<vector>


/**
 * @brief Represents a two-dimensional position.
 */
struct Position
{
	int first;  ///< The first coordinate (e.g., x-coordinate).
	int second; ///< The second coordinate (e.g., y-coordinate).
	 /**
	 * @brief Constructs a Position object with specified coordinates.
	 *
	 * @param x The first coordinate.
	 * @param y The second coordinate.
	 */
	Position(int x = -1, int y = -1);
	/**
	 * @brief Constructs a Position object with specified floating-point coordinates.
	 *
	 * @param x The first coordinate as a double.
	 * @param y The second coordinate as a double.
	 */
	Position(double x, double y)
		: first(static_cast<int>(x))
		, second(static_cast<int>(y))
	{
	}
	/**
	* @brief Overloads the == operator (checks if the current position is equal to another position).
	*
	* @param other The other Position to compare with.
	* @return True if the positions are equal, false otherwise.
	*/
	bool operator==(const Position& other) const;
	/**
	* @brief Overloads the != operator (checks if the current position is not equal to another position).
	*
	* @param other The other Position to compare with.
	* @return True if the positions are not equal, false otherwise.
	*/
	bool operator!=(const Position& other) const;
	/**
	 * @brief Checks if the position is valid (non-negative coordinates).
	 *
	 * @return True if the position is valid, false otherwise.
	 */
	bool IsValid() const;
	/**
	 * @brief Represents an empty (invalid) Position.
	 */
	static const Position EMPTY;
};
/**
 * @brief A list of Position objects.
 */
using PositionList = std::vector<Position>;
/**
 * @brief A list of PositionList objects, representing directions.
 */
using Directions = std::vector<PositionList>;