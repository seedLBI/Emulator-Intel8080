#include "LastPathManager.h"

LastPathManager::LastPathManager():SaveSystem(u8"LastPaths"), ISettingObject(u8"Последние проекты", u8"Общие")
{
}

LastPathManager::~LastPathManager()
{
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "LastPathManager::~LastPathManager()\n";
#endif // !WITH_DEBUG_OUTPUT
}
/// <summary>
/// Возвращает true если пользователь нажал на один из путей
/// </summary>
/// <returns></returns>
bool LastPathManager::Draw() {
	bool pressed = false;

	if (paths.size() == 0)
	{
		ImGui::Text(u8"Пока что здесь пусто, ну ты это.. хотя бы сохрани или открой файл я не знаю");
	}
	else {
		for (int i = 0; i < paths.size(); i++){

			std::string PathDraw = std::to_string(i + 1) + ". ";

			if (!ShowAllPath)
				PathDraw += paths[i].substr(paths[i].find_last_of("\\") + 1);
			else
				PathDraw += paths[i];


			if (ImGui::MenuItem(PathDraw.c_str())) {
				IndexChoosed = i;
				pressed = true;
			}

		}
	}
	return pressed;
}

std::string LastPathManager::GetChoosedPath() {
	return paths[IndexChoosed];
}







void LastPathManager::AddPath(std::string path) {

	if (!isFileExist(path))
		return;

	int index = PathIsNotEqual(path);
	if (index == -1) {
		paths.emplace_back(path);
	}
	else {
		paths.erase(paths.begin() + index);
		paths.insert(paths.begin(), path);
	}
}


int LastPathManager::PathIsNotEqual(const std::string& name) {
	for (int i = 0; i < paths.size(); i++) {
		if (paths[i] == name)
			return i;
	}
	return -1;
}


void LastPathManager::DrawSetting() {
	ISettingObject::DrawBegin();

	if (ImGui::RadioButton(u8"Показывать абсолютный путь", ShowAllPath))
		ShowAllPath = !ShowAllPath;

}

std::string LastPathManager::SaveSetting() {
	std::string output;

	output += save_MakeBegin(1);
	output += save_MakeItem("ShowAllPath", std::to_string(ShowAllPath));

	return output;
}

void LastPathManager::LoadSetting(const std::string& Data) {
	auto TokenizedData = load_TokenizeData(Data);

	for (int i = 0; i < TokenizedData.size(); i++){

		if (TokenizedData[i].NameVar == "ShowAllPath")
			ShowAllPath = stoi(TokenizedData[i].ValueVar);

	}
}



std::string LastPathManager::Save() {
	std::string output = "";
	output += MakeBegin(paths.size());
	for (int i = 0; i < paths.size(); i++)
	output += MakeSaveItem(std::string("Path"), paths[i]);
	return output;
}


void LastPathManager::Load(const std::string& Data) {
	PrintDebugInfoAboutData(Data);

	auto save_info = SplitData(Data);

	for (int i = 0; i < save_info.size(); i++) {

		std::string Name_Element = save_info[i].first;
		std::string Data_Element = save_info[i].second;

		if (Name_Element == "Path")
			AddPath(Data_Element);
		else
			std::cout << "Unknowed save element founded: [" << Name_Element << "] [" << Data_Element << "]\n";

	}

}