#ifndef LAST_PATH_MANAGER_H
#define LAST_PATH_MANAGER_H

#include "OpenglWindow/OpenglWindow.h"
#include "Utils/File_Utils.h"
#include "Core/Setting/interfaces/ISettingObject.h"
#include "Core/SaveSystem/SaveSystem.h"
#include <string>
#include <vector>

class LastPathManager : public SaveSystem, public ISettingObject
{
public:
	LastPathManager();
	~LastPathManager();


	void AddPath(std::string path);

	/// <summary>
	/// Рендерить только в Menu
	/// </summary>
	bool Draw();

	std::string GetChoosedPath();

	void DrawSetting() override;
	nlohmann::json SaveSetting() override;
	void LoadSetting(const nlohmann::json& Data) override;

	void Load(const nlohmann::json& Data) override;
	nlohmann::json Save() override;

private:
	std::vector<std::string> paths;

	int IndexChoosed = 0;

	int PathIsNotEqual(const std::string& name);

	bool ShowAllPath = true;
};




#endif // !LAST_PATH_MANAGER_H