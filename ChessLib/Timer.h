#include "ITimerListener.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <vector>

using TimerWeakPtr = std::weak_ptr<class ITimerListener>;
using TimerListenerList = std::vector<TimerWeakPtr>;

class Timer 
{
public:
	Timer();

	Timer(const Timer& other) = delete;
	Timer& operator=(const Timer& other) = delete;

	~Timer();

	void Start();
	void Pause();
	void Resume();
	void Stop();

	bool HadStarted() const;
	bool IsPaused() const;


	void AddListener(TimerWeakPtr listener);
	void RemoveListener(ITimerListener* listener);
	
	void Notify();

private:
	std::thread m_timerThread;
	std::condition_variable m_timerCondVariable;
	mutable std::mutex m_timerMutex;

	bool m_isRunning;
	bool m_isPaused;

	TimerListenerList m_listeners;
};