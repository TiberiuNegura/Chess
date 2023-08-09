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

	Timer& operator=(const Timer& other);

	void Start(int durationMilliseconds);
	void PlayPause();
	void Stop();

	size_t GetListenerSize() const;

	bool IsPaused() const;


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