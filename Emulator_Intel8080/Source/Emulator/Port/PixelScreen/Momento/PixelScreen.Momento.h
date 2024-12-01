#ifndef PIXEL_SCREEN_H
#define PIXEL_SCREEN_H

#include "Emulator/History/Momento.h"
#include <cstdint>

class PixelScreenMomento : public Momento{
public:
	 PixelScreenMomento(const uint8_t& count_input,const uint8_t& index_raw,const uint8_t& index_col, const uint8_t& mode_read_or_write,const uint8_t& last_color);
	~PixelScreenMomento();


	uint8_t get_count_input() const;
	uint8_t get_index_raw() const;
	uint8_t get_index_col() const;
	uint8_t get_mode_read_or_write() const;
	uint8_t get_last_color() const;


private:
	uint8_t count_input = 0;
	uint8_t index_raw = 0;
	uint8_t index_col = 0;
	uint8_t mode_read_or_write = 0;
	uint8_t last_color = 0;
};




#endif // !PIXEL_SCREEN_H
