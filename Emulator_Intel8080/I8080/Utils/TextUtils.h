#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <codecvt>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <bitset>
#include <Windows.h>
#include <fstream>
#include "utf8.h"
#include "robin_hood.h"


#ifndef TEXTUTILS_H
#define TEXTUTILS_H





std::string ConvertCP1251ToUTF8(const std::string& str);

std::string GetExeFileName();

std::string GetExePath();


std::string int2stringDec(const unsigned char& value);
std::string int2stringBin(const unsigned char& value, const int& countBits);
std::string int2stringBin(const unsigned char& value);
std::string int2stringHex(const unsigned char& value);
std::string int2string_0x_Hex(const unsigned char& value);
std::string int2stringDoubleHex(const uint16_t& value);

std::string int2stringDoubleHex(const unsigned char& value1,const unsigned char& value2);
std::string int2string_0x_DoubleHex(const unsigned char& value1,const unsigned char& value2);


unsigned int string2hex(std::string value);
unsigned int Adress_string_2int(std::string value);


std::vector<std::string> GetArguments(int argc, char* argv[]);

std::string cp1251_to_utf8(const char* str);
std::string utf8_encode(const std::wstring& wstr);
std::string from_utf8(const std::string& str, const std::locale& loc );
std::string from_utf8(const std::string& str);
bool is_valid_utf8(const char* string);

std::string GetSymbol_1251_OnNumber(const unsigned char& number_symbol);


int GetCountLines(const std::string& Text);




std::vector<uint8_t> readFileToByteArray(const std::string& filePath);


//TODO:
void AddSymbolToCount(std::string& text, char symbol, int count);
void SaveUniqueSpaces(std::string& text);
void SaveUniqueSpacesWithoutQuotes(std::string& text);
void EraseSideSpaces(std::string& text);

int GetCountSymbol(const std::string& text, const char& symbol);

void DeleteSideSymbols(std::string& text);

void DeleteAllFromFirstFindSymbol(std::string& text, const char& symbol);
void ToLowerAll(std::string& text);
void ToUpperALL(std::string& text);
void EraseAllSymbolType(std::string& text, const char& symbol);
void EraseAllSymbolType(std::vector<std::string>& text_array, const char& symbol);
void replaceAll(std::string& str, const std::string& from, const std::string& to);
std::vector<std::string> split(const std::string& text_, const std::string& delimeter_);
std::string cutFloat(std::string input, const int& countAfterDot);
std::vector<std::string> GetArrayLineFromFile(std::string path);
std::string OpenFileDialog();

std::string SaveFileDialogI8080();
std::string SaveFileDialogPNG();
std::string SaveFileDialogTXT();



std::wstring stringUTF8_to_wstring(const std::string& str);
std::string wstring_to_stringUTF8(const std::wstring& str);



enum class UTF8_SPLITER_ERROR {
	NOTHING,
	NOT_HAVE_ENOUGH_SIZE,
	UNSUPORTED_SYMBOL,
};

std::vector<std::string> utf8_splitter(const std::string& line, UTF8_SPLITER_ERROR& error);


enum class UTF8_to_CP1251_CONVERTER_ERROR {
    NOTHING,
    UNSUPPORTED_SYMBOL
};

std::pair<uint8_t, UTF8_to_CP1251_CONVERTER_ERROR> convert_utf8_toUTF8cp1251(const std::string& symbol);


#endif // !TEXTUTILS_H
