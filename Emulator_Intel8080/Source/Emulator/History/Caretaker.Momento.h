#ifndef CARATAKER_MOMENTO_H
#define CARATAKER_MOMENTO_H

#include "DataStructures/RingBuffer.h"
#include "Emulator/Processors/Processor.h"
#include "Momento.h"
#include <memory>
#include <deque>
#include <vector>
#include <string>


class Caretaker_Momento
{
public:
	Caretaker_Momento(Processor* processor);
	~Caretaker_Momento();

	void Backup();
	void Undo(const int& count = 1);
	void ClearHistory();
	virtual std::vector<std::pair<std::string, std::string>> GetHistory();

	void	 SetMaxCount(uint64_t count);
	uint64_t GetMaxCount();

protected:
	Processor* processor;
	RingBuffer<std::shared_ptr<Momento>> momentos;
	//std::deque< std::shared_ptr<Momento>> momentos;
	int MaxCount = 100;

	bool changed = true;
};

#endif // !CARATAKER_MOMENTO_H

