#ifndef ASYNC_KEYBOARD_MOMENTO_H
#define ASYNC_KEYBOARD_MOMENTO_H

#include "Emulator/History/Momento.h"
#include <cstdint>

class AsyncKeyboard_Momento : public Momento
{
public:
	AsyncKeyboard_Momento(const uint8_t& count_input, const uint8_t& currentKey);
	~AsyncKeyboard_Momento();

	uint8_t Get_count_input() const;
	uint8_t Get_currentKey() const;

private:
	uint8_t count_input = 0;
	uint8_t currentKey = 0;
};




#endif // !
