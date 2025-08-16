#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include <string>
#include <vector>
#include "Utils/Text/Text.h"


std::pair<std::vector<std::string>, int> Instructuion_to_String(const uint8_t& opcode, const uint8_t& firstByte, const uint8_t& secondByte);



#endif // !DISASSEMBLER_H
