#include "Event.h"


void Event::Wait() {
	WaitForSingleObject(ID, INFINITE);
}

void Event::Set() {
	SetEvent(ID);
}

void Event::Reset() {
	ResetEvent(ID);
}

Event::Event(const EVENT_TYPE_RESET type_reset, const bool begin_state, const char* text) {
	if (text == NULL) {
		ID = CreateEvent(NULL, static_cast<int>(type_reset), begin_state, NULL);

		if (ID == NULL) {
			std::cerr << "Error creation Event [" << text << "]: " << GetLastError() << std::endl;
			exit(1337);
		}
		else {
#ifdef _DEBUG
			std::cout << "Event Created:\n\tID: [" << ID << "]\n";
#endif // _DEBUG
		}
	}
	else {
		sa.nLength = sizeof(sa);
		sa.lpSecurityDescriptor = NULL;
		sa.bInheritHandle = TRUE;


		int length = MultiByteToWideChar(CP_ACP, 0, text, -1, NULL, 0);
		std::wstring wstr(length, 0);
		MultiByteToWideChar(CP_ACP, 0, text, -1, &wstr[0], length);


		ID = OpenEvent(EVENT_ALL_ACCESS, true, wstr.c_str());

		if (ID == NULL) {
#ifdef _DEBUG
			std::cout << "Event [\"" << text << "\"] not exist." << std::endl;
#endif

			ID = CreateEvent(&sa, static_cast<int>(type_reset), begin_state, wstr.c_str());

			if (ID == NULL) {
				std::cerr << "Error creation Event [" << text << "]: " << GetLastError() << std::endl;
				exit(1337);
			}
			else {
#ifdef _DEBUG
				std::cout << "Event Created:\n\tName: [" << text << "]\n\tID: [" << ID << "]\n";
#endif
			}
		}
		else {
#ifdef _DEBUG
			std::cout << "Event Opened:\n\tName: [" << text << "]\n\tID: [" << ID << "]\n";
#endif
		}
	}
}

Event::~Event() {
	std::cout << "Event EXIT:\n\tID: [" << ID << "]\n";
	CloseHandle(ID);
}