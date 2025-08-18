#include "Widget.Timer.h"

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

		Port_Timer* p = dynamic_cast<Port_Timer*>(processor->Get_External_Peripherals()[0x16]);
		ImGui::Text(std::to_string(p->GetOutput()).c_str());

		ImGui::End();
	}
}
void Widget_Timer::Update() {
	UpdateActive();
}


nlohmann::json Widget_Timer::Save() {
	return SaveDefaultParameters();
}

void Widget_Timer::Load(const nlohmann::json& Data) {
	ReadDefaultParameters(Data);
}