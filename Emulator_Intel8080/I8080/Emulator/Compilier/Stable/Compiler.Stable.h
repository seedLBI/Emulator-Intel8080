#ifndef COMPILER_STABLE_H
#define COMPILER_STABLE_H

#include "Emulator/Compilier/Compiler.h"
#include "robin_hood.h"
#include <vector>
#include <string>


class CompilerStable : public Compiler
{
public:
	CompilerStable();
	~CompilerStable();

	TranslatorOutput Compile(const std::vector<std::string>& Code) override;

private:
	std::vector<std::vector<std::string>> splited_code;
	std::vector<int> adressed_code;

	robin_hood::unordered_flat_map<std::string, uint16_t> Consts;
	robin_hood::unordered_flat_map<std::string, uint16_t> Markers;
	std::vector<VarsDebug> Vars;

	void ClearAllArrays();


	bool Step1_MarkingAdresses();

	bool Step2_ReplaceWithDirectValues();

	bool Step3_MakeByteArray();


	void MakeError(const TypeTranslatorError& typeError,const int& Line);
};




#endif // !COMPILER_STABLE_H
