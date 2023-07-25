#pragma once

class IGameListener
{
public:

	virtual void OnGameOver() = 0;
	virtual void OnCheck() = 0;
	virtual void OnPawnEvolve() = 0;
	virtual void OnTieRequest() = 0;
	virtual void OnMovePiece() = 0;


	virtual ~IGameListener() = default;
};