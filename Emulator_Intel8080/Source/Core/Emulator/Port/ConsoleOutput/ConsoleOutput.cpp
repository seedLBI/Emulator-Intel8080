#include "ConsoleOutput.h"


Port_ConsoleOutput::Port_ConsoleOutput() : Port(0x02) {
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "init port ConsoleOutput: 0x02" << std::endl;
#endif
}

void Port_ConsoleOutput::SetInput(const uint8_t& value) {
	LastActionIsInput = true;

	if (Memory.size() >= maxSize)
		Memory.pop_front();
	Memory.emplace_back(value);
}

uint8_t Port_ConsoleOutput::GetOutput() {
	LastActionIsInput = false;

	return 0;
}

std::deque<uint8_t> Port_ConsoleOutput::GetConsoleData() {
	return Memory;
}

void Port_ConsoleOutput::Reset() {
	Memory.clear();
}

uint8_t Port_ConsoleOutput::GetPort() { return Port::GetPort(); }


std::shared_ptr<Momento> Port_ConsoleOutput::SaveState() {
	if (Memory.empty())
		return std::shared_ptr<Momento>(new ConsoleOutputMomento(false, 0));
	else
		return std::shared_ptr<Momento>(new ConsoleOutputMomento(LastActionIsInput, Memory.front()));
}

void Port_ConsoleOutput::RestoreState(const std::shared_ptr<Momento>& momento) {
	auto data = dynamic_cast<ConsoleOutputMomento*>(momento.get());

	if (data->Get_LastActionIsInput() == false)
		return;

	if (Memory.size() >= maxSize)
		Memory.pop_back();
	Memory.emplace_front(data->Get_LastSymbol());
}