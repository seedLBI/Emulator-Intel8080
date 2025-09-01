#ifndef I8080_PORT_ASYNCKEYBOARD
#define I8080_PORT_ASYNCKEYBOARD


#include "Momento/AsyncKeyboard.Momento.h"
#include "Core/Emulator/Port/Port.h"

class Port_AsyncKeyboard : public Port {
public:
	Port_AsyncKeyboard();

	void SetInput(const uint8_t& value) override;
	uint8_t GetOutput() override;
	void Reset() override;
	uint8_t GetPort();

	std::shared_ptr<Momento> SaveState() override;
	void					 RestoreState(const std::shared_ptr<Momento>& momento) override;

private:
	uint8_t count_input = 0;
	uint8_t currentKey = -1;
};




#endif // !I8080_PORT_ASYNCKEYBOARD
