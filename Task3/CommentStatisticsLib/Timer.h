// by Klepatskyi Oleh
#ifndef _KLEPATSKYI_TIMER_H_
#define _KLEPATSKYI_TIMER_H_

#include <chrono>

class Timer {
	using microseconds = std::chrono::microseconds;
	using system_clock = std::chrono::system_clock;
private:
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

#endif
