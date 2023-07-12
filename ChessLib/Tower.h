#pragma once

#include "Piece.h"

class Tower : public Piece
{
	
public:
	void move(std::pair<int, int> destination, std::vector<std::shared_ptr<PieceInterface>>& pieces) override;
	bool isValid(std::pair<int, int> destination) override;


	std::unordered_set<std::pair<int, int>> createPattern() override;

};

