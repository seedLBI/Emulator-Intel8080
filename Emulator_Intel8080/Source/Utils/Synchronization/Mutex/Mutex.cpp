#include "Mutex.h"

Mutex::Mutex() {
	ID = CreateMutex(NULL, false, NULL);

	if (ID == NULL) {
#ifdef _DEBUG
		std::cerr << "Ошибка создания Мьютекста " << GetLastError() << std::endl;
#endif
		exit(1337);
	}
	else {
#ifdef _DEBUG
		std::cout << "Mutex Created:\n\tID: [" << ID << "]\n";
#endif // _DEBUG

	}
}

Mutex::Mutex(const char* Name) {

	if (Name == NULL) {
		Mutex();
	}
	else {

		sa.nLength = sizeof(sa);
		sa.lpSecurityDescriptor = NULL;
		sa.bInheritHandle = TRUE;


		int length = MultiByteToWideChar(CP_ACP, 0, Name, -1, NULL, 0);
		std::wstring wstr(length, 0);
		MultiByteToWideChar(CP_ACP, 0, Name, -1, &wstr[0], length);


		ID = OpenMutex(MUTEX_ALL_ACCESS, true, wstr.c_str());

		if (ID == NULL) {
#ifdef _DEBUG
			std::cout << "Mutex \"" << Name << "\" not exist." << std::endl;
#endif
			ID = CreateMutex(&sa, false, wstr.c_str());

			if (ID == NULL) {
#ifdef _DEBUG
				std::cerr << "Error Creation Mutex [" << Name << "]: " << GetLastError() << std::endl;
#endif
				exit(1337);
			}
			else {
#ifdef _DEBUG
				std::cout << "Mutex Created:\n\tName: [" << Name << "]\n\tID: [" << ID << "]\n";
#endif
			}
		}
		else {
#ifdef _DEBUG
			std::cout << "Mutex Opened:\n\tName: [" << Name << "]\n\tID: [" << ID << "]\n";
#endif
		}


	}
}

void Mutex::Enter() {
	DWORD waitResult = WaitForSingleObject(ID, INFINITE);
	if (waitResult != WAIT_OBJECT_0) {
		DWORD errorCode = GetLastError();
		std::cerr << "Ошибка ожидания мьютекса: " << errorCode << std::endl;
		throw std::runtime_error("Ошибка ожидания мьютекса");
	}
}
void Mutex::Leave() {
	if (!ReleaseMutex(ID)) {
		DWORD errorCode = GetLastError();
		std::cerr << "Ошибка освобождения мьютекса: " << errorCode << std::endl;
		throw std::runtime_error("Ошибка освобождения мьютекса");
	}
}

Mutex::~Mutex() {
#ifdef DEBUG
	std::cout << "Mutex EXIT:\n\tID: [" << ID << "]\n";
#endif // DEBUG

	CloseHandle(ID);
}