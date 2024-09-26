#include "LastPathManager.h"

LastPathManager::LastPathManager():SaveSystem("LastPaths")
{
}

LastPathManager::~LastPathManager()
{
}
/// <summary>
/// ¬озвращает true если пользователь нажал на один из путей
/// </summary>
/// <returns></returns>
bool LastPathManager::Draw() {
	bool pressed = false;

	if (paths.size() == 0)
	{
		ImGui::Text(u8"ѕока что здесь пусто, ну ты это.. хот€ бы сохрани или открой файл € не знаю");
	}
	else {
		for (int i = 0; i < paths.size(); i++)
		{
			if (ImGui::MenuItem(std::string(std::to_string(i + 1) + ". " + paths[i]).c_str())) {
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
	if (!PathIsExist(path))
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

bool LastPathManager::PathIsExist(const std::string& name) {
	if (FILE* file = fopen(name.c_str(), "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}
int LastPathManager::PathIsNotEqual(const std::string& name) {
	for (int i = 0; i < paths.size(); i++) {
		if (paths[i] == name)
			return i;
	}
	return -1;
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