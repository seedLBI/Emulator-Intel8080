#include "SaveSystemManager.h"


void SaveSystemManager::ChangePathSaving(const std::string& newPath) {
	this->SavingPath = newPath;
}

void SaveSystemManager::AddObjectPtr(SaveSystem* object) {
	objects.emplace_back(object);
}

void SaveSystemManager::Save() {
	std::string SaveData = "";

	for (SaveSystem* obj : objects) {
		SaveData += obj->Save();
	}

	std::ofstream FileSave;
	FileSave.open(SavingPath);
	FileSave << SaveData;
	FileSave.close();
}


void SaveSystemManager::Load() {
	if (isFileExist(SavingPath)){

		std::ifstream FileSave;
		FileSave.open(SavingPath);

		if (isFileNotEmpty(FileSave))
		{
#ifdef WITH_DEBUG_OUTPUT
			std::cout << "File save [Begin Reading]:\n";
#endif
			while (!FileSave.eof()) {
				std::string line;
				getline(FileSave, line);
				if (line.empty())
					continue;

				auto begin = line.find_first_of('[') + 1;
				auto end = line.find_first_of(']');

				std::string FirstArgument = line.substr(begin, end - begin);
#ifdef WITH_DEBUG_OUTPUT
				std::cout <<"-------------------------" << FirstArgument << std::endl;
#endif
				if (FirstArgument == "BEGIN") {

					begin = line.find_last_of('[') + 1;
					end = line.find_last_of(']');

					std::string Name_Object = line.substr(begin, end - begin);

					begin = line.find_last_of('(') + 1;
					end = line.find_last_of(')');
					int CountLines = stoi(line.substr(begin, end - begin));
#ifdef WITH_DEBUG_OUTPUT
					std::cout << "-------------------------" << CountLines << std::endl;
#endif
					int index_save_object = GetIndexSaveObject(Name_Object);

					std::string Data_save_object = "";


					for (int i = 0; i < CountLines; i++) {
						getline(FileSave, line);

						if (i == CountLines - 1)
							Data_save_object += line;
						else
							Data_save_object += line + '\n';
					}

					objects[index_save_object]->Load(Data_save_object);
				}
			}


		}
		else {
			std::cout << "File save [empty]\n";
		}

		FileSave.close();
	}
	else {
		std::cout << "File save [not exist]\n";
	}
}


int SaveSystemManager::GetIndexSaveObject(const std::string& NameObject) {
	for (int i = 0; i < objects.size(); i++){
		if (objects[i]->GetName() == NameObject)
			return i;
	}

	std::cout << "Save object with name: [" << NameObject << "] not exist\n";
	exit(101);
	return -1;
}



SaveSystemManager::SaveSystemManager(const std::string& SavingPath) {
	this->SavingPath = SavingPath;
}

SaveSystemManager::~SaveSystemManager() {

}
