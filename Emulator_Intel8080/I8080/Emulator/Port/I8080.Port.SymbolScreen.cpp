#include "I8080.Port.SymbolScreen.h"



I8080_SymbolScreen::I8080_SymbolScreen() :I8080_Port(0x07) {
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "init port Symbol screen: 0x07" << std::endl;
#endif
	Init();
}

void I8080_SymbolScreen::SetInput(uint8_t value) {
	//cout << "inputted: " << int2stringBin(value) << endl;
	switch (count_input)
	{
	case 0:
		if (value > 19)
			value = 19;
		index_raw = value;

		break;
	case 1:
		if (value > 19)
			value = 19;
		index_col = value;
		break;
	case 2:
		mode_read_or_write = (unsigned int(value) == 0 ? 0 : 1);
		break;
	case 3:
		if ((unsigned int)value > 63) {
			color = 63;
		}
		else {
			color = value;
		}

		break;
	case 4:
		symbol = (value > 32 ? value : ' ');
		break;
	default:
		break;
	}
	count_input++;
	if (count_input > 4)
	{
		count_input = 0;
		if (mode_read_or_write == 0) {
			arraySymbols[index_raw][index_col] = symbol;
			arrayColors[index_raw][index_col] = color;
		}

	}
}
uint8_t I8080_SymbolScreen::GetOutput() {
	count_input++;
	if (count_input == 4) {
		if (mode_read_or_write == 1)
			return arrayColors[index_raw][index_col];
	}
	else if (count_input == 5) {
		count_input = 0;
		if (mode_read_or_write == 1)
			return arraySymbols[index_raw][index_col];
	}
	return 0;
}

uint8_t I8080_SymbolScreen::GetPort() { return I8080_Port::GetPort(); }

std::vector<std::vector<uint8_t>> I8080_SymbolScreen::Get_Array_symbols() {
	return arraySymbols;
}
std::vector<std::vector<uint8_t>> I8080_SymbolScreen::Get_Array_colors() {
	return arrayColors;
}

void I8080_SymbolScreen::Reset() {
	Init();
	count_input = 0;
	index_raw = 0;
	index_col = 0;
	mode_read_or_write = 0;
	color = 0;
	symbol = 0;
}

void I8080_SymbolScreen::Init() {
	arraySymbols.erase(arraySymbols.begin(), arraySymbols.end());
	arrayColors.erase(arrayColors.begin(), arrayColors.end());

	arraySymbols.resize(20);
	arrayColors.resize(20);
	for (int i = 0; i < arraySymbols.size(); i++)
	{
		arraySymbols[i].resize(20, ' ');
		arrayColors[i].resize(20, 0);
	}

}
