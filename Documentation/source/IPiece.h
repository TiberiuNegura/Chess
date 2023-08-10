#pragma once

#include <vector>
#include <array>
#include <memory>

/**
 * @brief A shared pointer to an instance of the IPiece class.
 */
using IPiecePtr = std::shared_ptr<class IPiece>;

/**
 * @brief An enumeration representing the color of a chess piece.
 */
enum class EColor {
	WHITE, ///< The white color.
	BLACK, ///< The black color.
	NONE ///< Represents an absence of color.
};

/**
 * @brief An enumeration representing the type of a chess piece.
 */
enum class EType {
	PAWN,   ///< A pawn chess piece.
	ROOK,   ///< A rook chess piece.
	BISHOP, ///< A bishop chess piece.
	HORSE,  ///< A horse (knight) chess piece.
	QUEEN,  ///< A queen chess piece.
	KING,   ///< A king chess piece.
	EMPTY   ///< Represents an empty (no) piece.
};

/**
 * @brief A list of chess piece types.
 */
using TypeList = std::vector<EType>;

/**
 * @brief The interface for a chess piece.
 *
 * This interface defines methods to retrieve information about a chess piece, such as its name,
 * color, and type. It also provides methods to check if a piece matches specific criteria.
 */
class IPiece
{
public:
	/**
	 * @brief Gets the name of the chess piece.
	 *
	 * @return The character representing the name of the piece.
	 */
	virtual char GetName() const = 0;
	/**
	* @brief Gets the color of the chess piece.
	*
	* @return The color of the piece (WHITE or BLACK).
	*/
	virtual EColor GetColor() const = 0;
	/**
	 * @brief Gets the type of the chess piece.
	 *
	 * @return The type of the piece (PAWN, ROOK, HORSE, BISHOP, QUEEN, KING).
	 */
	virtual EType GetType() const = 0;
	/**
	 * @brief Checks if the piece matches a specific type and color.
	 *
	 * @param type The type to check for.
	 * @param color The color to check for.
	 * @return True if the piece matches the specified type and color, false otherwise.
	 */
	virtual bool Is(EType type, EColor color) const = 0;
	/**
	 * @brief Checks if the piece matches a specific type.
	 *
	 * @param type The type to check for.
	 * @return True if the piece matches the specified type, false otherwise.
	 */
	virtual bool Is(EType type) const = 0;
	/**
	 * @brief Checks if the piece matches a specific color.
	 *
	 * @param color The color to check for.
	 * @return True if the piece matches the specified color, false otherwise.
	 */
	virtual bool Is(EColor color) const = 0;
	/**
	 * @brief Checks if the piece matches any of the types in the given list.
	 *
	 * @param typeList The list of types to check against.
	 * @return True if the piece matches any of the specified types, false otherwise.
	 */
	virtual bool Is(const std::vector<EType>& typeList) const = 0;

	/**
	* @brief Virtual destructor to ensure proper cleanup in derived classes.
	*/
	virtual ~IPiece() = default;
};

