#ifndef I8080_PORT
#define I8080_PORT

#include "Emulator/History/Originator.Momento.h"
#include <cstdint>

class I8080_Port : public Originator_Momento {
public:
	I8080_Port(uint8_t port);
	void virtual SetInput(const uint8_t& value);
	uint8_t virtual GetOutput();
	uint8_t GetPort();
	void virtual Reset();
private:
	uint8_t port;
};

#endif // !I8080_PORT
