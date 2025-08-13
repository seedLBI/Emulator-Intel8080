#ifndef UTILS_TEXT_H
#define UTILS_TEXT_H

#include <vector>
#include <fstream>
#include <string>
#include <sstream>

std::vector<std::string> Split(const std::string& line, const std::string& delimiter);

std::string to_hex_string(const uint64_t& value);
std::wstring to_hex_wstring(const uint64_t& value);


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

#endif