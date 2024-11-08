#include "Emulator/Port/I8080.Port.ConsoleOutput.h"

I8080_ConsoleOutput::I8080_ConsoleOutput() : I8080_Port(0x02) {
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "init port ConsoleOutput: 0x02" << std::endl;
#endif
}

void I8080_ConsoleOutput::SetInput(uint8_t value) {
	if (Memory.size() >= maxSize)
		Memory.pop_front();
	Memory.emplace_back(value);
}

uint8_t I8080_ConsoleOutput::GetOutput() {
	return 0;
}

std::deque<uint8_t> I8080_ConsoleOutput::GetConsoleData() {
	return Memory;
}

void I8080_ConsoleOutput::Reset() {
	Memory.clear();
}

uint8_t I8080_ConsoleOutput::GetPort() { return I8080_Port::GetPort(); }