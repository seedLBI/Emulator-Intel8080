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



using namespace std;
using namespace std::string_literals;


std::string ConvertCP1251ToUTF8(const std::string& str);

std::string GetExeFileName();

std::string GetExePath();


string int2stringDec(const unsigned char& value);
string int2stringBin(const unsigned char& value,const int& countBits);
string int2stringBin(const unsigned char& value);
string int2stringHex(const unsigned char& value);
string int2string_0x_Hex(const unsigned char& value);
string int2stringDoubleHex(const uint16_t& value);

string int2stringDoubleHex(const unsigned char& value1,const unsigned char& value2);
string int2string_0x_DoubleHex(const unsigned char& value1,const unsigned char& value2);


unsigned int string2hex(string value);
unsigned int Adress_string_2int(string value);


std::vector<std::string> GetArguments(int argc, char* argv[]);

string cp1251_to_utf8(const char* str);
std::string utf8_encode(const std::wstring& wstr);
std::string from_utf8(const std::string& str, const std::locale& loc );
std::string from_utf8(const std::string& str);
bool is_valid_utf8(const char* string);

string GetSymbol_1251_OnNumber(const unsigned char& number_symbol);


int GetCountLines(const std::string& Text);




std::vector<uint8_t> readFileToByteArray(const std::string& filePath);


//TODO:
void AddSymbolToCount(string& text, char symbol, int count);
void SaveUniqueSpaces(string& text);
void SaveUniqueSpacesWithoutQuotes(string& text);
void EraseSideSpaces(string& text);

int GetCountSymbol(const string& text, const char& symbol);

void DeleteSideSymbols(string& text);

void DeleteAllFromFirstFindSymbol(string& text, const char& symbol);
void ToLowerAll(string& text);
void ToUpperALL(string& text);
void EraseAllSymbolType(string& text, const char& symbol);
void EraseAllSymbolType(vector<string>& text_array, const char& symbol);
void replaceAll(std::string& str, const std::string& from, const std::string& to);
vector<string> split(const string& text_, const string& delimeter_);
string cutFloat(string input, const int& countAfterDot);
vector<string> GetArrayLineFromFile(string path);
string OpenFileDialog();

string SaveFileDialogI8080();
string SaveFileDialogPNG();
string SaveFileDialogTXT();



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
