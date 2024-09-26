#include "I8080.UI.Output0x02.h"

void Widget_Output0x02::Draw() {
	if (GetFlagShow() == false)
		return;

	if (ImGui::Begin(GetName_c_str(), GetPtrFlagShow(), ImGuiWindowFlags_NoScrollbar)) {
		ImGui::Text(u8"Порт: 0х02");
		ImGui::SameLine();
		/*
		HelpMarker(
			u8"Способ обращения к порту: \n"
			u8"- Написать OUT 0x02 в коде.\n"
			u8"Протокол использования: \n"
			u8"1. Перед выводом убедиться что нужное для вывода значения лежит в регистре А\n"
			u8"2. После выполнения команды он отобразиться в консоле"
		);
		*/
		ImGui::SameLine();
		
		ImGui::Checkbox(u8"Вывод столбиком", &mode_output);
		ImGui::Separator();
		std::string text;
		for (int i = 0; i < processor->GetOutputConsole().size(); i++) {
			text += to_string(processor->GetOutputConsole()[i]);
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
	output += MakeBegin(2);
	output += MakeSaveItem(string("Flag_Show"), std::to_string(GetFlagShow()));
	output += MakeSaveItem(string("mode_output"), std::to_string(mode_output));
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
		else
			std::cout << "Unknown name argument for widget: " << name_arg << std::endl;
	}
}