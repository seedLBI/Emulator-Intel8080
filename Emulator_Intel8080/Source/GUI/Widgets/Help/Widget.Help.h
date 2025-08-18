#ifndef I8080_UI_HELP_H
#define I8080_UI_HELP_H

#include "Config_Compilier.h"
#include "Core/Emulator/Processors/Intel8080/I8080.h"
#include "Core/Theme/interface/IThemeLoadable.h"
#include "Core/Widget/I8080.Widget.h"
#include "Core/Emulator/Processors/Intel8080/InfoInstruction/InfoInstruction.Display.h"

#include "Utils/File/File.h"
#include "Utils/ImGui/Utils.ImGui.h"
#include "Utils/Text/Text.h"

#include "Help.Data.h"

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <any>

#ifdef _DEBUG
#include <iostream>
#endif

class Widget_Help : public I8080_Widget, public IThemeLoadable
{
public:
	Widget_Help();
	~Widget_Help();
	void Draw() override;
	void Update() override;

	nlohmann::json Save() override;
	void Load(const nlohmann::json& Data) override;

	std::string GetCommand() override;

	void LoadColors() override;
	std::vector<NamedColor> GetDefaultLightColors() override;
	std::vector<NamedColor> GetDefaultDarkColors() override;

private:
	ImVec4 color_Category;
	ImVec4 color_SubCategory;
	ImVec4 color_Tooltip;
	ImVec4 color_Attention;

	std::string Button_pressed = "";

	bool isDataLoaded = false;

	bool EnableWrapedText = true;

	struct Abbriv {
		std::string name;
		std::string mean;
	};
	struct CodeBlock {
		std::string name;
		std::string text;
	};
	struct ColoredText {
		std::string text;
	};
	struct HyperTextForWidget {
		std::string text;
	};

	struct SubCategory {
		std::string name;
		std::vector < std::vector< std::any >> text_with_index;
	};
	struct Category {
		std::string name;
		std::vector<SubCategory> categories;
	};

	
	std::vector<Abbriv> abrivs;
	std::vector<Category> categories;


	std::any GetIndexAbbriv(const std::string& name);
	void ReadFromMemory();

	void DrawTextWithAbbrivs(const std::vector < std::vector< std::any >>& Text);

	void DrawRightMousePopup();
};



#endif // !I8080_UI_HELP_H
