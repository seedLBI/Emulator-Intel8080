#include "I8080.UI.Input0x08.h"


Widget_Input0x08::Widget_Input0x08(I8080* processor) : I8080_Widget(u8"ќкно ввода") {
	this->processor = processor;
}
Widget_Input0x08::~Widget_Input0x08() {

}
void Widget_Input0x08::Draw() {



	ImVec4 ColorBG = ImGui::GetStyleColorVec4(ImGuiCol_WindowBg);
	float t = 0.f;

	float Lerp = pow(0.01, OpenglWindow::GetDeltaTime());

	if (processor->IsWaitingPortInput()) {


		float t = abs( sin(glfwGetTime() * 8.f) * 0.2f + 0.2f);
		ColorBG.x = 0.f;
		ColorBG.y = t;
		ColorBG.z = 0.f;

		if (GetFlagShow() == false)
			SetFlagShow(true);

		ImGui::SetWindowFocus(u8"ќкно ввода");
	}

	if (GetFlagShow() == false)
		return;


	ImVec4 NewColorBG = ImVec4((ColorBG.x) , (ColorBG.y), ColorBG.z, 1.0f);

 	ImGui::PushStyleColor(ImGuiCol_WindowBg, NewColorBG);

	if (ImGui::Begin(GetName_c_str(), GetPtrFlagShow(), ImGuiWindowFlags_AlwaysAutoResize)) {


		if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort)) {
			ImGui::BeginTooltip();
			ImGui::Text(info);
			ImGui::EndTooltip();
		}

		ImGui::Text(u8"¬вод значени€ в порт 0x08");
		ImGui::Separator();
		static char buf2[4] = "";
		if (ImGui::InputText(u8"«начение от 0 до 255", buf2, 4, ImGuiInputTextFlags_CharsDecimal)) {

		}
		

		ImGui::SameLine();
		if (ImGui::IsKeyPressed(ImGuiKey_Enter) && processor->IsWaitingPortInput())
		{
			string v(buf2);
			unsigned int value = stoi(v);
			if (value < 256) {

				processor->InputAnswer2Port(value);
				for (int i = 0; i < 4; i++)
				{
					buf2[i] = 0;
				}
			}
		}
		if (ImGui::Button(u8"¬вод") && processor->IsWaitingPortInput()) {
			string v(buf2);
			if (v.size() != 0) {
				unsigned int value = stoi(v);
				if (value < 256) {
					processor->InputAnswer2Port(value);

				}
				for (int i = 0; i < 4; i++)
				{
					buf2[i] = 0;
				}
			}


		}



		ImGui::End();
	}

	ImGui::PopStyleColor();

}
void Widget_Input0x08::Update() {

}

std::string Widget_Input0x08::Save() {
	std::string output = "";
	output += MakeBegin(1);
	output += MakeSaveItem(string("Flag_Show"), std::to_string(GetFlagShow()));
	return output;
}

void Widget_Input0x08::Load(const std::string& Data) {
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
