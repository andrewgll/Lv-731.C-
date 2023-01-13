// by Klepatskyi Oleh
#ifndef _KLEPATSKYI_TIMER_H_
#define _KLEPATSKYI_TIMER_H_

#include <chrono>

template <class Duration>
class Timer;

using TimerMicro = Timer<std::chrono::microseconds>;

template <class Duration> 
class Timer {
private:
	Duration start;
	bool _running;
public:
	Timer() : start(std::chrono::duration_cast<Duration>(std::chrono::system_clock::now().time_since_epoch())), _running(true)
	{}

	~Timer()
	{
		if (_running)
		{
			stop();
		}
	}

	std::time_t stop()
	{
		Duration end = std::chrono::duration_cast<Duration>(std::chrono::system_clock::now().time_since_epoch());
		_running = false;
		return end.count() - start.count();
	}
};

#endif // _KLEPATSKYI_TIMER_H_
