#ifndef I8080_UI_REGISTER_FLAGS_INFO_H
#define I8080_UI_REGISTER_FLAGS_INFO_H

#include "UI/Theme/interface/IThemeLoadable.h"
#include "Emulator\Processors\Intel8080\I8080.h"
#include "Emulator/Processors/Intel8080/Disassembler/I8080.Disassembler.h"
#include "UI\Widget\I8080.Widget.h"
#include "Utils\ImGui.Utils.h"
#include <string>


class Widget_RegisterFlagsInfo : public I8080_Widget, public IThemeLoadable
{
public:
	Widget_RegisterFlagsInfo(I8080* processor);
	~Widget_RegisterFlagsInfo();
	void Draw() override;
	void Update() override;
	void InitLastState();

	std::string Save() override;
	void Load(const std::string& Data) override;

	void LoadColors() override;
	std::vector<NamedColor> GetDefaultLightColors() override;
	std::vector<NamedColor> GetDefaultDarkColors() override;

private:
	I8080* processor;
	CurrentState		   current_state;
	CurrentStateNotPointer    prev_state;
	ImVec4 color_Changed = ImVec4(1.f, 0.7f, 0.3f, 0.7f);
};



#endif // !I8080_UI_REGISTER_FLAGS_INFO_H
