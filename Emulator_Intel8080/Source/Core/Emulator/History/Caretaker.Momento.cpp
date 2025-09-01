#include "Caretaker.Momento.h"

#include "Core/Emulator/Processor/Processor.h"

Caretaker_Momento::Caretaker_Momento(Processor* processor) {
	this->processor = processor;
	momentos.resize(MaxCount);
}

Caretaker_Momento::~Caretaker_Momento() {

}

void Caretaker_Momento::Backup() {

	momentos.push_front(processor->SaveState());
	
	changed = true;
	/*
	momentos.emplace_front(processor->SaveState());
	if (momentos.size() == MaxCount)
		momentos.pop_back();
	*/
	
}
void Caretaker_Momento::Undo(const int& count) {
	if (count <= 0 || momentos.size() == 0)
		return;

	int actualCount = std::min(count, static_cast<int>(momentos.size()));

	for (int i = 0; i < actualCount; ++i) {
		processor->RestoreState(momentos.front());
		processor->DecreaseCountInstruction();
		momentos.pop_front();
	}

	changed = true;
}

void Caretaker_Momento::ClearHistory() {
	momentos.clear();
	changed = true;
}

std::vector<std::pair<std::string, std::string>> Caretaker_Momento::GetHistory() {
	return {};
}

void	 Caretaker_Momento::SetMaxCount(uint64_t count) {
	MaxCount = (int)count;
	momentos.resize(count);
}
uint64_t Caretaker_Momento::GetMaxCount() {
	return MaxCount;
}