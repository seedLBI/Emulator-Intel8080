#include "I8080.UI.Timer.h"

Widget_Timer::Widget_Timer(I8080* processor) :I8080_Widget(u8"Таймер") {
	this->processor = processor;
}
Widget_Timer::~Widget_Timer() {

}
void Widget_Timer::Draw() {
	if (GetFlagShow() == false)
		return;

	if (ImGui::Begin(GetName_c_str(), GetPtrFlagShow(), ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Text(u8"Порт: 0х16");
		ImGui::Separator();
		ImGui::Text(u8"Значение: ");
		ImGui::SameLine();

		I8080_Timer* p = dynamic_cast<I8080_Timer*>(processor->Get_External_Peripherals()[0x16]);
		ImGui::Text(to_string(p->GetOutput()).c_str());

		ImGui::End();
	}
}
void Widget_Timer::Update() {

}


std::string Widget_Timer::Save() {
	std::string output = "";
	output += MakeBegin(1);
	output += MakeSaveItem(string("Flag_Show"), std::to_string(GetFlagShow()));
	return output;
}

void Widget_Timer::Load(const std::string& Data) {
	PrintDebugInfoAboutData(Data);

	std::vector<std::string> Lines = split(Data, "\n");
	for (int i = 0; i < Lines.size(); i++) {
		std::vector<std::string> info = SplitLine(Lines[i]);

		std::string name_arg = info[0];
		std::string value_arg = info[1];

		if (name_arg == "Flag_Show")
			SetFlagShow(stoi(value_arg));
		else
			std::cout << "Unknown name argument for widget: " << name_arg << std::endl;
	}
}