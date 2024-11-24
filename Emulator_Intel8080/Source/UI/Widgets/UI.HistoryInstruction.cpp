#include "UI.HistoryInstruction.h"

Widget_HistoryInstruction::Widget_HistoryInstruction(I8080* processor, EmulationThread* emulationThread, Caretaker_Momento* processor_CaretakerMomento) : I8080_Widget(u8"История выполнения") {
	this->processor = processor;
	this->emulationThread = emulationThread;
	this->processor_CaretakerMomento = processor_CaretakerMomento;
}


Widget_HistoryInstruction::~Widget_HistoryInstruction() {

}

void Widget_HistoryInstruction::Draw() {

	if (GetFlagShow() == false)
		return;

	if (ImGui::Begin(GetName_c_str(), GetPtrFlagShow(),  ImGuiWindowFlags_AlwaysAutoResize)) {

		if (emulationThread->GetControlMode() != ControlMode::Continous){

			auto data = processor_CaretakerMomento->GetHistory();

			for (int i = 0; i < data.size(); i++) {
				if (ImGui::Selectable((std::to_string(i) + ". " + data[i]).c_str(), false)) {

				}
			}
		}
		
		ImGui::End();
	}


}
void Widget_HistoryInstruction::Update() {
	UpdateActive();
}

std::string Widget_HistoryInstruction::Save() {
	std::string output = "";
	output += MakeBegin(2);
	output += MakeSaveItem(std::string("Flag_Show"), std::to_string(GetFlagShow()));
	output += MakeSaveItem(std::string("Flag_Active"), std::to_string(WindowIsVisiable()));
	return output;
}
void Widget_HistoryInstruction::Load(const std::string& Data) {
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