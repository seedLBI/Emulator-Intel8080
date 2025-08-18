#include "Widget.TableInstruction.h"

Widget_TableInstruction::Widget_TableInstruction() : I8080_Widget(u8"Таблица инструкций") {
	instruction.resize(256);

	GetAllInstruction();
}

Widget_TableInstruction::~Widget_TableInstruction() {

}

void Widget_TableInstruction::Draw() {

	if (GetFlagShow() == false)
		return;


	ImGuiStyle& style = ImGui::GetStyle();
	int prev_cellPadding = style.CellPadding.y;
	style.CellPadding.y = 1;

	ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_FirstUseEver);


	if (ImGui::Begin(GetName_c_str(), GetPtrFlagShow())) {

		const ImGuiWindowFlags flagsTable = ImGuiTableFlags_Borders | ImGuiTableFlags_NoHostExtendX;

		ImGui::BeginTable("TableOfInstruction",17, flagsTable); {

			ImGui::TableSetupColumn(std::to_string(0).c_str(), ImGuiTableColumnFlags_WidthFixed, ImGui::GetFontSize() * 2.f);

			for (int i = 1; i < 17; i++){
				ImGui::TableSetupColumn(std::to_string(i).c_str(), ImGuiTableColumnFlags_WidthStretch);
			}

			ImGui::TableNextRow(0, ImGui::GetFontSize()*2.5f);
			for (int i = 0; i < 16; i++)
			{
				ImGui::TableSetColumnIndex(i + 1);
				std::string value = to_hex_string(uint8_t(i)).substr(1, 1);
				ToUpperALL(value);
				TextCenteredOnLine(value.c_str(), i, 0, 0.5f, true);
			}




			for (int row = 1; row < 17; row++)
			{
				ImGui::TableNextRow(0, ImGui::GetFontSize()*2.5f);

				for (int col = 1; col < 17; col++)
				{
					//(0.6f, 0.6f, 0.6f, 1f)
					int index = (row - 1) * 16 + (col - 1);
					ImGui::TableSetColumnIndex(col);


					std::string i1 = instruction[index].first, i2 = instruction[index].second;

					ImColor ColorBG;

					if (i1[0] == '*')
						ColorBG = Singleton_I8080_HighlighterInstruction::Instance().GetColorFromName(i1.substr(1));
					else
						ColorBG = Singleton_I8080_HighlighterInstruction::Instance().GetColorFromName(i1);


					ImColor BG_system = ImGui::GetStyleColorVec4(ImGuiCol_WindowBg);

					float mix_coef = 0.5f;

					ColorBG.Value.x = BG_system.Value.x * mix_coef + ColorBG.Value.x * (1.f - mix_coef);
					ColorBG.Value.y = BG_system.Value.y * mix_coef + ColorBG.Value.y * (1.f - mix_coef);
					ColorBG.Value.z = BG_system.Value.z * mix_coef + ColorBG.Value.z * (1.f - mix_coef);


					if (sqrtf(powf(ColorBG.Value.x,2.f) + powf(ColorBG.Value.y, 2.f) + powf(ColorBG.Value.z, 2.f)) > sqrtf(powf(0.5f, 2.f) + powf(0.5f, 2.f) + powf(0.5f, 2.f)))
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0., 0., 0., 1));
					else
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1., 1., 1., 1));





					if (i2.empty())
						TextCenteredOnLine((i1).c_str(), col - 1, row - 1, 0.5f, true);
					else
						TextCenteredOnLine((i1 + " " + i2).c_str(), col - 1, row - 1,0.5f,true);
					//TextCenteredOnLine((instruction[index].first ).c_str(), col - 1, row - 1, 0.5f, true);
					ImGui::PopStyleColor();


					if (ImGui::TableGetHoveredColumn() == col && ImGui::TableGetHoveredRow() == row){
						ToLowerAll(i1); ToLowerAll(i2);
						ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, ImColor(1.f, 1.f, 1.f, 1.f));

						if (i1[0] == '*') {
							Singletone_InfoInstruction::Instance().Display(i1.substr(1), i2, true);
						}
						else {
							Singletone_InfoInstruction::Instance().Display(i1, i2);
						}

					}
					else {
						ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, ColorBG);
					}
					//ImGui::Text(Name_commands[(row - 1) * 16 + (col - 1)].c_str());

				}

				//ImGui::TableNextRow(0, ImGui::GetFontSize() * 2.5);
				ImGui::TableSetColumnIndex(0);

				std::string value = to_hex_string((uint8_t)(row - 1)).substr(1, 1);
				ToUpperALL(value);
				TextCenteredOnLine(value.c_str(), 0, row, 0.5f, true);
			}






			ImGui::EndTable();
		}


		ImGui::End();
	}



}

