#pragma once
#ifndef I8080_PORT_PIXELSCREEN
#define I8080_PORT_PIXELSCREEN

#include "Emulator/Port/I8080.Port.h"
#include "Momento/PixelScreen.Momento.h"
#include "Config_Compilier.h"

#include <vector>
#include <iostream>

class I8080_PixelScreen : public I8080_Port {
public:
	I8080_PixelScreen();
	void virtual SetInput(uint8_t value) override;
	uint8_t virtual GetOutput() override;
	void virtual Reset() override;
	uint8_t GetPort();

	std::vector<std::vector<uint8_t>> Get_Array_colors();

	std::shared_ptr<Momento> SaveState() override;
	void					 RestoreState(const std::shared_ptr<Momento>& momento) override;

private:
	uint8_t count_input		   = 0;
	uint8_t index_raw		   = 0;
	uint8_t index_col		   = 0;
	uint8_t mode_read_or_write = 0;
	uint8_t color			   = 0;

	std::vector<std::vector<uint8_t>> array_colors;

	void Init();
};




#endif // !I8080_PORT_PIXELSCREEN

