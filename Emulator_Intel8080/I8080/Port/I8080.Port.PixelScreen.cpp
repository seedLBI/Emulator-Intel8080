#include "I8080.Port.PixelScreen.h"


I8080_PixelScreen::I8080_PixelScreen() :I8080_Port(0x05) {
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "init port Pixel screen: 0x05" << std::endl;
#endif
	Init();
}

void I8080_PixelScreen::SetInput(uint8_t value) {
	switch (count_input)
	{
	case 0:
		index_raw = value;
		break;
	case 1:
		index_col = value;
		break;
	case 2:
		mode_read_or_write = (unsigned int(value) == 0 ? 0 : 1);
		break;
	case 3:
		color = value;
		break;
	default:
		break;
	}
	count_input++;

	if (count_input > 3)
	{
		count_input = 0;
		if (mode_read_or_write == 0) {
			array_colors[index_raw][index_col] = color;
		}

	}
}

uint8_t I8080_PixelScreen::GetOutput() {
	count_input++;
	if (count_input > 3) {
		count_input = 0;
		if (mode_read_or_write == 1)
			return array_colors[index_raw][index_col];
	}

	return 0;
}

uint8_t I8080_PixelScreen::GetPort()
{
	return I8080_Port::GetPort();
}


void I8080_PixelScreen::Reset() {
	Init();
	count_input = 0;
	index_raw = 0;
	index_col = 0;
	mode_read_or_write = 0;
	color = 0;
}


std::vector<std::vector<uint8_t>> I8080_PixelScreen::Get_Array_colors() {
	return array_colors;
}


void I8080_PixelScreen::Init() {
	array_colors.clear();
	array_colors.resize(256);
	for (int i = 0; i < 256; i++)
		array_colors[i].resize(256);
}