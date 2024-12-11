#include "InfoInstruction.Display.h"



void Singletone_InfoInstruction::Display(const std::string& name_instruction, const std::string& text_after, const bool dublicate) {



	if (map_InstructionInfo.contains(name_instruction) == false)
		return;


	if (str_NameInstruction != name_instruction || str_TextAfterInstruction != text_after){
		str_NameInstruction = name_instruction;
		str_TextAfterInstruction = text_after;

		ToLowerAll(str_NameInstruction);
		ToLowerAll(str_TextAfterInstruction);

		info = std::make_shared<InstructionInfo>(map_InstructionInfo.at(name_instruction));
		bool temp = false;
		splited_textAfter = split_line(str_TextAfterInstruction, temp);
		CalculateLength();
	}




	ImGui::PushStyleColor(ImGuiCol_ChildBg, Colors[PaletteIndex::Background]);
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10.0f, 10.0f));

	ImGui::SetWindowFontScale(1.f);
	ImVec2 sizeText1 = ImGui::CalcTextSize("                               ");
	ImVec2 sizeText2 = ImGui::CalcTextSize("                                             ");

	ImGui::SetNextWindowSize(ImVec2(sizeText1.x + sizeText2.x, 0));


	ImGui::BeginTooltip();

	DrawLeftBlock();

	ImGui::SameLine(0.f, 8.f);
	ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical, 4.f);
	ImGui::SameLine(0.f, 8.f);

	DrawRightBlock(dublicate);


	ImGui::EndTooltip();

	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}


