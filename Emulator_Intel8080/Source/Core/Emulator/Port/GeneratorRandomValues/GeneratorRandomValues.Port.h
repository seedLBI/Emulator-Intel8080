#ifndef I8080_PORT_GENERATORRANDOMVALUES
#define I8080_PORT_GENERATORRANDOMVALUES

#include "Config_Compilier.h"
#include "Core/Emulator/Port/Port.h"
#include "Momento/GeneratorRandomValues.Momento.h"

#include <cstdint>
#include <vector>
#include <ctime>

#ifdef _DEBUG
#include <iostream>
#endif

class Port_GeneratorRandomValues : public Port {
public:
	Port_GeneratorRandomValues();
	void SetInput(const uint8_t& value) override;
	uint8_t GetOutput() override;
	void Reset() override;
	uint8_t GetPort();

	std::shared_ptr<Momento> SaveState() override;
	void					 RestoreState(const std::shared_ptr<Momento>& momento) override;

private:
	uint8_t count_input = 0;
	uint8_t range = 0;

	void Init();
};

#endif // !I8080_PORT_GENERATORRANDOMVALUES

