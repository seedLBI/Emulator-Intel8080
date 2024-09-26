#include "Port\I8080.Port.h"

#pragma once
#ifndef I8080_PORT_GENERATORRANDOMVALUES
#define I8080_PORT_GENERATORRANDOMVALUES

#include "Config_Compilier.h"
#include <vector>
#include <iostream>

class I8080_GeneratorRandomValues : public I8080_Port {
public:
	I8080_GeneratorRandomValues();
	void virtual SetInput(uint8_t value) override;
	uint8_t virtual GetOutput() override;
	void virtual Reset() override;
	uint8_t GetPort();


private:
	unsigned int count_input = 0;
	unsigned int range = 0;

	void Init();
};

#endif // !I8080_PORT_GENERATORRANDOMVALUES

