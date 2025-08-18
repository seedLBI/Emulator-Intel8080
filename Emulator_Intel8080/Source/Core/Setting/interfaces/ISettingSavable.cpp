#include "ISettingSavable.h"


ISettingSavable::ISettingSavable(const std::string& NameObject) {
	this->NameObject      = NameObject;
	this->NameObject_cstr = NameObject.c_str();
}

nlohmann::json ISettingSavable::SaveSetting() {
#ifdef _DEBUG
	std::cout << "nlohmann::json ISettingSavable::SaveSetting()\n";
#endif // _DEBUG

	return nlohmann::json();
}
void ISettingSavable::LoadSetting(const nlohmann::json& Data) {
#ifdef _DEBUG
	std::cout << "void ISettingSavable::LoadSetting(const nlohmann::json& Data)\n";
#endif // _DEBUG
}

std::string ISettingSavable::GetSaveObjectName() {
	return NameObject;
}
const char* ISettingSavable::GetSaveObjectName_cstr() {
	return NameObject_cstr;
}