void Widget_TableInstruction::Update() {
	UpdateActive();
}


void Widget_TableInstruction::GetAllInstruction() {

	for (const auto& [key, value] : map_InstructionInfo) {

		std::vector<uint8_t> opcodes;
		for (int i = 0; i < value._Opcodes.size(); i++) {


			if (i != 0 && value._Opcodes[i - 1] == value._Opcodes[i]) {
				for (int j = value._Opcodes[i] + 1; j <= value._Opcodes[i + 1]; j++)
					opcodes.emplace_back(j);
				i++;
			}
			else {
				opcodes.emplace_back(value._Opcodes[i]);
			}

		}

		int indexUsedOpcode = 0;

		std::string result = key;

		ToUpperALL(result);

		if (value._Arguments.size() == 2) {

			if (value._Arguments[0] == value._Arguments[1]) {
				//result += " ";
				auto info = ENUM_Arguments_to_CommandArguments(value._Arguments[0]);

				for (int i = 0; i < info.available_values.size(); i++) {
					for (int j = 0; j < info.available_values.size(); j++) {
						if (info.available_values[i] == info.available_values[j] && info.available_values[i] == "M")
							continue;
						instruction[opcodes[indexUsedOpcode]] = { result, info.available_values[i] + ", " + info.available_values[j] };
						indexUsedOpcode++;
					}
				}
			}
			else {
				auto info = ENUM_Arguments_to_CommandArguments(value._Arguments[0]);
				auto info2 = ENUM_Arguments_to_CommandArguments(value._Arguments[1]);

				if (value._Arguments[0] == InstructionArguments::Value16)
					info.type_argument = "i16";
				else if (value._Arguments[0] == InstructionArguments::Value8)
					info.type_argument = "i8";

				if (value._Arguments[1] == InstructionArguments::Value16)
					info2.type_argument = "i16";
				else if (value._Arguments[1] == InstructionArguments::Value8)
					info2.type_argument = "i8";


				for (int i = 0; i < info.available_values.size(); i++) {
					instruction[opcodes[indexUsedOpcode]] = { result, info.available_values[i] + ", " + info2.type_argument };
					indexUsedOpcode++;
				}
			}

		}
		else if (value._Arguments.size() == 1)
		{
			auto info = ENUM_Arguments_to_CommandArguments(value._Arguments[0]);

			if (value._Arguments[0] == InstructionArguments::Value16 || value._Arguments[0] == InstructionArguments::Value8) {
				if (value._Arguments[0] == InstructionArguments::Value16)
					info.type_argument = "i16";
				else if (value._Arguments[0] == InstructionArguments::Value8)
					info.type_argument = "i8";

				instruction[opcodes[indexUsedOpcode]] = { result, info.type_argument };
				indexUsedOpcode++;
				if (opcodes.size() > 0) {
					for (int i = 1; i < opcodes.size(); i++) {
						instruction[opcodes[indexUsedOpcode]] = { "*" + result, info.type_argument };
						indexUsedOpcode++;
					}
				}
			}
			else if (value._Arguments[0] == InstructionArguments::ValueSpecial) {
				for (int i = 0; i < 8; i++) {
					instruction[opcodes[indexUsedOpcode]] = { result, std::to_string(i) };
					indexUsedOpcode++;
				}
			}
			else {
				for (int i = 0; i < info.available_values.size(); i++) {
					instruction[opcodes[indexUsedOpcode]] = { result, info.available_values[i] };
					indexUsedOpcode++; 
				}
			}



		}
		else {
			instruction[opcodes[indexUsedOpcode]] = { result,""};
			indexUsedOpcode++;
			if (opcodes.size() > 0) {
				for (int i = 1; i < opcodes.size(); i++) {
					instruction[opcodes[indexUsedOpcode]] = { "*" + result,""};
					indexUsedOpcode++;
				}
			}


		}
	}

	//sort(instruction.begin(), instruction.end());
}



nlohmann::json Widget_TableInstruction::Save() {
	return SaveDefaultParameters();
}
void Widget_TableInstruction::Load(const nlohmann::json& Data) {
	ReadDefaultParameters(Data);
}