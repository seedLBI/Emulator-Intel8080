#include "Momento.h"

ConsoleOutputMomento::ConsoleOutputMomento(const bool& LastActionIsInput, const char& LastSymbol) :
	Momento(0x02),
	LastActionIsInput(LastActionIsInput),
	LastSymbol(LastSymbol) 
{

}

ConsoleOutputMomento::~ConsoleOutputMomento() {

}

bool ConsoleOutputMomento::Get_LastActionIsInput() {
	return LastActionIsInput;
}
char ConsoleOutputMomento::Get_LastSymbol() {
	return LastSymbol;
}