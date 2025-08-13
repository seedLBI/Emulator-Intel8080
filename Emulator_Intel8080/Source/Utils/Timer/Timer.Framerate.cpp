#include "Timer.Framerate.h"

void FPS_Timer::SetTargetFPS(const double& value) {
	targetFPS = value;
	frameTime = 1.0 / targetFPS;
	Delta = 1.0 / targetFPS;
}

double FPS_Timer::GetDeltaTime() {
	return Delta;
}

void FPS_Timer::wait() {
	

	if (targetFPS == 0)
		return;

	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	double elapsedTime = static_cast<double>(currentTime.QuadPart - lastTime.QuadPart) / frequency.QuadPart;

	if (elapsedTime < frameTime) {
		DWORD sleepTime = static_cast<DWORD>((frameTime - elapsedTime) * 1000.0);
		if (sleepTime != 0)
			--sleepTime;
		if (sleepTime > 0)
			Sleep(sleepTime);

		do {
			QueryPerformanceCounter(&currentTime);
			elapsedTime = static_cast<double>(currentTime.QuadPart - lastTime.QuadPart) / frequency.QuadPart;
		} while (elapsedTime < frameTime);
	}

	lastTime = currentTime;
}

FPS_Timer::FPS_Timer() {
	frameTime = 1.0 / targetFPS;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&lastTime);
	timeBeginPeriod(1);
}

FPS_Timer::~FPS_Timer() {
	timeEndPeriod(1);
}