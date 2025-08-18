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
		ImGui::Text(u8"Пока что здесь пусто...\nхотя бы сохрани или открой файл я не знаю");
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

nlohmann::json LastPathManager::SaveSetting() {

	nlohmann::json result;

	result["flag_ShowAllPath"] = ShowAllPath;

	return result;

}

void LastPathManager::LoadSetting(const nlohmann::json& Data) {

	if (Data.contains("flag_ShowAllPath"))
		ShowAllPath = Data["flag_ShowAllPath"].get<bool>();

}



nlohmann::json LastPathManager::Save() {

	nlohmann::json result;

	for (int i = 0; i < paths.size(); i++)
		result["paths"][i] = paths[i];

	return result;

}


void LastPathManager::Load(const nlohmann::json& Data) {


	if (Data.contains("paths")) {
		for (auto& [index, PathData] : Data["paths"].items()) {
			AddPath(PathData.get<std::string>());
		}
	}


}