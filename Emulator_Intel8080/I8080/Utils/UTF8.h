#ifndef UTF8_H
#define UTF8_H

#include <vector>
#include <string>
#include <unordered_map>
#include "Unicode.h"

enum class UTF8_SPLITER_ERROR {
    NOTHING,
    NOT_HAVE_ENOUGH_SIZE,
    UNSUPORTED_SYMBOL,
};
enum class UTF8_to_CP1251_CONVERTER_ERROR {
    NOTHING,
    UNSUPPORTED_SYMBOL
};

std::vector<std::string> utf8_splitter(const std::string& line, UTF8_SPLITER_ERROR& error);
std::pair<uint8_t, UTF8_to_CP1251_CONVERTER_ERROR> convert_utf8_toCP1251(const std::string& symbol);

std::string convertText_utf8_toCP1251(const std::string& text);



std::string Lowercase_UTF8_Symbol(const std::string& UTF8symbol);
std::string Uppercase_UTF8_Symbol(const std::string& UTF8symbol);

void Lowercase_UTF8_Text(std::vector<std::string>& UTF8Text);
void Uppercase_UTF8_Text(std::vector<std::string>& UTF8Text);


#endif // !UTF8_H
