#ifndef I8080_UI_CODE_EDITOR_H
#define I8080_UI_CODE_EDITOR_H

#include "TextEditor.h"
#include "Core/Emulator/Processors/Intel8080/I8080.h"
#include "Core/Widget/I8080.Widget.h"
#include "Utils/Timer/Timer.Framerate.h"
#include <string>


class Widget_CodeEditor : public I8080_Widget
{
public:
	Widget_CodeEditor(FPS_Timer* fps_timer);
	~Widget_CodeEditor();
	void Draw() override;
	void Update() override;

	nlohmann::json Save() override;
	void Load(const nlohmann::json& Data) override;

	void SetFlagWindow(int flag_value);
	bool GetFlagWindow();

	TextEditor* GetPtrTextEditor();

private:
	bool IsActive = false;
	FPS_Timer* fps_timer;
	TextEditor* editor;
	ImGuiWindowFlags flags_CodeEditor = 0;
};






#endif