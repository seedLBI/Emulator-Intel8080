#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include <string>
#include <vector>
#include "Utils/Text/Text.h"


std::pair<std::vector<std::string>, int> Instructuion_to_String(const uint8_t& opcode, const uint8_t& firstByte, const uint8_t& secondByte);

uint8_t GetLengthInstructionFromOpcode(const uint8_t& opcode);
bool isJump(const uint8_t& opcode);
bool isJumpCondition(const uint8_t& opcode);
bool isRet(const uint8_t& opcode);
bool isRetCondition(const uint8_t& opcode);


#endif // !DISASSEMBLER_H
