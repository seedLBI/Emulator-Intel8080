#include "SaveSystemManager.h"


SaveSystemManager::SaveSystemManager(const std::wstring& SavingPath) {
#ifdef _DEBUG
	std::cout << "SaveSystemManager::SaveSystemManager(const std::wstring& SavingPath)\n";
#endif
	this->SavingPath = SavingPath;
}

SaveSystemManager::~SaveSystemManager() {
#ifdef _DEBUG
	std::cout << "SaveSystemManager::~SaveSystemManager()\n";
#endif
}

void SaveSystemManager::ChangePathSaving(const std::wstring& newPath) {
	this->SavingPath = newPath;
}

void SaveSystemManager::AddObjectPtr(SaveSystem* object) {
	objects.emplace_back(object);
}



void SaveSystemManager::Save() {
	nlohmann::json SaveData;

	for (SaveSystem* obj : objects) {
		SaveSystem::merge_json(SaveData[obj->GetName()], obj->Save());
	}

	std::ofstream FileSave;
	FileSave.open(SavingPath);
	FileSave << SaveData.dump(4);
	FileSave.close();
}


void SaveSystemManager::Load() {

	std::ifstream FileSave;
	FileSave.open(SavingPath);


	if (isFileExist(FileSave) == false) {
#ifdef _DEBUG
		std::cout << "File save [not exist]\n";
#endif
		//ReadFromMemory(DefaultSaveData);
	}
	else if (isFileNotEmpty(FileSave) == false) {
#ifdef _DEBUG
		std::cout << "File save [empty]\n";
#endif
	}
	else {
#ifdef _DEBUG
		std::cout << "File save [Begin Reading]:\n";
#endif

		ReadFromFile(FileSave);
	}

	FileSave.close();
}


int SaveSystemManager::GetIndexSaveObject(const std::string& NameObject) {
	for (int i = 0; i < objects.size(); i++){
		if (objects[i]->GetName() == NameObject)
			return i;
	}
#ifdef _DEBUG
	std::cout << "Save object with name: [" << NameObject << "] not exist\n";
#endif
	//exit(101);
	return -1;
}

void SaveSystemManager::LoadAllSaveToObjects(const nlohmann::json& SaveData) {

	for (auto& [key, value] : SaveData.items()) {

		int indexObject = GetIndexSaveObject(key);
		if (indexObject == -1)
			continue;

		objects[indexObject]->Load(value);

	}

}



void SaveSystemManager::ReadFromFile(std::ifstream& FileSave) {

	nlohmann::json DataLoad;

	try {
		DataLoad = nlohmann::json::parse(FileSave);
	}
	catch (const nlohmann::json::parse_error& e) {
#ifdef _DEBUG
		std::cout << "INCORRECT JSON DATA\n";
#endif
		return;
	}

	LoadAllSaveToObjects(DataLoad);
}

void SaveSystemManager::ReadFromMemory(const std::string& Data) {

	nlohmann::json DataLoad;

	try {
		DataLoad = nlohmann::json::parse(Data);
	}
	catch (const nlohmann::json::parse_error& e) {
#ifdef _DEBUG
		std::cout << "INCORRECT JSON DATA\n";
#endif
		return;
	}

	LoadAllSaveToObjects(DataLoad);
}
