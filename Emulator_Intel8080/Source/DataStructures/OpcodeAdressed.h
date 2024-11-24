#ifndef OPCODE_ADRESSED_H
#define OPCODE_ADRESSED_H

#include <string>

struct OpcodeAdressed {
	unsigned int adress_h;
	unsigned int adress_l;
	unsigned int opcode;
	std::string command;
	std::string marker;
	unsigned int adress_marker_h;
	unsigned int adress_marker_l;

};


#endif // !OPCODE_ADRESSED_H
