#include "Timer.h"

Timer::Timer() : isRunning(false), isPaused(false)
{

}

void Timer::Start(int durationMilliseconds)
{
	std::unique_lock<std::mutex> lock(mutex_);

	if (isRunning) {
		return;
	}

	isRunning = true;
	isPaused = true;
	thread_ = std::thread([this, durationMilliseconds]() {
		std::chrono::milliseconds interval(durationMilliseconds);

		while (isRunning) {
			std::this_thread::sleep_for(interval);
			if (!isPaused) {
				Notify();
			}
		}

		{
			std::unique_lock<std::mutex> lock(mutex_);
			isRunning = false;
			cv_.notify_one();
		}
		});
}

void Timer::PlayPause()
{
	isPaused = !isPaused;
}

void Timer::Stop()
{
	m_listeners.clear();
	{
		std::unique_lock<std::mutex> lock(mutex_);
		isRunning = false;
		cv_.notify_one();
	}

	if (thread_.joinable()) {
		thread_.join();
	}
}

void Timer::Wait()
{
	std::unique_lock<std::mutex> lock(mutex_);
	cv_.wait(lock, [this]() { return !isRunning; });
}

size_t Timer::GetListenerSize() const
{
	return m_listeners.size();
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