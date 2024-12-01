#include "AsyncKeyboard.Momento.h"

uint8_t AsyncKeyboard_Momento::Get_count_input() const {
	return count_input;
}

uint8_t AsyncKeyboard_Momento::Get_currentKey() const {
	return currentKey;
}

AsyncKeyboard_Momento::AsyncKeyboard_Momento(const uint8_t& count_input, const uint8_t& currentKey) : 
	Momento(0x10),
	count_input(count_input),
	currentKey(currentKey)
{



}

AsyncKeyboard_Momento::~AsyncKeyboard_Momento()
{
}
