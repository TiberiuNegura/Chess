#pragma once

#include <chrono>
using namespace std::chrono;

class ITimerListener
{
public:

	virtual void OnTimerTick(milliseconds blackRemaining, milliseconds whiteRemaining) = 0;


	virtual ~ITimerListener() = default;
};