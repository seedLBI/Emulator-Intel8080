#ifndef PIXEL_SCREEN_TWO_BUFFERS_MOMENTO_H
#define PIXEL_SCREEN_TWO_BUFFERS_MOMENTO_H

#include "Emulator/History/Momento.h"
#include <cstdint>
#include <vector>

class PixelScreenTwoBuffersMomento : public Momento
{
public:
	PixelScreenTwoBuffersMomento(
		const uint8_t& count_input,
		const uint8_t& index_raw,
		const uint8_t& index_col,
		const uint8_t& mode,
		const uint8_t& last_color,
		const std::vector<std::vector<uint8_t>>& Buffer1,
		const std::vector<std::vector<uint8_t>>& Buffer2);
	~PixelScreenTwoBuffersMomento();


	uint8_t get_count_input() const;
	uint8_t get_index_raw() const;
	uint8_t get_index_col() const;
	uint8_t get_mode() const;
	uint8_t get_last_color() const;
	std::vector<std::vector<uint8_t>> get_Buffer1() const;
	std::vector<std::vector<uint8_t>> get_Buffer2() const;
private:
	uint8_t count_input;
	uint8_t index_raw;
	uint8_t index_col;
	uint8_t mode;
	uint8_t last_color;
	std::vector<std::vector<uint8_t>> Buffer1;
	std::vector<std::vector<uint8_t>> Buffer2;
};



#endif // !PIXEL_SCREEN_TWO_BUFFERS_MOMENTO_H

