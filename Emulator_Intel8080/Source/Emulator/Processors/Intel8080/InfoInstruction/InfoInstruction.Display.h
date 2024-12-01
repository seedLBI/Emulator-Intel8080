#ifndef INFO_INSTRUCTION_DISPLAY_H
#define INFO_INSTRUCTION_DISPLAY_H

#include "InfoInstruction.Structures.h"
#include "InfoInstruction.Data.h"
#include <iostream>
#include <memory>
#include <deque>
#include "imgui.h"
#include "imgui_internal.h"
#include "IconFontCppHeaders/IconsFontAwesome6.h"
#include "Utils/ImGui.Utils.h"
#include "Utils/Values/Values.Utils.h"
#include "Utils/TextUtils.h"
#include "Utils/UTF8.h"



class Singletone_InfoInstruction
{
public:

	static Singletone_InfoInstruction& Instance();

	void Display(const std::string& name_instruction, const std::string& text_after);

private:
	Singletone_InfoInstruction();
	~Singletone_InfoInstruction();

	Singletone_InfoInstruction(Singletone_InfoInstruction const&) = delete;
	Singletone_InfoInstruction& operator= (Singletone_InfoInstruction const&) = delete; 

	
	std::string str_NameInstruction = "";
	std::string str_TextAfterInstruction = "";
	std::shared_ptr<InstructionInfo> info;
	std::vector<std::string> splited_textAfter;

	size_t MaxLengthForRightBlock = 0;

	std::deque<std::string> preCalculatedArguments;


	void CalculateLength();
	void ProcessLine(const int& line, const int& i, int& args_check_number, std::string& result_text);

	inline void DrawLeftBlock();

	inline void DrawRightBlock();


	std::vector<std::string> split_line(const std::string& line, bool& state_MultiLineComment);
};




#endif // !INFO_INSTRUCTION_DISPLAY_H
