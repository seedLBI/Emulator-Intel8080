#ifndef PORT_H
#define PORT_H

#include "Core/Emulator/History/Originator.Momento.h"
#include <cstdint>

class Port : public Originator_Momento {
public:
	Port(uint8_t port);
	void virtual SetInput(const uint8_t& value);
	uint8_t virtual GetOutput();
	uint8_t GetPort();
	void virtual Reset();
private:
	uint8_t port;
};

#endif // !I8080_PORT
