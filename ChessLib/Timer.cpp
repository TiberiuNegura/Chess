#include "Timer.h"

Timer::Timer(int s_timer, int ms_resolution) 
	: m_isRunning(false) 
	, m_isPaused(false)
	, m_time(1000 * s_timer)
	, m_resolution(ms_resolution)
	, m_blackRemaining(m_time)
	, m_whiteRemaining(m_time)
	, m_turn(ETurn::White)
{

}

void Timer::Start()
{
	if (m_isRunning)
		return;

	Notify(m_blackRemaining, m_whiteRemaining);

	m_isRunning = true;
	m_isPaused = false;
	m_timerThread = std::thread([this]()
	{
		while (m_isRunning)
		{
			time_point<system_clock> start_lock = system_clock::now();
			std::unique_lock<std::mutex> lock(m_timerMutex);
			m_timerCondVariable.wait_for(lock, m_resolution, [&] { return !m_isRunning; });
			time_point<system_clock> end_lock = system_clock::now();
			if (!m_isPaused)
			{
				milliseconds timePass = duration_cast<milliseconds>(end_lock - start_lock);
				m_turn == ETurn::Black ? m_blackRemaining -= timePass : m_whiteRemaining -= timePass;

				Notify(m_whiteRemaining, m_blackRemaining);
			}
			
		}
	});
}

void Timer::Resume()
{
	m_isPaused = false;
}

void Timer::Restart()
{
	m_whiteRemaining = m_time;
	m_blackRemaining = m_time;
	m_isPaused = true;
	Stop();
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


bool Timer::IsEnabled() const
{
	return m_time != 0ms;
}

bool Timer::IsRunning() const
{
	return m_isRunning;
}


bool Timer::IsPaused() const
{
	return m_isPaused;
}

void Timer::SetResolution(milliseconds resolution)
{
	m_resolution = resolution;
}

void Timer::UpdateTurn()
{
	m_turn = (m_turn == ETurn::White ? ETurn::Black : ETurn::White);
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

void Timer::Notify(milliseconds whiteTimer, milliseconds blackTimer)
{
	for (auto listener : m_listeners)
		listener.lock()->OnTimerTick(whiteTimer, blackTimer);
}