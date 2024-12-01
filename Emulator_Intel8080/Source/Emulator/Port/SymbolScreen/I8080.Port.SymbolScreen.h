#ifndef I8080_PORT_SYMBOLSCREEN
#define I8080_PORT_SYMBOLSCREEN

#include "Emulator/Port/I8080.Port.h"
#include "Momento/SymbolScreen.Momento.h"

#include "Config_Compilier.h"


#include <vector>
#include <iostream>

class I8080_SymbolScreen : public I8080_Port {
public:
	I8080_SymbolScreen();
	void virtual SetInput(uint8_t value) override;
	uint8_t virtual GetOutput() override;
	void virtual Reset() override;
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

