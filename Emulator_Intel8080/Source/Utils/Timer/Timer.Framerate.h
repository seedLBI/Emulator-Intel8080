#ifndef UTILS_TIMER_FRAMERATE_H
#define UTILS_TIMER_FRAMERATE_H

#pragma comment(lib, "winmm.lib")

#define _NO_COM
#include <Windows.h>
#include "Utils/Timer/Timer.h"


class FPS_Timer
{
public:
    FPS_Timer();
    ~FPS_Timer();
    void wait();

    void SetTargetFPS(const double& value);
    double GetTargetFPS();
    double GetDeltaTime();


private:
    double Start = 0.0, End = 0.0, Delta = 0.0;

    Timer deltaTimer;

    LARGE_INTEGER frequency;
    LARGE_INTEGER lastTime;
    double frameTime = 0.0;
    double targetFPS = 120.0;
};



#endif