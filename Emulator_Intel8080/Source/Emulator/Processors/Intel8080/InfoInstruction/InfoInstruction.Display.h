#ifndef INFO_INSTRUCTION_DISPLAY_H
#define INFO_INSTRUCTION_DISPLAY_H


#include "UI/Theme/interface/IThemeLoadable.h"
#include "InfoInstruction.Structures.h"
#include "InfoInstruction.Data.h"
#include <iostream>
#include <memory>
#include <deque>
#include <array>
#include "robin_hood.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "IconFontCppHeaders/IconsFontAwesome6.h"
#include "Utils/ImGui.Utils.h"
#include "Utils/Values/Values.Utils.h"
#include "Utils/TextUtils.h"
#include "Utils/UTF8.h"



class Singletone_InfoInstruction: public IThemeLoadable {
public:

	static Singletone_InfoInstruction& Instance();

	void Display(const std::string& name_instruction, const std::string& text_after,const bool dublicate = false);

	std::vector<NamedColor> GetDefaultLightColors() override;
	std::vector<NamedColor> GetDefaultDarkColors() override;
	void LoadColors() override;


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

	inline void DrawRightBlock(const bool& dublicate);


	std::vector<std::string> split_line(const std::string& line, bool& state_MultiLineComment);




	enum PaletteIndex {
		Background,
		NumberLinePseudoCode,
		ArgumentFirst,
		ArgumentSecond,
		AvailableArgumentsFirst,
		AvailableArgumentsSecond,
		ByteFirst,
		ByteOthers,
		FlagText,
		FlagUnaffected,
		FlagAffected,
		FlagReset,
		FlagSet,
		Attention,
		Max,
	};

	std::array < ImVec4, PaletteIndex::Max > Colors;
	robin_hood::unordered_flat_map<std::string, PaletteIndex> MapNameAndIndex;



};




#endif // !INFO_INSTRUCTION_DISPLAY_H
