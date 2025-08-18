#ifndef COMPILER_STABLE_H
#define COMPILER_STABLE_H

#include "Config_Compilier.h"
#include "Core/Emulator/Compiler/Compiler.h"
#include <robin_hood.h>
#include <vector>
#include <string>

#ifdef _DEBUG
#include <iostream>
#endif


class I8080_Compiler : public Compiler
{
public:
	I8080_Compiler();
	~I8080_Compiler();

	TranslatorOutput Compile(const std::vector<std::string>& Code) override;
	void Clear() override;

private:
	std::vector<std::vector<std::string>> splited_code;
	std::vector<std::vector<std::string>> splited_code_raw;

	std::vector<int> adressed_code;
	int CounterForNeedCheck = 0;
	std::vector<int> NeedCheckThatLineIndex;




	struct PosDotInfo {
		size_t pos_dot = 0;
		size_t pos_2dot = 0;
		bool flag_have_dot = false;
		bool flag_have_2dot = false;
	};

	std::vector<PosDotInfo> PosDotForNeedLine;


	std::vector<std::pair<std::string, uint16_t>> ConstsVector;
	robin_hood::unordered_flat_map<std::string, uint16_t> Consts;
	robin_hood::unordered_flat_map<std::string, uint16_t> Markers;
	std::vector<VarsDebug> Vars;


	bool Step1_MarkingAdresses();

	bool Step2_ReplaceWithDirectValues();

	bool Step3_MakeByteArray();


	void MakeError(const TypeTranslatorError& typeError,const int& Line);
};




#endif // !COMPILER_STABLE_H
