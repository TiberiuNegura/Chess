#include "ITimerListener.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <vector>

using namespace std::chrono;
using namespace std::chrono_literals;

using TimerWeakPtr = std::weak_ptr<class ITimerListener>;
using TimerListenerList = std::vector<TimerWeakPtr>;


enum class ETurn
{
	Black,
	White
};

class Timer 
{
public:
	Timer(int s_timer = 0, int ms_resolution = 30);

	Timer(const Timer& other) = delete;
	Timer& operator=(const Timer& other) = delete;

	~Timer();

	void Start();
	void Pause();
	void Resume();
	void Restart();
	void Stop();

	milliseconds GetElapsedTime() const;

	bool IsEnabled() const;
	bool IsRunning() const;
	bool IsPaused() const;

	void SetResolution(milliseconds resolution);
	void UpdateTurn();

	void AddListener(TimerWeakPtr listener);
	void RemoveListener(ITimerListener* listener);

	
	void Notify(milliseconds whiteTimer, milliseconds blackTimer);

private:
	std::thread m_timerThread;
	std::condition_variable m_timerCondVariable;
	mutable std::mutex m_timerMutex;

	bool m_isRunning;
	bool m_isPaused;

	ETurn m_turn;

	milliseconds m_time, m_whiteRemaining, m_blackRemaining, m_resolution, m_elapsedTime;

	TimerListenerList m_listeners;
};