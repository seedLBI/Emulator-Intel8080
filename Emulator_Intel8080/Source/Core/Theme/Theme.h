#ifndef THEME_H
#define THEME_H

#include <vector>
#include <string>
#include "ThirdParty/ImGui/imgui.h"


struct NamedColor {
	std::string nameColor;
	ImColor color;
};

struct ObjectColors {
	std::string nameObject;
	std::vector<NamedColor> colors;
};

struct Theme {
	std::string nameTheme;
	std::vector<ObjectColors> objectColors;
};



#endif // !THEME_H