void Singletone_InfoInstruction::CalculateLength() {

	preCalculatedArguments.clear();
	MaxLengthForRightBlock = 0;

	for (int line = 0; line < info->_PseudoCode.size(); line++) {

		std::string line_text_before_equal = "";
		bool isCorrectLine = true;

		int args_check_number = 0;
		for (int i = 0; i < info->_PseudoCode[line].size(); i++){

			std::string result_text;

			if (info->_PseudoCode[line][i].type() == typeid(const char*)) {
				auto obj = std::any_cast<const char*>(info->_PseudoCode[line][i]);

				if (obj[0] == '=')
					break;
				else
					line_text_before_equal += obj;

			}
			else if (info->_PseudoCode[line][i].type() == typeid(InstructionArguments)) {
				auto obj = std::any_cast<InstructionArguments>(info->_PseudoCode[line][i]);
				auto Args = ENUM_Arguments_to_CommandArguments(obj);

				result_text = Args.type_argument;

				if (str_TextAfterInstruction.empty() == false){
					//splited_textAfter


					int IndexArg = -1;
					std::string ValueArg = "";
					if (splited_textAfter.empty() == false && splited_textAfter.size() - 1 >= args_check_number) {
						ToUpperALL(splited_textAfter[args_check_number]);

						std::vector<std::string>::iterator it;
						std::vector<std::string> coomandValues = Args.available_values;

						if (obj == InstructionArguments::Register16_WithSP_low)
							coomandValues = ENUM_Arguments_to_CommandArguments(InstructionArguments::Register16_WithSP).available_values;
						else if (obj == InstructionArguments::Register16_WithSP_high)
							coomandValues = ENUM_Arguments_to_CommandArguments(InstructionArguments::Register16_WithSP).available_values;
						else if (obj == InstructionArguments::Register16_WithPSW_low)
							coomandValues = ENUM_Arguments_to_CommandArguments(InstructionArguments::Register16_WithPSW).available_values;
						else if (obj == InstructionArguments::Register16_WithPSW_high)
							coomandValues = ENUM_Arguments_to_CommandArguments(InstructionArguments::Register16_WithPSW).available_values;


						it = std::find(coomandValues.begin(), coomandValues.end(), splited_textAfter[args_check_number]);
						bool isIndexFinded = it != coomandValues.end();

						if (isIndexFinded) {
							IndexArg = it - coomandValues.begin();
							ValueArg = Args.available_values[IndexArg];
						}

					}

					


					bool AllCorrectForCustom = IndexArg != -1;
					
					
					switch (obj)
					{
					case InstructionArguments::Register8: {
						result_text = ValueArg;
						break;
					}
					case InstructionArguments::Register16_WithSP:
					case InstructionArguments::Register16_WithPSW:
					case InstructionArguments::Register16_OnlyBD: {
						result_text = ValueArg;

						if (ValueArg == "B")
							result_text += "_C";
						else if (ValueArg == "D")
							result_text += "_E";
						else if (ValueArg == "H")
							result_text += "_L";
						else if (ValueArg == "PSW")
							result_text += "_A";

						break;
					}
					case InstructionArguments::Register16_WithSP_high:
					case InstructionArguments::Register16_WithPSW_high: {
						if (ValueArg == "SP")
							result_text = u8"SP.Стар";
						else
							result_text = ValueArg;

						break;
					}
					case InstructionArguments::Register16_WithSP_low:
					case InstructionArguments::Register16_WithPSW_low: {
						if (ValueArg == "B")
							result_text = "C";
						else if (ValueArg == "D")
							result_text = "E";
						else if (ValueArg == "H")
							result_text = "L";
						else if (ValueArg == "PSW")
							result_text = "A";
						else if (ValueArg == "SP")
							result_text = u8"SP.Млад";
						else
							result_text = ValueArg;
						break;
					}
					case InstructionArguments::Value8:
						if (IsCorrectValue(splited_textAfter[args_check_number])) {

							uint64_t value = correct_str_toUnsignedValue(splited_textAfter[args_check_number]);

							if (value > 255)
								break;

							result_text = Value2strHex(value);

						}
						break;
					case InstructionArguments::Value16:
						if (IsCorrectValue(splited_textAfter[args_check_number])) {

							uint64_t value = correct_str_toUnsignedValue(splited_textAfter[args_check_number]);

							if (value > 65535)
								break;

							result_text = Value2strHex(value);

						}
						break;
					case InstructionArguments::Value16_low:
						if (IsCorrectValue(splited_textAfter[args_check_number])) {

							uint64_t value = correct_str_toUnsignedValue(splited_textAfter[args_check_number]);

							if (value > 65535)
								break;

							result_text = Value2strHex(value%256);

						}
						break;
					case InstructionArguments::Value16_high:
						if (IsCorrectValue(splited_textAfter[args_check_number])) {

							uint64_t value = correct_str_toUnsignedValue(splited_textAfter[args_check_number]);

							if (value > 65535)
								break;

							result_text = Value2strHex(value / 256);

						}
						break;
					case InstructionArguments::ValueSpecial:
						if (IsCorrectValue(splited_textAfter[args_check_number])) {

							uint64_t value = correct_str_toUnsignedValue(splited_textAfter[args_check_number]);

							if (value > 7)
								break;

							result_text = std::to_string(value);

						}
						break;
					default:
						break;
					}



				}








				switch (obj) {
				case InstructionArguments::Register8:
				case InstructionArguments::Register16_WithSP:
				case InstructionArguments::Register16_WithSP_low:
				case InstructionArguments::Register16_WithSP_high:
				case InstructionArguments::Register16_WithPSW:
				case InstructionArguments::Register16_WithPSW_low:
				case InstructionArguments::Register16_WithPSW_high:
				case InstructionArguments::Register16_OnlyBD:
					if (line_text_before_equal.back() != '['){
						result_text.insert(result_text.begin(), '[');
						result_text.push_back(']');
					}
					break;
				default:
					break;
				}

				line_text_before_equal += result_text;


				const static std::vector<std::string> NoIncrementForThisInstruction = { "inr","inx","dcr","dcx" };
				if (std::find(NoIncrementForThisInstruction.begin(), NoIncrementForThisInstruction.end(), str_NameInstruction) == NoIncrementForThisInstruction.end())
					args_check_number++;

			}
			else if (info->_PseudoCode[line][i].type() == typeid(InstructionBranching)) {
				isCorrectLine = false;
				break;


			}

		}

		if (isCorrectLine) {
			UTF8_SPLITER_ERROR error;
			size_t count_symbols = count_symbols_utf8(line_text_before_equal, error);

			MaxLengthForRightBlock = std::max(count_symbols, MaxLengthForRightBlock);
		}

	}


}

