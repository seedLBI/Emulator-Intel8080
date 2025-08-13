#ifndef ISETTING_SAVABLE_H
#define ISETTING_SAVABLE_H

#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "Utils/Text/Text.h"


class ISettingSavable {
public:
	ISettingSavable(const std::string& NameObject);

	virtual nlohmann::json SaveSetting();
	virtual void LoadSetting(const nlohmann::json& Data);

	std::string GetSaveObjectName();
	const char* GetSaveObjectName_cstr();

private:
	std::string NameObject;
	const char* NameObject_cstr;
};



#endif // !ISETTING_SAVABLE_H
