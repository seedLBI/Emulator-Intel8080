#ifndef I8080_PORT_PIXELSCREEN_TWO_BUFFERS
#define I8080_PORT_PIXELSCREEN_TWO_BUFFERS

#include "Core/Emulator/Port/Port.h"
#include "Momento/PixelScreenTwoBuffers.Momento.h"
#include "Config_Compilier.h"

#include <vector>

#ifdef _DEBUG
#include <iostream>
#endif

#include <algorithm>

class Port_PixelScreenTwoBuffers : public Port {
public:
	Port_PixelScreenTwoBuffers();
	void SetInput(const uint8_t& value) override;
	uint8_t GetOutput() override;
	void Reset() override;
	uint8_t GetPort();

	std::vector<std::vector<uint8_t>> Get_Array_colors_FrontBuffer();
	std::vector<std::vector<uint8_t>> Get_Array_colors_BackBuffer();

	std::shared_ptr<Momento> SaveState() override;
	void					 RestoreState(const std::shared_ptr<Momento>& momento) override;

private:
	uint8_t count_input = 0;
	uint8_t index_raw = 0;
	uint8_t index_col = 0;
	uint8_t mode = 0;
	uint8_t color = 0;

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

