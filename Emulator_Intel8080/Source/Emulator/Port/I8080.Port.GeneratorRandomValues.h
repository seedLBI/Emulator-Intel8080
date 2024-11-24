#ifndef I8080_PORT_GENERATORRANDOMVALUES
#define I8080_PORT_GENERATORRANDOMVALUES

#include "Config_Compilier.h"
#include "Emulator/Port/I8080.Port.h"
#include "GeneratorRandomValuesMomento/GeneratorRandomValues.Momento.h"

#include <cstdint>
#include <vector>
#include <iostream>

class I8080_GeneratorRandomValues : public I8080_Port {
public:
	I8080_GeneratorRandomValues();
	void virtual SetInput(uint8_t value) override;
	uint8_t virtual GetOutput() override;
	void virtual Reset() override;
	uint8_t GetPort();

	std::shared_ptr<Momento> SaveState() override;
	void					 RestoreState(const std::shared_ptr<Momento>& momento) override;

private:
	uint8_t count_input = 0;
	uint8_t range = 0;

	void Init();
};

#endif // !I8080_PORT_GENERATORRANDOMVALUES

