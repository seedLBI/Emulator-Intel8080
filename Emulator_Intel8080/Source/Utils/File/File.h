#ifndef UTILS_FILE_H
#define UTILS_FILE_H


#include <Windows.h>
#include <vector>
#ifdef _DEBUG
#include <iostream>
#endif
#include <string>
#include <fstream>
#include <shobjidl.h>
#include <filesystem>
#include <algorithm>
#include <codecvt>

#include "Utils/Text/Encoding/Wstring/Wstring.h"

bool isFileExist(const std::wstring& PathFile);
bool isFileExist(const std::string& PathFile);
bool isFileExist(const std::ifstream& Fstream_File);

bool isFileNotEmpty(std::ifstream& Fstream_File);

bool HaveFolder(const std::wstring& Path);
bool CreateFolder(const std::wstring& Path);


std::vector<uint8_t> ReadFileToByteArray(const std::string& filePath);

std::vector<std::string> ReadTextFromFile(const std::wstring& PathFile);
std::vector<std::string> ReadTextFromFile(const std::string& PathFile);


std::string GetPathApplication();
std::wstring GetPathDirectory();

std::wstring Open_FileDialog(const wchar_t* TitleWindow, const wchar_t* Filter, const wchar_t* defaultPath = nullptr);

std::string Save_FileDialog(const std::string& TitleWindow, const std::string& Filter);


std::wstring Open_FolderDialog(const wchar_t* TitleWindow, const wchar_t* defaultPath = nullptr);

#endif