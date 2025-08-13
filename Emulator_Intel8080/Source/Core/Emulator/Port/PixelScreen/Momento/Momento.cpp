#include "Momento.h"

PixelScreenMomento::PixelScreenMomento(const uint8_t& count_input, const uint8_t& index_raw, const uint8_t& index_col, const uint8_t& mode_read_or_write, const uint8_t& last_color) :
	Momento(0x05),
	count_input(count_input),
	index_raw(index_raw),
	index_col(index_col),
	mode_read_or_write(mode_read_or_write),
	last_color(last_color)
{

}

PixelScreenMomento::~PixelScreenMomento() {

}


uint8_t PixelScreenMomento::get_count_input() const {
	return count_input;
}
uint8_t PixelScreenMomento::get_index_raw() const {
	return index_raw;
}
uint8_t PixelScreenMomento::get_index_col() const {
	return index_col;
}
uint8_t PixelScreenMomento::get_mode_read_or_write() const {
	return mode_read_or_write;
}
uint8_t PixelScreenMomento::get_last_color() const {
	return last_color;
}