inline void Singletone_InfoInstruction::DrawLeftBlock() {

	ImVec2 sizeText1 = ImGui::CalcTextSize("                               ");

	ImGui::BeginChild("LeftBlock_Instruction", ImVec2(sizeText1.x, 0), ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_Border); {

		ImGui::SeparatorText(u8"Аргументы");

		std::string command = str_NameInstruction;

		for (int i = 0; i < command.size(); i++)
			command[i] = toupper(command[i]);



		ImGui::Text(command.c_str());



		CommandArguments CommandArgs_first, CommandArgs_second;


		if (info->_Arguments.size() > 0) {
			CommandArgs_first = ENUM_Arguments_to_CommandArguments(info->_Arguments[0]);
			ImGui::SameLine(0, 0);
			ImGui::Text(" ");
			ImGui::SameLine(0, 0);
			DrawTextWithBackground(CommandArgs_first.type_argument.c_str(), Colors[PaletteIndex::ArgumentFirst]);
		}
		if (info->_Arguments.size() > 1) {
			CommandArgs_second = ENUM_Arguments_to_CommandArguments(info->_Arguments[1]);
			ImGui::SameLine(0, 0);
			ImGui::Text(", ");
			ImGui::SameLine(0, 0);
			DrawTextWithBackground(CommandArgs_second.type_argument.c_str(), Colors[PaletteIndex::ArgumentSecond]);
		}

		if (info->_Arguments.size() > 0) {
			ImGui::SeparatorText(CommandArgs_first.type_argument.c_str());

			ImGui::Text("");
			for (int i = 0; i < CommandArgs_first.available_values.size(); i++) {
				ImGui::SameLine(0, 0);
				DrawTextWithBackground(CommandArgs_first.available_values[i].c_str(), Colors[PaletteIndex::AvailableArgumentsFirst]);
				ImGui::SameLine(0, 0);
				ImGui::Text(" ");
			}
		}
		if (info->_Arguments.size() > 1 && info->_Arguments[0] != info->_Arguments[1]) {
			ImGui::SeparatorText(CommandArgs_second.type_argument.c_str());

			ImGui::Text("");
			for (int i = 0; i < CommandArgs_second.available_values.size(); i++) {
				ImGui::SameLine(0, 0);
				DrawTextWithBackground(CommandArgs_second.available_values[i].c_str(), Colors[PaletteIndex::AvailableArgumentsSecond]);
				ImGui::SameLine(0, 0);
				ImGui::Text(" ");
			}
		}




		ImGui::SeparatorText(u8"Байты");
		DrawTextWithBackground(ENUM_Bytes_to_str(InstructionBytes::Opcode).c_str(), Colors[PaletteIndex::ByteFirst]);
		ImGui::SameLine();
		ImGui::Text(" ");
		for (int i = 0; i < info->_Bytes.size(); i++) {
			ImGui::SameLine();
			DrawTextWithBackground(ENUM_Bytes_to_str(info->_Bytes[i]).c_str(), Colors[PaletteIndex::ByteOthers]);
			ImGui::SameLine();
			ImGui::Text(" ");
		}


		ImGui::SeparatorText(u8"Такты");
		ImGui::TextWrapped(Get_info_ticks_mean(info->_Ticks, info->_TicksMean).c_str());




		ImGui::SeparatorText(u8"Флаги");
		ImGui::TextColored(Colors[PaletteIndex::FlagText], "Sign       ");
		ImGui::SameLine();
		ImGui::TextColored(Colors[PaletteIndex::FlagUnaffected + (int)info->_Flags_status.Sign], std::string(ENUM_FlagsState_to_str(info->_Flags_status.Sign)).c_str());

		ImGui::Separator();

		ImGui::TextColored(Colors[PaletteIndex::FlagText], "Zero       ");
		ImGui::SameLine();
		ImGui::TextColored(Colors[PaletteIndex::FlagUnaffected + (int)info->_Flags_status.Zero], std::string(ENUM_FlagsState_to_str(info->_Flags_status.Zero)).c_str());

		ImGui::Separator();

		ImGui::TextColored(Colors[PaletteIndex::FlagText], "A. Carry   ");
		ImGui::SameLine();
		ImGui::TextColored(Colors[PaletteIndex::FlagUnaffected + (int)info->_Flags_status.ACarry], std::string(ENUM_FlagsState_to_str(info->_Flags_status.ACarry)).c_str());

		ImGui::Separator();

		ImGui::TextColored(Colors[PaletteIndex::FlagText], "Parity     ");
		ImGui::SameLine();
		ImGui::TextColored(Colors[PaletteIndex::FlagUnaffected + (int)info->_Flags_status.Parity], std::string(ENUM_FlagsState_to_str(info->_Flags_status.Parity)).c_str());

		ImGui::Separator();

		ImGui::TextColored(Colors[PaletteIndex::FlagText], "Carry      ");
		ImGui::SameLine();
		ImGui::TextColored(Colors[PaletteIndex::FlagUnaffected + (int)info->_Flags_status.Carry], std::string(ENUM_FlagsState_to_str(info->_Flags_status.Carry)).c_str());

		ImGui::EndChild();
	}


}

