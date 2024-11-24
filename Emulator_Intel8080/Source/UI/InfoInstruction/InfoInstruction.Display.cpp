#include "InfoInstruction.Display.h"



void Draw_InstructionInfo(const std::string& name_instruction) {
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


		if (info._Arguments.size() > 0){
			CommandArgs_first = ENUM_Arguments_to_CommandArguments(info._Arguments[0]);
			ImGui::SameLine(0, 0);
			ImGui::Text(" ");
			ImGui::SameLine(0,0);
			DrawTextWithBackground(CommandArgs_first.type_argument.c_str(), ImVec4(0.4f, 0.4f, 0.f, 1.f));
		}
		if (info._Arguments.size() > 1) {
			CommandArgs_second = ENUM_Arguments_to_CommandArguments(info._Arguments[1]);
			ImGui::SameLine(0,0);
			ImGui::Text(", ");
			ImGui::SameLine(0,0);
			DrawTextWithBackground(CommandArgs_second.type_argument.c_str(), ImVec4(0.6f, 0.4f, 0.f, 1.f));
		}

		if (info._Arguments.size() > 0) {
			ImGui::SeparatorText(CommandArgs_first.type_argument.c_str());

			ImGui::Text("");
			for (int i = 0; i < CommandArgs_first.available_values.size(); i++) {
				ImGui::SameLine(0,0);
				DrawTextWithBackground(CommandArgs_first.available_values[i].c_str(), ImVec4(0.1f, 0.3f, 0.6f, 1.f));
				ImGui::SameLine(0,0);
				ImGui::Text(" ");
			}
		} 
		if (info._Arguments.size() > 1 && info._Arguments[0] != info._Arguments[1]) {
			ImGui::SeparatorText(CommandArgs_second.type_argument.c_str());

			ImGui::Text("");
			for (int i = 0; i < CommandArgs_second.available_values.size(); i++) {
				ImGui::SameLine(0,0);
				DrawTextWithBackground(CommandArgs_second.available_values[i].c_str(), ImVec4(0.1f, 0.3f, 0.6f, 1.f));
				ImGui::SameLine(0,0);
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
		ImGui::TextWrapped(info._PseudoCode.c_str());

		ImGui::EndChild();
	}


	ImGui::EndTooltip();


	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}

