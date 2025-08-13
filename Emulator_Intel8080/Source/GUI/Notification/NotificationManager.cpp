#include "NotificationManager.h"




NotificationManager::NotificationManager() : ISettingObject(u8"Уведомления",u8"Общие") {

}

NotificationManager::~NotificationManager(){
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "NotificationManager::~NotificationManager()\n";
#endif // !WITH_DEBUG_OUTPUT
}

void NotificationManager::SetFlag_Enabled(const bool& flag) {
	isEnabled = flag;
}
void NotificationManager::ToggleFlag_Enabled() {
	isEnabled = !isEnabled;
}
bool NotificationManager::GetFlag_Enable() {
	return isEnabled;
}


void NotificationManager::AddNottification(const Notification& new_Notification) {
	if (!isEnabled)
		return;
	notifs.insert(notifs.begin(),new_Notification);

#ifdef WITH_DEBUG_OUTPUT
	std::cout << "Adding new Notification. Current count: " << notifs.size() << std::endl;
#endif // !WITH_DEBUG_OUTPUT


}






void NotificationManager::Draw() {
	if (!isEnabled)
		return;

	static const ImGuiWindowFlags flags = ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoSavedSettings;



	for (int i = 0; i < notifs.size(); i++) {

		notifs[i].Draw();

	}
}
void NotificationManager::Update() {
	if (!isEnabled)
		return;

	int size_x = 0, size_y = 0;
	glfwGetWindowSize(OpenglWindow::Vars::window, &size_x, &size_y);

	ImVec2 Pos = { 0.f,0.f };
	for (int i = 0; i < notifs.size(); i++) {



		notifs[i].SetPos({ Pos.x + notifs[i].GetSize().x,Pos.y });

		Pos.y += notifs[i].GetSize().y + distance_between;


		notifs[i].Update();

		if (notifs[i].isEnd()) {

#ifdef WITH_DEBUG_OUTPUT
			std::cout << "Deleting Notification." << std::endl;
#endif // !WITH_DEBUG_OUTPUT

			notifs.erase(notifs.begin() + i);
			i--;
		}
	}


	if (notifs.size() > maxCount){

		for (int i = maxCount; i < notifs.size(); i++){
			notifs[i].Kill();
		}

	}

}


void NotificationManager::DrawSetting() {
	ISettingObject::DrawBegin();

	if (ImGui::RadioButton(u8"Показывать", GetFlag_Enable()))
		ToggleFlag_Enabled();


}

nlohmann::json NotificationManager::SaveSetting() {

	nlohmann::json result;

	result["flag_Enabled"] = isEnabled;

	return result;

}

void NotificationManager::LoadSetting(const nlohmann::json& Data) {

	if (Data.contains("flag_Enabled"))
		isEnabled = Data["flag_Enabled"].get<bool>();

}