#include "I8080.Port.PixelScreenTwoBuffers.h"


I8080_PixelScreenTwoBuffers::I8080_PixelScreenTwoBuffers() :I8080_Port(0x06) {
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "init port Pixel screen with two buffers: 0x06" << std::endl;
#endif
	Init();
}

void I8080_PixelScreenTwoBuffers::SetInput(uint8_t value) {
	switch (count_input)
	{
	case 0:
		mode = value;
		break;
	case 1:
		index_raw = value;
		break;
	case 2:
		index_col = value;
		break;
	case 3:
		color = value;
		break;
	default:
		break;
	}
	count_input++;

	if (count_input > 3) {
		count_input = 0;
		if (mode == Modes::SetPixel) {
			Back[index_raw][index_col] = color;
		}

	}
	else if (mode == Modes::SwapBuffer){

		//swap(Front, Back);
		//Back = Front;

		Front = Back;

		count_input = 0;
	}
	else if (mode == Modes::ClearBuffers){
		for (int i = 0; i < 256; i++) {
			for (int j = 0; j < 256; j++){
				//Front[i][j] = 0;
				Back[i][j] = 0;
			}
		}
		count_input = 0;
	}


}

uint8_t I8080_PixelScreenTwoBuffers::GetOutput() {
	count_input++;
	if (count_input > 2) {
		if (mode == Modes::ReadPixel)
		{
			count_input = 0;
			return Back[index_raw][index_col];
		}
	}

	return 0;
}

uint8_t I8080_PixelScreenTwoBuffers::GetPort()
{
	return I8080_Port::GetPort();
}


void I8080_PixelScreenTwoBuffers::Reset() {
	Init();
	count_input = 0;
	index_raw = 0;
	index_col = 0;
	mode = 0;
	color = 0;
}


std::vector<std::vector<uint8_t>> I8080_PixelScreenTwoBuffers::Get_Array_colors() {
	return Front;
}


void I8080_PixelScreenTwoBuffers::Init() {
	Front.clear();
	Back.clear();
	Front.resize(256);
	Back.resize(256);
	for (int i = 0; i < 256; i++) {
		Front[i].resize(256);
		Back[i].resize(256);
	}
}