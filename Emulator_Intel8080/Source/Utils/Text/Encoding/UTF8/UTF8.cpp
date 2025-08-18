#include "UTF8.h"


int count_symbols_utf8(const std::string& line, UTF8_SPLITER_ERROR& error) {

    int result = 0;

    size_t i = 0;
    size_t length = line.size();

    while (i < length) {
        unsigned char byte = line[i];

        // Single-byte character (ASCII)
        if ((byte & 0b10000000) == 0b00000000) {
            result++;
            i++;
        }
        // Two-byte character
        else if ((byte & 0b11100000) == 0b11000000) {
            if (i + 1 < length
                && ((line[i + 1] & 0b11000000) == 0b10000000)) {
                result++;
                i += 2;
            }
            else {
                error = UTF8_SPLITER_ERROR::NOT_HAVE_ENOUGH_SIZE;
                return result;
            }
        }
        // Three-byte character
        else if ((byte & 0b11110000) == 0b11100000) {
            if (i + 2 < length
                && ((line[i + 1] & 0b11000000) == 0b10000000)
                && ((line[i + 2] & 0b11000000) == 0b10000000)) {
                result++;
                i += 3;
            }
            else {
                error = UTF8_SPLITER_ERROR::NOT_HAVE_ENOUGH_SIZE;
                return result;
            }
        }
        // Four-byte character
        else if ((byte & 0b11111000) == 0b11110000) {
            if (i + 3 < length
                && ((line[i + 1] & 0b11000000) == 0b10000000)
                && ((line[i + 2] & 0b11000000) == 0b10000000)
                && ((line[i + 3] & 0b11000000) == 0b10000000)) {
                result++;
                i += 4;
            }
            else {
                error = UTF8_SPLITER_ERROR::NOT_HAVE_ENOUGH_SIZE;
                return result;
            }
        }
        // Unsupported symbol
        else {
            error = UTF8_SPLITER_ERROR::UNSUPORTED_SYMBOL;
            return result;
        }
    }

    error = UTF8_SPLITER_ERROR::NOTHING;  // No errors
    return result;
}

std::vector<std::string> utf8_splitter(const std::string& line, UTF8_SPLITER_ERROR& error) {
    std::vector<std::string> result;
    size_t i = 0;
    size_t length = line.size();

    while (i < length) {
        unsigned char byte = line[i];

        // Single-byte character (ASCII)
        if ((byte & 0b10000000) == 0b00000000) {
            result.emplace_back(1, byte);
            i++;
        }
        // Two-byte character
        else if ((byte & 0b11100000) == 0b11000000) {
            if (i + 1 < length
                && ((line[i + 1] & 0b11000000) == 0b10000000)) {
                result.emplace_back(line.substr(i, 2));
                i += 2;
            }
            else {
                error = UTF8_SPLITER_ERROR::NOT_HAVE_ENOUGH_SIZE;
                return result;
            }
        }
        // Three-byte character
        else if ((byte & 0b11110000) == 0b11100000) {
            if (i + 2 < length
                && ((line[i + 1] & 0b11000000) == 0b10000000)
                && ((line[i + 2] & 0b11000000) == 0b10000000)) {
                result.emplace_back(line.substr(i, 3));
                i += 3;
            }
            else {
                error = UTF8_SPLITER_ERROR::NOT_HAVE_ENOUGH_SIZE;
                return result;
            }
        }
        // Four-byte character
        else if ((byte & 0b11111000) == 0b11110000) {
            if (i + 3 < length
                && ((line[i + 1] & 0b11000000) == 0b10000000)
                && ((line[i + 2] & 0b11000000) == 0b10000000)
                && ((line[i + 3] & 0b11000000) == 0b10000000)) {
                result.emplace_back(line.substr(i, 4));
                i += 4;
            }
            else {
                error = UTF8_SPLITER_ERROR::NOT_HAVE_ENOUGH_SIZE;
                return result;
            }
        }
        // Unsupported symbol
        else {
            error = UTF8_SPLITER_ERROR::UNSUPORTED_SYMBOL;
            return result;
        }
    }

    error = UTF8_SPLITER_ERROR::NOTHING;  // No errors
    return result;
}

