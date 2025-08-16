#ifndef UTILS_TEXT_H
#define UTILS_TEXT_H

#include <vector>
#include <fstream>
#include <string>
#include <bitset>
#include <sstream>
#include <numeric>

std::vector<std::string> Split(const std::string& line, const std::string& delimiter);

std::string to_hex_string(const uint8_t& value);
std::wstring to_hex_wstring(const uint8_t& value);

std::string to_hex_string(const uint16_t& value);
std::wstring to_hex_wstring(const uint16_t& value);

std::string to_bin_string(const uint8_t& value);
std::wstring to_bin_wstring(const uint8_t& value);

uint64_t string_formatted_to_value(const std::string& value_str);

void PadLeft(std::string& text, const char& symbol, int NeedLength);
void PadRight(std::string& text, const char& symbol, int NeedLength);

void SaveUniqueSpaces(std::string& text);
void EraseSideSpaces(std::string& text);

void ToLowerAll(std::string& text);
void ToUpperALL(std::string& text);

void RemoveSubstringFromStart(std::string& text, const std::string& substring);

void ReplaceAll(std::string& str, const std::string& from, const std::string& to);
void DeleteAllFromFirstFindSymbol(std::string& text, const char& symbol);
void RemoveSymbolUntilUnique(std::string& text);
void EraseAllSymbolType(std::string& text, const char& symbol);

int GetCountLines(const std::string& Text);
int GetCountLinesWithText(std::ifstream& File);
std::string cutFloat(std::string input, const int& countAfterDot);

std::string GetSymbol_1251_OnNumber(const unsigned char& number_symbol);
#endif