#include "Highlighter.h"



void Highlighter::InitListWordsAndColors() {

}

ImColor Highlighter::GetColorFromName(std::string name) {
	ToLowerAll(name);

	for (auto& obj : categories) {
		for (auto& obj_name : obj.Names) {
			if (obj_name == name)
				return obj.color;
		}
	}

	return ImColor{ 0 };
}

int Highlighter::GetIndexFromName(std::string name) {
	ToLowerAll(name);

	for (int i = 0; i < categories.size(); i++){
		for (int j = 0; j < categories[i].Names.size(); j++){
			if (categories[i].Names[j] == name) {
				return i;
			}
		}
	}

	return -1;
}

ImColor Highlighter::GetColorFromIndex(const int& index) {
	if (index >= 0 && index <= categories.size() - 1)
		return categories[index].color;
	return ImColor(0);
}



std::vector<NamedColor> Highlighter::GetDefaultLightColors() {
	return {};
}

std::vector<NamedColor> Highlighter::GetDefaultDarkColors() {
	return {};
}

void Highlighter::LoadColors() {
	for (int i = 0; i < object_colors.colors.size(); i++) {
		std::string toSearch = object_colors.colors[i].nameColor;

		for (int j = 0; j < categories.size(); j++) {
			if (categories[j].Category == toSearch) {
				categories[j].color = object_colors.colors[i].color;
				break;
			}
		}
	}
}


Highlighter::Highlighter(const std::string& name) : IThemeLoadable(name) {
	InitListWordsAndColors();
}

Highlighter::~Highlighter() {

}