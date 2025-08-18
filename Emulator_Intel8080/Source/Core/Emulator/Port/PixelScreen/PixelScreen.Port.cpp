#include "PixelScreen.Port.h"


Port_PixelScreen::Port_PixelScreen() :Port(0x05) {
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "init port Pixel screen: 0x05" << std::endl;
#endif
	Init();
}

void Port_PixelScreen::SetInput(const uint8_t& value) {
	switch (count_input) {
	case 0:
		index_raw = value;
		break;
	case 1:
		index_col = value;
		break;
	case 2:
		mode_read_or_write = (value == 0 ? 0 : 1);
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
		if (mode_read_or_write == 0) {
			array_colors[index_raw][index_col] = color;
		}

	}
}

uint8_t Port_PixelScreen::GetOutput() {
	count_input++;
	if (count_input > 3) {
		count_input = 0;
		if (mode_read_or_write == 1)
			return array_colors[index_raw][index_col];
	}

	return 0;
}

uint8_t Port_PixelScreen::GetPort() {
	return Port::GetPort();
}


void Port_PixelScreen::Reset() {
	Init();
	count_input = 0;
	index_raw = 0;
	index_col = 0;
	mode_read_or_write = 0;
	color = 0;
}


std::vector<std::vector<uint8_t>> Port_PixelScreen::Get_Array_colors() {
	return array_colors;
}


void Port_PixelScreen::Init() {
	array_colors.clear();
	array_colors.resize(256);
	for (int i = 0; i < 256; i++)
		array_colors[i].resize(256);
}

std::shared_ptr<Momento> Port_PixelScreen::SaveState() {
	return std::shared_ptr<Momento>(new PixelScreenMomento(count_input, index_raw, index_col, mode_read_or_write, array_colors[index_raw][index_col]));
}
void Port_PixelScreen::RestoreState(const std::shared_ptr<Momento>& momento) {
	auto data = dynamic_cast<PixelScreenMomento*>(momento.get());

	count_input = data->get_count_input();
	index_raw = data->get_index_raw();
	index_col = data->get_index_col();
	mode_read_or_write = data->get_mode_read_or_write();
	array_colors[index_raw][index_col] = data->get_last_color();

}