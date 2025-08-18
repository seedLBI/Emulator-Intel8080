#include "Timer.h"

void Timer::start() {
    start_time = std::chrono::high_resolution_clock::now();
}

void Timer::stop() {
    stop_time = std::chrono::high_resolution_clock::now();
}

long long Timer::elapsedNanoseconds() const {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(stop_time - start_time).count();
}

long long Timer::elapsedMicroseconds() const {
    return std::chrono::duration_cast<std::chrono::microseconds>(stop_time - start_time).count();
}

long long Timer::elapsedMilliseconds() const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time).count();
}

double Timer::elapsedSeconds() const {
    return std::chrono::duration<double>(stop_time - start_time).count();
}