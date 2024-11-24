#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>
#include <fstream>
#include "Utils/TextUtils.h"


bool isFileExist(std::string& PathFile);
bool isFileExist(std::ifstream& Fstream_File);

bool isFileNotEmpty(std::ifstream& Fstream_File);


#endif


