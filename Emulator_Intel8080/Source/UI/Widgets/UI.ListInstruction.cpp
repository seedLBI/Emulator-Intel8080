#include "UI.ListInstruction.h"

Widget_ListInstruction::Widget_ListInstruction() : I8080_Widget(u8"Список инструкций") {
	GetAllInstruction();
}

Widget_ListInstruction::~Widget_ListInstruction() {

}

void Widget_ListInstruction::Draw() {

	if (GetFlagShow() == false)
		return;


	ImGuiStyle& style = ImGui::GetStyle();
	int prev_cellPadding = style.CellPadding.y;
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
						instruction.emplace_back(result + info.available_values[i] + ", " + info.available_values[j]);
					}
				}
			}
			else {
				auto info = ENUM_Arguments_to_CommandArguments(value._Arguments[0]);
				auto info2 = ENUM_Arguments_to_CommandArguments(value._Arguments[1]);

				for (int i = 0; i < info.available_values.size(); i++){
					instruction.emplace_back(result + " " + info.available_values[i] + ", " + info2.type_argument);
				}
			}

		}
		else if (value._Arguments.size() == 1)
		{
			auto info = ENUM_Arguments_to_CommandArguments(value._Arguments[0]);

			if (value._Arguments[0] == ENUM_Arguments::Value16 || value._Arguments[0] == ENUM_Arguments::Value8 || value._Arguments[0] == ENUM_Arguments::ValueSpecial){
				instruction.emplace_back(result + " " + info.type_argument);
			}
			else {
				for (int i = 0; i < info.available_values.size(); i++) {
					instruction.emplace_back(result + " " + info.available_values[i]);
				}
			}

			

		}
		else {
			instruction.emplace_back(result);
		}
	}

	sort(instruction.begin(), instruction.end());
}



std::string Widget_ListInstruction::Save() {
	std::string output = "";
	output += MakeBegin(2);
	output += MakeSaveItem(std::string("Flag_Show"), std::to_string(GetFlagShow()));
	output += MakeSaveItem(std::string("Flag_Active"), std::to_string(WindowIsVisiable()));
	return output;
}
void Widget_ListInstruction::Load(const std::string& Data) {
	PrintDebugInfoAboutData(Data);

	std::vector<std::string> Lines = split(Data, "\n");
	for (int i = 0; i < Lines.size(); i++) {
		std::vector<std::string> info = SplitLine(Lines[i]);

		std::string name_arg = info[0];
		std::string value_arg = info[1];

		if (name_arg == "Flag_Show")
			SetFlagShow(stoi(value_arg));
		else if (name_arg == "Flag_Active") {
			if (stoi(value_arg) == 1)
				SetActive();
		}
		else
			std::cout << "Unknown name argument for widget: " << name_arg << std::endl;
	}
}