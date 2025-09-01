#include "Widget.ListInstruction.h"


Widget_ListInstruction::Widget_ListInstruction() : I8080_Widget(u8"Список инструкций") {
	GetAllInstruction();
}

Widget_ListInstruction::~Widget_ListInstruction() {

}

void Widget_ListInstruction::Draw() {

	if (GetFlagShow() == false)
		return;


	ImGuiStyle& style = ImGui::GetStyle();
	style.CellPadding.y = 1;

	ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_FirstUseEver);


	if (ImGui::Begin(GetName_c_str(), GetPtrFlagShow())) {

		
		for (int i = 0; i < instruction.size(); i++) {
			ImGui::Text(instruction[i].c_str());
		}


		ImGui::End();
	}



}

void Widget_ListInstruction::Update() {
	UpdateActive();
}


void Widget_ListInstruction::GetAllInstruction() {

	for (const auto& [key, value] : map_InstructionInfo) {
		
		std::vector<std::string> opcodes;
		for (int i = 0; i < value._Opcodes.size(); i++){


			if (i != 0 && value._Opcodes[i-1] == value._Opcodes[i]){
				for (int j = value._Opcodes[i] + 1; j <= value._Opcodes[i + 1]; j++)
					opcodes.push_back(Value2strHex(j) + " ");
				i++;
			}
			else {
				opcodes.push_back(Value2strHex(value._Opcodes[i]) + " ");
			}

		}

		int indexUsedOpcode = 0;

		std::string result = key;

		ToUpperALL(result);

		if (value._Arguments.size() == 2 ){

			if (value._Arguments[0] == value._Arguments[1]){
				result += " ";
				auto info = ENUM_Arguments_to_CommandArguments(value._Arguments[0]);

				for (int i = 0; i < info.available_values.size(); i++) {
					for (int j = 0; j < info.available_values.size(); j++) {
						if (info.available_values[i] == info.available_values[j] && info.available_values[i] == "M")
							continue;
						instruction.emplace_back(opcodes[indexUsedOpcode] + result + info.available_values[i] + ", " + info.available_values[j]);
						indexUsedOpcode++;
					}
				}
			}
			else {
				auto info = ENUM_Arguments_to_CommandArguments(value._Arguments[0]);
				auto info2 = ENUM_Arguments_to_CommandArguments(value._Arguments[1]);

				for (int i = 0; i < info.available_values.size(); i++){
					instruction.emplace_back(opcodes[indexUsedOpcode] + result + " " + info.available_values[i] + ", " + info2.type_argument);
					indexUsedOpcode++;
				}
			}

		}
		else if (value._Arguments.size() == 1)
		{
			auto info = ENUM_Arguments_to_CommandArguments(value._Arguments[0]);

			if (value._Arguments[0] == InstructionArguments::Value16 || value._Arguments[0] == InstructionArguments::Value8){
				instruction.emplace_back(opcodes[indexUsedOpcode] + result + " " + info.type_argument);
				indexUsedOpcode++;

				if (opcodes.size() > 0) {
					for (int i = 1; i < opcodes.size(); i++) {
						instruction.emplace_back(opcodes[indexUsedOpcode] + "*" + result + " " + info.type_argument);
						indexUsedOpcode++;
					}
				}
			}
			else if (value._Arguments[0] == InstructionArguments::ValueSpecial) {
				for (int i = 0; i < 8; i++) {
					instruction.emplace_back(opcodes[indexUsedOpcode] + result + " " + std::to_string(i));
					indexUsedOpcode++;
				}
			}
			else {
				for (int i = 0; i < info.available_values.size(); i++) {
					instruction.emplace_back(opcodes[indexUsedOpcode] + result + " " + info.available_values[i]);
					indexUsedOpcode++;
				}
			}

			

		}
		else {
			instruction.emplace_back(opcodes[indexUsedOpcode] + result);
			indexUsedOpcode++;
			if (opcodes.size() > 0){
				for (int i = 1; i < opcodes.size(); i++) {
					instruction.emplace_back(opcodes[indexUsedOpcode] + "*" + result);
					indexUsedOpcode++;
				}
			}

			
		}
	}

	sort(instruction.begin(), instruction.end());
}



nlohmann::json Widget_ListInstruction::Save() {
	return SaveDefaultParameters();
}
void Widget_ListInstruction::Load(const nlohmann::json& Data) {
	ReadDefaultParameters(Data);
}