inline void Singletone_InfoInstruction::DrawRightBlock(const bool& dublicate) {

	ImGui::BeginChild("RightBlock_Instruction", ImVec2(0, 0), ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_Border); {

		ImGui::SeparatorText(u8"Описание");
		ImGui::TextWrapped(info->_Declaration.c_str());

		ImGui::SeparatorText(u8"Псевдокод");



		int LineNumber = 0;


		for (int line = 0; line < info->_PseudoCode.size(); line++) {
			LineNumber++;


			if (info->_PseudoCode[line][0].type() == typeid(InstructionBranching)) {
				LineNumber = 0;
			}
			else {
				ImGui::PushStyleColor(ImGuiCol_Text, Colors[PaletteIndex::NumberLinePseudoCode]);
				ImGui::Text((std::to_string(LineNumber) + ".").c_str());
				ImGui::SameLine(0, 0);
				ImGui::PopStyleColor();
			}


			std::string result_text = "";
			int args_check_number = 0;

			for (int i = 0; i < info->_PseudoCode[line].size(); i++) {
				ProcessLine(line, i, args_check_number, result_text);
			}

			ImGui::Text(result_text.c_str());
		}

		if (dublicate){

			ImGui::PushStyleColor(ImGuiCol_Text, Colors[PaletteIndex::Attention]);
			ImGui::SeparatorText(u8"Внимание!");
			ImGui::PopStyleColor();
			ImGui::TextWrapped(u8"Этот опкод официально не задокументирован, но при работе, оригинальный процессор выполняет именно эту инструкцию.");

		}


		ImGui::EndChild();
	}

}

