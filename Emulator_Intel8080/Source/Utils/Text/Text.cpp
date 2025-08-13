#include "Text.h"



std::string to_hex_string(const uint64_t& value) {
    std::stringstream sstream;
    sstream << std::hex << value;
    return sstream.str();
}

std::wstring to_hex_wstring(const uint64_t& value) {
    auto s_value = to_hex_string(value);
    return std::wstring(s_value.begin(), s_value.end());
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