#include "Values.Utils.h"


uint64_t correct_str_toUnsignedValue(const std::string& value) {
    if (IsHexValue(value))
        return StrHex2int(value);
    if (IsDecValue(value))
        return StrDec2int(value);
    if (IsBinValue(value))
        return StrBin2int(value);
    else
        exit(123456);
}


bool IsCorrectValue(const std::string& value) {
    if (IsHexValue(value))
        return true;
    if (IsDecValue(value))
        return true;
    if (IsBinValue(value))
        return true;
    return false;
}

bool IsHexValue(const std::string& value) {
    if (value.size() <= 2)
        return false;

    //ToLowerAll(value);

    if (value[0] != '0' || (value[1] != 'x' && value[1] != 'X'))
        return false;


    // it's hex begin
    for (int i = 2; i < value.size(); ++i) {
        char current_symbol = value[i];

        bool is_number = (current_symbol >= 48 && current_symbol <= 57);
        bool is_letter = (current_symbol >= 97 && current_symbol <= 102) || (current_symbol >= 65 && current_symbol <= 70);

        if (is_number || is_letter) {
            continue;
        }
        else {
            return false;
        }
    }

    return true;
}
bool IsDecValue(const std::string& value) {
    if (value.size() > 1) {
        if (value[0] == '0')
        {
            return false;
        }
    }
    for (int i = 0; i < value.size(); ++i) {
        char current_symbol = value[i];

        bool is_number = (current_symbol >= 48 && current_symbol <= 57);
        if (is_number == false) {
            return false;
        }
    }
    return true;
}
bool IsBinValue(const std::string& value) {
    if (value.size() <= 2)
        return false;

    //ToLowerAll(value);

    if (value[0] != '0' || (value[1] != 'b' && value[1] != 'B'))
        return false;

    // it's bin begin
    for (int i = 2; i < value.size(); ++i) {
        char current_symbol = value[i];

        bool is_number = (current_symbol >= 48 && current_symbol <= 49);

        if (is_number == false) {
            return false;
        }
    }

    return true;

}

uint64_t StrHex2int(const std::string& value) {
    return std::stoull(value.substr(2), nullptr, 16);
}
uint64_t StrDec2int(const std::string& value) {
    return std::stoull(value, nullptr, 10);
}
uint64_t StrBin2int(const std::string& value) {
    return std::stoull(value.substr(2), nullptr, 2);
}


std::string Value2strHex(const uint64_t& value) {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(1) << std::hex << (value | 0);
    std::string res = ss.str();
    if (res.size() % 2 == 1)
        res.insert(0, "0");
    ToUpperALL(res);
    res.insert(0, "0x");

    return res;
}

std::string Value2strHex_without0x(const uint64_t& value) {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(1) << std::hex << (value | 0);
    std::string res = ss.str();
    if (res.size() % 2 == 1)
        res.insert(0, "0");
    ToUpperALL(res);
    return res;
}

std::string Value2strDec(const uint64_t& value) {
    return std::to_string(value);
}