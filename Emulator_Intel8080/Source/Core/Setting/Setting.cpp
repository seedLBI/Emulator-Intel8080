#include "Setting.h"


Setting::Setting() : SaveSystem("Setting") {
#ifdef _DEBUG
	std::cout << "Setting::Setting() : SaveSystem(\"Setting\")\n";
#endif
}

Setting::~Setting() {
#ifdef _DEBUG
	std::cout << "Setting::~Setting()\n";
#endif
}



void Setting::AddSettingObject(ISettingObject* object) {
	bool CreateNewOne = false;

	int indexTab = GetIndexTab(object->NameTab);

	if (indexTab != -1) {
		tabs[indexTab].setting_objects.emplace_back(object);
	}
	else {
		Tabs newTab;
		newTab.TabName = object->NameTab;
		newTab.setting_objects.push_back(object);

		tabs.emplace_back(newTab);
	}
}



void Setting::Draw() {
	if (Popup_Open == false)
		return;


	ImGui::OpenPopup(u8"Настройки");

	static const ImGuiWindowFlags flagsWindow = 
		ImGuiWindowFlags_NoDocking |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoScrollbar | 
		ImGuiWindowFlags_NoScrollWithMouse;

	ImVec2 center = ImGui::GetMainViewport()->GetCenter();

	ImVec2 size = ImGui::GetMainViewport()->WorkSize;
	ImGui::SetNextWindowSize(ImVec2(size.x / 1.5f, size.y / 1.5f));

	ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, ImVec2(0.5, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	if (ImGui::BeginPopupModal(u8"Настройки", &Popup_Open, flagsWindow)) {


		center.x -= ImGui::GetCurrentWindow()->Size.x / 2;
		center.y -= ImGui::GetCurrentWindow()->Size.y / 2;
		ImGui::GetCurrentWindow()->Pos = center;

		ImVec2 pos = ImGui::GetCursorScreenPos();


		ImGui::BeginChild("left pane", ImVec2(ImGui::CalcTextSize(u8"  Управление  ").x, 0));


		static int IndexChoosedTab = 0;

		for (int i = 0; i < tabs.size(); i++){
			if (ImGui::Selectable(tabs[i].TabName.c_str(), i == IndexChoosedTab, ImGuiSelectableFlags_Centered, ImVec2(0, ImGui::GetTextLineHeight() * 2.f)))
				IndexChoosedTab = i;
		}



		ImGui::EndChild();


		ImGui::SameLine(0.f, 0.f);
		ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical, 4.f);
		ImGui::SameLine(0.f, 10.f);

		ImGui::BeginChild("right pane");



		for (int j = 0; j < tabs[IndexChoosedTab].setting_objects.size(); j++) {
			tabs[IndexChoosedTab].setting_objects[j]->DrawSetting();
			ImGui::Dummy(ImVec2(1, 4));
		}


		ImGui::EndChild();


		/*
		string WaterMark = "seedLBI 2024";
		ImGui::SetCursorScreenPos(ImVec2((pos.x + avail_size.x) - ImGui::CalcTextSize(WaterMark.c_str()).x - 2.f, (pos.y + avail_size.y) - ImGui::CalcTextSize(WaterMark.c_str()).y - 7.f - 2.f));
		ImGui::TextColored(ImVec4(1, 1, 1, 0.2), WaterMark.c_str());
		*/


		ImGui::EndPopup();
	}

	ImGui::PopStyleVar();
	ImGui::PopStyleVar();

}



void Setting::Open() {
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "Open setting" << std::endl;
#endif

	Popup_Open = true;
}


void Setting::Toggle() {
	Popup_Open = !Popup_Open;
}


bool Setting::isOpen() {
	return Popup_Open;
}


nlohmann::json Setting::Save() {
	nlohmann::json SaveData;


	for (int i = 0; i < tabs.size(); i++) {
		nlohmann::json tab_SaveData;

		for (int j = 0; j < tabs[i].setting_objects.size(); j++) {
			SaveSystem::merge_json(tab_SaveData[tabs[i].TabName][tabs[i].setting_objects[j]->GetSaveObjectName()], tabs[i].setting_objects[j]->SaveSetting());
		}

		SaveSystem::merge_json(SaveData, tab_SaveData);
	}


	return SaveData;
}


void Setting::Load(const nlohmann::json& SaveData) {

	for (auto& [Tab_name, TabSettings] : SaveData.items()) {

		int indexTab = GetIndexTab(Tab_name);
		if (indexTab == -1)
			continue;


		for (auto& [setting_object_name, settings_data] : TabSettings.items()) {

			int indexObject = GetIndexSettingObject(indexTab, setting_object_name);

			if (indexObject == -1)
				continue;

			tabs[indexTab].setting_objects[indexObject]->LoadSetting(settings_data);
		}

	}


}


int Setting::GetIndexTab(const std::string& NameTab) {
	for (int i = 0; i < tabs.size(); i++) {
		if (tabs[i].TabName == NameTab)
			return i;
	}

#ifdef _DEBUG
	std::cout << "Tab with name: [" << NameTab << "] not exist\n";
#endif

	return -1;
}
int Setting::GetIndexSettingObject(const int& indexTab, const std::string& NameObject) {
	for (int i = 0; i < tabs[indexTab].setting_objects.size(); i++) {
		if (tabs[indexTab].setting_objects[i]->GetSaveObjectName() == NameObject)
			return i;
	}

#ifdef _DEBUG
	std::cout << "Object with name: [" << NameObject << "] not exist in Tab [" << tabs[indexTab].TabName << "]\n";
#endif

	return -1;
}

