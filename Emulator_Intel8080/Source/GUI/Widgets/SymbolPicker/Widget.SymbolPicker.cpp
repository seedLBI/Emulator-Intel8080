#include "Widget.SymbolPicker.h"



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
					editor->InsertText("0x" + to_hex_string((uint8_t)(16 * h + j)));
				}
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNone)) {
					ImGui::BeginTooltip();
					ImGui::Text(("0x" + to_hex_string((uint8_t)(16 * h + j))).c_str());
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

nlohmann::json Widget_SymbolPicker::Save() {
	return SaveDefaultParameters();
}
void Widget_SymbolPicker::Load(const nlohmann::json& Data) {
	ReadDefaultParameters(Data);
}