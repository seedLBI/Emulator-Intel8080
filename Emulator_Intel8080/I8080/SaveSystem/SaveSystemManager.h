#ifndef SAVE_SYSTEM_MANAGER_H
#define SAVE_SYSTEM_MANAGER_H

#include "Config_Compilier.h"
#include "SaveSystem\SaveSystem.h"
#include "Utils/File_Utils.h"
#include <vector>
#include <fstream>
#include <iostream>


class SaveSystemManager
{
public:
	SaveSystemManager(const std::string& SavingPath);
	~SaveSystemManager();

	void ChangePathSaving(const std::string& newPath);
	void AddObjectPtr(SaveSystem* object);

	void Save();
	void Load();

private:
	std::string SavingPath;
	std::vector<SaveSystem*> objects;

	int GetIndexSaveObject(const std::string& NameObject);
};

#endif // !SAVE_SYSTEM_MANAGER_H
