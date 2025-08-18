#include "Utils/Timer/Timer.Framerate.h"

void FPS_Timer::SetTargetFPS(const double& value) {
	targetFPS = value;
	if (targetFPS == 0){
		frameTime = 0.0;
		Delta = 0.0;
	}
	else {
		frameTime = 1.0 / targetFPS;
		Delta = 0.0;
	}
	deltaTimer.start();
}

double FPS_Timer::GetTargetFPS() {
	return targetFPS;
}

double FPS_Timer::GetDeltaTime() {
	return Delta;
}

void FPS_Timer::wait() {
	deltaTimer.stop();
	Delta = deltaTimer.elapsedSeconds();

	if (targetFPS == 0) {
		deltaTimer.start();
		return;
	}

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

	Delta = elapsedTime;
	lastTime = currentTime;

	deltaTimer.start();
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