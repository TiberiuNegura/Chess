#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <unordered_set>

class PieceInterface
{
public:
		virtual void move(std::pair<int, int> destination, std::vector<std::shared_ptr<PieceInterface>>& pieces) = 0;
		virtual bool isValid(std::pair<int, int> destination) = 0;
		virtual std::unordered_set<std::pair<int, int>> createPattern() = 0;

		virtual ~PieceInterface() = default;

};

