#ifndef GENERATOR_RANDOM_VALUES_MOMENTO_H
#define GENERATOR_RANDOM_VALUES_MOMENTO_H

#include "Emulator/History/Momento.h"
#include <cstdint>

class GeneratorRandomValuesMomento : public Momento
{
public:
	GeneratorRandomValuesMomento(const uint8_t& count_input, const uint8_t& range);
	~GeneratorRandomValuesMomento();

	uint8_t get_count_input() const;
	uint8_t get_range() const;

private:
	uint8_t count_input = 0;
	uint8_t range = 0;
};



#endif // !GENERATOR_RANDOM_VALUES_MOMENTO_H
