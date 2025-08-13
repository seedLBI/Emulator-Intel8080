#include "IThemeLoadable.h"

IThemeLoadable::IThemeLoadable(const std::string& NameObject) {
	this->object_colors.nameObject = NameObject;
}
IThemeLoadable::~IThemeLoadable() {

}

void IThemeLoadable::SetDefaultLightColors() {
	MergeColors(GetDefaultLightColors());
	LoadColors();
}
void IThemeLoadable::SetDefaultDarkColors() {
	MergeColors(GetDefaultDarkColors());
	LoadColors();
}

std::vector<NamedColor> IThemeLoadable::GetDefaultLightColors() {
	return {};
}
std::vector<NamedColor> IThemeLoadable::GetDefaultDarkColors() {
	return {};
}

std::string IThemeLoadable::GetName() {
	return object_colors.nameObject;
}

void IThemeLoadable::InitListWord(const std::vector<std::string>& Names) {
	object_colors.colors.clear();
	object_colors.colors.resize(Names.size());

	for (int i = 0; i < Names.size(); i++) {
		object_colors.colors[i].nameColor = Names[i];
		object_colors.colors[i].color = ImColor(0);
	}
}

void IThemeLoadable::LoadColors(const std::vector<NamedColor>& colors) {
	MergeColors(colors);
	LoadColors();
}
void IThemeLoadable::LoadColors() {

}

std::vector<NamedColor> IThemeLoadable::GetColors() {
	return object_colors.colors;
}

std::vector<NamedColor>* IThemeLoadable::GetColorsPTR() {
	return &object_colors.colors;
}




void IThemeLoadable::MergeColors(const std::vector<NamedColor>& colors) {
	for (int i = 0; i < colors.size(); i++){
		auto obj = colors[i];
		auto it = std::find_if(object_colors.colors.begin(), object_colors.colors.end(), [&obj](const NamedColor& to_check) {return to_check.nameColor == obj.nameColor; });
		if (it != object_colors.colors.end()) {
			int index =int(it - object_colors.colors.begin());
			object_colors.colors[index].color = obj.color;
		}
	}
}