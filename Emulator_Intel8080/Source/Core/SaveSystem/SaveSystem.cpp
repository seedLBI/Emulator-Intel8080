#include "SaveSystem.h"


SaveSystem::SaveSystem(const std::string& NameObject) {
	this->NameObject = NameObject;
}



SaveSystem::~SaveSystem() {
#ifdef _DEBUG
	std::cout << "SaveSystem::~SaveSystem()\n";
#endif
}

std::string SaveSystem::GetName() {
	return NameObject;
}

nlohmann::json SaveSystem::Save() {
#ifdef _DEBUG
	std::cout << "nlohmann::json SaveSystem::Save()\n";
#endif
	return nlohmann::json();
}
void SaveSystem::Load(const nlohmann::json& Data) {
#ifdef _DEBUG
	std::cout << "void SaveSystem::Load(const nlohmann::json& Data)\n";
#endif

}


void SaveSystem::merge_json(nlohmann::json& target, const nlohmann::json& source) {
	if (target.is_object() && source.is_object()) {
		for (auto& [key, value] : source.items()) {
			if (target.contains(key) && target[key].is_object() && value.is_object()) {
				merge_json(target[key], value);
			}
			else {
				target[key] = value;
			}
		}
	}
	else {
		target = source;
	}
}