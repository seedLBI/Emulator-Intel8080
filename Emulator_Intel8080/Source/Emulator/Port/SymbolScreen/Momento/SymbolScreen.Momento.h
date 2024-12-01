#ifndef SYMBOL_SCREEN_MOMENTO_H
#define SYMBOL_SCREEN_MOMENTO_H

#include "Emulator/History/Momento.h"
#include <cstdint>

class SymbolScreenMomento : public Momento
{
public:
	SymbolScreenMomento(
		const uint8_t& count_input,
		const uint8_t& index_raw,
		const uint8_t& index_col,
		const uint8_t& mode_read_or_write,
		const uint8_t& last_color,
		const uint8_t& last_symbol);
	~SymbolScreenMomento();

	uint8_t get_count_input() const;
	uint8_t get_index_raw() const;
	uint8_t get_index_col() const;
	uint8_t get_mode_read_or_write() const;
	uint8_t get_last_color() const;
	uint8_t get_last_symbol() const;

private:
	uint8_t count_input;
	uint8_t index_raw;
	uint8_t index_col;
	uint8_t mode_read_or_write;
	uint8_t last_color;
	uint8_t last_symbol;
};




#endif // !SYMBOL_SCREEN_MOMENTO_H
