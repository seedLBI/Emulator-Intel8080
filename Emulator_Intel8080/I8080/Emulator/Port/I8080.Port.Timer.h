#include "Emulator/Port/I8080.Port.h"

#pragma once
#ifndef I8080_PORT_TIMER
#define I8080_PORT_TIMER

#include "Config_Compilier.h"

#include <vector>
#include <iostream>
#include <chrono>

class I8080_Timer : public I8080_Port {
public:
	I8080_Timer();
	void virtual SetInput(uint8_t value) override;
	uint8_t virtual GetOutput() override;
	void virtual Reset() override;
	uint8_t GetPort();

private:
	uint8_t countPartSec = 0;
	std::chrono::system_clock::time_point clock_start = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point clock_end = std::chrono::system_clock::now();
};


#endif // !I8080_PORT_TIMER

