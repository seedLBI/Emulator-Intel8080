#include "Momento.h"


SymbolScreenMomento::SymbolScreenMomento(
	const uint8_t& count_input,
	const uint8_t& index_raw,
	const uint8_t& index_col,
	const uint8_t& mode_read_or_write,
	const uint8_t& last_color,
	const uint8_t& last_symbol) :
	Momento(0x07),
	count_input(count_input),
	index_raw(index_raw),
	index_col(index_col),
	mode_read_or_write(mode_read_or_write),
	last_color(last_color),
	last_symbol(last_symbol)
{

}

SymbolScreenMomento::~SymbolScreenMomento() {

}

uint8_t SymbolScreenMomento::get_count_input() const {
	return count_input;
}
uint8_t SymbolScreenMomento::get_index_raw() const {
	return index_raw;
}
uint8_t SymbolScreenMomento::get_index_col() const {
	return index_col;
}
uint8_t SymbolScreenMomento::get_mode_read_or_write() const {
	return mode_read_or_write;
}
uint8_t SymbolScreenMomento::get_last_color() const {
	return last_color;
}
uint8_t SymbolScreenMomento::get_last_symbol() const {
	return last_symbol;
}