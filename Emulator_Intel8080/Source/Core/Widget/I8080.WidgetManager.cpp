#include "I8080.WidgetManager.h"

I8080_WidgetManager::I8080_WidgetManager(FPS_Timer* fps_timer) : SaveSystem("Widgets") {
	this->fps_timer = fps_timer;
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
	ptr_widget->Init_FPS_Timer(fps_timer);

	if (ptr_widget->GetName() == u8"Руководство")
		indexHelp = (int)ptr_widgets.size() - 1;
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
#ifdef _DEBUG
	std::cout << "Don't have widget object with Name: " << NameObject << std::endl;
#endif
	//exit(545);
	return -1;
}

void I8080_WidgetManager::Load(const nlohmann::json& Data) {

	for (auto& [name_widget, widget_data] : Data.items()) {
		int index_widget = GetIndexSaveObject(name_widget);
		if (index_widget == -1) 
			continue;
		ptr_widgets[index_widget]->Load(widget_data);
	}

}


nlohmann::json I8080_WidgetManager::Save() {

	nlohmann::json result;

	for (int i = 0; i < ptr_widgets.size(); i++)
		result[ptr_widgets[i]->GetName()] = ptr_widgets[i]->Save();
	
	return result;

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