#include "Timer.Momento.h"


TimerMomento::TimerMomento(const uint8_t& countPartSec) :
	Momento(0x16),
	countPartSec(countPartSec)
{

}

TimerMomento::~TimerMomento() {

}

uint8_t TimerMomento::get_countPartSec() const {
	return countPartSec;
}