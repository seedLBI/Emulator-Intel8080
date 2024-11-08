#ifndef I8080_PORT_CONSOLEOUTPUT_H
#define I8080_PORT_CONSOLEOUTPUT_H



#include "Config_Compilier.h"
#include "Emulator/Port/I8080.Port.h"

#include <deque>
#include <vector>
#include <iostream>
#include <chrono>

class I8080_ConsoleOutput : public I8080_Port {
public:
	I8080_ConsoleOutput();
	void SetInput(uint8_t value) override;
	uint8_t GetOutput() override;
	void Reset() override;

	std::deque<uint8_t> GetConsoleData();

	uint8_t GetPort();

private:
	std::deque<uint8_t> Memory;
	const int maxSize = 4096;
};


#endif // !I8080_PORT_CONSOLEOUTPUT_H

