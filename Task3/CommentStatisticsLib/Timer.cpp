// by Klepatskyi Oleh
#include "Timer.h"
#include <iostream>

void Timer::stop()
{
	microseconds end = std::chrono::duration_cast<microseconds>(system_clock::now().time_since_epoch());
	std::cout << "Process took " << ((double)(end.count() - start.count()) / 1000) << " ms\n";
	_running = false;
}