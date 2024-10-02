#include "FontManager.h"



FontManager::FontManager():SaveSystem("Font") {
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "Reading icon font: Fonts\\fa-solid-900.ttf\n";
#endif

	LoadIconsFont_fromMemory();
	LoadDefaultMainFont_fromMemory();

	SetFont("JetBrainsMonoNL");

}

FontManager::~FontManager() {

}

void FontManager::Draw() {


	ImGui::SeparatorText(u8"Шрифт");

	if (ImGui::BeginCombo(u8"Шрифт", Name_Font_Selected.c_str(), ImGuiComboFlags_WidthFitPreview)) {

		for (int i = 0; i < List_Fonts.size(); i++)
		{
			bool selected = List_Fonts[i].Name == Name_Font_Selected;

			if (ImGui::Selectable(List_Fonts[i].Name.c_str(), &selected)) {
				SetFont(List_Fonts[i].Name);
			}

			if (selected)
				ImGui::SetItemDefaultFocus();
		}


		if(ButtonCenteredOnLine(u8"Добавить свой шрифт", 0.5f)){
			nfdchar_t* outPath = NULL;
			nfdresult_t result = NFD_OpenDialog("ttf,otf", NULL, &outPath);
			if (result == NFD_OKAY) {
				LoadFontFromFile(outPath);
			}
			else if (result == NFD_CANCEL) {
#ifdef WITH_DEBUG_OUTPUT
				std::cout << "User pressed cancel.\n";
#endif
			}
			else {
				printf("Error: %s\n", NFD_GetError());
			}
		}

		ImGui::EndCombo();
	}
	ImGui::SameLine();
	HelpMarker(u8"Выбор типа шрифта");



	if (ImGui::BeginCombo(u8"Размер", std::to_string(Current_Scale).c_str(), ImGuiComboFlags_WidthFitPreview)) {

		for (int i = 0; i < GetListSizes().size(); i++) {

			bool selected = stoi(GetListSizes()[i]) == Current_Scale;

			if (ImGui::Selectable(GetListSizes()[i].c_str(), &selected)) {
				Current_Scale = stoi(GetListSizes()[i]);
				NeedReloadFontSize = true;
			}

			if (selected)
				ImGui::SetItemDefaultFocus();
		}

		ImGui::EndCombo();
	}
	ImGui::SameLine();
	HelpMarker(u8"Единица измерения - пиксель.");



}

void FontManager::SetFont(const std::string& NameFont) {

	int Index_Font = -1;
	for (int i = 0; i < List_Fonts.size(); i++)
	{
		if (List_Fonts[i].Name == NameFont) {
			Index_Font = i;
		}
	}
	
	if (Index_Font == -1){

		Name_Font_Selected = "JetBrainsMonoNL";
		MainFontData = Default_MainFont;
	}
	else{
		Name_Font_Selected = NameFont;

		MainFontData = List_Fonts[Index_Font].Data;
#ifdef WITH_DEBUG_OUTPUT
		std::cout << "set data: " << MainFontData.size() << std::endl;
#endif
	}

	
	NeedReloadFontSize = true;
}

void FontManager::SetSize(const int& sizeFont) {
	if (sizeFont < Min_Scale)
		Current_Scale = Min_Scale;
	else if(sizeFont > Max_Scale)
		Current_Scale = Max_Scale;
	else
		Current_Scale = sizeFont;
}

void FontManager::LoadNewFont() {

}

void FontManager::LoadFontFromFile(std::string Path2File) {
	std::string name = Path2File.substr(Path2File.find_last_of('\\') + 1);
	name.erase(name.begin() + name.find_last_of("."), name.end());

	FontInfo new_font;
	new_font.Path = Path2File;
	new_font.Name = name;
	new_font.Data = readFileToByteArray(Path2File);

	if (new_font.Data.empty())
		return;

#ifdef WITH_DEBUG_OUTPUT
	std::cout << "Loading new font:\n";
	std::cout << "Path: [" << new_font.Path << "]" << std::endl;
	std::cout << "Name: [" << new_font.Name << "]" << std::endl;
	std::cout << "size: [" << new_font.Data.size() << "]" << std::endl;
#endif

	List_Fonts.push_back(new_font);
}

