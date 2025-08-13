#ifndef EVENT_H
#define EVENT_H

#include <windows.h>
#include <iostream>
#include <string>

enum class EVENT_TYPE_RESET {
	AUTO_RESET = false,
	MANUAL_RESET = true,
};

class Event {
public:
	Event(const EVENT_TYPE_RESET type_reset = EVENT_TYPE_RESET::MANUAL_RESET, const bool begin_state = false, const char* text = NULL);
	~Event();

	void Set();
	void Reset();
	void Wait();

private:
	HANDLE ID = 0;
	SECURITY_ATTRIBUTES sa;
};






#endif