#ifndef THEME_MANAGER_H
#define THEME_MANAGER_H

#include "Core/Theme/Theme.h"
#include "Core/Theme/interface/IThemeLoadable.h"
#include "Core/Setting/interfaces/ISettingObject.h"

#include "Utils/Values/Values.h"
#include "Utils/Text/Text.h"
#include "Utils/ImGui/Utils.ImGui.h"


class ThemeManager : public ISettingObject {
public:
	ThemeManager ();
	~ThemeManager ();
	
	void LoadChoosedTheme();
	void LoadForced();


	void AddObject(IThemeLoadable* new_object);

	nlohmann::json SaveSetting() override;
	void LoadSetting(const nlohmann::json& SaveData) override;

	void DrawSetting() override;



private:
	std::vector<IThemeLoadable*> objects;

	std::vector<Theme> themes;
	int indexChoosed = 0;

	int countObjects = 0;

	void CalculateCountObjects();

	void SetDarkTheme();
	void SetLightTheme();

	void CreateThemeFromCurrentColors(const std::string& name);


	bool PopupCreation_isOpen = false;
	void DrawPopupCreation();


	std::string ImColor2Hex(const ImColor& color);
	ImColor Hex2ImColor(const std::string& hex);
};




#endif // !THEME_MANAGER_H
