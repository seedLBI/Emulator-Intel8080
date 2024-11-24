#include "Momento.h"

Momento::Momento() {
	this->portNumber = -1;
}

Momento::Momento(const int& portNumber){
	this->portNumber = portNumber;
}

Momento::~Momento(){
}

int Momento::GetPortNumber() {
	return portNumber;
}