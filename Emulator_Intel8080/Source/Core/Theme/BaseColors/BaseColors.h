#ifndef BASE_COLORS_H
#define BASE_COLORS_H

#ifdef _DEBUG
#include <iostream>
#endif
#include <memory>
#include <robin_hood.h>
#include "ThirdParty/ImGui/imgui.h"
#include "Core/Theme/interface/IThemeLoadable.h"

class BaseColors : public IThemeLoadable
{
public:
	BaseColors();
	~BaseColors();

	std::vector<NamedColor> GetDefaultLightColors() override;
	std::vector<NamedColor> GetDefaultDarkColors() override;
	void LoadColors() override;
private:

	robin_hood::unordered_flat_map<std::string, ImGuiCol_> MapNameAndIndex;
};

#endif // !BASE_COLORS_H