std::pair<uint8_t, UTF8_to_CP1251_CONVERTER_ERROR> convert_utf8_toCP1251(const std::string& symbol) {

    const static std::unordered_map<std::string, uint8_t> utf8_to_utf8cp1251{
        {u8" ",0x20},{u8"!",0x21},{u8"\"",0x22},{u8"#",0x23},{u8"$",0x24},{u8"%",0x25},{u8"&",0x26},{u8"\'",0x27},{u8"(",0x28},{u8")",0x29},{u8"*",0x2a},{u8"+",0x2b},{u8",",0x2c}, {u8"-",0x2d},{u8".",0x2e},{u8"/",0x2f},
        {u8"0",0x30},{u8"1",0x31},{u8"2",0x32}, {u8"3",0x33},{u8"4",0x34},{u8"5",0x35},{u8"6",0x36},{u8"7",0x37}, {u8"8",0x38},{u8"9",0x39},{u8":",0x3a},{u8";",0x3b},{u8"<",0x3c}, {u8"=",0x3d},{u8">",0x3e},{u8"?",0x3f},
        {u8"@",0x40},{u8"A",0x41},{u8"B",0x42}, {u8"C",0x43},{u8"D",0x44},{u8"E",0x45},{u8"F",0x46},{u8"G",0x47}, {u8"H",0x48},{u8"I",0x49},{u8"J",0x4a},{u8"K",0x4b},{u8"L",0x4c}, {u8"M",0x4d},{u8"N",0x4e},{u8"O",0x4f},
        {u8"P",0x50},{u8"Q",0x51},{u8"R",0x52}, {u8"S",0x53},{u8"T",0x54},{u8"U",0x55},{u8"V",0x56},{u8"W",0x57}, {u8"X",0x58},{u8"Y",0x59},{u8"Z",0x5a},{u8"[",0x5b},{u8"\\",0x5c},{u8"]",0x5d},{u8"^",0x5e},{u8"_",0x5f},
        {u8"`",0x60},{u8"a",0x61},{u8"b",0x62}, {u8"c",0x63},{u8"d",0x64},{u8"e",0x65},{u8"f",0x66},{u8"g",0x67}, {u8"h",0x68},{u8"i",0x69},{u8"j",0x6a},{u8"k",0x6b},{u8"l",0x6c}, {u8"m",0x6d},{u8"n",0x6e},{u8"o",0x6f},
        {u8"p",0x70},{u8"q",0x71},{u8"r",0x72}, {u8"s",0x73},{u8"t",0x74},{u8"u",0x75},{u8"v",0x76},{u8"w",0x77}, {u8"x",0x78},{u8"y",0x79},{u8"z",0x7a},{u8"{",0x7b},{u8"|",0x7c}, {u8"}",0x7d},{u8"~",0x7e},
        {u8"�",0x80},{u8"�",0x81},{u8"�",0x82}, {u8"�",0x83},{u8"�",0x84},{u8"�",0x85},{u8"�",0x86},{u8"�",0x87}, {u8"�",0x88},{u8"�",0x89},{u8"�",0x8a},{u8"�",0x8b},{u8"�",0x8c}, {u8"�",0x8d},{u8"�",0x8e},{u8"�",0x8f},
        {u8"�",0x90},{u8"�",0x91},{u8"�",0x92}, {u8"�",0x93},{u8"�",0x94},{u8"�",0x95},{u8"�",0x96},{u8"�",0x97}              ,{u8"�",0x99},{u8"�",0x9a},{u8"�",0x9b},{u8"�",0x9c}, {u8"�",0x9d},{u8"�",0x9e},{u8"�",0x9f},
                     {u8"�",0xa1},{u8"�",0xa2}, {u8"�",0xa3},{u8"�",0xa4},{u8"�",0xa5},{u8"�",0xa6},{u8"�",0xa7}, {u8"�",0xa8},{u8"�",0xa9},{u8"�",0xaa},{u8"�",0xab},{u8"�",0xac},              {u8"�",0xae},{u8"�",0xaf},
        {u8"�",0xb0},{u8"�",0xb1},{u8"�",0xb2}, {u8"�",0xb3},{u8"�",0xb4},{u8"�",0xb5},{u8"�",0xb6},{u8"�",0xb7}, {u8"�",0xb8},{u8"�",0xb9},{u8"�",0xba},{u8"�",0xbb},{u8"�",0xbc}, {u8"�",0xbd},{u8"�",0xbe},{u8"�",0xbf},
        {u8"�",0xc0},{u8"�",0xc1},{u8"�",0xc2}, {u8"�",0xc3},{u8"�",0xc4},{u8"�",0xc5},{u8"�",0xc6},{u8"�",0xc7}, {u8"�",0xc8},{u8"�",0xc9},{u8"�",0xca},{u8"�",0xcb},{u8"�",0xcc}, {u8"�",0xcd},{u8"�",0xce},{u8"�",0xcf},
        {u8"�",0xd0},{u8"�",0xd1},{u8"�",0xd2}, {u8"�",0xd3},{u8"�",0xd4},{u8"�",0xd5},{u8"�",0xd6},{u8"�",0xd7}, {u8"�",0xd8},{u8"�",0xd9},{u8"�",0xda},{u8"�",0xdb},{u8"�",0xdc}, {u8"�",0xdd},{u8"�",0xde},{u8"�",0xdf},
        {u8"�",0xe0},{u8"�",0xe1},{u8"�",0xe2}, {u8"�",0xe3},{u8"�",0xe4},{u8"�",0xe5},{u8"�",0xe6},{u8"�",0xe7}, {u8"�",0xe8},{u8"�",0xe9},{u8"�",0xea},{u8"�",0xeb},{u8"�",0xec}, {u8"�",0xed},{u8"�",0xee},{u8"�",0xef},
        {u8"�",0xf0},{u8"�",0xf1},{u8"�",0xf2}, {u8"�",0xf3},{u8"�",0xf4},{u8"�",0xf5},{u8"�",0xf6},{u8"�",0xf7}, {u8"�",0xf8},{u8"�",0xf9},{u8"�",0xfa},{u8"�",0xfb},{u8"�",0xfc}, {u8"�",0xfd},{u8"�",0xfe},{u8"�",0xff},
    };
    auto it = utf8_to_utf8cp1251.find(symbol);

    if (it != utf8_to_utf8cp1251.end()) {
        return { it->second,UTF8_to_CP1251_CONVERTER_ERROR::NOTHING };
    }
    else {
        return { 0,UTF8_to_CP1251_CONVERTER_ERROR::UNSUPPORTED_SYMBOL };
    }


}

