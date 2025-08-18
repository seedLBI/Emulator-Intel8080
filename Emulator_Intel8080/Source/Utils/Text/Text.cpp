#include "Text.h"



std::string to_hex_string(const uint8_t& value) {
    std::stringstream sstream;
    sstream << std::hex << (uint16_t)value;

    if (sstream.str().size() == 1)
        return "0" + sstream.str();
    else
        return sstream.str();
}

std::wstring to_hex_wstring(const uint8_t& value) {
    auto s_value = to_hex_string(value);
    return std::wstring(s_value.begin(), s_value.end());
}

std::string to_hex_string(const uint16_t& value) {
    std::stringstream sstream;
    sstream << std::hex << value;

    if (sstream.str().size() < 4) {
        std::string add;
        add.append(4 - sstream.str().size(), '0');
        return add + sstream.str();
    }
    else
        return sstream.str();
}

std::wstring to_hex_wstring(const uint16_t& value) {
    auto s_value = to_hex_string(value);
    return std::wstring(s_value.begin(), s_value.end());
}

std::string to_bin_string(const uint8_t& value) {
    return std::bitset<8>(value).to_string();
}
std::wstring to_bin_wstring(const uint8_t& value) {
    auto s_value = to_bin_string(value);
    return std::wstring(s_value.begin(), s_value.end());
}

uint64_t string_formatted_to_value(const std::string& value_str) {
    long n;
    std::string type = value_str.substr(0, 2);
    if (type == "0x") {
        char* p;
        n = strtol(value_str.substr(2).c_str(), &p, 16);
    }
    else if (type == "0b") {
        char* p;
        n = strtol(value_str.substr(2).c_str(), &p, 2);
    }
    else {
        n = stoi(value_str);
    }

    return n;
}


std::vector<std::string> Split(const std::string& line, const std::string& delimiter) {
    std::string s = line;
    //std::string delimiter = delimiter;

    std::vector<std::string> result;

    size_t pos = 0;
    std::string token;

    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        result.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    if (s.length() != 0) {
        result.push_back(s);
    }
    return result;
}

void PadLeft(std::string& text, const char& symbol, int NeedLength) {
    int countDelta = NeedLength - int(text.size());
    if (countDelta < 0)
        return;
    for (int i = 0; i < countDelta; i++) {
        text.insert(text.begin(), symbol);
    }
}
void PadRight(std::string& text, const char& symbol, int NeedLength) {
    int countDelta = NeedLength - int(text.size());
    if (countDelta < 0)
        return;
    for (int i = 0; i < countDelta; i++) {
        text.push_back(symbol);
    }
}


void RemoveSubstringFromStart(std::string& text, const std::string& substring) {
    if (text.find(substring) == 0) {
        text.erase(text.begin(), text.begin() + substring.size());
    }
}



void SaveUniqueSpaces(std::string& text) {
    if (text.size() == 0) { return; }

    for (int i = int(text.size()) - 1; i > 0; --i) {
        if (text[i] == ' ' && text[i] == text[i - 1])
            text.erase(text.begin() + i);
    }
}
void EraseSideSpaces(std::string& text) {
    for (int i = 0; i < text.size() - 1; ++i) {
        if (text[i] == ' ') {
            text.erase(text.begin() + i);
            i--;
        }
        else
            break;
    }

    for (int i = int(text.size()) - 1; i >= 0; --i) {
        if (text[i] == ' ')
            text.erase(text.begin() + i);
        else
            break;
    }
}


void ToLowerAll(std::string& text) {
    for (int i = 0; i < text.size(); ++i)
        text[i] = tolower(text[i]);
}
void ToUpperALL(std::string& text) {
    for (int i = 0; i < text.size(); ++i)
        text[i] = toupper(text[i]);
}


