#include "PixelScreenTwoBuffers.h"


Port_PixelScreenTwoBuffers::Port_PixelScreenTwoBuffers() : Port(0x06) {
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "init port Pixel screen with two buffers: 0x06" << std::endl;
#endif
	Init();
}

void Port_PixelScreenTwoBuffers::SetInput(const uint8_t& value) {
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
		Front = Back;
		count_input = 0;
	}
	else if (mode == Modes::ClearBuffers){
		for (uint16_t i = 0; i < 256; i++){
			for (uint16_t j = 0; j < 256; j++)
				Back[i][j] = 0;
		}
		count_input = 0;
	}


}

uint8_t Port_PixelScreenTwoBuffers::GetOutput() {
	count_input++;
	if (count_input > 2) {
		if (mode == Modes::ReadPixel){
			count_input = 0;
			return Back[index_raw][index_col];
		}
	}

	return 0;
}

uint8_t Port_PixelScreenTwoBuffers::GetPort() {
	return Port::GetPort();
}


void Port_PixelScreenTwoBuffers::Reset() {
	Init();
	count_input = 0;
	index_raw = 0;
	index_col = 0;
	mode = 0;
	color = 0;
}


std::vector<std::vector<uint8_t>> Port_PixelScreenTwoBuffers::Get_Array_colors_FrontBuffer() {
	return Front;
}
std::vector<std::vector<uint8_t>> Port_PixelScreenTwoBuffers::Get_Array_colors_BackBuffer() {
	return Back;
}

void Port_PixelScreenTwoBuffers::Init() {
	Front.clear();
	Back.clear();
	Front.resize(256);
	Back.resize(256);
	for (int i = 0; i < 256; i++) {
		Front[i].resize(256);
		Back[i].resize(256);
	}
}

std::shared_ptr<Momento> Port_PixelScreenTwoBuffers::SaveState() {

	if (count_input != 0){
		return std::shared_ptr<Momento>(new PixelScreenTwoBuffersMomento(
			count_input,
			index_raw,
			index_col,
			mode,
			Back[index_raw][index_col],
			{}, {}));
	}
	else {
		return std::shared_ptr<Momento>(new PixelScreenTwoBuffersMomento(
			count_input,
			index_raw,
			index_col,
			mode,
			Back[index_raw][index_col],
			Front, Back));
	}
}
void Port_PixelScreenTwoBuffers::RestoreState(const std::shared_ptr<Momento>& momento) {
	auto data = dynamic_cast<PixelScreenTwoBuffersMomento*>(momento.get());

	count_input = data->get_count_input();
	index_raw = data->get_index_raw();
	index_col = data->get_index_col();
	mode = data->get_mode();
	Back[index_raw][index_col] = data->get_last_color();
	if (count_input == 0){
		Front = data->get_Buffer1();
		Back = data->get_Buffer2();
	}

}