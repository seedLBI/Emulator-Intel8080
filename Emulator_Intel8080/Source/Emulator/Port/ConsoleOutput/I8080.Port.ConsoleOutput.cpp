#include "Emulator/Port/ConsoleOutput/I8080.Port.ConsoleOutput.h"


I8080_ConsoleOutput::I8080_ConsoleOutput() : I8080_Port(0x02) {
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "init port ConsoleOutput: 0x02" << std::endl;
#endif
}

void I8080_ConsoleOutput::SetInput(const uint8_t& value) {
	LastActionIsInput = true;

	if (Memory.size() >= maxSize)
		Memory.pop_front();
	Memory.emplace_back(value);
}

uint8_t I8080_ConsoleOutput::GetOutput() {
	LastActionIsInput = false;

	return 0;
}

std::deque<uint8_t> I8080_ConsoleOutput::GetConsoleData() {
	return Memory;
}

void I8080_ConsoleOutput::Reset() {
	Memory.clear();
}

uint8_t I8080_ConsoleOutput::GetPort() { return I8080_Port::GetPort(); }


std::shared_ptr<Momento> I8080_ConsoleOutput::SaveState() {
	if (Memory.empty())
		return std::shared_ptr<Momento>(new ConsoleOutputMomento(false, 0));
	else
		return std::shared_ptr<Momento>(new ConsoleOutputMomento(LastActionIsInput, Memory.front()));
}

void I8080_ConsoleOutput::RestoreState(const std::shared_ptr<Momento>& momento) {
	auto data = dynamic_cast<ConsoleOutputMomento*>(momento.get());

	if (data->Get_LastActionIsInput() == false)
		return;

	if (Memory.size() >= maxSize)
		Memory.pop_back();
	Memory.emplace_front(data->Get_LastSymbol());
}