void Singletone_InfoInstruction::ProcessLine(const int& line, const int& i, int& args_check_number, std::string& result_text) {

	if (info->_PseudoCode[line][i].type() == typeid(const char*)) {
		auto obj = std::any_cast<const char*>(info->_PseudoCode[line][i]);

		if (obj[0] == '=') {

			UTF8_SPLITER_ERROR error;
			size_t count_symbols = count_symbols_utf8(result_text, error);


			if (count_symbols < MaxLengthForRightBlock) {


				int delta = MaxLengthForRightBlock - count_symbols;

				for (int k = 0; k < delta; k++)
					result_text.push_back(' ');

			}

			result_text += " " + std::string(obj) + " ";
		}
		else
			result_text += obj;

	}
	else if (info->_PseudoCode[line][i].type() == typeid(InstructionArguments)) {

		auto obj = std::any_cast<InstructionArguments>(info->_PseudoCode[line][i]);
		auto Args = ENUM_Arguments_to_CommandArguments(obj);

		std::string temp = ENUM_Arguments_to_CommandArguments(obj).type_argument;


		if (splited_textAfter.empty() == false && str_TextAfterInstruction.empty() == false) {
			//splited_textAfter


			int IndexArg = -1;
			std::string ValueArg = "";



			if (splited_textAfter.empty() == false && splited_textAfter.size() - 1 >= args_check_number) {
				ToUpperALL(splited_textAfter[args_check_number]);

				std::vector<std::string>::iterator it;
				std::vector<std::string> coomandValues = Args.available_values;

				if (obj == InstructionArguments::Register16_WithSP_low)
					coomandValues = ENUM_Arguments_to_CommandArguments(InstructionArguments::Register16_WithSP).available_values;
				else if (obj == InstructionArguments::Register16_WithSP_high)
					coomandValues = ENUM_Arguments_to_CommandArguments(InstructionArguments::Register16_WithSP).available_values;
				else if (obj == InstructionArguments::Register16_WithPSW_low)
					coomandValues = ENUM_Arguments_to_CommandArguments(InstructionArguments::Register16_WithPSW).available_values;
				else if (obj == InstructionArguments::Register16_WithPSW_high)
					coomandValues = ENUM_Arguments_to_CommandArguments(InstructionArguments::Register16_WithPSW).available_values;

				it = std::find(coomandValues.begin(), coomandValues.end(), splited_textAfter[args_check_number]);
				bool isIndexFinded = it != coomandValues.end();

				if (isIndexFinded) {
					IndexArg = it - coomandValues.begin();
					ValueArg = Args.available_values[IndexArg];
				}

			}

			bool AllCorrectForCustom = IndexArg != -1;

			if (AllCorrectForCustom)
			{
				switch (obj)
				{
				case InstructionArguments::Register8: {
					temp = ValueArg;
					break;
				}
				case InstructionArguments::Register16_WithSP:
				case InstructionArguments::Register16_WithPSW:
				case InstructionArguments::Register16_OnlyBD: {
					temp = ValueArg;

					if (ValueArg == "B")
						temp += "C";
					else if (ValueArg == "D")
						temp += "E";
					else if (ValueArg == "H")
						temp += "L";
					else if (ValueArg == "PSW")
						temp += "_A";

					break;
				}
				case InstructionArguments::Register16_WithSP_high:
				case InstructionArguments::Register16_WithPSW_high:
				case InstructionArguments::Register16_WithPSW_low:
				case InstructionArguments::Register16_WithSP_low: {
					temp = ValueArg;
					break;
				}
				default:
					break;
				}

			}
			else {
				if (splited_textAfter.empty() == false && splited_textAfter.size() - 1 >= args_check_number)
				{

					switch (obj)
					{
					case InstructionArguments::Value8:
						if (IsCorrectValue(splited_textAfter[args_check_number])) {

							uint64_t value = correct_str_toUnsignedValue(splited_textAfter[args_check_number]);

							if (value > 255)
								break;

							temp = Value2strHex(value);

						}
						break;
					case InstructionArguments::Value16:
						if (IsCorrectValue(splited_textAfter[args_check_number])) {

							uint64_t value = correct_str_toUnsignedValue(splited_textAfter[args_check_number]);

							if (value > 65535)
								break;

							temp = Value2strHex(value);

						}
						break;
					case InstructionArguments::Value16_low:
						if (IsCorrectValue(splited_textAfter[args_check_number])) {

							uint64_t value = correct_str_toUnsignedValue(splited_textAfter[args_check_number]);

							if (value > 65535)
								break;

							temp = Value2strHex(value % 256);

						}
						break;
					case InstructionArguments::Value16_high:
						if (IsCorrectValue(splited_textAfter[args_check_number])) {

							uint64_t value = correct_str_toUnsignedValue(splited_textAfter[args_check_number]);

							if (value > 65535)
								break;

							temp = Value2strHex(value / 256);

						}
						break;
					case InstructionArguments::ValueSpecial:
						if (IsCorrectValue(splited_textAfter[args_check_number])) {

							uint64_t value = correct_str_toUnsignedValue(splited_textAfter[args_check_number]);

							if (value > 7)
								break;

							temp = std::to_string(value);

						}
						break;
					default:
						break;
					}

				}

			}



		}




		switch (obj)
		{
		case InstructionArguments::Register8:
		case InstructionArguments::Register16_WithSP:
		case InstructionArguments::Register16_WithSP_low:
		case InstructionArguments::Register16_WithSP_high:
		case InstructionArguments::Register16_WithPSW:
		case InstructionArguments::Register16_WithPSW_low:
		case InstructionArguments::Register16_WithPSW_high:
		case InstructionArguments::Register16_OnlyBD:
			if (result_text.back() != '[') {
				temp.insert(temp.begin(), '[');
				temp.push_back(']');
			}

			break;
		default:
			break;
		}

		result_text += temp;

		const static std::vector<std::string> NoIncrementForThisInstruction = { "inr","inx","dcr","dcx" };
		if (std::find(NoIncrementForThisInstruction.begin(), NoIncrementForThisInstruction.end(), str_NameInstruction) == NoIncrementForThisInstruction.end())
			args_check_number++;

	}
	else if (info->_PseudoCode[line][i].type() == typeid(InstructionBranching)) {
		auto obj = std::any_cast<InstructionBranching>(info->_PseudoCode[line][i]);

		result_text += ENUM_Branching_to_str(obj);
	}
}

