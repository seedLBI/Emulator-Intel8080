#ifndef PROCESSOR_H
#define PROCESSOR_H


#include "Emulator/History/Originator.Momento.h"
#include <vector>
#include <string>

class Processor: public Originator_Momento
{
public:
	Processor(const std::string& Name);
	~Processor();

	virtual bool OnBreakPoint();
	virtual void RemoveAllBreakPoints();

	virtual void EraseMemory();
	virtual void Reset();
	virtual void LoadMemory(const std::vector<uint8_t>& data, const bool& isBinary);
	virtual void NextStep();
	virtual void NextStepWithHistorySaving();

	uint64_t GetCountTicks();
	uint64_t GetCountInstruction();
	void	 DecreaseCountInstruction();


	void ActiveFlagStop();
	void ResetFlagStop();
	void SetFlagStop(bool flag);
	bool GetFlagStop();
	bool* IsStop();

	void Set_HistoryMode(bool flag);
	void ToggleHistoryMode();
	bool isHistoryModeEnabled();

protected:
	std::string Name = "";

	uint64_t CountInstruction = 0;
	uint64_t CountTicks = 0;

	bool FlagStop = false;

	bool Flag_HistoryModeEnabled = false;
};



#endif