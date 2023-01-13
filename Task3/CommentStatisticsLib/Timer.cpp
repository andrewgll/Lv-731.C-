// by Klepatskyi Oleh
#include "Timer.h"



#ifdef NDEBUG

void Timer::stop()
{}

#else 

std::mutex Timer::_mutex;

#include <iostream>

void Timer::stop()
{	
	microseconds end = std::chrono::duration_cast<microseconds>(system_clock::now().time_since_epoch());
	std::lock_guard<std::mutex> lg(_mutex);
	std::cout << "Process took " << ((double)(end.count() - start.count()) / 1000) << " ms\n";
	_running = false;
}

#endif