void ReplaceAll(std::string& str, const std::string& from, const std::string& to) {
    if (from.empty())
        return;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

void DeleteAllFromFirstFindSymbol(std::string& text, const char& symbol) {
    if (text.find_first_of(symbol) != std::string::npos)
        text.erase(text.begin() + text.find_first_of(symbol), text.end());
}
void RemoveSymbolUntilUnique(std::string& text) {
    if (text.empty())
        return;
    char symbol = text[0];

    for (int i = 1; i < text.size(); i++)
    {
        if (text[i] != symbol) {
            text.erase(text.begin(), text.begin() + i);
            break;
        }
    }
}
void EraseAllSymbolType(std::string& text, const char& symbol) {
    for (int i = 0; i < text.size(); ++i)
    {
        if (text[i] == symbol)
        {
            if (i != 0 && text[i - 1] == '\\')
            {
                text.erase(text.begin() + i - 1);
                i--;
            }
            else {
                text.erase(text.begin() + i);
                i--;
            }

        }
    }
}


int GetCountLines(const std::string& Text) {
    if (Text.size() == 0)
        return 0;

    int count = 0;
    size_t it = 0;
    while (1) {
        it = Text.find('\n', it + 1);
        if (it == std::string::npos) {
            break;
        }
        count++;
    }

    return count;
}

int GetCountLinesWithText(std::ifstream& File) {
    std::string line = "";
    int count = 0;


    while (std::getline(File,line)) {
        count++;
    }

    return count;
}


std::string cutFloat(std::string input, const int& countAfterDot) {
    int pos = int(input.find('.'));
    if (pos + 1 + countAfterDot > input.size() - 1)
        return input;
    else {
        input.erase(input.begin() + pos + 1 + countAfterDot, input.end());

        for (int i = int(input.size()) - 1; i >= 0; i--)
        {
            if (input[i] == '0')
                input.erase(input.begin() + i);
            else
                break;
        }

        if (input.back() == '.')
            input.erase(input.begin() + input.size() - 1);

        return input;
    }
}

std::string GetSymbol_1251_OnNumber(const unsigned char& number_symbol) {
    const static std::vector<std::string> arr{
        u8" ",  u8" ",   u8" " , u8" ",u8" ",u8" ",u8" ",u8" ",  u8" ", u8"\\t",  u8"\\n",  u8" ",  u8" ",  u8" ",  u8" ",  u8" ",
        u8" ",  u8" ",  u8" " ,   u8" ",  u8" ",  u8" ",  u8" ",  u8" ",  u8" ",   u8" ",  u8" ",  u8" ",  u8" ",  u8" ",  u8" ",  u8" ",
        u8" ",  u8"!",   u8"\"",   u8"#",  u8"$",  u8"%",  u8"&",  u8" ",  u8"(",   u8")",  u8"*",  u8"+", u8" ",  u8" ",  u8" ",  u8"/",
        u8"0",  u8"1",   u8"2" ,   u8"3",  u8"4",  u8"5",  u8"6",  u8"7",  u8"8",   u8"9",  u8":",  u8";",  u8"<",  u8"=",  u8">",  u8"?",
        u8"@",  u8"A",   u8"B" ,   u8"C",  u8"D",  u8"E",  u8"F",  u8"G",  u8"H",   u8"I",  u8"J",  u8"K",  u8"L", u8"M",  u8"N",  u8"O",
        u8"P",  u8"Q",   u8"R" ,   u8"S",  u8"T",  u8"U",  u8"V",  u8"W",  u8"X",   u8"Y",  u8"Z",  u8"[",  u8"\\", u8"]",  u8"^",  u8"_",
        u8"`",  u8"a",   u8"b" ,   u8"c",  u8"d",  u8"e",  u8"f",  u8"g",  u8"h",   u8"i",  u8"j",  u8"k",  u8"l",  u8"m",  u8"n",  u8"o",
        u8"p",  u8"q",   u8"r" ,   u8"s",  u8"t",  u8"u",  u8"v",  u8"w",  u8"x",   u8"y",  u8"z",  u8"{",  u8"|",  u8"}",  u8"~",  u8" ",
      u8"€",u8"", u8"‚" , u8"ƒ",u8"„",u8"…",u8"†",u8"‡",u8"ˆ", u8"‰",u8"Š",u8"<",u8"Œ",u8"",u8"",u8"",
      u8"",u8"'", u8"'" , u8"\"",u8"\"",u8"•",  u8"-",u8"-",u8" ", u8"™",u8"š",u8">",u8"œ",u8"",u8"",u8"Ÿ",
      u8" ",u8"¡", u8"¢" , u8"",u8"¤",u8"¥",u8"¦",u8"§",u8"¨", u8"©",u8"ª",u8"«",u8"¬",u8" ",u8"®",u8"¯",
      u8"°",u8"±", u8"²" , u8"³",u8"´",u8"µ",u8"¶",u8"·",u8"¸", u8"¹",u8"º",u8"»",u8"¼",u8"½",u8"¾",u8"¿",
      u8"À",u8"Á", u8"Â",  u8"Ã",u8"Ä",u8"Å",u8"Æ",u8"Ç",u8"È", u8"É",u8"Ê",u8"Ë",u8"Ì",u8"Í",u8"Î",u8"Ï",
      u8"Ğ",u8"Ñ", u8"Ò",  u8"Ó",u8"Ô",u8"Õ",u8"Ö",u8"×",u8"Ø", u8"Ù",u8"Ú",u8"Û",u8"Ü",u8"İ",u8"Ş",u8"ß",
      u8"à",u8"á", u8"â",  u8"ã",u8"ä",u8"å",u8"æ",u8"ç",u8"è", u8"é",u8"ê",u8"ë",u8"ì",u8"í",u8"î",u8"ï",
      u8"ğ",u8"ñ", u8"ò",  u8"ó",u8"ô",u8"õ",u8"ö",u8"÷",u8"ø", u8"ù",u8"ú",u8"û",u8"ü",u8"ı",u8"ş",u8"ÿ"
    };

    return arr[number_symbol];;
}