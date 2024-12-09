#ifndef I8080_UI_MNEMOCODE_VIEWER_H
#define I8080_UI_MNEMOCODE_VIEWER_H


#include "Emulator\Processors\Intel8080\I8080.h"
#include "UI\Widget\I8080.Widget.h"
#include "Utils/ImGui.Utils.h"
#include <string>
#include "DataStructures\TypesCommand.h"
#include "UI/Setting/ISettingObject.h"


class Widget_MnemocodeViewer : public I8080_Widget, public ISettingObject
{
public:
	Widget_MnemocodeViewer(I8080* processor, TranslatorOutput* translator);
	~Widget_MnemocodeViewer();
	void Draw() override;
	void Update() override;

	void FollowCursorPC();
	void FollowCursor(int position);

	std::string Save() override;
	void Load(const std::string& Data) override;

	void ToggleFlagAlwaysFocus();

	void DrawMainMenu();
	void DrawSetting() override;
	std::string SaveSetting() override;
	void LoadSetting(const std::string& Data) override;
private:
	I8080* processor;
	TranslatorOutput* translator;

	int pos_follow = 0;

	bool flag_EnableAlwaysFocus = false;

}; 


#endif // !I8080_UI_MNEMOCODE_VIEWER_H
