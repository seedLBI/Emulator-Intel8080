#ifndef I8080_PORT_TIMER
#define I8080_PORT_TIMER

#include "Config_Compilier.h"

#include "Core/Emulator/Port/Port.h"
#include "Momento/Timer.Momento.h"
#include <vector>
#include <chrono>

#ifdef _DEBUG
#include <iostream>
#endif


class Port_Timer : public Port {
public:
	Port_Timer();
	void SetInput(const uint8_t& value) override;
	uint8_t GetOutput() override;
	void Reset() override;
	uint8_t GetPort();

	std::shared_ptr<Momento> SaveState() override;
	void					 RestoreState(const std::shared_ptr<Momento>& momento) override;


private:
	uint8_t countPartSec = 0;
	std::chrono::system_clock::time_point clock_start = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point clock_end = std::chrono::system_clock::now();
};


#endif // !I8080_PORT_TIMER

