#ifndef _KLEPATSKYI_TIMER_H_
#define _KLEPATSKYI_TIMER_H_

#include <chrono>
#include <iostream>

class Timer {
	using milliseconds = std::chrono::milliseconds;
	using system_clock = std::chrono::system_clock;
private:
	milliseconds start;
public:
	Timer() : start(std::chrono::duration_cast<milliseconds>(system_clock::now().time_since_epoch()))
	{}

	void stop()
	{
		milliseconds end = std::chrono::duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		std::cout << "Process took " << (end.count() - start.count()) << " ms\n";
	}
};

#endif
