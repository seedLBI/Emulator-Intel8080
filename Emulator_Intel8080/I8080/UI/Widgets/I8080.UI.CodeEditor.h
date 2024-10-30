#ifndef I8080_UI_CODE_EDITOR_H
#define I8080_UI_CODE_EDITOR_H


#include "Emulator\I8080.h"
#include "TextEditor.h"
#include "UI\Widget\I8080.Widget.h"
#include <string>


class Widget_CodeEditor : public I8080_Widget
{
public:
	Widget_CodeEditor();
	~Widget_CodeEditor();
	void Draw() override;
	void Update() override;

	std::string Save() override;
	void Load(const std::string& Data) override;

	void SetFlagWindow(int flag_value);
	bool GetFlagWindow();

	TextEditor* GetPtrTextEditor();

private:
	bool IsActive = false;

	TextEditor* editor;
	ImGuiWindowFlags flags_CodeEditor = 0;
};






#endif