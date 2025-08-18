#include "Values.h"


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

std::string ConvertToSI(const uint64_t& value, const char* unit) {
    int Kilo = int(value / (uint64_t)1'000);
    int Mega = int(value / (uint64_t)1'000'000);
    int Giga = int(value / (uint64_t)1'000'000'000);
    int Tera = int(value / (uint64_t)1'000'000'000'000);

    std::string output;
    std::string AfterDot;

    if (Tera > 0) {
        output = std::to_string(Tera);
        AfterDot = std::to_string(value).substr(output.size());
        if (AfterDot.size() > 3)
            AfterDot.erase(AfterDot.begin() + 3, AfterDot.end());
        return output + "," + AfterDot + u8" Ò" + unit;
    }
    if (Giga > 0) {
        output = std::to_string(Giga);
        AfterDot = std::to_string(value).substr(output.size());
        if (AfterDot.size() > 3)
            AfterDot.erase(AfterDot.begin() + 3, AfterDot.end());
        return output + "," + AfterDot + u8" Ã" + unit;
    }
    if (Mega > 0) {
        output = std::to_string(Mega);
        AfterDot = std::to_string(value).substr(output.size());
        if (AfterDot.size() > 3)
            AfterDot.erase(AfterDot.begin() + 3, AfterDot.end());
        return output + "," + AfterDot + u8" Ì" + unit;
    }
    if (Kilo > 0) {
        output = std::to_string(Kilo);
        AfterDot = std::to_string(value).substr(output.size());
        if (AfterDot.size() > 3)
            AfterDot.erase(AfterDot.begin() + 3, AfterDot.end());
        return output + "," + AfterDot + u8" Ê" + unit;
    }




    return std::to_string(value) + u8" " + unit;

}