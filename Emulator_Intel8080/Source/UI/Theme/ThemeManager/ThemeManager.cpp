#include "ThemeManager.h"

ThemeManager::ThemeManager() : ISettingObject(u8"Themes", u8"Цветовая тема") {

}

ThemeManager::~ThemeManager() {

}
void ThemeManager::AddObject(IThemeLoadable* new_object) {
	objects.push_back(new_object);
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


	for (int i = 0; i < themes[indexChoosed].objectColors.size(); i++) {
		for (int j = 0; j < objects.size(); j++) {
			if (objects[j]->GetName() == themes[indexChoosed].objectColors[i].nameObject){
				objects[j]->LoadColors(themes[indexChoosed].objectColors[i].colors);
				break;
			}
		}
	}

}


std::string ThemeManager::SaveSetting() {

	std::string data;


	Theme theme;
	theme.nameTheme = "Test";

	for (size_t i = 0; i < objects.size(); i++)
		theme.objectColors.push_back(ObjectColors{ objects[i]->GetName(), objects[i]->GetDefaultDarkColors() });

	themes.push_back(theme);


	for (int i = 0; i < themes.size(); i++) {
		data += save_MakeItem(u8"NameTheme", themes[i].nameTheme);
		for (int j = 0; j < themes[i].objectColors.size(); j++){
			data += save_MakeItem(u8"NameObject", themes[i].objectColors[j].nameObject);
			for (int k = 0; k < themes[i].objectColors[j].colors.size(); k++){
				data += save_MakeItem(themes[i].objectColors[j].colors[k].nameColor, ImColor2Hex(themes[i].objectColors[j].colors[k].color));
			}
		}
	}

	data += save_MakeItem(u8"IndexChoosed", std::to_string(indexChoosed));

	std::string begin_info = save_MakeBegin(GetCountLines(data));

	return begin_info + data;

}
void ThemeManager::LoadSetting(const std::string& Data) {
	themes.clear();

	auto data = load_TokenizeData(Data);

	Theme theme;
	ObjectColors object;


	bool WasNameObject = false;
	bool WasNameTheme = false;

	for (int i = 0; i < data.size(); i++){

		if (data[i].NameVar == u8"NameTheme"){
			if (theme.objectColors.empty() == false) {
				theme.objectColors.push_back(object);
				themes.push_back(theme);
			}
			theme.objectColors.clear();
			theme.nameTheme = data[i].ValueVar;
		}
		else if (data[i].NameVar == u8"NameObject"){
			if (object.colors.empty() == false){
				theme.objectColors.push_back(object);
				object.colors.clear();
			}
			object.nameObject = data[i].ValueVar;
		}
		else if (data[i].NameVar == u8"IndexChoosed")
			indexChoosed = std::stoi(data[i].ValueVar);
		else{
			object.colors.push_back({ data[i].NameVar, Hex2ImColor(data[i].ValueVar) });
		}

	}

	LoadChoosedTheme();

}



std::string ThemeManager::ImColor2Hex(const ImColor& color) {
	std::string red = Value2strHex_without0x(static_cast<uint8_t>(color.Value.x * 255.));
	std::string green = Value2strHex_without0x(static_cast<uint8_t>(color.Value.y * 255.));
	std::string blue = Value2strHex_without0x(static_cast<uint8_t>(color.Value.z * 255.));
	std::string alpha = Value2strHex_without0x(static_cast<uint8_t>(color.Value.w * 255.));

	return red + green + blue + alpha;
}

ImColor ThemeManager::Hex2ImColor(const std::string& hex) {
	ImColor result;

	result.Value.x = StrHex2int("0x" + hex.substr(1, 2));
	result.Value.y = StrHex2int("0x" + hex.substr(3, 2));
	result.Value.z = StrHex2int("0x" + hex.substr(5, 2));
	result.Value.w = StrHex2int("0x" + hex.substr(7, 2));

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

void ThemeManager::DrawSetting() {

	if (ImGui::Button(u8"Тёмная"))
		SetDarkTheme();

	ImGui::SameLine();

	if (ImGui::Button(u8"Светлая"))
		SetLightTheme();

	ImGui::SameLine();

	if (ImGui::Button(u8"Применить"))
		LoadForced();

	for (int i = 0; i < objects.size(); i++) {
		auto colors_data = objects[i]->GetColorsPTR();
		std::string NameObject = "##color" + objects[i]->GetName();

		if (ImGui::TreeNode(objects[i]->GetName().c_str())) {

			for (int i = 0; i < colors_data->size(); i++) {
				if (ImGui::ColorEdit4(std::string(NameObject + std::to_string(i)).c_str(), (float*)&colors_data->at(i).color, ImGuiColorEditFlags_AlphaPreviewHalf | ImGuiColorEditFlags_None)) {
					LoadForced();
				}
				ImGui::SameLine();
				ImGui::Text(colors_data->at(i).nameColor.c_str());
			}

			ImGui::TreePop();
		}

		
	}

}