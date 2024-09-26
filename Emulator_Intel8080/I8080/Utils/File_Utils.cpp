#include "Utils/File_Utils.h"

bool isFileExist(const std::string& PathFile) {
    if (FILE* file = fopen(PathFile.c_str(), "r")) {
        fclose(file);
        return true;
    }
    else {
        return false;
    }
}

bool isFileNotEmpty(std::ifstream& Fstream_File) {
    return !(Fstream_File.peek() == std::ifstream::traits_type::eof());
}