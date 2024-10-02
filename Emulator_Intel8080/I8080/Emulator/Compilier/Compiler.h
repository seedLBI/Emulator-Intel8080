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

    virtual void Clear();

protected:
    TranslatorOutput CompilerOutput;

	std::vector<std::string> split_line(const std::string& line);
	std::vector<std::vector<std::string>> split_code (const std::vector<std::string>& code);


	bool IsAllSpecialSymbols(const std::string& command);


    enum class TypeValue {
        DEC,
        HEX,
        BIN,
        UNKNOWN
    };

    std::pair<uint64_t, TypeValue> FromString2Int(const std::string& value);


    bool CheckName(const string& name);

    int GetCountBytes(const string& cmd);
    int GetCountParams(const string& cmd);


    vector<uint8_t> TranslateInstruction(const vector<string>& splitted_command);


private:


     bool IsHexValue(const string& value);
     bool IsDecValue(const string& value);
     bool IsBinValue(const string& value);

     uint64_t StrHex2int(const std::string& value);
     uint64_t StrDec2int(const std::string& value);
     uint64_t StrBin2int(const std::string& value);


};


#endif
