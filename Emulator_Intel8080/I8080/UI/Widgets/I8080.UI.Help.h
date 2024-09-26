#ifndef I8080_UI_HELP_H
#define I8080_UI_HELP_H

#include "Config_Compilier.h"
#include "Emulator\I8080.h"
#include "UI\Widget\I8080.Widget.h"
#include "Utils/File_Utils.h"
#include "Utils/ImGui.Utils.h"
#include "Utils/TextUtils.h"

#include <UTF8_2_CP1251/utf8_to_cp1251.h>
#include <string>
#include <fstream>
#include <vector>
#include <any>
#include <iostream>
#include <any>


class Widget_Help : public I8080_Widget
{
public:
	Widget_Help();
	~Widget_Help();
	void Draw() override;
	void Update() override;

	std::string Save() override;
	void Load(const std::string& Data) override;

private:

	bool EnableWrapedText = true;

	struct Abbriv {
		std::string name;
		std::string mean;
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
	void ReadFromFile(const std::string& Path2File);

	void DrawTextWithAbbrivs(const std::vector < std::vector< std::any >>& Text);

	void DrawRightMousePopup();
};



#endif // !I8080_UI_HELP_H
