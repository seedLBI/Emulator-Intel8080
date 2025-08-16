#ifndef I8080_UI_MNEMOCODE_VIEWER_H
#define I8080_UI_MNEMOCODE_VIEWER_H


#include <string>

#include "Core/Emulator/Processors/Intel8080/I8080.h"
#include "Core/Widget/I8080.Widget.h"
#include "Core/Setting/interfaces/ISettingObject.h"
#include "Core/Theme/interface/IThemeLoadable.h"

#include "Utils/ImGui/Utils.ImGui.h"

#include "DataStructures/TypesCommand.h"

#include "GUI/HighlighterInstruction/I8080/I8080.HighlighterInstruction.h"



class Widget_MnemocodeViewer : public I8080_Widget, public ISettingObject, public IThemeLoadable
{
public:
	Widget_MnemocodeViewer(I8080* processor, TranslatorOutput* translator);
	~Widget_MnemocodeViewer();
	void Draw() override;
	void Update() override;

	void FollowCursorPC();
	void FollowCursor(int position);

	nlohmann::json Save() override;
	void Load(const nlohmann::json& Data) override;

	void ToggleFlagAlwaysFocus();
	bool GetFlagAlwaysFocus();

	void DrawMainMenu();
	void DrawSetting() override;
	nlohmann::json SaveSetting() override;
	void LoadSetting(const nlohmann::json& Data) override;


	std::vector<NamedColor> GetDefaultLightColors() override;
	std::vector<NamedColor> GetDefaultDarkColors() override;
	void LoadColors() override;


private:
	I8080* processor;
	TranslatorOutput* translator;

	int pos_follow = 0;

	bool flag_EnableAlwaysFocus = false;

	ImColor color_Breakpoint = ImVec4(0.9f, 0.9f, 0.3f, 0.45f);
	ImColor color_PC = ImVec4(0.3f, 0.9f, 0.3f, 0.25f);
	ImColor color_Visited = ImVec4(0.9f, 0.2f, 0.9f, 0.25f);
	ImColor color_HL = ImVec4(0.1f, 0.1f, 1.f, 0.3f);

}; 


#endif // !I8080_UI_MNEMOCODE_VIEWER_H
