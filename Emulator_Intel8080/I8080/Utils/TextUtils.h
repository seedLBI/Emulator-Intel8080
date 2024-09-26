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

#ifndef TEXTUTILS_H
#define TEXTUTILS_H



using namespace std;
using namespace std::string_literals;


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


#endif // !TEXTUTILS_H
