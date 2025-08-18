#include "GeneratorRandomValues.Momento.h"

GeneratorRandomValuesMomento::GeneratorRandomValuesMomento(const uint8_t& count_input, const uint8_t& range) :
	Momento(0x09),
	count_input(count_input),
	range(range)
{

}

GeneratorRandomValuesMomento::~GeneratorRandomValuesMomento() {

}

uint8_t GeneratorRandomValuesMomento::get_count_input() const {
	return count_input;
}

uint8_t GeneratorRandomValuesMomento::get_range() const {
	return range;
}