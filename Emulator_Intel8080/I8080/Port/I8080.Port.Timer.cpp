#include "I8080.Port.Timer.h"


I8080_Timer::I8080_Timer() : I8080_Port(0x16) {
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "init port Timer: 0x16" << std::endl;
#endif
	clock_start = std::chrono::system_clock::now();
}

void I8080_Timer::SetInput(uint8_t value) {
	countPartSec = value;
	clock_start = std::chrono::system_clock::now();
}
uint8_t I8080_Timer::GetOutput() {
	clock_end = std::chrono::system_clock::now();
	float timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds> (clock_end - clock_start).count() / 1000.f;
	float timeSetted = float(unsigned int(countPartSec)) * 0.01f;


	if (timeElapsed > timeSetted)
	{
		return 0;
	}
	else {

		return unsigned int((timeSetted - timeElapsed) * 100.f);
	}
}

void I8080_Timer::Reset() {
	countPartSec = 0;
}


uint8_t I8080_Timer::GetPort() { return I8080_Port::GetPort(); }