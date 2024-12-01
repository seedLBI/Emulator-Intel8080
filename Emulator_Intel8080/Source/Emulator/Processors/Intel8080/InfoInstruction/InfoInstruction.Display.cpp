#include "InfoInstruction.Display.h"



void Singletone_InfoInstruction::Display(const std::string& name_instruction, const std::string& text_after) {

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




	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.15, 0.15, 0.15, 1.0));
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

	DrawRightBlock();


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
			else if (info->_PseudoCode[line][i].type() == typeid(ENUM_Arguments)) {
				auto obj = std::any_cast<ENUM_Arguments>(info->_PseudoCode[line][i]);
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

						if (obj == ENUM_Arguments::Register16_WithSP_low)
							coomandValues = ENUM_Arguments_to_CommandArguments(ENUM_Arguments::Register16_WithSP).available_values;
						else if (obj == ENUM_Arguments::Register16_WithPSW_low)
							coomandValues = ENUM_Arguments_to_CommandArguments(ENUM_Arguments::Register16_WithPSW).available_values;

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
					case ENUM_Arguments::Register8: {
						result_text = ValueArg;
						break;
					}
					case ENUM_Arguments::Register16_WithSP:
					case ENUM_Arguments::Register16_WithPSW:
					case ENUM_Arguments::Register16_OnlyBD: {
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
					case ENUM_Arguments::Register16_WithSP_high:
					case ENUM_Arguments::Register16_WithPSW_high: {
						if (ValueArg == "SP")
							result_text = u8"SP.Стар";
						else
							result_text = ValueArg;

						break;
					}
					case ENUM_Arguments::Register16_WithSP_low:
					case ENUM_Arguments::Register16_WithPSW_low: {
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
					case ENUM_Arguments::Value8:
						if (IsCorrectValue(splited_textAfter[args_check_number])) {

							uint64_t value = correct_str_toUnsignedValue(splited_textAfter[args_check_number]);

							if (value > 255)
								break;

							result_text = Value2strHex(value);

						}
						break;
					case ENUM_Arguments::Value16:
						if (IsCorrectValue(splited_textAfter[args_check_number])) {

							uint64_t value = correct_str_toUnsignedValue(splited_textAfter[args_check_number]);

							if (value > 65535)
								break;

							result_text = Value2strHex(value);

						}
						break;
					case ENUM_Arguments::Value16_low:
						if (IsCorrectValue(splited_textAfter[args_check_number])) {

							uint64_t value = correct_str_toUnsignedValue(splited_textAfter[args_check_number]);

							if (value > 65535)
								break;

							result_text = Value2strHex(value%256);

						}
						break;
					case ENUM_Arguments::Value16_high:
						if (IsCorrectValue(splited_textAfter[args_check_number])) {

							uint64_t value = correct_str_toUnsignedValue(splited_textAfter[args_check_number]);

							if (value > 65535)
								break;

							result_text = Value2strHex(value / 256);

						}
						break;
					case ENUM_Arguments::ValueSpecial:
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
				case ENUM_Arguments::Register8:
				case ENUM_Arguments::Register16_WithSP:
				case ENUM_Arguments::Register16_WithSP_low:
				case ENUM_Arguments::Register16_WithSP_high:
				case ENUM_Arguments::Register16_WithPSW:
				case ENUM_Arguments::Register16_WithPSW_low:
				case ENUM_Arguments::Register16_WithPSW_high:
				case ENUM_Arguments::Register16_OnlyBD:
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
			else if (info->_PseudoCode[line][i].type() == typeid(ENUM_Branching)) {
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
			DrawTextWithBackground(CommandArgs_first.type_argument.c_str(), ImVec4(0.4f, 0.4f, 0.f, 1.f));
		}
		if (info->_Arguments.size() > 1) {
			CommandArgs_second = ENUM_Arguments_to_CommandArguments(info->_Arguments[1]);
			ImGui::SameLine(0, 0);
			ImGui::Text(", ");
			ImGui::SameLine(0, 0);
			DrawTextWithBackground(CommandArgs_second.type_argument.c_str(), ImVec4(0.6f, 0.4f, 0.f, 1.f));
		}

		if (info->_Arguments.size() > 0) {
			ImGui::SeparatorText(CommandArgs_first.type_argument.c_str());

			ImGui::Text("");
			for (int i = 0; i < CommandArgs_first.available_values.size(); i++) {
				ImGui::SameLine(0, 0);
				DrawTextWithBackground(CommandArgs_first.available_values[i].c_str(), ImVec4(0.1f, 0.3f, 0.6f, 1.f));
				ImGui::SameLine(0, 0);
				ImGui::Text(" ");
			}
		}
		if (info->_Arguments.size() > 1 && info->_Arguments[0] != info->_Arguments[1]) {
			ImGui::SeparatorText(CommandArgs_second.type_argument.c_str());

			ImGui::Text("");
			for (int i = 0; i < CommandArgs_second.available_values.size(); i++) {
				ImGui::SameLine(0, 0);
				DrawTextWithBackground(CommandArgs_second.available_values[i].c_str(), ImVec4(0.1f, 0.3f, 0.6f, 1.f));
				ImGui::SameLine(0, 0);
				ImGui::Text(" ");
			}
		}




		ImGui::SeparatorText(u8"Байты");
		DrawTextWithBackground(ENUM_Bytes_to_str(ENUM_Bytes::Opcode).c_str(), ImVec4(0.1f, 0.4f, 0.5f, 1.f));
		ImGui::SameLine();
		ImGui::Text(" ");
		for (int i = 0; i < info->_Bytes.size(); i++) {
			ImGui::SameLine();
			DrawTextWithBackground(ENUM_Bytes_to_str(info->_Bytes[i]).c_str(), ImVec4(0.6f, 0.3f, 0.1f, 1.f));
			ImGui::SameLine();
			ImGui::Text(" ");
		}


		ImGui::SeparatorText(u8"Такты");
		ImGui::TextWrapped(Get_info_ticks_mean(info->_Ticks, info->_TicksMean).c_str());



		static const std::vector<ImVec4> ColorStatusFlag = {
			ImVec4(1.f,0.3f,0.3f,1.f),
			ImVec4(0.3f,1.0f,0.3f,1.f),
			ImVec4(1.f, 1.f, 0.2f, 1.f),
			ImVec4(1.f, 1.f, 0.2f, 1.f),
		};


		ImGui::SeparatorText(u8"Флаги");
		ImGui::TextColored(ImVec4(1.f, 0.81f, 0.05f, 1.f), "Sign       ");
		ImGui::SameLine();
		ImGui::TextColored(ColorStatusFlag[(int)info->_Flags_status.Sign], std::string(ENUM_FlagsState_to_str(info->_Flags_status.Sign)).c_str());

		ImGui::Separator();

		ImGui::TextColored(ImVec4(1.f, 0.81f, 0.05f, 1.f), "Zero       ");
		ImGui::SameLine();
		ImGui::TextColored(ColorStatusFlag[(int)info->_Flags_status.Zero], std::string(ENUM_FlagsState_to_str(info->_Flags_status.Zero)).c_str());

		ImGui::Separator();

		ImGui::TextColored(ImVec4(1.f, 0.81f, 0.05f, 1.f), "A. Carry   ");
		ImGui::SameLine();
		ImGui::TextColored(ColorStatusFlag[(int)info->_Flags_status.ACarry], std::string(ENUM_FlagsState_to_str(info->_Flags_status.ACarry)).c_str());

		ImGui::Separator();

		ImGui::TextColored(ImVec4(1.f, 0.81f, 0.05f, 1.f), "Parity     ");
		ImGui::SameLine();
		ImGui::TextColored(ColorStatusFlag[(int)info->_Flags_status.Parity], std::string(ENUM_FlagsState_to_str(info->_Flags_status.Parity)).c_str());

		ImGui::Separator();

		ImGui::TextColored(ImVec4(1.f, 0.81f, 0.05f, 1.f), "Carry      ");
		ImGui::SameLine();
		ImGui::TextColored(ColorStatusFlag[(int)info->_Flags_status.Carry], std::string(ENUM_FlagsState_to_str(info->_Flags_status.Carry)).c_str());

		ImGui::EndChild();
	}


}

inline void Singletone_InfoInstruction::DrawRightBlock() {

	ImGui::BeginChild("RightBlock_Instruction", ImVec2(0, 0), ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_Border); {

		ImGui::SeparatorText(u8"Описание");
		ImGui::TextWrapped(info->_Declaration.c_str());

		ImGui::SeparatorText(u8"Псевдокод");



		int LineNumber = 0;


		for (int line = 0; line < info->_PseudoCode.size(); line++) {
			LineNumber++;


			if (info->_PseudoCode[line][0].type() == typeid(ENUM_Branching)) {
				LineNumber = 0;
			}
			else {
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.65, 0.65, 0.65, 1));
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
	else if (info->_PseudoCode[line][i].type() == typeid(ENUM_Arguments)) {

		auto obj = std::any_cast<ENUM_Arguments>(info->_PseudoCode[line][i]);
		auto Args = ENUM_Arguments_to_CommandArguments(obj);

		std::string temp = ENUM_Arguments_to_CommandArguments(obj).type_argument;


		if (str_TextAfterInstruction.empty() == false) {
			//splited_textAfter


			int IndexArg = -1;
			std::string ValueArg = "";



			if (splited_textAfter.empty() == false && splited_textAfter.size() - 1 >= args_check_number) {
				ToUpperALL(splited_textAfter[args_check_number]);

				std::vector<std::string>::iterator it;
				std::vector<std::string> coomandValues = Args.available_values;

				if (obj == ENUM_Arguments::Register16_WithSP_low)
					coomandValues = ENUM_Arguments_to_CommandArguments(ENUM_Arguments::Register16_WithSP).available_values;
				else if (obj == ENUM_Arguments::Register16_WithPSW_low)
					coomandValues = ENUM_Arguments_to_CommandArguments(ENUM_Arguments::Register16_WithPSW).available_values;


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
				case ENUM_Arguments::Register8: {
					temp = ValueArg;
					break;
				}
				case ENUM_Arguments::Register16_WithSP:
				case ENUM_Arguments::Register16_WithPSW:
				case ENUM_Arguments::Register16_OnlyBD: {
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
				case ENUM_Arguments::Register16_WithSP_high:
				case ENUM_Arguments::Register16_WithPSW_high:
				case ENUM_Arguments::Register16_WithPSW_low:
				case ENUM_Arguments::Register16_WithSP_low: {
					temp = ValueArg;
					break;
				}
				default:
					break;
				}

			}
			else {
				if (splited_textAfter.size() - 1 >= args_check_number)
				{

					switch (obj)
					{
					case ENUM_Arguments::Value8:
						if (IsCorrectValue(splited_textAfter[args_check_number])) {

							uint64_t value = correct_str_toUnsignedValue(splited_textAfter[args_check_number]);

							if (value > 255)
								break;

							temp = Value2strHex(value);

						}
						break;
					case ENUM_Arguments::Value16:
						if (IsCorrectValue(splited_textAfter[args_check_number])) {

							uint64_t value = correct_str_toUnsignedValue(splited_textAfter[args_check_number]);

							if (value > 65535)
								break;

							temp = Value2strHex(value);

						}
						break;
					case ENUM_Arguments::Value16_low:
						if (IsCorrectValue(splited_textAfter[args_check_number])) {

							uint64_t value = correct_str_toUnsignedValue(splited_textAfter[args_check_number]);

							if (value > 65535)
								break;

							temp = Value2strHex(value % 256);

						}
						break;
					case ENUM_Arguments::Value16_high:
						if (IsCorrectValue(splited_textAfter[args_check_number])) {

							uint64_t value = correct_str_toUnsignedValue(splited_textAfter[args_check_number]);

							if (value > 65535)
								break;

							temp = Value2strHex(value / 256);

						}
						break;
					case ENUM_Arguments::ValueSpecial:
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
		case ENUM_Arguments::Register8:
		case ENUM_Arguments::Register16_WithSP:
		case ENUM_Arguments::Register16_WithSP_low:
		case ENUM_Arguments::Register16_WithSP_high:
		case ENUM_Arguments::Register16_WithPSW:
		case ENUM_Arguments::Register16_WithPSW_low:
		case ENUM_Arguments::Register16_WithPSW_high:
		case ENUM_Arguments::Register16_OnlyBD:
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
	else if (info->_PseudoCode[line][i].type() == typeid(ENUM_Branching)) {
		auto obj = std::any_cast<ENUM_Branching>(info->_PseudoCode[line][i]);

		result_text += ENUM_Branching_to_str(obj);
	}
}


Singletone_InfoInstruction::Singletone_InfoInstruction() {

}
Singletone_InfoInstruction::~Singletone_InfoInstruction() {

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








/*
void Draw_InstructionInfo(const std::string& name_instruction,const std::string& after_instruction_line) {
	if (map_InstructionInfo.contains(name_instruction) == false)
		return;

	InstructionInfo info = map_InstructionInfo.at(name_instruction);


	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.15, 0.15, 0.15, 1.0));
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10.0f, 10.0f));


	ImGui::SetWindowFontScale(1.f);
	ImVec2 sizeText1 = ImGui::CalcTextSize("                               ");
	ImVec2 sizeText2 = ImGui::CalcTextSize("                                            ");


	ImGui::SetNextWindowSize(ImVec2(sizeText1.x + sizeText2.x, 0));



	ImGui::BeginTooltip();

	ImGui::BeginChild("LeftBlock_Instruction", ImVec2(sizeText1.x, 0), ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_Border); {

		ImGui::SeparatorText(u8"Аргументы");

		std::string command = name_instruction;

		for (int i = 0; i < command.size(); i++)
			command[i] = toupper(command[i]);



		ImGui::Text(command.c_str());



		CommandArguments CommandArgs_first, CommandArgs_second;


		if (info._Arguments.size() > 0) {
			CommandArgs_first = ENUM_Arguments_to_CommandArguments(info._Arguments[0]);
			ImGui::SameLine(0, 0);
			ImGui::Text(" ");
			ImGui::SameLine(0, 0);
			DrawTextWithBackground(CommandArgs_first.type_argument.c_str(), ImVec4(0.4f, 0.4f, 0.f, 1.f));
		}
		if (info._Arguments.size() > 1) {
			CommandArgs_second = ENUM_Arguments_to_CommandArguments(info._Arguments[1]);
			ImGui::SameLine(0, 0);
			ImGui::Text(", ");
			ImGui::SameLine(0, 0);
			DrawTextWithBackground(CommandArgs_second.type_argument.c_str(), ImVec4(0.6f, 0.4f, 0.f, 1.f));
		}

		if (info._Arguments.size() > 0) {
			ImGui::SeparatorText(CommandArgs_first.type_argument.c_str());

			ImGui::Text("");
			for (int i = 0; i < CommandArgs_first.available_values.size(); i++) {
				ImGui::SameLine(0, 0);
				DrawTextWithBackground(CommandArgs_first.available_values[i].c_str(), ImVec4(0.1f, 0.3f, 0.6f, 1.f));
				ImGui::SameLine(0, 0);
				ImGui::Text(" ");
			}
		}
		if (info._Arguments.size() > 1 && info._Arguments[0] != info._Arguments[1]) {
			ImGui::SeparatorText(CommandArgs_second.type_argument.c_str());

			ImGui::Text("");
			for (int i = 0; i < CommandArgs_second.available_values.size(); i++) {
				ImGui::SameLine(0, 0);
				DrawTextWithBackground(CommandArgs_second.available_values[i].c_str(), ImVec4(0.1f, 0.3f, 0.6f, 1.f));
				ImGui::SameLine(0, 0);
				ImGui::Text(" ");
			}
		}




		ImGui::SeparatorText(u8"Байты");
		DrawTextWithBackground(ENUM_Bytes_to_str(ENUM_Bytes::Opcode).c_str(), ImVec4(0.1f, 0.4f, 0.5f, 1.f));
		ImGui::SameLine();
		ImGui::Text(" ");
		for (int i = 0; i < info._Bytes.size(); i++) {
			ImGui::SameLine();
			DrawTextWithBackground(ENUM_Bytes_to_str(info._Bytes[i]).c_str(), ImVec4(0.6f, 0.3f, 0.1f, 1.f));
			ImGui::SameLine();
			ImGui::Text(" ");
		}


		ImGui::SeparatorText(u8"Такты");
		ImGui::TextWrapped(Get_info_ticks_mean(info._Ticks, info._TicksMean).c_str());



		static const std::vector<ImVec4> ColorStatusFlag = {
			ImVec4(1.f,0.3f,0.3f,1.f),
			ImVec4(0.3f,1.0f,0.3f,1.f),
			ImVec4(1.f, 1.f, 0.2f, 1.f),
			ImVec4(1.f, 1.f, 0.2f, 1.f),
		};


		ImGui::SeparatorText(u8"Флаги");
		ImGui::TextColored(ImVec4(1.f, 0.81f, 0.05f, 1.f), "Sign       ");
		ImGui::SameLine();
		ImGui::TextColored(ColorStatusFlag[(int)info._Flags_status.Sign], std::string(ENUM_FlagsState_to_str(info._Flags_status.Sign)).c_str());

		ImGui::Separator();

		ImGui::TextColored(ImVec4(1.f, 0.81f, 0.05f, 1.f), "Zero       ");
		ImGui::SameLine();
		ImGui::TextColored(ColorStatusFlag[(int)info._Flags_status.Zero], std::string(ENUM_FlagsState_to_str(info._Flags_status.Zero)).c_str());

		ImGui::Separator();

		ImGui::TextColored(ImVec4(1.f, 0.81f, 0.05f, 1.f), "A. Carry   ");
		ImGui::SameLine();
		ImGui::TextColored(ColorStatusFlag[(int)info._Flags_status.ACarry], std::string(ENUM_FlagsState_to_str(info._Flags_status.ACarry)).c_str());

		ImGui::Separator();

		ImGui::TextColored(ImVec4(1.f, 0.81f, 0.05f, 1.f), "Parity     ");
		ImGui::SameLine();
		ImGui::TextColored(ColorStatusFlag[(int)info._Flags_status.Parity], std::string(ENUM_FlagsState_to_str(info._Flags_status.Parity)).c_str());

		ImGui::Separator();

		ImGui::TextColored(ImVec4(1.f, 0.81f, 0.05f, 1.f), "Carry      ");
		ImGui::SameLine();
		ImGui::TextColored(ColorStatusFlag[(int)info._Flags_status.Carry], std::string(ENUM_FlagsState_to_str(info._Flags_status.Carry)).c_str());

		ImGui::EndChild();
	}


	ImGui::SameLine(0.f, 8.f);

	ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical, 4.f);

	ImGui::SameLine(0.f, 8.f);



	ImGui::BeginChild("RightBlock_Instruction", ImVec2(0, 0), ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_Border); {

		ImGui::SeparatorText(u8"Описание");
		ImGui::TextWrapped(info._Declaration.c_str());

		ImGui::SeparatorText(u8"Псевдокод");

		bool tttt = false;
		auto tokens = split_line_for_instruction_info(after_instruction_line, tttt);
		for (int i = 0; i < tokens.size(); i++)
			ToUpperALL(tokens[i]);

		int countArguments = 0;
		for (int i = 0; i < info._PseudoCode.size(); i++) {

			if (info._PseudoCode[i].type() == typeid(const char*)) {
				auto obj = std::any_cast<const char*>(info._PseudoCode[i]);
				ImGui::Text(obj);
			}
			else if (info._PseudoCode[i].type() == typeid(ENUM_Arguments)) {
				countArguments++;
				auto obj = std::any_cast<ENUM_Arguments>(info._PseudoCode[i]);

				bool AllOK = false;





				if (tokens.size() >= countArguments) {

					std::vector<std::string> available, temp1;

					int countSymbolsNeed = ENUM_Arguments_to_CommandArguments(obj).type_argument.size() - 2;

					switch (obj)
					{
					case ENUM_Arguments::Value16: {

						if (IsCorrectValue(tokens[countArguments-1])) {
							if (correct_str_toUnsignedValue(tokens[countArguments - 1]) <= 65535)
								AllOK = true;
							else
								break;

							ToLowerAll(tokens[countArguments - 1]);

							if (tokens[countArguments - 1].size() < countSymbolsNeed - 1)
							{
								int delta = countSymbolsNeed - tokens[countArguments - 1].size() - 1;
								for (int i = 0; i < delta; i++)
									tokens[countArguments - 1] += " ";
							}

							ImGui::SameLine();
							ImGui::Text(tokens[countArguments-1].c_str());
							ImGui::SameLine();
						}
						break;
					}
					case ENUM_Arguments::Value8: {

						if (IsCorrectValue(tokens[countArguments-1])) {

							if (correct_str_toUnsignedValue(tokens[countArguments - 1]) <= 255)
								AllOK = true;
							else
								break;
							
							ToLowerAll(tokens[countArguments - 1]);

							if (tokens[countArguments - 1].size() < countSymbolsNeed - 1)
							{
								int delta = countSymbolsNeed - tokens[countArguments - 1].size() - 1;
								for (int i = 0; i < delta; i++)
									tokens[countArguments - 1] += " ";
							}

							ImGui::SameLine();
							ImGui::Text(tokens[countArguments-1].c_str());
							ImGui::SameLine();
						}
						break;
					}
					case ENUM_Arguments::ValueSpecial: {

						if (IsCorrectValue(tokens[countArguments - 1])) {

							if (correct_str_toUnsignedValue(tokens[countArguments - 1]) <= 8)
								AllOK = true;
							else
								break;

							ToLowerAll(tokens[countArguments - 1]);

							if (tokens[countArguments - 1].size() < countSymbolsNeed - 1)
							{
								int delta = countSymbolsNeed - tokens[countArguments - 1].size() - 1;
								for (int i = 0; i < delta; i++)
									tokens[countArguments - 1] += " ";
							}


							ImGui::SameLine();
							ImGui::Text(tokens[countArguments - 1].c_str());
							ImGui::SameLine();
						}
						break;
					}
					case ENUM_Arguments::Register16_WithPSW_low: {

						available = ENUM_Arguments_to_CommandArguments(ENUM_Arguments::Register16_WithPSW).available_values;
						temp1 = ENUM_Arguments_to_CommandArguments(ENUM_Arguments::Register16_WithPSW_low).available_values;

						auto it = std::find(available.begin(), available.end(), tokens[0]);

						if (it != available.end()) {
							AllOK = true;

							int index = it - available.begin();

							if (available[index].size() < countSymbolsNeed - 1) {
								int delta = countSymbolsNeed - available[index].size() - 1;
								for (int i = 0; i < delta; i++)
									available[index] += " ";
							}

							ImGui::SameLine();
							ImGui::Text(temp1[index].c_str());
							ImGui::SameLine();
						}
						break;
					}
					case ENUM_Arguments::Register16_WithPSW_high: {

						available = ENUM_Arguments_to_CommandArguments(ENUM_Arguments::Register16_WithPSW).available_values;
						temp1 = ENUM_Arguments_to_CommandArguments(ENUM_Arguments::Register16_WithPSW_high).available_values;

						auto it = std::find(available.begin(), available.end(), tokens[0]);

						if (it != available.end()) {
							AllOK = true;

							int index = it - available.begin();

							if (available[index].size() < countSymbolsNeed - 1) {
								int delta = countSymbolsNeed - available[index].size() - 1;
								for (int i = 0; i < delta; i++)
									available[index] += " ";
							}

							ImGui::SameLine();
							ImGui::Text(temp1[index].c_str());
							ImGui::SameLine();
						}
						break;
					}
					case ENUM_Arguments::Register8: {

						available = ENUM_Arguments_to_CommandArguments(ENUM_Arguments::Register8).available_values;

						auto it = std::find(available.begin(), available.end(), tokens[countArguments - 1]);

						if (it != available.end()) {
							AllOK = true;

							int index = it - available.begin();

							if (available[index].size() < countSymbolsNeed - 1){
								int delta = countSymbolsNeed - available[index].size() - 1;
								for (int i = 0; i < delta; i++)
									available[index] += " ";
							}

							ImGui::SameLine();
							ImGui::Text(available[index].c_str());
							ImGui::SameLine();
						}

						break;
					}
					case ENUM_Arguments::Register16_OnlyBD: {

						available = ENUM_Arguments_to_CommandArguments(ENUM_Arguments::Register16_OnlyBD).available_values;

						auto it = std::find(available.begin(), available.end(), tokens[countArguments - 1]);

						if (it != available.end()) {
							AllOK = true;

							int index = it - available.begin();

							if (available[index].size() < countSymbolsNeed - 1) {
								int delta = countSymbolsNeed - available[index].size() - 1;
								for (int i = 0; i < delta; i++)
									available[index] += " ";
							}

							ImGui::SameLine();
							ImGui::Text(available[index].c_str());
							ImGui::SameLine();
						}

						break;
					}
					case ENUM_Arguments::Register16_WithSP: {

						available = ENUM_Arguments_to_CommandArguments(ENUM_Arguments::Register16_WithSP).available_values;

						auto it = std::find(available.begin(), available.end(), tokens[countArguments - 1]);

						if (it != available.end()) {
							AllOK = true;

							int index = it - available.begin();

							if (available[index].size() < countSymbolsNeed - 1) {
								int delta = countSymbolsNeed - available[index].size() - 1;
								for (int i = 0; i < delta; i++)
									available[index] += " ";
							}

							ImGui::SameLine();
							ImGui::Text(available[index].c_str());
							ImGui::SameLine();
						}

						break;
					}
					case ENUM_Arguments::Register16_WithPSW : {

						available = ENUM_Arguments_to_CommandArguments(ENUM_Arguments::Register16_WithPSW).available_values;

						auto it = std::find(available.begin(), available.end(), tokens[countArguments - 1]);

						if (it != available.end()) {
							AllOK = true;

							int index = it - available.begin();

							if (available[index].size() < countSymbolsNeed - 1) {
								int delta = countSymbolsNeed - available[index].size() - 1;
								for (int i = 0; i < delta; i++)
									available[index] += " ";
							}

							ImGui::SameLine();
							ImGui::Text(available[index].c_str());
							ImGui::SameLine();
						}

						break;
					}
					default:
						break;
					}
				}
					



				if (AllOK == false) {
					std::string text = ENUM_Arguments_to_CommandArguments(obj).type_argument;

					ImGui::SameLine();
					ImGui::Text(text.c_str());
					ImGui::SameLine();

				}


			}
		}



		ImGui::EndChild();
	}


	ImGui::EndTooltip();


	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}
*/

