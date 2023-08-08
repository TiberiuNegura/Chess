#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <vector>
#include "ITimerListener.h"

using TimerWeakPtr = std::weak_ptr<class ITimerListener>;
using TimerListenerList = std::vector<TimerWeakPtr>;

class Timer {
public:
	Timer();
	Timer(const Timer& other);

	Timer& operator=(const Timer& other)
	{
		if (&other != this)
		{
			std::unique_lock<std::mutex> lock_this(m_timerMutex, std::defer_lock);
			std::unique_lock<std::mutex> lock_other(other.m_timerMutex, std::defer_lock);

			std::lock(lock_this, lock_other);
		}
		return *this;
	}


	void Start(int durationMilliseconds);
	void PlayPause();
	void Stop();

	size_t GetListenerSize() const;


	~Timer();

	void AddListener(TimerWeakPtr listener);
	void RemoveListener(ITimerListener* listener);
	void Notify();
private:
	mutable std::mutex m_timerMutex;
	std::condition_variable m_timerCondVariable;
	std::thread m_timerThread;
	bool m_isRunning;
	bool m_isPaused;
	TimerListenerList m_listeners;

};