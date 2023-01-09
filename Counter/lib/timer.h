#include <chrono>
#include <memory>
#include <iostream>
#ifndef TIMER_TIMERCLASS_H_
#define TIMER_TIMERCLASS_H_
class Timer {
public: 
    Timer(){
        _Start_Time = std::chrono::high_resolution_clock::now();
    }
    double Stop(){
        auto endTimepoint = std::chrono::high_resolution_clock::now();

        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(_Start_Time).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

        auto duration = end - start;


        return duration;
    }
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> _Start_Time; 
};
#endif