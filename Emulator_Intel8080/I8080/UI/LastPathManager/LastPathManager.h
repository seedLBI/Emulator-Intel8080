#ifndef LAST_PATH_MANAGER_H
#define LAST_PATH_MANAGER_H

#include "OpenglWindow\OpenglWindow.h"
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
	/// ��������� ������ � Menu
	/// </summary>
	bool Draw();

	std::string GetChoosedPath();

	void Load(const std::string& Data) override;
	std::string Save() override;

private:
	std::vector<std::string> paths;

	int IndexChoosed = 0;

	bool PathIsExist(const std::string& name);
	int PathIsNotEqual(const std::string& name);

};




#endif // !LAST_PATH_MANAGER_H