Singletone_InfoInstruction::Singletone_InfoInstruction() : IThemeLoadable(u8"Подсказка к инструкциям") {
	Colors = {
		ImVec4(0.15, 0.15, 0.15, 1.0),	// Background
		ImVec4(0.65, 0.65, 0.65, 1),	// NumberLinePseudoCode
		ImVec4(0.4f, 0.4f, 0.f, 1.f),	// ArgumentFirst
		ImVec4(0.6f, 0.4f, 0.f, 1.f),	// ArgumentSecond
		ImVec4(0.1f, 0.3f, 0.6f, 1.f),	// AvailableArgumentsFirst
		ImVec4(0.1f, 0.3f, 0.6f, 1.f),	// AvailableArgumentsSecond
		ImVec4(0.1f, 0.4f, 0.5f, 1.f),	// ByteFirst
		ImVec4(0.6f, 0.3f, 0.1f, 1.f),	// ByteOthers
		ImVec4(1.f, 0.81f, 0.05f, 1.f),	// FlagText
		ImVec4(1.f,0.3f,0.3f,1.f),		// FlagUnaffected
		ImVec4(0.3f,1.0f,0.3f,1.f),		// FlagAffected
		ImVec4(1.f, 1.f, 0.2f, 1.f),	// FlagReset
		ImVec4(1.f, 1.f, 0.2f, 1.f),	// FlagSet
		ImVec4(1.f, 0, 0, 1.f),			// Attention
	};

	IThemeLoadable::InitListWord({
		u8"Фон",u8"Номер линии (Псевдокод)",u8"Аргумент (первый)",u8"Аргумент (второй)",
		u8"Список аргументов (первый)",u8"Список аргументов (второй)",
		u8"Байт (первый)",u8"Байт (остальные)",u8"Название флага",u8"Флаг (не изменяется)",
		u8"Флаг (изменяется)",u8"Флаг (Устанавливается 0)",u8"Флаг (Устанавливается 1)",u8"Внимание"
		});

	MapNameAndIndex = {
		{u8"Фон",PaletteIndex::Background},
		{u8"Номер линии (Псевдокод)",PaletteIndex::NumberLinePseudoCode},
		{u8"Аргумент (первый)",PaletteIndex::ArgumentFirst},
		{u8"Аргумент (второй)",PaletteIndex::ArgumentSecond},
		{u8"Список аргументов (первый)",PaletteIndex::AvailableArgumentsFirst},
		{u8"Список аргументов (второй)",PaletteIndex::AvailableArgumentsSecond},
		{u8"Байт (первый)",PaletteIndex::ByteFirst},
		{u8"Байт (остальные)",PaletteIndex::ByteOthers},
		{u8"Название флага",PaletteIndex::FlagText},
		{u8"Флаг (не изменяется)",PaletteIndex::FlagUnaffected},
		{u8"Флаг (изменяется)",PaletteIndex::FlagAffected},
		{u8"Флаг (Устанавливается 0)",PaletteIndex::FlagReset},
		{u8"Флаг (Устанавливается 1)",PaletteIndex::FlagSet},
		{u8"Внимание", PaletteIndex::Attention}
	};

	

}
Singletone_InfoInstruction::~Singletone_InfoInstruction() {

}



