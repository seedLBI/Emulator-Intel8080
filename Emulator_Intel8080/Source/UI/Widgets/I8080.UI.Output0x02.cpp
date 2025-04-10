#include "I8080.UI.Output0x02.h"

void Widget_Output0x02::Draw() {
	if (GetFlagShow() == false)
		return;

	if (ImGui::Begin(GetName_c_str(), GetPtrFlagShow(), ImGuiWindowFlags_NoScrollbar)) {
		ImGui::Text(u8"����: 0�02");
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
			ImGui::Checkbox(u8"����� ���������", &mode_output);

		ImGui::Separator();
		std::string text;

		I8080_ConsoleOutput* p = dynamic_cast<I8080_ConsoleOutput*>(processor->Get_External_Peripherals()[0x02]);
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
					text += to_string(Output[i]);
				else if (Hex_enable)
					text += int2stringHex(Output[i]);
				else if (Bin_enable)
					text += int2stringBin(Output[i]);

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
				ImGui::Text(u8"����� ���, ����� �����������\n����� � ����� ������.");
				ImGui::EndTooltip();
			}

			if (ImGui::IsMouseClicked(ImGuiMouseButton_Left,false)) {
				ImGui::SetClipboardText(text.c_str());

				static const ImVec4 color_GREEN{ 0.2f,0.45f,0.2f,1.0f };
				static const ImVec4 color_WHITE{ 1.f,1.f,1.f,1.f };

				string success = u8"����������� � ����� ������.";

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

Widget_Output0x02::Widget_Output0x02(I8080* processor, NotificationManager* notificationManager) : I8080_Widget(u8"���� ������") {
	this->processor = processor;
	this->notificationManager = notificationManager;

}

Widget_Output0x02::~Widget_Output0x02() {

}

std::string Widget_Output0x02::Save() {
	std::string output = "";
	output += MakeBegin(7);
	output += MakeSaveItem(std::string("Flag_Show"), std::to_string(GetFlagShow()));
	output += MakeSaveItem(std::string("Flag_Active"), std::to_string(WindowIsVisiable()));
	output += MakeSaveItem(std::string("mode_output"), std::to_string(mode_output));
	output += MakeSaveItem(std::string("Hex_enable"), std::to_string(Hex_enable));
	output += MakeSaveItem(std::string("Dec_enable"), std::to_string(Dec_enable));
	output += MakeSaveItem(std::string("Bin_enable"), std::to_string(Bin_enable));
	output += MakeSaveItem(std::string("Char_enable"), std::to_string(Char_enable));
	return output;
}

void Widget_Output0x02::Load(const std::string& Data) {
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
		else if (name_arg == "mode_output")
			mode_output = stoi(value_arg);
		else if (name_arg == "Hex_enable")
			Hex_enable = stoi(value_arg);
		else if (name_arg == "Dec_enable")
			Dec_enable = stoi(value_arg);
		else if (name_arg == "Bin_enable")
			Bin_enable = stoi(value_arg);
		else if (name_arg == "Char_enable")
			Char_enable = stoi(value_arg);
		else
			std::cout << "Unknown name argument for widget: " << name_arg << std::endl;
	}
}