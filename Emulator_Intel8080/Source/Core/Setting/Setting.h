#ifndef SETTING_H
#define SETTING_H

#include "Core/SaveSystem/SaveSystem.h"
#include "interfaces/ISettingObject.h"
#include "Utils/Text/Text.h"


class Setting : public SaveSystem
{
public:
	Setting();
	~Setting();

	void AddSettingObject(ISettingObject* object);

	void Draw();


	void Toggle();
	void Open();
	bool isOpen();

	nlohmann::json Save() override;
	void Load(const nlohmann::json& SaveData) override;

private:

	struct Tabs{
		std::string TabName;
		std::vector<ISettingObject*> setting_objects;
	};

	std::vector<Tabs> tabs;


	bool Popup_Open = false;


	int GetIndexTab(const std::string& NameTab);
	int GetIndexSettingObject(const int& indexTab, const std::string& NameObject);
};

#endif // !SETTING_H

