#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>
#include <fstream>

bool isFileExist(const std::string& PathFile);

bool isFileNotEmpty(std::ifstream& Fstream_File);


#endif


