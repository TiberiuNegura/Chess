#include "Piece.h"


class Pawn : public Piece
{
	public:
		Pawn(
			int row = 0,
			int column = 0,
			Color color = Color::NONE
		);
		// Inherited via PieceInterface
		virtual void move(std::pair<int, int> destination, std::vector<std::shared_ptr<PieceInterface>>& pieces) override;
		virtual bool isValid(std::pair<int, int> destination) override;
		virtual  std::vector<std::pair<int, int>> createPattern() override;
	private:
		//bool isFirstMove;
};
