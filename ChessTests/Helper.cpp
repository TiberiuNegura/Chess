#include "Helper.h"

bool Helper::ExpectedStatus(PositionList positions, std::unordered_set<Position, IntPairHash> expected)
{
	if (expected.size() != positions.size())
		return false;

	for (auto position : positions)
	{
		EXPECT_NO_THROW(expected.find(position) != expected.end());

		if (expected.find(position) != expected.end())
			expected.erase(position);

	}

	return expected.empty();
}

size_t Helper::IntPairHash::operator()(const Position& p) const
{
	// Use std::hash to get the hashes of both ints
	std::hash<int> hasher;
	size_t hash_first = hasher(p.first);
	size_t hash_second = hasher(p.second);

	// Combine the two hashes using XOR
	return hash_first ^ hash_second;
}
