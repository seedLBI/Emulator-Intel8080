#include "Processor.h"


Processor::Processor(const std::string& Name) {
	this->Name = Name;
}

Processor::~Processor() {

}

bool Processor::OnBreakPoint() {
	return false;
}
void Processor::RemoveAllBreakPoints() {

}
void Processor::EraseMemory() {

}
void Processor::Reset() {

}
void Processor::LoadMemory(const std::vector<uint8_t>& data, const bool& isBinary) {

}
void Processor::NextStep() {

}
void Processor::NextStepWithHistorySaving() {

}


uint64_t Processor::GetCountTicks() {
	return CountTicks;
}
uint64_t Processor::GetCountInstruction() {
	return CountInstruction;
}

void Processor::DecreaseCountInstruction() {
	if (CountInstruction != 0)
		CountInstruction--;
}

void Processor::ActiveFlagStop() {
	FlagStop = true;
}
void Processor::ResetFlagStop() {
	FlagStop = false;
}
void Processor::SetFlagStop(const bool& flag) {
	FlagStop = flag;
}
bool Processor::GetFlagStop() {
	return FlagStop;
}
bool* Processor::IsStop() {
	return &FlagStop;
}

void Processor::Set_HistoryMode(bool flag) {
	Flag_HistoryModeEnabled = flag;
}
void Processor::ToggleHistoryMode() {
	Flag_HistoryModeEnabled = !Flag_HistoryModeEnabled;
}
bool Processor::isHistoryModeEnabled() {
	return Flag_HistoryModeEnabled;
}