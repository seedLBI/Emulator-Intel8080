#include "NotificationManager.h"




NotificationManager::NotificationManager() : SaveSystem(u8"Notification"){

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


std::string NotificationManager::Save() {
	std::string result = MakeBegin(1);

	result += MakeSaveItem("Enabled", std::to_string(isEnabled));

	return result;
}

void NotificationManager::Load(const std::string& Data) {
	PrintDebugInfoAboutData(Data);

	auto save_info = SplitData(Data);

	for (int i = 0; i < save_info.size(); i++) {

		std::string Name_Element = save_info[i].first;
		std::string Data_Element = save_info[i].second;

		if (Name_Element == "Enabled") {
			isEnabled = stoi(Data_Element);
		}
		else {
			std::cout << "Unknowed save element founded: [" << Name_Element << "] [" << Data_Element << "]\n";
		}
	}

}