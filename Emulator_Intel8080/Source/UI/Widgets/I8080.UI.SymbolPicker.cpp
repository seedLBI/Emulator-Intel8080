#include "I8080.UI.SymbolPicker.h"



Widget_SymbolPicker::Widget_SymbolPicker(TextEditor* editor) :I8080_Widget(u8"Все символы") {
	this->editor = editor;
}

Widget_SymbolPicker::~Widget_SymbolPicker() {

}

void Widget_SymbolPicker::Draw() {
	if (GetFlagShow() == false)
		return;


	ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_FirstUseEver);
	if (ImGui::Begin(GetName_c_str(), GetPtrFlagShow(), ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize)) {

		ImGuiStyle& style = ImGui::GetStyle();
		float height = style.ItemSpacing.y;

		style.ItemSpacing.y = 0.f;
		ImVec2 SizeWind = { abs(ImGui::GetWindowSize().x) / 16.f, abs(ImGui::GetWindowSize().y - style.FramePadding.y - style.WindowPadding.y - ImGui::GetFontSize()) / 16.f };
		float minSize = (std::min)(SizeWind.x, SizeWind.y);
		for (unsigned int h = 0; h < 16; h++) {
			for (unsigned int j = 0; j < 16; j++) {
				char symbol(16 * h + j);

				if (j != 0) {
					ImGui::SameLine(0.f, 0.f);
				}

				if (ImGui::ButtonEx(GetSymbol_1251_OnNumber(symbol).c_str(), ImVec2(minSize, minSize), ImGuiButtonFlags_NoHoveredOnFocus)) {
					editor->InsertText(int2string_0x_Hex(16 * h + j));
				}
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNone)) {
					ImGui::BeginTooltip();
					ImGui::Text(int2string_0x_Hex(16 * h + j).c_str());
					ImGui::Text(std::to_string(16 * h + j).c_str());
					ImGui::EndTooltip();
				}
			}

		}


		style.ItemSpacing.y = height;
		ImGui::End();
	}
}

void Widget_SymbolPicker::Update() {

	UpdateActive();
}

std::string Widget_SymbolPicker::Save() {
	std::string output = "";
	output += MakeBegin(2);
	output += MakeSaveItem(std::string("Flag_Show"), std::to_string(GetFlagShow()));
	output += MakeSaveItem(std::string("Flag_Active"), std::to_string(WindowIsVisiable()));
	return output;
}
void Widget_SymbolPicker::Load(const std::string& Data) {
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