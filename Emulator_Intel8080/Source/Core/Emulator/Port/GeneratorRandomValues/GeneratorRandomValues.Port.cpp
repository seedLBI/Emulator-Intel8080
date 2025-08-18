#include "GeneratorRandomValues.Port.h"


Port_GeneratorRandomValues::Port_GeneratorRandomValues() : Port(0x09) {
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "init port Generator random: 0x09" << std::endl;
#endif
	Init();
}

void Port_GeneratorRandomValues::SetInput(const uint8_t& value) {
	switch (count_input)
	{
	case 0:
		range = value + 1;
		break;
	default:
		break;
	}
	count_input++;

	if (count_input > 1) {
		count_input = 0;
	}
}
uint8_t Port_GeneratorRandomValues::GetOutput() {
	count_input++;
	if (count_input == 2) {
		count_input = 0;
		return rand() % range;
	}
	return 0;
}

uint8_t Port_GeneratorRandomValues::GetPort() {
	return Port::GetPort();
}


void Port_GeneratorRandomValues::Reset() {
	Init();
	count_input = 0;
	range = 0;
}

void Port_GeneratorRandomValues::Init() {
	std::srand((unsigned int)std::time(nullptr));
}

std::shared_ptr<Momento> Port_GeneratorRandomValues::SaveState() {
	return std::shared_ptr<Momento>(new GeneratorRandomValuesMomento(count_input,range));
}
void Port_GeneratorRandomValues::RestoreState(const std::shared_ptr<Momento>& momento) {
	auto data = dynamic_cast<GeneratorRandomValuesMomento*>(momento.get());

	count_input = data->get_count_input();
	range = data->get_range();
}
