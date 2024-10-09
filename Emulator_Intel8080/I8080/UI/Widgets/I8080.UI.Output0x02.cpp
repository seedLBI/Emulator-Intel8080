#include "I8080.UI.Output0x02.h"

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
		}
		ImGui::SameLine();
		if (ImGui::RadioButton("Dec", Dec_enable)) {
			Hex_enable = false;
			Dec_enable = true;
			Bin_enable = false;
		}
		ImGui::SameLine();
		if (ImGui::RadioButton("Bin", Bin_enable)) {
			Hex_enable = false;
			Dec_enable = false;
			Bin_enable = true;
		}
		
		ImGui::Checkbox(u8"Вывод столбиком", &mode_output);
		ImGui::Separator();
		std::string text;
		for (int i = 0; i < processor->GetOutputConsole().size(); i++) {

			if (Dec_enable)
				text += to_string(processor->GetOutputConsole()[i]);
			else if (Hex_enable)
				text += int2stringHex(processor->GetOutputConsole()[i]);
			else if(Bin_enable)
				text += int2stringBin(processor->GetOutputConsole()[i]);

			if (mode_output)
				text += "\n";
			else
				text += " ";
		}
		ImGui::TextWrapped(text.c_str());
		ImGui::End();
	}
}
void Widget_Output0x02::Update() {

}

Widget_Output0x02::Widget_Output0x02(I8080* processor) : I8080_Widget(u8"Окно вывода")
{
	this->processor = processor;
}

Widget_Output0x02::~Widget_Output0x02()
{

}

std::string Widget_Output0x02::Save() {
	std::string output = "";
	output += MakeBegin(5);
	output += MakeSaveItem(string("Flag_Show"), std::to_string(GetFlagShow()));
	output += MakeSaveItem(string("mode_output"), std::to_string(mode_output));
	output += MakeSaveItem(string("Hex_enable"), std::to_string(Hex_enable));
	output += MakeSaveItem(string("Dec_enable"), std::to_string(Dec_enable));
	output += MakeSaveItem(string("Bin_enable"), std::to_string(Bin_enable));
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
		else if (name_arg == "mode_output")
			mode_output = stoi(value_arg);
		else if (name_arg == "Hex_enable")
			Hex_enable = stoi(value_arg);
		else if (name_arg == "Dec_enable")
			Dec_enable = stoi(value_arg);
		else if (name_arg == "Bin_enable")
			Bin_enable = stoi(value_arg);
		else
			std::cout << "Unknown name argument for widget: " << name_arg << std::endl;
	}
}