void FontManager::ReloadFont() {
	if (NeedReloadFontSize) {
		NeedReloadFontSize = false;

		ImGuiIO& io = ImGui::GetIO();
		if (io.Fonts->Locked)
		{
			std::cout << "cannot resize font(((" << std::endl;
			return;
		}

		ImFontConfig font_cfg;
		font_cfg.FontDataOwnedByAtlas = false;
		font_cfg.MergeMode = false;


		io.Fonts->Clear();  // Очистить текущие шрифты
		io.Fonts->Fonts.clear();




		if (MainFont != nullptr) {
			MainFont->ClearOutputData();
		}


		MainFont = io.Fonts->AddFontFromMemoryTTF(MainFontData.data(), MainFontData.size(), Current_Scale, &font_cfg, io.Fonts->GetGlyphRangesCyrillic());

		float iconFontSize = Current_Scale * 2.0f / 3.0f;
		static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
		ImFontConfig icons_config;
		icons_config.MergeMode = true;
		icons_config.PixelSnapH = true;
		icons_config.GlyphMinAdvanceX = iconFontSize;


		if (IconsFont != nullptr) {
			IconsFont->ClearOutputData();
		}

		IconsFont = io.Fonts->AddFontFromMemoryTTF(IconsFontData.data(), IconsFontData.size(), iconFontSize, &icons_config, icons_ranges);

		io.Fonts->Build();  // Перестроить атлас шрифтов


		ImGui_ImplOpenGL3_DestroyDeviceObjects();
		if (ImGui_ImplOpenGL3_CreateDeviceObjects() == false)
		{
			cout << "Error CreateDeviceObjects" << endl;
		}
		ImGui_ImplOpenGL3_DestroyFontsTexture();
		if (ImGui_ImplOpenGL3_CreateFontsTexture() == false) {
			cout << "Error CreateFontsTexture" << endl;
		}



		ImGui::SetCurrentFont(MainFont);

		//cout << "font seted" << endl;


		//ImGui::LoadIniSettingsFromMemory(INIdata, size);
	}
}

std::vector<std::string> FontManager::GetListSizes() {
	static std::vector<std::string> list;

	if (list.empty()) {
		for (int i = Min_Scale; i <= Max_Scale; i++){
			list.push_back(std::to_string(i));
		}
	}

	return list;
}

std::vector<FontInfo> FontManager::GetList_FontInfo() {
	return List_Fonts;
}

std::string FontManager::Save() {
	std::string result = MakeBegin(2 + List_Fonts.size() - 1);

	for (int i = 0; i < List_Fonts.size(); i++) {
		if (!List_Fonts[i].Path.empty())
			result += MakeSaveItem("Path", List_Fonts[i].Path);
	}

	result += MakeSaveItem("Scale", std::to_string(Current_Scale));
	result += MakeSaveItem("Font selected", Name_Font_Selected);


	return result;
}

void FontManager::Load(const std::string& Data) {
	PrintDebugInfoAboutData(Data);

	auto save_info = SplitData(Data);

	for (int i = 0; i < save_info.size(); i++){

		std::string Name_Element = save_info[i].first;
		std::string Data_Element = save_info[i].second;

		if (Name_Element == "Path"){
			LoadFontFromFile(Data_Element);
		}
		else if (Name_Element == "Font selected") {
			SetFont(Data_Element);
		}
		else if (Name_Element == "Scale") {
			SetSize(stoi(Data_Element));
		}
		else {
			std::cout << "Unknowed save element founded: [" << Name_Element << "] [" << Data_Element << "]\n";
		}
	}

}



void FontManager::LoadDefaultMainFont_fromMemory() {
	FontInfo new_font;
	new_font.Path = "";
	new_font.Name = u8"JetBrainsMonoNL";
	new_font.Data = Default_MainFont;

	List_Fonts.push_back(new_font);
}

void FontManager::LoadIconsFont_fromMemory() {
	IconsFontData = fa_solid_900;
}
