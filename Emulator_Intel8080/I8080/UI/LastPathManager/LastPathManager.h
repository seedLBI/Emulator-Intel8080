#ifndef LAST_PATH_MANAGER_H
#define LAST_PATH_MANAGER_H

#include "OpenglWindow\OpenglWindow.h"
#include "Utils/File_Utils.h"
#include "SaveSystem\SaveSystem.h"
#include <string>
#include <vector>

class LastPathManager : SaveSystem
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

	void Load(const std::string& Data) override;
	std::string Save() override;

private:
	std::vector<std::string> paths;

	int IndexChoosed = 0;

	int PathIsNotEqual(const std::string& name);

};




#endif // !LAST_PATH_MANAGER_H