std::vector<NamedColor> Singletone_InfoInstruction::GetDefaultLightColors() {
	return {
	{u8"Фон",						ImVec4(0.85, 0.85, 0.85, 1.0)},
	{u8"Номер линии (Псевдокод)",	ImColor(117,117,117,255)},
	{u8"Аргумент (первый)",			ImColor(229,229,147,255)},
	{u8"Аргумент (второй)",			ImColor(224,195,138,255)},
	{u8"Список аргументов (первый)",ImColor(229,229,147,255)},
	{u8"Список аргументов (второй)",ImColor(224,195,138,255)},
	{u8"Байт (первый)",				ImColor(156,211,229,255)},
	{u8"Байт (остальные)",			ImColor(223,181,153,255)},
	{u8"Название флага",			ImColor(86,69,0,255)},
	{u8"Флаг (не изменяется)",		ImColor(169,12,12,255)},
	{u8"Флаг (изменяется)",			ImColor(18,137,18,255)},
	{u8"Флаг (Устанавливается 0)",	ImColor(135,0,111,255)},
	{u8"Флаг (Устанавливается 1)",	ImColor(135,0,111,255)},
	{u8"Внимание",					ImVec4(1.f, 0, 0, 1.f)}
	};
}
std::vector<NamedColor> Singletone_InfoInstruction::GetDefaultDarkColors() {
	return {
		{u8"Фон",						ImVec4(0.15, 0.15, 0.15, 1.0)},
		{u8"Номер линии (Псевдокод)",	ImVec4(0.65, 0.65, 0.65, 1)},
		{u8"Аргумент (первый)",			ImVec4(0.4f, 0.4f, 0.f, 1.f)},
		{u8"Аргумент (второй)",			ImVec4(0.6f, 0.4f, 0.f, 1.f)},
		{u8"Список аргументов (первый)",ImVec4(0.4f, 0.4f, 0.f, 1.f)},
		{u8"Список аргументов (второй)",ImVec4(0.6f, 0.4f, 0.f, 1.f)},
		{u8"Байт (первый)",				ImVec4(0.1f, 0.4f, 0.5f, 1.f)},
		{u8"Байт (остальные)",			ImVec4(0.6f, 0.3f, 0.1f, 1.f)},
		{u8"Название флага",			ImVec4(1.f, 0.81f, 0.05f, 1.f)},
		{u8"Флаг (не изменяется)",		ImVec4(1.f,0.3f,0.3f,1.f)},
		{u8"Флаг (изменяется)",			ImVec4(0.3f,1.0f,0.3f,1.f)},
		{u8"Флаг (Устанавливается 0)",	ImVec4(1.f, 1.f, 0.2f, 1.f)},
		{u8"Флаг (Устанавливается 1)",	ImVec4(1.f, 1.f, 0.2f, 1.f)},
		{u8"Внимание",					ImVec4(1.f, 0, 0, 1.f)}
	};



}
void Singletone_InfoInstruction::LoadColors() {
	for (int i = 0; i < object_colors.colors.size(); i++) {

		std::string toSearch = object_colors.colors[i].nameColor;

		auto it = MapNameAndIndex.find(toSearch);
		bool ColorContains = it != MapNameAndIndex.end();

		if (ColorContains) {
			int index = static_cast<int>(it->second);
			Colors[index] = object_colors.colors[i].color;
		}
	}
}


