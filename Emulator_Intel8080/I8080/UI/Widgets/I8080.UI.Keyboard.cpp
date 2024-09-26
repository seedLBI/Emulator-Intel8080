#include "I8080.UI.Keyboard.h"

Widget_Keyboard::Widget_Keyboard(TextEditor* editor) : I8080_Widget(u8"Клавиатура") {
	this->editor = editor;
}

Widget_Keyboard::~Widget_Keyboard() {

}

void Widget_Keyboard::Update() {

}


void Widget_Keyboard::Draw() {
	if (GetFlagShow() == false)
		return;

	if (ImGui::Begin(GetName_c_str(), GetPtrFlagShow(), ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoNav)) {



		static vector<vector<float>> anim_background = {
			{0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f},
			{0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f},
			{0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f},
			{0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f},
			{0.f,0.f,0.f,0.f,0.f}
		};

		float TimesLerping = powf(0.01f, OpenglWindow::GetDeltaTime());


		for (int i = 0; i < layers_names_array.size(); i++)
		{
			for (int j = 0; j < layers_names_array[i].size(); j++)
			{
				anim_background[i][j] = anim_background[i][j] * TimesLerping;



				if (anim_background[i][j] < 0.f)
					anim_background[i][j] = 0.f;

				if (ImGui::IsKeyDown(layers_keys_array[i][j]))
					anim_background[i][j] = 1.f;

				if (j != 0)
					ImGui::SameLine();


				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(anim_background[i][j], 0., 0., 1));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(anim_background[i][j], 0., 0., 1));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(anim_background[i][j], 0., 0., 1));

				ImVec2 SizeText = ImGui::CalcTextSize(layers_names_array[i][j].c_str());
				if (ImGui::Button(string(layers_names_array[i][j]).c_str(), ImVec2((SizeText.x * 1.2f) * layers_sizes_array[i][j], SizeText.y * 1.1))) {
					editor->InsertText(layers_values_array[i][j]);
				}

				if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNone)) {
					ImGui::BeginTooltip();
					ImGui::Text(layers_values_array[i][j].c_str());
					ImGui::EndTooltip();
				}

				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
			}
		}
		ImGui::End();
	}
}

std::string Widget_Keyboard::Save() {
	std::string output = "";
	output += MakeBegin(1);
	output += MakeSaveItem(string("Flag_Show"), std::to_string(GetFlagShow()));
	return output;
}

void Widget_Keyboard::Load(const std::string& Data) {
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