#include "I8080.Port.GeneratorRandomValues.h"


I8080_GeneratorRandomValues::I8080_GeneratorRandomValues() :I8080_Port(0x09) {
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "init port Generator random: 0x09" << std::endl;
#endif
	Init();
}

void I8080_GeneratorRandomValues::SetInput(uint8_t value) {
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
uint8_t I8080_GeneratorRandomValues::GetOutput() {
	count_input++;
	if (count_input == 2) {
		count_input = 0;
		return rand() % range;
	}
	return 0;
}

uint8_t I8080_GeneratorRandomValues::GetPort() {
	return I8080_Port::GetPort();
}


void I8080_GeneratorRandomValues::Reset() {
	Init();
	count_input = 0;
	range = 0;
}

void I8080_GeneratorRandomValues::Init() {
	std::srand(std::time(nullptr));
}

std::shared_ptr<Momento> I8080_GeneratorRandomValues::SaveState() {
	return std::shared_ptr<Momento>(new GeneratorRandomValuesMomento(count_input,range));
}
void I8080_GeneratorRandomValues::RestoreState(const std::shared_ptr<Momento>& momento) {
	auto data = dynamic_cast<GeneratorRandomValuesMomento*>(momento.get());

	count_input = data->get_count_input();
	range = data->get_range();
}
