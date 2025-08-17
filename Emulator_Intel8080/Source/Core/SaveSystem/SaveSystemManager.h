#ifndef SAVE_SYSTEM_MANAGER_H
#define SAVE_SYSTEM_MANAGER_H

#include "SaveSystem.h"

#include "Utils/File/File.h"
#include "Utils/Text/Text.h"
#include "Utils/Text/Encoding/Wstring/Wstring.h"

#include "Core/Workspaces/Workspace.DefaultSave.h"

#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#ifdef _DEBUG
#include <iostream>
#endif


class SaveSystemManager
{
public:
	SaveSystemManager(const std::wstring& SavingPath);
	~SaveSystemManager();

	void ChangePathSaving(const std::wstring& newPath);
	void AddObjectPtr(SaveSystem* object);

	void Save();
	void Load();

private:
	std::wstring SavingPath;
	std::vector<SaveSystem*> objects;

	int GetIndexSaveObject(const std::string& NameObject);

	void ReadFromFile(std::ifstream& FileSave);
	void ReadFromMemory(const std::string& Data);


	void LoadAllSaveToObjects(const nlohmann::json& SaveData);
};

#endif // !SAVE_SYSTEM_MANAGER_H
