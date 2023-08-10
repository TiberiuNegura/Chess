#include "Timer.h"

#include <chrono>

using namespace std::chrono_literals;

Timer::Timer() 
	: m_isRunning(false) 
	, m_isPaused(false)
{

}

void Timer::Start()
{
	if (m_isRunning)
		return;

	m_isRunning = true;
	m_isPaused = false;
	m_timerThread = std::thread([this]()
	{
		std::chrono::milliseconds interval(10ms);
		while (m_isRunning)
		{
			if (!m_isPaused)
				Notify();

			std::unique_lock<std::mutex> lock(m_timerMutex);
			m_timerCondVariable.wait_for(lock, interval, [&] { return !m_isRunning; });
		}
	});
}

void Timer::Resume()
{
	m_isPaused = false;
}

void Timer::Pause()
{
	m_isPaused = true;
}

void Timer::Stop()
{
	m_listeners.clear();

	{
		std::unique_lock<std::mutex> lock(m_timerMutex);
		m_isRunning = false;
		m_timerCondVariable.notify_one();
	}

	if (m_timerThread.joinable())
		m_timerThread.join();
}


bool Timer::HadStarted() const
{
	return m_listeners.size() != 0;
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
		listener.lock()->OnSecondPass();
}