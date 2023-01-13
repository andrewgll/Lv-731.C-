// by Klepatskyi Oleh
#ifndef _KLEPATSKYI_TIMER_H_
#define _KLEPATSKYI_TIMER_H_

#ifdef NDEBUG

class Timer {
public:
	void stop();
};

#else 

#include <chrono>
#include <mutex>

class Timer {
	using microseconds = std::chrono::microseconds;
	using system_clock = std::chrono::system_clock;
private:
	static std::mutex _mutex;
	microseconds start;
	bool _running;
public:
	Timer() : start(std::chrono::duration_cast<microseconds>(system_clock::now().time_since_epoch())), _running(true)
	{}

	~Timer()
	{
		if (_running)
		{
			stop();
		}
	}

	void stop();
};

#endif // NDEBUG
#endif // _KLEPATSKYI_TIMER_H_
