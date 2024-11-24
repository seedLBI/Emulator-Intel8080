#ifndef ISETTING_SAVABLE_H
#define ISETTING_SAVABLE_H

#include <string>
#include <vector>
#include "Utils/TextUtils.h"


struct SettingLoadData {
	std::string  NameVar;
	std::string ValueVar;
	SettingLoadData(const std::string& NameVar, const std::string& ValueVar) {
		this->NameVar = NameVar;
		this->ValueVar = ValueVar;
	}
};

class ISettingSavable {
public:
	ISettingSavable(const std::string& NameObject);

	virtual std::string SaveSetting();
	virtual void LoadSetting(const std::string& Data);

	std::string GetSaveObjectName();
	const char* GetSaveObjectName_cstr();

	std::string save_MakeBegin(const int& count_Lines);
	std::string save_MakeItem(const std::string& NameItem, const std::string& ValueItem);

	std::vector<SettingLoadData> load_TokenizeData(const std::string& Data);

private:
	std::string NameObject;
	const char* NameObject_cstr;

	std::vector<std::string> SplitLine(const std::string& Line);
};



#endif // !ISETTING_SAVABLE_H
