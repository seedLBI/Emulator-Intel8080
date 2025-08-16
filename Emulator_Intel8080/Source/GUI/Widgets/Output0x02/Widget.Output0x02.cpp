#include "Widget.Output0x02.h"

void Widget_Output0x02::Draw() {
	if (GetFlagShow() == false)
		return;

	if (ImGui::Begin(GetName_c_str(), GetPtrFlagShow(), ImGuiWindowFlags_NoScrollbar)) {
		ImGui::Text(u8"Порт: 0х02");
		ImGui::SameLine();

		if (ImGui::RadioButton("Hex", Hex_enable)) {
			Hex_enable = true;
			Dec_enable = false;
			Bin_enable = false;
			Char_enable = false;
		}
		ImGui::SameLine();
		if (ImGui::RadioButton("Dec", Dec_enable)) {
			Hex_enable = false;
			Dec_enable = true;
			Bin_enable = false;
			Char_enable = false;
		}
		ImGui::SameLine();
		if (ImGui::RadioButton("Bin", Bin_enable)) {
			Hex_enable = false;
			Dec_enable = false;
			Bin_enable = true;
			Char_enable = false;
		}
		ImGui::SameLine();
		if (ImGui::RadioButton("Char", Char_enable)) {
			Hex_enable = false;
			Dec_enable = false;
			Bin_enable = false;
			Char_enable = true;
		}

		// bool Char_enable = false;
		if (!Char_enable)
			ImGui::Checkbox(u8"Вывод столбиком", &mode_output);

		ImGui::Separator();
		std::string text;

		Port_ConsoleOutput* p = dynamic_cast<Port_ConsoleOutput*>(processor->Get_External_Peripherals()[0x02]);
		auto Output = p->GetConsoleData();

		for (int i = 0; i < Output.size(); i++) {

			if (Char_enable) {
				if (Output[i] == 0x0a)
					text += "\n";
				else if (Output[i] == 0x09)
					text += "\t";
				else
					text += GetSymbol_1251_OnNumber(Output[i]).c_str();
			} else {
				if (Dec_enable)
					text += std::to_string(Output[i]);
				else if (Hex_enable)
					text += to_hex_string(Output[i]);
				else if (Bin_enable)
					text += to_bin_string(Output[i]);

				if (mode_output)
					text += "\n";
				else
					text += " ";
			}
		}

		auto prev_pos = ImGui::GetCursorScreenPos();

		RenderTextWrapped(text.c_str(), false);

		auto next_pos = ImGui::GetCursorScreenPos();

		auto Max_Width = prev_pos.x + ImGui::GetWindowWidth();


		if (ImGui::IsMouseHoveringRect(ImVec2(prev_pos.x, prev_pos.y), ImVec2(Max_Width, next_pos.y)) && text.empty() == false) {

			if (ImGui::BeginTooltip()) {
				ImGui::Text(u8"Нажми ЛКМ, чтобы скопировать\nтекст в буфер обмена.");
				ImGui::EndTooltip();
			}

			if (ImGui::IsMouseClicked(ImGuiMouseButton_Left,false)) {
				ImGui::SetClipboardText(text.c_str());

				static const ImVec4 color_GREEN{ 0.2f,0.45f,0.2f,1.0f };
				static const ImVec4 color_WHITE{ 1.f,1.f,1.f,1.f };

				std::string success = u8"Скопировано в буфер обмена.";

				notificationManager->AddNottification(Notification(color_GREEN, 1.f, std::vector<N_Element*>{
					new N_Message(color_WHITE, success),
				},
					nullptr));

			}

		}

		ImGui::End();
	}
}
void Widget_Output0x02::Update() {
	UpdateActive();
}

Widget_Output0x02::Widget_Output0x02(I8080* processor, NotificationManager* notificationManager) : I8080_Widget(u8"Окно вывода") {
	this->processor = processor;
	this->notificationManager = notificationManager;

}

Widget_Output0x02::~Widget_Output0x02() {

}

nlohmann::json Widget_Output0x02::Save() {

	nlohmann::json result = SaveDefaultParameters();

	result["mode_output"] = mode_output;
	result["Hex_enable"] = Hex_enable;
	result["Dec_enable"] = Dec_enable;
	result["Bin_enable"] = Bin_enable;
	result["Char_enable"] = Char_enable;

	return result;

}

void Widget_Output0x02::Load(const nlohmann::json& Data) {

	ReadDefaultParameters(Data);

	if (Data.contains("mode_output"))
		mode_output = Data["mode_output"].get<bool>();

	if (Data.contains("Hex_enable"))
		Hex_enable = Data["Hex_enable"].get<bool>();

	if (Data.contains("Dec_enable"))
		Dec_enable = Data["Dec_enable"].get<bool>();

	if (Data.contains("Bin_enable"))
		Bin_enable = Data["Bin_enable"].get<bool>();

	if (Data.contains("Char_enable"))
		Char_enable = Data["Char_enable"].get<bool>();

}