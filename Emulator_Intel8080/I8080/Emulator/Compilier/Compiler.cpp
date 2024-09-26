#include "Emulator/Compilier/Compiler.h"


Compiler::Compiler() = default;
Compiler::~Compiler() = default;
TranslatorOutput Compiler::Compile(const std::vector<std::string>& Code) { return TranslatorOutput{}; }


//TODO: Доделать логику для разбиение строк на символы
std::vector<std::string> Compiler::split_line(std::string line){
    std::vector<std::string> result;


    
    const int count_Single_quotes = GetCountSymbol(line, '\'');

    if (count_Single_quotes % 2 != 0){
        CompilerOutput.Error = TypeTranslatorError::ERROR_WHERE_SECOND_SINGLE_QUOTE;
        return result;
    }

    const int count_Double_quotes = GetCountSymbol(line, '\"');

    if (count_Double_quotes % 2 != 0) {
        CompilerOutput.Error = TypeTranslatorError::ERROR_WHERE_SECOND_DOUBLE_QUOTE;
        return result;
    }


    EraseAllSymbolType(line, '\t');
    SaveUniqueSpaces(line);
    EraseSideSpaces(line);


    std::string temp = "";
    for (int i = 0; i < line.size(); ++i) {

        if (line[i] == ':') {
            temp += line[i];
            result.emplace_back(temp);
            temp = "";
            continue;
        }
        else if (line[i] == ' ') {
            if (temp.size() == 0)
                continue;
            else if (temp.size() == 1 && temp[0] == '.')
                continue;
            if (line.size() > i && line[i + 1] == ':')
                continue;



            result.emplace_back(temp);
            temp = "";
            continue;
        }
        else if (line[i] == ',') {
            if (temp.size() == 0)
                continue;
            result.emplace_back(temp);
            temp = "";
            continue;
        }

        temp += line[i];
    }

    if (temp.size() != 0)
        result.emplace_back(temp);

    return result;
}
std::vector<std::vector<std::string>> Compiler::split_code(const std::vector<std::string>& code) {
    // init size equal count lines code	
    std::vector<std::vector<std::string>> result(code.size());

    for (int i = 0; i < code.size(); ++i) {
        result[i] = split_line(code[i]);
        if (CompilerOutput.Error != TypeTranslatorError::NOTHING) {
            CompilerOutput.LineError = i;
            return result;
        }
    }

    return result;
}


bool Compiler::IsAllSpecialSymbols(const string& command) {

    static const robin_hood::unordered_flat_set<char> special_symbols = { '.', ',', ':', '[', ']', '>', '<', '\\', '/', '|','\'','\"'};

    int count = 0;
    for (char c : command) {
        if (special_symbols.contains(c))
            count++;
    }


    return command.size() == count;

}

std::pair<uint64_t, Compiler::TypeValue> Compiler::FromString2Int(const string& value) {
    if (IsHexValue(value))
        return { StrHex2int(value), Compiler::TypeValue::HEX };
    else if (IsDecValue(value))
        return { StrDec2int(value), Compiler::TypeValue::DEC };
    else if (IsBinValue(value))
        return { StrBin2int(value), Compiler::TypeValue::BIN };

    return { uint64_t(0),  Compiler::TypeValue::UNKNOWN };
}

inline bool Compiler::IsHexValue(const string& value) {
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
inline bool Compiler::IsDecValue(const string& value) {
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
inline bool Compiler::IsBinValue(const string& value) {
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

inline uint64_t Compiler::StrHex2int(const std::string& value) {
    return std::stoull(value.substr(2), nullptr, 16);
}
inline uint64_t Compiler::StrDec2int(const std::string& value) {
    return std::stoull(value);
}
inline uint64_t Compiler::StrBin2int(const std::string& value) {
    return std::stoull(value.substr(2), nullptr, 2);
}


