#include "PixelScreenTwoBuffers.Momento.h"

PixelScreenTwoBuffersMomento::PixelScreenTwoBuffersMomento(
	const uint8_t& count_input,
	const uint8_t& index_raw,
	const uint8_t& index_col,
	const uint8_t& mode,
	const uint8_t& last_color,
	const std::vector<std::vector<uint8_t>>& Buffer1,
	const std::vector<std::vector<uint8_t>>& Buffer2) :
	Momento(0x06),
	count_input(count_input),
	index_raw(index_raw),
	index_col(index_col),
	mode(mode),
	last_color(last_color),
	Buffer1(Buffer1),
	Buffer2(Buffer2)
{

}


PixelScreenTwoBuffersMomento::~PixelScreenTwoBuffersMomento() {

}

uint8_t PixelScreenTwoBuffersMomento::get_count_input() const {
	return count_input;
}
uint8_t PixelScreenTwoBuffersMomento::get_index_raw() const {
	return index_raw;
}
uint8_t PixelScreenTwoBuffersMomento::get_index_col() const {
	return index_col;
}
uint8_t PixelScreenTwoBuffersMomento::get_mode() const {
	return mode;
}
uint8_t PixelScreenTwoBuffersMomento::get_last_color() const {
	return last_color;
}
std::vector<std::vector<uint8_t>> PixelScreenTwoBuffersMomento::get_Buffer1() const {
	return Buffer1;
}
std::vector<std::vector<uint8_t>> PixelScreenTwoBuffersMomento::get_Buffer2() const {
	return Buffer2;
}