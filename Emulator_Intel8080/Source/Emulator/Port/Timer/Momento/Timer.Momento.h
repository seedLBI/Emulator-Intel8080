#ifndef TIMER_MOMENTO_H
#define TIMER_MOMENTO_H

#include "Emulator/History/Momento.h"
#include <cstdint>


class TimerMomento : public Momento
{
public:
	TimerMomento(const uint8_t& countPartSec);
	~TimerMomento();

	uint8_t get_countPartSec() const;

private:
	uint8_t countPartSec = 0;
};




#endif // !TIMER_MOMENTO_H
