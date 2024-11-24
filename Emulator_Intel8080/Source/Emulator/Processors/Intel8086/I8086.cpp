#include "Emulator/Processors/Intel8086/I8086.h"

I8086::I8086() :Processor(u8"Intel 8086") {

}
I8086::~I8086() {

}

Momento* I8086::SaveState() {
	return nullptr;
}
void     I8086::RestoreState(Momento* momento) {

}

void I8086::RemoveAllBreakPoints() { // TODO:

}
void I8086::EraseMemory() {// TODO:

}

void I8086::Reset() {// TODO:

}

void I8086::LoadMemory(const std::vector<uint8_t>& data, const bool& isBinary) {// TODO:

}

void I8086::NextStep() {// TODO:

}