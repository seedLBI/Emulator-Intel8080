#include "ThemeManager.h"

ThemeManager::ThemeManager() : ISettingObject(u8"Themes", u8"Цветовая тема") {

}

ThemeManager::~ThemeManager() {

}

void ThemeManager::CalculateCountObjects() {
	countObjects = 0;
	for (int i = 0; i < objects.size(); i++) {
		countObjects += int(objects[i]->GetColors().size()) + 1;
	}
}

void ThemeManager::AddObject(IThemeLoadable* new_object) {
	objects.push_back(new_object);
	CalculateCountObjects();
	SetDarkTheme();
	LoadForced();
}


void ThemeManager::LoadForced() {
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->LoadColors(objects[i]->GetColors());
	}
}
void ThemeManager::LoadChoosedTheme() {

	if (indexChoosed <= 1){
		if (indexChoosed == 0)
			SetDarkTheme();
		else
			SetLightTheme();
		return;
	}

	if (themes.empty()) {
		SetDarkTheme();
		return;
	}


	for (int i = 0; i < themes[indexChoosed - 2].objectColors.size(); i++) {
		for (int j = 0; j < objects.size(); j++) {
			if (objects[j]->GetName() == themes[indexChoosed-2].objectColors[i].nameObject){
				objects[j]->LoadColors(themes[indexChoosed-2].objectColors[i].colors);
				break;
			}
		}
	}

}

nlohmann::json ThemeManager::SaveSetting() {

	nlohmann::json SaveData;

	std::string data;

	for (int i = 0; i < themes.size(); i++) {

		const std::string name_theme = themes[i].nameTheme;

		for (int j = 0; j < themes[i].objectColors.size(); j++){

			const std::string name_object = themes[i].objectColors[j].nameObject;

			for (int k = 0; k < themes[i].objectColors[j].colors.size(); k++){

				const std::string name_color = themes[i].objectColors[j].colors[k].nameColor;
				const std::string value_color = ImColor2Hex(themes[i].objectColors[j].colors[k].color);

				SaveData["themes"][name_theme]["objects"][name_object][name_color] = value_color;
			}
		}
	}

	SaveData[u8"indexChoosed"] = indexChoosed;

	return SaveData;

}
void ThemeManager::LoadSetting(const nlohmann::json& SaveData) {
	themes.clear();



	if (SaveData.contains("themes")) {
		Theme theme;
		ObjectColors object;

		for (auto& [name_theme, data_theme] : SaveData["themes"].items()) {
			theme.objectColors.clear();

			theme.nameTheme = name_theme;

			for (auto& [name_object, data_object] : data_theme["objects"].items()) {
				object.colors.clear();

				object.nameObject = name_object;

				for (auto& [name_color, value_color] : data_object.items()) {
					object.colors.push_back({ name_color,Hex2ImColor(value_color.get<std::string>()) });
				}

				theme.objectColors.push_back(object);
			}
			
			themes.push_back(theme);
		}
	}

	if (SaveData.contains("indexChoosed"))
		indexChoosed = SaveData["indexChoosed"].get<int>();
	else
		indexChoosed = 0;

	LoadChoosedTheme();

}


std::string ThemeManager::ImColor2Hex(const ImColor& color) {
	std::string red = Value2strHex_without0x(static_cast<uint8_t>(color.Value.x * 255.0));
	std::string green = Value2strHex_without0x(static_cast<uint8_t>(color.Value.y * 255.0));
	std::string blue = Value2strHex_without0x(static_cast<uint8_t>(color.Value.z * 255.0));
	std::string alpha = Value2strHex_without0x(static_cast<uint8_t>(color.Value.w * 255.0));

	return red + green + blue + alpha;
}

ImColor ThemeManager::Hex2ImColor(const std::string& hex) {
	ImColor result;

	std::string all = hex;

	std::string red = "0x" + hex.substr(0, 2);
	std::string green = "0x" + hex.substr(2, 2);
	std::string blue = "0x" + hex.substr(4, 2);
	std::string alpha = "0x" + hex.substr(6, 2);

	result.Value.x = (float)StrHex2int(red) / 255.f;
	result.Value.y = (float)StrHex2int(green) / 255.f;
	result.Value.z = (float)StrHex2int(blue) / 255.f;
	result.Value.w = (float)StrHex2int(alpha) / 255.f;

	return result;
}

void ThemeManager::SetDarkTheme() {
	indexChoosed = 0;
	for (int i = 0; i < objects.size(); i++){
		objects[i]->SetDefaultDarkColors();
	}
}

void ThemeManager::SetLightTheme() {
	indexChoosed = 1;
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->SetDefaultLightColors();
	}
}

void ThemeManager::CreateThemeFromCurrentColors(const std::string& name) {
	Theme theme;
	theme.nameTheme = name;
	for (size_t i = 0; i < objects.size(); i++)
		theme.objectColors.push_back(ObjectColors{ objects[i]->GetName(), objects[i]->GetColors() });

	themes.push_back(theme);
}

