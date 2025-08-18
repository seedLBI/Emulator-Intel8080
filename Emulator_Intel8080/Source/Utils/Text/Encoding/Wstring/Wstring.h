#ifndef UTILS_ENCODING_WSTRING_H
#define UTILS_ENCODING_WSTRING_H

#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include <string>
#include <codecvt>

std::wstring stringUTF8_to_wstring(const std::string& str);
std::string wstring_to_stringUTF8(const std::wstring& str);

#undef _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#endif UTILS_ENCODING_WSTRING_H