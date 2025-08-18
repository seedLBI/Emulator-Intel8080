#include "Widget.Keyboard.h"

Widget_Keyboard::Widget_Keyboard(FPS_Timer* fps_timer, TextEditor* editor) : I8080_Widget(u8"Клавиатура"), IThemeLoadable(u8"Клавиатура") {
	this->fps_timer = fps_timer;
	this->editor = editor;

	
	IThemeLoadable::InitListWord({ u8"Нажат",u8"Не нажат" });

}

Widget_Keyboard::~Widget_Keyboard() {

}


void Widget_Keyboard::LoadColors() {
	for (int i = 0; i < object_colors.colors.size(); i++) {
		if (object_colors.colors[i].nameColor == u8"Нажат")
			color_Active = object_colors.colors[i].color;
		else if (object_colors.colors[i].nameColor == u8"Не нажат")
			color_deActive = object_colors.colors[i].color;
	}
}
std::vector<NamedColor> Widget_Keyboard::GetDefaultLightColors() {
	return {
		{u8"Нажат",		ImColor(142,0,0,255)},
		{u8"Не нажат",  ImColor(255,241,217,255)}
	};
}
std::vector<NamedColor> Widget_Keyboard::GetDefaultDarkColors() {
	return {
		{u8"Нажат", ImVec4(1.f,0.f,0.f,1.f)},
		{u8"Не нажат",  ImVec4(0.f,0.f,0.f,1.f)}
	};
}



void Widget_Keyboard::Draw() {
	if (GetFlagShow() == false)
		return;


	if (ImGui::Begin(GetName_c_str(), GetPtrFlagShow(), ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoNav)) {



		static std::vector<std::vector<float>> anim_background = {
			{0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f},
			{0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f},
			{0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f},
			{0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f},
			{0.f,0.f,0.f,0.f,0.f}
		};

		float TimesLerping = powf(0.01f, fps_timer->GetDeltaTime());


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


				ImVec4 ResultColor = {
					color_Active.x * anim_background[i][j] + color_deActive.x * (1.f - anim_background[i][j]),
					color_Active.y * anim_background[i][j] + color_deActive.y * (1.f - anim_background[i][j]),
					color_Active.z * anim_background[i][j] + color_deActive.z * (1.f - anim_background[i][j]),
				1.f };



				ImGui::PushStyleColor(ImGuiCol_Button, ResultColor);
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ResultColor);
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ResultColor);

				ImVec2 SizeText = ImGui::CalcTextSize(layers_names_array[i][j].c_str());
				if (ImGui::Button(std::string(layers_names_array[i][j]).c_str(), ImVec2((SizeText.x * 1.2f) * layers_sizes_array[i][j], SizeText.y * 1.1))) {
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

void Widget_Keyboard::Update() {
	UpdateActive();
}

nlohmann::json Widget_Keyboard::Save() {
	return SaveDefaultParameters();
}

void Widget_Keyboard::Load(const nlohmann::json& Data) {
	ReadDefaultParameters(Data);
}