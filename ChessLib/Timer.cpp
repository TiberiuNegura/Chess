#include "Timer.h"

Timer::Timer() 
	: m_isRunning(false) 
	, m_isPaused(false)
{

}

Timer::Timer(const Timer& other)
	: m_isRunning(other.m_isRunning)
	, m_isPaused(other.m_isPaused)
{
	std::unique_lock<std::mutex> lock_other(other.m_timerMutex);
}

Timer& Timer::operator=(const Timer& other)
{
	if (&other != this)
	{
		std::unique_lock<std::mutex> lock_this(m_timerMutex, std::defer_lock);
		std::unique_lock<std::mutex> lock_other(other.m_timerMutex, std::defer_lock);

		std::lock(lock_this, lock_other);
	}
	return *this;
}

void Timer::Start(int durationMilliseconds)
{
	std::unique_lock<std::mutex> lock(m_timerMutex);

	if (m_isRunning) {
		return;
	}

	m_isRunning = true;
	m_isPaused = true;
	m_timerThread = std::thread([this, durationMilliseconds]() {
		std::chrono::milliseconds interval(durationMilliseconds);

		while (m_isRunning) {
			std::this_thread::sleep_for(interval);
			if (!m_isPaused) {
				Notify();
			}
		}

		{
			std::unique_lock<std::mutex> lock(m_timerMutex);
			m_isRunning = false;
			m_timerCondVariable.notify_one();
		}
		});
}

void Timer::PlayPause()
{
	m_isPaused = !m_isPaused;
}

void Timer::Stop()
{
	m_listeners.clear();
	{
		std::unique_lock<std::mutex> lock(m_timerMutex);
		m_isRunning = false;
		m_timerCondVariable.notify_one();
	}

	if (m_timerThread.joinable()) {
		m_timerThread.join();
	}
}


size_t Timer::GetListenerSize() const
{
	return m_listeners.size();
}


bool Timer::IsPaused() const
{
	return m_isPaused;
}

Timer::~Timer()
{
	Stop();
}

void Timer::AddListener(TimerWeakPtr listener)
{
	m_listeners.push_back(listener);
}

void Timer::RemoveListener(ITimerListener* listener)
{
	m_listeners.erase(
		std::remove_if(
			m_listeners.begin(),
			m_listeners.end(),
			[listener](TimerWeakPtr& weak)
			{
				auto sp = weak.lock();
				return !sp || sp.get() == listener;
			}
	));
}

void Timer::Notify()
{
	for (auto listener : m_listeners)
	{
		listener.lock()->OnSecondPass();
	}
}