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

	void Start(int durationMilliseconds);


	void PlayPause();

	void Stop();
	void Wait();

	size_t GetListenerSize() const;


	~Timer();

	void AddListener(TimerWeakPtr listener);
	void RemoveListener(ITimerListener* listener);
	void Notify();
private:
	std::mutex mutex_;
	std::condition_variable cv_;
	std::thread thread_;
	bool isRunning;
	bool isPaused;
	TimerListenerList m_listeners;
};