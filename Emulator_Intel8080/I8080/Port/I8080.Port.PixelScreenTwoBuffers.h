#pragma once
#ifndef I8080_PORT_PIXELSCREEN_TWO_BUFFERS
#define I8080_PORT_PIXELSCREEN_TWO_BUFFERS

#include "Port\I8080.Port.h"

#include "Config_Compilier.h"

#include <vector>
#include <iostream>

class I8080_PixelScreenTwoBuffers : public I8080_Port {
public:
	I8080_PixelScreenTwoBuffers();
	void virtual SetInput(uint8_t value) override;
	uint8_t virtual GetOutput() override;
	void virtual Reset() override;
	uint8_t GetPort();

	std::vector<std::vector<uint8_t>> Get_Array_colors();


private:
	unsigned int count_input = 0;
	unsigned int index_raw = 0;
	unsigned int index_col = 0;
	unsigned int mode = 0;
	unsigned int color = 0;

	std::vector<std::vector<uint8_t>> Front;
	std::vector<std::vector<uint8_t>> Back;


	void Init();


	enum Modes {
		SetPixel,
		ReadPixel,
		SwapBuffer,
		ClearBuffers
	};
};




#endif // !I8080_PORT_PIXELSCREEN

