#include "Setting.h"


Setting::Setting() : SaveSystem("Setting") {

}

Setting::~Setting() {
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "Setting::~Setting()\n";
#endif // !WITH_DEBUG_OUTPUT
}



void Setting::AddSettingObject(ISettingObject* object) {
	bool CreateNewOne = false;
	for (int i = 0; i < tabs.size(); i++) {
		if (tabs[i].TabName == object->NameTab) {
			tabs[i].setting_objects.emplace_back(object);
			return;
		}
	}
	Tabs newTab;
	newTab.TabName = object->NameTab;
	newTab.setting_objects.push_back(object);

	tabs.emplace_back(newTab);
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
		ImGuiWindowFlags_NoScrollbar;

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

std::string Setting::Save() {

	std::string data = "";
	for (int i = 0; i < tabs.size(); i++){
		for (int j = 0; j < tabs[i].setting_objects.size(); j++){
			data += tabs[i].setting_objects[j]->SaveSetting();
		}
	}

	std::string output = MakeBegin(GetCountLines(data));

	output += data;


	return output;

}

void Setting::Load(const std::string& Data) {
	PrintDebugInfoAboutData(Data);


	std::vector<std::string> Lines = split(Data, "\n");

	int index_line = -1;
	while (index_line != Lines.size() - 1) {
		index_line++;
		string line = Lines[index_line];

		auto begin = line.find_first_of('[') + 1;
		auto end = line.find_first_of(']');

		std::string FirstArgument = line.substr(begin, end - begin);
#ifdef WITH_DEBUG_OUTPUT
		std::cout << FirstArgument << std::endl;
#endif
		if (FirstArgument == "BEGIN") {

			begin = line.find_last_of('[') + 1;
			end = line.find_last_of(']');

			std::string Name_Object = line.substr(begin, end - begin);

			begin = line.find_last_of('(') + 1;
			end = line.find_last_of(')');
			int CountLines = stoi(line.substr(begin, end - begin));

			std::string Data_save_object = "";


			for (int i = 0; i < CountLines; i++) {
				index_line++;
				line = Lines[index_line];

				if (i == CountLines-1)
					Data_save_object += line;
				else
					Data_save_object += line + '\n';
			}

			for (int i = 0; i < tabs.size(); i++){
				for (int j = 0; j < tabs[i].setting_objects.size(); j++){
					if (tabs[i].setting_objects[j]->GetSaveObjectName() == Name_Object)
						tabs[i].setting_objects[j]->LoadSetting(Data_save_object);
				}
			}



		}

	}


}


