#ifndef CONSOLE_OUTPUT_MOMENTO_H
#define CONSOLE_OUTPUT_MOMENTO_H


#include "Core/Emulator/History/Momento.h"

class ConsoleOutputMomento : public Momento
{
public:
	ConsoleOutputMomento(const bool& LastActionIsInput, const char& LastSymbol);
	~ConsoleOutputMomento();

	bool Get_LastActionIsInput();
	char Get_LastSymbol();

private:
	bool LastActionIsInput = false;
	char LastSymbol = 0;
};


#endif // !CONSOLE_OUTPUT_MOMENTO_H
