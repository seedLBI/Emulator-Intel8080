#ifndef UTILS_TIMER_H
#define UTILS_TIMER_H

#include <chrono>

class Timer {
public:
    Timer() : running(false), start_time(), stop_time() {}

    void start();
    void stop();

    long long elapsedNanoseconds() const;
    long long elapsedMicroseconds() const;
    long long elapsedMilliseconds() const;

    double elapsedSeconds() const;

private:
    bool running;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> stop_time;
};




#endif