#pragma once

class ITimerListener
{
public:

	virtual void OnSecondPass() = 0;


	virtual ~ITimerListener() = default;
};