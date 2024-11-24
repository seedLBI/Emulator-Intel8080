#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H


#include <imgui_internal.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Config_Compilier.h"
#include "IconFontCppHeaders/IconsFontAwesome6.h"
#include "Utils/TextUtils.h"
#include "Utils/ImGui.Utils.h"
#include "UI/Setting/ISettingObject.h"
#include "SaveSystem\SaveSystem.h"
#include "nfd.h"

#include "FontsData/IconsFont.h"
#include "FontsData/MainFont.h"

#include <string>
#include <vector>
#include <iostream>


struct FontInfo {
	std::string Name;
	std::string Path;
	std::vector<uint8_t> Data;
};

class FontManager : public ISettingObject {

public:
	FontManager();
	~FontManager();

	void SetFont(const std::string& NameFont);
	void SetSize(const int& sizeFont);


	void SetOneStepBigger();
	void SetOneStepSmaller();




	void LoadNewFont();

	std::vector<FontInfo> GetList_FontInfo();
	std::vector<std::string> GetListSizes();

	void DrawSetting() override;
	std::string SaveSetting() override;
	void LoadSetting(const std::string& Data) override;

	// TODO: Put it after ImGui::EndFrame()
	void ReloadFont();


private:
	int Current_Scale = 21;
	static const int Min_Scale = 12;
	static const int Max_Scale = 34;

	std::vector<FontInfo> List_Fonts;


	bool NeedReloadFontSize = false;
	std::string Name_Font_Selected = "";


	ImFont* MainFont = nullptr;
	ImFont* IconsFont = nullptr;

	std::vector<uint8_t> IconsFontData;
	std::vector<uint8_t> MainFontData;

	void LoadFontFromFile(std::string Path2File);

	void LoadDefaultMainFont_fromMemory();
	void LoadIconsFont_fromMemory();


};





#endif // !FONT_MANAGER_H