void ThemeManager::DrawPopupCreation() {
	if (!PopupCreation_isOpen)
		return;

	ImGui::OpenPopup(u8"Создание названия для новой цветовой темы");

	const ImGuiWindowFlags flagsWindow = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;
	ImVec2 center = ImGui::GetMainViewport()->GetCenter();

	ImVec2 size = ImGui::GetMainViewport()->WorkSize;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, ImVec2(0.5, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));


	ImGui::SetNextWindowSize(ImVec2(ImGui::CalcTextSize(u8"Создание названия для новой цветовой темы              ").x, ImGui::GetFontSize() * 8.5f));


	static char buf_name[120];
	static bool FirstLoad = false;
	if (FirstLoad == false) {
		FirstLoad = true;
		for (int i = 0; i < 120; i++) {
			buf_name[i] = 0;
		}
	}

	if (ImGui::BeginPopupModal(u8"Создание названия для новой цветовой темы", &PopupCreation_isOpen, flagsWindow)) {
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + ImGui::GetFontSize() * 0.5f);
		center.x -= ImGui::GetCurrentWindow()->Size.x / 2;
		center.y -= ImGui::GetCurrentWindow()->Size.y / 2;
		ImGui::GetCurrentWindow()->Pos = center;

		ImGui::Dummy(ImVec2(0.f, ImGui::GetFontSize() * 0.25f));

		TextCenteredOnLine(u8"Название", 0, 0);

		ImGui::Dummy(ImVec2(0.f, ImGui::GetFontSize() * 0.25f));

		float input_width = ImGui::CalcItemWidth();
		ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x - input_width) / 2.f);
		ImGui::InputText("1102", buf_name, 120, ImGuiInputTextFlags_NoLabel);
		
		ImGui::Dummy(ImVec2(0.f, ImGui::GetFontSize() * 0.25f));

		bool pressed = ButtonCenteredOnLine(u8"Принять", 0.5f);

		if (ImGui::IsKeyPressed(ImGuiKey_Enter))
			pressed = true;

		if (pressed) {

			if (!std::string(buf_name).empty()) {

				bool NoCollision = true;
				for (int i = 0; i < themes.size(); i++) {
					if (std::string(buf_name) == themes[i].nameTheme){
						NoCollision = false;
						break;
					}
				}

				if (NoCollision) {
					PopupCreation_isOpen = false;
					CreateThemeFromCurrentColors(buf_name);
					FirstLoad = true;
				}
				else {
					pressed = false;
				}

			}
			else
				pressed = false;
		}


		ImGui::EndPopup();
	}

	ImGui::PopStyleVar();
	ImGui::PopStyleVar();

}


void ThemeManager::DrawSetting() {

	std::string preview_name;

	if (indexChoosed == 0)
		preview_name = u8"Тёмная";
	else if (indexChoosed == 1)
		preview_name = u8"Светлая";
	else
		preview_name = themes[indexChoosed - 2].nameTheme;


	if (ImGui::BeginCombo(u8"Выбор темы", preview_name.c_str(), ImGuiComboFlags_WidthFitPreview)) {

		if (ImGui::Selectable(u8"Тёмная", preview_name == u8"Тёмная")) {
			SetDarkTheme();
		}
		if (ImGui::Selectable(u8"Светлая", preview_name == u8"Светлая")) {
			SetLightTheme();
		}

		ImGuiWindow* imgui_window = ImGui::GetCurrentWindow();
		ImDrawList* draw_list = ImGui::GetForegroundDrawList();


		for (int i = 0; i < themes.size(); i++) {


			if (ButtonDelete(imgui_window, draw_list, ("userThemes" + std::to_string(i)).c_str(), ImColor(ImVec4(1.f, 1.f, 1.f, 1.f)))) {
				themes.erase(themes.begin() + i);
				i--;

				if (themes.size() == 0) {
					indexChoosed = 0;
				}

				continue;
			}



			if (ImGui::Selectable(themes[i].nameTheme.c_str(), preview_name == themes[i].nameTheme)) {
				indexChoosed = i + 2;
				LoadChoosedTheme();
			}
		}

		ImGui::EndCombo();
	}

	ImGui::SameLine();

	if (ImGui::Button(u8"Создать из текущих цветов")) {
		PopupCreation_isOpen = true;
	}
	DrawPopupCreation();



	if (ImGui::BeginTable("Table_of_colors", 1, ImGuiTableFlags_ScrollY, ImVec2(0, ImGui::GetContentRegionAvail().y - 10.f))) {


		static int row = 0;
		float scroll_y = ImGui::GetScrollY();
		static float pos_separator_y = ImGui::GetCursorPosY() - 4.f;
		static float last_pos_separator_y = ImGui::GetCursorPosY() - 4.f;

		static bool first_run = true;

		if (first_run)
			first_run = false;
		else
			ImGui::TableSetupScrollFreeze(1, 1);


		for (int i = 0; i < objects.size(); i++) {

			ImGui::TableNextRow();
			ImGui::TableNextColumn();

			last_pos_separator_y = pos_separator_y;
			pos_separator_y = ImGui::GetCursorPosY() - 4.f;

			if (last_pos_separator_y < scroll_y && scroll_y < pos_separator_y) {
				if (i == 0)
					row = 0;
				else
					row = i - 1;
			}

			if (i == 0) {
				ImGui::SeparatorText(objects[row]->GetName().c_str());
			}
			else
				ImGui::SeparatorText(objects[i]->GetName().c_str());

			auto colors_data = objects[i]->GetColorsPTR();
			std::string NameObject = "##color" + objects[i]->GetName();

			for (int j = 0; j < colors_data->size(); j++) {

				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);

				if (ImGui::ColorEdit4(std::string(NameObject + std::to_string(j)).c_str(), (float*)&colors_data->at(j).color, ImGuiColorEditFlags_AlphaPreviewHalf | ImGuiColorEditFlags_None)) {
					LoadForced();
				}
				ImGui::SameLine();
				ImGui::Text(colors_data->at(j).nameColor.c_str());

			}

		}

		ImGui::EndTable();
	}

}