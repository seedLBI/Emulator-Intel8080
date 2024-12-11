#ifndef THEME_MANAGER_H
#define THEME_MANAGER_H

#include "UI/Theme/Theme.h"
#include "UI/Theme/interface/IThemeLoadable.h"
#include "UI/Theme/BaseColors/BaseColors.h"
#include "UI/Setting/ISettingObject.h"
#include "Utils/Values/Values.Utils.h"
#include "Utils/TextUtils.h"


class ThemeManager : public ISettingObject {
public:
	ThemeManager ();
	~ThemeManager ();
	
	void LoadChoosedTheme();
	void LoadForced();


	void AddObject(IThemeLoadable* new_object);

	std::string SaveSetting() override;
	void LoadSetting(const std::string& Data) override;

	void DrawSetting() override;

private:
	std::vector<IThemeLoadable*> objects;

	std::vector<Theme> themes;
	int indexChoosed = 0;

	void SetDarkTheme();
	void SetLightTheme();



	std::string ImColor2Hex(const ImColor& color);
	ImColor Hex2ImColor(const std::string& hex);
};




#endif // !THEME_MANAGER_H
