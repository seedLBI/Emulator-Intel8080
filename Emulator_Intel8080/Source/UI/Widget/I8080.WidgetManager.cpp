#include "I8080.WidgetManager.h"

I8080_WidgetManager::I8080_WidgetManager() : SaveSystem("Widgets")
{

}


I8080_WidgetManager::~I8080_WidgetManager()
{
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "I8080_WidgetManager::~I8080_WidgetManager()\n";
#endif // !WITH_DEBUG_OUTPUT
}


void I8080_WidgetManager::Draw() {
	for (int i = 0; i < ptr_widgets.size(); i++) {


		ptr_widgets[i]->UpdateFocus();
		ptr_widgets[i]->Draw();


		float TimerFocus = ptr_widgets[i]->GetTimerFocus()* ptr_widgets[i]->GetTimerFocus();
		if (TimerFocus > 0.f) {

			ImGuiWindow* window = ImGui::FindWindowByName(ptr_widgets[i]->GetName_c_str());

			auto drawlist = window->DrawList;

			drawlist->AddRectFilled(
				window->Pos,
				{ window->Pos.x + window->Size.x,window->Pos.y + window->Size.y },
				ImGui::ColorConvertFloat4ToU32(ImVec4(0.f, TimerFocus, 0.f, TimerFocus)));
		}
	}
}
void I8080_WidgetManager::Update() {

	for (int i = 0; i < ptr_widgets.size(); i++)
		ptr_widgets[i]->Update();

	if (indexHelp == -1)
		return;

	std::string NamePressedButtonFromHelp = ptr_widgets[indexHelp]->GetCommand();
	if (NamePressedButtonFromHelp.empty())
		return;

	int index = GetIndexSaveObject(NamePressedButtonFromHelp);

	if (ptr_widgets[index]->GetFlagShow() == false)
		ptr_widgets[index]->SetFlagShow(true);
	else
		ptr_widgets[index]->SetFocus();

}

int I8080_WidgetManager::FindIndex(std::string nameWidget) {
	for (int i = 0; i < ptr_widgets.size(); i++) {
		if (ptr_widgets[i]->GetName() == nameWidget)
			return i;
	}
	return -1;
}

void I8080_WidgetManager::AddWidgetPtr(I8080_Widget* ptr_widget) {
	ptr_widgets.emplace_back(ptr_widget);
	if (ptr_widget->GetName() == u8"Руководство")
		indexHelp = ptr_widgets.size() - 1;
}

void I8080_WidgetManager::LoadVisibilitySettings(std::vector<std::pair<std::string, bool>> settingData) {
	for (int i = 0; i < settingData.size(); i++) {
		int index = FindIndex(settingData[i].first);
		if (index != -1)
			ptr_widgets[index]->SetFlagShow(settingData[i].second);
	}
}

std::vector<std::pair<std::string, bool>> I8080_WidgetManager::GetVisibilitySettings() {
	std::vector<std::pair<std::string, bool>> result;
	for (int i = 0; i < ptr_widgets.size(); i++){
		result.emplace_back(std::pair<std::string, bool>{ ptr_widgets[i]->GetName(),ptr_widgets[i]->GetFlagShow() });
	}
	return result;
}

int I8080_WidgetManager::GetIndexSaveObject(const std::string& NameObject) {
	for (int i = 0; i < ptr_widgets.size(); i++){
		if (ptr_widgets[i]->GetName() == NameObject)
			return i;
	}
	std::cout << "Don't have widget object with Name: " << NameObject << std::endl;
	exit(545);
}

void I8080_WidgetManager::Load(const std::string& Data) {
	PrintDebugInfoAboutData(Data);


	std::vector<std::string> Lines = split(Data, "\n");

	Lines.erase(Lines.begin());

	//std::cout << "-----------WidgetManager splited lines----------------" << std::endl;
	//for (int i = 0; i < Lines.size(); i++)
	//	std::cout << Lines[i] << std::endl;

	int index = 0;


	while (index < Lines.size() - 1) {
		auto begin = Lines[index].find_first_of('[') + 1;
		auto end = Lines[index].find_first_of(']');

		std::string text = Lines[index].substr(begin, end - begin);

		if (text == "BEGIN") {
			begin = Lines[index].find_last_of('[') + 1;
			end = Lines[index].find_last_of(']');

			std::string name_widget = Lines[index].substr(begin, end - begin);

			int index_object_widget = GetIndexSaveObject(name_widget);

			begin = Lines[index].find_last_of('(') + 1;
			end = Lines[index].find_last_of(')');

			int count_lines = stoi(Lines[index].substr(begin, end - begin));

			std::string data = "";

			for (int i = 0; i < count_lines; i++){
				index++;
				if (i == count_lines - 1)
					data += Lines[index];
				else
					data += Lines[index] + "\n";
			}
			ptr_widgets[index_object_widget]->Load(data);
		}


		index++;
	}

}


std::string I8080_WidgetManager::Save() {
	std::string output = "";

	std::string data = "";
	for (int i = 0; i < ptr_widgets.size(); i++)
		data += ptr_widgets[i]->Save();


	output += MakeBegin(GetCountLines(data));
	output += data;


	return output;
}



bool I8080_WidgetManager::GetFlag_AllOpened() {

	for (int i = 0; i < ptr_widgets.size(); i++)
	{
		if (ptr_widgets[i]->GetFlagShow() == false)
		{
			return false;
		}
	}

	return true;
}

void I8080_WidgetManager::CloseAll() {
	for (int i = 0; i < ptr_widgets.size(); i++)
		ptr_widgets[i]->SetFlagShow(false);
}
void I8080_WidgetManager::OpenAll() {
	for (int i = 0; i < ptr_widgets.size(); i++)
		ptr_widgets[i]->SetFlagShow(true);
}