Singletone_InfoInstruction& Singletone_InfoInstruction::Instance() {
	static Singletone_InfoInstruction obj;
	return obj;
}


std::vector<std::string> Singletone_InfoInstruction::split_line(const std::string& line, bool& state_MultiLineComment) {
	std::vector<std::string> result;

	const static std::string DoubleQuote = "\"";
	const static std::string CommentSymbol = ";";

	const static std::string Begin_MultiComment = "/*";
	const static std::string End_MultiComment = "*/";

	bool InQuote = false;

	UTF8_SPLITER_ERROR splitter_error = UTF8_SPLITER_ERROR::NOTHING;
	auto splitted_line = utf8_splitter(line, splitter_error);

	if (splitter_error != UTF8_SPLITER_ERROR::NOTHING) {
		return result;
	}


	std::string temp = "";
	for (int i = 0; i < splitted_line.size(); i++) {

		const std::string symbol = splitted_line[i];

		if (i < splitted_line.size() - 1) {

			const std::string two_symbol = splitted_line[i] + splitted_line[i + 1];

			if (two_symbol == Begin_MultiComment && state_MultiLineComment == false) {
				state_MultiLineComment = true;
				i++;
				continue;
			}
			else if (two_symbol == End_MultiComment) {
				if (state_MultiLineComment == false) {
					return result;
				}
				state_MultiLineComment = false;
				i++;
				continue;
			}

		}

		if (state_MultiLineComment) {
			continue;
		}



		if (symbol == CommentSymbol) { break; }

		if (symbol == DoubleQuote) {
			InQuote = true;
			i++;

			bool LastWasSlash = false;


			while (InQuote) {
				if (i > line.size() - 1)
					break;

				if (splitted_line[i] == DoubleQuote) {
					if (LastWasSlash) {
						auto t = convert_utf8_toCP1251(splitted_line[i]);
						if (t.second == UTF8_to_CP1251_CONVERTER_ERROR::UNSUPPORTED_SYMBOL) {
							return result;
						}
						i++;
						continue;
					}
					else {
						InQuote = false;
						break;
					}
				}
				else if (splitted_line[i] == "\\") {

					if (LastWasSlash == false) {
						LastWasSlash = true;
					}
					else {
						auto t = convert_utf8_toCP1251(splitted_line[i]);
						if (t.second == UTF8_to_CP1251_CONVERTER_ERROR::UNSUPPORTED_SYMBOL) {
							return result;
						}
						result.push_back(std::to_string(t.first));
						i++;
						continue;
					}
				}
				else {
					auto t = convert_utf8_toCP1251(splitted_line[i]);
					if (t.second == UTF8_to_CP1251_CONVERTER_ERROR::UNSUPPORTED_SYMBOL) {
						return result;
					}
					result.push_back(std::to_string(t.first));
				}

				LastWasSlash = false;


				i++;
			}

			if (InQuote) {
				//CompilerOutput.Error = ERROR_WHERE_SECOND_DOUBLE_QUOTE;
				return result;
			}

			continue;
		}

		if (symbol == ":") {
			temp += symbol;
			result.emplace_back(temp);
			temp = "";
			continue;
		}
		else if (symbol == " " || symbol == "\t") {
			if (temp.size() == 0)
				continue;
			else if (temp.size() == 1 && temp[0] == '.')
				continue;
			if (symbol.size() > i && splitted_line[i + 1] == ":")
				continue;



			result.emplace_back(temp);
			temp = "";
			continue;
		}
		else if (symbol == ",") {
			if (temp.size() == 0)
				continue;
			result.emplace_back(temp);
			temp = "";
			continue;
		}

		temp += symbol;
	}

	if (temp.size() != 0)
		result.emplace_back(temp);


	return result;
}