#ifndef VALUES_UTILS_H
#define VALUES_UTILS_H

#include <cstdint>
#include <string>
#include <string>
#include <sstream>
#include <iomanip>
#include "Utils/Text/Text.h"

uint64_t correct_str_toUnsignedValue(const std::string& value);

bool IsCorrectValue(const std::string& value);

bool IsHexValue(const std::string& value);
bool IsDecValue(const std::string& value);
bool IsBinValue(const std::string& value);

uint64_t StrHex2int(const std::string& value);
uint64_t StrDec2int(const std::string& value);
uint64_t StrBin2int(const std::string& value);

std::string Value2strHex(const uint64_t& value);
std::string Value2strHex_without0x(const uint64_t& value);


//std::string Value2strBin(const uint64_t& value);
std::string Value2strDec(const uint64_t& value);


#endif // !VALUES_UTILS_H