std::string convertText_utf8_toCP1251(const std::string& text) {

    UTF8_SPLITER_ERROR error;
    auto s = utf8_splitter(text,error);

    std::string output;
    output.resize(s.size());

    for (int i = 0; i < s.size(); i++){
        output[i] = convert_utf8_toCP1251(s[i]).first;
    }

    return output;
}


std::string transliterate_rus(const std::string& utf8_text) {
    static const robin_hood::unordered_flat_map<std::string, std::string> map = {
        {u8"�", "A"},       {u8"�", "a"},
        {u8"�", "B"},       {u8"�", "b"},
        {u8"�", "V"},       {u8"�", "v"},
        {u8"�", "G"},       {u8"�", "g"},
        {u8"�", "D"},       {u8"�", "d"},
        {u8"�", "E"},       {u8"�", "e"},
        {u8"�", "Yo"},      {u8"�", "yo"},
        {u8"�", "Zh"},      {u8"�", "zh"},
        {u8"�", "Z"},       {u8"�", "z"},
        {u8"�", "I"},       {u8"�", "i"},
        {u8"�", "Y"},       {u8"�", "y"},
        {u8"�", "K"},       {u8"�", "k"},
        {u8"�", "L"},       {u8"�", "l"},
        {u8"�", "M"},       {u8"�", "m"},
        {u8"�", "N"},       {u8"�", "n"},
        {u8"�", "O"},       {u8"�", "o"},
        {u8"�", "P"},       {u8"�", "p"},
        {u8"�", "R"},       {u8"�", "r"},
        {u8"�", "S"},       {u8"�", "s"},
        {u8"�", "T"},       {u8"�", "t"},
        {u8"�", "U"},       {u8"�", "u"},
        {u8"�", "F"},       {u8"�", "f"},
        {u8"�", "Kh"},      {u8"�", "kh"},
        {u8"�", "Ts"},      {u8"�", "ts"},
        {u8"�", "Ch"},      {u8"�", "ch"},
        {u8"�", "Sh"},      {u8"�", "sh"},
        {u8"�", "Shch"},    {u8"�", "shch"},
        {u8"�", "'"},       {u8"�", "'"},
        {u8"�", "Y"},       {u8"�", "y"},
        {u8"�", "'"},       {u8"�", "'"},
        {u8"�", "E"},       {u8"�", "e"},
        {u8"�", "Yu"},      {u8"�", "yu"},
        {u8"�", "Ya"},      {u8"�", "ya"}
    };
    
    UTF8_SPLITER_ERROR error;
    auto s = utf8_splitter(utf8_text, error);

    std::string result = "";

    for (int i = 0; i < s.size(); i++) {

        if (map.contains(s[i]))
            result += map.at(s[i]);
        else
            result += s[i];

    }
    return result;
}



std::string Lowercase_UTF8_Symbol(const std::string& UTF8symbol) {
    return UnicodeValue_to_UTF8str(LowerCase_Unicode(strUTF8Symbol_to_UnicodeValue(UTF8symbol)));
}
std::string Uppercase_UTF8_Symbol(const std::string& UTF8symbol) {
    return UnicodeValue_to_UTF8str(UpperCase_Unicode(strUTF8Symbol_to_UnicodeValue(UTF8symbol)));
}


void Lowercase_UTF8_Text(std::vector<std::string>& UTF8Text) {
    for (int i = 0; i < UTF8Text.size(); i++)
        UTF8Text[i] = Lowercase_UTF8_Symbol(UTF8Text[i]);
}
void Uppercase_UTF8_Text(std::vector<std::string>& UTF8Text) {
    for (int i = 0; i < UTF8Text.size(); i++)
        UTF8Text[i] = Uppercase_UTF8_Symbol(UTF8Text[i]);
}