#ifndef COMPILER_H
#define COMPILER_H

#include <vector>
#include <string>
#include "DataStructures/TranslatorOutput.h"
#include "Utils/TextUtils.h"
#include "robin_hood.h"

#define MAX16BIT 65535
#define MAX8BIT 255




class Compiler{
public:
	Compiler();
	~Compiler();
	virtual TranslatorOutput Compile(const std::vector<std::string>& Code);

protected:
    TranslatorOutput CompilerOutput;

	std::vector<std::string> split_line(std::string line);
	std::vector<std::vector<std::string>> split_code (const std::vector<std::string>& code);


	bool IsAllSpecialSymbols(const std::string& command);


    enum class TypeValue {
        DEC,
        HEX,
        BIN,
        UNKNOWN
    };

    std::pair<uint64_t, TypeValue> FromString2Int(const std::string& value);

private:


    inline bool IsHexValue(const string& value);
    inline bool IsDecValue(const string& value);
    inline bool IsBinValue(const string& value);

    inline uint64_t StrHex2int(const std::string& value);
    inline uint64_t StrDec2int(const std::string& value);
    inline uint64_t StrBin2int(const std::string& value);


};


#endif
