#ifndef I8080_PORT_SYMBOLSCREEN
#define I8080_PORT_SYMBOLSCREEN

#include "Core/Emulator/Port/Port.h"
#include "Momento/Momento.h"

#include "Config_Compilier.h"


#include <vector>
#include <iostream>

class Port_SymbolScreen : public Port {
public:
	Port_SymbolScreen();
	void SetInput(const uint8_t& value) override;
	uint8_t GetOutput() override;
	void Reset() override;
	uint8_t GetPort();

	std::vector<std::vector<uint8_t>> Get_Array_symbols();
	std::vector<std::vector<uint8_t>> Get_Array_colors();

	std::shared_ptr<Momento> SaveState() override;
	void					 RestoreState(const std::shared_ptr<Momento>& momento) override;


private:
	uint8_t count_input = 0;
	uint8_t index_raw = 0;
	uint8_t index_col = 0;
	uint8_t mode_read_or_write = 0;
	uint8_t color = 0;
	uint8_t symbol = 0;


	std::vector<std::vector<uint8_t>> arraySymbols;
	std::vector<std::vector<uint8_t>> arrayColors;

	void Init();
};


#endif // !I8080_PORT_SYMBOLSCREEN

